template<typename T>
struct CC {
    vector<T> xs;
    CC() {}
    void add(T x) {xs.push_back(x);}
    void init() {
        sort(xs.begin(), xs.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());
    }
    int operator()(T x) {
        return lower_bound(xs.begin(), xs.end(), x) - xs.begin();
    }
    T operator[](int i) {
        return xs[i];
    }
    int size() {
        return xs.size();
    }
};
