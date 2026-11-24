template <int BITS = 30, typename T = unsigned>
struct BinaryTrie {
    struct Node {
        int ch[2];
        int cnt;
        Node() : ch{0, 0}, cnt(0) {}
    };
    std::vector<Node> nodes;
    T lazy;

    explicit BinaryTrie(int reserve_nodes = 0) : lazy(0) {
        nodes.reserve(reserve_nodes + 1);
        nodes.emplace_back();
    }

    int size() const { return nodes[0].cnt; }
    bool empty() const { return size() == 0; }

    void clear() {
        nodes.clear();
        nodes.emplace_back();
        lazy = 0;
    }

    void apply_xor(T x) { lazy ^= x; }

    void insert(T x, int c = 1) {
        assert(c >= 0);
        x ^= lazy;
        int cur = 0;
        nodes[cur].cnt += c;
        for (int b = BITS - 1; b >= 0; --b) {
            int d = (x >> b) & 1;
            if (!nodes[cur].ch[d]) {
                nodes[cur].ch[d] = (int)nodes.size();
                nodes.emplace_back();
            }
            cur = nodes[cur].ch[d];
            nodes[cur].cnt += c;
        }
    }

    int count(T x) const {
        x ^= lazy;
        int cur = 0;
        for (int b = BITS - 1; b >= 0; --b) {
            cur = nodes[cur].ch[(x >> b) & 1];
            if (!cur) return 0;
        }
        return nodes[cur].cnt;
    }

    bool erase(T x, int c = 1) {
        if (count(x) < c) return false;
        x ^= lazy;
        int cur = 0;
        nodes[cur].cnt -= c;
        for (int b = BITS - 1; b >= 0; --b) {
            cur = nodes[cur].ch[(x >> b) & 1];
            nodes[cur].cnt -= c;
        }
        return true;
    }

    T kth(int k) const {
        assert(0 <= k && k < size());
        int cur = 0;
        T res = 0;
        for (int b = BITS - 1; b >= 0; --b) {
            int l = (int)((lazy >> b) & 1);
            int c0 = nodes[cur].ch[l];
            int n0 = c0 ? nodes[c0].cnt : 0;
            if (k < n0) {
                cur = c0;
            } else {
                k -= n0;
                cur = nodes[cur].ch[l ^ 1];
                res |= (T)1 << b;
            }
        }
        return res;
    }

    T min() const { return kth(0); }
    T max() const { return kth(size() - 1); }

    int count_less(T x) const {
        int cur = 0, res = 0;
        for (int b = BITS - 1; b >= 0; --b) {
            int l = (int)((lazy >> b) & 1);
            int xb = (int)((x >> b) & 1);
            if (xb) {
                int c0 = nodes[cur].ch[l];
                if (c0) res += nodes[c0].cnt;
                cur = nodes[cur].ch[l ^ 1];
            } else {
                cur = nodes[cur].ch[l];
            }
            if (!cur) return res;
        }
        return res;
    }

    int count_leq(T x) const {
        return count_less(x) + count(x);
    }

    T argmin_xor(T x) const { return walk(x, true); }
    T argmax_xor(T x) const { return walk(x, false); }

    T min_xor(T x) const { return argmin_xor(x) ^ x; }
    T max_xor(T x) const { return argmax_xor(x) ^ x; }

    int count_xor_less(T x, T y) const {
        T t = x ^ lazy;
        int cur = 0, res = 0;
        for (int b = BITS - 1; b >= 0; --b) {
            int tb = (int)((t >> b) & 1);
            int yb = (int)((y >> b) & 1);
            if (yb) {
                int same = nodes[cur].ch[tb];
                if (same) res += nodes[same].cnt;
                cur = nodes[cur].ch[tb ^ 1];
            } else {
                cur = nodes[cur].ch[tb];
            }
            if (!cur) return res;
        }
        return res;
    }

private:
    T walk(T x, bool minimize) const {
        assert(!empty());
        T t = x ^ lazy;
        int cur = 0;
        T s = 0;
        for (int b = BITS - 1; b >= 0; --b) {
            int tb = (int)((t >> b) & 1);
            int want = minimize ? tb : (tb ^ 1);
            int nx = nodes[cur].ch[want];
            if (!nx || nodes[nx].cnt == 0) {
                want ^= 1;
                nx = nodes[cur].ch[want];
            }
            cur = nx;
            s |= (T)want << b;
        }
        return s ^ lazy;
    }
};