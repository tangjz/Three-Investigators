#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define pii pair<int, int>
#define all(a) a.begin(), a.end()

const int B1 = 27, M1 = 1000000007;
const int B2 = 37, M2 = 1000000009;

const int maxn = 205, maxm = 200005;
int n, m;
int to[maxm], ne[maxm], he[maxn], e;
int len[maxn];
int vis[maxm], inx, p[maxm];
vector<int> g[maxn], h[maxn];
int ba_h[maxm], ba_g[maxm];
char s[maxm];

void link(int u, int v){
	//printf("edge: %d %d\n", u, v);
	to[++e] = v, ne[e] = he[u], he[u] = e;
}

bool dfs(int t){
	//printf("%d: %d\n", t, he[t]);
	for(int j = he[t]; j; j = ne[j])
		if(vis[to[j]] < inx){
			//printf("vis %d\n", to[j]);
			vis[to[j]] = inx;
			if(p[to[j]] == -1 || dfs(p[to[j]])){
				p[to[j]] = t;
				return 1;
			}
		}
	return 0;
}

bool check(int k){
	map<pii, int> mp;
	m = 0; e = 0;
	for(int i = 0; i < n; ++i){
		int tk = min(len[i], k);
		he[i] = 0;
		for(int j = tk; j < tk + len[i]; ++j){
			int gg = (g[i][j] - (ll)g[i][j - tk] * ba_g[tk]) % M1;
			int hh = (h[i][j] - (ll)h[i][j - tk] * ba_h[tk]) % M2;
			(gg < 0) && (gg += M1);
			(hh < 0) && (hh += M2);
			int x = mp.count(mkp(gg, hh)) ? mp[mkp(gg, hh)] : (p[m] = -1, mp[mkp(gg, hh)] = m++);
			//if(k == 1) printf("%d %d: %d %d %d\n", i, j, gg, hh, x);
			link(i, x);
			//printf("he[%d]: %d\n", i, he[i]);
		}
	}

	for(int i = 0; i < n; ++i){
		++inx;
		if(!dfs(i)) return 0;
	}
	return 1;
}

int main(){
	scanf("%d", &n);
	int maxl = 0;
	for(int i = 0; i < n; ++i){
		scanf("%s", s);
		len[i] = strlen(s);
	 
		g[i].resize(len[i] * 2);
		h[i].resize(len[i] * 2);
		int now1 = 0, now2 = 0;
		for(int j = 0; j < 2 * len[i]; ++j){
			g[i][j] = now1 = ((ll)now1 * B1 + s[j % len[i]] - 'a' + 1) % M1;
			h[i][j] = now2 = ((ll)now2 * B2 + s[j % len[i]] - 'a' + 1) % M2;
			
			//printf("%d %d: %d %d\n", i, j, g[i][j], h[i][j]);
		}
		maxl = max(maxl, len[i]);
	}
	
	ba_h[0] = ba_g[0] = 1;
	for(int i = 1; i <= maxl; ++i){
		ba_g[i] = (ll)ba_g[i - 1] * B1 % M1;
		ba_h[i] = (ll)ba_h[i - 1] * B2 % M2;
		//printf("base %d: %d %d\n", i, ba_g[i], ba_h[i]);
	}
	
	int l = 0, r = maxl;
	while(l + 1 < r){
		int d = (l + r) >> 1;
		if(check(d)) r = d;
		else l = d;
	}
	printf("%d\n", r);
	
#ifndef ONLINE_JUDGE
	system("pause");
#endif
	return 0;
}
