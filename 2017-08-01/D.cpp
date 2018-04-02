#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

const int maxn = 500100;
const int maxp = maxn * 31;
int T;
int a[maxn];
int cnt[2][maxp];
int son[2][maxp];
ll cal[2][31];
int tot;
int n;
ll ans;

void insert(int &t, int dp, bool k, int i){
	if(!t) t = ++tot;
	cnt[k][t]++;
	if(k) cnt[0][t]--;
	if(dp < 0) return;
	bool x = a[i] >> dp & 1;
	if(k){
		cal[x][dp] -= cnt[1][son[x ^ 1][t]];
		ans += cal[x][dp];
		cal[x ^ 1][dp] += cnt[0][son[x ^ 1][t]];
	}
	insert(son[x][t], dp - 1, k, i);
}

int main(){
	int T;
	scanf("%d", &T);
	while(T--){
		scanf("%d", &n);
		memset(cal, 0, sizeof(cal));
		memset(cnt, 0, sizeof(cnt));
		memset(son, 0, sizeof(son));
		int rt = 0; tot = 0;
		for(int i = 1; i <= n; ++i){
			scanf("%d", a + i);
			insert(rt, 29, 0, i);
		}
		ans = 0;
		for(int i = n; i >= 1; --i){
			insert(rt, 29, 1, i);
			
		}
		printf("%lld\n", ans);
	}
	
	return 0;
}
