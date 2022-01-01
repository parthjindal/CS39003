// testing file for function calls and other function related operators

// function to calculate factorial iteratively
int printInt(int num);
int printStr(char *c);
int readInt(int *eP);

int main() {
    int a, b, c;
    a = 10;
    b = 20;
    c = 30;
    printStr("The value of a is: ");
    printInt(a);
    printStr("\nThe value of b is: ");
    printInt(b);
    printStr("\nThe value of c is: ");
    printInt(c);

    int d, e;
    printStr("\nEnter a number: ");
    d = readInt(&e);
    printStr("\nThe number you entered is: ");
    printInt(d);
    return 0;
}