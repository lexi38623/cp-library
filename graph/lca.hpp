template <class T>
struct LCA {
    struct Edge {
        int to;
        T cost;
    };

    int n;
    int log2_n;
    vector<vector<Edge>> g;
    vector<vector<int>> parent;
    vector<int> depth;
    vector<T> dist_from_root;

    LCA(int n) : n(n), g(n), depth(n), dist_from_root(n, 0) {
        log2_n = 1;
        while ((1 << log2_n) < n) log2_n++;
        parent.assign(log2_n, vector<int>(n, -1));
    }

    void add_edge(int u, int v, T cost=1) {
        g[u].push_back({v, cost});
        g[v].push_back({u, cost});
    }

    void dfs(int v, int p, int d, T current_dist) {
        parent[0][v] = p;
        depth[v] = d;
        dist_from_root[v] = current_dist;
        for (const auto& edge : g[v]) {
            if (edge.to != p) {
                dfs(edge.to, v, d + 1, current_dist + edge.cost);
            }
        }
    }

    void build(int root = 0) {
        dfs(root, -1, 0, 0);
        for (int k = 0; k + 1 < log2_n; k++) {
            for (int v = 0; v < n; v++) {
                if (parent[k][v] < 0) {
                    parent[k + 1][v] = -1;
                } else {
                    parent[k + 1][v] = parent[k][parent[k][v]];
                }
            }
        }
    }

    int query(int u, int v) {
        if (depth[u] < depth[v]) swap(u, v);
        
        for (int k = 0; k < log2_n; k++) {
            if ((depth[u] - depth[v]) >> k & 1) {
                u = parent[k][u];
            }
        }
        
        if (u == v) return u;

        for (int k = log2_n - 1; k >= 0; k--) {
            if (parent[k][u] != parent[k][v]) {
                u = parent[k][u];
                v = parent[k][v];
            }
        }
        
        return parent[0][u];
    }

    int length(int u, int v) { return depth[u] + depth[v] - 2 * depth[query(u, v)]; }
    T dist(int u, int v) { return dist_from_root[u] + dist_from_root[v] - 2 * dist_from_root[query(u, v)]; }
};