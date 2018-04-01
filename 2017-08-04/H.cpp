#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

int T, m, n;
int rx[110], ry[110], x[110], y[110];

int main(){
	int T, ca = 0;
	scanf("%d", &T);
	while(T--){
		scanf("%d", &m);
		for(int i = 1; i <= m; ++i) scanf("%d%d", rx + i, ry + i);
		scanf("%d", &n);
		printf("Case %d:\n", ++ca);
		for(int i = 1; i <= n; ++i){
			scanf("%d%d", x + i, y + i);
			int xx = min(x[i], y[i]), yy = max(x[i], y[i]);
			int ansx = -1, ansy = -1, ansk = -1;
			for(int j = 1; j <= m; ++j){
				int tx = min(rx[j], ry[j]), ty = max(rx[j], ry[j]);
				int d = max((xx + tx - 1) / tx, (yy + ty - 1) / ty);
				
				int dx = rx[j] * d, dy = ry[j] * d, k = 0;
				if(x[i] * y[i] != dx * dy) ++k;
				if(x[i] > dx || y[i] > dy) ++k;

				if(ansx == -1 || dx * dy < ansx * ansy|| (dx * dy == ansx * ansy && dx < ansx) || (dx == ansx && dy == ansy && k < ansk)){
					ansx = dx, ansy = dy, ansk = k;
				}
			}
			printf("%d %d %d\n", ansx, ansy, ansk);
		}
	}
	
	return 0;
}
