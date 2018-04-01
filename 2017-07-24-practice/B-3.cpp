#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

const int maxn = 200100;
int n, T;
int fa[maxn], sa[maxn], p[maxn], rk[maxn];
int ban[maxn][26];
vector<int> neq[maxn], neqq[maxn];
char s[maxn];

int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }

void merge(int x, int y){
	if(x < 1 || y > 2 * n + 1) return;
	if(!(x & 1))
		fa[find(x / 2)] = find(y / 2);
}

void not_equal(int x, int y){
	if(x < 1 || y > 2 * n + 1) return;
	x = x / 2, y = y / 2;
	neq[x].pb(y);
	neq[y].pb(x);
}

bool solve(){
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", sa + i), sa[i]++, rk[sa[i]] = i, fa[i] = i;
		neq[i].clear();
		neqq[i].clear();
		s[i] = 0;
	}
	p[1] = p[2 * n + 1] = 1;
	bool flag = 0;
	for(int i = 2; i <= 2 * n; ++i){			
		scanf("%d", p + i);
		++p[i];
		if(i - p[i] < 0 || i + p[i] > 2 * n + 2) flag = 1;
		if((p[i] & 1) ^ (i & 1)) flag = 1;
	}
	if(flag) return 0;
	int id = 0, mx = 0;
	for(int i = 1; i <= 2 * n + 1; ++i){
		int x = mx > i ? min(p[id + id - i], mx - i) : 1;
		if(x > p[i]) return 0;
		while(x < p[i]) merge(i - x, i + x), ++x;
		not_equal(i - x, i + x);
		if(i + p[i] > mx) mx = i + p[i], id = i;
	}
	s[sa[1]] = 'a';
	s[find(sa[1])] = 'a';
	for(int i = 1; i <= n; ++i) find(i);
	for(int i = 1; i <= n; ++i){
		for(auto v : neq[i]){
			if(fa[i] == fa[v]) return 0;
			neqq[fa[i]].pb(fa[v]);
		}
	}
	for(auto v : neqq[fa[sa[1]]]) ban[v][0] = T + 1;
	int now = 0;
	rk[n + 1] = 0;
	for(int i = 2; i <= n; ++i){
		int x = sa[i];
		if(rk[x + 1] < rk[sa[i - 1] + 1]) ++now;
		while(now < 26 && ban[fa[x]][now] == T + 1) ++now;
		if(now >= 26) return 0;		
		if(!s[fa[x]]) {
			s[fa[x]] = now + 'a';
			for(auto v : neqq[fa[x]]) ban[v][now] = T + 1;
		}
		else if(now + 'a' != s[fa[x]]) return 0;
		s[x] = now + 'a';
	}
	for(int i = 1; i <= n; ++i){
		if(s[i] != s[fa[i]]) return 0;
		for(auto v : neq[i])
			if(s[i] == s[v]) return 0;
	}
	s[n + 1] = 0;
	return 1;
}

int main(){
	int ca = 0;
	scanf("%d", &T);
	while(T--){
		printf("Case #%d: ", ++ca);
		if(!solve()) printf("Wrong calculation!\n");
		else printf("%s\n", s + 1);
	}
	
	return 0;
}
