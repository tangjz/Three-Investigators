#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

set<int> s[10009];
int n;
vector<int> g[10009];
int p;
int ans;
bool tag[10009];

void dfs(int t, int fa){
	for(int v : g[t]){
		if(v == fa) continue;
		dfs(v, t);
		if(tag[t]) continue;
		if(s[v].size() > s[t].size()) swap(s[v], s[t]);
		for(int x : s[v])
			if(s[t].find(x) != s[t].end()) { tag[t] = 1; break; }
			else s[t].insert(x);
	}
	if(tag[t]) set<int>().swap(s[t]), ++ans;
}

int main(){
	while(~scanf("%d", &n)){
		for(int i = 0; i <= n; ++i)
			vector<int>().swap(g[i]), set<int>().swap(s[i]), tag[i] = 0;
		for(int i = 1; i <= n; ++i){
			static int u, v;
			scanf("%d%d", &u, &v);
			g[u].pb(v);
			g[v].pb(u);
		}
		scanf("%d", &p);
		for(int i = 1; i <= p; ++i){
			static int u, v;
			scanf("%d%d", &u, &v);
			if(u == v) tag[u] = 1;
			else{
				s[u].insert(i);
				s[v].insert(i);
			}
		}
		ans = 0;
		dfs(0, -1);
		printf("%d\n", ans);
	}
	
	return 0;
}
