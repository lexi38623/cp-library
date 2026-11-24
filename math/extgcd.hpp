// ax + by = gcd(x,y)の整数解を一つ求め，gcd(x,y)を返す．
long long extgcd(long long a, long long b, long long& x, long long& y) {
    if(b == 0){ x = 1, y = 0; return a; }
    long long q = a/b, g = extgcd(b, a-b*q, y, x);
    y -= q*x;
    return g;
}