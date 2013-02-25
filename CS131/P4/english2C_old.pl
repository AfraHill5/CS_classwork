
/* defining ~ */
:- op(200, fy, ~).
/* defining '%' */
:- op(400, yfx, '%').


/* changing the precedence of << / >> to be in line with C */
:- op(550, yfx, >>).
:- op(550, yfx, <<).
/* adding &, ^ and ! */
/*rs(K-L)    -->  [K],rs('-'L).*/
:- op(560, yfx, &).
:- op(570, yfx, ^). 
:- op(580, yfx, !).







english2C(E,C) :- exp(C, E, []). 

exp(E)        --> ls(E).
exp(E)        --> extension(E).



ls(X+Y) --> [add,X,and,Y], {integer(X), integer(Y)}.
ls(X+Y) --> [add,X,to,Y], {integer(X), integer(Y)}.
ls(J-I) --> [subtract,I,from,J], {integer(J), integer(I)}.
ls(+I)  --> [I,unaltered], {integer(I)}.
ls(-I)  --> [negative,of,I], {integer(I)}.
ls(~I)  --> [complement,of,I], {integer(I)}.
ls(I*J) --> [multiply,I,by,J], {integer(I), integer(J)}.
ls(I*J) --> [multiply,I,and,J], {integer(I), integer(J)}.
ls(I/J) --> [divide,I,by,J], {integer(I), integer(J)}.
ls(I'%'J) --> [take,the,remainder,of,I,after,dividing,by,J], {integer(I), integer(J)}.
ls(I<<J) --> [I,shifted,left,J,bits], {integer(I), integer(J)}.
ls(I>>J) --> [I,shifted,right,J,bits], {integer(I), integer(J)}.
ls(I&J) --> [I,and,J], {integer(I), integer(J)}.
ls(I^J) --> [I,exclusive,or,J], {integer(I), integer(J)}.
ls(I!J) --> [I,or,J], {integer(I), integer(J)}.
ls(I,J) --> [I,then,discard,and,use,J,instead], {integer(I), integer(J)}.


extension(J+K) --> exp(J),[',',then,add,K], {integer(K)}.
extension(J-K) --> exp(J), [',',then,subtract,K], {integer(K)}.
extension(J*K) --> exp(J), [',',then,multiply,by,K], {integer(K)}.
extension(J/K) --> exp(J), [',',then,divide,by,K], {integer(K)}.
extension(J'%'K) --> exp(J), [',',then,divide,by,K,and,take,the,remainder], {integer(K)}.
extension(J<<K) --> exp(J), [',',then,shift,left,K,bits],{integer(K)}.
extension(J>>K) --> exp(J), [',',then,shift,right,K,bits],{integer(K)}.
extension(J&K)  --> exp(J), [',',then,and,with,K],{integer(K)}.
extension(J^K)  --> exp(J), [',',then,exclusive,or,with,K],{integer(K)}.
extension(J!K)  --> exp(J), [',',then,or,with,K],{integer(K)}.
extension(J,K)--> exp(J), [',',then,discard,and,use,K,instead],{integer(K)}.



/*doesnt work right now */
extension('+'E)  --> exp(E), [',',then,do,nothing].
extension(-E)  --> exp(E), [',',then,negate,it].




/*
extension(+E)   --> ls(E), rs('+').
extension(-E)  --> ls(E), rs('-').


rs('+')       --> [',',then,do,nothing].
rs('-')       --> [',',then,negate,it].
rs('+'K)        --> [',',then,add], rs(K).
rs(K+L)     --> [K],rs('+'L).
rs('-'K)        --> [',',then,subtract], rs(K).
rs(K-L)  --> [K],rs('-'L).





rs(K)         --> [K].

*/
