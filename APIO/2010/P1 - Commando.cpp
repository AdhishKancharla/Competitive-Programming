/*
Author - Adhish Kancharla(ak2006)
Problem Name - 2010 APIO P1 - Commando
Tags - Convex Hull Trick (Dynamic Programming), Prefix Sums
Official Solution Link - http://apio-olympiad.org/2010/solutions.pdf
Use either Solution 3 in the link above or speed up Solution 2 using the CHT Data Structure
*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using vb = vector<bool>;
using vvb = vector<vb>;
using vi = vector<int>;
using vvi = vector<vi>;
using vl = vector<ll>;
using vvl = vector<vl>;
using vc = vector<char>;
using vvc = vector<vc>;
const ll mod = 1e9 + 7,inf = 1e18;
const ld eps = 1e-9;
#define pb push_back
#define fast ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

struct line
{
    ll m,b;
    ld meet(line other){
        return (ld)(other.b - b) / (ld)(m - other.m);
    }
};
struct CHT
{
    deque<line>hull;
    deque<ld>intersections;
    void add_line(line x)
    {
        if (hull.empty()){hull.pb(x);return;}
        if ((int)hull.size() == 1){intersections.pb(hull.back().meet(x));hull.pb(x);return;}
        while ((int)hull.size() >= 2){
            line l2 = hull.back();
            hull.pop_back();
            line l1 = hull.back();
            if (l1.meet(x) - l1.meet(l2) > eps){
                hull.pb(l2);
                break;
            }
            else intersections.pop_back();
        }
        intersections.pb(hull.back().meet(x));
        hull.pb(x);
    }
    ll eval(line l,ll x)
    {
        return l.m * x + l.b;
    }
    ll findBest(ld x)
    {
        int pos = lower_bound(intersections.begin(),intersections.end(),x) - intersections.begin();
        return eval(hull[pos],x);
    }
};
int main()
{
    fast;
    int n;
    cin>>n;
    ll a,b,c;
    cin>>a>>b>>c;
    vl x(n + 1),dp(n + 1),ps(n + 1);
    for (int i = 1;i<=n;i++){cin>>x[i];ps[i] = ps[i - 1] + x[i];}

    CHT cht;
    line l;

    l.b = 0;
    l.m = 0;
    cht.add_line(l);


    for (int i = 1;i<=n;i++){
        dp[i] = a * ps[i] * ps[i] + b * ps[i] + c + cht.findBest(-2 * a * ps[i]);
        l.b = a * ps[i] * ps[i] - b * ps[i] + dp[i];
        l.m = ps[i];
        cht.add_line(l);

        //for (int j = i - 1;j>=0;j--)
          //dp[i] = max(dp[i],a * ps[i] * ps[i] + b * ps[i] + c + (- 2 * a * ps[i] * ps[j]) + a * ps[j] * ps[j] - b * ps[j] + dp[j]);
        //cout<<dp[i]<<endl;

    }
    cout<<dp[n];
    return 0;
}
