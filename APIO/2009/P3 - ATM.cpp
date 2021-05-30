/*
Author - Adhish Kancharla(ak2006)
Problem Name - APIO 2009 P3 - ATM
Tags - SCC DAG, DP 
Idea - The official solution explains the idea really well and concisely (attached in this folde)
Note: This code gets only 40 points due to MLE
*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using vl = vector<ll>;
using vvl = vector<vl>;
using vb = vector<bool>;
using vvb = vector<vb>;
using vc = vector<char>;
using vvc = vector<vc>;
#define fast ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define pb push_back

int n = 5e5 + 5,m,cur,start,q;
stack<int>s;
vvi adj(n),radj(n),g(n);
vi cmp(n);
vi money(n),vals(n),dp(n);
vb vis(n);
void setIO()
{
    fast;
    #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    #endif
}
void inp()
{
    cin>>n>>m;
    while (m--){
        int u,v;
        cin>>u>>v;
        adj[u].pb(v);
        radj[v].pb(u);
    }
    for (int i = 1;i<=n;i++)cin>>money[i];
}
void dfs(int u)
{
    vis[u] = 1;
    for (int v:adj[u])if (!vis[v])
        dfs(v);
    s.push(u);
}
void dfs2(int u)
{
    cmp[u] = cur;
    vis[u] = 1;
    for (int v:radj[u])if (!vis[v])
        dfs2(v);
}
void SCC()
{
    for (int i = 1;i<=n;i++)if (!vis[i])
        dfs(i);
     for (int i = 1;i<=n;i++)vis[i] = 0;
     while (!s.empty()){
         int c = s.top();
         if (!vis[c])
             ++cur,dfs2(c);
         s.pop();
     }
    for (int i = 1;i<=n;i++){
        vis[i] = 0;
        for (int v:adj[i])if (cmp[i] != cmp[v])
            g[cmp[i]].pb(cmp[v]);
    }
    for (int i = 1;i<=n;i++)vals[cmp[i]] += money[i];
    for (int i = 1;i<=n;i++)dp[cmp[i]] = vals[cmp[i]];

}
void solve(int u)
{
    vis[u] = 1;
    for (int v:g[u]){
        if (!vis[v]){
            dp[v] = max(dp[v],dp[u] + vals[v]);
            solve(v);
        }
    }
}
void computeDP()
{
    cin>>start>>q;
    solve(cmp[start]);
    int ans = 0;
    while (q--){
        int x;
        cin>>x;
        ans = max(ans,dp[cmp[x]]);
    }
    cout<<ans;
}
int main()
{
    setIO();
    inp();
    SCC();
    computeDP();
    return 0;
}
