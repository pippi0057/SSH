#include <bits/stdc++.h>
using namespace std;

// 観測点の座標
constexpr double x1 = 5000.0;
constexpr double y1 = 1.0;
constexpr double x2 = 2500.0;
constexpr double y2 = 1.0;
constexpr double z2 = 4000.0;

// 3次元の点を扱うためのライブラリ
namespace Geometry3D{
    constexpr double EPS = 1e-10;
    constexpr double PI = 3.14159265358979;
    inline double dtor(double d){ return d * PI / 180.0; }
    inline double rtod(double r){ return r * 180.0 / PI; }
    inline int sgn(const double a){ return a < -EPS ? -1 : a > EPS ? 1 : 0; }
    struct Point{
        double x, y, z;
        Point() : x(0.0), y(0.0), z(0.0) {}
        Point(double x, double y, double z) : x(x), y(y), z(z) {}
        constexpr Point operator +() const{ return *this; }
        constexpr Point operator -() const{ return{ -x, -y, -z }; }
        constexpr Point operator +(const Point& other) const{ return{ x + other.x, y + other.y, z + other.z }; }
        constexpr Point operator -(const Point& other) const{ return{ x - other.x, y - other.y, z - other.z }; }
        constexpr Point operator *(double s) const{ return{ x * s, y * s, z * s }; }
        constexpr Point operator /(double s) const{ return{ x / s, y / s, z / s }; }
        Point& operator +=(const Point& other){ x += other.x; y += other.y; z += other.z; return *this; }
        Point& operator -=(const Point& other){ x -= other.x; y -= other.y; z -= other.z; return *this; }
        Point& operator *=(double s){ x *= s; y *= s; z *= s; return *this; }
        Point& operator /=(double s){ x /= s; y /= s; z /= s; return *this; }
        inline bool operator ==(Point other){ return !(sgn(x - other.x)) && !(sgn(y - other.y)) &&!(sgn(z - other.z)); }
        inline bool operator !=(Point other){ return !(*this == other); }
        double length() const{ return sqrt(max(0.0, length2())); }
        constexpr double length2() const{ return dot(*this); }
        constexpr double dot(const Point& other) const{ return x * other.x + y * other.y + z * other.z; }
        double dist(const Point& other) const{ return (other - *this).length(); }
    };
}

struct ObservationPoint { Geometry3D::Point p; double r; };

int main(){
    clock_t start = clock();
    ObservationPoint p0 = {{0.0, 0.0, 0.0}, 0.0}, p1 = {{x1, y1, 0.0}, 0.0}, p2 = {{x2, y2, z2}, 0.0};

    // 距離の入力(r0 -> r1 -> r2)
    cin >> p0.r >> p1.r >> p2.r;

    // 重心の座標
    Geometry3D::Point g = (p0.p + p1.p + p2.p) / 3;

    auto f = [p0, p1, p2](Geometry3D::Point p) -> double{
        return p0.p.dist(p) + p1.p.dist(p) + p2.p.dist(p);
    };
    
}
