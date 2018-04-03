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

int n, m;
double a;
int v[100];
char s[1000];

int main(){
	freopen("m.in", "r", stdin);
	freopen("m.out", "w", stdout);

	scanf("%d%lf\n", &n, &a);
	
	int m = 0;
	while(gets(s)){
		for(int i = 0; s[i]; ++i){
			if(s[i] >= '0' && s[i] <= '9'){
				int num = s[i] - '0';
				while(s[i + 1] >= '0' && s[i + 1] <= '9')
					num = num * 10 + (s[++i] - '0');
				v[m] |= 1 << (num - 1);
				//	printf("%d ", num);
			}
		}
		//puts("");
		m++;
	}
	int ans = 0;
	int lim = a * m;
	//printf("%d\n", lim);
	for(int i = 1; i < 1 << n; ++i){
		int tmp = 0;
		for(int j = 0; j < m; ++j){
			tmp += (i & v[j]) == i;
		}
		//printf("%d: %d\n", i, tmp);
		ans += tmp >= lim;
	}
	printf("%d\n", ans);
	
	return 0;
}
