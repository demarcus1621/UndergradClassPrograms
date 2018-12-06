/*
Author: DeMarcus Campbell
COMP3220
Homework 6
*/

/*
Exercise 1
This portion of the program expects
queries of the form
?- sister(x,y).
Returns true if x is sister of y
*/

parent(dad, son).
parent(dad, daughter).
parent(mom, son).
parent(mom, daughter).

male(dad).
male(son).

female(mom).
female(daughter).

sister(X, Y):-
    female(X),
    parent(Z, X),
    parent(Z,Y).
	
/*
Exercise 2
Expects the estimated max, and an
input list. Queries should
be of the form.
?- max(estimateMax,[x1,x2,x3....]).
returns true if estimateMax is the 
max of the given list
*/

max(0, []).

max(X, [H|T]):-
    member(X, [H|T]),
    max(X1, T),
    (   
    	H > X1 ->  
    		X is H
    	;
    		X is X1
    ).
	
/*
Exercise 3
Expects two lists as parameters. Queries
should be of the form
?- intersection([x1,x2,x3,....],[a1,a2,a3,...]).
returns true if the two lists do not have
an intersection.
*/

intersection([], []).
intersection([], [_H|_T]).
intersection([_H|_T], []).

intersection([H|T], [HE|TE]):-
    (   
    	member(H, [HE|TE]) ->  
    		fail
    	;   
    	intersection(T,[HE|TE])
    ).
	
/*
Exercise 4
Expects two lists to be input as parametes.
Appends second list to the first, thus creating
the union of the two lists. This works using the
the assumption of lists instead of sets, thus 
replicated elements are allowed. Queries should
be of the form:
?- union([x1,x2,x3,.....],[a1,a2,a3,...]).
prints result list to console and returns true.
*/

union([], [H|T]):-
    write([H|T]).
union([H|T], []):-
    write([H|T]).
union([H|T],[HE|TE]):-
    append([H|T],[HE|TE],X),
	write(X)
	
/*
Exercise 5
Expects two lists as parameters, and checks
if the second list is equivalent to the 
quicksorted permutation of the first list.
Queries should be of the form:
?- qs([x1,x2,x3,...],[a1,a2,a3....]).
returns true if [a] is the quicksorted permutation
of [x].
*/

qs([H|T],Y) :-
  	partition(T,H,L,R),
  	qs(L,Ls),
  	qs(R,Rs),
  	append(Ls,[H|Rs],Y).
qs([],[]).

partition([H|T],Y,[H|Ls],Rs) :-
  	H =< Y, 
  	partition(T,Y,Ls,Rs).
partition([H|T],Y,Ls,[H|Rs]) :-
    H > Y,
  	partition(T,Y,Ls,Rs).
partition([],_Y,[],[]).

append([],Ys,Ys).
append([H|T],Ys,[H|Z]) :- 
	append(T,Ys,Z).
