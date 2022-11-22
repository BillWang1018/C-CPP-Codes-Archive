#include <iostream>
#include <set>
#include <utility>
#include <cmath>
#include <iomanip>
#define ADDPAIR(a,b) {a.first+b.first, a.second+b.second}
using namespace std;
int main() {
    set<pair<double,double>> pts;
    pair<double,double> d1, d2, ans, pt[4];
    do {
        for(int _{}; _<4; _++) {
            double x,y;
            cin >> x >> y;
            pts.emplace(x,y);
            pt[_] = {x,y};
        }
        
        d1 = {pt[1].first-pt[0].first, pt[1].second-pt[0].second};
        d2 = {pt[3].first-pt[2].first, pt[3].second-pt[2].second};
        if(!pts.count(ADDPAIR(pt[0], d1))) {
            d1 = {-d1.first, -d1.second};
        }
        if(!pts.count(ADDPAIR(pt[3], d2))) {
            d2 = {-d2.first, -d2.second};
        }
        ans = ADDPAIR(d1,d2), ans = ADDPAIR(ans, pt[0]);
        cout << fixed << setprecision(3) << ans.first << " " << ans.second << "\n";

    } while(cin.eof());
    return 0;
}