#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define pii pair<int, int>
#define M 1000000007
#define all(a) a.begin(), a.end()

const int maxn = 1005;
struct Point{
	int x, y;
	Point(int x = 0, int y = 0) : x(x), y(y) {}
	void input(){
		scanf("%d%d", &x, &y);
	}
	Point operator - (const Point &R) const{
		return Point(x - R.x, y - R.y);
	}
	bool operator < (const Point &R) const{
		if(x == R.x) return y < R.y;
		else return x < R.x;
	}
	int operator ^ (const Point &R) const{
		return x * R.y - y * R.x;
	}
	bool operator == (const Point &R) const{
		return x == R.x && y == R.y;
	}
}wel[maxn], loc[maxn];
int w, p;
int vis[maxn];
int from[maxn];
bool flag;
vector<int> g[maxn];

bool SegmentProperIntersection(Point a1, Point a2, Point b1, Point b2){
	int c1 = (a2 - a1) ^ (b1 - a1);
	int c2 = (a2 - a1) ^ (b2 - a1);
	if(c1 == 0 && c2 == 0){
		if(a2 < a1) swap(a1, a2);
		if(b2 < b1) swap(b1, b2);
		return max(a1, b1) < min(a2, b2) || max(a1, b1) == min(a2, b2);
	}
	int c3 = (b2 - b1) ^ (a1 - b1);
	int c4 = (b2 - b1) ^ (a2 - b1);
	return (ll)c1 * c2 <= 0 && (ll)c3 * c4 <= 0;
}

void dfs(int t, int c){
	if(vis[t] != -1){
		if(vis[t] != c) flag = 1;
		return;
	}
	vis[t] = c;
	for(int v : g[t]) dfs(v, c ^ 1);
}

int main(){
	scanf("%d%d", &w, &p);
	for(int i = 1; i <= w; ++i) wel[i].input();
	for(int i = 1; i <= p; ++i){
		scanf("%d", &from[i]);
		loc[i].input();			
	}
	for(int i = 1; i <= p; ++i)
		for(int j = i + 1; j <= p; ++j)
			if(from[i] != from[j])
				if(SegmentProperIntersection(wel[from[i]], loc[i], wel[from[j]], loc[j])){
					g[i].pb(j);
					g[j].pb(i);
					//printf("%d %d\n", i, j);
				}
	
	memset(vis, -1, sizeof(vis));
	for(int i = 1; i <= p; ++i)
		if(vis[i] == -1) dfs(i, 0);
	
	printf("%s\n", flag ? "impossible" : "possible");
#ifndef ONLINE_JUDGE
	system("pause");
#endif
	return 0;
}

