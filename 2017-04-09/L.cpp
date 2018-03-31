#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
#define ll long long
 
ll n;
int T;
 
ll cal(ll n){
    return n * (n + 1) / 2;
}
 
ll check(ll d){
    ll m = n / d;
    ll cnt = d * cal(m - 1);
    cnt += n % (m * d) * m;
    return cnt;
}
 
int main(){
    scanf("%d", &T);
    while(T--){
        scanf("%lld", &n);
        ll l = 0, r = n + 1;
        while(l + 1 < r){
            ll d = (l + r) >> 1;
            if(check(d) <= n) r = d;
            else l = d;
        }
        printf("%lld\n", r);
    }
    return 0;  
}
