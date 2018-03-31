#include <cstdio>
#include <cstdlib>
#include <cstring>
 
using namespace std;
 
const int NMAX = 11000, KMAX = 11000, MOD = 1000000007;
 
int T, N, K, M, ans;
int fa[NMAX], fac[NMAX + KMAX], ifac[NMAX + KMAX];
bool visit[NMAX];
 
int find(int x)
{
    int pa, tmp;
    for(pa = x;fa[pa] >= 0;pa = fa[pa]);
    while(x != pa)
    {
        tmp = fa[x];
        fa[x] = pa;
        x = tmp;
    }
    return pa;
}
 
void Union(int x, int y)
{
    int X = find(x), Y = find(y);
    if(X == Y)
        return;
    if(fa[X] < fa[Y])
    {
        fa[X] += fa[Y];
        fa[Y] = X;
    }
    else
    {
        fa[Y] += fa[X];
        fa[X] = Y;
    }
}
 
int C(int n, int m)
{
    return (long long)fac[n] * ifac[m] % MOD * ifac[n - m] % MOD;
}
 
int solve(int n)
{
    return C(n + K - 1, K - 1);
}
 
int quickModPow(int x, int y)
{
    int res = 1;
    while(y)
    {
        if(y & 1)
            res = (long long)res * x % MOD;
        y >>= 1;
        x = (long long)x * x % MOD;
    }
    return res;
}
 
int main()
{
    int t, i, x, y;
    scanf("%d", &T);
    ifac[0] = fac[0] = 1;
    for(i = 1;i <= NMAX + KMAX;i += 1)
    {
        fac[i] = (long long)i * fac[i - 1] % MOD;
        ifac[i] = quickModPow(fac[i], MOD - 2);
    }
    for(t = 0;t < T;t += 1)
    {
        ans = 1;
        memset(fa, -1, sizeof(fa));
        memset(visit, 0, sizeof(visit));
        scanf("%d %d %d", &N, &M, &K);
        for(i = 0;i < M;i += 1)
        {
            scanf("%d %d", &x, &y);
            Union(x, y);
        }
        for(i = 1;i <= N;i += 1)
        {
            x = find(i);
            if(!visit[x])
            {
                visit[x] = true;
                ans = (long long)ans * solve(-fa[x]) % MOD;
            }
        }
        printf("%d\n", ans);
    }
    exit(0);
}
