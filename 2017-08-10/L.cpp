#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

int T, n, W, pw, dw;
ll g[100100][18];
int f[100100][18];
int a[100100], pre[100100], nex[100100];
int Q;

int main(){
	freopen("1012.in", "r", stdin);
	freopen("1012.out", "w", stdout);
	scanf("%d", &T);
	while(T--){
		scanf("%d%d%d%d", &n, &W, &dw, &pw);
		dw = W - pw - dw;
		for(int i = 1; i <= n; ++i) scanf("%d", a + i), g[i][0] = a[i];
		
		for(int j = 1; j <= 16; ++j)
			for(int i = 1; i + (1 << j) - 1 <= n; ++i)
				g[i][j] = g[i][j - 1] + g[i + (1 << (j - 1))][j - 1] + 1;
		
		int now = 0, line = 0;
		for(int i = 1; i <= n; ++i){
			if(now < a[i]) ++line, now = W;
			now -= a[i] + 1;
			pre[i] = line;
		}
		now = 0, line = 0;
		for(int i = n; i >= 1; --i){
			if(now < a[i]) ++line, now = W;
			now -= a[i] + 1;
			nex[i] = line;
		}
		for(int i = 1; i <= n; ++i){
			int now = pw, x = i;
			for(int j = 16; j >= 0; --j)
				if(x + (1 << j) - 1 <= n && g[x][j] <= now) now -= g[x][j] + 1, x += 1 << j;
			now = dw;
			for(int j = 16; j >= 0; --j)
				if(x + (1 << j) - 1 <= n && g[x][j] <= now) now -= g[x][j] + 1, x += 1 << j;
			f[i][0] = x - i;
		}
		
		memset(f[n + 1], 0, sizeof(f[n + 1]));
		for(int j = 1; j <= 16; ++j)
			for(int i = 1; i <= n; ++i)
				f[i][j] = f[i][j - 1] + f[i + f[i][j - 1]][j - 1];
		
		nex[n + 1] = 0;
		scanf("%d", &Q);
		while(Q--){
			int x, h;
			scanf("%d%d", &x, &h);
			if(pre[n] <= x - 1){
				printf("%d\n", pre[n] + h);
				continue;
			}
			int l = 0, r = n + 1;
			while(l + 1 < r){
				int d = (l + r) >> 1;
				if(pre[d] <= x - 1) l = d;
				else r = d;
			}
			for(int i = 16; i >= 0; --i)
				if(h >> i & 1)
					r += f[r][i];
			printf("%d\n", x + h - 1 + nex[r]);
		}
	}
	
	return 0;
}
