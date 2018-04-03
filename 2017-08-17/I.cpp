#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

const int maxn = 1010, maxm = 10010, INF = 1e9;
int inw[maxn], pre[maxn];
int u[maxm], v[maxm], w[maxm], ru[maxm], rv[maxm];
int vis[maxn], blg[maxn];
int n, m, tmp;

int zle(int n, int root){
	int ans = 0, cnt;
	while(1){
		for(int i = 0; i < n; ++i) inw[i] = INF;
		for(int i = 0; i < m; ++i)
			if(u[i] != v[i] && inw[v[i]] > w[i])																				
				inw[v[i]] = w[i], pre[v[i]] = u[i];

		inw[root] = 0;
		for(int i = 0; i < n; ++i)
			if(inw[i] == INF) return INF;
		cnt = 0;
		memset(vis, -1, sizeof(vis));
		memset(blg, -1, sizeof(blg));
		for(int i = 0, j; i < n; ++i){
			ans += inw[i];
			for(j = i; vis[j] != i && blg[j] == -1 && j != root; j = pre[j]) vis[j] = i;
			if(j != root && blg[j] == -1){
				for(int k = pre[j]; k != j; k = pre[k]) blg[k] = cnt;
				blg[j] = cnt++;
			}
		}
		if(cnt == 0) return ans;
		for(int i = 0; i < n; ++i)
			if(blg[i] == -1) blg[i] = cnt++;
		for(int i = 0, j; i < m; ++i){
			j = v[i];
			u[i] = blg[u[i]]; v[i] = blg[v[i]];
			if(u[i] != v[i]) w[i] -= inw[j];
		}
		n = cnt; root = blg[root];
	}
}

int main(){
	freopen("1009.in", "r", stdin);
	freopen("1009_.out", "w", stdout);
	int T;
	scanf("%d", &T);
	while(T--){
		scanf("%d%d", &n, &m);
		for(int i = 0; i < m; ++i){
			scanf("%d%d%d", u + i, v + i, w + i);
			--u[i], --v[i];
			ru[i] = u[i], rv[i] = v[i], w[i] = -w[i] * 1000;
			if(v[i] == n - 1) w[i] += u[i];
		}
		int ans = zle(n, 0), res2 = 0;
		while(ans % 1000) ++res2, --ans;
		printf("%d %d\n", -ans / 1000, res2 + 1);
	}
	return 0;
}
