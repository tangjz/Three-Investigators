#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

int T, n, m;
int a[200100], b[200100];

int main(){
	scanf("%d", &T);
	while(T--){
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; ++i) scanf("%d", a + i);
		for(int i = 29; i >= 0; --i)
			if(m >> i & 1){
				memset(b, 0, sizeof(b));
				for(int j = 1; j <= n; ++j)
					if(j <= (1 << i))
						b[j] = a[j];
					else b[j] = b[j - (1 << i)] ^ a[j];
				memcpy(a, b, sizeof(b));
			}
		for(int i = 1; i <= n; ++i)
			printf("%d%c", a[i], " \n"[i == n]);
	}

	return 0;
}
