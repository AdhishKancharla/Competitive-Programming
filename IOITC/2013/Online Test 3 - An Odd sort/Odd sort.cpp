/*
Author - Adhish Kancharla (ak2006)
Problem Name - IOITC 2013 Online Test 3 : An Odd Sort

Solution Code Idea - https://github.com/keshav57/ioi-training/blob/master/IOITC/2013/OddSort/OddSort.cpp

Tags - DP , Modification of LIS

Explanation -
Initially move all elements to their correct positions in the sorted array - this is an upper bound on the cost required to sort the array (i.e the sum of
all elements in the array is definitely enough to sort the array)
But we can do better!
The key idea is we don not need to resort a sorted subsequence , so find the Maximum sum of an increasing subsequence
Note that this problem is just a variation of the LIS but N^2 works (We do not need to find an N log N solution although it exists)
Also note that we do not need a strictly increasing subsequence - non decreasing is fine
*/
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
const ll mod = 1e9 + 7,inf = 1e18;
#define pb push_back
#define fast ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
int main()
{
    int n;
    cin>>n;
    vi a(n),dp(n);
    int sum = 0;
    for (int i = 0;i<n;i++)cin>>a[i],dp[i] = a[i],sum += a[i];
    int max_inc = 0;
    for (int i = 0;i<n;i++){
        for (int j = i - 1;j>=0;j--)
            if (a[i] >= a[j])dp[i] = max(dp[i],dp[j] + a[i]);
        max_inc = max(max_inc,dp[i]);
    }
    cout<<sum - max_inc;
    return 0;
}
