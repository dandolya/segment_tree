#include <iostream>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include<string.h>
#include <string>
using namespace std;
 
void push(vector<int>& flag, vector<int>& treeL, vector<int>& treeM, vector<int>& treeR, vector<int>& treeSum, int v, int vl, int vm, int vr)
{
	if (vl + 1 < vr)
	{
		if (flag[v] != 2)
		{
			flag[2 * v + 1] = flag[v];
			treeL[2 * v + 1] = flag[v];
			treeM[2 * v + 1] = flag[v];
			treeR[2 * v + 1] = flag[v];
			treeSum[2 * v + 1] = flag[v] * (vm - vl);
			flag[2 * v + 2] = flag[v];
			treeL[2 * v + 2] = flag[v];
			treeM[2 * v + 2] = flag[v];
			treeR[2 * v + 2] = flag[v];
			treeSum[2 * v + 2] = flag[v] * (vr - vm);
		}
	}
	flag[v] = 2;
}
 
void set(vector<int>& flag, vector<int>& treeL, vector<int>& treeM, vector<int>& treeR, vector<int>& treeSum, int v, int vl, int vr, int ql, int qr, int x)
{
	int vm = vl + (vr - vl) / 2;
	push(flag, treeL, treeM, treeR, treeSum, v, vl, vm, vr);
	if (ql <= vl && qr > vr)
	{
		treeL[v] = x;
		treeM[v] = x;
		treeR[v] = x;
		if (x == 1)
		{
			treeSum[v] = (vr - vl);
		}
		else
		{
			treeSum[v] = x;
		}
		flag[v] = x;
		return;
	}
	if (ql > vr || qr < vl || vl + 1 == vr)
	{
		return;
	}
	set(flag, treeL, treeM, treeR, treeSum, 2 * v + 1, vl, vm, ql, qr, x);
	set(flag, treeL, treeM, treeR, treeSum, 2 * v + 2, vm, vr, ql, qr, x);
	treeSum[v] = treeSum[2 * v + 1] + treeSum[2 * v + 2];
	treeM[v] = treeM[2 * v + 1] + treeM[2 * v + 2];
	treeL[v] = treeL[2 * v + 1];
	treeR[v] = treeR[2 * v + 2];
	if (treeR[2 * v + 1] == 1 && treeL[2 * v + 2] == 1)
	{
		treeM[v]--;
	}
}
 
int main()
{
	int m;
	cin >> m;
	vector <char> find(m);
	vector <int> left(m);
	vector <int> length(m);
	int min = INT_MAX, max = -1;
	for (int i = 0; i < m; i++)
	{
		cin >> find[i] >> left[i] >> length[i];
		if (left[i] < min)
		{
			min = left[i];
		}
		if (length[i] + left[i] > max)
		{
			max = length[i] + left[i];
		}
	}
	int n = max - min + 1;
	vector <int> treeL(4 * n);
	vector <int> treeM(4 * n);
	vector <int> treeR(4 * n);
	vector <int> treeSum(4 * n);
	vector <int> flag(4 * n, 2);
	string str;
	for (int i = 0; i < m; i++)
	{
		if (find[i] == 'W')
		{
			set(flag, treeL, treeM, treeR, treeSum, 0, 0, n, left[i] - min, left[i] - min + length[i] + 1, 0);
			str += to_string(treeM[0]) + " " + to_string(treeSum[0]) + "\n";
		}
		else if (find[i] == 'B')
		{
			set(flag, treeL, treeM, treeR, treeSum, 0, 0, n, left[i] - min, left[i] - min + length[i] + 1, 1);
			str += to_string(treeM[0]) + " " + to_string(treeSum[0]) + "\n";
		}
		//for (int i = 0; i < 4 * n; i++)
		//{
		//	cout << i << " " << treeL[i] << " " << treeM[i] << " " << treeR[i] << " " << treeSum[i] << "\n";
		//}
	}
	cout << str;
}
