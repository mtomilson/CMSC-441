#include <iostream>
#include <vector>
#include <numeric>
#include <chrono>
using namespace std;
using namespace std::chrono;


void generateCombinationsHelper(vector<int>& arr, vector<int>& data, int start, int end, int index, int r, long long& count);

long generateCombinations(int n, int r);


int main() {
        int n = 35;
        int i = n / 2;
        auto start = high_resolution_clock::now();
        long count = generateCombinations(n, i);
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(end - start).count();
        cout << "n = " << n << ", i = " << i
             << " → combinations = " << count
             << ", time = " << duration << " ms\n";
    
}
void generateCombinationsHelper(vector<int>& arr, vector<int>& data, int start, int end, int index, int r, long long& count) {
    if (index == r) {
        count++;
        return;
    }

    for (int i = start; i <= end && end - i + 1 >= r - index; i++) {
        data[index] = arr[i];
        generateCombinationsHelper(arr, data, i + 1, end, index + 1, r, count);
    }
}

long generateCombinations(int n, int r) {
    vector<int> arr(n);
    iota(arr.begin(), arr.end(), 1);
    vector<int> data(r);
    long long count = 0;
    generateCombinationsHelper(arr, data, 0, n - 1, 0, r, count);
    return count;
}
