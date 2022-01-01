int printStr(char *c);
int readInt(int *ep);
int printInt(int i);

int binpow(int b, int p) {
    int ans = 1;
    while (p > 0) {
        int rem = p - (p / 2) * 2;
        if (rem == 1) {
            ans = ans * b;
        } else {
        }
        b = b * b;
        p = p / 2;
    }
    return ans;
}

int main() {
    int i, j, ep;
    printStr("Enter a base: ");
    i = readInt(&ep);
    printStr("Enter a power: ");
    j = readInt(&ep);
    printStr("Result using binary exponentiation: ");
    printInt(binpow(i, j));
    printStr("\n");
    return 0;
}
