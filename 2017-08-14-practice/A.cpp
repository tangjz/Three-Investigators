#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

const int maxn = 1010;
int n;
int x[maxn], y[maxn];
int f[maxn][maxn], s[maxn][maxn];

bool ckmin(int &a, int b){
	return a > b ? a = b, 1 : 0;
}

int main(){
	while(~scanf("%d", &n)){
		for(int i = 1; i <= n; ++i) scanf("%d%d", x + i, y + i);
		memset(f, 127, sizeof(f));
		for(int len = 1; len <= n; ++len)
			for(int i = 1; i + len - 1 <= n; ++i){
				int j = i + len - 1;
				if(i == j) f[i][j] = 0, s[i][j] = i;
				else{
					for(int k = s[i][j - 1]; k <= s[i + 1][j] && k < j; ++k)
						if(ckmin(f[i][j], f[i][k] + f[k + 1][j] + x[k + 1] - x[i] + y[k] - y[j]))
							s[i][j] = k;
				}
			}
		printf("%d\n", f[1][n]);
	}
	return 0;
}
