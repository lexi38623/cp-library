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

    bool operator==(const Point &other) const { return x == other.x && y == other.y; }
    bool operator!=(const Point &other) const { return x != other.x || y != other.y; }

    double arg() { return atan2(y, x); }
    Point rotate(const Point &p, const double theta) { return { p.x * cos(theta) - p.y * sin(theta), p.x * sin(theta) + p.y * cos(theta) }; }
};

template<typename T> T dot(const Point<T>& a, const Point<T>& b) { return a.x*b.x + a.y*b.y; }
template<typename T> T cross(const Point<T>& a, const Point<T>& b) { return a.x*b.y - a.y*b.x; }
template<typename T> istream &operator>>(istream &is, Point<T> &p) { is >> p.x >> p.y; return is; }

// a-b-cの角度のうち小さい方を返す
template<typename T>
double get_angle(const Point<T> &a, Point<T> &b, Point<T> &c) {
    const Point<T> u(b-a), v(c-b);
    double alpha = atan2(u.y, u.x), beta = atan2(v.y, v.x);
    double theta = abs(beta-alpha);
    return min(theta, 2*PI-theta);
}

/* -------------------- 計算幾何ライブラリ ここまで -------------------- */