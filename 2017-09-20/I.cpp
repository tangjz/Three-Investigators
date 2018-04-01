#include<bits/stdc++.h>
using namespace std;

int n, m;
char s[100101];
int tot, cnt[200101], son[200101][2], rt;
int ans;

void insert(int &t, int dp){
	if(!t) t = ++tot;
	++cnt[t];
	if(dp == m) return;
	insert(son[t][s[dp] - '0'], dp + 1);
}

void work(int t, int dp){
	if(!t) return;
	int k = s[dp] - '0';
	if(k == 0) work(son[t][1], dp + 1);
	else ans += cnt[son[t][1]], work(son[t][0], dp + 1);
}

int main(){
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; ++i){
		scanf("%s", s);
		ans = 0;
		work(rt, 0);
		insert(rt, 0);
		printf("%d\n", ans);
		fflush(stdout);
	}
	return 0;
}
