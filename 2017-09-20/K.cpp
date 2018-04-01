#include<bits/stdc++.h>
using namespace std;
#define M 1000000007
#define ll long long
#define pb push_back

const int N = 2500000;
const int maxn = 100005;
int n;
int a[maxn];
vector<int> id[N + 5];
int cnt[maxn], mx;
int f[maxn], g[maxn], s0[maxn], s1[maxn], pre[maxn];
int ss0[maxn], ss1[maxn];
int v[maxn];

int gcd(int a, int b){
	return !b ? a : gcd(b, a % b);
}

void work(int m, int w){
	memset(f, 0, sizeof(int) * m);
	memset(g, 0, sizeof(int) * m);
	memset(s0, 0, sizeof(int) * m);
	memset(s1, 0, sizeof(int) * m);
	int r = 0, gc = v[0] / w;
	while(gc > 1 && r < m - 1)
		gc = gcd(gc, v[++r] / w);
	if(gc > 1) return;
	int t = r, l = 0;
	for(int i = r, gc = 0; i >= 0; --i)
		pre[i] = gc = gcd(gc, v[i] / w);
	while(l < r && pre[l + 1] == 1) ++l;
	f[r] = 1;
	g[r] = (ll)(l + 1) * cnt[mx] % M;
	ss0[r] = s0[1] = g[r];
	ss1[r] = s1[1] = (ll)g[r] * r % M;

	for(r = r + 1, gc = 0; r < m; ++r){
		gc = gcd(gc, v[r] / w);
		if(t == l){
			int gg = 0;
			for(int i = r; i > l; --i)
			   pre[i] = gg = gcd(gg, v[i] / w);
			gc = 0;
			t = r;
		}
		while(l < r && gcd(pre[l + 1], gc) == 1){
			++l;
			if(t == l){
				int gg = 0;
				for(int i = r; i > l; --i)
					pre[i] = gg = gcd(gg, v[i] / w);
				gc = 0;
				t = r;
			}
		}
		f[r] = (l ? f[l - 1] : 0) + 1;
		if(f[r] == 1){
			g[r] = (ll)(l + 1) * cnt[mx] % M;
		}else{
			g[r] = ((ll)l * ss0[l - 1] - ss1[l - 1]) % M;
			(g[r] < 0) && (g[r] += M);
		}
		s0[f[r]] += g[r];
		(s0[f[r]] >= M) && (s0[f[r]] -= M);
		s1[f[r]] += (ll)g[r] * r % M;
		(s1[f[r]] >= M) && (s1[f[r]] -= M);
		ss0[r] = s0[f[r]];
		ss1[r] = s1[f[r]];
	}
	for(int i = 1; i <= f[m - 1]; ++i)
		cnt[i + mx] = s0[i];
	mx += f[m - 1];
}

int main(){
	//freopen("K.in", "r", stdin);
	//freopen("K.out", "w", stdout);
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i){
		scanf("%d", a + i);
		id[a[i]].pb(i);
	}
	int ans = 0, ways = 0;
	for(int i = 1; i <= N; ++i){
		for(int j = i + i; j <= N; j += i)
			for(int v : id[j])
				id[i].pb(v);
		sort(id[i].begin(), id[i].end());

		int m = id[i].size();
		memset(cnt, 0, sizeof(int) * (m + 1));
		cnt[0] = 1;
		mx = 0;
		for(int j = 0, k = 0; j < m; j = k){
			k = j + 1;
			int nn = 1; v[0] = a[id[i][j]];
			while(k < m && id[i][k] == id[i][k - 1] + 1) v[nn++] = a[id[i][k++]];
			work(nn, i);
		}
		if(mx > ans) ans = mx, ways = cnt[mx];
		else if(mx == ans) ways = (ways + cnt[mx]) % M;
	}
	printf("%d %d\n", ans, ways);
	//system("pause");
	return 0;
}
