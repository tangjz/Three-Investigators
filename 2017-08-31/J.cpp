#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

const int maxp = 100100 * 30 * 4;
int n, q;
int res;
int tot;
int rt[100100];
int f[100100], v[100100];
int son[maxp][2];

void insert(int &t, int v, int dp){
	if(!t) t = ++tot, son[t][0] = son[t][1] = 0;
	if(dp < 0) return;
	insert(son[t][v >> dp & 1], v, dp - 1);
}

int merge(int u, int v){
	if(!u || !v) return u | v;
	int t = ++tot;
	son[t][0] = merge(son[u][0], son[v][0]);
	son[t][1] = merge(son[u][1], son[v][1]);
	return t;
}

void ask(int t, int v, int dp){
	if(dp < 0) return;
	int k = v >> dp & 1;
	if(son[t][k ^ 1]){
		res |= 1 << dp;
		ask(son[t][k ^ 1], v, dp - 1);
	}else
		ask(son[t][k], v, dp - 1);
}

int main(){
	while(~scanf("%d%d", &n, &q)){
		memset(rt, 0, sizeof(rt)); tot = 0;
		for(int i = 1; i <= n; ++i){
			scanf("%d", v + i);
			insert(rt[i], v[i], 29);
		}
		for(int i = 2; i <= n; ++i)
			scanf("%d", f + i);
		for(int i = n; i >= 2; --i)
			rt[f[i]] = merge(rt[f[i]], rt[i]);
		while(q--){
			static int u, x;
			scanf("%d%d", &u, &x);
			res = 0;
			ask(rt[u], x, 29);
			printf("%d\n", res);
		}
	}
	
#ifndef ONLINE_JUDGE
	system("pause");
#endif
	return 0;
}
