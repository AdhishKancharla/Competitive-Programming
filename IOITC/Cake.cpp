#include <bits/stdc++.h>
using namespace std;
using ld = long double;
using vld = vector<ld>;
using vi = vector<int>;
int main()
{
    int n,m;
    cin>>n>>m;
    multiset<pair<ld,int>>s;
    vi cnt(1e5 + 1);
    for (int i = 0;i<n;i++){int x;cin>>x;cnt[x]++;}
    for (int i = 0;i<=1e5;i++)if (cnt[i])s.insert({i,cnt[i]});
    ld ans = 1e9;

    while (m > 0){
        ans = min(ans,(*s.rbegin()).first - (*s.begin()).first);
        int num = ceil((*s.rbegin()).first / ((*s.begin()).first));
        if (num == 1)num++;
        //cout<<num<<" "<<m<<" "<<fixed<<setprecision(6)<<(*s.rbegin()).first<<" "<<(*s.begin()).first<<endl;
        num = min(num,m + 1);
        m -= num - 1;

        int c = ((*s.rbegin()).second);

        s.insert({(*s.rbegin()).first/num,num});
        if ((*s.rbegin()).second > 1)
            s.insert({(*s.rbegin()).first,(*s.rbegin()).second - 1});
        s.erase(*s.rbegin());
    }

    //for (auto it:s)cout<<fixed<<setprecision(6)<<it.first<<endl;

    ans = min(ans,(*s.rbegin()).first - (*s.begin()).first);
    cout<<ans;
    return 0;
}
