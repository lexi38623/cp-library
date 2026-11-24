struct HLD {
    vector<int> par, dep, sz;
    vector<int> vs, vid, head;

    HLD(int n, vector<vector<int>>& g, int r = 0) : par(n), dep(n), sz(n), vs(n), vid(n), head(n) {
        auto dfs1 = [&](auto& dfs1, int v, int p) -> void {
            par[v] = p;
            dep[v] = (p == -1 ? 0 : dep[p] + 1);
            sz[v] = 1;
            if (!g[v].empty() && g[v][0] == p) swap(g[v][0], g[v].back());
            for (int& u : g[v]) {
                if (u == p) continue;
                dfs1(dfs1, u, v);
                sz[v] += sz[u];
                if (sz[u] > sz[g[v][0]]) swap(g[v][0], u);
            }
        };
        dfs1(dfs1, r, -1);

        int k = 0;
        auto dfs2 = [&](auto& dfs2, int v, int p) -> void {
            vid[v] = k;
            vs[k++] = v;
            for (int& u : g[v]) {
                if (u == p) continue;
                bool heavy = (u == g[v][0]);
                head[u] = (heavy ? head[v] : u);
                dfs2(dfs2, u, v);
            }
        };
        head[r] = r;
        dfs2(dfs2, r, -1);
    }

    int Level_Ancestor(int v, int d) {
        assert(0 <= d && d <= dep[v]);
        while (dep[head[v]] > d) {
            v = par[head[v]];
        }
        return vs[vid[v] - (dep[v] - d)];
    }

    int LCA(int u, int v) {
        while (head[u] != head[v]) {
            if (vid[u] > vid[v]) swap(u, v);
            v = par[head[v]];
        }
        return (vid[u] < vid[v] ? u : v);
    }

    int dist(int u, int v) {
        int w = LCA(u, v);
        return (dep[u] - dep[w]) + (dep[v] - dep[w]);
    }

    int Jump(int a, int b, int i) {
        int c = LCA(a, b);
        int d = dist(a, b);
        if (d < i) return -1;
        if (i < dep[a] - dep[c]) return Level_Ancestor(a, dep[a] - i);
        return Level_Ancestor(b, dep[b] - (d - i));
    }
};