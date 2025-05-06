#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

using namespace std;

vector<int> solve(const vector<int>& items, int target) {
    int maxSum=0;
    vector<int> ans;
    for (int item : items) {
        maxSum += item;
    }

    function<void(int, int, int, int)> dfs = [&](int subset, int i, int sum, int remaining) {
        if (sum + remaining < target) return; // not promising
        if (sum > target) return; // not promising
        if (sum == target) {
            ans.push_back(subset);
            return;
        }
        dfs(subset | (1 << i), i + 1, sum + items[i], remaining - items[i]);
        dfs(subset, i + 1, sum, remaining - items[i]);
    };

    dfs(0, 0, 0, maxSum);
    sort(ans.begin(), ans.end());
    return ans;
}

int main() {
    int w, item;
    vector<int> items, ans;

    cin >> w;
    while(cin >> item) {
        items.push_back(item);
    }
    // invert the order of items
    reverse(items.begin(), items.end());
    ans = solve(items, w);
    for(int i = 0; i < ans.size(); i++) {
        cout << ans[i] << " ";
    }

    return 0;
}