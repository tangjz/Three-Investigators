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

const int maxn = 100005;
int n, m, k;
int w[maxn], s[maxn], L[maxn];

int main(){
	scanf("%d%d%d", &n, &m, &k);
	for(int i = 1, j = 0; i <= n; ++i){
		scanf("%d", w + i), s[i] = s[i - 1] + w[i];
		while(s[i] - s[j + 1] > k) ++j;
		L[i] = j;
	}
	int ans = -1, j = 0, x, y = 0;
	for(int i = 1; i <= m; ++i){
		scanf("%d", &x);
		if(j + (x - y - 1) >= n){
			ans = y + (n - j);
			break;
		}
		j += x - y - 1;
		j = L[j];
		y = x;
	}
	if(ans == -1)
		ans = y + (n - j);
	printf("%d\n", ans);
	

	return 0;
}
