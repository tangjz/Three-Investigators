#include<bits/stdc++.h>
using namespace std;

char s[100000];
string sen[10000];
map<string, bool> mp[10000];
string ch[10000];

int main(){
	gets(s);
	int n = strlen(s), m = 0, last = 0;
	for(int i = 0; i <= n; ){
		if(i == n){
			while(s[last] == ' ') ++last;
			int now = i - 1;
			while(s[now] == ' ') --now;
			for(int j = last; j <= now; ++j)
				sen[m] = sen[m] + s[j];
			//cout << "sen: " << sen[m] << '\n';
			++m;
			break;
		}
		if(s[i] == '.'){
			while(s[++i] == ' ');
			//if(s[i] == 0) break;
			if(s[i] < 'a' || s[i] > 'z'){
				while(s[last] == ' ') ++last;
				int now = i - 1;
				while(s[now] == ' ') --now;
				for(int j = last; j <= now; ++j)
					sen[m] = sen[m] + s[j];
				//cout << "sen: " << sen[m] << '\n';
				last = i;
				++m;
			}
		}else if(s[i] == '!' || s[i] == '?'){
			while(s[last] == ' ') ++last;
			for(int j = last; j <= i; ++j)
				sen[m] = sen[m] + s[j];
			//cout << "sen: " << sen[m] << '\n';
			++i;
			last = i;
			++m;
		}else if(s[i] == ' '){
			++i;
		}else{
			string str;
			while(i < n && s[i] != ' ' && s[i] != '.' && s[i] != '!' && s[i] != '?'){
				str = str + char(s[i] >= 'A' && s[i] <= 'Z' ? s[i] - 'A' + 'a' : s[i]);
				++i;
			}
			//cout << "word: " << str << '\n';
			mp[m][str] = 1;		
		}
	}
	scanf("%d\n", &n);
	while(n--){
		gets(s);
		printf("Search results for \"%s\":\n", s);
		int l = strlen(s), k = 0;
		for(int i = 0; i < l; ){
			if(s[i] == ' ') ++i;
			else{
				string str;
				while(i < l && s[i] != ' '){
					str = str + char(s[i] >= 'A' && s[i] <= 'Z' ? s[i] - 'A' + 'a' : s[i]);
					++i;
				}
				ch[k++] = str;
				//cout << "ch: " << str << "\n";
			}
		}
		for(int i = 0, j; i < m; ++i){
			for(j = 0; j < k; ++j)
				if(!mp[i].count(ch[j])) break;
			if(j == k)
				cout << "- \"" << sen[i] << "\"\n";
		}
	}
	return 0;
}
