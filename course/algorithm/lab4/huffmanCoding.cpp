#include <iostream>
#include <string>
#include <queue>
#include <functional>

using namespace std;

typedef unsigned char uchar;

struct Node {
    uchar ch;
    int freq;
    int index;
    Node* left;
    Node* right;

    Node(uchar c, int f, int i) : ch(c), freq(f), index(i), left(nullptr), right(nullptr) {}
};
    

string huffmanCoding(const string& input) {
    // Create a frequency map for the characters in the input string
    int freq[256] = {0};
    int firstAppear[256] = {0};

    fill(begin(firstAppear), end(firstAppear), -1);
    for (int i=0; i<input.length(); i++) {
        uchar c = input[i];
        freq[c]++;
        if (firstAppear[c] == -1) {
            firstAppear[c] = i;
        }
    }

    // Create a priority queue to store the nodes of the Huffman tree
    auto cmp = [&](Node* a, Node* b) {
        return (a->freq == b->freq) ? (a->index > b->index) : (a->freq > b->freq); // Sort by frequency, then by character
    };
    priority_queue<Node*, vector<Node*>, decltype(cmp)> pq(cmp);

    // Create a leaf node for each character and add it to the priority queue
    for (int i=0; i<256; i++) {
        if (freq[i] > 0) {
            pq.push(new Node(i, freq[i], firstAppear[i]));
        }
    }
    

    // Build the Huffman tree
    while (pq.size() > 1) {
        Node* l, *r;
        l = pq.top();
        pq.pop();
        r = pq.top();
        pq.pop();

        Node* parent = new Node('\0', l->freq + r->freq, min(l->index, r->index));
        parent->left = l;
        parent->right = r;
        pq.push(parent);
    }

    // The root of the tree is now the only node in the priority queue
    Node* root = pq.top();
    pq.pop();

    // Generate the Huffman codes
    string code[256];
    function<void(Node*, string)> generateCodes = [&](Node* node, string str) {
        if (!node) return;
        if (node->ch != '\0') {
            code[node->ch] = str;
            //cout << "Code: " << node->ch << "=" << str << " freq:" << node->freq << " index:" << node->index << endl;
        }
        generateCodes(node->left, str + "0");
        generateCodes(node->right, str + "1");
    };
    generateCodes(root, "");

    // Encode the input string using the generated Huffman codes
    string ans = "";
    for (uchar c : input) {
        ans += code[c];
    }

    return ans;
}

string binaryStringToHex(string str) {
    int len = str.length();
    // padding
    for (int i=0; i < (4 - (len % 4)) % 4; i++) {
        str.push_back('0');
    }
    
    string hexStr;
    for (int i=0; i<str.length(); i+=4) {
        string byte = str.substr(i, 4);
        int value = 0;
        for (uchar c : byte) {
            value = (value << 1) | (c - '0');
        }
        hexStr += (value < 10) ? (uchar)(value + '0') : (uchar)(value - 10 + 'A');
    }
    return hexStr;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string input;
    getline(cin, input);
    cout << binaryStringToHex(huffmanCoding(input)) << endl;

    return 0;
}