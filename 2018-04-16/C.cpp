#include<bits/stdc++.h>
using namespace std;

int n;
char str[21];
int L[17][17];
int f[17][1 << 16];

int main(){
    scanf("%s", str);
    n = strlen(str);
    int sta = 0;
    for(int i = 0; i < n; ++i)
        sta |= (str[i] == '1') << i;

    for(int i = 0; i < n; ++i){
        L[i][i] = 1 << i;
        for(int j = i + 1; j < n; ++j)
            L[i][j] = L[i][j - 1] | (1 << j);
    }

    f[0][sta] = 1;
    //printf("%d\n", sta);
    int k = 0, aim = (1 << n) - 1;
    while(!f[k][aim]){
        ++k;
        memcpy(f[k], f[k - 1], sizeof(f[k]));

        for(int s = 0; s < 1 << n; ++s)
            if(f[k - 1][s])
                for(int i = 0; i < n; ++i)
                    f[k][s ^ L[i][min(i + k - 1, n - 1)]] = 1;
    }

    printf("%d\n", k);
}
