// 直線
// ベクトルb-aで直線を扱う
template<typename T>
struct Line {
    Point<T> a, b;
    Line(Point<T> a_, Point<T> b_) : a(a_), b(b_) {}
    // Ax+By+C=0
    Line(T A, T B, T C) {
        if(equal(A, 0)) {
            a = Point(0, -C / B), b = Point(1, -C / B);
        } else if(equal(B, 0)) {
            a = Point(-C / A, 0), b = Point(-C / A, 1);
        } else {
            a = Point(0, -C / B), b = Point(-C / A, 0);
        }
    }

    template<typename S = T>
    vector<S> to_equation() const {
        vector<S> res(3);
        res[0] = static_cast<S>(b.y) - a.y;
        res[1] = static_cast<S>(a.x) - b.x;
        res[2] = static_cast<S>(b.x) * a.y - static_cast<S>(a.x) * b.y;
        return res;
    }
};