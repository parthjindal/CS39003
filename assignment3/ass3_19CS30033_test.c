#include <stdio.h>
/* This is a multiline comment */
typedef struct test {
    int a;
    float b;
    char c;
    struct test *d;
};

int main() {
    //Main function starts

    //CONSTANTS TESTING
    int a = 13213;
    int b = 0;
    float c = 3.14;
    float d = -1e-2;
    float e = -32.24e4;
    char f = '\n';
    char g = 'a';

    //STRING LITERAL
    char *h = "Hello World\n";

    //KEYWORD TESTING
    auto, break, case, char, const, continue, default, do, double, else, enum, extern, float, for, goto, if, int, long, register, return, short, signed, sizeof, static, struct, switch, typedef, union, unsigned, void, volatile, while;
    restrict, return, short, signed, sizeof, static, struct, switch, typedef, union
 	unsigned, void, volatile, while, _Bool, _Complex, _Imaginary;

    int i = 1;
    while(i < 10){
        i++;
    }
    int a[10];
    a[0] = 1;
    a[1] = 2;
    a[2] = 3;
    a[3] = 4;
    a[4] = 5;
    a[5] = 6;
    a[6] = 7;
    a[7] = 8;
    a[8] = 9;
    a[9] = 10;

    int sum = 0;
    for(int i = 0; i < 10; i++){
        sum += a[i];
    }
    printf("%d\n", sum);

    test t;
    t.a = 1;
    t.b = 2.0;
    t.c = 'a';
    t.d = NULL;
    enum months {jan, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec};
    enum months m = jan;
    printf("%d\n", m);

    _Imaginary asfa;
    _Bool b = 1;
    _Complex c = 1.0;

    return 0;   
}
