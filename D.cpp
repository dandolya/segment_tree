#include <iostream>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include <string.h>
#include <string>
using namespace std;
 
vector <long long> arr(0);
vector <long long> tree(0);
vector <long long> setTree(0);
vector <long long> addTree(0);
 
void build(int v, int vl, int vr)
{
	if (vl + 1 == vr) {
		tree[v] = arr[vl];
		return;
	}
	int vm = vl + (vr - vl) / 2;
	build(2 * v + 1, vl, vm);
	build(2 * v + 2, vm, vr);
	tree[v] = min(tree[2 * v + 1], tree[2 * v + 2]);
}
 
void push(int v, int vl, int vr)
{
	if (vl + 1 < vr)
	{
		if (setTree[v] != LLONG_MAX)
		{
			setTree[2 * v + 1] = setTree[v];
			addTree[2 * v + 1] = 0;
			tree[2 * v + 1] = setTree[v];
			setTree[2 * v + 2] = setTree[v];
			addTree[2 * v + 2] = 0;
			tree[2 * v + 2] = setTree[v];
		}
 
		if (addTree[v] != 0)
		{
			tree[2 * v + 1] += addTree[v];
			tree[2 * v + 2] += addTree[v];
			addTree[2 * v + 1] += addTree[v];
			addTree[2 * v + 2] += addTree[v];
		}
	}
	addTree[v] = 0;
	setTree[v] = LLONG_MAX;
}
 
long long get_min(int v, int vl, int vr, long long ql, long long qr)
{
	if (qr <= vl || vr <= ql)
	{
		return LLONG_MAX;
	}
	else if (ql <= vl && vr <= qr)
	{
		return tree[v];
	}
	int vm = vl + (vr - vl) / 2;
	push(v, vl, vr);
	return min(get_min(2 * v + 1, vl, vm, ql, qr), get_min(2 * v + 2, vm, vr, ql, qr));
}
 
void set(int v, int vl, int vr, int ql, int qr, long long x)
{
	if (ql >= vr || qr <= vl)
	{
		return;
	}
	if (ql <= vl && qr >= vr)
	{
		addTree[v] = 0;
		setTree[v] = x;
		tree[v] = x;
		return;
	}
	if (vl + 1 == vr)
	{
		return;
	}
	int vm = vl + (vr - vl) / 2;
	push(v, vl, vr);
	set(2 * v + 1, vl, vm, ql, qr, x);
	set(2 * v + 2, vm, vr, ql, qr, x);
	tree[v] = min(tree[2 * v + 1], tree[2 * v + 2]);
}
 
void addfck(int v, int vl, int vr, int ql, int qr, long long x)
{
	if (ql >= vr || qr <= vl)
	{
		return;
	}
	if (ql <= vl && qr >= vr)
	{
		addTree[v] += x;
		push(v, vl, vr);
		tree[v] += x;
		return;
	}
	if (vl + 1 == vr)
	{
		return;
	}
	int vm = vl + (vr - vl) / 2;
	push(v, vl, vr);
	addfck(2 * v + 1, vl, vm, ql, qr, x);
	addfck(2 * v + 2, vm, vr, ql, qr, x);
	tree[v] = min(tree[2 * v + 1], tree[2 * v + 2]);
}
 
int main()
{
	int n;
	cin >> n;
	arr.resize(n);
	for (int i = 0; i < n; i++)
	{
		cin >> arr[i];
	}
	tree.resize(4 * n);
	build(0, 0, n);
	string s, str;
	setTree.resize(4 * n);
	for (long long i = 0; i < 4 * n; i++)
	{
		setTree[i] = LLONG_MAX;
	}
	addTree.resize(4 * n);
	while (cin >> s)
	{
		int a, b;
		cin >> a >> b;
		if (s[0] == 'm')
		{
			str += to_string(get_min(0, 0, n, a - 1, b)) + "\n";
		}
		if (s[0] == 's')
		{
			long long c;
			cin >> c;
			set(0, 0, n, a - 1, b, c);
		}
		if (s[0] == 'a')
		{
			long long c;
			cin >> c;
			addfck(0, 0, n, a - 1, b, c);
		}
	}
	cout << str;
}
