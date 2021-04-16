/*
Author - Adhish Kancharla (ak2006)
Problem Name - IOITC 2012 Test 1 Under the Microscope

Tags - Cakewalk, Simulation
Idea -
1) This problem is really trivial compared to the other problems - just store upper and lower points of the slide
2) Move the slide as needed (up or down and left or right)
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
    int n,m,r,c,k;
    cin>>n>>m>>r>>c>>k;
    ll xl = 0,yl = 0,xu = r - 1,yu = c - 1;
    ll ans = 0;
    while (k--){
        ll x,y;
        cin>>x>>y;
        if (x < xl){
            ans += xl - x;
            xl = x;
            xu = x + r - 1;
        }
        if (x > xu){
            ans += x - xu;
            xu = x;
            xl = x - r + 1;
        }
        if (y < yl){
            ans += yl - y;
            yl = y;
            yu = y + c - 1;
        }
        if (y > yu){
            ans += y - yu;
            yu = y;
            yl = y - c + 1;
        }
    }
    cout<<ans;
    return 0;
}
