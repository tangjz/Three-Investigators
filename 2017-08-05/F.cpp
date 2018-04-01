#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

pair<int, int> ed[24];
int rig[4][4], dow[4][4];
bool tag[24];
int p[24], re[24];
int squ[24][2][3];
bool ok[24][2];
int n, T;
int c[30];
pair<int, int> f[1 << 12];
int res[2];

int main(){
	int ca = 0;
	scanf("%d", &T);
	for(int i = 0, tt = 0; i < 4; ++i)
		for(int j = 0; j < 4; ++j){
			if(j < 3){
				ed[tt++] = mkp(i * 4 + j, i * 4 + j + 1);
				rig[i][j] = tt - 1;
			}
			if(i < 3){
				ed[tt++] = mkp(i * 4 + j, (i + 1) * 4 + j);
				dow[i][j] = tt - 1;
			}
		}
	for(int i = 0; i < 4; ++i)
		for(int j = 0; j < 4; ++j){
			if(j < 3){
				if(i){
					ok[rig[i][j]][0] = 1;
					squ[rig[i][j]][0][0] = dow[i - 1][j];
					squ[rig[i][j]][0][1] = rig[i - 1][j];
					squ[rig[i][j]][0][2] = dow[i - 1][j + 1];
				}
				if(i < 3){
					ok[rig[i][j]][1] = 1;
					squ[rig[i][j]][1][0] = dow[i][j];
					squ[rig[i][j]][1][1] = rig[i + 1][j];
					squ[rig[i][j]][1][2] = dow[i][j + 1];
				}
			}
			if(i < 3){
				if(j){
					ok[dow[i][j]][0] = 1;
					squ[dow[i][j]][0][0] = rig[i][j - 1];
					squ[dow[i][j]][0][1] = dow[i][j - 1];
					squ[dow[i][j]][0][2] = rig[i + 1][j - 1];
				}
				if(j < 3){
					ok[dow[i][j]][1] = 1;
					squ[dow[i][j]][1][0] = rig[i][j];
					squ[dow[i][j]][1][1] = dow[i][j + 1];
					squ[dow[i][j]][1][2] = rig[i + 1][j];
				}
			}
		}
	
	
	while(T--){
		scanf("%d", &n);
		int m = 24 - n;
		memset(tag, 0, sizeof(tag));
		res[0] = res[1] = 0;
		for(int i = 1; i <= n; ++i){
			static int x, y;
			scanf("%d%d", &x, &y);
			if(x > y) swap(x, y);
			--x, --y;
			for(int j = 0; j < 24; ++j)
				if(x == ed[j].fi && y == ed[j].se){
					tag[j] = 1;
					c[i] = j;
				}
			//printf("%d\n", c[i]);
			int cnt = 0;
			for(int k = 0; k < 2; ++k)
				if(ok[c[i]][k]){
					int tmp = 0;
					for(int l = 0; l < 3; ++l)
						tmp += tag[squ[c[i]][k][l]];
					if(tmp == 3) cnt++;
				}
			res[i & 1] += cnt;
		}
		for(int i = 0, j = 0; i < 24; ++i)
			if(!tag[i]) p[i] = j, re[j] = i, j++;
		f[(1 << m) - 1] = mkp(0, 0);
		for(int i = (1 << m) - 2; i >= 0; --i){
			f[i] = mkp(0, 0);
			for(int j = 0; j < m; ++j)
				if(!((i >> j & 1))){
					int ti = i | (1 << j);
					int cnt = 0;
					for(int k = 0; k < 2; ++k)
						if(ok[re[j]][k]){
							int tmp = 0;
							for(int l = 0; l < 3; ++l)
								tmp += tag[squ[re[j]][k][l]] || (i >> p[squ[re[j]][k][l]] & 1);
							if(tmp == 3) cnt++;
						}
					f[i] = max(f[i], mkp(cnt + f[ti].se, f[ti].fi));
				}
		}
		res[n & 1] += f[0].se;
		res[!(n & 1)] += f[0].fi;
		printf("Case #%d: %s\n", ++ca, res[1] > res[0] ? "Tom200" : "Jerry404");
	}
	
	return 0;
}
