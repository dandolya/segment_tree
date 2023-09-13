#include <iostream>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include<string.h>
#include <fstream>
#include <string>
 
using namespace std;
 
vector <long long> arr(0);
vector <long long> treeSum(0);
vector <long long> treeMin(0);
vector <long long> treeCoord(0);
 
void build(long long v, long long vl, long long vr)
{
	if (vl + 1 == vr) {
		treeSum[v] = arr[vl];
		treeMin[v] = arr[vl];
		treeCoord[v] = vl;
		return;
	}
	long long vm = vl + (vr - vl) / 2;
	build(2 * v + 1, vl, vm);
	build(2 * v + 2, vm, vr);
	treeSum[v] = treeSum[2 * v + 1] + treeSum[2 * v + 2];
	treeMin[v] = min(treeMin[2 * v + 1], treeMin[2 * v + 2]);
	if (treeMin[2 * v + 1] < treeMin[2 * v + 2])
	{
		treeCoord[v] = treeCoord[2 * v + 1];
	}
	else
	{
		treeCoord[v] = treeCoord[2 * v + 2];
	}
}
 
long long get_sum(long long v, long long vl, long long vr, long long ql, long long qr)
{
	if (qr <= vl || vr <= ql)
	{
		return 0;
	}
	else if (ql <= vl && vr <= qr)
	{
		return treeSum[v];
	}
	long long vm = vl + (vr - vl) / 2;
	return get_sum(2 * v + 1, vl, vm, ql, qr) + get_sum(2 * v + 2, vm, vr, ql, qr);
}
 
pair <long long, long long> get_min(long long v, long long vl, long long vr, long long ql, long long qr)
{
	if (qr <= vl || vr <= ql)
	{
		return { LLONG_MAX, -1 };
	}
	else if (ql <= vl && vr <= qr)
	{
		return { treeMin[v], treeCoord[v] };
	}
	long long vm = vl + (vr - vl) / 2;
	pair <long long, long long> p1 = get_min(2 * v + 1, vl, vm, ql, qr);
	pair <long long, long long> p2 = get_min(2 * v + 2, vm, vr, ql, qr);
	pair <long long, long long> p;
	p.first = min(p1.first, p2.first);
	if (p1.first < p2.first && p1.second != -1)
	{
		p.second = p1.second;
	}
	else
	{
		p.second = p2.second;
	}
	return p;
}
 
long long Best = -1;
long long coordLBest = 0;
long long coordRBest = 0;
 
void getBest(long long v, long long vl, long long vr, long long ql, long long qr)
{
	pair <long long, long long> p = get_min(v, vl, vr, ql, qr);
	long long a = get_sum(v, vl, vr, ql, qr) * p.first;
	if (a > Best)
	{
		Best = a;
		coordLBest = ql + 1;
		coordRBest = qr;
	}
	if (ql + 1 < qr)
	{
		getBest(v, vl, vr, ql, p.second);
		getBest(v, vl, vr, p.second + 1, qr);
	}
}
 
int main()
{
	long long n;
	cin >> n;
	arr.resize(n);
	treeSum.resize(4 * n);
	treeMin.resize(4 * n);
	treeCoord.resize(4 * n);
	for (long long i = 0; i < n; i++)
	{
		cin >> arr[i];
	}
	build(0, 0, n);
	getBest(0, 0, n, 0, n);
	cout << Best << "\n" << coordLBest << " " << coordRBest;
}
