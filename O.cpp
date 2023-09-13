#include <iostream>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include<string.h>
#include <string>
using namespace std;

int p(int i)
{
	return (i & (i + 1)) - 1;
}

int f(int i)
{
	return i | (i + 1);
}

void add(vector <int>& arr, int n, int x, int y, int z, int plus)
{
	int k = z;
	while (k < n)
	{
		int j = y;
		while (j < n)
		{
			int i = x;
			while (i < n)
			{
				// arr[i][j][k] += plus;
				arr[i * n * n + j * n + k] += plus;
				i = f(i);
			}
			j = f(j);
		}
		k = f(k);
	}
}
int prefix(vector <int> & arr, int n, int x, int y, int z)
{
	int sum = 0;
	int k = z;
	while (k >= 0)
	{
		int j = y;
		while (j >= 0)
		{
			int i = x;
			while (i >= 0)
			{
				sum += arr[i * n * n + j * n + k];
				i = p(i);
			}
			j = p(j);
		}
		k = p(k);
	}
	return sum;
}

int getSum(vector <int>& arr, int n, int x1, int y1, int z1, int x2, int y2, int z2)
{
	x1--;
	y1--;
	z1--;
	int sum = prefix(arr, n, x2, y2, z2) - prefix(arr, n, x1, y2, z2) -prefix(arr, n, x2, y1, z2) + prefix(arr, n, x1, y1, z2) - prefix(arr, n, x2, y2, z1) + prefix(arr, n, x2, y1, z1) + prefix(arr, n, x1, y2, z1) - prefix(arr, n, x1, y1, z1);
	return sum;
}


int main()
{
	int n;
	cin >> n;
	vector <int> arr(n * n * n);
	
	int a;
	string str;
	while (true)
	{
		cin >> a;
		if (a == 1)
		{
			int x, y, z, p;
			cin >> x >> y >> z >> p;
			add(arr, n, x, y, z, p);
		}
		else if (a == 2)
		{
			int x1, y1, z1, x2, y2, z2;
			cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
			str += to_string(getSum(arr, n, x1, y1, z1, x2, y2, z2)) + "\n";
		} 
		else if (a == 3)
		{
			break;
		}
	}
	cout << str;
}
