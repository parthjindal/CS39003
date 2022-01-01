main: main.o libass2.a
	gcc main.o -L. -lass2 -o main

main.o: main.c myl.h
	gcc -c main.c
 
libass2.a: ass2.o
	ar -rcs libass2.a ass2.o

ass2.o: ass2_19CS30033.c myl.h
	gcc -c -o ass2.o ass2_19CS30033.c

clean:
	rm main.o libass2.a ass2.o
