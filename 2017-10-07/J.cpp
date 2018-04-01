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

int n, x;
int re[256];

int main(){
	scanf("%d", &n);
	for(int i = 0; i < 256; ++i)
		re[(i ^ (i << 1)) & 255] = i;
	for(int i = 1; i <= n; ++i){
		scanf("%d", &x);
		printf("%d ", re[x]);
	}
	
#ifndef ONLINE_JUDGE
	system("pause");
#endif
	return 0;
}
