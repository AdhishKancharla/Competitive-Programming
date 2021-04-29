/*
Author - Adhish Kancharla (ak2006)
Problem Name - 2014 Test 3 : Cake

Tags - Data Structures, Greedy

Hint - https://www.commonlounge.com/discussion/e276aad6fbbb4c108990da38e703e6f7/all/e6074c6fb29347a6b07ecdbf0e62cd45

Idea -
1) Using the hint above take the largest slice and cut it into some # of pieces of equal size
2) Unfortunately there can be multiple largest slices and how do we know how many pieces the slice should be cut into?
3) Key Idea - (credits to https://codeforces.com/profile/EnEm (Nishchay Manwani) for giving the idea)
    Take the largest slice and its frequency (# of pieces of this largest size)
    then cut that slice into frequency + 1 slices of equal size
    Hence remove the original slice (and its corresponding frequency) and insert the new slices with frequency + 1 # of occurrences
    This can be efficiently done using a multiset

*/
#include <bits/stdc++.h>
using namespace std;
using ld = double;
using vld = vector<ld>;
using vi = vector<int>;
int main()
{
    int n,m;
    cin>>n>>m;
    multiset<pair<ld,int>>s;
    for (int i = 0;i<n;i++){int x;cin>>x;s.insert({x,1});}
    ld ans = 1e9;

    while (m > 0){
        ans = min(ans,(*s.rbegin()).first - (*s.begin()).first);//update ans to be min of ans and the difference b/w max and min sized slices in this iteration
        m--;

        int c = ((*s.rbegin()).second);

        s.insert({((*s.rbegin()).first * c)/(c + 1),c + 1});//The invariant is that the total sum of slice sizes is constant hence we can derive the new slice size after cutting
        s.erase(s.find(*s.rbegin()));
    }

    ans = min(ans,(*s.rbegin()).first - (*s.begin()).first);//Be careful to consider the end state also and take the min with that state as well
    cout<<fixed<<setprecision(6)<<ans;
    return 0;
}
