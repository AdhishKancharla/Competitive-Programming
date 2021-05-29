/*
Author - Adhish Kancharla(ak2006)
Problem Name - 2011 Day 1 P3 - Switch the Lamp On
Tags - 0/1 BFS
This is a simple problem on 0/1 BFS although the implementation can be a bit tricky
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
using pii = pair<int,int>;
using vpii = vector<pii>;
const ll mod = 1e9 + 7,inf = 1e18;
#define pb push_back
#define fast ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
int main()
{
    int n,m;
    cin>>n>>m;
    map<pii,vpii>p;
    vvi d(n + 1,vi(m + 1,1e9));

    for (int i = 0;i<n;i++){
        for (int j = 0;j<m;j++){
            char x;
            cin>>x;
            if (x == '/')
                p[{i + 1,j}].pb({i,j + 1}),p[{i,j + 1}].pb({i + 1,j});
            else
                p[{i,j}].pb({i + 1,j + 1}),p[{i + 1,j + 1}].pb({i,j});
        }
    }

    deque<pair<int,int>>q;
    q.push_front({0,0});
    d[0][0] = 0;

    while (!q.empty()){
        int i = q.front().first,j = q.front().second;
        q.pop_front();

        vpii v = p[{i,j}];
        pii a = {i + 1,j + 1},b = {i - 1,j + 1};
        bool is0 = (find(v.begin(),v.end(),a) != v.end()),is1 = (find(v.begin(),v.end(),b) != v.end());


        if (is0){
            if (d[i + 1][j + 1] > d[i][j]){
                d[i + 1][j + 1] = d[i][j];
                q.push_front({i + 1,j + 1});
            }
        }
        else{
            if (i + 1 <= n && j + 1 <= m && d[i + 1][j + 1] > d[i][j] + 1){
                d[i + 1][j + 1] = d[i][j] + 1;
                q.push_back({i + 1,j + 1});
            }
        }

        if (is1){
            if (d[i - 1][j + 1] > d[i][j]){
                d[i - 1][j + 1] = d[i][j];
                q.push_front({i - 1,j + 1});
            }
        }
        else{
            if (i - 1 >= 0 && j + 1 <= m && d[i - 1][j + 1] > d[i][j] + 1){
                d[i - 1][j + 1] = d[i][j] + 1;
                q.push_back({i - 1,j + 1});
            }
        }

        a = {i - 1,j - 1},b = {i + 1,j - 1};

        is0 = find(v.begin(),v.end(),a) != v.end(),is1 = find(v.begin(),v.end(),b) != v.end();

        if (is0){
            if (d[i - 1][j - 1] > d[i][j]){
                d[i - 1][j - 1] = d[i][j];
                q.push_front({i - 1,j - 1});
            }
        }
        else{
            if (i - 1 >= 0 && j - 1 >= 0 && d[i - 1][j - 1] > d[i][j] + 1){
                d[i - 1][j - 1] = d[i][j] + 1;
                q.push_back({i - 1,j - 1});
            }
        }

        if (is1){
            if (d[i + 1][j - 1] > d[i][j]){
                d[i + 1][j - 1] = d[i][j];
                q.push_front({i + 1,j - 1});
            }
        }
        else{
            if (i + 1 <= n && j - 1 >= 0 && d[i + 1][j - 1] > d[i][j] + 1){
                d[i + 1][j - 1] = d[i][j] + 1;
                q.push_back({i + 1,j - 1});
            }
        }
    }
    if (d[n][m] == 1e9)cout<<"NO SOLUTION";
    else cout<<d[n][m];
    return 0;
}
/*
4 4
\/\\
////
//\/
//\/
*/
