#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

const int N = 200001;
int pri[N];
bool nop[N + 100];
int a, b, tot;

int f[N + 100], g[N + 100];
int c[2][N + 100];

void init(){
	for(int i = 2; i <= N; ++i){
		if(!nop[i]) pri[++tot] = i;
		for(int j = 1; j <= tot && pri[j] * i <= N; ++j){
			nop[pri[j] * i] = 1;
			if(i % pri[j] == 0) break;
		}
	}
}

void add(int k, int x, int v){
	x -= a - 1;
	for(; x <= b - a + 1; x += x & -x) c[k][x] = (c[k][x] + v) % M;
}

int ask(int k, int x){
	x -= a - 1;
	int res = 0;
	for(; x; x -= x & -x) res = (res + c[k][x]) % M;
	return res;
}

int main(){
	freopen("jumping.in", "r", stdin);
	freopen("jumping.out", "w", stdout);
	init();
	scanf("%d%d", &a, &b);
	g[1] = 1;
	for(int i = a; i <= b; ++i){
		int li = sqrt(i + 0.1);
		int p = 0;
		for(int j = 1; j <= tot && pri[j] <= li; ++j)
			if(i % pri[j] == 0){
				p = pri[j];
				break;
			}
		f[i - a + 1] = ask(1, i);
		add(0, i, f[i - a + 1]);

		if(!p) continue;
		int L = max(a, i - i / p), R = min(i - 1, i - p);
		if(L <= R) g[i - a + 1] = (ask(0, R) - ask(0, L - 1) + M) % M;

		L = max(i + 1, i + p), R = min(b, i + i / p);
		if(L <= R) add(1, L, g[i - a + 1]), add(1, R + 1, M-g[i - a + 1]);
	}
	
	printf("%d\n", (f[b - a + 1] + g[b - a + 1]) % M);
	
	return 0;
}
