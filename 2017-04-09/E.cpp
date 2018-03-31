#include <cstdio>
typedef double DB;
const int maxn = 25, maxt = 100;
const DB eps = 1e-12;
int t, n, deg[maxn], cnt[maxn];
DB f[maxn][maxn], p[maxn][maxn];
inline int sgn(DB x)
{
    return (x > eps) - (x < -eps);
}
inline int dcmp(DB x, DB y)
{
    return sgn(x - y);
}
inline DB getval(int dep, DB x)
{
    DB ret = 0;
    for(int i = deg[dep]; i >= 0; --i)
        ret = ret * x + f[dep][i];
    //printf("f %d (%f) : %f\n", dep, x, ret);
    return ret;
}
void shrink(int dep)
{
    int tp = 0;
    for(int i = 1; i <= cnt[dep]; ++i)
        if(dcmp(-2, p[dep][i]) < 0 && dcmp(p[dep][i], 2) < 0)
            p[dep][++tp] = p[dep][i];
    cnt[dep] = tp;
}
bool getroot(int dep, DB L, DB R, DB &ans)
{
    int sgnL = sgn(getval(dep, L)), sgnR = sgn(getval(dep, R));
    if(sgnL * sgnR >= 0)
        return 0;
    for(int i = 0; i < maxt; ++i)
    {
        DB M = L + (R - L) * 0.5;
        int sgnM = sgn(getval(dep, M));
        if(sgnL * sgnM < 0)
            R = M;
        else
            L = M;
    }
    ans = L;
    return 1;
}
void solve(int dep)
{
    DB coeff = f[dep][deg[dep]];
    for(int i = 0; i <= deg[dep]; ++i)
        f[dep][i] /= coeff;
    if(deg[dep] == 0)
    {
        cnt[dep] = 0;
        return;
    }
    deg[dep + 1] = deg[dep] - 1;
    for(int i = 0; i < deg[dep]; ++i)
        f[dep + 1][i] = f[dep][i + 1] * (i + 1);
    solve(dep + 1);
    shrink(dep + 1);
    //printf("solve %d\n", dep);
    //for(int i = 0; i <= deg[dep]; ++i)
    //  printf("%f%c", f[dep][i], " \n"[i == deg[dep]]);
    p[dep + 1][0] = -2;
    p[dep + 1][cnt[dep + 1] + 1] = 2;
    cnt[dep] = 0;
    for(int i = 0; i <= cnt[dep + 1] + 1; ++i)
    {
        if(i > 0)
        {
            DB tp;
            if(getroot(dep, p[dep + 1][i - 1], p[dep + 1][i], tp))
                p[dep][++cnt[dep]] = tp;
        }
        if(sgn(getval(dep, p[dep + 1][i])) == 0)
            p[dep][++cnt[dep]] = p[dep + 1][i];
    }
}
int main()
{
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d", &n);
        deg[0] = n;
        for(int i = 0; i <= n; ++i)
            scanf("%lf", f[0] + i);
        while(deg[0] > 1 && sgn(f[0][deg[0]]) == 0)
            --deg[0];
        //for(int i = 0; i <= n; ++i)
        //  printf("%.20f%c", f[0][i], " \n"[i == n]);
        solve(0);
        // shrink(0);
        printf("%d\n", cnt[0]);
        if(!cnt[0])
            puts("");
        for(int i = 1; i <= cnt[0]; ++i)
            printf("%.4f%c", p[0][i], " \n"[i == cnt[0]]);
    }
    return 0;
}
/*
3
1
1.78564615673 1.0
2
0.391186657321 1.26030958081 1.0
5
6.43458827910338820000 17.93797102373996600000 20.00000000000000000000 11.14808069738498700000 3.10658271118873450000 0.34623239204599215000
*/
