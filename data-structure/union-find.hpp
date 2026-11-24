struct UnionFind {
    vector<int> par;
    DSU(int n) : par(n,-1) {}

    int root(int x) {
        if(par[x] < 0) return x;
        return par[x] = root(par[x]);
    }

    bool merge(int x, int y) {
        int rx = root(x), ry = root(y);
        if(rx == ry) return false;
        if(-par[rx] < -par[ry]) swap(rx,ry);
        par[rx] += par[ry];
        par[ry] = rx;
        return true;
    }

    bool same(int x, int y) {
        return root(x) == root(y);
    }

    int size(int x) {
        return -par[root(x)];
    }
};
