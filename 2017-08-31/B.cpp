#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

const int inf = 1e9;

const int maxp = 150000 * 20;
int rt[51];
int tot;
int tr[maxp], ls[maxp], rs[maxp];

void insert(int &t, int l, int r, int x, int v){
	if(!t) t = ++tot, ls[t] = rs[t] = 0, tr[t] = inf;
	tr[t] = min(tr[t], v);
	if(l == r) return;
	int mid = (l + r) >> 1;
	if(x <= mid) insert(ls[t], l, mid, x, v);
	else insert(rs[t], mid + 1, r, x, v);
}

int ask(int t, int l, int r, int x, int y){
	if(!t) return inf;
	if(x <= l && y >= r) return tr[t];
	int mid = (l + r) >> 1;
	if(y <= mid) return ask(ls[t], l, mid, x, y);
	else if(x > mid) return ask(rs[t], mid + 1, r, x, y);
	else return min(ask(ls[t], l, mid, x, y), ask(rs[t], mid + 1, r, x, y));
}

int main(){
	int ty;
	while(scanf("%d", &ty), ty != 3){
		if(ty == 0){
			memset(rt, 0, sizeof(rt));
			tot = 0;
		}else if(ty == 1){
			int x, y, c;
			scanf("%d%d%d", &x, &y, &c);
			insert(rt[c], 1, 1000000, y, x);
		}else{
			int x, y, yy;
			scanf("%d%d%d", &x, &y, &yy);
			int res = 0;
			for(int i = 0; i <= 50; ++i)
				if(ask(rt[i], 1, 1000000, y, yy) <= x) ++res;
			printf("%d\n", res);
		}
	}
	
#ifndef ONLINE_JUDGE
	system("pause");
#endif
	return 0;
}
