#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

const int maxn = 550, maxm = 20;
int n, m;
int a[maxn][maxn];
bool tag[maxn];
int b[maxm];
int f[maxn][maxm], d[maxn][maxm], from[maxn][maxm];
vector<int> ans;
char s[maxn];

int main(){
	freopen("simplicity.in", "r", stdin);
	freopen("simplicity.out", "w", stdout);
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i){
		scanf("%s", s + 1);
		for(int j = 1; j <= n; ++j)
			a[i][j] = s[j] - '0';
	}
	scanf("%d", &m);
	for(int i = 1; i <= m; ++i)
		scanf("%d", b + i), tag[b[i]] = 1, ans.pb(b[i]);
	
	vector<int> q;
	for(int i = 1; i <= n; ++i)
		if(!tag[i]) q.pb(i);
	sort(all(q), [](const int &i, const int &j) { return a[i][j]; });
	
 
	for(int mask = 0; mask < 1 << m; ++mask){
		vector<int> qq;
		for(int j = 0; j < m; ++j)
			if(mask >> j & 1) qq.pb(b[j + 1]);
		
		int k = qq.size();
		for(int i = 0; i < k; ++i)
			for(int j = 0; j < i; ++j)
				if(!a[qq[j]][qq[i]]) swap(qq[i], qq[j]);
		
		bool flag = 1;
		for(int i = 0; i < k; ++i)
			for(int j = 0; j < i; ++j)
				if(!a[qq[j]][qq[i]]) flag = 0;
		if(!flag) continue;
		
		for(int i = 1; i <= n - m; ++i){
			int p = 0;
			while(p < k && a[qq[p]][q[i - 1]]) p++;
			
			flag = 1;
			for(int j = p; j < k; ++j) if(a[qq[j]][q[i - 1]]) flag = 0;
			
			for(int j = 0; j <= k; ++j)
				f[i][j] = f[i - 1][j] + 1, d[i][j] = 1, from[i][j] = j;
			if(flag){
				for(int j = 0; j <= p; ++j)
					if(f[i - 1][j] < f[i][p])
						f[i][p] = f[i - 1][j], d[i][p] = 0, from[i][p] = j;
			}
		}
		
		int now = -1, res = 1e9;
		for(int i = 0; i <= k; ++i)
			if(f[n - m][i] < res) res = f[n - m][i], now = i;
		vector<int> po;
		for(int i = n - m; i >= 1; --i){
			if(d[i][now]) po.pb(q[i - 1]);
			now = from[i][now];
		}
		if(m - k + po.size() < ans.size()){
			ans.clear();
			for(int i = 0; i < m; ++i)
				if(!(mask >> i & 1)) ans.pb(b[i + 1]);
			for(auto v : po) ans.pb(v);
		}
	}
	
	printf("%d\n", (int)ans.size());
	for(auto v : ans) printf("%d ", v);
	
	return 0;
}
