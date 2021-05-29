/*
Author - Adhish Kancharla(ak2006)
Problem Name - 2011 APIO P2 - Backup
Tags - DP for 50 points, Greedy for full
Solution Link - http://apio-olympiad.org/2007/solutions.pdf, https://www.iarcs.org.in/inoi/online-study-material/problems/backup-soln.php#solution
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
    fast;
    int n,k;
    cin>>n>>k;
    vl a(n + 5);
    for (int i = 1;i<=n;i++)cin>>a[i];
    priority_queue<vl>q;
    vi next(n + 5),prev(n + 5);
    vl dist(n + 5);

    for (int i = 1;i<=n;i++)dist[i] = a[i] - a[i - 1];
    for (int i = 2;i<=n;i++)q.push({-dist[i],i - 1,i});
    for (int i = 1;i<=n;i++)next[i] = i + 1,prev[i] = i - 1;
    vb vis(n + 5);
    ll ans = 0;
    int cnt = 0;
    while (cnt < k && !q.empty()){
        ll wt = -q.top()[0];
        int i = q.top()[1],j = q.top()[2];

        q.pop();

        if (vis[i] || vis[j])continue;

        ans += wt;
        cnt++;
        vis[i] = vis[j] = 1;
        int nextj = next[j],previ = prev[i];

        next[previ] = nextj,prev[nextj] = previ;

        dist[nextj] += dist[i] - dist[j];
        if (previ >= 1 && nextj <= n && !vis[previ] && !vis[nextj])q.push({-dist[nextj],previ,nextj});

    }
    cout<<ans;
    //}
    return 0;
}
