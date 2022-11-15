#include <iostream>
#include <vector>
using namespace std;

struct Node
{
    Node *next = nullptr;
    Node *prev = nullptr;
    int id = -1;
};

void erase(Node* player) {
    if(player->next == nullptr) { // is tail
        player->prev->next = nullptr;
    } else {
        player->prev->next = player->next;
        player->next->prev = player->prev;
    }

    free(player);
}

void surpass(Node* player) {
    if(player->prev->id == -1) return; //is no.1 

    Node *pp, *p, *n; // pp -> p -> player -> n
    p = player->prev; 
    pp = player->prev->prev;
    if(player->next != nullptr) {
        n = player->next;
        // assign data (end)
        p->next = n;
        n->prev = p;
    } else {
        p->next = nullptr;
    }
    pp->next = player;
    player->prev = pp;
    p->prev = player;
    player->next = p;

}

void printList(Node* head) {
    while(head->next != nullptr) {
        head = head->next;
        cout << head->id << ((head->next == nullptr) ? "" : " ");
    }
    cout << "\n";
}

int main() {    
    int N, M, t, x;
    cin >> N >> M;
    Node* head = new Node;
    Node* tail = head;
    vector<Node*> pos(N+1, nullptr);
    for(int i=1; i<=N; i++) {
        Node* newNode = new Node;
        pos[i] = newNode;
        tail->next = newNode;
        newNode->prev = tail;
        newNode->id = i;
        tail = newNode;
    }   
    for(int i=1; i<=M; i++) {
        cin >> t >> x;
        if(t==0) {
            erase(pos[x]);
        }
        if(t==1) {
            surpass(pos[x]);
        }
    }
    printList(head);

    return 0;
}