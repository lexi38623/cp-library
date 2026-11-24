// https://atcoder.jp/contests/abc212/tasks/abc212_h
template <typename T>
void FastWalshHadamardTransform(vector<T>& a) {
    int n = (int)a.size();
    for (int i = 1; i < n; i <<= 1) {
        for (int j = 0; j < n; j++) if(i&j) {
            int k = i^j;
            T x = a[k], y = a[j];
            a[k] = x + y;
            a[j] = x - y;
        }
    }
}
