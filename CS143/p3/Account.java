import java.io.*;
import java.text.*;
import java.util.*;
import java.sql.*;
import javax.servlet.*;
import javax.servlet.http.*;

// Account Servlet:
//
// Performs database updates and queries pertaining to
// user accounts (in Person table)
//
// Capable of:
//      - Creating new accounts (OPID 1)
//      - Resetting Account table (OPID 66)

public class Account extends HttpServlet {

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

            out.println("<html>");
            out.println("<head>");


            String OPID = request.getParameter("OPID");

            switch (OPID)
            {
                // Create a new user
                case "1":
                {
                    // Get inputs from users
                    String email =  request.getParameter("email");
                    if (!email.isEmpty())
                    {
                        out.println("Received Email: " + email + "<br>");
                    }
                    else
                    {
                        out.println("Please Enter an email.<br>");
                        out.println("<a href = ../main.html>Back to login page</a>");
                        break;
                    }

                    String last_name = request.getParameter("last_name");
                    if (!last_name.isEmpty())
                    {
                        out.println("Received Last Name: " + last_name + "<br>");
                    }
                    else
                    {
                        out.println("Please Enter a last name.<br>");
                        out.println("<a href = ../main.html>Back to login page</a>");
                        break;
                    }

                    // Check to see if user already exists
                    ResultSet rs = stmt.executeQuery("SELECT * FROM Person WHERE email = \"" + email + "\"");
                    if(rs.next())
                    {
                        out.println("User already exists with given email.<br>");
                        out.println("<a href = ../main.html>Enter a new email or Login with existing account.");
                        break;
                    }

                    // Create new Person
                    stmt.executeUpdate("INSERT INTO Person VALUES (\""+email+"\",\""+last_name+"\",null,null,null,0)");
                    out.println("<title>New User Created</title>");
                    out.println("Email/User Name: " + email + "<br>");
                    out.println("Password: " + last_name + "<br>");
                    out.println("<a href = ../main.html>Back to Login Page</a>");


                    rs.close();
                } break;
                // Reset all Account Information
                case "66":
                {
                    stmt.executeUpdate("DELETE FROM Person");
                    stmt.executeUpdate("DELETE FROM Conference");
                    stmt.executeUpdate("DELETE FROM Paper");
                    stmt.executeUpdate("DELETE FROM Author");
                    stmt.executeUpdate("DELETE FROM Reviewer");
                    out.println("Databases Reset.<br>");
                } break;
                default:
                {
                    out.println("UNKNOWN OPERATION ID: " + OPID + "<br>");
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
