/*
Author - Adhish Kancharla(ak2006)
Problem Name - IOI 2010 Day 1 P3 - Quality of Living
Tags - Binary Search, 2D Prefix Sums
Submit here - https://oj.uz/problem/view/IOI10_quality
Same problem can be solved here also - https://atcoder.jp/contests/abc203/tasks/abc203_d
Idea - 
1) Binary search on the answer
2) Replace every cell in the grid with 1,-1 or 0 (1 if the # > mid, 0 if # = mid and -1 if # < mid)
3) Now we just need to find a subrectangle of size H by W with a sum == 0 since this means that there are equal # of 1's and -1's
4) Update the binary search invariant accordingly 
*/
#include "quality.h"
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vb = vector<bool>;
using vvb = vector<vb>;
using vi = vector<int>;
using vvi = vector<vi>;
using vl = vector<ll>;
using vvl = vector<vl>;
using vc = vector<char>;
using vvc = vector<vc>;
using vs = vector<string>;
const ll mod = 1e9 + 7,inf = 1e18;
#define pb push_back
#define fast ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

bool is(int n,int m,int mid,int g[3001][3001],int h,int w)
{
    vvi p(n + 1,vi(m + 1));
    for (int i = 1;i<=n;i++)for (int j = 1;j<=m;j++){
        p[i][j] = p[i - 1][j] + p[i][j - 1] - p[i - 1][j - 1];
        if (g[i - 1][j - 1] > mid)p[i][j]++;
        else if (g[i - 1][j - 1] < mid)p[i][j]--;
    }
    for (int i = 1;i + h - 1 <=n;i++)
        for (int j = 1;j + w - 1 <= m;j++){
            if (p[i + h - 1][j + w - 1] - p[i + h - 1][j - 1] - p[i - 1][j + w - 1] + p[i - 1][j - 1] <= 0){
                return true;
            }
        }
    return false;
}

int rectangle(int n, int m, int h, int w, int Q[3001][3001]) {
	int l = 0,r = 1e9,ans = 1e9;
    while (l <= r){
        int mid = (l + r)/2;
        if (is(n,m,mid,Q,h,w)){ans = mid;r = mid - 1;}
        else l = mid + 1;
    }
    return ans;
}
