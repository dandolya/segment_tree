#include <iostream>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include<string.h>
#include <string>
using namespace std;
 
void build(vector <long long>& arr, vector <long long>& tree, int v, int vl, int vr)
{
	if (vl + 1 == vr) {
		tree[v] = arr[vl];
		return;
	}
	int vm = vl + (vr - vl) / 2;
	build(arr, tree, 2 * v + 1, vl, vm);
	build(arr, tree, 2 * v + 2, vm, vr);
	tree[v] = tree[2 * v + 1] + tree[2 * v + 2];
}
 
long long get_sum(vector<long long>& tree, int v, int vl, int vr, int ql, int qr)
{
	if (qr <= vl || vr <= ql)
	{
		return 0;
	}
	else if (ql <= vl && vr <= qr)
	{
		return tree[v];
	}
	int vm = vl + (vr - vl) / 2;
	return get_sum(tree, 2 * v + 1, vl, vm, ql, qr) + get_sum(tree, 2 * v + 2, vm, vr, ql, qr);
}
 
void set(vector<long long>& tree, int v, int vl, int vr, int q, int x)
{
	if (q < vl || vr <= q)
	{
		return;
	}
	if (vl + 1 == vr)
	{
		tree[v] = x;
		return;
	}
	int vm = vl + (vr - vl) / 2;
	set(tree, 2 * v + 1, vl, vm, q, x);
	set(tree, 2 * v + 2, vm, vr, q, x);
	tree[v] = tree[2 * v + 1] + tree[2 * v + 2];
}
 
int main()
{
	int n;
	cin >> n;
	vector <long long> arr1(n);
	vector <long long> arr2(n);
	for (int i = 0; i < n; i++)
	{
		
		if (i % 2 == 0)
		{
			cin >> arr1[i];
			arr2[i] = -arr1[i];
		} 
		else 
		{
			cin >> arr2[i];
			arr1[i] = -arr2[i];
		}
	}
	vector <long long> tree1(4 * n);
	vector <long long> tree2(4 * n);
	build(arr1, tree1, 0, 0, n);
	build(arr2, tree2, 0, 0, n);
	string str;
	int m;
	cin >> m;
	for (int i = 0; i < m; i++)
	{
		int a, b, c;
		cin >> a >> b >> c;
		if (a == 1)
		{
			if (b % 2 == 0)
			{
				str += to_string(get_sum(tree2, 0, 0, n, b - 1, c)) + "\n";
			}
			else
			{
				str += to_string(get_sum(tree1, 0, 0, n, b - 1, c)) + "\n";
			}
		}
		else
		{
			b--;
			if (b % 2 == 0)
			{
				set(tree1, 0, 0, n, b, c);
				set(tree2, 0, 0, n, b, -c);
			}
			else
			{
				set(tree2, 0, 0, n, b, c);
				set(tree1, 0, 0, n, b, -c);
			}
		}
	}
	cout << str;
}
