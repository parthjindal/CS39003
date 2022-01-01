output.txt: a.out ass3_19CS30033_test.c
	./a.out < ass3_19CS30033_test.c > output.txt

a.out: lex.yy.c ass3_19CS30033.c header.h
	cc lex.yy.c ass3_19CS30033.c -lfl

lex.yy.c: ass3_19CS30033.l header.h
	flex ass3_19CS30033.l

# hack for flex overwriting the file
ass3_19CS30033.c:
	touch ass3_19CS30033.c 

clean:
	rm a.out lex.yy.c output.txt