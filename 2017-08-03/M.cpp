#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

const int maxn = 100100;
const int B = 300, cntB = maxn / B + 5;
int b[cntB][cntB], c[maxn][cntB], mp[cntB][maxn];
int tb[cntB], tagb[cntB], tc[maxn], tagc[maxn], idx;
int fa[maxn], a[maxn];
int T, n, m;

int find(int x) { return x == fa[x] ? x : fa[x]  = find(fa[x]); }

inline void unbuild(int id){
	for(int i = id * B, r = min(n, (id + 1) * B); i < r; ++i){
		a[i] = a[find(i)];
		mp[id][a[i]] = 0;
	}
}

inline void build(int id){
	for(int i = id * B, r = min(n, (id + 1) * B); i < r; ++i){
		if(!mp[id][a[i]]) mp[id][a[i]] = i;
		fa[i] = mp[id][a[i]];
	}
}

int main(){
	freopen("1013.in", "r", stdin);
	freopen("1013.out", "w", stdout);
	scanf("%d", &T);
	while(T--){
		scanf("%d%d", &n, &m);
		memset(b, 0, sizeof(b));
		memset(c, 0, sizeof(c));
		for(int i = 0; i < n; ++i) scanf("%d", a + i);
		for(int i = 0; i < n; i += B){
			build(i / B);
			for(int j = i; j < i + B && j < n; ++j)
				for(int k = i; k < n; k += B){
					++b[a[j] / B][k / B];
					++c[a[j]][k / B];
				}
		}
		while(m--){
			static int ty, x, y, l, r;
			scanf("%d%d%d%d", &ty, &l, &r, &x); --l, --r;
			int lb = l / B, rb = r / B;
			if(ty == 1){
				scanf("%d", &y);
				int cntx = 0;
				for(int id = lb; id <= rb; ++id){
					if(l > id * B || r < (id + 1) * B - 1){
						int lt = max(l, id * B), rt = min(r, (id + 1) * B - 1);
						unbuild(id);
						for(int i = lt; i <= rt; ++i)
							if(a[i] == x) { cntx++; a[i] = y; }
						build(id);
					}else{
						if(mp[id][x]){
							int t = mp[id][x]; mp[id][x] = 0;
							if(!mp[id][y]) mp[id][y] = t, a[t] = y;
							else fa[t] = mp[id][y];
						}
						int tmp = c[x][id] - (id ? c[x][id - 1] + cntx : 0);
						cntx += tmp;
					}
					b[x / B][id] -= cntx;
					c[x][id] -= cntx;
					b[y / B][id] += cntx;
					c[y][id] += cntx;
				}
				for(int id = rb + 1; id * B < n; ++id){
					b[x / B][id] -= cntx;
					c[x][id] -= cntx;
					b[y / B][id] += cntx;
					c[y][id] += cntx;	
				}
			}else{
				//printf("12345\n");
				idx++;
				for(int i = l; i <= min(r, (lb + 1) * B - 1); ++i){
					a[i] = a[find(i)];
					if(tagb[a[i] / B] != idx) tagb[a[i] / B] = idx, tb[a[i] / B] = 0;
					if(tagc[a[i]] != idx) tagc[a[i]] = idx, tc[a[i]] = 0;
					++tb[a[i] / B];
					++tc[a[i]];
				}
				if(lb < rb){
					for(int i = rb * B; i <= r; ++i){
						a[i] = a[find(i)];
						if(tagb[a[i] / B] != idx) tagb[a[i] / B] = idx, tb[a[i] / B] = 0;
						if(tagc[a[i]] != idx) tagc[a[i]] = idx, tc[a[i]] = 0;
						++tb[a[i] / B];
						++tc[a[i]];
					}
				}
				rb--; if(lb > rb) lb--;
				for(int i = 0; i <= n; i += B){
					int tmp = (tagb[i / B] == idx ? tb[i / B] : 0) + b[i / B][rb] - b[i / B][lb];
					if(x <= tmp){
						for(int j = i; j < i + B; ++j){
							int tmp = (tagc[j] == idx ? tc[j] : 0) + c[j][rb] - c[j][lb];
							if(x <= tmp){
								//x = -1;
								printf("%d\n", j);
								break;
							}else x -= tmp;
						}
						break;
					}else x -= tmp;
				}
				//if(x != -1) printf("12345\n");
			}
		}
		for(int i = 0; i < n; i += B) unbuild(i / B);
	}
	
	return 0;
}
