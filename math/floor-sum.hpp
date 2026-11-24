long long floor_sum(long long n, long long m, long long a, long long b) {
    long long a1 = a / m, a2 = a % m;
    if (a2 < 0) { a1--; a2 += m; }
    long long s = n * (n - 1) / 2 * a1;
    long long b1 = b / m, b2 = b % m;
    if (b2 < 0) { b1--; b2 += m; }
    if (a2 == 0) return s + b1 * n;
    long long k = (a2 * (n - 1) + b2) / m;
    return s + n * (k + b1) - floor_sum(k, a2, m, m + a2 - b2 - 1);
}