#include <iostream>
#include <cstdio>
#include <set>
#include <utility>
#include <iomanip>
using namespace std;
int main() {
    double px[5]{}, py[5]{};
    while((scanf("%lf %lf %lf %lf %lf %lf %lf %lf", &px[0], &py[0], &px[1], &py[1], &px[2], &py[2], &px[3], &py[3])) != EOF) {
        px[4] = py[4] = 0;
        set<pair<double,double>> pts;
        int dup{};
        for(int i{}; i<4; i++) {
            double a=px[i],b=py[i];
            if(pts.count({a,b}) == 0)
                pts.emplace(a,b);
            else
                dup = i;
        }
        //printf("%d <== dup\n", dup);
        for(int i{}; i<4; i++) 
            px[4]+=px[i], py[4]+=py[i];
        px[4]-=(px[dup]*3), py[4]-=(py[dup]*3);
        /*
        switch (dup) {
            case 1:

            case 2:
                px[4] = px[0]+px[3]-px[2];
                py[4] = py[0]+py[3]-py[2];
                break;
            case 3:
                px[4] = px[0]+px[2]-px[3];
                py[4] = py[0]+py[2]-py[3];
                break;
        }
        */
        printf("%.3lf %.3lf\n", px[4], py[4]);
    }
    return 0;
}