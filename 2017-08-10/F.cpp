#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

char mp[110][110];
int n, m;
int A[7], H[7];
ll As, Ds, Hs, Ms;
int Am, Dm, Hm, Mm;
int Ab, Db, Hb, Mb;
vector<int> touch[128];
ll atk_buff[128], def_buff[128], hp_buff[128], mp_buff[128];
bool vis[110][110];
ll f[128][21][21];
int T;

bool inmap(int x, int y){
	return x >= 0 && y >= 0 && x < n && y < m;
}

inline void ckmax(ll &a, ll b){
	(a < b) && (a = b);
}

void dfs(int x, int y, int mask){
	if(!inmap(x, y)) return;
	if(vis[x][y]) return;
	vis[x][y] = 1;
	if(mp[x][y] == '#') return;
	if(mp[x][y] >= '0' && mp[x][y] <= '6'){
		if(~mask >> (mp[x][y] - '0') & 1){
			touch[mask].pb(mp[x][y] - '0');
			return;
		}
	}
	if(mp[x][y] == 'A') atk_buff[mask] += Ab;
	else if(mp[x][y] == 'D') def_buff[mask] += Db;
	else if(mp[x][y] == 'H') hp_buff[mask] += Hb;
	else if(mp[x][y] == 'M') mp_buff[mask] += Mb;
	dfs(x - 1, y, mask);
	dfs(x + 1, y, mask);
	dfs(x, y - 1, mask);
	dfs(x, y + 1, mask);
}

int main(){
	freopen("1006.in", "r", stdin);
	freopen("1006.out", "w", stdout);
	scanf("%d", &T);
	while(T--){
		scanf("%d%d", &n, &m);
		int start_x, start_y;
		for(int i = 0; i < n; ++i){
			scanf("%s", mp[i]);
			for(int j = 0; j < m; ++j)
				if(mp[i][j] == 'S') 
					start_x = i, start_y = j;
		}
		for(int i = 0; i < 7; ++i)
			scanf("%d%d", A + i, H + i);
		scanf("%lld%lld%lld%lld", &As, &Ds, &Hs, &Ms);
		scanf("%d%d%d%d", &Am, &Dm, &Hm, &Mm);
		scanf("%d%d%d%d", &Ab, &Db, &Hb, &Mb);
		memset(atk_buff, 0, sizeof(atk_buff));
		memset(def_buff, 0, sizeof(def_buff));
		memset(hp_buff, 0, sizeof(hp_buff));
		memset(mp_buff, 0, sizeof(mp_buff));
		for(int mask = 0; mask < 1 << 7; ++mask){
			touch[mask].clear();
			memset(vis, 0, sizeof(vis));
			dfs(start_x, start_y, mask);			
			mp_buff[mask] += Ms;
		}
		
		memset(f, 0, sizeof(f));
		As += atk_buff[0];
		Ds += def_buff[0];
		Hs += hp_buff[0];
		Ms = mp_buff[0];
		for(int x = 0; x <= Ms / Mm && x <= 20; ++x)
			for(int y = 0; x + y <= Ms / Mm && y <= 20; ++y){
				int z = Ms / Mm - x - y;
				ckmax(f[0][min(As + x * Am, 20LL)][min(Ds + y * Dm, 20LL)], Hs + (ll)z * Hm);
			}
		for(int mask = 0; mask < 1 << 7; ++mask)
			for(int i = 1; i <= 20; ++i)
				for(int j = 0; j <= 20; ++j)
					if(f[mask][i][j] > 0){
						for(int v : touch[mask]){
							int round = (H[v] + i - 1) / i;
							int dec = round * max(A[v] - j, 0);
							if(dec >= f[mask][i][j]) continue;
							
							int tmask = mask | 1 << v;
							ll atk = atk_buff[tmask] - atk_buff[mask] + i;
							ll def = def_buff[tmask] - def_buff[mask] + j;
							ll hp = hp_buff[tmask] - hp_buff[mask] + f[mask][i][j] - dec;
							ll magic = mp_buff[tmask] / Mm - mp_buff[mask] / Mm;
							for(int x = 0; x <= magic && x <= 20; ++x)
								for(int y = 0; x + y <= magic && y <= 20; ++y){
									int z = magic - x - y;
									ckmax(f[tmask][min(atk + x * Am, 20LL)][min(def + y * Dm, 20LL)], hp + (ll)z * Hm);
								}
						}
					}
		ll ans = 0;
		for(int i = 1; i <= 20; ++i)
			for(int j = 0; j <= 20; ++j)
				ans = max(ans, f[127][i][j]);
		printf("%lld\n", ans ? ans : -1);
	}
	return 0;
}
