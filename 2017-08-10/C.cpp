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
vector<int> g[100100];
int a[100100];
int w[100100];
int tag[100100];
int n;

int main(){
	scanf("%d", &T);
	n = 100000;
	for(int i = 2; i <= n; ++i) 
		for(int j = i; j <= n; j += i)
			g[j].pb(i);
	while(T--){
		scanf("%d", &n);
		for(int i = 1; i <= n; ++i)
			scanf("%d", a + i), w[i] = i;
		sort(w + 1, w + n + 1, [](int i, int j) { return a[i] > a[j]; });
		memset(tag, 0, sizeof(tag));
		for(int i = 1; i <= n; ++i)
			for(int j : g[w[i]])
				if(tag[j] == i - 1) tag[j] = i;
		for(int i = 2; i <= n; ++i)
			printf("%d%c", a[w[tag[i] + 1]], " \n"[i == n]);
	}
	
	return 0;
}
