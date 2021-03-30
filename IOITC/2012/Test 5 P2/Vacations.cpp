/*
Author - Adhish Kancharla (ak2006) 
Problem Name - IOITC 2012 Test 5 P2 : Vacations

Way 1 - SQRT Decomposition on array using a set and small to large merging - commented out part (does not work as intended)
Way 2 - Standard Mo's with frequency array


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
vi freq(1e6+1);
int n = 1e5 + 5,rn;
vi a(n);
int cnt = 0;
void add(int i)
{
    if (freq[a[i]] == 0)cnt++;
    freq[a[i]]++;
}
void sub(int i)
{
    if (freq[a[i]] == 1)cnt--;
    freq[a[i]]--;
}
bool cmp(vi&f,vi&s)
{
    if (f[0]/rn != s[0]/rn)return f[0]/rn < s[0]/rn;
    return f[1] < s[1];
}
int main()
{
    fast;
    cin>>n;
    for (int i = 0;i<n;i++)cin>>a[i];
    rn = ceil(sqrt(n));
//    vector<set<int>>blocks(rn);
//    for (int i = 0;i<n;i++)
//        blocks[i/rn].insert(a[i]);

    int q;
    cin>>q;
//    while (q--){
//        int l,r;
//        cin>>l>>r;
//        l--,r--;
//        set<int>cur;
//        while (l<=r && l%rn != 0){
//            cur.insert(a[l]);
//            l++;
//        }
//
//        assert(l > r || l%rn == 0);
//
//        while (l + rn <= r){
//            if (blocks[l/rn].size() > cur.size())swap(blocks[l/rn],cur);
//            for (auto it:blocks[l/rn])cur.insert(it);
//            l += rn;
//        }
//        while (l<=r){
//            cur.insert(a[l]);
//            l++;
//        }
//        cout<<cur.size()<<'\n';
//    }
    vvi queries(q);
    vi out(q);
    for (int i = 0;i<q;i++){
        int l,r;
        cin>>l>>r;
        l--,r--;
        queries[i] = {l,r,i};
    }
    sort(queries.begin(),queries.end(),cmp);
    int l = 0,r = 0;
    add(0);
    for (int i = 0;i<q;i++){
        int newl = queries[i][0],newr = queries[i][1];
        while (l > newl)
            add(--l);
        while (r < newr)
            add(++r);
        while (r > newr)
            sub(r--);
        while (l < newl)
            sub(l++);
        out[queries[i][2]] = cnt;
    }
    for (int i = 0;i<q;i++)cout<<out[i]<<'\n';
    return 0;
}
