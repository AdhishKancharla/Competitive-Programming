/*
Author - Adhish Kancharla(ak2006)
Problem Name - 2011 Day 1 P1 - Growing Trees
Submit Here - https://cses.fi/100/list/ (after agreeing to upsolve the contest)
Tags - BIT/Segment Tree Data Structure, Binary Search
Idea - See the official solution which explains the idea really well
Implementation - Dont use a segment tree because a binary indexed tree/fenwick tree is much easier to code and sufficient for this problem since we are doing RUPQ
                 (Range Updates and Point Queries)
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
#define lc 2 * no
#define rc 2 * no + 1
int n = 1e5 + 5,q;
vi bit(n);
void update(int i,int inc)
{
    i++;
    for (;i<=n;i+=i&(-i))bit[i] += inc;
}
int sum(int i)
{
    i++;
    int ret = 0;
    for (;i>0;i-=i&(-i))ret += bit[i];
    return ret;
}
int lowerBound(int h)
{
    int l = 0,r = n - 1;
    while (l < r){
        int mid = (l + r)/2;
        if (sum(mid) >= h)r = mid;
        else l = mid + 1;
    }
    return l;
}
int Lower2(int h)
{
    int l = 0,r = n - 1;
    while (l < r){
        int mid = (l + r)/2;
        if (sum(mid + 1) <= h)l = mid + 1;
        else r = mid;
    }
    return l;
}
int32_t main()
{
    fast;
    cin>>n>>q;
    vi a(n + 1);
    for (int i = 1;i<=n ;i++)cin>>a[i];
    sort(a.begin() + 1,a.end());

    for (int i = 1;i<=n;i++)update(i - 1,a[i] - a[i - 1]);

    while (q--){
        char x;
        cin>>x;
        if (x == 'F'){
            int c,h;
            cin>>c>>h;

            if (sum(n - 1) < h)continue;

            int first = lowerBound(h);//first index to be updated

            int Last = min(n - 1,first + c - 1);//last index to be updated

            if (first + c - 1 >= n)c = n - first;

            int val = sum(Last);//height of the last index to be updated

            int pos1 = lowerBound(val),pos2 = Lower2(val);

            int rem = c - (pos1 - first);

            update(first,1);
            update(pos1,-1);
            update(pos2 - rem + 1,1);
            update(pos2 + 1,-1);


        }
        else{
            int mn,mx;
            cin>>mn>>mx;
            int L1 = lowerBound(mn),L2 = Lower2(mx);
            if (sum(0) > mx or sum(n - 1) < mn)cout<<0<<'\n';
            else cout<<L2 - L1 + 1<<'\n';
        }
    }
    return 0;
}
