#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

const int maxn = 2000100;
int n, len;
int p[maxn];
int c[maxn], tag[maxn], res1[maxn], res2[maxn];
char s[maxn], str[maxn];

void add(int x, int v){
	x = min(x, len);
	for(; x; x -= x & -x) c[x] = max(c[x], v);
}

int ask(int x){
	int res = 0;
	for(; x <= len; x += x & -x) res = max(res, c[x]);
	return res;
}

void work(int res[]){
	int now = 0;
	for(int i = 1, j = n + 1; j <= len; ++i, ++j){
		int x = min(n, p[i] - 1);
		add(i - x + 2 * n, x);
		tag[i - x + 2 * n] = max(tag[i - x + 2 * n], x);
		
		now = max(now - 1, tag[j]);
		res[j] = max(ask(j), now);
	}
}

int main(){
	scanf("%d", &n);
	scanf("%s", str + 1);
	s[0] = '%';  
	s[len = 1] = '#';
	for(int i = 1; i <= n * 2; ++i){
    s[++len] = str[i <= n ? i : i - n];
    s[++len] = '#';
	}
	int id = 0, mx = 0;
	for(int i = 1; i <= len; ++i){
    p[i] = mx > i ? min(p[id + id - i], mx - i) : 1;
    while(s[i + p[i]] == s[i - p[i]]) ++p[i];
    if(i + p[i] > mx)
			mx = i + p[i], id = i;
	}
	
	work(res1);
	reverse(p + 1, p + len + 1);	
	memset(c, 0, sizeof(c));
	memset(tag, 0, sizeof(tag));
	work(res2);
	for(int i = 1; i <= n; ++i)
		printf("%d\n", max(res1[2 * (i + n) - 1], res2[len - 2 * i + 2]));
	
	return 0;
}
