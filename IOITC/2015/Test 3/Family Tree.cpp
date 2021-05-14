/*
Author - Adhish Kancharla (ak2006)
Problem Name - IOITC 2015 Final Test 3 Family Tree
Tags - Binary Lifting, Euler Tour Traversal
Idea -
1) Compute the standard depth, subtree size (although not needed) and in out times (Euler Tour Way 1) for each of the trees
2) Then do binary lifting pre processing to find kth ancestor of a node in O(Log N) - actually do this in the DFS only
3) Do BFS to compute the nodes per level in the trees
4) Find kth ancestor of the node in the query and then use lower bound upper bound to find all the nodes in the ancestor's subtree at depth of u
More Details Here - https://www.commonlounge.com/discussion/3e8329edb1404d8382eafe086cb51c46/main
Same Problem Available to Submit Here - https://codeforces.com/contest/208/problem/E
Note -
1) The given graph is a forest of many trees
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

int t = 1;
int n = 1e6 + 5;
vvi adj(n),up(n,vi(21)),lev(n);
vi dep(n),sub(n),in(n),out(n),par(n),et;
void dfs(int u,int p)
{
    in[u] = t++;
    et.pb(u);
    sub[u] = 1;
    up[u][0] = p;

    for (int i = 1;i<=20;i++)up[u][i] = up[up[u][i - 1]][i - 1];

    for (int v:adj[u]){
        if (v == p)continue;
        dep[v] = dep[u] + 1;
        dfs(v,u);
        sub[u] += sub[v];
    }

    out[u] = t - 1;
}
int anc(int u,int d,vvi&up)
{
    for (int i = 20;i>=0;i--){
        if (d & (1<<i))u = up[u][i];
    }
    return u;
}
int main()
{
    fast;
    int q;
    cin>>n;

    for (int i = 1;i<=n;i++){
        int p;
        cin>>p;
        if (p != 0)adj[p].pb(i);
        par[i] = p;
    }

    for (int i = 1;i<=n;i++)
        if (par[i] == 0)dfs(i,0);


    queue<int>qu;

    for (int i = 1;i<=n;i++)if (dep[i] == 0)qu.push(i);
    while (!qu.empty()){
        int c = qu.front();
        qu.pop();
        lev[dep[c]].pb(in[c]);
        for (int v:adj[c]){
            if (dep[v] < dep[c])continue;
            qu.push(v);
        }
    }
    cin>>q;
    while (q--){
        int u,d;
        cin>>u>>d;
        if (dep[u] < d){cout<<0<<'\n';continue;}
        int p = anc(u,d,up);

        int posStart = lower_bound(lev[dep[u]].begin(),lev[dep[u]].end(),in[p]) - lev[dep[u]].begin();
        int posEnd = upper_bound(lev[dep[u]].begin(),lev[dep[u]].end(),out[p]) - lev[dep[u]].begin();

        cout<<posEnd - posStart - 1<<'\n';
    }
    return 0;
}
/*
Sample TestCase -
17
0
1
2
3
3
2
6
6
6
2
10
1
12
13
13
13
12
1
*/
