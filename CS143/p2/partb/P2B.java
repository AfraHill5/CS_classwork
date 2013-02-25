import java.io.*;
import java.text.*;
import java.util.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class P2B extends HttpServlet {
	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws IOException, ServletException {
		response.setContentType("text/html");
		PrintWriter out = response.getWriter();
		out.println("<html>");
		out.println("<head>");
		String title = "P2B Servlet"; //changed name from Copycat
		out.println("<title>" + title + "</title>");
		out.println("</head>");
		out.println("<body bgcolor=white>");
		out.println("<h1>" + title + "</h1>");
		//NEW: changed the request.getParameter to take input "menu" from the HTML menu
		String param = request.getParameter("menu");
		if (param != null)
			out.println("You requested " + param);
		out.println("</body>");
		out.println("</html>");
	}
}
