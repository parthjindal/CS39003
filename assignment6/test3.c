// gcd function
int printInt(int num);
int printStr(char *c);
int readInt(int *eP);

int gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        int q = a / b;
        int rem = a - q * b;
        b = rem;
        a = t;
    }
    return a;
}

int test(int a) {
    int ee;
    printStr("Enter 1st number: ");

    int x = readInt(&ee);

    printStr("Enter 2nd number: ");

    int y = readInt(&ee);

    int z = gcd(x, y);
    printStr("gcd of ");
    printInt(x);
    printStr(" and ");
    printInt(y);
    printStr(" is ");
    printInt(z);
    printStr("\n");
    // arithmetic operators check
    int a = x - z;
    int b = y + z;
    int c = x * z;
    int d = x / z;

    printStr("a - gcd(a, b) = ");
    printInt(a);
    printStr("\n");
    printStr("b + gcd(a, b) = ");
    printInt(b);
    printStr("\n");
    printStr("a * gcd(a, b) = ");
    printInt(c);
    printStr("\n");
    printStr("a / gcd(a, b) = ");
    printInt(d);
    printStr("\n");

    return 0;
}
int main() {
    printStr("Testing GCD function \n");
    int a;
    a = test(0);
    // calling test function

    return 0;
}