#include <iostream>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include <string.h>
#include <string>
using namespace std;
 
vector <int> tree(0);
vector <int> treeCoord(0);
vector <int> setTree(0);
void build(int v, int vl, int vr)
{
	if (vl + 1 == vr) {
		treeCoord[v] = vl + 1;
		return;
	}
	int vm = vl + (vr - vl) / 2;
	build(2 * v + 1, vl, vm);
	build(2 * v + 2, vm, vr);
	treeCoord[v] = treeCoord[2 * v + 1];
}
 
void push(int v, int vl, int vr)
{
	if (vl + 1 != vr)
	{
		if (setTree[v] != INT_MAX)
		{
			if (setTree[v] > tree[2 * v + 1])
			{
				setTree[2 * v + 1] = setTree[v];
				tree[2 * v + 1] = setTree[2 * v + 1];
			}
			if (setTree[v] > tree[2 * v + 2])
			{
				setTree[2 * v + 2] = setTree[v];
				tree[2 * v + 2] = setTree[2 * v + 2];
			}
		}
	}
	setTree[v] = INT_MAX;
}
 
pair <int, int> get_min(int v, int vl, int vr, int ql, int qr)
{
	push(v, vl, vr);
	if (qr <= vl || vr <= ql)
	{
		pair <int, int> arr = { INT_MAX, -1 };
		return arr;
	}
	if (ql <= vl && vr <= qr)
	{
		pair <int, int> arr = { tree[v], treeCoord[v] };
		return arr;
	}
	int vm = vl + (vr - vl) / 2;
	pair <int, int> arr;
	pair <int, int> arr1;
	pair <int, int> arr2;
	arr1 = get_min(2 * v + 1, vl, vm, ql, qr);
	arr2 = get_min(2 * v + 2, vm, vr, ql, qr);
	arr.first = min(arr1.first, arr2.first);
 
	//мб здесь???
	if (arr1.first <= arr2.first && arr1.first != -1)
	{
		arr.second = arr1.second;
	}
	else if (arr2.first != -1)
	{
		arr.second = arr2.second;
	}
	else
	{
		//arr.second = 1234123 / 0;
	}
	//мб здесь???
 
	return arr;
}
 
void set(int v, int vl, int vr, int ql, int qr, int x)
{
	push(v, vl, vr);
	if (ql >= vr || qr <= vl)
	{
		return;
	}
	//if (x <= Tree[v])
	//{
		//return;
	//}
	if (ql <= vl && qr >= vr)
	{
		setTree[v] = x;
		tree[v] = max(tree[v], x);
		push(v, vl, vr);
		return;
	}
	int vm = vl + (vr - vl) / 2;
	set(2 * v + 1, vl, vm, ql, qr, x);
	set(2 * v + 2, vm, vr, ql, qr, x);
	tree[v] = min(tree[2 * v + 1], tree[2 * v + 2]);
	if (tree[2 * v + 1] < tree[2 * v + 2])
	{
		treeCoord[v] = treeCoord[2 * v + 1];
	}
	else
	{
		treeCoord[v] = treeCoord[2 * v + 2];
	}
}
 
int main()
{
	int n, m;
	cin >> n >> m;
	tree.resize(4 * n);
	treeCoord.resize(4 * n);
	build(0, 0, n);
	string str;
	setTree.resize(4 * n, INT_MAX);
	for (int i = 0; i < m; i++)
	{
		string s;
		int a, b;
		cin >> s >> a >> b;
		if (s[0] == 'a')
		{
			pair <int, int> arr = get_min(0, 0, n, a - 1, b);
			str += to_string(arr.first) + " " + to_string(arr.second) + "\n";
		}
		if (s[0] == 'd')
		{
			int c;
			cin >> c;
			set(0, 0, n, a - 1, b, c);
		}
	}
	cout << str;
}
