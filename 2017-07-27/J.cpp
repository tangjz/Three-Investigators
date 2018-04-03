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
int tot, root, last, par[maxn * 2], go[maxn * 2][27], val[maxn * 2];
vector<int> son[maxn * 2];
int tag[maxn * 2];
int tt;
int L[maxn * 2], R[maxn * 2];
char s[maxn], t[maxn];
int n, m;
int f[maxn], pos[maxn];
int w[maxn];
int fa[maxn * 2][21];

//root=last=tot=1
void extend(int w){
	int p = last, np;
	if(!go[p][w]){
		np = ++tot; val[np] = val[p] + 1;
		while(p && !go[p][w]) go[p][w] = np, p = par[p];
		if(!p) par[np] = root;
		else{
			int q = go[p][w];
			if(val[p] + 1 == val[q]) par[np] = q;
			else{
				int nq = ++tot; val[nq] = val[p] + 1;
				memcpy(go[nq], go[q], sizeof(go[q]));
				par[nq] = par[q];
				par[q] = par[np] = nq;
				while(p && go[p][w] == q) go[p][w] = nq, p = par[p];
			}
		}
		last = np;
	}else{
		int q = go[p][w];
		if(val[p] + 1 == val[q]) last = q;
		else{
			int nq = ++tot; val[nq] = val[p] + 1;
			memcpy(go[nq], go[q], sizeof(go[q]));
			par[nq] = par[q];
			par[q] = nq;
			while(p && go[p][w] == q) go[p][w] = nq, p = par[p];
			last = nq;
		}
	}
}

int rt[maxn * 4];
const int maxp = maxn * 20 * 20;
int tot_p;
int ls[maxp], rs[maxp], tr[maxp];

void modify(int& t, int l, int r, int x){
	if(!t) t = ++tot_p, ls[t] = 0, rs[t] = 0;
	if(l == r){
		tr[t] = f[x];
		return;
	}
	int mid = (l + r) >> 1;
	if(x <= mid) modify(ls[t], l, mid, x);
	else modify(rs[t], mid + 1, r, x);
	tr[t] = tr[ls[t]] + tr[rs[t]];
}

void modify(int t, int l, int r, int x, int y){
	modify(rt[t], 1, n, y);
	if(l == r) return;
	int mid = (l + r) >> 1;
	if(x <= mid) modify(t << 1, l, mid, x, y);
	else modify((t << 1) | 1, mid + 1, r, x, y);
}

int ask(int t, int l, int r, int x, int y){
	if(!t) return 0;
	if(x <= l && y >= r) return tr[t];
	int mid = (l + r) >> 1;
	return (x <= mid ? ask(ls[t], l, mid, x, y) : 0) + (y > mid ? ask(rs[t], mid + 1, r, x, y) : 0);
}

int ask(int t, int l, int r, int x, int y, int xx, int yy){
	if(x <= l && y >= r) return ask(rt[t], 1, n, xx, yy);
	int mid = (l + r) >> 1;
	return (x <= mid ? ask(t << 1, l, mid, x, y, xx, yy) : 0) + 
		(y > mid ? ask((t << 1) | 1, mid + 1, r, x, y, xx, yy) : 0);
}

void dfs(int t){
	L[t] = tt + 1;
	if(tag[t]){
		w[tag[t]] = ++tt;
		modify(1, 1, n, tt, tag[t]);
	}
	for(int i = 1; fa[t][i - 1]; ++i)
		fa[t][i] = fa[fa[t][i - 1]][i - 1];
	for(auto v : son[t]){
		fa[v][0] = t;
		dfs(v);
	}
	R[t] = tt;
}

int main(){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int T;
	scanf("%d", &T);
	while(T--){
		root = last = tot = 1;
		tt = 0; tot_p = 0;
		memset(go, 0, sizeof(go));
		memset(fa, 0, sizeof(fa));
		memset(tag, 0, sizeof(tag));
		memset(rt, 0, sizeof(rt));
		scanf("%s%s", s + 1, t + 1);
		n = strlen(s + 1);
		m = strlen(t + 1);
		for(int i = 1; i <= n; ++i) scanf("%d", f + i);
		for(int i = 1; i <= n; ++i) extend(s[i] - 'a'), tag[last] = i;
		last = 1;
		for(int i = 1; i <= m; ++i) extend(t[i] - 'a'), pos[i] = last;
		for(int i = 1; i <= tot; ++i) son[i].clear();
		for(int i = 2; i <= tot; ++i) son[par[i]].pb(i);
		dfs(1);
		int Q;
		scanf("%d", &Q);
		int ans = 0;
		while(Q--){
			static int ty, x, y, xx, yy;
			scanf("%d", &ty);
			if(ty == 1){
				scanf("%d%d", &x, &y);
				//x ^= ans, y ^= ans;
				//x++;
				f[x] = y;
				modify(1, 1, n, w[x], x);
			}else{
				scanf("%d%d%d%d", &x, &y, &xx, &yy);
				//x ^= ans, y ^= ans, xx ^= ans, yy ^= ans;
				//x++, y++, xx++, yy++;
				int p = pos[y];
				for(int i = 18; i >= 0; --i)
					if(val[fa[p][i]] >= y - x + 1) p = fa[p][i];
				if(L[p] > R[p] || y - x > yy - xx) printf("%d\n", ans = 0);
				else printf("%d\n", ans = ask(1, 1, n, L[p], R[p], xx + (y - x), yy));
			}
		}
	}
	
	return 0;
}
