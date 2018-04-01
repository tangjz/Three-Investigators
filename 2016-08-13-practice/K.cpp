//看看会不会爆int!
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define FOR(i, l, r) for(int i = l; i <= r; i++)
#define ROF(i, r, l) for(int i = r; i >= l; i--)
#define all(a) a.begin(), a.end()
inline int ckmax(int &a, int b) { return a < b ? a = b, 1 : 0; }
inline int ckmin(int &a, int b) { return a > b ? a = b, 1 : 0; }
#define clean(a) memset(a, 0, sizeof(a))

const int maxn = 5100;
int n, k, ans, anst, ansx, ansy, u, v;
int f[maxn], mf1[maxn], mf2[maxn], m1[maxn], m2[maxn], m3[maxn];
vector<int> g[maxn];

void dfs(int t, int fa){
	f[t] = mf1[t] = mf2[t] = m1[t] = m2[t] = m3[t] = 0;
	for(auto v : g[t])
		if(v != fa){
			dfs(v, t);
			f[t] = max(f[t], f[v]);

			if(f[v] > mf1[t]) mf2[t] = mf1[t], mf1[t] = f[v];
			else if(f[v] > mf2[t]) mf2[t] = f[v];

			int mv = m1[v] + 1;
			if(mv > m1[t]) m3[t] = m2[t], m2[t] = m1[t], m1[t] = mv;
			else if(mv > m2[t]) m3[t] = m2[t], m2[t] = mv;
			else if(mv > m3[t]) m3[t] = mv;
		}
	f[t] = max(f[t], m1[t] + m2[t]);
}

int now_rt;
void dfs(int t, int fa, int dp, int maxL, int maxA){
	if(dp > k) return;
	int tmp = max(f[t], max(maxL + m1[t], maxA));
	if(tmp < ans || (tmp == ans && dp < anst)){
		ans = tmp; anst = dp;
		ansx = now_rt, ansy = t;
	}
	for(auto v : g[t])
		if(v != fa){
			int _maxL = maxL;
			if(m1[t] == m1[v] + 1) _maxL = max(_maxL, m2[t]);
			else _maxL = m1[t];

			int _maxA = maxA;
			if(mf1[t] == f[v]) _maxA = max(_maxA, mf2[t]);
			else _maxA = max(_maxA, mf1[t]);
			if(m1[t] == m1[v] + 1) _maxA = max(_maxA, m2[t] + m3[t]);
			else if(m2[t] == m1[v] + 1) _maxA = max(_maxA, m1[t] + m3[t]);
			else _maxA = max(_maxA, m1[t] + m2[t]);
			if(m1[t] == m1[v] + 1) _maxA = max(_maxA, m2[t] + maxL);
			else _maxA = max(_maxA, m1[t] + maxL);

			dfs(v, t, dp + 1, _maxL, _maxA);
		}
}

void work(int rt){
	now_rt = rt;
	dfs(rt, 0);
	dfs(rt, 0, 0, 0, 0);
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("x.in", "r", stdin);
	freopen("x.out", "w", stdout);
#endif
	scanf("%d%d", &n, &k);
	for(int i = 1; i < n; ++i){
		scanf("%d%d", &u, &v);
		u++, v++;
		g[u].pb(v), g[v].pb(u);
	}
	ans = 1e9;
	for(int i = 1; i <= n; ++i) work(i);
	printf("%d\n", ans);
	printf("%d\n", anst);
	if(anst) printf("%d %d", ansx - 1, ansy - 1);
  return 0;
}
/*
                   _ooOoo_
                  o8888888o
                  88" . "88
                  (| -_- |)
                  O\  =  /O
               ____/`---'\____
             .'  \\|     |//  `.
            /  \\|||  :  |||//  \
           /  _||||| -:- |||||-  \
           |   | \\\  -  /// |   |
           | \_|  ''\---/''  |   |
           \  .-\__  `-`  ___/-. /
         ___`. .'  /--.--\  `. . __
      ."" '<  `.___\_<|>_/___.'  >'"".
     | | :  `- \`.;`\ _ /`;.`/ - ` : | |
     \  \ `-.   \_ __\ /__ _/   .-` /  /
======`-.____`-.___\_____/___.-`____.-'======
                   `=---='
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
         佛祖保佑       永无BUG
*/
