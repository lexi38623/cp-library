struct binomial {
    vector<mint> fact, ifact;
    binomial(int n): fact(n+1), ifact(n+1) {
        fact[0] = 1;
        for (int i = 1; i <= n; i++) fact[i] = fact[i-1] * i;
        ifact[n] = fact[n].inv();
        for (int i = n; i >= 1; i--) ifact[i-1] = ifact[i] * i;
    }
    mint operator()(int n, int k) {
        if(k < 0 || n < k) return 0;
        return fact[n] * ifact[n-k] * ifact[k];
    }
};