/*
Author - Adhish Kancharla (ak2006)
Problem Name - 2011 Day 1 P2 : Ice Cream
Tags - Cake Walk

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
int main()
{
    int n,m;
    cin>>n>>m;
    vvi is(n + 1,vi(n + 1,1));
    while (m--){
        int u,v;
        cin>>u>>v;
        is[u][v] = is[v][u] = 0;
    }
    int cnt = 0;
    for (int i = 1;i<=n - 2;i++){
        for (int j = i + 1;j<=n - 1;j++){
            for (int k = j + 1;k<=n;k++){
                if (is[i][j] && is[i][k] && is[j][k])cnt++;
            }
        }
    }
    cout<<cnt;
    return 0;
}
