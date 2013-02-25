import java.io.*;
import java.text.*;
import java.util.*;
import java.sql.*;
import javax.servlet.*;
import javax.servlet.http.*;

// ChairOps Servlet:
//
// Performs database updates on a Conference from the Chair admin perspective.
// Capable of:
//  - creating new conferences (OPID 1)
//  - adding a reviewer to a conference (OPID 2)
//  - assigning a paper in a conference to a reviewer in a conference (OPID 3)
//  - triggers computataion of papers' final decision (accept or reject) for a conference (OPID 4)

public class ChairOps extends HttpServlet {

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
            out.println("<p>Selected Conference: " + conference + "</p>");




            switch (OPID)
            {
                case "0": //default, just display the options (no modifications)
                {
                    // Trigger final computation of Conference
                    out.println("<form method=get action=ChairOps>");
                    out.println("<input type='hidden' name='OPID' value='4'>");
                    out.println("<input type='hidden' name='cid' value='"+conference+"'>");
                    out.println("<input type='submit' name='sub' value='END CONFERENCE'>");
                    out.println("</form>");

                    // Add reviewers to the conference
                    out.println("<h1>Add Reviewer to Conference</h1>");
                    out.println("<form method=get action=ChairOps>");
                    out.println("Reviewer Email: <input type=text name='rev_email' size=50>");
                    out.println("<input type='hidden' name='OPID' value='2'>");
                    out.println("<input type='hidden' name='cid' value='"+conference+"'>");
                    out.println("<input type='submit' name='sub' value='Submit'>");
                    out.println("</form>");

                    //Assign papers in the conference to reviewers in the conference
                    out.println("<h1>Assign Paper to Reviewer</h1>");
                    out.println("<form method=get action=ChairOps>");
                    out.println("Reviewer Email: <input type=text name='rev_email' size=50>");
                    out.println("Paper ID: <input type=text name='pid' size=50>");
                    out.println("<input type='hidden' name='OPID' value='3'>");
                    out.println("<input type='hidden' name='cid' value='"+conference+"'>");
                    out.println("<input type='submit' name='sub' value='Submit'>");
                    out.println("</form>");
                    

                
                    out.println("<h1>Edit Conference Information</h1>");
                    
                    // Change Conference Name
                    out.println("<form method=get action=ChairOps>");
                    out.println("<p>Change Conference Name: <input type=text name='name' size=40> </p>");
                    out.println("<input type='hidden' name='OPID' value='5'>");
                    out.println("<input type='hidden' name='cid' value='" + conference + "'>");
                    out.println("<input type='submit' name='sub' value='Submit'>");
                    out.println("</form>");
                    
                    // Change Coference Start Date
                    out.println("<form method=get action=ChairOps>");
                    out.println("<p>Change Conference Start Date:");
                    out.println("<SELECT NAME='start_year'>");
                    out.println("<OPTION SELECTED>2012");
                    out.println("<OPTION>2011");
                    out.println("<OPTION>2010");
                    out.println("<OPTION>2009");
                    out.println("<OPTION>2008");
                    out.println("<OPTION>2007");
                    out.println("<OPTION>2006");
                    out.println("<OPTION>2005");
                    out.println("<OPTION>2004");
                    out.println("<OPTION>2003");
                    out.println("<OPTION>2002");
                    out.println("<OPTION>2001");
                    out.println("<OPTION>2000");
                    out.println("<OPTION>1999");
                    out.println("<OPTION>1998");
                    out.println("<OPTION>1997");
                    out.println("<OPTION>1996");
                    out.println("<OPTION>1995");
                    out.println("<OPTION>1994");
                    out.println("<OPTION>1993");
                    out.println("<OPTION>1992");
                    out.println("<OPTION>1991");
                    out.println("<OPTION>1990");
                    out.println("</SELECT>");

                    out.println("<SELECT NAME='start_month'>");
                    out.println("<OPTION SELECTED>January");
                    out.println("<OPTION>February");
                    out.println("<OPTION>March");
                    out.println("<OPTION>April");
                    out.println("<OPTION>May");
                    out.println("<OPTION>June");
                    out.println("<OPTION>July");
                    out.println("<OPTION>August");
                    out.println("<OPTION>September");
                    out.println("<OPTION>October");
                    out.println("<OPTION>November");
                    out.println("<OPTION>December");
                    out.println("</SELECT>");

                    out.println("<SELECT NAME='start_day'>");
                    out.println("<OPTION SELECTED>1<OPTION>2<OPTION>3<OPTION>4<OPTION>5<OPTION>6<OPTION>7<OPTION>8<OPTION>9<OPTION>10");
                    out.println("<OPTION>10<OPTION>11<OPTION>12<OPTION>13<OPTION>14<OPTION>15<OPTION>16<OPTION>17<OPTION>18<OPTION>19");
                    out.println("<OPTION>20<OPTION>21<OPTION>22<OPTION>23<OPTION>24<OPTION>25<OPTION>26<OPTION>27<OPTION>28<OPTION>29");
                    out.println("<OPTION>30<OPTION>31</SELECT>");

                    out.println("<SELECT NAME='start_hour'>");
                    out.println("<OPTION SELECTED>12AM<OPTION>1AM<OPTION>2AM<OPTION>3AM<OPTION>4AM<OPTION>5AM<OPTION>6AM<OPTION>7AM<OPTION>8AM<OPTION>9AM<OPTION>10AM<OPTION>11AM");
                    out.println("<OPTION>12PM<OPTION>1PM<OPTION>2PM<OPTION>3PM<OPTION>4PM<OPTION>5PM<OPTION>6PM<OPTION>7PM<OPTION>8PM<OPTION>9PM<OPTION>10PM<OPTION>11PM");
                    out.println("</SELECT></p>");

                    out.println("<input type=submit name='sub' value='Submit'>");
                    out.println("<input type='hidden' name='cid' value='"+conference+"'>");
                    out.println("<input type='hidden' name='OPID' value='6'></form>");

                    // Change Conference End Date
                    out.println("<form method=get action=ChairOps>");
                    out.println("<p>Change Conference End Date:");
                    out.println("<SELECT NAME='end_year'>");
                    out.println("<OPTION>2020");
                    out.println("<OPTION>2019");
                    out.println("<OPTION>2018");
                    out.println("<OPTION>2017");
                    out.println("<OPTION>2016");
                    out.println("<OPTION>2015");
                    out.println("<OPTION>2014");
                    out.println("<OPTION>2013");
                    out.println("<OPTION SELECTED>2012");
                    out.println("<OPTION>2011");
                    out.println("<OPTION>2010");
                    out.println("<OPTION>2009");
                    out.println("<OPTION>2008");
                    out.println("<OPTION>2007");
                    out.println("<OPTION>2006");
                    out.println("<OPTION>2005");
                    out.println("<OPTION>2004");
                    out.println("<OPTION>2003");
                    out.println("<OPTION>2002");
                    out.println("<OPTION>2001");
                    out.println("<OPTION>2000");
                    out.println("<OPTION>1999");
                    out.println("<OPTION>1998");
                    out.println("<OPTION>1997");
                    out.println("<OPTION>1996");
                    out.println("<OPTION>1995");
                    out.println("<OPTION>1994");
                    out.println("<OPTION>1993");
                    out.println("<OPTION>1992");
                    out.println("<OPTION>1991");
                    out.println("<OPTION>1990");
                    out.println("</SELECT>");

                    out.println("<SELECT NAME='end_month'>");
                    out.println("<OPTION SELECTED>January");
                    out.println("<OPTION>February");
                    out.println("<OPTION>March");
                    out.println("<OPTION>April");
                    out.println("<OPTION>May");
                    out.println("<OPTION>June");
                    out.println("<OPTION>July");
                    out.println("<OPTION>August");
                    out.println("<OPTION>September");
                    out.println("<OPTION>October");
                    out.println("<OPTION>November");
                    out.println("<OPTION>December");
                    out.println("</SELECT>");

                    out.println("<SELECT NAME='end_day'>");
                    out.println("<OPTION SELECTED>1<OPTION>2<OPTION>3<OPTION>4<OPTION>5<OPTION>6<OPTION>7<OPTION>8<OPTION>9<OPTION>10");
                    out.println("<OPTION>10<OPTION>11<OPTION>12<OPTION>13<OPTION>14<OPTION>15<OPTION>16<OPTION>17<OPTION>18<OPTION>19");
                    out.println("<OPTION>20<OPTION>21<OPTION>22<OPTION>23<OPTION>24<OPTION>25<OPTION>26<OPTION>27<OPTION>28<OPTION>29");
                    out.println("<OPTION>30<OPTION>31</SELECT>");

                    out.println("<SELECT NAME='end_hour'>");
                    out.println("<OPTION SELECTED>12AM<OPTION>1AM<OPTION>2AM<OPTION>3AM<OPTION>4AM<OPTION>5AM<OPTION>6AM<OPTION>7AM<OPTION>8AM<OPTION>9AM<OPTION>10AM<OPTION>11AM");
                    out.println("<OPTION>12PM<OPTION>1PM<OPTION>2PM<OPTION>3PM<OPTION>4PM<OPTION>5PM<OPTION>6PM<OPTION>7PM<OPTION>8PM<OPTION>9PM<OPTION>10PM<OPTION>11PM");
                    out.println("</SELECT></p>");

                    out.println("<input type=submit name='sub' value='Submit'>");
                    out.println("<input type='hidden' name='cid' value='"+conference+"'>");
                    out.println("<input type='hidden' name='OPID' value='7'></form>");
                    
                    // Change Number of Reviewers per paper
                    out.println("<form method=get action=ChairOps>");
                    out.println("<p>Change Number of Reviewers per Paper: <input type=text name='rpp' size=40> </p>");
                    out.println("<input type='hidden' name='OPID' value='8'>");
                    out.println("<input type='hidden' name='cid' value='" + conference + "'>");
                    out.println("<input type='submit' name='sub' value='Submit'>");
                    out.println("</form>");
                    
                    // Change Max number of papers per reviewer
                    out.println("<form method=get action=ChairOps>");
                    out.println("<p>Change Maximum number of papers per reviewer: <input type=text name='ppr' size=40> </p>");
                    out.println("<input type='hidden' name='OPID' value='9'>");
                    out.println("<input type='hidden' name='cid' value='" + conference + "'>");
                    out.println("<input type='submit' name='sub' value='Submit'>");
                    out.println("</form>");


                }break;
                    
                case "1": //create a new conference
                {
                    //got here from CreateConf.html so can pull data
                    String name = request.getParameter("name");

                    //start time
                    String start_year = request.getParameter("start_year");
                    String start_month = request.getParameter("start_month");
                    String start_day = request.getParameter("start_day");
                    String start_hour = request.getParameter("start_hour");

                    //create timestamp for start time
                    int day_limit = 0;
                    int smn = 0;    // Number of the month of the start date (1-12)
                    int st = 0;     // Number of the time of day (0-23)
                    String start_timestamp = start_year + "-";
                    switch(start_month)
                    {
                        case "January": start_timestamp += "01-"; day_limit = 31; smn = 1; break;
                        case "February": start_timestamp += "02-"; smn = 2;
                                         int temp = Integer.parseInt(start_year);
                                         if (temp % 4 == 0)
                                         {
                                            day_limit = 29;
                                         }
                                         else
                                         {
                                            day_limit = 28;
                                         }
                                         break;
                        case "March": start_timestamp += "03-"; day_limit = 31; smn = 3; break;
                        case "April": start_timestamp += "04-"; day_limit = 30; smn = 4; break;
                        case "May": start_timestamp += "05-"; day_limit = 31; smn = 5; break;
                        case "June": start_timestamp += "06-"; day_limit = 30; smn = 6; break;
                        case "July": start_timestamp += "07-"; day_limit = 31; smn = 7; break;
                        case "August": start_timestamp += "08-"; day_limit = 31; smn = 8; break;
                        case "September": start_timestamp += "09-"; day_limit = 30; smn = 9; break;
                        case "October": start_timestamp += "10-"; day_limit = 31; smn = 10; break;
                        case "November": start_timestamp += "11-"; day_limit = 30; smn = 11; break;
                        case "December": start_timestamp += "12-"; day_limit = 31; smn = 12; break;
                        default: day_limit = 0;
                    };
                    
                    int day = Integer.parseInt(start_day);
                    if (day > day_limit)
                    {
                        out.println("Date not allowed. Please enter a valid date.");
                        break;
                    }
                    if (day < 10)
                    {
                        start_timestamp += "0";
                    }
                    start_timestamp += start_day + " ";

                    String time_num = start_hour.substring(0, start_hour.length()-2);
                    String ampm = start_hour.substring(start_hour.length()-2, start_hour.length());

                    int time_num_int = Integer.parseInt(time_num);
                    if (time_num_int == 12 && ampm == "AM")
                    {
                        st = 0;
                        start_timestamp += "00";
                    }
                    else if (ampm == "PM")
                    {
                        time_num_int += 12;
                        time_num = Integer.toString(time_num_int);
                        st = time_num_int;
                        start_timestamp += time_num;
                    }
                    else
                    {
                        if (time_num_int < 10)
                        {
                            start_timestamp += "0";
                        }
                        start_timestamp += time_num_int;
                        st = time_num_int;
                    }

                    start_timestamp += ":00:00";



                    //end time
                    String end_year = request.getParameter("end_year");
                    String end_month = request.getParameter("end_month");
                    String end_day = request.getParameter("end_day");
                    String end_hour = request.getParameter("end_hour");

                    //create timestamp for end time
                    day_limit = 0;
                    int emn = 0;            // Number of the month (1-12)
                    int et = 0;             // Number of the hour (0-23)
                    String end_timestamp = end_year + "-";
                    switch(end_month)
                    {
                        case "January": end_timestamp += "01-"; day_limit = 31; emn = 1; break;
                        case "February": end_timestamp += "02-"; emn = 2; 
                                         int temp = Integer.parseInt(end_year);
                                         if (temp % 4 == 0)
                                         {
                                            day_limit = 29;
                                         }
                                         else
                                         {
                                            day_limit = 28;
                                         }
                                         break;
                        case "March": end_timestamp += "03-"; day_limit = 31; emn = 3; break;
                        case "April": end_timestamp += "04-"; day_limit = 30; emn = 4; break;
                        case "May": end_timestamp += "05-"; day_limit = 31; emn = 5; break;
                        case "June": end_timestamp += "06-"; day_limit = 30; emn = 6; break;
                        case "July": end_timestamp += "07-"; day_limit = 31; emn = 7; break;
                        case "August": end_timestamp += "08-"; day_limit = 31; emn = 8; break;
                        case "September": end_timestamp += "09-"; day_limit = 30; emn = 9; break;
                        case "October": end_timestamp += "10-"; day_limit = 31; emn = 10; break;
                        case "November": end_timestamp += "11-"; day_limit = 30; emn = 11; break;
                        case "December": end_timestamp += "12-"; day_limit = 31; emn = 12; break;
                        default: day_limit = 0;
                    };
                    
                    day = Integer.parseInt(end_day);
                    if (day > day_limit)
                    {
                        out.println("Date not allowed. Please enter a valid date.");
                        break;
                    }
                    if (day < 10)
                    {
                        end_timestamp += "0";
                    }
                    end_timestamp += end_day + " ";

                    time_num = end_hour.substring(0, end_hour.length()-2);
                    ampm = end_hour.substring(end_hour.length()-2, end_hour.length());

                    time_num_int = Integer.parseInt(time_num);
                    if (time_num_int == 12 && ampm == "AM")
                    {
                        et = 0;
                        end_timestamp += "00";
                    }
                    else if (ampm == "PM")
                    {
                        time_num_int += 12;
                        time_num = Integer.toString(time_num_int);
                        et = time_num_int;
                        end_timestamp += time_num;
                    }
                    else
                    {
                        if (time_num_int < 10)
                        {
                            end_timestamp += "0";
                        }
                        end_timestamp += time_num_int;
                        et = time_num_int;
                    }

                    end_timestamp += ":00:00";

                    //Check to see if conference ends before start time
                    int sy = Integer.parseInt(start_year);
                    int ey = Integer.parseInt(end_year);
                    int sd = Integer.parseInt(start_day);
                    int ed = Integer.parseInt(end_day);
                    if (sy > ey ||
                        (sy == ey && (smn > emn)) ||
                        (sy == ey && smn == emn && (sd > ed)) ||
                        (sy == ey && smn == emn && sd == ed && (st >= et)))
                    {
                        out.println("Start time cannot be later than end time.");
                        break;
                    }
                    


                    // Get other attributes
                    String num_reviewers = request.getParameter("num_reviewers");
                    String p_p_r= request.getParameter("papers_per_reviewer");

                    //Check to see if there are any conferences in table
                    rs = stmt.executeQuery("SELECT * FROM Conference");
                    String conf_value = "";
                    if (!rs.next())
                    {
                        conf_value = "1";
                    }
                    else
                    {
                        conf_value = "(SELECT MAX(T.ID)+1 FROM (SELECT * FROM Conference) AS T)";
                    }


                    // Add conference to table
                    String x = "INSERT INTO Conference VALUES("+conf_value+", '" + name + "', '" + start_timestamp + "', '" + end_timestamp + "', " + num_reviewers + ", " + p_p_r + ")";
                    out.println("<p>" + x + "</p>");
                    stmt.executeUpdate(x);
                    out.println("<p>Conference created.</p>");
                } break;

                case "2": //add a reviewer to the conference
                {
                    String rev_email = request.getParameter("rev_email");
                    if(rev_email.isEmpty())
                    {
                        out.println("Please enter the email of an existing user.");
                        break;
                    }

                    rs = stmt.executeQuery("SELECT * FROM Person WHERE email = '"+rev_email+"'");
                    if(!rs.next())
                    {
                        out.println("User " + rev_email + " does not exist.");
                        break;
                    }

                    if(rev_email.equals(email))
                    {
                        out.println("A Chair cannot be a reviewer in this conference.");
                        break;
                    }

                    stmt.executeUpdate("INSERT INTO Reviewer VALUES('"+rev_email+"',"+conference+",null,null,null)");
                    out.println("Added " + rev_email + " as a reviewer of conference " + conference);

                    rs = stmt.executeQuery("SELECT * FROM Reviewer WHERE email = '" + rev_email + "' AND paper_id IS NULL");
                    if(rs.next())
                    {
                        stmt.executeUpdate("DELETE FROM Reviewer WHERE email = '" + rev_email + "' AND paper_id IS NULL");
                    }
                    
                } break;

                case "3": //assign paper to a reviewer
                {
                    // Get parameters, check for null values
                    String rev_email = request.getParameter("rev_email");
                    if(rev_email.isEmpty())
                    {
                        out.println("Please provide a reviewer email.");
                        break;
                    }
                    String pid = request.getParameter("pid");
                    if(pid.isEmpty())
                    {
                        out.println("Please provide a paper id.");
                        break;
                    }

                    // Check to make sure reviewer and paper exist
                    rs = stmt.executeQuery("SELECT * FROM Reviewer WHERE email = '"+rev_email+"' AND conference_id = "+conference);
                    int papers_for_this_reviewer = 0;
                    while(rs.next())
                    {
                        papers_for_this_reviewer++;
                    }
                    if(papers_for_this_reviewer == 0)
                    {
                        out.println("Reviewer not found in conference.");
                        break;
                    }
                    stmt.executeUpdate("DELETE FROM Reviewer WHERE email = '" + rev_email + "' AND paper_id IS NULL");
                    rs = stmt.executeQuery("SELECT * FROM Reviewer WHERE paper_id = "+pid+" AND conference_id = "+conference);
                    int reviewers_for_this_paper = 0;
                    while(rs.next())
                    {
                        reviewers_for_this_paper++;
                    }
                    
                    // Check other constraints
                    rs = stmt.executeQuery("SELECT reviewers_per_paper FROM Conference WHERE id = " + conference);
                    rs.next();
                    String rpp = rs.getString(1);
                    int r = Integer.parseInt(rpp);
                    if(reviewers_for_this_paper >= r)
                    {
                        out.println("This paper already has the maximum number of reviewers.");
                        break;
                    }

                    rs = stmt.executeQuery("SELECT max_papers_per_reviewer FROM Conference WHERE id = " +conference);
                    rs.next();
                    String mppr = rs.getString(1);
                    int m = Integer.parseInt(mppr);
                    if(papers_for_this_reviewer >= m)
                    {
                        out.println("This Reviewer is already reviewing the max number of papers for this conference.");
                        break;
                    }

                    // Add paper to reviewer
                    stmt.executeUpdate("INSERT INTO Reviewer VALUES('"+rev_email+"',"+conference+","+pid+",null,null)");
                    out.println("Added Paper " + pid + " to Reviewer " + rev_email);


                } break;

                case "4": //trigger final computation
                {
                    // Check to make sure all papers have enough reviewers
                    rs=stmt.executeQuery("SELECT * FROM Conference WHERE id=" + conference);
                    rs.next(); //formatting
                    int rev_per_paper = rs.getInt(5);
                    int max_pap_per_rev = rs.getInt(6);


                    //get all papers in conference, store in arraylist
                    rs = stmt.executeQuery("SELECT * FROM Paper WHERE conference=" + conference);
                    ArrayList papersInConf = new ArrayList();
                    while (rs.next())
                    {
                        int pid = rs.getInt(1);
                        papersInConf.add(pid);
                    }
                    boolean finalReady = true;
                    for (int i = 0; i < papersInConf.size(); i++)
                    {
                        rs = stmt.executeQuery("SELECT COUNT(*),COUNT(score) FROM Reviewer WHERE conference_id=" + conference + " AND paper_id=" + papersInConf.get(i));
                        rs.next(); //formatting
                        if (rs.getInt(1) < rev_per_paper) //not enough reviewers
                        {
                            out.println("<p>Not enough reviewers per paper to trigger final review.</p>");
                            finalReady  = false;
                            break;
                        }
                        if (rs.getInt(2) < rs.getInt(1)) //not all reviewers have submitted yet
                        {
                            out.println("<p>Not every reviewer has submitted their score yet.</p>");
                            finalReady = false;
                            break;
                        }

                    } 
                    if (finalReady) //ready to calculate scores 
                    // Calculate average score, decide whether to accept or reject for all papers
                    {
                        int total = 0;
                        int num_reviews = 0;
                        double avg = 0;
                        for (int i = 0; i < papersInConf.size(); i++)
                        {
                            total = 0;
                            num_reviews = 0;
                            avg = 0;

                            rs = stmt.executeQuery("SELECT * FROM Reviewer WHERE conference_id =" + conference + " AND paper_id=" + papersInConf.get(i));
                            while (rs.next())
                            {
                                num_reviews ++;
                                total += rs.getInt(4);
                                
                            }
                            avg = total / num_reviews; //calc the avg
                            if (avg >= 4) //accept
                            {
                                out.println("<p>Paper " + papersInConf.get(i) + " has been accepted with score " + avg + ".</p>");
                                //push the update to the Paper table
                                stmt.executeUpdate("UPDATE Paper SET decision_status='accept' WHERE id=" + papersInConf.get(i));
                            }
                            else //reject
                            {
                                out.println("<p>Paper " + papersInConf.get(i) + " has been rejected with score " + avg + ".</p>");
                                //SQL
                                stmt.executeUpdate("UPDATE Paper SET decision_status='reject' WHERE id=" + papersInConf.get(i));

                            }
                        }
                    }

                } break;

                case "5": //edit conference name
                {
                    // Get new name
                    String name = request.getParameter("name");
                    if(name.isEmpty())
                    {
                        out.println("Invalid conference name.");
                        break;
                    } 

                    rs = stmt.executeQuery("SELECT name FROM Conference WHERE id = " + conference);
                    rs.next();

                    String old_name = rs.getString("name");

                    // Change table
                    stmt.executeUpdate("UPDATE Conference SET name = '" + name + "' WHERE id = " + conference);

                    out.println("Changed Conference " + old_name + " to be named " + name);
                } break;

                case "6": // edit conference start time
                {
                    // Get parameter values
                    String start_year = request.getParameter("start_year");
                    String start_month = request.getParameter("start_month");
                    String start_day = request.getParameter("start_day");
                    String start_hour = request.getParameter("start_hour");
                    
                    // Get end timestamp
                    rs = stmt.executeQuery("SELECT end_time FROM Conference WHERE id = " + conference);
                    rs.next();
                    String end_time = rs.getString("end_time");

                    // Create new start time timestamp
                    String start_timestamp = start_year + "-";
                    
                    int st = 0;
                    int day_limit = 0;
                    int smn = 0; // Number corresponding to month
                    switch (start_month)
                    {
                        case "January": start_timestamp += "01-"; day_limit = 31; smn = 1; break;
                        case "February": start_timestamp += "02-"; smn = 2;
                                         int temp = Integer.parseInt(start_year);
                                         if (temp % 4 == 0)
                                         {
                                            day_limit = 29;
                                         }
                                         else
                                         {
                                            day_limit = 28;
                                         }
                                         break;
                        case "March": start_timestamp += "03-"; day_limit = 31; smn = 3; break;
                        case "April": start_timestamp += "04-"; day_limit = 30; smn = 4; break;
                        case "May": start_timestamp += "05-"; day_limit = 31; smn = 5; break;
                        case "June": start_timestamp += "06-"; day_limit = 30; smn = 6; break;
                        case "July": start_timestamp += "07-"; day_limit = 31; smn = 7; break;
                        case "August": start_timestamp += "08-"; day_limit = 31; smn = 8; break;
                        case "September": start_timestamp += "09-"; day_limit = 30; smn = 9; break;
                        case "October": start_timestamp += "10-"; day_limit = 31; smn = 10; break;
                        case "November": start_timestamp += "11-"; day_limit = 30; smn = 11; break;
                        case "December": start_timestamp += "12-"; day_limit = 31; smn = 12; break;
                        default: day_limit = 0;
                    };

                    int day = Integer.parseInt(start_day);
                    if (day > day_limit)
                    {
                        out.println("Date not allowed. Please enter a valid date.");
                        break;
                    }
                    if (day < 10)
                    {
                        start_timestamp += "0";
                    }
                    start_timestamp += start_day + " ";

                    String time_num = start_hour.substring(0, start_hour.length()-2);
                    String ampm = start_hour.substring(start_hour.length()-2, start_hour.length());

                    int time_num_int = Integer.parseInt(time_num);
                    if (time_num_int == 12 && ampm == "AM")
                    {
                        st = 0;
                        start_timestamp += "00";
                    }
                    else if (ampm == "PM")
                    {
                        time_num_int += 12;
                        time_num = Integer.toString(time_num_int);
                        st = time_num_int;
                        start_timestamp += time_num;
                    }
                    else
                    {
                        if (time_num_int < 10)
                        {
                            start_timestamp += "0";
                        }
                        start_timestamp += time_num_int;
                        st = time_num_int;
                    }

                    start_timestamp += ":00:00";

                    // Check to see if new start time is valid given end time
                    int sy = Integer.parseInt(start_year);
                    String temp = end_time.substring(0,4);
                    int ey = Integer.parseInt(temp);
                    int sd = Integer.parseInt(start_day);
                    temp = end_time.substring(5,7);
                    int emn = Integer.parseInt(temp);
                    temp = end_time.substring(8,10);
                    int ed = Integer.parseInt(temp);
                    temp = end_time.substring(11,13);
                    int et = Integer.parseInt(temp);
                    if (sy > ey ||
                        (sy == ey && (smn > emn)) ||
                        (sy == ey && smn == emn && (sd > ed)) ||
                        (sy == ey && smn == emn && sd == ed && (st >= et)))
                    {
                        out.println("Start time cannot be later than end time.");
                        out.println("Start timestamp: " + start_timestamp);
                        out.println("End timestamp: " + end_time);
                        break;
                    }

                    stmt.executeUpdate("UPDATE Conference SET start_time = '" + start_timestamp + "' WHERE id = " + conference);
                    out.println("Changed Start time of Conference " + conference + " to " + start_timestamp);
                    
                } break;

                case "7": //change conference end date
                {
                    // Get parameter values
                    String end_year = request.getParameter("end_year");
                    String end_month = request.getParameter("end_month");
                    String end_day = request.getParameter("end_day");
                    String end_hour = request.getParameter("end_hour");
                    
                    // Get start timestamp
                    rs = stmt.executeQuery("SELECT start_time FROM Conference WHERE id = " + conference);
                    rs.next();
                    String start_time = rs.getString("start_time");

                    // Create new end time timestamp
                    String end_timestamp = end_year + "-";
                    
                    int et = 0;
                    int day_limit = 0;
                    int emn = 0; // Number corresponding to month
                    switch (end_month)
                    {
                        case "January": end_timestamp += "01-"; day_limit = 31; emn = 1; break;
                        case "February": end_timestamp += "02-"; emn = 2;
                                         int temp = Integer.parseInt(end_year);
                                         if (temp % 4 == 0)
                                         {
                                            day_limit = 29;
                                         }
                                         else
                                         {
                                            day_limit = 28;
                                         }
                                         break;
                        case "March": end_timestamp += "03-"; day_limit = 31; emn = 3; break;
                        case "April": end_timestamp += "04-"; day_limit = 30; emn = 4; break;
                        case "May": end_timestamp += "05-"; day_limit = 31; emn = 5; break;
                        case "June": end_timestamp += "06-"; day_limit = 30; emn = 6; break;
                        case "July": end_timestamp += "07-"; day_limit = 31; emn = 7; break;
                        case "August": end_timestamp += "08-"; day_limit = 31; emn = 8; break;
                        case "September": end_timestamp += "09-"; day_limit = 30; emn = 9; break;
                        case "October": end_timestamp += "10-"; day_limit = 31; emn = 10; break;
                        case "November": end_timestamp += "11-"; day_limit = 30; emn = 11; break;
                        case "December": end_timestamp += "12-"; day_limit = 31; emn = 12; break;
                        default: day_limit = 0;
                    };

                    int day = Integer.parseInt(end_day);
                    if (day > day_limit)
                    {
                        out.println("Date not allowed. Please enter a valid date.");
                        break;
                    }
                    if (day < 10)
                    {
                        end_timestamp += "0";
                    }
                    end_timestamp += end_day + " ";

                    String time_num = end_hour.substring(0, end_hour.length()-2);
                    String ampm = end_hour.substring(end_hour.length()-2, end_hour.length());

                    int time_num_int = Integer.parseInt(time_num);
                    if (time_num_int == 12 && ampm == "AM")
                    {
                        et = 0;
                        end_timestamp += "00";
                    }
                    else if (ampm == "PM")
                    {
                        time_num_int += 12;
                        time_num = Integer.toString(time_num_int);
                        et = time_num_int;
                        end_timestamp += time_num;
                    }
                    else
                    {
                        if (time_num_int < 10)
                        {
                            end_timestamp += "0";
                        }
                        end_timestamp += time_num_int;
                        et = time_num_int;
                    }

                    end_timestamp += ":00:00";

                    // Check to see if new start time is valid given end time
                    int ey = Integer.parseInt(end_year);
                    String temp = start_time.substring(0,4);
                    int sy = Integer.parseInt(temp);
                    int ed = Integer.parseInt(end_day);
                    temp = start_time.substring(5,7);
                    int smn = Integer.parseInt(temp);
                    temp = start_time.substring(8,10);
                    int sd = Integer.parseInt(temp);
                    temp = start_time.substring(11,13);
                    int st = Integer.parseInt(temp);
                    if (sy > ey ||
                        (sy == ey && (smn > emn)) ||
                        (sy == ey && smn == emn && (sd > ed)) ||
                        (sy == ey && smn == emn && sd == ed && (st >= et)))
                    {
                        out.println("Start time cannot be later than end time.");
                        out.println("Start timestamp: " + start_time);
                        out.println("End timestamp: " + end_timestamp);
                        break;
                    }

                    stmt.executeUpdate("UPDATE Conference SET end_time = '" + end_timestamp + "' WHERE id = " + conference);
                    out.println("Changed END time of Conference " + conference + " to " + end_timestamp);
                } break;

                case "8": // Change number of reiewers per paper
                {
                    String rpp = request.getParameter("rpp");
                    if(rpp.isEmpty())
                    {
                        out.println(rpp + "is not a valid number.");
                        break;
                    }

                    int r = Integer.parseInt(rpp);
                    if (r < 1 || r > 1000)
                    {
                        out.println(rpp + "is out of range (1 to 1000).");
                        break;
                    }

                    rs = stmt.executeQuery("SELECT COUNT(T.email) FROM (SELECT * FROM Reviewer WHERE conference_id = "+conference+") as T GROUP BY  paper_id");
                    while(rs.next())
                    {
                        String count = rs.getString(1);
                        int int_count = Integer.parseInt(count);
                    }
                    out.println("Changed number of reviewers per paper of Conference " + conference + " to " + rpp);
                } break;
                
                case "9": // Change maximum number of papers per reviewer
                {
                    String ppr = request.getParameter("ppr");
                    if(ppr.isEmpty())
                    {
                        out.println("Please provide a valid number of papers.");
                        break;
                    }

                    int p = Integer.parseInt(ppr);
                    if (p < 1 || p > 1000)
                    {
                        out.println("Number of papers out of bound.");
                        break;
                    }

                    rs = stmt.executeQuery("SELECT COUNT(T.paper_id) FROM (SELECT * FROM Reviewer WHERE conference_id = "+conference+") as T GROUP BY email");
                    while(rs.next())
                    {
                        String count = rs.getString(1);
                        int int_count = Integer.parseInt(count);
                        if(int_count > p)
                        {
                            out.println("Some reviewers already have more than " + ppr + " papers to review");
                            break;
                        }
                    }

                    stmt.executeUpdate("UPDATE Conference SET max_papers_per_reviewer = " + ppr + " WHERE id = " + conference);
                    out.println("Changed max number of papers per reviewer of Conference " + conference + " to " + ppr);
                } break;

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
