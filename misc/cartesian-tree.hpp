template <typename T>
struct CartesianTree {
    int n, root;
    vector<int> parent, left, right;

    CartesianTree(const vector<T>& a) {
        n = a.size();
        parent.assign(n, -1);
        left.assign(n, -1);
        right.assign(n, -1);
        root = -1;

        vector<int> st;
        for (int i = 0; i < n; i++) {
            int last_popped = -1;
            
            // (Max-Cartesian Tree にしたい場合はここを a[st.back()] < a[i] に変更)
            while (!st.empty() && a[st.back()] > a[i]) {
                last_popped = st.back();
                st.pop_back();
            }

            if (last_popped != -1) {
                left[i] = last_popped;
                parent[last_popped] = i;
            }

            if (!st.empty()) {
                right[st.back()] = i;
                parent[i] = st.back();
            }

            st.push_back(i);
        }

        if (!st.empty()) {
            root = st.front();
        }
    }
};