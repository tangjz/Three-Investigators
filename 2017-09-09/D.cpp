#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

struct point{
	int x, t;
	bool operator < (const point &R) const{
		return x < R.x || (x == R.x && t < R.t);
	}
}p[1100];

int N, K, L, T, ca;
int f[1100][1100], g[1100][1100];
int add[1100][1100], del[1100][1100];

int main(){
	scanf("%d", &T);
	while(T--){
		scanf("%d%d%d", &N, &L, &K);
		for(int i = 1; i <= N; ++i){
			scanf("%d%d", &p[i].x, &p[i].t);
		}
		++N;
		p[N].x = K, p[N].t = 0;
		++N;
		p[N].x = 0, p[N].t = 0;
		sort(p + 1, p + N + 1);
		/*
		for(int i = 1; i < N; ++i){
			del[i][i] = p[i].t - p[i].x;
			add[i][i] = p[i].t + p[i].x;
			for(int j = i + 1; j <= N; ++j){
				del[i][j] = max(del[i][j - 1], p[j].t - p[j].x);
				add[i][j] = max(add[i][j - 1], p[j].t + p[j].x);
			}
		}
		*/
		
		int mid = 1;
		while(p[mid].x != K || p[mid].t != 0) ++mid;
		
		for(int i = 1; i <= mid; ++i)
			for(int j = mid; j <= N; ++j)
				f[i][j] = g[i][j] = (1e9) + 7;
		f[1][N] = 0;
		for(int i = 1; i <= mid; ++i)
			for(int j = N; j >= mid; --j){
				if(f[i][j] < 1e9 && i < mid){
					f[i + 1][j] = min(f[i + 1][j], max(p[i + 1].t, f[i][j] + p[i + 1].x - p[i].x));
					g[i + 1][j] = min(g[i + 1][j], max(p[j].t, f[i][j] + p[j].x - p[i].x));
				}
				if(g[i][j] < 1e9 && j > mid){
					g[i][j - 1] = min(g[i][j - 1], max(p[j - 1].t, g[i][j] + p[j].x - p[j - 1].x));
					f[i][j - 1] = min(f[i][j - 1], max(p[i].t, g[i][j] + p[j].x - p[i].x));
				}
			}
		printf("Case #%d: %d\n", ++ca, min(f[mid][mid], g[mid][mid]));
	}
	return 0;
}
