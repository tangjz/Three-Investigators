#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define pii pair<int, int>
#define M 1000000007
#define all(a) a.begin(), a.end()

const int maxp = 400000;
int tot;
int dis[maxp], vis[maxp], idx;
int g[maxp][9];
int n;
int p[10];
char s[20];
unordered_map<ll, int> mp;

inline ll gethas(){
	ll has = 0;
	for(int i = 0; i < n; ++i)
		has = has * n + p[i];
	return has;
}

void init(){
	for(int i = 0; i < n; ++i) p[i] = i;
	do{
		ll num = gethas();
		mp[num] = ++tot;
	}while(next_permutation(p, p + n));
	
	for(int i = 0; i < n; ++i) p[i] = i;
	do{
		ll num = gethas();
		int u = mp[num];
		for(int i = 1; i < n; ++i){
			swap(p[i], p[0]);
			int v = mp[gethas()];
			g[u][i - 1] = v;
			swap(p[i], p[0]);
		}
	}while(next_permutation(p, p + n));
}

int bfs(int S, int T){
	queue<int> q;
	++idx;
	q.push(S);
	dis[S] = 0;
	while(!q.empty()){
		int t = q.front(); q.pop();
		for(int i = 0; i < n - 1; ++i){
			int v = g[t][i];
			if(vis[v] != idx){
				dis[v] = dis[t] + 1;
				vis[v] = idx;
				if(v == T) return dis[v];
				q.push(v);
			}
		}
	}
	return -1;
}

int main(){
	scanf("%d", &n);
	init();
	for(int i = 0; i < 5; ++i){
		scanf("%s", s);
		for(int i = 0; i < n; ++i)
			p[i] = s[i] - '1';
		int S = mp[gethas()];
		scanf("%s", s);
		for(int i = 0; i < n; ++i)
			p[i] = s[i] - '1';
		int T = mp[gethas()];
		printf("%d\n", bfs(S, T));
	}
	
#ifndef ONLINE_JUDGE
	system("pause");
#endif
	return 0;
}
