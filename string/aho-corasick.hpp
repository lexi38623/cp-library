template<int ALPHABET_SIZE = 26, char MARGIN = 'a'>
struct AhoCorasick {
    struct Node {
        std::vector<int> next;
        int fail;
        int match_count;
        std::vector<int> accept;

        Node() : next(ALPHABET_SIZE, -1), fail(-1), match_count(0) {}
    };

    std::vector<Node> nodes;
    std::vector<int> bfs_order;

    AhoCorasick() {
        nodes.emplace_back();
    }

    int add(const std::string& s, int id = -1) {
        int now = 0;
        for (char c : s) {
            int k = c - MARGIN;
            if (nodes[now].next[k] == -1) {
                nodes[now].next[k] = nodes.size();
                nodes.emplace_back();
            }
            now = nodes[now].next[k];
        }
        if (id != -1) nodes[now].accept.push_back(id);
        nodes[now].match_count++;
        return now;
    }

    void build() {
        std::queue<int> que;
        nodes[0].fail = 0;
        
        for (int i = 0; i < ALPHABET_SIZE; ++i) {
            if (nodes[0].next[i] != -1) {
                nodes[nodes[0].next[i]].fail = 0;
                que.push(nodes[0].next[i]);
            } else {
                nodes[0].next[i] = 0;
            }
        }

        while (!que.empty()) {
            int now = que.front();
            que.pop();
            bfs_order.push_back(now);

            int f = nodes[now].fail;
            nodes[now].match_count += nodes[f].match_count;
            // ※特定のパターンIDが必要な場合は、ここで nodes[now].accept に nodes[f].accept を結合する

            for (int i = 0; i < ALPHABET_SIZE; ++i) {
                if (nodes[now].next[i] != -1) {
                    int nxt = nodes[now].next[i];
                    nodes[nxt].fail = nodes[f].next[i];
                    que.push(nxt);
                } else {
                    nodes[now].next[i] = nodes[f].next[i];
                }
            }
        }
    }

    int next_state(int current_state, char c) const {
        return nodes[current_state].next[c - MARGIN];
    }
};