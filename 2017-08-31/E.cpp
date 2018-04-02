#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

const int maxn = 100100;
int n, q;
unsigned a[maxn], pre1[maxn], pre2[maxn], pre3[maxn], suf1[maxn], suf2[maxn], suf3[maxn];

int main(){
	while(~scanf("%d%d", &n, &q)){
		pre1[0] = ~0;
		for(int i = 1; i <= n; ++i){
			scanf("%u", a + i);
			pre1[i] = pre1[i - 1] & a[i];
			pre2[i] = pre2[i - 1] | a[i];
			pre3[i] = pre3[i - 1] ^ a[i];
		}
		suf1[n + 1] = ~0;
		suf2[n + 1] = suf3[n + 1] = 0;
		for(int i = n; i >= 1; --i){
			suf1[i] = suf1[i + 1] & a[i];
			suf2[i] = suf2[i + 1] | a[i];
			suf3[i] = suf3[i + 1] ^ a[i];
		}
		while(q--){
			static int p;
			scanf("%d", &p);
			printf("%u %u %u\n", pre1[p - 1] & suf1[p + 1], pre2[p - 1] | suf2[p + 1], pre3[p - 1] ^ suf3[p + 1]);
		}
	}
	
#ifndef ONLINE_JUDGE
	system("pause");
#endif
	return 0;
}
