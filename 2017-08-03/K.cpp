#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

int T;
char s[10][30];

int work(int base){
	if(s[0][base + 1] == 'X'){//0 2 3 5 6 7 8 9
		if(s[1][base] == 'X'){// 0 5 6 8 9
			if(s[4][base] == 'X'){ //0 6 8
				if(s[1][base + 3] == 'X'){//0 8
					if(s[3][base + 1] == 'X'){
						return 8;
					}else{
						return 0;
					}
				}else{
					return 6;
				}
			}else{ //5 9
				if(s[1][base + 3] == 'X'){
					return 9;
				}else{
					return 5;
				}
			}
		}else{ //2 3 7
			if(s[4][base] == 'X'){
				return 2;
			}else{// 3 7
				if(s[3][base + 1] == 'X'){
					return 3;
				}else{
					return 7;
				}
			}
		}
	}else{
		if(s[1][base] == 'X'){
			return 4;
		}else{
			return 1;
		}
	}
}

int main(){
	scanf("%d", &T);
	while(T--){
		for(int i = 0; i < 7; ++i){
			scanf("%s", s[i]);
		}
		printf("%d%d:%d%d\n", work(0), work(5), work(12), work(17));
	}
	
	return 0;
}
