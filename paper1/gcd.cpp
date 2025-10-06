#include <iostream>
#include <cmath>
#include <map>
#include <chrono> // necessary for measuring duration of functions

using namespace std;

// gcd calculation using prime factorization
map<int, int> primeFactors(int n);
int primeFactorGcd(int m, int n);

// gcd caculation using euclid's method
int euclidGcd(int m, int n);

// gcd calculation using iterative approach
int iterativeGcd(int m, int n);
void print(int m, int n);

int divisions = 0;

int main()
{
    // numbers
    // small pairs m = 100-200, and n around 60
    // int m[5] = {110, 124, 133, 154, 120};
    // int n[5] = {54, 64, 57, 61, 54};

    // second pairs
    // int m[5] = {1200, 1550, 1724, 1820, 1340};
    // int n[5] = {640, 720, 630, 824, 540};

    // large pairs
    int m[5] = {9876543, 12345678, 98765432, 45678912, 87654321};
    int n[5] = {1234567, 9876543, 12345678, 34567890, 76543210};


    for (int i = 0; i < 5; i++)
    {
        cout << "Evalutated: " << m[i] << " & " << n[i] << endl;
        cout << endl;
        print(m[i], n[i]);
    }

    return 0;
}

void print(int m, int n)
{
    using std::chrono::duration;
    using std::chrono::high_resolution_clock;
    using std::chrono::milliseconds;

    divisions = 0;

    auto t1 = high_resolution_clock::now();
    int pfgcd = primeFactorGcd(m, n);
    auto t2 = high_resolution_clock::now();
    duration<double, std::milli> totalTime = t2 - t1;

    cout << "GCD from prime factorization: " << pfgcd << endl;
    cout << "Time for prime factorization: " << totalTime.count() << endl;
    cout << "Amount of Divisions: " << divisions << endl;
    cout << endl;

    divisions = 0;

    t1 = high_resolution_clock::now(); // start of time

    int iterGCD = iterativeGcd(m, n);

    t2 = high_resolution_clock::now(); //end of time 
    totalTime = t2 - t1; // time calculation

    cout << "GCD from iterative GCD: " << iterGCD << endl;
    cout << "Time for iterative GCD: " << totalTime.count() << endl; 
    cout << "Amount of Divisions: " << divisions << endl;
    cout << endl;

    divisions = 0;

    t1 = high_resolution_clock::now();
    int euclid = euclidGcd(m, n);
    t2 = high_resolution_clock::now();
    totalTime = t2 - t1;

    cout << "GCD from euclid GCD: " << euclid << endl;
    cout << "Total time for Euclid: " << totalTime.count() << endl;
    cout << "Amount of Divisions: " << divisions << endl;
    cout << "------" << endl;
}

map<int, int> primeFactors(int num)
{
    map<int, int> factors;

    for (int i = 2; i * i <= num; i++)
    {
        divisions++;
        while (num % i == 0)
        {
            divisions++;
            factors[i]++;
            num = num / i;
        }
    }
    if (num > 1)
    {
        factors[num]++;
    }
    return factors;
}

int primeFactorGcd(int num1, int num2)
{
    map<int, int> map1 = primeFactors(num1); // map for prime factors of number 1
    map<int, int> map2 = primeFactors(num2); // map for prime factors of number 2

    int gcd = 1; // must be 1, if no values are the same in maps, the gcd will be 1.

    for (auto const &factors : map1)
    {
        if (map2.count(factors.first))
        {                                                       // check if map2 has this prime factor, if not we don't use
            int exp = min(factors.second, map2[factors.first]); // figure out the smaller of the 2 exponents, this will tell us how many times to mult essentially
            gcd *= pow(factors.first, exp);
        }
    }

    return gcd;
}

int euclidGcd(int m, int n)
{
    while (n != 0)
    {
        int temp = n;
        n = m % n;
        divisions++;
        m = temp;
    }
    return m;
}

int iterativeGcd(int m, int n)
{
    int small = m > n ? n : m;
    int gcd = 1;

    for (int i = small; i > 0; i--)
    {
        divisions = divisions + 2;
        if (m % i == 0 && n % i == 0)
        {
            gcd = i;
            break; // once we find one gcd, we know it's the largest gcd break from loop
        }
    }

    return gcd;
}