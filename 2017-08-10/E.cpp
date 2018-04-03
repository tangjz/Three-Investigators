#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

const int xx[] = {0, 0, 1, -1};
const int yy[] = {1, -1, 0, 0};

int f[2][1 << 8];
bool ban[8][8];
char mp[8][12];
int T, n, m;
int ans;

inline bool inmap(int x, int y){
	return x >= 0 && y >= 0 && x < n && y < m;
}

inline void add(int &a, int b){
	(a += b, a >= M) && (a -= M);
}

void dp(){
	memset(f, 0, sizeof(f));
	f[0][(1 << m) - 1] = 1;
	int pre = 0, now = 1;
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < m; ++j){
			memset(f[now], 0, sizeof(f[now]));
			for(int mask = 0; mask < 1 << m; ++mask){
				if(!f[pre][mask]) continue;
				if(ban[i][j]){
					if(mask >> j & 1) add(f[now][mask], f[pre][mask]);
				}else{
					if(j && (mask >> j & 1) && (~mask >> (j - 1) & 1))
						add(f[now][mask | (1 << (j - 1))], f[pre][mask]);
					if(~mask >> j & 1)
						add(f[now][mask | (1 << j)], f[pre][mask]);
					if(mask >> j & 1)
						add(f[now][mask ^ (1 << j)], f[pre][mask]);
				}
			}
			swap(pre, now);
		}
	add(ans, f[pre][(1 << m) - 1]);
}

void dfs(int x, int y){
	ban[x][y] = 1;
	dp();
	for(int d = 0; d < 4; ++d){
		int tx = x + 2 * xx[d], ty = y + 2 * yy[d];
		int gx = x + xx[d], gy = y + yy[d];
		if(!inmap(tx, ty) || ban[gx][gy] || ban[tx][ty]) continue;
		ban[gx][gy] = 1;
		dfs(tx, ty);
		ban[gx][gy] = 0;
	}
	ban[x][y] = 0;
}

int main(){
	scanf("%d", &T);
	while(T--){
		scanf("%d%d", &n, &m);
		memset(ban, 0, sizeof(ban));
		int start_x, start_y;
		for(int i = 0; i < n; ++i){
			scanf("%s", mp[i]);
			for(int j = 0; j < m; ++j)
				if(mp[i][j] == 'X') ban[i][j] = 1;			
				else if(mp[i][j] == '@') start_x = i, start_y = j;
		}
		ans = 0;
		dfs(start_x, start_y);
		printf("%d\n", ans);
	}
	
#ifndef ONLINE_JUDGE
	system("pause");
#endif
	return 0;
}
