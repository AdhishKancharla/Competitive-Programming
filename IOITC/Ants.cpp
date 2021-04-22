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
void bin_expo(vvl g,ll power)
{
    if (power > y * x)return;
    vvl ret = g;
    power--;
    while (power > 0){
        if (power & 1)ret = mult(ret,g);
        g = mult(g,g);
        power /= 2;
    }
    cout<<ret[0][1]<<endl;
    ans = max(ans,ret[0][1]);
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
    for (int t = 1;t<=y;t++)bin_expo(g,t * x);
    if (ans > -inf)cout<<ans;
    else cout<<"IMPOSSIBLE";
    return 0;
}
/*
4
7 9
-999 1 1 -999
-999 -999 -999 -999
-999 -999 -999 1
1 -999 -999 -999
*/
