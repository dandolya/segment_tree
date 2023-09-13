 
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>
using namespace std;
 
int main() {
    int n;
     long long x, y, a_0;
    cin >> n >> x >> y >> a_0;
    vector <long long> prefixSum(n);
    prefixSum[0] = a_0;
    prefixSum[1] = a_0 + ((x * a_0 + y) % 65536);
    for (long long i = 2; i < n; i++)
    {
        prefixSum[i] = prefixSum[i - 1] + (x * (prefixSum[i - 1] - prefixSum[i - 2]) + y) % 65536;
    }
    int m;
    long long z, t, b_0;
    cin >> m >> z >> t >> b_0;
    vector <long long> c(m * 2);
    long long b = b_0;
    if (m > 0) {
        c[0] = b_0 % n;
    }
    for (long long i = 1; i < m * 2; i++) 
    {
        long long i1 = z * b + t;
        if (i1 >= 0) {
            b = i1 % 1073741824;
        }
        else {
            b = 1073741824 + i1;
        }
        c[i] = b % n;
    }
    long long sum = 0;
    for (long long i = 0; i < m; i++) {
        long long l = min(c[2 * i], c[2 * i + 1]);
        long long r = max(c[2 * i], c[2 * i + 1]);
        sum += prefixSum[r];
        if (l > 0) {
            sum -= prefixSum[l - 1];
        }
    }
    cout << sum;
}
