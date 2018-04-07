#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int maxn = 100005;
int ca;
int n;
string pp;
string s[101];
ll f[101], dp[101];
int p[maxn];

int main(){
	while(cin >> n){
        memset(f, 0, sizeof(f));
        memset(dp, 0, sizeof(dp));
        cin >> pp;
        cout << "Case " << ++ca << ": ";
        f[0] = 1, f[1] = 1;
        s[0] = "0", s[1] = "1";
        int m = pp.length();
        if(m == 1){
            f[(pp[0] - '0') ^ 1] = 0;
            for(int i = 2; i <= n; ++i){
                f[i] = f[i - 1] + f[i - 2];
            }
            cout << f[n] << '\n';
        }else{
            if(n < 2){
                cout << 0 << '\n';
                continue;
            }
            int j = 0;
            p[1] = 0;
            for(int i = 2; i <= m; ++i){
                while(j && pp[j] != pp[i - 1]) j = p[j];
                if(pp[j] == pp[i - 1]) ++j;
                p[i] = j;
            }

            for(int k = 2; k <= n; ++k){
                f[k] = f[k - 1] + f[k - 2];
                s[k] = s[k - 1] + s[k - 2];
                if(f[k] >= m){
                    int l = f[k], j = 0;
                    for(int i = 1; i <= l; ++i){
                        while(j && pp[j] != s[k][i - 1]) j = p[j];
                        if(pp[j] == s[k][i - 1]) ++j;
                        if(j == m) ++dp[k], j = p[j];
                        //cout << j << '\n';
                    }

                    //cout << s[k] << '\n';
                    //cout << dp[k] << '\n';

                    if(k < n){
                        ++k;
                        f[k] = f[k - 1] + f[k - 2];
                        s[k] = s[k - 1] + s[k - 2];
                        int mid[2];
                        int l = f[k]; mid[0] = mid[1] = 0;
                        for(int i = 1; i <= l; ++i){
                            while(j && pp[j] != s[k][i - 1]) j = p[j];
                            if(pp[j] == s[k][i - 1]) ++j;
                            if(j == m){
                                if(i < m) ++mid[0];
                                else ++dp[k];
                                j = p[j];
                            }
                        }

                        //cout << dp[k] << ' ' << mid[0] << '\n';
                        //cout << j << '\n';

                        --k; l = f[k];
                        int mid2 = 0;
                        for(int i = 1; i <= m - 1; ++i){
                            while(j && pp[j] != s[k][i - 1]) j = p[j];
                            if(pp[j] == s[k][i - 1]) ++j;
                            if(j == m) ++mid[1], j = p[j];
                        }

                        //cout << mid[1] << '\n';

                        k += 2; int cur = 1;
                        while(k <= n){
                            dp[k] = dp[k - 1] + dp[k - 2] + mid[cur];
                            ++k; cur ^= 1;
                        }
                    }
                }
            }
            cout << dp[n] << '\n';
        }
	}
	return 0;
}
