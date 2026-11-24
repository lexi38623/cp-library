/* -------------------- 計算幾何ライブラリ -------------------- */

const double EPS = 1e-8, PI = acos(-1.0);
inline bool equal(const double &a, const double &b) { return fabs(a - b) < EPS; }

// 点（原点を基準としたベクトル）
template<typename T>
struct Point {
    T x, y;
    Point() = default;
    Point (T x_, T y_) : x(x_), y(y_) {}

    Point operator+(const Point &other) const { return {x + other.x, y + other.y}; }
    Point operator-(const Point &other) const { return {x - other.x, y - other.y}; }
    Point operator*(double c) const { return {x * c, y * c}; }
    friend Point operator*(T c, const Point &p) { return {p.x * c, p.y * c}; }

    double operator*(const Point &other) const { return x * other.x + y * other.y; }
    double operator^(const Point &other) const { return x * other.y - y * other.x; }
    double norm() { return sqrt(x * x + y * y); }
    T norm2() { return x * x + y * y; }
    double arg() { return atan2(y, x); }
    Point rotate(const Point &p, const double theta) { return { p.x * cos(theta) - p.y * sin(theta), p.x * sin(theta) + p.y * cos(theta) }; }
};

template<typename T> istream &operator>>(istream &is, Point<T> &p) { is >> p.x >> p.y; return is; }

// a-b-cの角度のうち小さい方を返す
template<typename T>
double get_angle(const Point<T> &a, Point<T> &b, Point<T> &c) {
    const Point<T> u(b-a), v(c-b);
    double alpha = atan2(u.y, u.x), beta = atan2(v.y, v.x);
    double theta = abs(beta-alpha);
    return min(theta, 2*PI-theta);
}

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

/* -------------------- 計算幾何ライブラリ ここまで -------------------- */
