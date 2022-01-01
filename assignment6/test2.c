//This testfile checks the functioning of the library functions printInt, readInt and printStr

int printInt(int num);
int printStr(char *c);
int readInt(int *eP);

// user-defined function (with pointer parameters)
// return an int value
int test(int *a) {
    return a;
}

int main() {
    printStr("Testing for if-else cases when comparing two numbers");
    int a, b, e;
    printStr("\nEnter a: ");
    a = readInt(&e);
    printStr("Enter b: ");
    b = readInt(&e);

    if (a > b) {
        printStr("\na is greater than b");
    } else if (a < b) {
        printStr("\na is less than b");
    } else {
        printStr("\na is equal to b");
    }
    
    return 0;
}