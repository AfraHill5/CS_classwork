import java.io.*;
import java.text.*;
import java.util.*;
import java.sql.*;
import javax.servlet.*;
import javax.servlet.http.*;

// User Servlet:
// 
// Perform operations specific to a user
//
// Logs in to User Page and displays information/options

public class User extends HttpServlet {

    public void doGet(HttpServletRequest request, HttpServletResponse response)
    throws IOException, ServletException
    {
        try
        {
            Class.forName("com.mysql.jdbc.Driver");
        }
        catch (Exception e)
        {
            e.printStackTrace();
        }

        HttpSession session = request.getSession(true);
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();

        ResultSet rs;

        try
        {
            Connection con = null;
            String url = "jdbc:mysql://localhost/cs143zno";
            String userName = "cs143zno";
            String password = "8hdsngnv";

            con = DriverManager.getConnection(url, userName, password);
            Statement stmt = con.createStatement();

            out.println("<html>");
            out.println("<head>");
            out.println("<body>");

            // Get user information
            String email = request.getParameter("email");
            if (email != null) //a new email was passed in
            {
                if(email.isEmpty())
                {
                    out.println("Please enter an email.");
                    throw new Exception();
                }
                else
                {
                    out.println("Received email: " + email + "<br>");
                }


                String pword = request.getParameter("password"); //password is last name
                rs = stmt.executeQuery("SELECT * FROM Person WHERE email='" + email + "' AND last_name='" + pword + "';");
                if(rs.next())
                {
                    out.println("<p>Received valid password.</p>");
                }
                else
                {
                    out.println("<p>Password incorrect.</p>");
                    out.println("<a href = ../main.html>Back to login page.</a>");
                    throw new Exception();
                }

            
                // Check to make sure Person is in database
                rs = stmt.executeQuery("SELECT * FROM Person WHERE email = \"" + email + "\"");
                if(!rs.next())
                {
                    out.println("Invalid User Name and Password.<br>");
                    out.println("<a href = ../main.html>Login with a different account, or add a new account.</a>");
                    throw new Exception();
                }


                session.setAttribute("email", email);
            }
            else // should keep email throughout session
            {
                email = (String)session.getAttribute("email");
                if (!email.isEmpty())
                    out.println("Welcome back, " + email + "<br>");
                else //error
                {
                    throw new Exception();
                }
            }

            rs = stmt.executeQuery("SELECT * FROM Person WHERE email = \"" + email + "\"");
            rs.next();

            // Get person's full name
            String person_last_name = rs.getString(2); // Won't be null, it's their password

            String person_middle_name = rs.getString(3);
            if (person_middle_name == null)
            {
                person_middle_name = "";
            }

            String person_first_name = rs.getString(4);
            if (person_first_name == null)
            {
                person_first_name = "";
            }
            else
            {
                person_first_name = ", " + person_first_name;
            }

            String person_name = person_last_name + person_first_name + " " + person_middle_name;

            // Get person's affiliation
            String person_affil = rs.getString(5);
            if (person_affil == null)
            {
                person_affil = "No Affiliation";
            }

            out.println("<h1>" + person_name +"</h1><p>" + person_affil + "</p>");
            
            out.println("SESSION ID: " + session.getAttribute("email"));
            out.println("<p><a href = ../UserEdit.html>Edit User Information.</a></p>");
            out.println("<p><a href = ../main.html>Logout</a></p>");
            
            rs = stmt.executeQuery("SELECT * FROM Person WHERE email = '" + email + "' AND isChair = 1");
            //check if user is a chair'
            if (rs.next())
            {   
                out.println("<h2>Chair Info</h2>");
                out.println("<p><a href=../NewConf.html>Create new conference</a></p>");
           
                rs = stmt.executeQuery("SELECT * FROM Conference");
                while (rs.next())
                {
                    //list the conferences
                    String conf_id = rs.getString(1);
                    String conf_name = rs.getString(2);


                    // check to see if conference is over
                    boolean over = false;
                    Connection temp_con = DriverManager.getConnection(url, userName, password);
                    Statement temp_stmt = temp_con.createStatement();
                    ResultSet temp_rs = null;

                    temp_rs = temp_stmt.executeQuery("SELECT decision_status FROM Paper WHERE conference = " + conf_id);
                    if(temp_rs.next())
                    {
                        String decision = temp_rs.getString(1);
                        if(!(decision.equals("in review")))
                        {
                            over = true;
                        }
                    }
                    
                    if(!over)
                    {
                        out.println("<p><a href=./ChairOps?cid=" + conf_id +"&OPID=0>Manage conference " + conf_name + "</a></p>");
                    }
                    else
                    {
                        out.println("<p>Conference " + conf_name + " has ended.</p>");
                    }

                    temp_rs.close();
                    temp_stmt.close();
                    temp_con.close();

                }
            }
            else //can't be a chair and other 
            {

                out.println("<h2>Reviewer Info</h2>");
                rs = stmt.executeQuery("SELECT DISTINCT conference_id FROM Reviewer WHERE email = \"" + email + "\";");
                while (rs.next())
                {
                    // list the conferences where the user is a reviewer
                    
                    // get conference names
                    Connection temp_con = DriverManager.getConnection(url, userName, password);
                    Statement temp_stmt = temp_con.createStatement();
                    ResultSet temp_rs = null;

                    String rev_id = rs.getString(1);
                    temp_rs = temp_stmt.executeQuery("SELECT name FROM Conference WHERE id = "+rev_id);
                    temp_rs.next();
                    String conf_name = temp_rs.getString(1);

                    // Check to see if conference is over
                    boolean over = false;
                    temp_rs = temp_stmt.executeQuery("SELECT decision_status FROM Paper WHERE conference = "+rev_id);
                    if(temp_rs.next())
                    {
                        String decision = temp_rs.getString(1);
                        if(!(decision.equals("in review")))
                        {
                            over = true;
                        }
                    }
                    
                    if (!over)
                    {
                        out.println("<p><a href=./RevOps?cid=" + rev_id +"&OPID=0>Review conference " +conf_name + "</a></p>");
                        //pass through the data about the user to conference to get review screen
                    }
                    else
                    {
                        out.println("<p>Conference " + conf_name + " over.</p>");
                    }
                    
                    temp_rs.close();
                    temp_stmt.close();
                    temp_con.close();
                }


                out.println("<h2>Author Info</h2>");
                out.println("<p><a href=../NewPap.html>Create new paper</a></p>");
                rs = stmt.executeQuery("SELECT * FROM Author WHERE email = \"" + email + "\";");
               
                while (rs.next())
                {
                    //list the papers the user is an author of
                    String pap_id = rs.getString(2);

                    Connection temp_con = DriverManager.getConnection(url, userName, password);
                    Statement temp_stmt = temp_con.createStatement();
                    ResultSet temp_rs = null;
                    
                    temp_rs = temp_stmt.executeQuery("SELECT title FROM Paper where id = " + pap_id);
                    temp_rs.next();
                    String pap_title = temp_rs.getString(1);

                    out.println("<p><a href=./AuthOps?pid=" + pap_id +"&OPID=0>Manage paper " + pap_title + "</a></p>");

                    temp_rs.close();
                    temp_stmt.close();
                    temp_con.close();
                }
            }

            out.println("</body>");
            out.println("</html>");
            
            rs.close();
            stmt.close();
            con.close();
        }
        
        catch (SQLException ex)
        {
            out.println("SQLException caught<br>");
            out.println("---<br>");
            while (ex != null)
            {
                out.println("Message    : " + ex.getMessage() + "<br>");
                out.println("SQLState   : " + ex.getSQLState() + "<br>");
                out.println("ErrorCode  : " + ex.getErrorCode() + "<br>");
                out.println("---<br>");
                ex = ex.getNextException();
            }
        }
        
        catch (Exception no_user_ex)
        {
            //Should already display error message

        }
    }
}
