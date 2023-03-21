#include <iostream>
#include <cmath>
#define MOD 1000000007
using namespace std;

bool checkBeauti(int, int *);
int nextBeauti(int, int *);
void printNum(int, int *);

int T, N, M;
int main() {
    cin >> T;
    while(T--) {
        int ans{};
        int num[101];
        cin >> N >> M;
        for(int i=1; i<N; i++) {
            num[0] = i;
            ans += nextBeauti(1, num) % MOD;
        }

        cout << ans << "\n";
    }
    return 0;
}

bool checkBeauti(int d, int *num) {
    int countDig{};
    for(int i=0; i<d; i++) {
        countDig |= (1 << num[i]);
        if (i != d-1)
            if(abs(num[i] - num[i+1]) != 1) 
                return 0;
    }
    if(countDig == (1<<N)-1) return 1;
    return 0;
}

int nextBeauti(int d, int *num) {
    // cout << "nextBeauti" << "\t|\t";
    // printNum(d, num);
    int rt = checkBeauti(d, num);

    if(d < M) {
        int last = num[d-1];
        d++;

        if(last > 0) {
            num[d-1] = last-1;
            rt += nextBeauti(d, num) % MOD;
        }

        if(last < N-1) {
            num[d-1] = last+1;
            rt += nextBeauti(d, num) % MOD;
        }

    }
    
    return rt;
}

void printNum(int d, int *num) {
    for(int i=0; i<d; i++)
        cout << num[i];
    cout << "\n";
}
// 3210
// 1011
// 0100
// 1111