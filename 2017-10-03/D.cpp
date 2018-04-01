#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define pii pair<int, int>
#define B 9173
#define M 1000000007
#define all(a) a.begin(), a.end()

char s[5005], t[5005];
int n, m;
unordered_map<int, int> mp[4005];
int base[26], rd[26];

void solve(){
	int ans = 0;
	for(int i = 0; i < n; ++i){
		int has = 0, thas = 1;
		for(int j = i; j < n; ++j){
			has = (has + base[s[j] - 'a']) % M;
			thas = (ll)thas * rd[s[j] - 'a'] % M;
			mp[j - i][has] = thas;
		}
	}
	for(int i = 0; i < m; ++i){
		int has = 0, thas = 1;
		for(int j = i; j < m; ++j){
			has = (has + base[t[j] - 'a']) % M;
			thas = (ll)thas * rd[t[j] - 'a'] % M;
			if(mp[j - i].count(has) && mp[j - i][has] == thas) ans = max(ans, j - i + 1);
		}
	}
	printf("%d\n", ans);
}

int main(){
	srand(time(0));
	scanf("%s", s);
	scanf("%s", t);
	n = strlen(s);
	m = strlen(t);
	base[0] = 1;
	for(int i = 1; i < 26; ++i)
		base[i] = (ll)base[i - 1] * B % M;
	for(int i = 0; i < 26; ++i)
		rd[i] = rand() % (M - 1) + 1;
	solve();
	
#ifndef ONLINE_JUDGE
	system("pause");
#endif
	return 0;
}
