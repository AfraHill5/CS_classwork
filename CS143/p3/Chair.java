import java.io.*;
import java.text.*;
import java.util.*;
import java.sql.*;
import javax.servlet.*;
import javax.servlet.http.*;

// Chair Servlet:
// 
// Perform operations specific to a chair: 
//    - creates conferences
//    - adds reviewer to a conference
//    - manually assigns each paper in a conference to a reviewer
//    - triggers computation of paper final decision (accept or reject)
//    - modifies conference info
//
// Logs in to User Page and displays information/options

public class Chair extends HttpServlet {

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

            // Get user information
            String email = (String)session.getAttribute("email");
            if(email.isEmpty())
            {
                throw new Exception(); //some sort of error
            }

            // Check to make sure Person is in database
            ResultSet rs = stmt.executeQuery("SELECT * FROM Person WHERE email = \"" + email + "\"");
            if(!rs.next())
            {
                throw new Exception();
            }

            
            out.println("SESSION ID: " + session.getAttribute("email"));
            out.println("<a href = ../servlet/User>Back to user page</a>");

            out.println("This is where Chair Shit will go if Person is chair.<br><br>");
            out.println("This is where Reviewer Shit will go if Person is reviewer.<br><br>");
            out.println("This is where Author shit will go if Person is author.<br><br><br>");
            out.println("It's all shit. That's what I'm getting at.<br>");

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
        catch (Exception no_email_ex)
        {
            out.println("ERROR: session error. Please log back in and try again.");
            out.println("</body>");
            out.println("</html>");
        }
    }
}
