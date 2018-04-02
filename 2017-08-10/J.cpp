#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

int T, n, k;
int f[510];
vector<int> g[510];
bool flag;

void dfs(int t){
	f[t] = 1;
	for(int v : g[t]){
		dfs(v);
		if(f[v]){
			if(f[t]) f[t]--;
			else flag = 0;
		}
	}
}

int main(){
	scanf("%d", &T);
	while(T--){
		scanf("%d%d", &n, &k);
		for(int i = 1; i <= n; ++i) g[i].clear();
		for(int i = 1; i < n; ++i){
			int u;
			scanf("%d", &u);
			g[u].pb(i + 1);
		}
		if(n & 1){
			printf("Alice\n");
			continue;
		}
		if(k < n / 2 - 1){
			printf("Alice\n");
			continue;
		}
		flag = 1;
		dfs(1);
		printf("%s\n", flag ? "Bob" : "Alice");
	}
	
	return 0;
}
