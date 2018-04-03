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
int n;
vector<int> f[110], g[110];
int h[110], sz[110], rd[110], hh[110], szz[110];

void dfs(int t, int b1, int b2, vector<int> f[]){
	sz[t] = 1;
	h[t] = 1;
	for(int v : f[t]){
		if(v == b1 || v == b2) continue;
		dfs(v, b1, b2, f);
		sz[t] += sz[v];
		h[t] = (ll)h[t] * (h[v] + rd[sz[v]]) % M;
	}
}

int main(){
	freopen("1004.in", "r", stdin);
	freopen("1004.out", "w", stdout);
	scanf("%d", &T);
	for(int i = 1; i <= 100; ++i)
		rd[i] = rand() + 2;
	while(T--){
		scanf("%d", &n);
		for(int i = 1; i <= n; ++i) f[i].clear(), g[i].clear();
		for(int i = 1; i < n; ++i){
			int p;
			scanf("%d", &p);
			f[p].pb(i + 1);
		}
		for(int i = 1; i < n; ++i){
			int p;
			scanf("%d", &p);
			g[p].pb(i + 1);
		}
		set<vector<int> > st;
		bool flag = 0;
		dfs(1, 0, 0, f);
		memcpy(hh, h, sizeof(h));
		memcpy(szz, sz, sizeof(sz));
		for(int i = 2; i <= n; ++i)
			for(int j = i + 1; j <= n; ++j){
				dfs(1, i, j, f);
				dfs(i, 1, j, f);
				int t1 = n - sz[i] - szz[j], t2 = sz[i], t3 = szz[j];
				int h1 = h[1], h2 = h[i], h3 = hh[j];
				if(mkp(t1, h1) > mkp(t2, h2)) swap(t1, t2), swap(h1, h2);
				if(mkp(t1, h1) > mkp(t3, h3)) swap(t1, t3), swap(h1, h3);
				if(mkp(t2, h2) > mkp(t3, h3)) swap(t2, t3), swap(h2, h3);
				st.insert(vector<int>{t1, t2, h1, h2, h3});
			}
		dfs(1, 0, 0, g);
		memcpy(hh, h, sizeof(h));
		memcpy(szz, sz, sizeof(sz));
		for(int i = 2; i <= n; ++i)
			for(int j = i + 1; j <= n; ++j){
				dfs(1, i, j, g);
				dfs(i, 1, j, g);
				int t1 = n - sz[i] - szz[j], t2 = sz[i], t3 = szz[j];
				int h1 = h[1], h2 = h[i], h3 = hh[j];
				if(mkp(t1, h1) > mkp(t2, h2)) swap(t1, t2), swap(h1, h2);
				if(mkp(t1, h1) > mkp(t3, h3)) swap(t1, t3), swap(h1, h3);
				if(mkp(t2, h2) > mkp(t3, h3)) swap(t2, t3), swap(h2, h3);
				if(st.find(vector<int>{t1, t2, h1, h2, h3}) != st.end()){
					flag = 1;
					break;
				}
			}
		printf("%s\n", flag ? "YES" : "NO");
	}
	return 0;
}
