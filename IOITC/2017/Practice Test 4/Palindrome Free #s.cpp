/*
Author - Adhish Kancharla (ak2006)
Problem Name - IOITC 2017 Practice Test 4 Palindrome Free Numbers
Same problem - BOI 2013 Day 1 P2

Tags - Digit DP
Idea -
1) DP state is position, last digit,second last digit,whether or not # is less than a so far,whether or not the number is > 0
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
ll dp[20][11][11][2][2];
ll solve(vi&a,int i,int l1,int l2,int tight,int started)
{
    if (dp[i][l1][l2][tight][started] != 0)return dp[i][l1][l2][tight][started];
    if (i == (int)a.size())return started == 1;
    if (tight){
        for (int j = 0;j<a[i];j++){
            if (l1 == j || l2 == j)continue;
            if (started || j != 0)dp[i][l1][l2][1][started] += solve(a,i + 1,j,l1,0,1);
            else dp[i][l1][l2][1][0] += solve(a,i + 1,10,l1,0,0);
        }
        if (l1 != a[i] && l2 != a[i]){
            if (started || a[i] != 0)dp[i][l1][l2][1][started] += solve(a,i + 1,a[i],l1,1,1);
            else dp[i][l1][l2][1][0] += solve(a,i + 1,10,l1,1,0);
        }
    }
    else{
        for (int j = 0;j<=9;j++){
            if (l1 == j || l2 == j)continue;
            if (started || j != 0)dp[i][l1][l2][0][started] += solve(a,i + 1,j,l1,0,1);
            else dp[i][l1][l2][0][0] += solve(a,i + 1,10,l1,0,0);
        }
    }
    return dp[i][l1][l2][tight][started];
}
int main()
{
    ll a,b;
    cin>>a>>b;
    if (b == 0){cout<<1;return 0;}
    vi diga,digb;
    a--;
    while (a > 0){diga.pb(a%10);a/=10;}
    while (b > 0){digb.pb(b%10);b/=10;}
    if (!diga.empty())reverse(diga.begin(),diga.end());
    reverse(digb.begin(),digb.end());
    ll ans = 0;
    if (!diga.empty())ans = solve(diga,0,10,10,1,0);
    memset(dp,0,sizeof(dp));
    ans = -ans + solve(digb,0,10,10,1,0);
    if (a + 1 == 0)ans++;
    cout<<ans;
    return 0;
}
