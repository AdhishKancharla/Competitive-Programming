/*
Author - Adhish Kancharla (ak2006)
Problem Name - 2013 Test 4 : Ancestors Sum

Tags - Euler Tour Traversal on the tree, BIT
Hints - Solve https://cses.fi/problemset/task/1138/ and refer to https://usaco.guide/gold/tree-euler?lang=cpp (the CSES tree problem and the USACO Guide Gold Module on ETT)

*/
#include <bits/stdc++.h>
using namespace std;
#define int long long
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

int maxN = 4e5 + 5;
int n = 4e5 + 5,q,cur;
vi in(n),out(n);
vvi adj(n);
struct BIT
{
    vi bit;
    BIT(int _n)
    {
        bit.assign(4e5 + 6,0);
    }
    void update(int i,int inc)
    {
        for (;i<=maxN;i += i & (-i))bit[i] += inc;
    }
    int sum(int i)
    {
        int ret = 0;
        for (;i>0;i-=i&(-i))ret += bit[i];
        return ret;
    }
};
void dfs(int i,int p)
{
    in[i] = ++cur;
    for (int c:adj[i]){
        if (c == p)continue;
        dfs(c,i);
    }
    out[i] = ++cur;
}
int32_t main()
{
    fast;
    cin>>n;
    for (int i = 0;i<n - 1;i++){
        int u,v;
        cin>>u>>v;
        adj[u].pb(v),adj[v].pb(u);
    }
    BIT val(n);
    dfs(0,-1);
    cin>>q;
    while (q--){
        char t;
        cin>>t;
        if (t == 'A'){
            int u,x;
            cin>>u>>x;
            val.update(in[u],x),val.update(out[u],-x);
        }
        else{
            int u;
            cin>>u;
            cout<<val.sum(in[u])<<'\n';
        }
    }
    return 0;
}
