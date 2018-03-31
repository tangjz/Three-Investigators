#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

const int maxn = 100100, maxp = maxn * 2 * 40;
int tot, root, last, par[maxn * 2], go[maxn * 2][26], val[maxn * 2];
vector<int> son[maxn * 2];
int rt[maxn * 2];
int tt, ls[maxp], rs[maxp];
int the_last[maxn], bg[maxn];
char s[maxn];
int R[maxn][26], _R[26];
int n, Q, T;
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

void insert(int& t, int l, int r, int x){
	if(!t) t = ++tt, ls[t] = rs[t] = 0; assert(tt < maxp);
	if(l == r) return;
	int mid = (l + r) >> 1;
	if(x <= mid) insert(ls[t], l, mid, x);
	else insert(rs[t], mid + 1, r, x);
}

int merge(int a, int b){
	if(!a || !b) return a | b;
	int c = ++tt;
	ls[c] = merge(ls[a], ls[b]);
	rs[c] = merge(rs[a], rs[b]);
	return c;
}

bool ask(int t, int l, int r, int x){
	if(!t) return 0;
	if(l == r) return 1;
	int mid = (l + r) >> 1;
	if(x <= mid) return ask(ls[t], l, mid, x);
	else return ask(rs[t], mid + 1, r, x);
}

void dfs(int t){
	for(int v : son[t]){
		dfs(v);
		rt[t] = merge(rt[t], rt[v]);
	}
}

bool sub_seq(int x, int y){
	for(int i = bg[x], j = bg[y]; i < bg[x + 1]; ++i, ++j){
		j = R[j][s[i] - 'a'];
		if(j >= bg[y + 1]) return 0;
	}
	return 1;
}

int main(){
	scanf("%d", &T);
	while(T--){
		memset(go, 0, sizeof(go));
		memset(rt, 0, sizeof(rt));
		tot = root = 1;
		tt = 0;

		scanf("%d%d", &n, &Q);
		for(int i = 0; i < n; ++i){
			last = 1;
			scanf("%s", s + bg[i]);
			bg[i + 1] = bg[i] + strlen(s + bg[i]);
			for(int j = bg[i]; j < bg[i + 1]; ++j){
				extend(s[j] - 'a');
				insert(rt[last], 1, n, i + 1);
			}
			the_last[i] = last;
		}
		for(int i = 1; i <= tot; ++i) son[i].clear();
		for(int i = 2; i <= tot; ++i) son[par[i]].pb(i);
		dfs(1);

		for(int i = 0; i < 26; ++i) R[bg[n]][i] = bg[n];
		for(int i = bg[n] - 1; i >= 0; --i){
			memcpy(R[i], R[i + 1], sizeof(R[i + 1]));
			R[i][s[i] - 'a'] = i;
		}
		map<pair<int, int>, bool> mp;
		for(int i = 0; i < Q; ++i){
			static int x, y;
			scanf("%d%d", &x, &y); --x, --y;
			bool res = mp.count(mkp(x, y)) ? mp[mkp(x, y)] : 
				bg[x + 1] - bg[x] <= bg[y + 1] - bg[y] ? sub_seq(x, y) : 0;
			mp[mkp(x, y)] = res;
			putchar('0' + res);
			putchar('0' + ask(rt[the_last[x]], 1, n, y + 1));
		}
		puts("");
	}
	return 0;
}
