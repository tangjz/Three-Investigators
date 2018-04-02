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

const int maxn = 111;
int T;
int n;
int x[maxn], y[maxn];
int sta[maxn];
int col[maxn];
int w[maxn];

inline int cross(int x, int y, int xx, int yy){
	return x * yy - y * xx;
}

inline int cross(int a, int b, int c){
	return cross(x[b] - x[a], y[b] - y[a], x[c] - x[a], y[c] - y[a]);
}

bool cmp(int i, int j){
	return x[i] != x[j] ? x[i] < x[j] : y[i] < y[j];
}

void output(){
	puts("YES");
	for(int i = 1; i <= n; ++i)
		putchar('A' + col[i]);
	puts("");
}

void work(){
	for(int i = 1; i <= n - 2; ++i)
		for(int j = i + 1; j <= n - 1; ++j)
			for(int k = j + 1; k <= n; ++k)
				if(cross(w[i], w[j], w[k]) == 0){
					col[w[i]] = col[w[k]] = 0;
					col[w[j]] = 1;
					output();
					return;
				}
	if(n == 3) { puts("NO"); return; }
	
	int top = 0;
	for(int i = 1; i <= n; ++i){
		while(top > 1 && cross(sta[top - 1], sta[top], w[i]) > 0) --top;
		sta[++top] = w[i];
	}
	int tmp = top;
	for(int i = n - 1; i >= 1; --i){
		while(top > tmp && cross(sta[top - 1], sta[top], w[i]) > 0) --top;
		sta[++top] = w[i];
	}
	
	--top;
	if(top > 3){
		for(int i = 1; i <= top; ++i) col[sta[i]] = 0;
		col[sta[1]] = col[sta[3]] = 1;
		output();
	}else{
		for(int i = 1; i <= n; ++i) col[i] = 0;
		for(int i = 1; i <= top; ++i)
			col[sta[i]] = 1;
		output();
	}
}

int main(){
	scanf("%d", &T);
	while(T--){
		scanf("%d", &n);
		for(int i = 1; i <= n; ++i) scanf("%d%d", x + i, y + i), w[i] = i;
		sort(w + 1, w + n + 1, cmp);
		if(n <= 2){
			puts("NO");
			continue;
		}
		work();
	}
	return 0;
}
