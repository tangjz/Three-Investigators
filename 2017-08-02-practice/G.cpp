#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000009
#define all(a) a.begin(), a.end()

const int maxn = 100100;
const int maxm = 5000100;
bool tag[maxn];
char s[maxm], str[maxm];
int ha[maxm];
set<int> st[maxn];
int ba[maxn];

int main(){
	int T, ca = 0;
	scanf("%d", &T);
	ba[0] = 1;
	for(int i = 1; i < maxn; ++i) ba[i] = ba[i - 1] * 2 % M;
	while(T--){
		int n;
		scanf("%d", &n);
		printf("Case #%d:\n", ++ca);
		vector<int> vec;
		memset(tag, 0, sizeof(tag));
		int last = 0;
		while(n--){
			scanf("%s", str);
			int l = strlen(str + 1);
			for(int i = 1; i <= l; ++i)
				s[i] = str[(i + last - 1) % l + 1];
			if(str[0] == '+'){
				int has = 0;
				for(int i = 1; i <= l; ++i)
					has = (has * 2 + s[i] - '0') % M;
				st[l].insert(has);
				if(!tag[l]) tag[l] = 1, vec.pb(l);
			}else{
				int cnt = 0;
				for(int i = 1; i <= l; ++i){
					ha[i] = (ha[i - 1] * 2 + s[i] - '0') % M;
					for(int v : vec){
						if(i - v < 0) continue;
						int has = (ha[i] - (ll)ha[i - v] * ba[v] % M + M) % M;
						if(st[v].find(has) != st[v].end()) cnt++;
					}
				}
				printf("%d\n", last = cnt);
			}
		}
		
		for(auto v : vec) st[v].clear();
	}
	
#ifndef ONLINE_JUDGE
	system("pause");
#endif
	return 0;
}
