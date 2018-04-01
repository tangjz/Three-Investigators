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

const int maxn = 505;
int A, B, n, n1, n2;
int vis[maxn], inx;
int a[maxn], b[maxn], p[maxn];
bool g[maxn][maxn];

bool find(int x){
	for(int i = 1; i <= n; ++i)
		if(vis[i] < inx && g[x][i]){
			vis[i] = inx;
			if(!p[i] || find(p[i])){
				p[i] = x;
				return 1;
			}
		}
	return 0;
}

void work(){
	for(int i = 1; i <= n; ++i){
		++inx;
		if(!find(i)){
			puts("Liar");
			return;
		}
	}
	puts("No reason");
	for(int i = 1; i <= n; ++i)
		printf("%d %d\n", a[p[i]], b[i]);
}

int main(){
	scanf("%d%d", &A, &B);
	scanf("%d", &n);
	for(int i = 1, x, y; i <= n; ++i){
		scanf("%d%d", &x, &y);
		if(y == 0) a[++n1] = x;
		else b[++n2] = x;
	}
	n >>= 1;
	assert(n1 == n && n2 == n);
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= n; ++j)
			g[i][j] = a[i] < b[j] && (b[j] - a[i] >= A || b[j] - a[i] <= B);
	
	work();
	
	return 0;
}
