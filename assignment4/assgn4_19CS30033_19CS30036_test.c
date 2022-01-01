volatile int test_var;
extern int func_1();
double func_2(double a, double b) {
    return a + b;
}

static char func_3(char a, char b) {
    return a + b - 2 + 4;
}

void for_loop() {
    int i;
    for (i = 0; i < 10; i++) {
        test_var = i;
    }
}

/**
 * @brief This is the main function,
 * This is a multiline comment
 */
void main() {
    float f = 945.2e-2;
    // My name (single line comment)
    char name[20] = "Parth Jindal\t\t";
    int i = 0;
    for (i = 0; i < 20; i++) {
        test_var = i;
    }
    char arr[4] = "";

    while (i < 20) {
        test_var = i;
        i++;
    }
    do {
        i++;
    } while (i < 100);
    _Bool b = 1;
    _Imaginary i1 = 1;
    _Complex c = 1;
    int xas = func_1();
    func_2(1, 2);
    char x = func_3('a', 'b');

    for_loop();
    main();
}