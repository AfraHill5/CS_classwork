--- Create tables in database

CREATE TABLE Person (
   email varchar(50),
   last_name varchar(50),
   middle_name varchar(50),
   first_name varchar(50),
   affiliation varchar(50),
   isChair int,
   primary key(email));

CREATE TABLE Conference (
    id int,
    name varchar(50),
    start_time timestamp,
    end_time timestamp,
    reviewers_per_paper int,
    max_paper_per_reviewer int,
    primary key(id));

CREATE TABLE Paper (
    id int,
    title varchar(50),
    abstract varchar(50),
    content varchar(50),
    conference int,
    decision_status varchar(50),
    primary key(id));

CREATE TABLE Reviewer (
    email varchar(50),
    conference_id int,
    paper_id int,
    score int,
    comments varchar(100));

CREATE TABLE Author (
    email varchar(50),
    paper_id int);

--- Create administrator
INSERT INTO Person VALUES ('admin','admin',null,null,null,1);
