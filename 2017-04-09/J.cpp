#include <cstdio>
#include <cstdlib>
#include <cstring>
 
using namespace std;
 
int T, N, M, S;
long long ans;
 
int main()
{
    int t;
    scanf("%d", &T);
    for(t = 1;t <= T;t += 1)
    {
        scanf("%d %d %d", &N, &M, &S);
        ans = 1;
        ans *= (N + S - 1) / S;
        ans *= (M + S - 1) / S;
        ans *= (N - 1) % S + 1;
        ans *= (M - 1) % S + 1;
        printf("%lld\n", ans);
    }
    exit(0);
}
