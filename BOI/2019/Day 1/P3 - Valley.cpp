/*
Author - Adhish Kancharla(ak2006)
Problem Name - BOI 2019 Day 1 P3 - Valley
Submit - https://oj.uz/problem/view/BOI19_valley
Tags - Tree DP, Euler Tour, Binary Lifting/Jumping
Solution:
Idea - Same as official solution (https://boi2019.eio.ee/wp-content/uploads/2019/05/valley.sol_.en-1.pdf)

1) Root the tree at the "s" vertex so that we can answer the reachibility queries easily
2) For each query, when we remove the edge (u,v) where u is the parent of v, all the vertices in the subtree of v are cutoff from the root and all other vertices
   can still reach the root
3) Hence use the Euler Tour Traversal to find in-out times and to check if "escape" is the answer just check if the node R is NOT a descendant of v (or v is NOT an ancestor of R)
4) Now for the main case where R is in the subtree of v - 
   Notice that dist(u,v) = dist(u) + dist(v) - 2 * dist(lca(u,v))
   Now to compute min(dist(R,ShopNode)) we need to find the LCA, hence let the lca be fixed = w
   Now we know that the answer will be the min value of dist(R) - 2 * dist(w) + dist(ShopNode) where ShopNode can be any node with a shop in the subtree of w (including u itself)
   Hence lets define Magic(w) to be the min value of dist(ShopNode) (since we want to minimize the whole expression above)
   Further lets increase Magic(w) by - 2 * dist(w) (after the initial Tree DP to compute Magic(w))
   This means Magic(w) = - 2 * dist(w) + dist(ShopNode)
   Hence we just need to find min(dist(R) + Magic(w)) for all w in the path from R to the node v
   = min(Magic(w)) + dist(R)
   Now if you know what Binary Jumping is, it should be obvious that computing the minimum value of Magic(w) in the path from R to v can be done easily using Binary Jumping
   If you dont know what it is, learn from here - https://usaco.guide/plat/bin-jump

Similar problems can be found there (https://usaco.guide/plat/bin-jump)
   

*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vl = vector<ll>;
using vvl = vector<vl>;
using vvvl = vector<vvl>;
using vi = vector<int>;
using vvi = vector<vi>;
using vb = vector<bool>;
#define fast ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define pb push_back
const ll inf = 1e15;
void setIO()
{
	fast;
	#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	#endif
}
int n = 1e5 + 5,s,q,root;
vi in(n),out(n),num(n);
vl magic(n,inf),dist(n);
vvl anc(n,vl(21)),dp(n,vl(21));
vvvl adj(n);
vb shop(n);
int t;
void dfs(int u,int p,ll wt)
{
	if (p != -1)dist[u] = dist[p] + wt,num[u] = num[p] + 1;
	in[u] = t++;
	if (shop[u])magic[u] = dist[u];

	for (auto x:adj[u]){
		int v = x[0];
		ll w = x[1];
		if (v == p)continue;
		dfs(v,u,w);
		magic[u] = min(magic[u],magic[v]);
	}
	
	out[u] = t++;
}
bool is_ancestor(int u,int v)
{
	return in[u] <= in[v] && out[u] >= out[v];
}
void dfs2(int u,int p)
{
	anc[u][0] = p;
	dp[u][0] = magic[u];
	for (int i = 1;i<=20;i++){
		anc[u][i] = anc[anc[u][i - 1]][i - 1];
		dp[u][i] = min(dp[u][i - 1],dp[anc[u][i - 1]][i - 1]);
	}
	for (auto x:adj[u]){
		int v = x[0];
		if (v == p)continue;
		dfs2(v,u);
	}
}
int main()
{
	setIO();	
	cin>>n>>s>>q>>root;
	vvi edges;
	for (int i = 1;i<n;i++){
		int u,v,w;
		cin>>u>>v>>w;
		adj[u].pb({v,w});
		adj[v].pb({u,w});
		edges.pb({u,v});
	}
	for (int i = 1;i<=s;i++){
		int x;
		cin>>x;
		shop[x] = 1;
	}
	dfs(root,-1,0);
	for (int i = 1;i<=n;i++)if (magic[i] < inf)magic[i] += -2 * dist[i];
	dfs2(root,root);
	while (q--){
		int pos,u;
		cin>>pos>>u;
		int child = edges[pos - 1][0],par = edges[pos - 1][1];
		if (in[child] < in[par])swap(child,par);
		if (!is_ancestor(child,u))cout<<"escaped"<<'\n';
		else {
			//now find min of magic[v] for all v on the path from u to child
			int distance = - num[child] + num[u] + 1;
			int node = u;
			ll val = inf;
			for (int i = 0;i<=20;i++){
				if (distance&(1<<i)){
					val = min(val,dp[u][i]);
					u = anc[u][i];
				}
			}
			if (val >= inf)cout<<"oo"<<'\n';
			else cout<<dist[node] + val<<'\n';
		}
	}
	return 0;
}
