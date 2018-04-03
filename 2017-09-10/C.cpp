#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

const int B = 200000;
typedef bitset<2 * B> Bit;

int T, n, a[95];
Bit f[2][95];

Bit trans(Bit &b, int x){
	if(x >= 0) return b << x;
	else return b >> (-x);
}

int main(){
	while(~scanf("%d", &n)){
		for(int i = 1; i <= n; ++i) scanf("%d", a + i);
		for(int i = 1; i <= n + 1; ++i)
			f[0][i].reset(), f[0][i].set(B);
		int now = 0, pre = 1;
		for(int len = 2; len <= n; len += 2){
			swap(pre, now);
			for(int i = 1; i + len - 1 <= n; ++i){
				int l = i, r = i + len - 1, tmp = max(a[l], a[r]);
				if(a[l] >= a[r]) ++l; else --r;
				f[now][i] = trans(f[pre][l], tmp - a[r]) | 
					trans(f[pre][l + 1], tmp - a[l]);
			}
		}
		int res = 1;
		while(res < B && !f[now][1][res + B]) ++res;
		if(res < B) printf("%d\n", res);
		else printf("The child will be unhappy...\n");
	}
	
#ifndef ONLINE_JUDGE
	system("pause");
#endif
	return 0;
}
