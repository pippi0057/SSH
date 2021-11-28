#include <bits/stdc++.h>
using namespace std;

// 観測点の座標
constexpr double x1 = 600.0;
constexpr double x2 = 300.0;
constexpr double y2 = 600.0;

struct Point { double x, y; }; // 座標を扱うための構造体
struct ObservationPoint { Point p; double r; }; // 観測点を扱うための構造体

template <class T> inline bool chmin(T& a, T b){ if(a > b){ a = b; return 1; } return 0; }

int main(){
    clock_t START = clock();
    cout << fixed << setprecision(5);
    double min = 999999999.999; Point res;
    ObservationPoint p0 = {{0, 0}, 0}, p1 = {{x1, 0}, 0}, p2 = {{x2, y2}, 0};
    
    // 距離の入力
    // r0 >> r1 >> r2
    cin >> p0.r >> p1.r >> p2.r;

    // 重心の座標
    Point g = {(p1.p.x + p2.p.x) / 3, p2.p.y / 3};
    
    // 評価式
    auto f = [p0, p1, p2](Point p) -> double{
        return abs(p.x * p.x + p.y * p.y - p0.r * p0.r)
            + abs((p.x - p1.p.x) * (p.x - p1.p.x) + p.y * p.y - p1.r * p1.r)
            + abs(((p.x - p2.p.x) * (p.x - p2.p.x) + (p.y - p2.p.y) * (p.y - p2.p.y)) - p2.r * p2.r);
    };

    // 全探索
    for(double X = g.x - 5000.0; X <= g.x + 5000.0; X += 10.0){
        for(double Y = g.y - 5000.0; Y <= g.y + 5000.0; Y += 10.0){
            if(chmin(min, f({X, Y}))) res = {X, Y};
        }
    }

    cout << res.x << " " << res.y << endl;
    cout << double(clock() - START) / CLOCKS_PER_SEC * 1000.0 << "ms" << endl;
}