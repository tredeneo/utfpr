:- dynamic you_have/1, location/2, connect/2, contadora/1.

contadora(0).

location(egg, duck_pen).
location(ducks, duck_pen).
location(fox, woods).
location(you, house).

link(yard, house).
link(yard, duck_pen).
link(yard, woods).

connect(X, X).
connect(X, Y):- link(X, Y).
connect(X, Y):- link(Y, X).

goto(X) :-
    location(you, L),
    connect(L, X),
    retract(location(you, L)),
    assert(location(you, X)),
    write("You are in the "), write(X), nl.
goto(_) :-
    write("You can't get there from here"), nl.

fox :-
    random_member(X,[house,yard,woods,duck_pen]),
    location(fox, L),
    connect(L, X),
    retract(location(fox,L)),
    assert(location(fox,X)),
    write("The fox has moved to the "), write(X), nl,
    X = duck_pen,
    contadora(N),
    C is N+1,
    retract(contadora(N)),
    assert(contadora(C)),
    write("The fox has taken a duck"), nl.
fox.

open(gate) :-
    \+location(you, yard),
    write("You can't do that here."), nl.
open(gate) :-
    connect(yard, duck_pen),
    write("The gate is already opened!"), nl.
open(gate) :-
    assert(connect(yard, duck_pen)),
    assert(connect(duck_pen, yard)),
    write("The gate is now opened."), nl.

cl(gate) :-
    \+location(you, yard),
    write("You can't do that here."), nl.
cl(gate) :-
    \+connect(yard, duck_pen),
    write("The gate is already closed!"), nl.
cl(gate) :-
    retract(connect(yard, duck_pen)),
    retract(connect(duck_pen, yard)),
    write("The gate is now closed."), nl.

take(X) :-
    \+(X = egg),
    write("You can't take that."), nl.
take(X) :-
    location(you, L),
    \+location(X, L),
    write("You can't do that here!"), nl.
take(X) :-
    you_have(X),
    write("You already have the egg!"), nl.
take(X) :-
    assert( you_have(X) ),
    write("You took the egg."), nl.

go :- done.
go :-
    write(">> "),
    read(X),
    call(X),
    fox,
    go.

reset :-
    retract(you_have(egg)),
    location(fox,X),
    retract(location(fox,X)),
    assert(location(fox,woods)),
    contadora(N),
    retract(contadora(N)),
    assert(contadora(0)).
reset :-
    retract(connect(yard, duck_pen)),
    retract(connect(duck_pen, yard)).

done :-
    location(you, house),
    you_have(egg),
    write("Thanks for getting the egg"), nl,
    contadora(N),
    write("The fox took: "), write(N), nl,
    reset.


