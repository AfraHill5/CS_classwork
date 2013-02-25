import java.io.*;
import java.text.*;
import java.util.*;
import java.sql.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class ServletOps extends HttpServlet {

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


            /* OPERATION ID |  RELATED FILE(S)   |  DESCRIPTION
             * -------------|--------------------|-------------------
             *              |                    | Adds an Author to 
             * 1            | i1.html            | a Paper (updates
             *              |                    | CoAuthor info too)
             * -------------|--------------------|-------------------
             *              |                    | Adds citation
             * 2            | i2.html            | between two Papeers
             *              |                    |
             * -------------|--------------------|--------------------
             *              |                    | Adds comments to
             * 3            | i3.html            | Papers
             *              |                    |
             * -------------|--------------------|--------------------
             *              |                    | Adds papers to
             * 4            | i4.html            | database (must
             *              |                    | provide Author)
             * -------------|--------------------|---------------------
             *              |                    | Searches database
             *  5           | s1.html            | by keyword (Title
             *              |                    | or Author)
             * -------------|--------------------|---------------------
             *              |                    | Displays Paper
             *  6           | b1.html (s1.html)  | information for
             *              |                    | specific Paper
             * -------------|--------------------|----------------------
             *              |                    | Displays Author
             *  7           | b2.html (s1.html)  | information for
             *              |                    | specific Author
             * -------------|--------------------|----------------------
             *              |                    | Add a new author
             *  8           | addauther.html     | to the database
             *              |                    | with given name
             */
            switch (OPID)
            {
                case "1":
                {
	    	        String title = "Add an Author";
	    	        out.println("<title>" + title + "</title>");
	    	        out.println("</head>");
	    	        out.println("<body bgcolor=white>");
	    	        out.println("<h1>" + title + "</h1>");

                    String paper_id = request.getParameter("paper_id");
                    if (!paper_id.isEmpty())
			            out.println("Received Paper ID: " + paper_id + "<br>");
                    else
                    {
                        out.println("Please Enter a Paper ID.<br>");
                        out.println("<a href = ../i1.html>Back to input page</a>");
                        break;
                    }
                    String author_id = request.getParameter("author_id");
                    if (!author_id.isEmpty())
                        out.println("Received Author ID: " + author_id + "<br><br>");
                    else
                    {
                        out.println("Please Enter an Author ID.<br>");
                        out.println("<a href = ../i1.html>Back to input page</a>");
                        break;
                    }

                    
                    // Check to see if Paper exists with input ID
                    ResultSet rs = stmt.executeQuery("SELECT * FROM Paper WHERE ID = \"" + paper_id + "\"");
                    if (!rs.next())
                    {
                        out.println("No Paper found with ID = " + paper_id + "<br>");
                        out.println("<a href = ../i1.html>Back to input page</a>");
                        break;
                    }

                    // Check to see if Author exists with input ID
                    rs = stmt.executeQuery("SELECT * FROM Author WHERE ID = \"" + author_id + "\"");
                    if (!rs.next())
                    {
                        out.println("No Author found with ID = " + author_id + "<br>");
                        out.println("<a href = ../i1.html>Back to input page</a>");
                        break;
                    }

                    // Check to see if Author is already Author of paper 
                    rs = stmt.executeQuery("SELECT * FROM Authored WHERE AuthorID = " + author_id +
                                           " AND paperID = " + paper_id);
                    if (rs.next())
                    {
                        out.println("Author with ID " + author_id +
                                    " is already listed as an author of Paper with ID " + paper_id + "<br>");
                        out.println("<a href = ../i1.html>Back to input page</a>");
                        break;
                    }
                    
                    // Insert new Author/Paper pair into Authored
                    rs = stmt.executeQuery("SELECT MAX(ID)+1 FROM Authored");
                    rs.next();
                    int new_authored_id = rs.getInt(1);

                    rs = stmt.executeQuery("SELECT COUNT(*)+1 FROM Authored WHERE paperID = " + paper_id);
                    rs.next();
                    int new_rank = rs.getInt(1);

                    stmt.executeUpdate("INSERT INTO Authored VALUES ("+new_authored_id+","+author_id+","+paper_id+",null,"+new_rank+",null,null,null,null,null)");
                    out.println("Added Author " + author_id + " to Paper " + paper_id + "<br><br>");

                    // Insert new coauthor information into CoAuthored
                    rs = stmt.executeQuery("SELECT * FROM Authored WHERE paperID = " + paper_id);
                    while(rs.next())
                    {
                        // Establish new connection
                        Connection temp_con = DriverManager.getConnection(url, userName, password);
                        Statement temp_stmt = temp_con.createStatement();

                        int other_author_id = rs.getInt("AuthorID");
                        if(Integer.parseInt(author_id) != other_author_id)
                        {
                            temp_stmt.executeUpdate("INSERT INTO CoAuthored VALUES( (SELECT MAX(T.ID)+1 FROM (SELECT * FROM CoAuthored) as T) ," 
                                               + author_id + ","+other_author_id+","+paper_id+")");
                            out.println("Added Author " + author_id + " as coauthor of Author " + other_author_id + "<br>");
                            temp_stmt.executeUpdate("INSERT INTO CoAuthored VALUES( (SELECT MAX(T.ID)+1 FROM (SELECT * FROM CoAuthored) as T)," +
                                               other_author_id + ", " + author_id + ", " + paper_id + ")");
                            out.println("Added Author " + other_author_id + " as coauthor of Author " + author_id + "<br><br>");
                        }

                        temp_stmt.close();
                        temp_con.close();
                    }
                    rs.close();
                } break;
                case "2":
                {
	    	        String title = "Add a Citation";
	    	        out.println("<title>" + title + "</title>");
	    	        out.println("</head>");
	    	        out.println("<body bgcolor=white>");
	    	        out.println("<h1>" + title + "</h1>");


                    String paper_id = request.getParameter("paper_id");
                    if (paper_id.isEmpty())
                    {
                        out.println("Please enter a Paper ID.<br>");
                        out.println("<a href = ../i2.html>Back to input page</a>");
                        break;
                    }
                    String citation_id = request.getParameter("citation_id");
                    if (citation_id.isEmpty())
                    {
                        out.println("Please enter a Citation (Paper) ID<br>");
                        out.println("<a href = ../i2.html>Back to input page</a>");
                        break;
                    }
                    
                    out.println("Received Paper ID: " + paper_id + "<br>");
                    out.println("Received Citation ID: " + citation_id + "<br><br>");


                    // Check to see if Paper exists with input ID
                    ResultSet rs = stmt.executeQuery("SELECT * FROM Paper WHERE ID = \"" + paper_id + "\"");
                    if (!rs.next())
                    {
                        out.println("No Paper found with ID = " + paper_id + "<br>");
                        out.println("<a href = ../i2.html>Back to input page</a>");
                        break;
                    }

                    // Check to see if Paper exists with citation input ID
                    rs = stmt.executeQuery("SELECT * FROM Paper WHERE ID = \"" + citation_id + "\"");
                    if (!rs.next())
                    {
                        out.println("No Paper found with ID = " + citation_id + "<br>");
                        out.println("<a href = ../i2.html>Back to input page</a>");
                        break;
                    }

                    // Check to see if Paper is already cited by other paper
                    rs = stmt.executeQuery("SELECT * FROM Cites WHERE paper1ID = " + paper_id + " AND paper2ID = " + citation_id);
                    if (rs.next())
                    {
                        out.println("Paper " + paper_id + " already cites Paper " +citation_id + "<br>");
                        out.println("<a href = ../i2.html>Back to input page</a>");
                        break;
                    }
                    
                    // Insert new citation into Cites
                    int self_citation = 0;
                    if (paper_id.equals(citation_id))
                    {
                        self_citation++;
                    }
                    stmt.executeUpdate("INSERT INTO Cites VALUES ((SELECT MAX(T.ID)+1 FROM (SELECT * FROM Cites) as T)," + paper_id + "," + citation_id + "," + self_citation + ")");
                    rs.close();
                } break;
                case "3":
                {
	    	        String title = "Add a Comment";
	    	        out.println("<title>" + title + "</title>");
	    	        out.println("</head>");
	    	        out.println("<body bgcolor=white>");
	    	        out.println("<h1>" + title + "</h1>");

                    String paper_id = request.getParameter("paper_id");
                    if (paper_id.isEmpty())
                    {
                        out.println("Please enter a Paper ID.<br>");
                        out.println("<a href = ../i3.html>Back to input page</a>");
                        break;
                    }
                    String comment = request.getParameter("comment");
                    if (comment.isEmpty())
                    {
                        out.println("Please enter a Comment<br>");
                        out.println("<a href = ../i3.html>Back to input page</a>");
                        break;
                    }
                    
                    out.println("Received Paper ID: " + paper_id + "<br>");
                    out.println("Received Comment: " + comment + "<br><br>");

                    ResultSet rs = stmt.executeQuery("SELECT comments_str FROM Paper WHERE ID = \"" + paper_id + "\"");
                    if(!rs.next())
                    {
                        out.println("No Paper found with ID " + paper_id + "<br>");
                        out.println("<a href = ../i3.html>Back to input page</a>");
                        break;
                    }

                    String cmt = rs.getString(1);
                    cmt += ", ";
                    cmt += comment;
                    if(cmt.length() >= 1000)
                    {
                        out.println("Comment too large. Resizing.<br>");
                        cmt = cmt.substring(0,999);
                    }

                    stmt.executeUpdate("UPDATE Paper SET comments_str = \"" + cmt + "\" WHERE ID = " + paper_id);
                    out.println("The comment is now \"" + cmt + "\" on paper " + paper_id);

                    rs.close();

                } break;
                case "4":
                {
	    	        String title = "Add a Paper";
	    	        out.println("<title>" + title + "</title>");
	    	        out.println("</head>");
	    	        out.println("<body bgcolor=white>");
	    	        out.println("<h1>" + title + "</h1>");
                    
                    String author_id = request.getParameter("author_id");
                    if (author_id.isEmpty())
                    {
                        out.println("Please enter a Author ID.<br>");
                        out.println("<a href = ../i4.html>Back to input page</a>");
                        break;
                    }
                    String paper_title = request.getParameter("paper_title");
                    if (paper_title.isEmpty())
                    {
                        out.println("Please enter a Paper Title<br>");
                        out.println("<a href = ../i4.html>Back to input page</a>");
                        break;
                    }

                    out.println("Received Author ID: " + author_id + "<br>");
                    out.println("Received Paper Title: " + paper_title + "<br><br>");
                    
                    ResultSet rs = stmt.executeQuery("SELECT * FROM Author WHERE ID = \"" + author_id + "\"");
                    if (!rs.next())
                    {
                        out.println("Author " + author_id + " does not exist.<br>");
                        out.println("<a href = ../i4.html>Back to input page</a>");
                        break;
                    }
                    
                    //Find new Paper id (ID)
                    int new_ID = 0;
                    int new_paper_id = 0;
                    rs = stmt.executeQuery("SELECT MAX(ID) FROM Paper");
                    if(rs.next())
                    {
                        new_ID = rs.getInt(1) + 1;
                    }
                    // (paper_id)
                    rs = stmt.executeQuery("SELECT MAX(paper_id) FROM Paper");
                    if(rs.next())
                    {
                        new_paper_id = rs.getInt(1) + 1;
                    }

                    //Find new Authored ID
                    int new_authored_id = 0;
                    rs = stmt.executeQuery("SELECT MAX(ID) FROM Authored");
                    if(rs.next())
                    {
                        new_authored_id = rs.getInt(1) + 1;
                    }

                    // Add new paper into Paper table
                    stmt.executeUpdate("INSERT INTO Paper VALUES ("+new_ID+","+new_paper_id+", \"" + paper_title + "\", null,null,null,null,null,null,null,null,null,null,null,null)");
                    out.println("Added paper \"" + paper_title + "\" to Paper database with ID = " + new_ID + " and paper_id = " + new_paper_id + "<br>");

                    // Add new information into Authored table
                    stmt.executeUpdate("INSERT INTO Authored VALUES("+new_authored_id+"," + author_id + ","+new_ID+",null,1,null,null,null,null,null)");
                    out.println("Added link between Author " + author_id + " and Paper " + paper_title + " in Authored table.");

                    rs.close();
                } break;
                case "5":
                {
	    	        String title = "Search Results";
	    	        out.println("<title>" + title + "</title>");
	    	        out.println("</head>");
	    	        out.println("<body bgcolor=white>");
	    	        out.println("<h1>" + title + "</h1>");

                    String search_type = request.getParameter("search_type");
                    if (search_type.isEmpty())
                    {
                        out.println("Invalid search type.<br>");
                        out.println("<a href = ../s1.html>Back to input page</a>");
                        break;
                    }
                    String keyword = request.getParameter("keyword");
                    if (keyword.isEmpty())
                    {
                        out.println("Please enter a keyword<br>");
                        out.println("<a href = ../s1.html>Back to input page</a>");
                        break;
                    }

                    out.println("Received Search Type: " + search_type + "<br>");
                    out.println("Received Keyword: " + keyword + "<br><br>");

                    if(search_type.equals("Title"))
                    {
                        boolean no_results = true;
                        ResultSet rs = stmt.executeQuery("SELECT ID, title_str FROM Paper WHERE title_str LIKE \"%" + keyword + "%\"");
                        while(rs.next())
                        {
                            no_results = false;
                            int id_match = rs.getInt(1);
                            String title_match = rs.getString(2);
                            out.println("<a href = ./ops?id=" + id_match + "&sub=submit&OPID=6>" + title_match + "</a><br>");
                        }
                        if (no_results)
                        {
                            out.println("Sorry! No corresponding titles found.<br>");
                        }
                    }

                    if(search_type.equals("Author"))
                    {
                        boolean no_results = true;
                        ResultSet rs = stmt.executeQuery("SELECT ID, author_name FROM Author WHERE author_name LIKE \"%" + keyword + "%\"");
                        while(rs.next())
                        {
                            no_results = false;
                            int id_match = rs.getInt(1);
                            String name_match = rs.getString(2);
                            out.println("<a href = ./ops?id=" + id_match + "&sub=submit&OPID=7>" + name_match + "</a><br>");
                        }
                        if (no_results)
                        {
                            out.println("Sorry! No corresponding Authors found.<br>");
                        }
                    }
                } break;
                case "6":
                {
	    	        String title = "Browse Papers";
	    	        out.println("<title>" + title + "</title>");
	    	        out.println("</head>");
	    	        out.println("<body bgcolor=white>");
	    	        out.println("<h1>" + title + "</h1>");

                    String id = request.getParameter("id");
                    if (id.isEmpty())
                    {
                        out.println("No id provided.<br>");
                        out.println("<a href = ../s1.html>Back to search page</a>");
                        break;
                    }

                    ResultSet rs = stmt.executeQuery("SELECT * FROM Paper WHERE ID = \"" + id + "\"");
                    if(!rs.next())
                    {
                        out.println("No paper exists with ID " + id + "<br>");
                        out.println("<a href = ../s1.html>Back to search page</a>");
                        break;
                    }
                    
                    // Output information
                    String title_str = rs.getString(3);
                    out.println("</p><h2>" + title_str + "</h2><p>");

                    String subject_area = rs.getString(5);
                    int num_pages = rs.getInt(9);
                    String comments = rs.getString(12);
                    
                    // Find all Authors
                    rs = stmt.executeQuery("SELECT AuthorID FROM Authored WHERE paperID = " + id); 
                    while(rs.next())
                    {
                        Connection temp_con = DriverManager.getConnection(url, userName, password);
                        Statement temp_stmt = temp_con.createStatement();
                        ResultSet temp_rs = null;

                        int author_id = rs.getInt(1);
                        temp_rs = temp_stmt.executeQuery("SELECT author_name FROM Author WHERE ID = " + author_id);

                        if(temp_rs.next())
                        {
                            String author_name = temp_rs.getString(1);
                            out.println("<a href=./ops?id="+author_id+"&sub-submit&OPID=7>"+author_name + "</a><br>");
                        }

                        temp_rs.close();
                        temp_stmt.close();
                        temp_con.close();
                    }

                    // More info
                    out.println("ID: " + id + "<br><br>");
                    
                    if (subject_area != null)
                    {
                        out.println("Subject: " + subject_area + "<br>");
                    }
                    if (num_pages != 0)
                    {
                        out.println("Length: " + num_pages + " pages<br>");
                    }
                    if (comments != null)
                    {
                        out.println("Comments: " + comments + "<br>");
                    }

                    // Find citations
                    rs = stmt.executeQuery("SELECT paper2ID FROM Cites WHERE paper1ID = " + id);
                    out.println("Citations:<br>");
                    while(rs.next())
                    {
                        Connection temp_con = DriverManager.getConnection(url, userName, password);
                        Statement temp_stmt = temp_con.createStatement();
                        ResultSet temp_rs = null;

                        int paper_id = rs.getInt(1);
                        temp_rs = temp_stmt.executeQuery("SELECT title_str FROM Paper WHERE ID = " + paper_id);

                        temp_rs.next();
                        String match_title = temp_rs.getString(1);
                        out.println("<a href = ./ops?id="+paper_id+"&sub=submit&OPID=6>"+match_title+"</a><br>");

                        temp_rs.close();
                        temp_stmt.close();
                        temp_con.close();
                    }

                    out.println("<a href = ../s1.html>Back to search page</a><br>");
                    rs.close();
                }break;
                case "7":
                {
	    	        String title = "Browse Papers";
	    	        out.println("<title>" + title + "</title>");
	    	        out.println("</head>");
	    	        out.println("<body bgcolor=white>");
	    	        out.println("<h1>" + title + "</h1>");

                    String id = request.getParameter("id");
                    if (id.isEmpty())
                    {
                        out.println("No id provided.<br>");
                        out.println("<a href = ../s1.html>Back to search page</a>");
                        break;
                    }

                    ResultSet rs = stmt.executeQuery("SELECT * FROM Author WHERE ID = \"" + id + "\"");
                    if(!rs.next())
                    {
                        out.println("No Author exists with ID " + id + "<br>");
                        out.println("<a href = ../s1.html>Back to search page</a>");
                        break;
                    }

                    // Output information
                    String title_str = rs.getString(2);
                    out.println("</p><h2>" + title_str + "</h2><p>");

                    out.println("ID: " + id + "<br>");

                    out.println("Authors this author has worked with: <br>");
                    rs = stmt.executeQuery("SELECT DISTINCT author2ID FROM CoAuthored WHERE author1ID = " + id);
                    
                    while(rs.next())
                    {
                        Connection temp_con = DriverManager.getConnection(url, userName, password);
                        Statement temp_stmt = temp_con.createStatement();
                        ResultSet temp_rs = null;

                        int author_id = rs.getInt(1);
                        temp_rs = temp_stmt.executeQuery("SELECT author_name FROM Author WHERE ID = " + author_id);

                        temp_rs.next();
                        String match_name = temp_rs.getString(1);
                        out.println("<a href = ./ops?id="+author_id+"&sub=submit&OPID=7>"+match_name+"</a><br>");

                        temp_rs.close();
                        temp_stmt.close();
                        temp_con.close();
                    }

                    out.println("<br>Papers written by this Author: <br>");
                    rs = stmt.executeQuery("SELECT paperID FROM Authored WHERE AuthorID = " + id);
                    while(rs.next())
                    {
                        Connection temp_con = DriverManager.getConnection(url, userName, password);
                        Statement temp_stmt = temp_con.createStatement();
                        ResultSet temp_rs = null;

                        int paper_id = rs.getInt(1);
                        temp_rs = temp_stmt.executeQuery("SELECT title_str FROM Paper WHERE ID = " + paper_id);

                        temp_rs.next();
                        String match_title = temp_rs.getString(1);
                        out.println("<a href = ./ops?id="+paper_id+"&sub=submit&OPID=6>"+match_title+"</a><br>");

                        temp_rs.close();
                        temp_stmt.close();
                        temp_con.close();
                    }

                    out.println("<a href = ../s1.html>Back to search page</a><br>");
                    rs.close();
                } break;
                case "8":
                {
	    	        String title = "New Author Added";
	    	        out.println("<title>" + title + "</title>");
	    	        out.println("</head>");
	    	        out.println("<body bgcolor=white>");
	    	        out.println("<h1>" + title + "</h1>");

                    String author_name = request.getParameter("author_name");
                    if(author_name.isEmpty())
                    {
                        out.println("Please enter an author name.<br>");
                        out.println("<a href = ../addauthor.html>Add an author</a>");
                        break;
                    }

                    ResultSet rs = stmt.executeQuery("SELECT MAX(ID)+1 FROM Author");
                    rs.next();
                    int new_id = rs.getInt(1);
                    stmt.executeUpdate("INSERT INTO Author VALUES ("+new_id+",\""+author_name+"\",null,null,null)");
                    out.println("Author " + author_name + " created with ID " + new_id + ".");

                    rs.close();
                } break;
                case "66":
                {  
                    // EXECUTE ORDER NUMBER 66! (Reset the database)
                    stmt.executeUpdate("DELETE FROM Authored");
                    stmt.executeUpdate("DELETE FROM Author");
                    stmt.executeUpdate("DELETE FROM CoAuthored");
                    stmt.executeUpdate("DELETE FROM Cites");
                    stmt.executeUpdate("DELETE FROM Paper");

                    stmt.executeUpdate("LOAD DATA LOCAL INFILE '/u/cs/class/cs143/cs143ta/proj1/data/Author.csv' INTO TABLE Author FIELDS TERMINATED BY ',' OPTIONALLY ENCLOSED BY '\"' LINES TERMINATED BY '\n'");
                    stmt.executeUpdate("LOAD DATA LOCAL INFILE '/u/cs/class/cs143/cs143ta/proj1/data/CoAuthored.csv' INTO TABLE CoAuthored FIELDS TERMINATED BY ',' OPTIONALLY ENCLOSED BY '\"' LINES TERMINATED BY '\n'");
                    stmt.executeUpdate("LOAD DATA LOCAL INFILE '/u/cs/class/cs143/cs143ta/proj1/data/Authored.csv' INTO TABLE Authored FIELDS TERMINATED BY ',' OPTIONALLY ENCLOSED BY '\"' LINES TERMINATED BY '\n'");
                    stmt.executeUpdate("LOAD DATA LOCAL INFILE '/u/cs/class/cs143/cs143ta/proj1/data/Paper.csv' INTO TABLE Paper FIELDS TERMINATED BY ',' OPTIONALLY ENCLOSED BY '\"' LINES TERMINATED BY '\n'");
                    stmt.executeUpdate("LOAD DATA LOCAL INFILE '/u/cs/class/cs143/cs143ta/proj1/data/Cites.csv' INTO TABLE Cites FIELDS TERMINATED BY ',' OPTIONALLY ENCLOSED BY '\"' LINES TERMINATED BY '\n'");

	    	        String title = "Databases Reset";
	    	        out.println("<title>" + title + "</title>");
	    	        out.println("</head>");
	    	        out.println("<body bgcolor=white>");
	    	        out.println("<h1>" + title + "</h1>");
                    
                } break;
                default: out.println("UNKNOWN OPERATION ID");
            }
            out.println("<p><a href=\"../main.html\">Back to main page</a></p>");
		    out.println("</body>");
		    out.println("</html>");

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
