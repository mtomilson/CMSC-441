#include <iostream>
#include <cmath>
#include <map>
#include <chrono> 
#include <vector>
#include <numeric>



using namespace std;
using namespace std::chrono;

void minimalChangeAlgo(int n, vector<int>& arr);
int findLargestMobile(vector<int>& arr, vector<int>& dir);
void johnsonTrotterAlgo(int n);

int main() {
        int n = 9;

        vector<int> arr(n);
        iota(arr.begin(), arr.end(), 1);

        auto start1 = high_resolution_clock::now();
        minimalChangeAlgo(n, arr);
        auto end1 = high_resolution_clock::now();
        auto start2 = high_resolution_clock::now();
        johnsonTrotterAlgo(n);
        auto end2 = high_resolution_clock::now();
        
        auto dur1 = duration_cast<milliseconds>(end1 - start1).count();
        auto dur2 = duration_cast<milliseconds>(end2 - start2).count();

        cout << "n = " << n << "\n";
        cout << "Minimal-Change Time: " << dur1 << " ms\n";
        cout << "Johnson Trotter Time: " << dur2 << " ms\n";
    


    
    return 0;
}

int findLargestMobile(vector<int>& arr, vector<int>& dir) {
    int mobile = -1;
    int mobileIndex = -1;
    int n = arr.size();

    for (int i = 0; i < n; i++) {
        int neighbor = i + dir[arr[i]];
        if (neighbor >= 0 && neighbor < n && arr[i] > arr[neighbor] && arr[i] > mobile) {
            mobile = arr[i];
            mobileIndex = i;
        }
    }

    return mobileIndex;
}

void johnsonTrotterAlgo(int n) {
    vector<int> arr(n);
    iota(arr.begin(), arr.end(), 1);

    vector<int> dir(n + 1, -1);

    while (true) {
        for (int x : arr) {
            cout << x << " ";
        }
        cout << "\n";

        int mobileIndex = findLargestMobile(arr, dir);
        if (mobileIndex == -1) {
            break;
        }

        int mobile = arr[mobileIndex];
        int neighbor = mobileIndex + dir[mobile];

        swap(arr[mobileIndex], arr[neighbor]);

        for (int i = 1; i <= n; i++) {
            if (i > mobile) dir[i] *= -1;
        }
    }
}


void minimalChangeAlgo(int n, vector<int>& arr) {
    if(n == 1) {
        for(int x : arr) {
            cout << x << " ";
        }
        cout << "\n";
        return;

    }

    for(int i = 0; i < n - 1; i++ ) {
        minimalChangeAlgo(n - 1, arr); 
        if(n % 2 == 0) {
            swap(arr[i], arr[n - 1]);
        }
        else {
            swap(arr[0], arr[n - 1]);
        }
    }
    minimalChangeAlgo(n - 1, arr);
}