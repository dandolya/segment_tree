#include <iostream>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include<string.h>
#include <string>
 
using namespace std;
 
void build(vector <long long> arr, vector <long long>& sparseTable, vector <int> loges, int n)
{
    for (int i = 0; i < n; i++)
    {
        sparseTable[i] = arr[i];
    }
    int minus = 1;
    for (int i = 1; i <= loges[n]; i++)
    {
        for (int j = 0; j < n - minus; j++) {
            sparseTable[i * n + j] = min(sparseTable[(i - 1) * n + j], sparseTable[(i - 1) * n + j + pow(2, i - 1)]);
        }
        minus += pow(2, i);
    }
}
 
int get_min(vector <long long> sparseTable, vector <int> loges, int n, int ql, int qr)
{
    int a = loges[qr - ql + 1];
    return min(sparseTable[a * n + ql - 1], sparseTable[a * n + qr - pow(2, a)]);
}
 
int main()
{
    int n, m, a_0;
    cin >> n >> m >> a_0;
    vector <long long> arr(n);
    vector <int> loges(n + 1);
    arr[0] = a_0;
    for (int i = 1; i <= n; i++)
    {
        loges[i] = (int)log2(i);
        if (i != n)
        {
            arr[i] = (23 * arr[i - 1] + 21563) % 16714589;
        }
    }
    vector <long long> sparseTable(n * (loges[n] + 1));
    build(arr, sparseTable, loges, n);
    int u, v;
    cin >> u >> v;
    int r;
    if (u < v)
    {
        //r = get_min(sparseTable, loges, n, u, v);
        int a = loges[v - u + 1];
        r = min(sparseTable[a * n + u - 1], sparseTable[a * n + v - pow(2, a)]);
    }
    else
    {
        int a = loges[u - v + 1];
        r = min(sparseTable[a * n + v - 1], sparseTable[a * n + u - pow(2, a)]);
    }
    for (int i = 1; i < m; i++)
    {
        u = ((17 * u + 751 + r + i * 2) % n) + 1;
        v = ((13 * v + 593 + r + i * 5) % n) + 1;
 
        if (u < v)
        {
            int a = loges[v - u + 1];
            r = min(sparseTable[a * n + u - 1], sparseTable[a * n + v - pow(2, a)]);
        }
        else
        {
            int a = loges[u - v + 1];
            r = min(sparseTable[a * n + v - 1], sparseTable[a * n + u - pow(2, a)]);
        }
    }
    cout << u << " " << v << " " << r;
}
