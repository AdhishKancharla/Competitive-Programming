/*
Author - Adhish Kancharla (ak2006)
Problem Name - IOITC 2008 Final Test 1 P3 : Petrol Tank

Tags - MST, Binary Lifting, LCA
Idea -
1) Find a minimum spanning tree of the graph
2) Find the minimum edge on the path between the 2 nodes in the query by using Binary Lifting technique (on the MST) in LogN time

*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vb = vector<bool>;
using vvb = vector<vb>;
using vi = vector<int>;
using vvi = vector<vi>;
using vvvi = vector<vvi>;
using vl = vector<ll>;
using vvl = vector<vl>;
using vc = vector<char>;
using vvc = vector<vc>;
const ll mod = 1e9 + 7,inf = 1e18;
#define pb push_back
#define fast ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

int n = 1e5 + 5,m,cur = 0;
vvi el;
vvvi adj(n);
vvi dp(n,vi(20));
vvi up(n,vi(20));
vi in(n),out(n),level(n);
struct dsu
{
    vi p;
    dsu()
    {
        p.assign(n,0);
        for (int i = 0;i<=n;i++)p[i] = i;
    }
    int Find(int a)
    {
        if (p[a] == a)return a;
        return p[a] = Find(p[a]);
    }
    void Unite(int a,int b)
    {
        a = Find(a),b = Find(b);
        if (a == b)return;
        p[b] = a;
    }
};
bool cmp(vi&a,vi&b)
{
    return a[2] < b[2];
}
bool is_anc(int u,int v)
{
    return in[u] <= in[v] && out[u] >= out[v];
}
int lca(int u,int v)
{
    if (is_anc(u,v))return u;
    if (is_anc(v,u))return v;
    if (in[v] < in[u])swap(u,v);
    for (int i = 19;i>=0;i--){
        if (!is_anc(up[v][i],u))v = up[v][i];
    }
    return up[v][0];
}
void dfs(int i,int p,int w)
{
    in[i] = ++cur;
    level[i] = level[p] + 1;
    dp[i][0] = w;
    up[i][0] = p;
    for (int j = 1;j<=19;j++){
        up[i][j] = up[up[i][j - 1]][j - 1];
        dp[i][j] = max(dp[i][j - 1],dp[up[i][j - 1]][j - 1]);
    }
    for (auto e:adj[i]){
        int curw = e[1],v = e[0];
        if (v == p)continue;
        dfs(v,i,curw);
    }
    out[i] = ++cur;
}
void inp()
{
    cin>>n>>m;
    for (int i = 0;i<m;i++){
       int u,v,w;
       cin>>u>>v>>w;
       el.pb({u,v,w});
    }
    sort(el.begin(),el.end(),cmp);
    dsu val;
    for (vi e:el){
        int u = e[0],v = e[1],w = e[2];
        if (val.Find(u) != val.Find(v)){val.Unite(u,v);adj[u].pb({v,w}),adj[v].pb({u,w});}
    }
    dfs(1,1,0);
}
int maxEdge(int u,int v)
{
    int jump = level[u] - level[v];
    int ret = 0;
    for (int i = 19;i>=0;i--){
        //cout<<u<<endl;
        if (jump & (1<<i)){
            ret = max(ret,dp[u][i]);
            u = up[u][i];
        }
    }
    return ret;
}
void query()
{
    int q;
    cin>>q;
    while (q--){
        int s,d;
        cin>>s>>d;
        int LCA = lca(s,d);
        cout<<max(maxEdge(s,LCA),maxEdge(d,LCA))<<'\n';
    }
}
int main()
{
    inp();
    query();
    return 0;
}
