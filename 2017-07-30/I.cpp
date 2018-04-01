#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define ull unsigned long long
#define M 1000000007
#define all(a) a.begin(), a.end()

const int maxn = 100100;
const int base = 277;
int m, l;
char s[maxn];
ull has[maxn], b[maxn];
map<ull, int> mp;

int main(){
	b[0] = 1;
	for(int i = 1; i < maxn; ++i) b[i] = b[i - 1] * base;
	while(~scanf("%d%d", &m, &l)){
		scanf("%s", s + 1);
		int n = strlen(s + 1);
		for(int i = 1; i <= n; ++i) has[i] = has[i - 1] * base + s[i];
		int ans = 0;
		for(int i = 1; i <= l; ++i){
			int pre_max = 0;
			mp.clear();
			for(int j = i, k = 1; j + l - 1 <= n; j += l, ++k){
				ull now = has[j + l - 1] - has[j - 1] * b[l];
				pre_max = max(pre_max, mp[now]);
				mp[now] = j;
				if(k >= m && pre_max < j - (m - 1) * l) ans++;
			}
		}

		printf("%d\n", ans);
	}
	
	return 0;
}
