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

double a, b;
int n, m;
int d[25][25];
double dmin[25][25];
char s[10000];

void walk(int i, int j){
	if(i > 1){
		if(dmin[i - 1][j - 1] + b * d[i][j] == dmin[i][j])
			walk(i - 1, j - 1);
		else if(dmin[i][j] == dmin[i - 2][j - 1] + a * d[i - 1][j] + a * d[i][j]){
			walk(i - 2, j - 1);
			printf("(%d,%d)\n", i - 1, j);
		}else{
			walk(i - 1, j - 2);
			printf("(%d,%d)\n", i, j - 1);
		}
	}
		
	printf("(%d,%d)\n", i, j);
}

int main(){
	scanf("%lf%lf\n", &a, &b);
	while(gets(s)){
		n++;
		m = 0;
		for(int i = 0; s[i]; ++i){
			if(s[i] >= '0' && s[i] <= '9'){
				m++;
				int num = s[i] - '0';
				while(s[i + 1] >= '0' && s[i + 1] <= '9')
					num = num * 10 + (s[++i] - '0');
				d[m][n] = num;
				//	printf("%d ", num);
			}
		}
		//puts("");
	}
	swap(n, m);
	printf("%d %d\n", n, m);
	
	for(int i = 0; i <= n; ++i)
		for(int j = 0; j <= m; ++j)
			dmin[i][j] = 1e9;
	dmin[1][1] = d[1][1];
	for(int i = 2; i <= n; ++i){
		for(int j = 2; j <= m; ++j){
			dmin[i][j] = dmin[i - 1][j - 1] + b * d[i][j];
			if(i > 2){
				dmin[i][j] = min(dmin[i][j], dmin[i - 2][j - 1] + a * d[i - 1][j] + a * d[i][j]);
			}
			if(j > 2){
				dmin[i][j] = min(dmin[i][j], dmin[i - 1][j - 2] + a * d[i][j - 1] + a * d[i][j]);
			}
		}
	}
	
	printf("%.6f\n", dmin[n][m]);
	walk(n, m);
	
#ifndef ONLINE_JUDGE
	system("pause");
#endif
	return 0;
}
