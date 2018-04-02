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

int n, m, q;
int p[111], tag[111];

int main(){
	while(~scanf("%d%d", &n, &m)){
		for(int i = 1; i <= n; ++i)
			scanf("%d", p + i), tag[i] = 0;
		scanf("%d", &q);
		for(int i = 1; i <= q; ++i){
			int x; scanf("%d", &x); ++x;
			tag[x] = 1;
		}
		int lim = n, sum = !tag[n];
		while(sum < m) sum += !tag[--lim];
		int ans = 1e9, pp, qq;
		for(int i = 1; i <= lim; ++i)
			if(!tag[i]){
				for(int j = i + 1, k = 1; j <= n; ++j){
					k += !tag[j];
					if(k > m) break;
					if(!tag[j]){
						if(p[i] + p[j] < ans) ans = p[i] + p[j], pp = i, qq = j;
					}
				}
			}
		printf("%d %d\n", pp - 1, qq - 1);
	}
	return 0;
}
