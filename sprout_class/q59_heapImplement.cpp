#include <iostream>
#include <vector>
#define MAX 1e6+5
using namespace std;
int main() {
    int  T, n, b=-1; // b = index of last element
    vector<int> heap(MAX);
    cin >> T;
    while (T--) {
        cin >> n;
        if(n == 1) { // insert
            cin >> n;
            b++, heap[b] = n;
            int i=b;
            while(i) {
                if(heap[i] < heap[(i-1)/2]) {
                    int tmp = heap[i];
                    heap[i] = heap[(i-1)/2], heap[(i-1)/2] = tmp;
                    i = (i-1)/2;
                } else break;
            }
            
        } else { // 2: pop
            if(b<0) {
                cout << "empty!\n";
                continue;
            }
            cout << heap[0] << '\n';
            heap[0] = heap[b];
            b--;
            int i=0;
            while(i*2+1 <= b) {
                if(i*2+2 <= b)
                    i = (heap[i*2+1] < heap[i*2+2]) ? i*2+1 : i*2+2; // t->left, f->right
                else 
                    i = i*2+1;
                if(heap[i] < heap[(i-1)/2]) {
                    int tmp = heap[i];
                    heap[i] = heap[(i-1)/2], heap[(i-1)/2] = tmp;
                } else break;
            }
        }
    }
    return 0;
}