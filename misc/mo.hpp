struct Mo {
    int n;
    vector<pair<int,int>> qs;

    explicit Mo(int n) : n(n) {}

    // [l, r)
    void add_query(int l, int r) {
        qs.emplace_back(l, r);
    }

    template<typename AL, typename AR, typename DL, typename DR, typename REM>
    void build(const AL &add_left, const AR &add_right, const DL &del_left, const DR &del_right, const REM &rem) {
        int q = qs.size();
        if (q == 0) return;

        int bsz = max<int>(1, n / max<double>(1.0, sqrt(q)));
        vector<int> ord(q);
        iota(ord.begin(), ord.end(), 0);

        sort(ord.begin(), ord.end(), [&](int a, int b) {
            int ablock = qs[a].first / bsz, bblock = qs[b].first / bsz;
            if (ablock != bblock) return ablock < bblock;
            return (ablock & 1) ? qs[a].second > qs[b].second : qs[a].second < qs[b].second;
        });

        int l = 0, r = 0;
        for (auto idx : ord) {
            int ql = qs[idx].first, qr = qs[idx].second;
            while (l > ql) add_left(--l);
            while (r < qr) add_right(r++);
            while (l < ql) del_left(l++);
            while (r > qr) del_right(--r);
            rem(idx);
        }
    }

    template<typename ADD, typename DEL, typename REM>
    void build(const ADD &add, const DEL &del, const REM &rem) {
        build(add, add, del, del, rem);
    }
};