#include <iostream>
#include <string>
#include <queue>
#include <functional>
#include <bitset>

using namespace std;

typedef unsigned char uchar;
#define MAX_BITS 65536// Maximum number of bits for the bitset

struct Node {
    uchar ch;
    int freq;
    int index;
    Node* left;
    Node* right;

    Node(uchar c, int f, int i) : ch(c), freq(f), index(i), left(nullptr), right(nullptr) {}
};
    

// Return a pair: the bitset and the number of valid bits
pair<bitset<MAX_BITS>, int> huffmanCoding(const string& input) {
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

    // Generate the Huffman codes using bitset
    struct BitCode {
        bitset<1024> bits;
        int length = 0;
    } code[256];

    function<void(Node*, bitset<1024>, int)> generateCodes = [&](Node* node, bitset<1024> bits, int len) {
        if (!node) return;
        if (node->ch != '\0') {
            code[node->ch].bits = bits;
            code[node->ch].length = len;
        }
        if (node->left) {
            bits[len] = 0;
            generateCodes(node->left, bits, len + 1);
        }
        if (node->right) {
            bits[len] = 1;
            generateCodes(node->right, bits, len + 1);
        }
    };
    bitset<1024> emptyBits;
    generateCodes(root, emptyBits, 0);

    // Encode the input string using the generated Huffman codes (bitset)
    bitset<MAX_BITS> ansBits;
    int ansLen = 0;
    for (uchar c : input) {
        for (int i = 0; i < code[c].length; ++i) {
            ansBits[ansLen++] = code[c].bits[i];
        }
    }

    return {ansBits, ansLen};
}

string binaryBitsetToHex(const bitset<MAX_BITS>& bits, int bitlen) {
    // padding to multiple of 4
    int paddedLen = bitlen + (4 - (bitlen % 4)) % 4;
    string hexStr;
    for (int i = 0; i < paddedLen; i += 4) {
        int value = 0;
        for (int j = 0; j < 4; ++j) {
            int idx = i + j;
            value = (value << 1) | (idx < bitlen ? bits[idx] : 0);
        }
        hexStr += (value < 10) ? (char)(value + '0') : (char)(value - 10 + 'A');
    }
    return hexStr;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string input;
    getline(cin, input);
    auto [bits, bitlen] = huffmanCoding(input);
    cout << binaryBitsetToHex(bits, bitlen) << endl;

    return 0;
}