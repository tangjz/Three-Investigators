#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
 
using namespace std;
 
const int NMAX = 1100000;
 
int T, N, L, ans;
int f[NMAX], factor[NMAX], top;
 
int main()
{
    int t, i, j, x, res;
    scanf("%d", &T);
    for(t = 0;t < T;t += 1)
    {
        ans = 0;
        scanf("%d %d", &N, &L);
        for(i = 0;i < NMAX;i += 1)
            f[i] = 0;
        for(i = 1, res = 0;i <= N;i += 1)
        {
            scanf("%d", &x);
            for(j = 1, res = 0;j * j <= x;j += 1)
            {
                if(x % j)
                    continue;
                if(j >= L)
                    res = max(res, f[j]);
                if(x / j >= L)
                    res = max(res, f[x / j]);
            }
            for(j = 1;j * j <= x;j += 1)
            {
                if(x % j)
                    continue;
                f[j] = max(res + 1, f[j]);
                f[x / j] = max(res + 1, f[x / j]);
            }
            ans = max(ans, res + 1);
        }
        printf("%d\n", ans);
    }
    exit(0);
}
