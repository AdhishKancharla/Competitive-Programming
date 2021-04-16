/*
Author - Adhish Kancharla (ak2006)
Problem Name - IOITC 2012 Test 2 - Here there be dragons

Hint - Sort by x and then do the obviouse DP
Ideas -
1) dp[n][k] = min distance to travel in order to kill K dragons, considering the first n dragons
2) Compute dp[n][k] naively in O(n * k * n)
3) I have not proved why the above solution work - ( I got a proof by AC :) )

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
    ll r,c,k,d,out = inf;
    cin>>r>>c>>k>>d;
    vvl p(d + 1,vl(2)),dp(d + 1,vl(k + 1,inf));
    for (int i = 1;i<=d;i++)cin>>p[i][0]>>p[i][1];
    sort(p.begin() + 1,p.end());
    dp[0][0] = 0;
    for (int i = 1;i<=d;i++){
        for (int j = 1;j<=k;j++)
            for (int x = 0;x<=i - 1;x++)
                dp[i][j] = min(dp[i][j],dp[x][j - 1] + abs(p[i][0] - p[x][0]) + abs(p[i][1] - p[x][1]));
        out = min(out,dp[i][k]);
    }
    cout<<out;
    return 0;
}
