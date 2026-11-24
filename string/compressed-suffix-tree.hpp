struct CompressedSuffixTree {
    vector<vector<int>> to;
    vector<int> par, dep;
    int n;
    CompressedSuffixTree(vector<int> sa, vector<int> lcp) : n(sa.size()), to(1), par(1, -1), dep(1, 0) {
        int v = 0;
        for (int i = 0; i < n; i++) {
            int d = n-sa[i];
            if (dep[v] < d) {
                int u = to.size();
                to.resize(u+1);
                par.push_back(v);
                dep.push_back(d);
                to[v].push_back(u);
                v = u;
            }

            if (i == n-1) break;
            d = lcp[i];
            while (d < dep[v]) v = par[v];
            if (d != dep[v]) {
                int u = to.size();
                to.resize(u+1);
                par.push_back(v);
                dep.push_back(d);
                to[u].push_back(to[v].back());
                par[to[v].back()] = u;
                to[v].back() = u;
                v = u;
            }
        }
    }
};