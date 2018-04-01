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
char s[105][105], t[105][105];
char res[105 * 105], a[105 * 105];
int w[105], rk[105];

bool cmp(int i, int j){
	for(int k = 0; k < m; ++k)
		if(s[i][k] != s[j][k]) return s[i][k] > s[j][k];
	return 0;
}

bool cmpxy(int x, int y, int bg){
	for(int i = bg; i < m; ++i)
		if(s[x][i] != s[y][i]) return s[x][i] > s[y][i];
	return rk[x] > rk[y];
}

bool cmpall(){
	for(int i = 0; i < n * m; ++i)
		if(a[i] != res[i]) return a[i] > res[i];
	return 0;
}

void work(bool flag){
	for(int i = 0; i < n; ++i)
		w[i] = i;
	sort(w, w + n, cmp);
	for(int i = 0; i < n; ++i)
		rk[w[i]] = i;
	
	for(int i = 0; i < m; ++i){
		int id = 0;
		
		for(int j = 1; j < n; ++j)
			if(cmpxy(j, id, i)) id = j;
		
		int len = 0;
		for(int j = i; j < m; ++j) a[len++] = s[id][j];
		for(int j = 0; j < n; ++j)
			if(w[j] != id){
				for(int k = 0; k < m; ++k)
					a[len++] = s[w[j]][k];
			}
		for(int j = 0; j < i; ++j) a[len++] = s[id][j];
		assert(len == n * m);

		if(!flag || cmpall()){
			memcpy(res, a, sizeof(a));
			flag = 1;
		}
	}
}

int main(){
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; ++i)
		scanf("%s", s[i]);
	work(0);
	memcpy(t, s, sizeof(s));
	for(int i = 0; i < m; ++i)
		for(int j = 0; j < n; ++j)
			s[i][j] = t[j][i];
	swap(n, m);
	work(1);

	puts(res);

	return 0;
}
