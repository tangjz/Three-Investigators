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

const int maxn = 300005;
int n, m;
int a[maxn], s[maxn], w[maxn];

int main(){
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i){
		scanf("%d%d", a + i, s + i);
		w[i] = i;
	}
	sort(w + 1, w + n + 1, [](int i, int j) { return a[i] < a[j]; });
	
	priority_queue<int> q;
	int ans = 0;
	for(int i = 1; i <= n; ++i){
		int x = w[i];
		while(!q.empty() && a[x] + q.top() > m + 1) q.pop();
		if(!q.empty() && -q.top() < a[x]) ans++, q.pop();
		q.push(-(a[x] + s[x] - 1));
	}
	
	printf("%d\n", ans);
	
#ifndef ONLINE_JUDGE
	system("pause");
#endif
	return 0;
}
