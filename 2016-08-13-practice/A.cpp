#include<bits/stdc++.h>
using namespace std;
#define pb push_back

bitset<4001> f[31][4001], ff[4001];
vector<int> T[31];
int n;
vector<int> a[3];

int main(){
	f[0][0].set(0);
	scanf("%d", &n);
	for(int i = 1, x; i <= n; ++i){
		scanf("%d", &x);
		T[x].pb(i);		
	}
	int sum = 0;
	for(int i = 1; i <= 30; ++i){
		memcpy(f[i], f[i - 1], sizeof(f[i]));
		for(int j = 1; j <= T[i].size(); ++j){
			memcpy(ff, f[i], sizeof(f[i]));
			sum += i;
			for(int k = 0; k <= min(sum, 4000); ++k){
				f[i][k] = ff[k] | ff[k] << i;
				if(k >= i) f[i][k] |= ff[k - i];
			}
		}
	}
	
	int ans = 1e9, ansj, ansk;
	for(int i = 0; i <= 4000; ++i)
		for(int j = 0; j <= 4000; ++j)
			if(f[30][i].test(j)){
				int k = sum - i - j;
				if(max({i, j, k}) - min({i, j, k}) < ans){
					ans = max({i, j, k}) - min({i, j, k});
					ansj = i;
					ansk = j;
				}
		}
	
	for(int i = 30; i >= 1; --i){
		bool flag = 0;
		for(int j = 0; j <= T[i].size() && !flag; ++j)
			for(int k = 0; j + k <= T[i].size() && !flag; ++k)
				if(ansj >= i * j && ansk >= i * k && f[i - 1][ansj - i * j].test(ansk - i * k)){
					flag = 1;
					ansj -= i * j;
					ansk -= i * k;
					for(int l = 0; l < T[i].size(); ++l)
						if(l < j) a[0].pb(T[i][l]);
						else if(l < j + k) a[1].pb(T[i][l]);
						else a[2].pb(T[i][l]);
				}
	}
	
	printf("%d\n", ans);
	for(int i = 0; i < 3; ++i){
		printf("%d", (int)a[i].size());
		for(int v : a[i]) printf(" %d", v);
		puts("");
	}
	
	return 0;
}
