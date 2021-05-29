/*
Author - Adhish Kancharla(ak2006)
Problem Name - 2011 BOI Day 1 P4 - Treasures and Vikings
Tags - BFS on grid, tight TL
Note - This code gives only 50 points on CSES
Idea - Same as the official solution 
1) We need to find the min time that the Viking takes to reach every cell 
2) We need to do BFS from the starting cell and visit all cells which are at a distance <= Viking's time taken to reach that cell
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
const vi dx = {1,-1,0,0},dy = {0,0,1,-1};
#define pb push_back
#define fast ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
int main()
{
    fast;
    int n,m;
    cin>>n>>m;
    vvc g(n,vc(m));
    vvi d1(n,vi(m,1e9)),d2(n,vi(m,1e9)),d3(n,vi(m,1e9)),d(n,vi(m,1e9));
    int vi = -1,vj = -1,yi = -1,yj = -1,ti = -1,tj = -1;
    for (int i = 0;i<n;i++)
        for (int j = 0;j<m;j++){
            cin>>g[i][j];
            if (g[i][j] == 'V')vi = i,vj = j;
            if (g[i][j] == 'Y')yi = i,yj = j;
            if (g[i][j] == 'T')ti = i,tj = j;
        }
    queue<pair<int,int>>q;
    q.push({vi,vj});
 
    d1[vi][vj] = 0,d2[vi][vj] = 0,d3[vi][vj] = 0;
 
    while (!q.empty()){
        int ci = q.front().first,cj = q.front().second;
 
        for (int i = ci;i>=0;i--){
            if (g[i][cj] == 'I')break;
            d2[i][cj] = min(d2[i][cj],d1[ci][cj]);
        }
 
        for (int i = ci;i<n;i++){
            if (g[i][cj] == 'I')break;
            d2[i][cj] = min(d2[i][cj],d1[ci][cj]);
        }
 
        for (int j = cj;j>=0;j--){
            if (g[ci][j] == 'I')break;
            d2[ci][j] = min(d2[ci][j],d1[ci][cj]);
        }
 
        for (int j = cj;j<m;j++){
            if (g[ci][j] == 'I')break;
            d2[ci][j] = min(d2[ci][j],d1[ci][cj]);
        }
 
        q.pop();
        for (int x = 0;x<4;x++){
            int ni = ci + dx[x],nj = cj + dy[x];
            if (ni < 0 or nj < 0 or ni >= n or nj >= m or g[ni][nj] == 'I')continue;
 
            if (d1[ni][nj] <= d1[ci][cj] + 1)continue;
            d1[ni][nj] = d1[ci][cj] + 1;
            q.push({ni,nj});
        }
    }
    for (int i = 0;i<n;i++)for (int j = 0;j<m;j++)d1[i][j] = d2[i][j];
 
    q.push({yi,yj});
    d[yi][yj] = 0;
    while (!q.empty()){
        int ci = q.front().first,cj = q.front().second;
        q.pop();
        //cout<<d[ci][cj]<<" "<<d1[ci][cj]<<endl;
        for (int x = 0;x<4;x++){
            int ni = ci + dx[x],nj = cj + dy[x];
            if (ni < 0 or nj < 0 or ni >= n or nj >= m or g[ni][nj] == 'I' or d[ci][cj] + 1 >= d1[ni][nj] or d[ni][nj] != 1e9)continue;
            d[ni][nj] = d[ci][cj] + 1;
            q.push({ni,nj});
        }
    }
    if (d[ti][tj] < 1e9 && d[ti][tj] < d1[ti][tj])cout<<"YES";
    else cout<<"NO";
    return 0;
}
/*
2 3
.YT
VII
/*
