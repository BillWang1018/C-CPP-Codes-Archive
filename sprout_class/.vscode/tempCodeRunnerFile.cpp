vector<int> twoSum(vector<int>& nums, int target) {
        int N = nums.size();
        vector<int> ans;
        map<int,int> m;
        for(int i=0; i<N; i++) {
            int k = target-nums[i];
            if(m.count(k)) {
                ans.push_back(k);
                ans.push_back(i);
                return ans;
            } else {
                m[nums[i]] = i;
            }
        }
        return;
    }