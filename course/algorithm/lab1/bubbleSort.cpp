#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <chrono>
using namespace std;

void bubbleSort(vector<int> &arr, int n) {
    for(int i=0; i<n; i++) {
        for(int j=0; j<n-i-1; j++) { // last i elements are already sorted
            if(arr[j] > arr[j+1]) {
                swap(arr[j], arr[j+1]);
            }
        }
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
        bubbleSort(arr, arr.size());
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
        cout << "Bubble sort cost: " << duration.count() << " 10^-9 (sec)" << endl;

        // print the sorted array
        cout << "Sorted array < [10]: ";
        for(int i=0; i<10; i++) {
            cout << arr[i] << " ";
        }
        
        cout << "\n" << endl;
    }



    return 0;
}