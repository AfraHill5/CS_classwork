import java.io.*;
import java.text.*;
import java.util.*;
import java.sql.*;
import javax.servlet.*;
import javax.servlet.http.*;

// RevOps Servlet:
//
// Performs database updates from the Reviewer perspective.
// Capable of:
//  - submitting reviews for each assigned paper before the review period ends
//  - reading information on each assigned paper

public class RevOps extends HttpServlet {

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
            String conference = request.getParameter("cid");
            String email = (String)session.getAttribute("email");

            out.println("<p>Currently logged in as " + email + ".</p>");
            out.println("<p><a href=../servlet/User>Back to user page.</a></p>");
            out.println("<p><a href=../main.html>Logout</a></p>");
            out.println("<h2>Selected Conference: " + conference + "</h2>");

            switch(OPID)
            {
                case "0": //list papers reviewer needs to review and prompt for reviews
                {
                    out.println("<h3><b>Papers in Conference</b></h3>");
                    //get all the papers in this conference that Reviewer needs to review
              
                    rs = stmt.executeQuery("SELECT * FROM Reviewer WHERE email='"+email+"' AND conference_id = "+conference+" AND paper_id IS NOT NULL");
                    ArrayList papersAssigned = new ArrayList();
                    while(rs.next())
                    {
                        String s = rs.getString(3);
                        int paper_id = Integer.parseInt(s);
                        papersAssigned.add(paper_id);
                    }
                    for(int i = 0; i < papersAssigned.size(); i++)
                    {
                        int id = (int) papersAssigned.get(i);
                        rs = stmt.executeQuery("SELECT * FROM Paper WHERE id="+id);

                        while(rs.next())
                        {
                            String title = rs.getString(2);
                            String abs = rs.getString(3);
                            String content = rs.getString(4);
                            String status = rs.getString(6);

                            out.println("<p><u>Paper " + id + "</u></p>");
                            out.println("<p>Title: " + title + "</p>");
                            out.println("<p>Abstract: " + abs + "</p>");
                            out.println("<p>Content: " + content + "</p>");
                            out.println("<p><i>Review status: " + status + "</i></p>");

                            if(status.equals("in review"))
                            {
                                out.println("<p><a href=RevOps?cid="+conference+"&OPID=1&pid="+id+">Submit review</a></p>");
                            }
                            out.println("<br>");
                        }
                    }
                } break;

                case "1"://enter stuff for review
                {
                    String pid = request.getParameter("pid");
                    out.println("<h2>Review for Paper " + pid + "</h2>");
                    out.println("<form method=get action=RevOps>");


                    out.println("<p>Comments: <input type=text name='comments' size=40> </p>");

                    out.println("<p>Review Score: </p>");
                    out.println("<select name='score'>");
                    out.println("<option selected>1");
                    out.println("<option>2");
                    out.println("<option>3");
                    out.println("<option>4");
                    out.println("<option>5");
                    out.println("<option>6");
                    out.println("<option>7");
                    out.println("</select>");


                    out.println("<input type=hidden name='OPID' value='2'>");
                    out.println("<input type=hidden name='cid' value='" + conference + "'>");
                    out.println("<input type=hidden name='pid' value='" + pid + "'>");
                    out.println("<p><input type=submit name='sub' value='Submit'> </p>");
                    out.println("</form>");
               

                    break;
                }


                case "2":
                {
                    String pid = request.getParameter("pid");
                    String comments = request.getParameter("comments");
                    String score = request.getParameter("score");

                    String update = "UPDATE Reviewer SET score=" + score + ", comments='" + comments +"' WHERE email='" + email + "' AND paper_id=" + pid ;
                    stmt.executeUpdate(update);
                    out.println("<p>" + update + "</p>");
                    out.println("<p>Review has been recorded. Score = " + score + "</p>");
                    break;

                }
                case "3":

                case "4":

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
