int max(int x, int y) {
    if (x > y)
        return x;
    else
        return y;
}

int min(int x, int y) {
    if (x < y)
        return x;
    else
        return y;
}

int cal(int a, int b) {
    int c, d;
    c = max(a, b);
    d = min(c, a + b);
    return c + d;
}

int main() {
    int a, b, d;
    a = 10, b = 5;
    d = cal(a, b);
    return 0;
}