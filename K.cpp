#include <iostream>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include<string.h>
#include <fstream>
#include <string>
 
using namespace std;
 
vector <int> arr1(0);
vector <int> arr2(0);
vector <int> arr3(0);
vector <int> arr4(0);
vector <int> tree1(0);
vector <int> tree2(0);
vector <int> tree3(0);
vector <int> tree4(0);
 
void build(int v, int vl, int vr, int r)
{
	if (vl + 1 == vr) {
		tree1[v] = arr1[vl];
		tree2[v] = arr2[vl];
		tree3[v] = arr3[vl];
		tree4[v] = arr4[vl];
		return;
	}
	int vm = vl + (vr - vl) / 2;
	build(2 * v + 1, vl, vm, r);
	build(2 * v + 2, vm, vr, r);
	if (tree1[2 * v + 1] == 1 && tree2[2 * v + 1] == 0 && tree3[2 * v + 1] == 0 && tree4[2 * v + 1] == 1)
	{
		tree1[v] = tree1[2 * v + 2];
		tree2[v] = tree2[2 * v + 2];
		tree3[v] = tree3[2 * v + 2];
		tree4[v] = tree4[2 * v + 2];
	}
	else if (tree1[2 * v + 2] == 1 && tree2[2 * v + 2] == 0 && tree3[2 * v + 2] == 0 && tree4[2 * v + 2] == 1)
	{
		tree1[v] = tree1[2 * v + 1];
		tree2[v] = tree2[2 * v + 1];
		tree3[v] = tree3[2 * v + 1];
		tree4[v] = tree4[2 * v + 1];
	}
	else
	{
		tree1[v] = ((tree1[2 * v + 1] * tree1[2 * v + 2]) % r + (tree2[2 * v + 1] * tree3[2 * v + 2]) % r) % r;
		tree2[v] = ((tree1[2 * v + 1] * tree2[2 * v + 2]) % r + (tree2[2 * v + 1] * tree4[2 * v + 2]) % r) % r;
		tree3[v] = ((tree3[2 * v + 1] * tree1[2 * v + 2]) % r + (tree4[2 * v + 1] * tree3[2 * v + 2]) % r) % r;
		tree4[v] = ((tree3[2 * v + 1] * tree2[2 * v + 2]) % r + (tree4[2 * v + 1] * tree4[2 * v + 2]) % r) % r;
	}
}
 
vector <int> get_product(int v, int vl, int vr, int ql, int qr, int r)
{
	if (qr <= vl || vr <= ql)
	{
		vector<int> a = { 1, 0, 0, 1 };
		return a;
	}
	else if (ql <= vl && vr <= qr)
	{
		vector<int> a = { tree1[v], tree2[v], tree3[v], tree4[v] };
		return a;
	}
	int vm = vl + (vr - vl) / 2;
	vector<int> arr1(4);
	arr1 = get_product(2 * v + 1, vl, vm, ql, qr, r);
	vector<int> arr2(4);
	arr2 = get_product(2 * v + 2, vm, vr, ql, qr, r);
	vector<int> arr(4);
 
	if (arr1[0] == 1 && arr1[1] == 0 && arr1[2] == 0 && arr1[3] == 1)
	{
		return arr2;
	}
	if (arr2[0] == 1 && arr2[1] == 0 && arr2[2] == 0 && arr2[3] == 1)
	{
		return arr1;
	}
	arr[0] = (((arr1[0] * arr2[0]) % r) + ((arr1[1] * arr2[2]) % r)) % r;
	arr[1] = (((arr1[0] * arr2[1]) % r) + ((arr1[1] * arr2[3]) % r)) % r;
	arr[2] = (((arr1[2] * arr2[0]) % r) + ((arr1[3] * arr2[2]) % r)) % r;
	arr[3] = (((arr1[2] * arr2[1]) % r) + ((arr1[3] * arr2[3]) % r)) % r;
	return arr;
}
 
int main()
{
	ifstream fileIn;
	fileIn.open("crypto.in");
	int r, n, m;
	fileIn >> r >> n >> m;
	arr1.resize(n);
	arr2.resize(n);
	arr3.resize(n);
	arr4.resize(n);
	tree1.resize(4 * n);
	tree2.resize(4 * n);
	tree3.resize(4 * n);
	tree4.resize(4 * n);
	for (int i = 0; i < n; i++)
	{
		fileIn >> arr1[i] >> arr2[i] >> arr3[i] >> arr4[i];
	}
	build(0, 0, n, r);
	string str;
 
	for (int i = 0; i < m; i++)
	{
		int a, b;
		fileIn >> a >> b;
		vector <int >c(4);
		c = get_product(0, 0, n, a - 1, b, r);
		str += to_string(c[0]) + " " + to_string(c[1]) + "\n" + to_string(c[2]) + " " + to_string(c[3]) + "\n\n";
	}
	ofstream fileOut;
	fileOut.open("crypto.out");
 
	fileOut << str;
}
