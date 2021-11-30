#include <bits/stdc++.h>
using namespace std;

// 観測点の座標
constexpr double x1 = 5000.0;
constexpr double x2 = 2500.0;
constexpr double y2 = 4000.0;

// 
struct Point { double x, y; };
struct ObservationPoint { Point p; double r; };

int main(){
    clock_t start = clock();
    Point res;
    ObservationPoint p0 = {{0.0, 0.0}, 0.0}, p1 = {{x1, 0.0}, 0.0}, p2 = {{x2, y2}, 0.0};
    vector<pair<double, Point>> v;
    set<pair<double, double>> st;
    
    // 半径を入力する
    // r0 >> r1 >> r2
    cin >> p0.r >> p1.r >> p2.r;

    // 重心の座標
    Point g = {(p1.p.x + p2.p.x) / 3, p2.p.y / 3};

    // 三分探索用の評価式
    auto f = [p0, p1, p2](Point p) -> double{
        return abs(p.x * p.x + p.y * p.y - p0.r * p0.r)
            + abs((p.x - p1.p.x) * (p.x - p1.p.x) + p.y * p.y - p1.r * p1.r)
            + abs(((p.x - p2.p.x) * (p.x - p2.p.x) + (p.y - p2.p.y) * (p.y - p2.p.y)) - p2.r * p2.r);
    };

    // sortに使う比較式
    auto compare = [](pair<double, Point> a, pair<double, Point> b) -> bool{
        if(a.first != b.first) return a.first < b.first;
        if(a.second.x != a.second.y) return a.second.x < a.second.y;
        return a.second.y < a.second.y;
    };

    // xを決め打ちし、yを三分探索して座標の候補を調べる
    for(double nx = g.x - 5000.0; nx <= g.x + 5000.0; nx += 0.1){
        double L = g.y - 5000.0, R = g.y + 5000.0, ty1, ty2;
        while(R - L > 0.1){
            ty1 = L + (R - L) / 3;
            ty2 = R - (R - L) / 3;
            if(f({nx, ty1}) < f({nx, ty2})) R = ty2;
            else L = ty1;
        }
        Point temp = {nx, ty1};
        v.push_back({f(temp), temp});
    }

    // yを決め打ちし、xを三分探索して座標の候補を調べる
    for(double ny = g.y - 5000.0; ny <= g.y + 5000.0; ny += 0.1){
        double L = g.x - 5000.0, R = g.x + 5000.0, tx1, tx2;
        while(R - L > 0.1){
            tx1 = L + (R - L) / 3;
            tx2 = R - (R - L) / 3;
            if(f({tx1, ny}) < f({tx2, ny})) R = tx2;
            else L = tx1;
        }
        Point temp = {tx1, ny};
        v.push_back({f(temp), temp});
    }
    
    sort(v.begin(), v.end(), compare);

    for(int i = 0; i < 50; i++) for(int j = 0; j < 50; j++) st.insert({v[i].second.x, v[j].second.y});

    for(const auto& [x, y] : st) res.x += x, res.y += y;
    res.x /= st.size(); res.y /= st.size();
        
    cout << fixed << setprecision(5) << res.x << " " << res.y << endl
        << double(clock() - start) / CLOCKS_PER_SEC * 1000.0 << "ms" << endl;
}
