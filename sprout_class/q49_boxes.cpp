#include <iostream>
#include <vector>
using namespace std;

struct Node
{
    Node *parent = nullptr;
    int id;
};

int main() {
    int T, n, m, q, x, y;
    cin >> T;
    while(T--) {
        cin >> n >> m;
        vector<Node*> box(n+1);
        for(int i=1; i<=n; i++) {
            box[i] = new Node;
            box[i]->id = i;
        }
        vector<int> count(n+1, 1);
        while(m--) {
            cin >> x >> y;
            box[y]->parent = box[x];
            Node *tmp = box[y];
            while(tmp->parent) {
                count[tmp->parent->id] += count[y];
                //printf("count[%d] += count[%d]\n", tmp->parent->id, tmp->id);
                tmp = tmp->parent;
            }
        }
        cin >> q;
        while(q--) {
            cin >> x;
            cout << count[x] << "\n";
        }
    }



    return 0;
}