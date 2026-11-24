struct Wavelet_Matrix {
    int H, N;
    vector<vector<int>> dat;
    Wavelet_Matrix(int H, vector<int> A) : H(H), N(A.size()), dat(H) {
        for (int h = H - 1; h >= 0; h--) {
            vector<int> dir(N);
            vector<int> left, right;
            for (int i = 0; i < N; i++) {
                dir[i] = A[i] >> h & 1;
                (dir[i] == 0 ? left : right).emplace_back(A[i]);
            }
            int a = left.size(), b = right.size();
            for (int i = 0; i < a; i++) A[i] = left[i];
            for (int i = 0; i < b; i++) A[a + i] = right[i];

            dat[h].resize(N + 1);
            for (int i = 0; i < N; i++) dat[h][i + 1] = dat[h][i] + dir[i];
        }
    };

    tuple<int, int, int, int> get_subtree_range(int h, int l, int r) {
        int a0 = l - dat[h][l], a1 = dat[h][l];
        int b0 = r - dat[h][r], b1 = dat[h][r];
        int c0 = N - dat[h][N];
        return {a0, b0, c0 + a1, c0 + b1};
    }
};