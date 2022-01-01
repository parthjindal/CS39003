
#include "myl.h"

int main(int argc, char* argv[]) {
    int ok = 0;
    printStr("----------------------------------------------------------\n");
    printStr("CS39003 Laboratory-2  Author: Parth Jindal (19CS30033) \n");
    printStr("----------------------------------------------------------\n\n");

    printStr("Testing printStr function\n");
    int len = printStr("Hello World!\n");
    printStr("No. of characters printed: ");
    printInt(len);

    printStr("\n\nTesting printInt function for '-12345': ");
    len = printInt(-12345);
    printStr("\nNo. of characters printed: ");
    printInt(len);

    printStr("\n\nTesting printFlt function for '1456.375': ");
    len = printFlt(1456.375);
    printStr("\nNo. of characters printed: ");
    printInt(len);

    printStr("\n\nTesting readInt function: Enter an integer: ");
    int n;
    ok = readInt(&n);
    if (ok) {
        printStr("You entered: ");
        printInt(n);
    } else {
        printStr("Error reading integer");
    }

    printStr("\n\nTesting readFlt function: Enter a float: ");
    float f2;
    ok = readFlt(&f2);
    if (ok) {
        printStr("You entered: ");
        printFlt(f2);
    } else {
        printStr("Error reading float");
    }
    printStr("\n");
}