#include<bits/stdc++.h>
using namespace std;

int main(){
	int n;
	scanf("%d", &n);
	if(n > 6 || n == 5) printf("-1\n");
	else if(n == 1){
		puts("1");
	}else if(n == 2) puts("1 2");
	else if(n == 3) puts("2 1 3");
	else if(n == 4) puts("4 2 1 3");
	else puts("3 6 2 4 1 5");
	return 0;
}	
