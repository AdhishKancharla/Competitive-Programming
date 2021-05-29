/*
Author - Adhish Kancharla(ak2006)
Problem Name - 2018 Day 2 P3 - Paths
Submit Here - https://oj.uz/problem/view/BOI18_paths
Tags - DP with Bitmasks
Idea - Simple problem on DP with bitmasks
1) The low constraint on k should give you an idea of a 1<<k or k! factor in the time complexity of the solution
2) Let dp[u][mask] be the # of paths which start at u and currently have the set represented by mask colors visited
3) Hence dp[u][mask] is initally 1 and we have the recurrence dp[u][mask] = sum of dp[v][mask | (1<< col[u])] 
4) The answer is just the sum of dp[u][0] (because we are starting at u without any colors) and we actually need to sum dp[u][0] - 1 BECAUSE we are counting the case where 
the PATH IS OF LENGTH 1 which is not allowed so just subtract out that 1
5) Implementation Detail: If you are using TOP DOWN DP (like I did) DONT FORGET to use a visited array along with the dp array to avoid revisiting already computed states
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
void setIO()
{
	fast;
}
int n = 3e5 + 5,m = 3e5 + 5,k = 5;
vvi adj(n);
vi col(n);
vvl dp(n,vl(1<<k));
vvb vis(n,vb(1<<k));
void dfs(int u,int mask)
{
	int mask2 = mask |  (1<<col[u]);
	dp[u][mask] = 1;
	vis[u][mask] = 1;
	for (int v:adj[u]){
		if ((mask2 & (1<<col[v])))continue;
		if (!vis[v][mask2])dfs(v,mask2);
		dp[u][mask] += dp[v][mask2];
	}
}
int main()
{
	setIO();
	cin>>n>>m>>k;
	for (int i = 1;i<=n;i++){cin>>col[i];col[i]--;}
	while (m--){
		int u,v;
		cin>>u>>v;
		adj[u].pb(v),adj[v].pb(u);
	}
	ll ans = 0;
	for (int i = 1;i<=n;i++){
		for (int mask = 0;mask < (1<<k);mask++){
			if (mask & (1<<col[i]))continue;
			dfs(i,mask);
			if (mask == 0)ans += dp[i][0] - 1;
		}
	}
	cout<<ans;
	return 0;
}
