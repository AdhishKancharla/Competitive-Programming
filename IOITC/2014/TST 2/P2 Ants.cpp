/*
Author - Adhish Kancharla (ak2006)
Problem Name - 2014 TST 2 : Ants

Tags - Matrix Exponentiation DP

Idea -
1) First solve the 2 CSES problems from here - https://usaco.guide/plat/mat-exp?lang=cpp (after watching the Errichto videos linked in the guide)
2) Its easy to solve 30 points first using standard matrix exponentiation
3) Key Idea for 100 points (credits to https://codeforces.com/profile/gaddopur_coder (Aman Singh) for giving the idea)

    Let g1 = bin_expo(g1,steps Per Second) because this represents the move of the ant in 1 second (the ant has to travel EXACTLY these many steps in 1 second)
    Now introduce SELF LOOPS in g1 by doing g1[i][i] = max(0,g1[i][i]) for i = 0 to N - 1
    This allows us to stop before TIME LIMIT is reached i.e - if the optimal movement consisted of repeating the ants move for X seconds
    then we could just use the SELF LOOP at the end node for the remaining TIME LIMIT - X seconds

    Hence just do bin_expo(g1,TIME LIMIT)

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
ll ans = -inf,x,y;
vvl mult(vvl&a,vvl&b)
{
    int A = (int)a.size(),B = (int)a[0].size(),C = (int)b[0].size();
    vvl mat(A,vl(C,-inf));
    for (int i = 0;i<A;i++)
        for (int j = 0;j<C;j++)
            for (int k = 0;k<B;k++)
                mat[i][k] = max(mat[i][k],(a[i][j] > -inf && b[j][k] > -inf ? a[i][j] + b[j][k] : -inf));
    return mat;
}
vvl bin_expo(vvl g,ll power)
{
    vvl ret = g;
    power--;
    while (power > 0){
        if (power & 1)ret = mult(ret,g);
        g = mult(g,g);
        power /= 2;
    }
    ans = max(ans,ret[0][1]);
    return ret;
}
int main()
{
    ll n;
    cin>>n>>x>>y;
    vvl g(n,vl(n));
    for (int i = 0;i<n;i++){
        for (int j = 0;j<n;j++){
            cin>>g[i][j];
            if (g[i][j] == -999)g[i][j] = -inf;
        }
    }


    g = bin_expo(g, x);
    for(int i = 0; i < n; i++)
        g[i][i] = max(0LL, g[i][i]);

    bin_expo(g, y);
    if (ans > -inf)cout<<ans;
    else cout<<"IMPOSSIBLE";
    return 0;
}
