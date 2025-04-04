#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <chrono>
using namespace std;

void mergeSort(vector<int> &arr, int l, int r) {
    // left: arr.begin, right: arr.end
    if (l >= r) return;
    int m = l + (r-l)/2;

    mergeSort(arr, l, m);
    mergeSort(arr, m+1, r);

    // merge
    vector<int> left(m-l+1), right(r-m);
    // copy array to temp array
    for (int i=0; i<left.size(); i++) {
        left[i] = arr[l+i];
    }
    for (int i=0; i<right.size(); i++) {
        right[i] = arr[m+1+i];
    }

    // pointer to left, right, and original array
    int i=0, j=0, k=l;

    while(i<left.size() && j<right.size()) {
        // compare left and right
        // copy the smaller one and move the pointer
        if (left[i] <= right[j]) {
            arr[k++] = left[i++];
        } else {
            arr[k++] = right[j++];
        }
    }
    // copy the rest of left
    while(i<left.size()) {
        arr[k++] = left[i++];
    }
    // copy the rest of right
    while(j<right.size()) {
        arr[k++] = right[j++];
    }
}

int main() {

    // progress count
    int lineIndex = 1;

    // read csv
    ifstream data("./data/data.csv");

    // for reading a line
    string line{};

    // read the file line by line
    while (getline(data, line)) {
        cout << "Line " << lineIndex++ << ": ";

        // input string stream
        istringstream iss(line);

        // each element in the line
        vector<int> arr;
        string substring{};

        // read each element from iss
        while (getline(iss, substring, ',')) {
            arr.push_back(stoi(substring));
        }

        // print elements count
        cout << "Elements count: " << arr.size() << endl;

        // sort the array
        auto start = chrono::high_resolution_clock::now();
        mergeSort(arr, 0, arr.size()-1);
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
        cout << "Merge sort cost: " << duration.count() << " 10^-9 (sec)" << endl;

        // print the sorted array
        cout << "Sorted array < [10]: ";
        for(int i=0; i<10; i++) {
            cout << arr[i] << " ";
        }
        
        cout << "\n" << endl;
    }

    return 0;
}