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
int e[200100];
int tag[200100];

int main(){
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; ++i){
		scanf("%d", e + i);
		tag[e[i]] = 1;
	}
	reverse(e + 1, e + m + 1);
	for(int i = 1; i <= m; ++i){
		if(tag[e[i]] == 1) printf("%d\n", e[i]);
		tag[e[i]] = 2;
	}
	for(int i = 1; i <= n; ++i)
		if(!tag[i]) printf("%d\n", i);
	
#ifndef ONLINE_JUDGE
	system("pause");
#endif
	return 0;
}
