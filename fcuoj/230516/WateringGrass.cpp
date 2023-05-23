#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;

struct Sprinkler {
    float l, r;
};

Sprinkler findBoarder(float pos, float rad, float w) {
    w/=2;
    float offset = sqrt((rad*rad)-(w*w));
    // cout << offset;
    return {pos-offset, pos+offset};
}

int main() {
    int N, L, W;
    while(cin >> N >> L >> W) {
        vector<Sprinkler> sp;
        for(int n{}; n<N; n++) {
            int pos, rad;
            cin >> pos >> rad;
            if(rad*2 <= W) continue;
            sp.push_back(findBoarder(pos, rad, W));
            // cout << ": " << sp.back().l << " " << sp.back().r << "\n";

        }
        sort(sp.begin(), sp.end(), [](Sprinkler a, Sprinkler b) {
            return (a.l != b.l) ? a.l < b.l : a.r > b.r;
        });
        
        int i{}, ans{};
        bool isFound = false;
        Sprinkler hold = {0,0}, next = {0,0};
        while(i<sp.size()) {
            while(sp[i].l <= hold.r) {
                isFound = true;
                if(sp[i].r >= next.r) {
                    next = sp[i];
                }
                if(next.r >= L) // has reach the end of the ground
                    break;
                i++;
            }
            // cout << ":: " << next.l << " " << next.r << "\n";

            ans++;
            hold = next;
            
            if(!isFound) // can't find next one to cover all ground
                break;

            if(next.r >= L) // has reach the end of the ground
                break;

            isFound = false;
        }

        // cout << "out | ";
        if(isFound) cout << ans << "\n";
        else cout << "-1\n";
        
    }

    return 0;
}