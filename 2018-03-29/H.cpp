#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e6 + 1;
int tot, pr[maxn], d[maxn], f[maxn], g[maxn];
int main() {
    for(int i = 2; i < maxn; ++i) {
        if(!d[i]) {
            pr[tot++] = d[i] = i;
            f[i] = g[i] = 1;
        }
        for(int j = 0, k; (k = i * pr[j]) < maxn; ++j) {
            d[k] = pr[j];
            if(d[i] == pr[j]) {
                f[k] = f[i];
                break;
            }
            f[k] = f[i] + 1;
        }
    }
    for(int i = 2; i < maxn; ++i) {
        f[i] += f[i - 1];
        g[i] += g[i - 1];
    }
    int q;
    scanf("%d", &q);
    while(q--) {
        int L, R;
        long long ans = 0;
        scanf("%d%d", &L, &R);
        for(int i = 1, j; i <= R; i = j + 1) {
            int x = (L - 1) / i, y = R / i;
            j = R / y;
            if(x)
                j = min(j, (L - 1) / x);
            ans += (g[j] - g[i - 1]) * (long long)(y - x) * (y - x);
        }
        ans = (ans - f[R] + f[L - 1]) / 2;
        printf("%lld\n", ans);
        fflush(stdout);
    }
    return 0;
}
