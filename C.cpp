#include <iostream>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include<string.h>
#include <string>
using namespace std;
 
void build(vector <long long> &arr, vector <long long> &tree, int v, int vl, int vr)
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
 
long long get_sum(vector<long long> &tree, int v, int vl, int vr, int ql, int qr)
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
 
void set(vector<long long> &tree, int v, int vl, int vr, int q, int x)
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
	vector <long long> arr(n);
	for (int i = 0; i < n; i++)
	{
		cin >> arr[i];
	}
	vector <long long> tree(4 * n);
	build(arr, tree, 0, 0, n);
	string s, str;
	while (cin >> s)
	{
		int a, b;
		cin >> a >> b;
		if (s.compare("sum") == 0)
		{
			str += to_string(get_sum(tree, 0, 0, n, a - 1, b)) + "\n";
			//cout << get_min(tree, 0, 0, n, a - 1, b);
		}
		if (s.compare("set") == 0)
		{
			set(tree, 0, 0, n, a - 1, b);
		}
	}
	cout << str;
}
