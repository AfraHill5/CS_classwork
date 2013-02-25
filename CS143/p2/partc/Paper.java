import java.io.*;
import java.text.*;
import java.util.*;
import java.sql.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class Paper extends HttpServlet {

	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws IOException, ServletException {
		//
		// Register MySQL JDBC driver
		//

		try {
			// register the MySQL JDBC driver with DriverManager
			Class.forName("com.mysql.jdbc.Driver");
		} catch (Exception e) {
			e.printStackTrace();
		}

		//
		// get the output stream for result page
		//

		response.setContentType("text/html");
		PrintWriter out = response.getWriter();

		try {
			//
			// Connect to the database
			//

			Connection con = null;

			//
			// URL is jdbc:mysql:dbname
			// Change CS143 to the right database that you use
			//
			String url = "jdbc:mysql://localhost/cs143zno";
			String userName = "cs143zno";
			String password = "8hdsngnv";

			// connect to the database, user name and password can be specified
			// through this method
			con = DriverManager.getConnection(url, userName, password);

			//
			// Execute a SQL statement and print out the result
			//

			// Execute a SQL statement
			Statement stmt = con.createStatement();
			ResultSet rs = stmt.executeQuery("SELECT * FROM Paper");

			// print out the result
			out.println("<html>");
			out.println("<head>");
			String title = "Paper Servlet";
			out.println("<title>" + title + "</title>");
			out.println("</head>");
			out.println("<body bgcolor=white>");
			out.println("<h1>" + title + "</h1>");

			out.println("Received results:<p>");
			out.println("<table border=\"1\">");
            out.println("<tr><th>ID</th><th>paper_id</th><th>title_str</th><th>authors_str</th><th>area</th><th>num_abstract_words</th><th>num_authors</th><th>num_kb</th><th>num_pages</th><th>num_revisions</th><th>num_title_wds</th><th>comments_str</th><th>submit_date</th><th>submitter_email</th><th>submitter_name</th></tr>");
			// print the result set
			// rs.next() returns false when there are no more rows
			while (rs.next()) {
				int id =                    rs.getInt(1);
                int paper_id =              rs.getInt(2);
                String title_str =          rs.getString(3);
                String authors_str =        rs.getString(4);
                String area =               rs.getString(5);
                int num_abstract_words =    rs.getInt(6);
                int num_authors =           rs.getInt(7);
                int num_kb =                rs.getInt(8);
                int num_pages =             rs.getInt(9);
                int num_revisions =         rs.getInt(10);
                int num_title_wds =         rs.getInt(11);
                String comments_str =       rs.getString(12);
                int submit_date =           rs.getInt(13);
                String submitter_email =    rs.getString(14);
                String submitter_name =     rs.getString(15);

                out.println("<tr><td>" + id +           "</td><td>" + paper_id
						+ "</td><td>" + title_str +     "</td><td>" + authors_str
						+ "</td><td>" + area +          "</td><td>" + num_abstract_words
						+ "</td><td>" + num_authors +   "</td><td>" + num_kb
						+ "</td><td>" + num_pages +     "</td><td>" + num_revisions
						+ "</td><td>" + num_title_wds + "</td><td>" + comments_str
						+ "</td><td>" + submit_date +   "</td><td>" + submitter_email
						+ "</td><td>" + submitter_name + "</td></tr>");
			}
			out.println("</table>");
			out.println("</body>");
			out.println("</html>");

			rs.close();
			stmt.close();
			con.close();
		} catch (SQLException ex) {
			out.println("SQLException caught<br>");
			out.println("---<br>");
			while (ex != null) {
				out.println("Message   : " + ex.getMessage() + "<br>");
				out.println("SQLState  : " + ex.getSQLState() + "<br>");
				out.println("ErrorCode : " + ex.getErrorCode() + "<br>");
				out.println("---<br>");
				ex = ex.getNextException();
			}
		}
	}
}
