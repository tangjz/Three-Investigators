#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

const int maxn = 5010;
int n;
int a[maxn][maxn];
char s[maxn];
int du[maxn], w[maxn];
int ress[maxn], rest[maxn];
bool vis[maxn];

int main(){
	freopen("powersum.in", "r", stdin);
	freopen("powersum.out", "w", stdout);
	scanf("%d", &n);
	for(int i = 0; i < n; ++i){
		scanf("%s", s);
		for(int j = 0; j < n; ++j){
			a[i][j] = s[j] - '0';
			if(a[i][j] == 1) du[j]++;
		}
	}
	for(int i = 0; i < n; ++i) w[i] = i;
	sort(w, w + n, [](const int &i, const int &j) { return du[i] < du[j]; });
	
	vector<int> q;
	int cnt = 0;
	for(int i = 0; i < n; ++i) ress[i] = -1e9;

	for(int i = 0; i < n; ++i){
		int x = w[i];
		for(int j = 0; j < n; ++j){
			if(a[j][x] && !vis[j]) ress[j] = n - (++cnt), vis[j] = 1;
			if(!a[j][x] && vis[j]){
				printf("NO\n");
				return 0;
			}
		}
		rest[x] = cnt - n;
	}
	printf("YES\n");
	for(int i = 0; i < n; ++i)
		printf("%d %d\n", ress[i], rest[i]);
	printf("0\n");
	/*
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
			if(!(a[i][j] == (ress[i] + rest[j] >= 0)))
				printf("%d %d\n", i, j);
	*/
	return 0;
}
