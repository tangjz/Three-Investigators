#include<bits/stdc++.h>
using namespace std;
#define M 1000000007
#define ll long long

const int maxn = 1000005;
int n, k;
int go[maxn][26];
int tag[maxn];
int q[maxn];
int fac[maxn], inv[maxn];
int c[maxn];
int tot = 1, m;
char s[maxn];

void insert(char *s, int i){
    int cur = 1;
    while(*s){
        int c = (*s++) - 'a';
        if(!go[cur][c]) go[cur][c] = ++tot;
        cur = go[cur][c];
    }
    tag[cur] = i;
}

void dfs(int t){
    if(tag[t]) tag[t] = ++m;
    else{
        for(int i = 0; i < 26; ++i)
            if(go[t][i]) dfs(go[t][i]);
    }
}

void add(int x){
    for(; x <= n; x += x & -x) ++c[x];
}

int ask(int x){
    int res = 0;
    for(; x; x -= x & -x) res += c[x];
    return res;
}

int P(int n, int m){
    return (ll)fac[n] * inv[n - m] % M;
}

int main(){
    scanf("%d%d", &n, &k);
    for(int i = 1; i <= n; ++i){
        scanf("%s", s);
        insert(s, i);
    }
    dfs(1);
    scanf("%s", s);

    fac[1] = fac[0] = inv[1] = inv[0] = 1;
    for(int i = 2; i <= n; ++i){
        fac[i] = (ll)fac[i - 1] * i % M;
        inv[i] = (ll)(M - M / i) * inv[M % i] % M;
    }
    for(int i = 2; i <= n; ++i) inv[i] = (ll)inv[i] * inv[i - 1] % M;

    int res = 0;
    for(int i = 0, cur = 1, t = 0; s[i]; ++i){
        int c = s[i] - 'a';
        cur = go[cur][c];
        if(tag[cur]){
            q[++t] = tag[cur], cur = 1;
            int t1 = q[t] - 1 - ask(q[t]);
            res = (res + (ll)t1 * P(n - t, k - t)) % M;
            add(q[t]);
            //printf("%d t1=%d res=%d\n", q[t], t1, res);
        }
    }

    printf("%d\n", (res + 1) % M);
    //system("pause");
    return 0;
}
