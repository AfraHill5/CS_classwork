import java.io.*;
import java.text.*;
import java.util.*;
import java.sql.*;
import javax.servlet.*;
import javax.servlet.http.*;

// UserEdit Servlet:
//
// Performs database updates on a User
// Capable of:
//      - Editing last name (OPID = 1)
//      - Editing middle name (OPID = 2)
//      - Editing first name (OPID = 3)
//      - Editing affiliation (OPID = 4)

public class UserEdit extends HttpServlet {

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
            String email = (String)session.getAttribute("email");
            String input = request.getParameter("input");

            out.println("<p>Currently logged in as " + email + ".</p>");
            out.println("<p><a href=../servlet/User>Back to user page.</a></p>");
            out.println("<p><a href=../UserEdit.html>Back to edit user info page.</a></p>");



            switch (OPID)
            {
                case "1":
                {
                    //change last name
                    if(input.isEmpty())
                    {
                        out.println("<p>Last name cannot be empty</p>");
                        break;
                    }

                    stmt.executeUpdate("UPDATE Person SET last_name='" + input + "' WHERE email='" + email + "';");
                    out.println("<p>Last name successfully changed to " + input + "</p>");
                    break;
                }

                case "2":
                {
                    //change middle name
                    stmt.executeUpdate("UPDATE Person SET middle_name='" + input + "' WHERE email='" + email + "';");
                    out.println("<p>Middle name successfully changed to " + input + "</p>");
                    break;
                }

                case "3":
                {
                    //change first name
                    stmt.executeUpdate("UPDATE Person SET first_name='" + input + "' WHERE email='" + email + "';");
                    out.println("<p>First name successfully changed to " + input + "</p>");
                    break;
                }

                case "4":
                {
                    //change first name
                    stmt.executeUpdate("UPDATE Person SET affiliation='" + input + "' WHERE email='" + email + "';");
                    out.println("<p>Affiliation successfully changed to " + input + "</p>");
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
