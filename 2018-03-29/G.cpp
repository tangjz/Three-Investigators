#include<bits/stdc++.h>
using namespace std;
#define y1 y114514
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define pii pair<int, int>
#define M 1000000007
#define all(a) a.begin(), a.end()
typedef long long ll;

int T, n;
int p[100100];
int f[100100], g[100100];
int tf[100100], tg[100100];

int main(){
	scanf("%d", &T);
	while(T--){
		scanf("%d", &n);
		for(int i = 1; i <= n; ++i){
			scanf("%d", p + i);
			if(i == 1){
				f[i] = 0;
				g[i] = n + 1;
			}else{
				tg[i] = tf[i] = -1;
				if(p[i] > p[i - 1] && tg[i - 1] != -1){
					g[i] = g[i - 1]; tg[i] = 1;
				}else if(p[i] < p[i - 1] && tf[i - 1] != -1){
					f[i] = f[i - 1]; tf[i] = 0;
				}
				if(p[i] > f[i - 1] && tf[i - 1] != -1){
					if(p[i - 1] > g[i] || tg[i] == -1)
						g[i] = p[i - 1], tg[i] = 0;
				}
				if(p[i] < g[i - 1] && tg[i - 1] != -1){
					if(p[i - 1] < f[i] || tf[i] == -1)
						f[i] = p[i - 1], tf[i] = 1;
				}
			}
		}
		
		vector<int> fq, gq;
		if(tf[n] != -1 || tg[n] != -1){
			int cur = 0;
			if(tf[n] != -1) fq.pb(p[n]), cur = tf[n];
			else gq.pb(p[n]), cur = tg[n];
			for(int i = n - 1; i; --i){
				if(cur) gq.pb(p[i]), cur = tg[i];
				else fq.pb(p[i]), cur = tf[i];
			}
			reverse(all(fq));
			reverse(all(gq));
			puts("YES");
			printf("%d", (int)gq.size());
			for(int v : gq) printf(" %d", v);
			puts("");
			printf("%d", (int)fq.size());
			for(int v : fq) printf(" %d", v);
			puts("");
		}else puts("NO");
	}
	
#ifndef ONLINE_JUDGE
	system("pause");
#endif
	return 0;
}
