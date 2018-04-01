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

int n;
int m[1005];
char p[11], q[11];
int tot;
vector<int> f[305];
vector<pii> edges[1005];
bool pos[1005];
bitset<305> b[305];
bool gt[305][305];
vector<int> ids[305][305];
map<ll, int> mp;

inline int get(char s[]){
	int len = strlen(s);
	ll has = 0;
	for(int i = 0; i < len; ++i)
		has = has * 255 + s[i];
	return mp.count(has) ? mp[has] : mp[has] = ++tot;
}

void init(){
	scanf("%s%s", p, q);
	int bs = get(p), bt = get(q);
	gt[bs][bt] = 1;
	b[bs][bt] = 1;
	scanf("%d", &n);
	queue<int> que;
	
	for(int i = 1; i <= n; ++i){
		scanf("%d", &m[i]);
		for(int j = 0; j < m[i]; ++j){
			scanf("%s%s", p, q);
			int s = get(p), t = get(q);
			if(s == bs && t == bt && !pos[i]) pos[i] = 1, que.push(i);
			edges[i].pb(mkp(s, t));
			ids[s][t].pb(i);
		}
	}
	
	for(int i = 1; i <= tot; ++i) b[i][i] = 1;
	
	while(!que.empty()){
		int t = que.front(); que.pop();
		for(auto v : edges[t]){
			if(gt[v.fi][v.se]) continue;
			gt[v.fi][v.se] = 1;
			for(int i = 1; i <= tot; ++i)
				if(b[i][v.fi] && !b[i][v.se]){
					b[i] |= b[v.se];
					for(int x : ids[i][v.se])
						if(!pos[x]) pos[x] = 1, que.push(x);
				}
		}
	}
}

bool check(){
	for(int i = 1; i <= tot; ++i)
		for(int j = 1; j <= tot; ++j)
			if(i != j && b[i][j] && b[j][i]) return 0;
	for(int i = 1; i <= n; ++i)
		if(!pos[i])
			for(auto ed : edges[i])
				if(b[ed.fi][ed.se]) return 0;
	return 1;
}

int main(){
	init();
	if(check()) printf("Yes");
	else printf("No");
#ifndef ONLINE_JUDGE
	system("pause");
#endif
	return 0;
}
