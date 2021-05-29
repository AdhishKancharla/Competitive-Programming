/*
Author - Adhish Kancharla(ak2006)
Problem Name - Baltic OI 2019 Day 2 P3 - Olympiads
Tags - Fracturing Search
Idea - Excellent introductory problem on fracturing search
Learn fracturing search from here - https://usaco.guide/adv/fracture and watch this video by Algorithms Live - https://www.youtube.com/watch?v=EG_HfFMM0lE
The official solution also explains the idea well
Implementation Detail - Follow the template for fracturing search problems because the implementation can get tricky 

Basic Idea of Fracturing Search - 
1) Fracturing Search can be used in problems where we need to find the Kth best solution. For example Kth best MST or the Kth best score in this problem.
2) Find the best solution using the normal algorithm and sequentially find the next best solution using a priority queue and by fixing some items to take and fixing some item to not take
   Refer to the video and the official solution for more details.
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
	// #ifndef ONLINE_JUDGE
	// freopen("input.txt","r",stdin);
	// freopen("output.txt","w",stdout);
	// #endif
}
int main()
{
	setIO();
	int n,m,k;
	cin>>n>>m>>k;
	vvl scores(n,vl(m));
	for (int i = 0;i<n;i++)for (int j = 0;j<m;j++)cin>>scores[i][j];
	vvi best_scores(m,vi(n));
	for (int i = 0;i<m;i++){
		for (int j = 0;j<n;j++)best_scores[i][j] = j;
		sort(best_scores[i].begin(), best_scores[i].end(),[&](int a,int b){
			return scores[a][i] > scores[b][i];
		});
	}
	struct Item{
		int score;
		int pos;
		vi current;
		vb forbidden;
		const bool operator<(const Item &other)const{
			return score < other.score;
		}
	};
	const auto evaluate = [&](const vi& cur)
	{
		vl res(m);
		ll ret = 0;
		for (int i = 0;i<(int)cur.size();i++){
			int pos = best_scores[i][cur[i]];
			for (int j = 0;j<m;j++){
				res[j] = max(res[j],scores[pos][j]);
			}
		}
		for (int j = 0;j<m;j++)ret += res[j];
		return ret;
	};
	Item best;
	best.score = 0,best.pos = 0;
	best.current.assign(m,-1);
	best.forbidden.assign(n,0);
	for (int i = 0;i<m;i++){
		int pos = 0;
		while (pos < n && best.forbidden[best_scores[i][pos]])pos++;
		if (pos < n){
			best.current[i] = pos;
			best.forbidden[best_scores[i][pos]] = 1;
		}
	}
	best.score = evaluate(best.current);
	k--;
	priority_queue<Item>pq;
	pq.push(best);
	while (k--){
		Item now = pq.top();
		pq.pop();
		for (int j = now.pos;j<m;j++){
			int pos = now.current[j];
			now.forbidden[best_scores[j][now.current[j]]] = 1;
			while (pos < n && now.forbidden[best_scores[j][pos]])pos++;
			if (pos < n){
				Item next = now;
				next.pos = j;
				next.current[j] = pos;
				next.score = evaluate(next.current);
				next.forbidden[best_scores[j][pos]] = 1;
				pq.push(next);
			}
		}
	}
	cout<<pq.top().score;
	return 0;
}
