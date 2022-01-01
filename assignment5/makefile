TEST: a.out
	./a.out	< test1.c > test1_quads.out
	./a.out	< test2.c > test2_quads.out
	./a.out	< test3.c > test3_quads.out
	./a.out	< test4.c > test4_quads.out
	./a.out	< test5.c > test5_quads.out


a.out: lex.yy.o assgn5_19CS30033_19CS30036.tab.o assgn5_19CS30033_19CS30036_translator.o
	g++ lex.yy.o assgn5_19CS30033_19CS30036.tab.o assgn5_19CS30033_19CS30036_translator.o -lfl

assgn5_19CS30033_19CS30036_translator.o: assgn5_19CS30033_19CS30036_translator.cxx assgn5_19CS30033_19CS30036_translator.h
	g++ -c assgn5_19CS30033_19CS30036_translator.h
	g++ -c assgn5_19CS30033_19CS30036_translator.cxx

lex.yy.o: lex.yy.c
	g++ -c lex.yy.c

assgn5_19CS30033_19CS30036.tab.o: assgn5_19CS30033_19CS30036.tab.c
	g++ -c assgn5_19CS30033_19CS30036.tab.c

lex.yy.c: assgn5_19CS30033_19CS30036.l assgn5_19CS30033_19CS30036.tab.h assgn5_19CS30033_19CS30036_translator.h
	flex assgn5_19CS30033_19CS30036.l

assgn5_19CS30033_19CS30036.tab.c: assgn5_19CS30033_19CS30036.y
	bison -dtv assgn5_19CS30033_19CS30036.y -W

assgn5_19CS30033_19CS30036.tab.h: assgn5_19CS30033_19CS30036.y
	bison -dtv assgn5_19CS30033_19CS30036.y -W

clean:
	rm lex.yy.c lex.yy.o a.out  assgn5_19CS30033_19CS30036.tab.c \
	assgn5_19CS30033_19CS30036.tab.h assgn5_19CS30033_19CS30036.tab.o \
	assgn5_19CS30033_19CS30036_translator.o assgn5_19CS30033_19CS30036_translator.h.gch \
	test1_quads.out test2_quads.out test3_quads.out test4_quads.out test5_quads.out