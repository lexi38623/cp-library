template <typename S, auto op, auto e>
struct SegmentTree {
    int n;
    vector<S> d;

    SegmentTree(const vector<S>& a) {
        int sz = a.size();
        n = 1;
        while (n < sz) n <<= 1;
        d.assign(2 * n, e());
        for (int i = 0; i < sz; i++) d[n + i] = a[i];
        for (int i = n - 1; i >= 1; i--) update(i);
    }

    SegmentTree(int sz) {
        n = 1;
        while (n < sz) n <<= 1;
        d.assign(2 * n, e());
    }

    void update(int i) {
        d[i] = op(d[i << 1], d[i << 1 | 1]);
    }

    void set(int p, const S& x) {
        p += n;
        d[p] = x;
        while (p > 1) {
            p >>= 1;
            update(p);
        }
    }

    S operator[](int i) const {
        return d[n + i];
    }

    S prod(int l, int r) {
        S sml = e(), smr = e();
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) sml = op(sml, d[l++]);
            if (r & 1) smr = op(d[--r], smr);
        }
        return op(sml, smr);
    }
};