#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

int T;
int n;
ll base[15];
char s[100100], t[20];
int c[100100];
ll h[100100];
int ls, lt;

inline void add(int x, int v){
	++x;
	for(; x <= ls; x += x & -x)
		c[x] += v;
}

inline int ask(int x){
	++x;
	int res = 0;
	for(; x; x -= x & -x)
		res += c[x];
	return res;
}

int main(){
	scanf("%d", &T);
	base[0] = 1;
	for(int i = 1; i < 10; ++i)
		base[i] = base[i - 1] * 26;
	while(T--){
		scanf("%d", &n);
		scanf("%s", s);
		scanf("%s", t);
		ls = strlen(s), lt = strlen(t);
		ll thas = 0;
		for(int i = 0; i < lt; ++i)
			thas = thas * 26 + (t[i] - 'A');
		//printf("t: %lld\n", thas);
		memset(c, 0, sizeof(int) * (ls + 1));
		for(int i = lt - 1; i < ls; ++i){
			h[i] = 0;
			for(int j = 0; j < lt; ++j)
				h[i] = h[i] + base[j] * (s[i - j] - 'A');
			if(h[i] == thas) add(i, 1);
			//printf("%d: %lld\n", i, h[i]);
		}
		while(n--){
			scanf("%s", t);
			if(t[0] == 'Q'){
				static int l, r;
				scanf("%d%d", &l, &r); --l, --r;
				if(l + lt - 1 > r){
					printf("0\n");					
				}else{
					printf("%d\n", ask(r) - ask(l + lt - 2));
				}
			}else{
				static int x;
				scanf("%d%s", &x, t); --x;
				for(int i = 0; i < lt && x + i < ls; ++i){
                    if(x + i < lt - 1) continue;
					if(h[x + i] == thas) add(x + i, -1);
					h[x + i] -= base[i] * (s[x] - 'A');
					h[x + i] += base[i] * (t[0] - 'A');
					if(h[x + i] == thas) add(x + i, 1);
				}
				s[x] = t[0];
			}
		}
        printf("\n");
	}
	return 0;
}
