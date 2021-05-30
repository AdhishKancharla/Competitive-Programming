/*
Author - Adhish Kancharla(ak2006)
Problem Name - CEOI 2012 Day 2 P1 - Highways
Tags - Interactive Problem, Geometry
Submit Here - https://oj.uz/problem/view/CEOI12_highway
Idea - 
1) This problem is a nice introductory problem on thinking about interactive problems (think about what queries you should ask and what is invariant)
2) The first line will always be (1,2) - now think how do we find 2 points which are not on the line from 1 to 2 (in N/2 + 2 queries)
3) Just ask isOnLine(1,i,i + 1) and if we get a value of false then we know one out of i and i + 1 will not be on the line from 1 to 2
4) Hence just ask isOnLine(1,2,i) and if we get a true then we know i + 1 is on line 2 and if we get a false then we know i is on line 2
5) Thus we take only N/2 + 2 queries (+2 for the 2 extra isOnLine(1,2,i) query)
6) There is one twist (the above steps only get you 40% - in our loop we run only till i < n but if i = n => i will be on the line 2 if there are < 2 points so far on line 2
and if there are >= 2 points on line 2 then we ignore the nth point)
*/
#include <bits/stdc++.h>
#include "office.h"
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
using vs = vector<string>;
const ll mod = 1e9 + 7,inf = 1e18;
#define pb push_back
#define fast ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
void setIO()
{
    fast;
    #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("outut.txt","w",stdout);
    #endif
}
int main()
{
    //setIO();
    vi l2;
    int n = GetN();
    for (int i = 2;i<n;i+=2){
        if (l2.size() == 2)break;
        if (!isOnLine(1,i,i + 1)){
            if (isOnLine(1,2,i))l2.pb(i + 1);
            else l2.pb(i);
        }
    }
    if (l2.size() != 2){
        assert(l2.size() == 1);
        assert(!isOnLine(1,2,n));
        l2.pb(n);
    }
    Answer(1,2,l2[0],l2[1]);
    return 0;
}
