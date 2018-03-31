#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define ll long long
#define M 1000000007
 
int T, n, m;
int a[50], b[50];
 
ll cal(int n, int i, int x, int j, int y){
    if(i < j) swap(i, j), swap(x, y);
    if(i == j){
        if(x == y){
            ll tmp = n >> (i + 1) << i;
            int geti = n >> i & 1;
            if(x < geti) tmp += 1 << i;
            else if(x == geti) tmp += (n & ((1 << i) - 1)) + 1;
            return tmp;
        }else return 0;
    }
    ll tmp = n >> (i + 1) << (i - 1);
    int geti = n >> i & 1, getj = n >> j & 1;
    if(geti > x) tmp += 1 << (i - 1);
    else if(geti == x){
        tmp += (n & ((1 << i) - 1)) >> (j + 1) << j;
        if(getj > y) tmp += 1 << j;
        else if(getj == y) tmp += (n & ((1 << j) - 1)) + 1;  
    }
    return tmp;
}
 
int main(){
    scanf("%d", &T);
    while(T--){
        scanf("%d%d", &n, &m);
        ll ans = 0;
        //printf("%lld\n", cal(1, 1, 1, 0, 1));
        //continue;
        for(int i = 0; i < 31; ++i)
            for(int j = 0; j < 31; ++j){
                for(int x = 0; x < 2; ++x)
                    for(int y = 0; y < 2; ++y)
                        (ans += (ll)cal(n, i, x, j, y) * cal(m, i, x ^ 1, j, y ^ 1) % M * (1 << i) % M * (1 << j) % M) %= M;
            }
        printf("%lld\n", ans);
    }
    return 0;  
}
