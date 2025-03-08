#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <chrono>
using namespace std;

void quickSort(vector<int> &arr, int low, int high) {
    // only 1 elements
    if(low >= high) return;

    // select pivot
    int pivot = arr[high];
    // correct position of pivot
    int i = low;

    // from low to high-1
    for (int j = low; j < high; j++) {
        // move the element smaller than pivot to the left
        if(arr[j] < pivot) {
            swap(arr[i++], arr[j]);
        }
    }

    // move the pivot to the correct position
    swap(arr[i], arr[high]);

    quickSort(arr, low, i-1);
    quickSort(arr, i+1, high);
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
        quickSort(arr, 0, arr.size()-1);
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