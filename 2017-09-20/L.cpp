#include<bits/stdc++.h>
using namespace std;

int main(){
	int i, j, k;
	scanf("%d%d%d", &i, &j, &k);
	if(i && j && k){
		if(j > i && j > k){
			if(j > 3) puts("2");
			else puts("1");
		}else puts("0");
	}else{
		if(i){
			if(j) puts("2");
			else puts("0");
		}else puts("1");
	}
	return 0;
}
