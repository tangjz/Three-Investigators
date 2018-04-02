#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

const int maxn = 100100;
int tot, root, last, par[maxn * 2], go[maxn * 2][26], val[maxn * 2];
int cnt[maxn * 2];

int e, he[maxn * 2], to[maxn * 2], ne[maxn * 2];
int T, k;
char s[maxn];
ll ans;

void extend(int w){
	int p = last;
	int np = ++tot; memset(go[np], 0, sizeof(go[np])); cnt[np] = 0;
	val[np] = val[p] + 1;
	while(p && !go[p][w]) go[p][w] = np, p = par[p];
	if(!p) par[np] = root;
	else{
		int q = go[p][w];
		if(val[p] + 1 == val[q]) par[np] = q;
		else{
			int nq = ++tot; memset(go[nq], 0, sizeof(go[nq])); cnt[nq] = 0;
			val[nq] = val[p] + 1;
			memcpy(go[nq], go[q], sizeof(go[q]));
			par[nq] = par[q];
			par[q] = nq;
			par[np] = nq;
			while(p && go[p][w] == q) go[p][w] = nq, p = par[p];
		}
	}
	last = np;
}

void dfs(int t){
	for(int j = he[t]; j; j = ne[j])
		dfs(to[j]), cnt[t] += cnt[to[j]];
	if(cnt[t] == k && t != 1)
		ans += val[t] - val[par[t]];
}

int main(){
	scanf("%d", &T);
	while(T--){
		scanf("%d", &k);
		scanf("%s", s);
		root = tot = last = 1; memset(go[1], 0, sizeof(go[1]));
		for(int i = 0; s[i]; ++i){
			extend(s[i] - 'a');
			++cnt[last];
		}
		e = 0; memset(he, 0, sizeof(int) * (tot + 1));
		for(int i = 2; i <= tot; ++i){
			to[++e] = i; ne[e] = he[par[i]]; he[par[i]] = e;
		}
		ans = 0;
		dfs(1);
		printf("%lld\n", ans);
	}
	return 0;
}
