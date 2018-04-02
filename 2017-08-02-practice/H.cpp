#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

char s[100];

int main(){
	int T, ca = 0;
	scanf("%d", &T);
	while(T--){
		scanf("%s", s);
		int i = 0, j = 0;
		while(s[i] != '[') ++i;
		while(s[j] != ']') ++j;
		i++;
		long double now = 100, base = 1000. / 1024;
		if(s[i] != 'B'){
			now *= base;
			if(s[i] != 'K'){
				now *= base;
				if(s[i] != 'M'){
					now *= base;
					if(s[i] != 'G'){
						now *= base;
						if(s[i] != 'T'){
							now *= base;
							if(s[i] != 'P'){
								now *= base;
								if(s[i] != 'E'){
									now *= base;
									if(s[i] != 'Z'){
										now *= base;
									}
								}
							}
						}
					}
				}
			}
		}
		printf("Case #%d: %.2f%%\n", ++ca, float(100. - now));
	}
	
#ifndef ONLINE_JUDGE
	system("pause");
#endif
	return 0;
}
