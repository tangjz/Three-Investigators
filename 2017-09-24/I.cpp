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

const double L = sqrt(3) * 5 / 2;

double xx[100][100], yy[100][100];
bool vis[100][100];

void dfs(int i, int j, double x, double y){
	vis[i][j] = 1;
	xx[i][j] = x, yy[i][j] = y;
	if(!vis[i + 1][j] && i < 20){
		dfs(i + 1, j, x + L * 2, y);
	}
	if(!vis[i - 1][j] && i > 1){
		dfs(i - 1, j, x - L * 2, y);
	}
	if(!vis[i][j + 1] && j < 20){
		dfs(i, j + 1, x + L, y + 7.5);
	}
	if(!vis[i][j - 1] && j > 1){
		dfs(i, j - 1, x - L, y - 7.5);
	}
}

int main(){
	int x, y;
	dfs(10, 10, 0, 0);

	for(int i = 0; i < 10; ++i){
		scanf("%d%d", &x, &y);
		for(int j = 1; j <= 20; ++j)
			for(int k = 1; k <= 20; ++k)
				if(x - y >= xx[j][k] - yy[j][k] - L && x - y <= xx[j][k] - yy[j][k] + L && x + y >= xx[j][k] + yy[j][k] - L && x + y <= xx[j][k] + yy[j][k] + L){
					printf("[%d,%d]", j - 10, k - 10);
					if(i < 9) printf(", ");
					else printf("\n");
				}
		printf("\n");
	}
	
#ifndef ONLINE_JUDGE
	system("pause");
#endif
	return 0;
}
