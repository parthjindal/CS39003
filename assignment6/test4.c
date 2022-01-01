int printInt(int num);
int printStr(char *c);
int readInt(int *eP);

int factItr(int n) {
    int val = 1;
    int i = 2;
    for (i; i <= n; i++) {
        val = val * i;
    }
    return val;
}

// function to calculate fatorial recursively
int factRec(int n) {
    if (n == 1) {
        return 1;
    } else {
        int res = n;
        res = res * factRec(n - 1);
        return res;
    }
}

// test function
void test(int x) {
    // recursive call
    int recval = factRec(x);
    // iterative call
    int itrval = factItr(x);

    printStr("The value of ");
    printInt(x);
    printStr("! calculated iteratively = ");
    printInt(itrval);
    printStr("\n");
    printStr("The value of ");
    printInt(x);
    printStr("! calculated recursively = ");
    printInt(recval);
    printStr("\n");
    return;
}

int main() {
    int ee;
    printStr("Enter a number: < 10");

    int x = readInt(&ee);
    test(x);

    return 0;
}