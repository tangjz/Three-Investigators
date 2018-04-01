#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define mkp make_pair
#define fi first
#define se second

map<string, int> mp;
int totcol;
int R;
int n;
char s[100];
double f[501][501][101];
int x[101], y[101], z[101];

inline int getID(string& str){
	if(mp.count(str)) return mp[str];
	else return mp[str] = ++totcol;
}

int main(){
	scanf("%d", &R);
	mp["END"] = 0;
	for(int i = 1; i <= R; ++i){
		scanf("%s", s);
		string str = s;
		x[i] = getID(str);
		scanf("%s", s);
		str = s;
		y[i] = getID(str);
		scanf("%s", s);
		str = s;
		z[i] = getID(str);
		//printf("ed: %d %d %d\n", x[i], y[i], z[i]);
	}
	int T;
	scanf("%d", &T);
	while(T--){
		scanf("%d", &n);
		string str;
		for(int i = 0, id; i < n; ++i){
			for(int j = 1; j <= totcol; ++j) f[i][i][j] = -1e60;
			while(scanf("%s", s), str = s, id = getID(str)){
				static double p;
				scanf("%lf", &p);
				f[i][i][id] = log(p);
			}
		}
		
		for(int len = 2; len <= n; ++len){
			for(int i = 0, j; i + len - 1 < n; ++i){
				j = i + len - 1;
				for(int k = 1; k <= totcol; ++k) f[i][j][k] = -1e60;

				for(int t = i; t < j; ++t){
					for(int k = 1; k <= R; ++k){
						static double l, r;
						l = f[i][t][x[k]], r = f[t + 1][j][y[k]];
						f[i][j][z[k]] = max(f[i][j][z[k]], l + r);
						l = f[i][t][y[k]], r = f[t + 1][j][x[k]];
						f[i][j][z[k]] = max(f[i][j][z[k]], l + r);
					}
				}
			}
		}
		
		pair<double, int> mx = mkp(-1e60, -1);
		for(int i = 1; i <= totcol; ++i){
			//printf("%d: %.5f\n", i, f[0][n - 1][i]);
			mx = max(mkp(f[0][n - 1][i], i), mx);
		}
		if(mx.fi < -1e40) puts("GAMEOVER");
		else{
			for(auto &&v : mp)
				if(v.se == mx.se){
					int l = v.fi.size();
					for(int i = 0; i < l; ++i) s[i] = (v.fi)[i];
					s[l] = 0;
					printf("%s\n", s);
				}
		}
	}
	return 0;
}
