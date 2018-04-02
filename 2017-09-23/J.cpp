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

const int inf = 1e9;
const int maxp = 400001;
int tot;
map<int, int> mp[9];
vector<int> q[9];
int used[11];
int ch[11];
vector<int> g[maxp];
int dis[maxp];

int T;
char bg[11], ed[11];
int cursor;

void dfs(int t, int num){
	if(t && used[8]){
		mp[t][num] = ++tot;
		q[t].pb(num);
	}
	if(t == 8) return;
	for(int i = 1; i <= 8; ++i)
		if(!used[i]){
			used[i] = 1;
			dfs(t + 1, num * 10 + i);
			used[i] = 0;
		}
}

int LEF(int n, int cur){
	swap(ch[cur], ch[cur - 1]);
	int num = 0;
	for(int i = 1; i <= n; ++i)
		num = num * 10 + ch[i];
	swap(ch[cur], ch[cur - 1]);
	return mp[n][num];
}

int RIG(int n, int cur){
	swap(ch[cur], ch[cur + 1]);
	int num = 0;
	for(int i = 1; i <= n; ++i)
		num = num * 10 + ch[i];
	swap(ch[cur], ch[cur + 1]);
	return mp[n][num];
}

int delLEF(int n, int cur){
	int num = 0;
	for(int i = 1; i <= n; ++i)
		if(i != cur - 1)
			num = num * 10 + ch[i];
	return mp[n - 1][num];
}

int delRIG(int n, int cur){
	int num = 0;
	for(int i = 1; i <= n; ++i)
		if(i != cur + 1)
			num = num * 10 + ch[i];
	return mp[n - 1][num];
}

int INS(int n, int cur, int x){
	int num = 0;
	for(int i = 1; i <= n; ++i){
		if(i == cur) num = num * 10 + x;
		num = num * 10 + ch[i];
	}
	return mp[n + 1][num];
}

void init(){
	dfs(0, 0);
	int idx = 5;
	for(int i = 1; i <= 8; ++i)
		for(int v : q[i]){
			int cur = -1, po = mp[i][v];
			++idx;
			for(int j = 1, x = v; j <= i; ++j){
				ch[i - j + 1] = x % 10, x /= 10;
				if(ch[i - j + 1] == 8) cur = i - j + 1;
				used[ch[i - j + 1]] = idx;
			}
			
			if(cur > 1){
				int lef = LEF(i, cur);
				g[po].pb(lef);
			}
			if(cur < i){
				int rig = RIG(i, cur);
				g[po].pb(rig);
			}
			if(cur > 1){
				int lef = delLEF(i, cur);
				int md = ++tot;
				g[po].pb(md);
				g[md].pb(lef);
			}
			if(cur < i){
				int rig = delRIG(i, cur);
				int md = ++tot;
				g[po].pb(md);
				g[md].pb(rig);
			}
			for(int k = 1; k <= 7; ++k)
				if(used[k] != idx){
					int gt = INS(i, cur, k);
					int md = ++tot;
					g[po].pb(md);
					g[md].pb(gt);
				}
		}
}

void bfs(int S){
	queue<int> q;
	q.push(S);
	memset(dis, 127, sizeof(int) * (tot + 1));
	dis[S] = 0;
	while(!q.empty()){
		int t = q.front(); q.pop();
		for(int v : g[t])
			if(dis[v] > inf){
				dis[v] = dis[t] + 1;
				q.push(v);
			}
	}
}

int main(){
	init();
	
	//scanf("%d", &T);
	while(~scanf("%s%d%s", bg, &cursor, ed)){
		int n = strlen(bg), m = strlen(ed);
		int num = 0;
		for(int i = 0; i < n; ++i){
			if(cursor == i) num = num * 10 + 8;
			num = num * 10 + bg[i] - 'a' + 1;
		}if(cursor == n) num = num * 10 + 8;
		int po = mp[n + 1][num];
		bfs(po);
		int ans = inf;
		for(int i = 0; i <= m; ++i){
			int num = 0;
			for(int j = 0; j < m; ++j){
				if(i == j) num = num * 10 + 8;
				num = num * 10 + ed[j] - 'a' + 1;
			}if(i == m) num = num * 10 + 8;
			if(!mp[m + 1].count(num)) continue;
			ans = min(ans, dis[mp[m + 1][num]]);
		}
		if(ans == inf) printf("-1\n");
		else printf("%.1f\n", ans / 2.);
	}
	return 0;
}

