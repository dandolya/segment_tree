#include <iostream>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include <string.h>
#include <string>
#include <fstream>
 
using namespace std;
 
vector <int> arr(0);
vector <int> tree(0);
vector <int> setTree(0);
 
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
		if (setTree[v] != INT_MAX)
		{
			setTree[2 * v + 1] = setTree[v];
			tree[2 * v + 1] = setTree[v];
			setTree[2 * v + 2] = setTree[v];
			tree[2 * v + 2] = setTree[v];
		}
	}
	setTree[v] = INT_MAX;
}
 
int get_min(int v, int vl, int vr, int ql, int qr)
{
	if (qr <= vl || vr <= ql)
	{
		return INT_MAX;
	}
	else if (ql <= vl && vr <= qr)
	{
		return tree[v];
	}
	int vm = vl + (vr - vl) / 2;
	push(v, vl, vr);
	return min(get_min(2 * v + 1, vl, vm, ql, qr), get_min(2 * v + 2, vm, vr, ql, qr));
}
 
void set(int v, int vl, int vr, int ql, int qr, int x)
{
	if (ql >= vr || qr <= vl)
	{
		return;
	}
	if (ql <= vl && qr >= vr)
	{
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
 
struct finds
{
	vector <int> a;
	vector <int> b;
	vector <int> c;
};
 
finds merge(finds f1, finds f2, int n1, int n2)
{
	vector <int> a3(n1 + n2);
	vector <int> b3(n1 + n2);
	vector <int> c3(n1 + n2);
	finds f3 = { a3, b3, c3 };
	int i = 0, j = 0, k = 0;
	while (i < n1 && j < n2)
	{
		if (f1.c[i] < f2.c[j])
		{
			f3.c[k] = f1.c[i];
			f3.b[k] = f1.b[i];
			f3.a[k] = f1.a[i];
			i++;
		}
		else
		{
			f3.c[k] = f2.c[j];
			f3.b[k] = f2.b[j];
			f3.a[k] = f2.a[j];
			j++;
		}
		k++;
	}
	while (i < n1)
	{
		f3.c[k] = f1.c[i];
		f3.b[k] = f1.b[i];
		f3.a[k] = f1.a[i];
		i++;
		k++;
	}
	while (j < n2) {
		f3.c[k] = f2.c[j];
		f3.b[k] = f2.b[j];
		f3.a[k] = f2.a[j];
		j++;
		k++;
	}
	return f3;
}
 
finds mergeSort(finds f, int n)
{
	if (n == 1)
	{
		return f;
	}
	vector <int> c1(n / 2);
	vector <int> a1(n / 2);
	vector <int> b1(n / 2);
	vector <int> c2(n - (n / 2));
	vector <int> a2(n - (n / 2));
	vector <int> b2(n - (n / 2));
	for (int i = 0; i < n / 2; i++)
	{
		c1[i] = f.c[i];
		a1[i] = f.a[i];
		b1[i] = f.b[i];
	}
	for (int i = 0; i < n - (n / 2); i++)
	{
		c2[i] = f.c[n / 2 + i];
		a2[i] = f.a[n / 2 + i];
		b2[i] = f.b[n / 2 + i];
	}
	finds f1 = { a1, b1, c1 };
	finds f2 = { a2, b2, c2 };
	f1 = mergeSort (f1, n / 2);
	f2 = mergeSort (f2, n - (n / 2));
	return merge(f1, f2, n / 2, n - (n / 2));
}
 
int main()
{
	ifstream fileIn;
	fileIn.open("rmq.in");
 
	int n, m;
	fileIn >> n >> m;
	tree.resize(4 * n);
	string s, str;
	setTree.resize(4 * n, INT_MAX);
 
	vector <int> al(m);
	vector <int> bl(m);
	vector <int> cl(m);
	for (int i = 0; i < m; i++)
	{
		fileIn >> al[i] >> bl[i] >> cl[i];
	}
	fileIn.close();
	finds f = { al, bl, cl };
	f = mergeSort(f, m);
	for (int i = 0; i < m; i++)
	{
		set(0, 0, n, f.a[i] - 1, f.b[i], f.c[i]);
	}
	
	bool b = false;
 
	for (int i = 0; i < m; i++)
	{
		if (get_min(0, 0, n, f.a[i] - 1, f.b[i]) != f.c[i])
		{
			b = true;
			break;
		}
	}
	ofstream fileOut;
	fileOut.open("rmq.out");
	if (b)
	{
		fileOut << "inconsistent";
	}
	else
	{
		fileOut << "consistent\n";
		for (int i = 0; i < n; i++)
		{
			fileOut << get_min(0, 0, n, i, i + 1) << " ";
		}
	}
}
