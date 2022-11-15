#include <iostream>
using namespace std;

struct Node
{
    Node *r = nullptr;
    Node *l = nullptr;
    int val = -1;
};


void postOrder(Node *n) {
    if(n->l->val != -1)
        postOrder(n->l);
    if(n->r->val != -1)
        postOrder(n->r);
    cout << n->val << "\n";
}

int main() {
    int N, k;
    Node *head = new Node;
    cin >> N;
    // input tree
    for(int i=0; i<N; i++) {
        Node *tmp = head;
        cin >> k;
        while(tmp->val != -1)
            tmp = (k < tmp->val) ? tmp->l : tmp->r;
        tmp->val = k;
        tmp->l = new Node;
        tmp->r = new Node;

    }
    postOrder(head);
    
    return 0;
}