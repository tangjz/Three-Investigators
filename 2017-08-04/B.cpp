#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

void work(int x){
	if(x == 1) printf("Yakk");
	else if(x == 2) printf("Doh");
	else if(x == 3) printf("Seh");
	else if(x == 4) printf("Ghar");
	else if(x == 5) printf("Bang");
	else printf("Sheesh");
}

int main(){
	int T, ca = 0, x, y;
	scanf("%d", &T);
	while(T--){
		scanf("%d%d", &x, &y);
		printf("Case %d: ", ++ca);
		if(x < y) swap(x, y);
		if(x == y){
			if(x == 1) printf("Habb Yakk\n");
			else if(x == 2) printf("Dobara\n");
			else if(x == 3) printf("Dousa\n");
			else if(x == 4) printf("Dorgy\n");
			else if(x == 5) printf("Dabash\n");
			else if(x == 6) printf("Dosh\n");
		}else if(x == 6 && y == 5) printf("Sheesh Beesh\n");
		else work(x), putchar(' '), work(y), putchar('\n');
	}
	
	return 0;
}
