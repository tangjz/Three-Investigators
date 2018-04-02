#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

int T, m;
char s[5010];

int main(){
	scanf("%d", &T);
	while(T--){
		scanf("%d", &m);
		scanf("%s", s + 1);
		int n = strlen(s + 1);
		int ans = 0;
		for(int ii = n - 1; ii >= 1; --ii){
			int w = 0, l = 0;
			for(int j = ii + 1, i = ii; j <= n && i >= 1; ++j, --i){
				w += abs(s[i] - s[j]); ++l;
				while(w > m) --l, w -= abs(s[i + l] - s[j - l]);
				ans = max(ans, l);
			}
			w = 0, l = 0;
			for(int j = ii + 2, i = ii; j <= n && i >= 1; ++j, --i){
				w += abs(s[i] - s[j]); ++l;
				while(w > m) --l, w -= abs(s[i + l] - s[j - l]);
				ans = max(ans, l);
			}
		}
		printf("%d\n", ans);
	}
	
	return 0;
}
