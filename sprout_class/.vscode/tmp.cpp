#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        int N = nums.size();
        vector<vector<int>> ans;
        for(int i=0; i<N; i++) {
            int sum2 = -nums[i];
            vector<int> tmpans;    
            map<int,int> m;
            bool flag = false;
            tmpans.push_back(i);
            for(int j=i+1; j<N; j++) {
                int k = sum2-nums[j];
                if(m.count(k)) {
                    tmpans.push_back(m[k]);
                    tmpans.push_back(j);
                    flag = true;
                } else {
                    m[nums[j]] = j;
                }
                if(flag) {
                    ans.push_back(tmpans);
                }
            }
        }
        
        return ans;
    }
};  