#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
#define M 1000000009
#define ll long long
 
int n, K;
int a[101];
int f[2][2501][31][31];
 
inline void add(int &a, int b){
    a = (a + b) % M;   
}
 
int main(){
    while(~scanf("%d%d", &n, &K)){
        for(int i = 1; i <= n; ++i) scanf("%d", a + i); 
        memset(f, 0, sizeof(f));
        f[0][0][0][0] = 1;
        int now = 1, pre = 0;
        for(int i = 0; i < n; ++i, swap(now, pre)){
            memset(f[now], 0, sizeof(f[now]));
            for(int j = 0; j <= K; ++j)
                for(int k = min(i, n / 2); k >= 0; --k)
                for(int l = min(i, n / 2); l >= 0; --l)
                    if(f[pre][j][k][l]){
                        if(j + a[i + 1] * 2 <= K) add(f[now][j + a[i + 1] * 2][k + 1][l + 1], f[pre][j][k][l]);
                        if(j + a[i + 1] <= K){
                            add(f[now][j + a[i + 1]][k][l], f[pre][j][k][l]);
                            if(k) add(f[now][j + a[i + 1]][k][l], (ll)f[pre][j][k][l] * k % M);
                            if(l) add(f[now][j + a[i + 1]][k][l], (ll)f[pre][j][k][l] * l % M);
                        }
                        if(k && l) add(f[now][j][k - 1][l - 1], (ll)f[pre][j][k][l] * k * l % M);
                    }
        }
        printf("%d\n", f[pre][K][0][0]);
    }
    return 0;  
}
