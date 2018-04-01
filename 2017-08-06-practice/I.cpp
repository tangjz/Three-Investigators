#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

int T;
int s[210][2];
int du[210];
vector<int> g[210];
bool tag[210];
bool visit[210];
int n;
char str[10];

void dfs(int t){
	if(du[t] == 0 || visit[t]) return;
	visit[t] = true;
	s[t][0] = s[t][1] = -1;
	bool k = tag[t];
	for(auto v : g[t]){
		dfs(v);
		if(s[v][k] > s[t][k])
			s[t][0] = s[v][0], s[t][1] = s[v][1];
	}
}

void dfs(int t, int res){
	if(du[t] == 0 || visit[t]) return;
	visit[t] = true;
	s[t][0] = s[t][1] = -1;
	bool k = tag[t];
	int tmp = 1e5;
	for(auto v : g[t]){
		dfs(v, res);
		if(k){ //Xiaoqiang
			if(s[v][1] >= res){
				if(s[v][0] > s[t][0])
					s[t][0] = s[v][0], s[t][1] = s[v][1];
			}else tmp = min(tmp, s[v][0]);
		}else{ //AMB 
			if(s[v][0] > s[t][0])
				s[t][0] = s[v][0], s[t][1] = s[v][1];
		}
	}
	if(k && s[t][0] == -1) s[t][0] = tmp, s[t][1] = -1;
}

int main(){
	int l, r, mid;
	scanf("%d", &T);
	while(T--){
		memset(visit, 0, sizeof(visit));
		scanf("%d", &n);
		for(int i = 1; i <= n; ++i)
			g[i].clear();
		vector<int> q;
		for(int i = 1; i <= n; ++i){
			scanf("%d", du + i);
			for(int j = 1; j <= du[i]; ++j){
				static int x;
				scanf("%d", &x);
				g[i].pb(x);
			}
			if(du[i]){
				scanf("%s", str);
				tag[i] = str[0] == 'X';
			}else scanf("%d%d", s[i] + 0, s[i] + 1), q.pb(s[i][1]);
		}
		dfs(1);
		printf("%d", s[1][1]);
		sort(all(q));
		l = 0;
		r = q.size();
		while(l + 1 < r) {
			mid = (l + r)>>1;
			memset(visit, 0, sizeof(visit));
			dfs(1, q[mid]);
			if(s[1][1] >= q[mid])
				l = mid;
			else
				r = mid;
		}
		printf(" %d\n", q[l]);
	}

	return 0;
}
