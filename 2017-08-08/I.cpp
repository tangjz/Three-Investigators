#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 998244353
#define all(a) a.begin(), a.end()

const int MAXN = 5010;
int res;
int B = 10000;
struct bign{
    int len, s[MAXN / 4 + 2];
    bign(){
        len = 1;
        memset(s, 0, sizeof(s));
    }
    bign(const char *num) { *this = num; }
    bign(int num) { *this = num; }
    inline void clean(){
        while(len > 1 && !s[len - 1]) len--;
    }
    bign operator = (int num){
        len = 0;
        memset(s, 0, sizeof(s));
        do{ s[len++] = num % B; num /= B; }while(num);
        return *this;
    }
    bign operator = (const char *num){
        for(int i = 0; num[i] == '0'; num++);
        int slen = strlen(num); len = 0;
        for(int i = 0; i < slen; i += 4){
            s[i / 4] = 0;
            for(int j = min(i + 4 - 1, slen - 1); j >= i; --j)
                s[i / 4] = s[i / 4] * 10 + num[slen - j - 1] - '0';
            len++;
        }
        return *this;
    }
    bign operator - (const bign &b) const{
        bign c;
        c.len = len;
        for(int i = 0; i < len; ++i){
            c.s[i] += s[i] - b.s[i];
            if(c.s[i] < 0) c.s[i] += B, c.s[i + 1]--;
        }
        c.clean();
        return c;
    }
    bign operator + (const bign &b) const{
        bign c;
        c.len = max(len, b.len);
        for(int i = 0; i < c.len; ++i){
            c.s[i] += s[i] + b.s[i];
            if(c.s[i] >= B) c.s[i] -= B, c.s[i + 1]++;
        }
        if(c.s[c.len]) c.len++;
        return c;
    }
    bign operator * (const int x){
        bign c;
        if(!x) return c;
        c.len = len;
        int r = 0;
        for(int i = 0; i < len; ++i){
            c.s[i] = s[i] * x + r;
            r = c.s[i] / B;
            c.s[i] %= B;
        }
        while(r) c.s[c.len++] = r % B, r /= B;
        c.clean();
        return c;
    }
    bign operator / (const int x){
        bign c;
        res = 0;
        for(int i = len - 1; i >= 0; --i){
            res = res * B + s[i];
            c.s[i] = res / x;
            res %= x;
        }
        c.len = len;
        c.clean();
        return c;
    }
    bool operator < (const bign &b){
        if(len != b.len) return len < b.len;
        for(int i = len - 1; i >= 0; --i)
            if(s[i] != b.s[i]) return s[i] < b.s[i];
        return false;
    }
    bool operator > (const bign &b){
        if(len != b.len) return len < b.len;
        for(int i = len - 1; i >= 0; --i)
            if(s[i] != b.s[i]) return s[i] > b.s[i];
        return false;
    }
}numL, numR;
int fac[5010];
int p[5010];
bool tag[5010];

bool check(bign &N, int d){
    bign R, base = 1;
    for(int i =    1; i <= d; ++i){
        R = R + base * (i - 1);
        if(R.len > N.len) return 0;
        base = base * d;
    }
    if(R < N) return 1;
    else return 0;
}

int c[5010];
inline int ask(int x){
    int res = 0;
    for(; x; x -= x & -x) res += c[x];
    return res;
}

inline void add(int d, int x){
    for(; x <= d; x += x & -x) ++c[x];
}

int solve(bign &N, int d){    
    bign NN = N;
    for(int i = 0; i < d; ++i){
        NN = NN / d;
        p[i] = res;
    }
    if(!p[d - 1]) return 0;
    if(NN.len > 1 || NN.s[0] != 0) return 0;
    memset(tag, 0, sizeof(bool) * d);
    memset(c, 0, sizeof(int) * (d + 1));
    int ans = 0;
    for(int i = d - 1; i >= 0; --i){
        int tmp = p[i] - ask(p[i]) - (i == d - 1);
        ans = (ans + (ll)tmp * fac[i]) % M;
        add(d, p[i] + 1);
        if(tag[p[i]]) break;
        tag[p[i]] = 1;
    }
    return ans;
}

int work(bign N){
    int ans = 0;
    int l = 2, r = 4 * (N.len + 1);
    while(l + 1 < r){
        int d = (l + r) >> 1;
        if(check(N, d)) l = d;
        else r = d;
    }
    for(int i = 2; i <= l; ++i)
        ans = (ans + ((fac[i] - fac[i - 1] + M) % M)) % M;
    ans = (ans + solve(N, r)) % M;
    return ans;
}

char sL[5010], sR[5010];

int main(){

	freopen("1009.in", "r", stdin);
	freopen("1009.out", "w", stdout);
    int T;
    scanf("%d", &T);
    fac[0] = 1;
    for(int i = 1; i <= 5000; ++i) fac[i] = (ll)fac[i - 1] * i % M;
    while(T--){
        scanf("%s%s", sL, sR);
        numL = sL;
        numR = sR;
        bign one = 1;
        int res = (work(numR + one) - work(numL) + M) % M;
        printf("%d\n", res);
    }
    
    return 0;
}
