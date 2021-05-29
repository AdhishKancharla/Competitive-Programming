/*
Author - Adhish Kancharla(ak2006)
Problem Name - IOI 2015 Day 1 P1 - Boxes
Submit Here - https://dmoj.ca/problem/ioi15p1io or Here - https://oj.uz/problem/view/IOI15_boxes
Tags - Greedy, DP, Prefix and Suffix Sums
Idea - Same as the official Solution - 

1) Make the observations as given in the offical solution, then to compute l[i] and r[i] use DP
2) l[i] = 2 * pos[i] + l[i - k] and r[i] = 2 * (L - pos[i]) + r[i + k]
3) Then use the same idea as proof 1 : take min(l[i] + r[i + 1]) and min(l[i - 1] + r[i + k] + L) 
4) Note here l[i] is min cost to deliver boxes 0 to i - 1 and r[i] is min cost to deliver boxes i to n - 1

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
	#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	#endif
}
int main()
{
	setIO();
	ll n,k,L;
	cin>>n>>k>>L;
	vl pos(n);
	for (int i = 0;i<n;i++)cin>>pos[i];
	vl pref(n),suf(n);
	for (int i = 0;i<n;i++)pref[i] = 1ll * 2 * pos[i] + (i >= k ? pref[i - k] : 0);
	for (int i = n - 1;i>=0;i--)suf[i] = 1ll * 2 * (L - pos[i]) + (i + k < n ? suf[i + k] : 0);
	ll ans = min(pref[n - 1],suf[0]);
	for (int i = 0;i<n - 1;i++)ans = min(ans,pref[i] + suf[i + 1]);
	for (int i = 0;i<n;i++)
		ans = min(ans,(i >= 1 ? pref[i - 1] : 0) + (i + k < n ? suf[i + k] : 0) + L);
	cout<<ans;
	return 0;
}
