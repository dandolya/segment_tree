#include <iostream>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include <string.h>
#include <string>
#include <fstream>
 
using namespace std;
 
vector <long long> arr(0);
vector <long long> tree(0);
 
void build(int v, int vl, int vr)
{
	if (vl + 1 == vr) {
		tree[v] = arr[vl];
		return;
	}
	int vm = vl + (vr - vl) / 2;
	build(2 * v + 1, vl, vm);
	build(2 * v + 2, vm, vr);
	tree[v] = max(tree[2 * v + 1], tree[2 * v + 2]);
}
 
int enter(int v, int vl, int vr, int q)
{
	if (vl + 1 == vr)
	{
		tree[v] = -1;
		return vl;
	}
	int a;
	if (tree[2 * v + 1] >= q)
	{
		a = enter(2 * v + 1, vl, vl + (vr - vl) / 2, q);
	}
	 else if (tree[2 * v + 2] >= q)
	{
		a = enter(2 * v + 2, vl + (vr - vl) / 2, vr, q);
	}
	else if (tree[2 * v + 1] != -1)
	{
		a = enter(2 * v + 1, vl, vl + (vr - vl) / 2, q);
	}
	else
	{
		a = enter(2 * v + 2, vl + (vr - vl) / 2, vr, q);
	}
	tree[v] = max(tree[2 * v + 1], tree[2 * v + 2]);
	return a;
}
 
void exit(int v, int vl, int vr, int q)
{
	if (q < vl || vr <= q)
	{
		return;
	}
	if (vl + 1 == vr)
	{
		tree[v] = q;
		return;
	}
	int vm = vl + (vr - vl) / 2;
	exit(2 * v + 1, vl, vm, q);
	exit(2 * v + 2, vm, vr, q);
	tree[v] = max(tree[2 * v + 1], tree[2 * v + 2]);
}
 
int main()
{
	ifstream fileIn;
	fileIn.open("parking.in");
 
	int n, m;
	fileIn >> n >> m;
	arr.resize(n);
	for (int i = 0; i < n; i++)
	{
		arr[i] = i;
	}
	tree.resize(4 * n);
	build(0, 0, n);
	string s, str;
	for (int i = 0; i < m; i++)
	{
		fileIn >> s;
		int a;
		fileIn >> a;
		if (s[1] == 'n')
		{
			str += to_string(enter(0, 0, n, a - 1) + 1) + "\n";
		}
		if (s[1] == 'x')
		{
			exit(0, 0, n, a - 1);
		}
	}
 
	ofstream fileOut;
	fileOut.open("parking.out");
	fileOut << str;
}
