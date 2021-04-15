/*
Author - Adhish Kancharla (ak2006)
Problem Name - 2015 Test 1 : Islands and Bridges

Tags - Sorting, DSU
Hints - https://www.commonlounge.com/discussion/a7e92cb3bb654cb4a7b21c71132c3e5b/main
Idea -
1) Sort edges in decreasing order of their weights and process them as follows -
2) For the edge u to v with weight w, this edge will be the minimum cost edge for all nodes in u's current component
   to v's current component (Think a bit why this is true)
   So just add size[u] * sz[v] * w to the answer

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
struct dsu
{
    vi p;
    vl sz;
    ll tot = 0;
    dsu(int n)
    {
        p.assign(n + 1,0);
        sz.assign(n + 1,1);
        for (int i = 1;i<=n;i++)p[i] = i;
    }
    int Find(int a)
    {
        if (p[a] == a)return a;
        return p[a] = Find(p[a]);
    }
    void Unite(int a,int b,ll w)
    {
        a = Find(a),b = Find(b);
        if (a == b)return;
        if (sz[a] < sz[b])swap(a,b);
        p[b] = a;
        tot += sz[b] * sz[a] * w;
        sz[a] += sz[b];
    }
};
bool cmp(vl&a,vl&b)
{
    return a[2] > b[2];
}
int main()
{
    int n;
    cin>>n;
    dsu val(n + 1);
    vvl el(n - 1,vl(3));
    for (int i = 0;i<n - 1;i++)cin>>el[i][0]>>el[i][1]>>el[i][2];
    sort(el.begin(),el.end(),cmp);
    for (auto it:el){
        int u = it[0],v = it[1];
        ll w = it[2];
        val.Unite(u,v,w);
    }
    cout<<val.tot;
    return 0;
}
