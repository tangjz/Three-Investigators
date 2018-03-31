#include <cstdio>
#include <cstdlib>
#include <algorithm>
 
using namespace std;
 
int N, ans;
 
int main()
{
    while(scanf("%d", &N) != EOF)
    {
        ans = 0;
        while(N)
        {
            ans += N / 5;
            N /= 5;
        }
        printf("%d\n", ans);
    }
    exit(0);
}
