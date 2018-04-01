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

char str[1000];
string s;
char UP(char ch){
	return ch >= 'a' ? ch - 'a' + 'A' : ch;
}

char DOWN(char ch){
	return ch < 'a' ? ch - 'A' + 'a' : ch;
}

int main(){
	gets(str);
	for(int i = 0; str[i]; ++i)
		s += str[i];
	if(s.find(',') != string::npos){
		int l = s.find_first_of('{');
		int r = s.find_first_of('}');
		s[l + 1] = UP(s[l + 1]);
		cout << s.substr(l + 1, r - l - 1);
		
		cout << ' ';

		l = s.find_first_of('(');
		r = s.find_first_of(')');
		s[l + 1] = DOWN(s[l + 1]);
		cout << s.substr(l + 1, r - l - 1);

		cout << ' ';

		l = s.find_first_of('[');
		r = s.find_first_of(']');
		s[l + 1] = DOWN(s[l + 1]);
		cout << s.substr(l + 1, r - l - 1);

		l = s.find(',');
		r = min({s.find_last_of('['), s.find_last_of('{'), s.find_last_of('(')});
		cout << s.substr(l, r - l);
		
		l = s.find_last_of('{');
		r = s.find_last_of('}');
		s[l + 1] = DOWN(s[l + 1]);
		cout << s.substr(l + 1, r - l - 1);
		
		cout << ' ';

		l = s.find_last_of('(');
		r = s.find_last_of(')');
		s[l + 1] = DOWN(s[l + 1]);
		cout << s.substr(l + 1, r - l - 1);

		cout << ' ';

		l = s.find_last_of('[');
		r = s.find_last_of(']');
		s[l + 1] = DOWN(s[l + 1]);
		cout << s.substr(l + 1, r - l - 1);
	}else{
		int l = s.find_first_of('{');
		int r = s.find_first_of('}');
		s[l + 1] = UP(s[l + 1]);
		cout << s.substr(l + 1, r - l - 1);
		
		cout << ' ';

		l = s.find_first_of('(');
		r = s.find_first_of(')');
		s[l + 1] = DOWN(s[l + 1]);
		cout << s.substr(l + 1, r - l - 1);

		cout << ' ';

		l = s.find_first_of('[');
		r = s.find_first_of(']');
		s[l + 1] = DOWN(s[l + 1]);
		cout << s.substr(l + 1, r - l - 1);
	}
	
	
	return 0;
}
