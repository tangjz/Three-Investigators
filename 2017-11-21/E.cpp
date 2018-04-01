#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define mkp make_pair
#define fi first
#define se second

int n, m, x;
int c[111];

int main(){
	while(~scanf("%d%d%d", &m, &n, &x)){
		priority_queue<pair<int, int> > q;
		for(int i = 1; i <= n; ++i){
			scanf("%d", c + i);
			q.push(mkp(-0, -c[i]));
		}
		int a = 0;
		while(m && q.size()){
			auto t = q.top(); q.pop();
			m--;
			if(-t.fi - t.se <= x){
				if(-t.fi - t.se < x) q.push(mkp(t.fi + t.se, t.se));
			}else if(-t.fi - t.se > x) ++a;
		}
		printf("%d %d\n", m, a);
	}
	return 0;
}
