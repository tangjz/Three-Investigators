#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

struct edge{
	int u, v, w;
	edge(){}
	edge(int u, int v, int w) : u(u), v(v), w(w) {}
};
vector<edge> ans;
int T, n, m, ca = 0;
queue<int> vec[3];

int main(){
	scanf("%d", &T);
	while(T--){
		scanf("%d%d", &n, &m);
		int sum = 0;
		ans.clear();
		for(int i = 1; i < n; ++i){
			ans.pb(edge(i, i + 1, i));
			sum += i;
		}
		int x = n; sum += n;
		for(int i = 0; i < 3; ++i)
			while(!vec[i].empty()) vec[i].pop();
		while(sum % 3 != 0){
			vec[x % 3].push(x);
			sum++, x++;
		}
		ans.pb(edge(n, 1, x));
		for(int i = x + 1; i <= m; ++i) vec[i % 3].push(i);
		for(int i = 3; i <= n; ++i){
			int now = i - 1;
			for(int j = i - 2; j >= 1; --j){
				now += j;
				int x = (3 - now % 3) % 3; 
				if(!vec[x].empty()){
					int t = vec[x].front(); vec[x].pop();
					ans.pb(edge(i, j, t));
				}
			}
		}
		bool flag = 1;
		for(int i = 0; i < 3; ++i) if(vec[i].size()) flag = 0;
		printf("Case #%d:\n", ++ca);
		if(!flag) printf("-1\n");
		else{
			for(edge e : ans)
				printf("%d %d %d\n", e.u, e.v, e.w);
		}
	}
	
#ifndef ONLINE_JUDGE
	system("pause");
#endif
	return 0;
}
