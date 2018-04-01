#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

const int MAXN = 200005;
const int N = 26;

struct Palindromic_Tree{
	int next[MAXN][N];
	int fail[MAXN];
	int cnt[MAXN];
	int num[MAXN];
	int len[MAXN];
	int S[MAXN];
	int last;
	int n;
	int p;

	int newnode(int l){
		for(int i = 0; i < N; ++i) next[p][i] = 0;
		cnt[p] = 0;
		num[p] = 0;
		len[p] = l;
		return p++;
	}

	void init(){
		p = 0;
		newnode(0);
		newnode(-1);  
		last = 0;
		n = 0;
		S[n] = -1;
		fail[0] = 1;
	}

	int get_fail(int x){
		while(S[n - len[x] - 1] != S[n]) x = fail[x];
		return x;
	}

	void add(int c){
		c -= 'a';
		S[++n] = c;
		int cur = get_fail(last);
		if (!next[cur][c]){
			int now = newnode (len[cur] + 2);
			fail[now] = next[get_fail (fail[cur])][c];
			next[cur][c] = now;
			num[now] = num[fail[now]] + 1;
		}
		last = next[cur][c];
		cnt[last]++;
	}

	void count(){
		for (int i = p - 1; i >= 0; --i) cnt[fail[i]] += cnt[i];
	}
}T;

char s[100100];
int n;

int main(){
	scanf("%s", s);
	n = strlen(s);
	T.init();
	for(int i = 0; i < n; ++i) T.add(s[i]);
	T.count();
	ll ans = 0;
	for(int i = 2; i <= T.n; ++i)
		ans += (ll)T.cnt[i] * (T.cnt[i] - 1) / 2;
	printf("%lld\n", ans % M);
	return 0;
}
