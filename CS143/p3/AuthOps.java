import java.io.*;
import java.text.*;
import java.util.*;
import java.sql.*;
import javax.servlet.*;
import javax.servlet.http.*;

// AuthOps Servlet:
//
// Performs database updates on Papers from the Author perspective.
// Capable of:
//  - creating new papers
//  - editing paper info
//  - adding coauthor information to paper

public class AuthOps extends HttpServlet {

    public void doGet(HttpServletRequest request,
                      HttpServletResponse response)
    throws IOException, ServletException {
    
        // Register MySQL JDBC driver
        try {
            // register the MySQL JDBC driver with DriverManager
            Class.forName("com.mysql.jdbc.Driver");
        } catch (Exception e) {
            e.printStackTrace();
        }


        HttpSession session = request.getSession(true);
        // get the output stream for result page
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();

        try {
            // connect to database
            Connection con = null;
            String url = "jdbc:mysql://localhost/cs143zno";
            String userName = "cs143zno";
            String password = "8hdsngnv";

            con = DriverManager.getConnection(url, userName, password);
            Statement stmt = con.createStatement();
            ResultSet rs;

            out.println("<html>");
            out.println("<head>");
           
            String OPID = request.getParameter("OPID");
            String pid = request.getParameter("pid"); //paper ID number in DB
            String email = (String)session.getAttribute("email");

            out.println("<p>Currently logged in as " + email + ".</p>");
            out.println("<p><a href=../servlet/User>Back to user page.</a></p>");
            out.println("<p><a href=../main.html>Logout</a></p>");
            out.println("<p>Selected Paper: " + pid + "</p>");




            switch (OPID)
            {
                case "0": //default, just display options
                {
                    //Paper data
                    rs = stmt.executeQuery("SELECT * FROM Paper WHERE id = " + pid);
                    rs.next(); //formatting
                    int conf = rs.getInt(5);
                    out.println("<p>This paper is in conference " + conf + ".</p>");
                    String status = rs.getString(6);
                    out.println("<p>This paper's status is currently: " + status + ".</p>");
                    if (status.equals("in review")) //can't modify paper once rev.
                    {
                        //Paper modifications
                        out.println("<h3>Edit paper information: </h3>");

                        out.println("<form method=get action=AuthOps>");
                        out.println("<p>Change title: <input type=text name='title' size=40> </p>");
                        out.println("<input type='hidden' name='OPID' value='2'>");
                        out.println("<input type='hidden' name='pid' value='" + pid + "'>");
                        out.println("<input type='submit' name='sub' value='Submit'>");
                        out.println("</form>");

                        out.println("<form method=get action=AuthOps>");
                        out.println("<p>Change abstract: <input type=text name='abstract' size=40> </p>");
                        out.println("<input type='hidden' name='OPID' value='3'>");
                        out.println("<input type='hidden' name='pid' value='" + pid + "'>");
                        out.println("<input type='submit' name='sub' value='Submit'>");
                        out.println("</form>");

                        out.println("<form method=get action=AuthOps>");
                        out.println("<p>Change content: <input type=text name='content' size=40> </p>");
                        out.println("<input type='hidden' name='OPID' value='4'>");
                        out.println("<input type='hidden' name='pid' value='" + pid + "'>");
                        out.println("<input type='submit' name='sub' value='Submit'>");
                        out.println("</form>");
                    
                        out.println("<form method=get action=AuthOps>");
                        out.println("<p>Add a coauthor: <input type=text name='coauthor' size=40> </p>");
                        out.println("<input type='hidden' name='OPID' value='5'>");
                        out.println("<input type='hidden' name='pid' value='" + pid + "'>");
                        out.println("<input type='submit' name='sub' value='Submit'>");
                        out.println("</form>");
                    }
                    else // Conference is over, display results for paper
                    {
                        out.println("<h1>Conference results:</h1>");
                        rs = stmt.executeQuery("SELECT email, score, comments FROM Reviewer WHERE paper_id = " + pid);
                        while(rs.next())
                        {
                            String reviewer = rs.getString(1);
                            String score = rs.getString(2);
                            String comments = rs.getString(3);

                            out.println("<p>Reviewer: " + reviewer + "</p>");
                            out.println("<p>Score: " + score + "   Comments: " + comments + "</p><br>");
                        }
                    }
                }   break;
                case "1": //create new paper
                {
                    String title = request.getParameter("title");
                    if(title.isEmpty())
                    {
                        out.println("Please enter a title.");
                        break;
                    }
                    String abs = request.getParameter("abstract");
                    if(abs.isEmpty())
                    {
                        abs = "null";
                    }
                    String content = request.getParameter("content");
                    if(content.isEmpty())
                    {
                        content = "null";
                    }
                    String conf = request.getParameter("conf");
                    if(conf.isEmpty())
                    {
                        out.println("Paper must be submitted to a conference. Enter a conference id.");
                        break;
                    }

                    rs = stmt.executeQuery("SELECT * FROM Conference WHERE id = "+conf);
                    if(!rs.next())
                    {
                        out.println("No conference exists with id " + conf);
                        break;
                    }
                    
                    //get the id number of the paper
                    rs = stmt.executeQuery("SELECT MAX(ID)+1 FROM Paper");
                    rs.next(); //formatting
                    int id = rs.getInt(1);

                    if (title.length() > 50) title = title.substring(0,50);
                    if (abs.length() > 50) abs = abs.substring(0,50);
                    if (content.length() > 50) content = content.substring(0,50);
                    String update = "INSERT INTO Paper VALUES (";
                    update += id + ", '" + title + "', '" + abs + "', '" + content;
                    update += "', " +  conf + ", 'in review')";
                    //debug
                    out.println("<p>" + update + "</p>");
                    stmt.executeUpdate(update);

                    //now need to update Author
                    update = "INSERT INTO Author VALUES('" + email + "', " + id + ")";
                    out.println("<p>" + update + "</p>");
                    stmt.executeUpdate(update);

                    out.println("<p>Successfully added new paper " + title + " with id=" + id + ".</p>");
                    break;
                }
                case "2": //update title
                {
                    String title = request.getParameter("title");
                    String update = "UPDATE Paper SET title='" + title + "'WHERE id=" + pid;
                    //debug
                    out.println("<p>" + update + "</p>");
                    stmt.executeUpdate(update);
                    break;
                }


                case "3": //update abstract
                {
                    String abs = request.getParameter("abstract");
                    String update = "UPDATE Paper SET abstract='" + abs + "'WHERE id=" + pid;
                    //debug
                    out.println("<p>" + update + "</p>");
                    stmt.executeUpdate(update);
                    break;
                }
                case "4": //update paper content
                {
                    String content = request.getParameter("content");
                    String update = "UPDATE Paper SET content='" + content + "'WHERE id=" + pid;
                    //debug
                    out.println("<p>" + update + "</p>");
                    stmt.executeUpdate(update);
                    break;
                }
                case "5":
                {
                    String coauthor = request.getParameter("coauthor");
                    //First check if the author exists and break if they do not
                    rs = stmt.executeQuery("SELECT * FROM Person WHERE email='" + coauthor + "' AND isChair<>1;");
                    if (!rs.next()) //author doesn't exist, so don't insert
                        out.println("<p>That author doesn't exist or cannot be an author. Please try a different author.</p>");
                    else  //good to go
                    {
                        String dupCheck = "SELECT * FROM Author WHERE email='" + coauthor + "'AND paper_id=" + pid;
                        rs = stmt.executeQuery(dupCheck);
                        if (rs.next()) //already exists
                            out.println("<p>That author is already a coauthor of this paper.</p>");
                        else
                        {

                            String update = "INSERT INTO Author VALUES('" + coauthor + "', " + pid + ")";
                            //debug
                            out.println("<p>" + update + "</p>");
                            stmt.executeUpdate(update);
                        }
                    }
                    break;
                }

                default:
                {
                    out.println("UNKNOWN OPERATION ID: " + OPID + "<br>");
                    break;
                }
            }

            out.println("</body>");
            out.println("</html>");
            stmt.close();
            con.close();
        } catch (SQLException ex) {
            out.println("SQLException caught<br>");
            out.println("---<br>");
            while (ex != null) {
                out.println("Message    : " + ex.getMessage() + "<br>");
                out.println("SQLState   : " + ex.getSQLState() + "<br>");
                out.println("ErrorCode  : " + ex.getErrorCode() + "<br>");
                out.println("---<br>");
                ex = ex.getNextException();
            }
        }
    }
}
