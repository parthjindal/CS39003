
test: a.out assgn4_19CS30033_19CS30036_test.c
	./a.out < assgn4_19CS30033_19CS30036_test.c > test_result.txt

a.out:	y.tab.o assgn4_19CS30033_19CS30036.o lex.yy.o
	gcc y.tab.o assgn4_19CS30033_19CS30036.o lex.yy.o -lfl

lex.yy.c:	assgn4_19CS30033_19CS30036.l y.tab.h
		flex assgn4_19CS30033_19CS30036.l 

y.tab.c:	assgn4_19CS30033_19CS30036.y
		bison -dty assgn4_19CS30033_19CS30036.y --report=solved

assgn4_19CS30033_19CS30036.o:	assgn4_19CS30033_19CS30036.c 
				gcc -c assgn4_19CS30033_19CS30036.c

assgn4_19CS30033_19CS30036.c:
				touch assgn4_19CS30033_19CS30036.c


y.tab.h:	assgn4_19CS30033_19CS30036.y
		bison -dty assgn4_19CS30033_19CS30036.y --report=solved

lexy.yy.o:	lex.yy.c 
		gcc -c lex.yy.c 

y.tab.o:	y.tab.c 
		gcc -c y.tab.c 

clean:	
	rm y.output a.out y.tab.c y.tab.h y.tab.o lex.yy.c lex.yy.o assgn4_19CS30033_19CS30036.o 


