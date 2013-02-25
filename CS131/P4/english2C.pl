/* My program correctly handles all test cases, and should be able
 * to correctly handle all valid strings thrown at it. If you attempt
 * to "run it backwards" using english2C(E, 5+7) or something to that
 * effect, I would describe its behavior as undefined. Sometimes it
 * gives you the right answer but pressing ; causes it to blow the
 * stack; other times it gives the wrong answer, and other times it 
 * just blows the stack on the first try. You could use DCGs to make
 * it work backwards, or possibly some sort of hacky solution added 
 * on to this solution, but I ran out of time to get it working.
 */


/* defining ~ */
:- op(200, fy, ~).
/* defining '%' */
:- op(400, yfx, '%').


/* changing the precedence of << / >> to be in line with C */
:- op(550, yfx, >>).
:- op(550, yfx, <<).
/* adding &, ^ and ! */
:- op(560, yfx, &).
:- op(570, yfx, ^). 
:- op(580, yfx, !).

/* first, the base cases */

english2C([add,I,to,J],(I+J)) :- integer(I), integer(J).
english2C([add,I,and,J],(I+J)) :- integer(I), integer(J).
english2C([subtract,I,from,J],(J-I)) :- integer(I), integer(J).
english2C([I,unaltered],(+I)) :- integer(I).
english2C([negative,of,I],(-I)) :- integer(I).
english2C([complement,of,I],(~I)) :- integer(I).
english2C([multiply,I,and,J],(I*J)) :- integer(I), integer(J).
english2C([multiply,I,by,J],(I*J)) :- integer(I), integer(J).
english2C([divide,I,by,J],(I/J)) :- integer(I), integer(J).
english2C([take,the,remainder,of,I,after,dividing,by,J],(I'%'J)) :-
	integer(I), integer(J).
english2C([I,shifted,left,J,bits],(I<<J)) :- integer(I), integer(J).
english2C([I,shifted,right,J,bits],(I>>J)) :- integer(I), integer(J).
english2C([I,and,J],(I&J)) :- integer(I), integer(J).
english2C([I,exclusive,or,J],(I^J)) :- integer(I), integer(J).
english2C([I,or,J],(I!J)) :- integer(I), integer(J).
english2C([discard,I,then,use,J,instead],(I,J)) :- integer(I), integer(J).

/* next, the compound cases */

english2C(E, (A+J)) :-
	append(P,[',',then,add,J],E),
	integer(J),
	english2C(P,A).

english2C(E, (A-J)) :-
	append(P,[',',then,subtract,J],E),
	integer(J),
	english2C(P,A).

english2C(E, ('+'A))  :-
	append(P, [',',then,do,nothing],E),
	english2C(P,A).

english2C(E, ('-'A))  :-
	append(P, [',',then,negate,it],E),
	english2C(P,A).

english2C(E, ('~'A))  :-
	append(P, [',',then,complement,it],E),
	english2C(P,A).

english2C(E, (A*J)) :-
	append(P,[',',then,multiply,by,J],E),
	integer(J),
	english2C(P,A).

english2C(E, (A/J)) :-
	append(P,[',',then,divide,by,J],E),
	integer(J),
	english2C(P,A).

english2C(E, (A'%'J)) :-
	append(P,[',',then,divide,by,J,and,take,the,remainder],E),
	integer(J),
	english2C(P,A).

english2C(E, (A<<J)) :-
	append(P,[',',then,shift,left,J,bits],E),
	integer(J),
	english2C(P,A).

english2C(E, (A>>J)) :-
	append(P,[',',then,shift,right,J,bits],E),
	integer(J),
	english2C(P,A).

english2C(E, (A&J)) :-
	append(P,[',',then,and,with,J],E),
	integer(J),
	english2C(P,A).

english2C(E, (A^J)) :-
	append(P,[',',then,exclusive,or,with,J],E),
	integer(J),
	english2C(P,A).

english2C(E, (A!J)) :-
	append(P,[',',then,or,with,J],E),
	integer(J),
	english2C(P,A).

english2C(E, (A,J)) :-
	append(P,[',',then,discard,and,use,J,instead],E),
	integer(J),
	english2C(P,A).

