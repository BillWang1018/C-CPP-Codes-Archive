#include <iostream>
#include <algorithm>
using namespace std;
int main() {
    struct block {
        int x,y,z;
    } blocks[200]{}, height[200]{};
    int n{}, caseCt{};

    while(cin >> n) {
        if(!n) break;
        caseCt++;

        for(int _{}; _<n*6;) {
            int x,y,z;
            cin >> x >> y >> z;
            blocks[_++] = {x,y,z};
            blocks[_++] = {x,z,y};
            blocks[_++] = {y,x,z};
            blocks[_++] = {y,z,x};
            blocks[_++] = {z,x,y};
            blocks[_++] = {z,y,x};
        }

        sort(blocks, blocks+n*6, [](block a, block b) {
            if(a.x == b.x) return a.y > b.y;
            return a.x > b.x;
        });

        for(int i=0; i<n*6; i++) {
            height[i] = blocks[i];
            cout << "| " << blocks[i].x << " " << blocks[i].y << " " << blocks[i].z << " |\n";
        }
            
        for(int i=0; i<n*6; i++) {
            for(int j=0; j<n*6; j++) {
                if(blocks[j].x < height[i].x && blocks[j].y < height[i].y) {
                    if(height[i].z < height[j].z + blocks[j].z) {
                        height[i].x = blocks[j].x;
                        height[i].y = blocks[j].y;
                        height[i].z = height[j].z + blocks[j].z;
                    }
                }
            }
        }

        int ans{};
        for(int i=0; i<n*6; i++) {
            cout << ":: " << height[i].z << " ::\n";
            ans = max(ans, height[i].z);
        }
        cout << "Case " << caseCt << ": maxium height = " << ans << "\n";
        
    }
    
    return 0;
}