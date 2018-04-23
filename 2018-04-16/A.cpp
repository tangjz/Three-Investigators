#include<bits/stdc++.h>
using namespace std;

const double eps = 1e-12;
const double inf = 1e10;
int dcmp(double x){
    return (x > eps) - (x < -eps);
}
struct Point{
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}

    double operator ^ (const Point &P) const{
        return x * P.y - y * P.x;
    }
    Point operator - (const Point &P) const{
        return Point(x - P.x, y - P.y);
    }
    Point operator + (const Point &P) const{
        return Point(x + P.x, y + P.y);
    }

    double length(){
        return sqrt(x * x + y * y);
    }
};

double Cross(Point p, Point q){
    return p.x * q.y - p.y * q.x;
}

double GetLineInter(Point P, Point v, Point Q1, Point Q2){
    Point u = P - Q1, w = Q2 - Q1;
    double t = Cross(w, u) / Cross(v, w);
    return t;
}

bool SegInter(Point P, Point v, Point Q1, Point Q2){
    double c1 = Cross(v, Q1 - P), c2 = Cross(v, Q2 - P);
    return dcmp(c1 * c2) <= 0;
}

const int maxn = 205;
int n, m;
Point P[maxn], Q[maxn], v[maxn];
double L[maxn], R[maxn], T[maxn][maxn];
double f[2 * maxn][2 * maxn];

int main(){
    scanf("%d", &n);
    for(int i = 0; i < n; ++i){
        scanf("%lf%lf", &Q[i].x, &Q[i].y);
    }
    scanf("%d", &m);
    for(int i = 0; i < m; ++i){
        scanf("%lf%lf", &P[i].x, &P[i].y);
        L[i] = -inf, R[i] = inf;
    }
    for(int i = 0; i < m; ++i)
        v[i] = P[(i + 1) % m] - P[i];
    

    for(int i = 0; i < m; ++i)
        for(int j = 0; j < n; ++j){
            if(dcmp(Cross(v[i], Q[(j + 1) % n] - Q[j])) == 0) continue;
            if(SegInter(P[i], v[i], Q[j], Q[(j + 1) % n])){
                double t = GetLineInter(P[i], v[i], Q[j], Q[(j + 1) % n]);
                if(dcmp(t) <= 0) L[i] = max(L[i], t);
                else R[i] = min(R[i], t);
                //printf("%d %d: %.6lf\n", i, j, t);
            }
            //printf("i:%d L=%lf R=%lf\n", i, L[i], R[i]);
        }

    for(int i = 0; i < m; ++i)
        for(int j = 0; j < m; ++j){
            if(dcmp(Cross(v[i], v[j])) == 0) T[i][j] = inf;
            else T[i][j] = GetLineInter(P[i], v[i], P[j], P[j] + v[j]);
            //printf("T: %d %d: %lf\n", i, j, T[i][j]);
        }

    int mm = 2 * m - 1;
    for(int len = 1; len < m; ++len){
        for(int i = 0; i + len - 1 < mm; ++i){
            int j = i + len - 1;
            int pre_i = (i + m - 1) % m, suf_j = (j + 1) % m;
            f[i][j] = inf;
            for(int k = i; k <= j; ++k){
                double lt = L[k % m], rt = R[k % m];
                if(dcmp(T[k % m][pre_i]) <= 0) lt = max(lt, T[k % m][pre_i]);
                else rt = min(rt, T[k % m][pre_i]);
                if(dcmp(T[k % m][suf_j]) <= 0) lt = max(lt, T[k % m][suf_j]);
                else rt = min(rt, T[k % m][suf_j]);
                
                f[i][j] = min(f[i][j], (k ? f[i][k - 1] : 0) + f[k + 1][j] + (rt - lt) * v[k % m].length());

                //printf("upd: %d %d %d: %lf %lf\n", i, j, k, lt, rt);
            }

            //printf("f: %d %d: %lf\n", i, j, f[i][j]);
        }
    }

    double res = inf;
    for(int i = 0; i < m; ++i){
        res = min(res, f[i + 1][i + m - 1] + (R[i] - L[i]) * v[i].length());
        //printf("upd_res: %d: %lf %lf\n", i, f[i + 1][i + m - 1], (R[i] - L[i]) * v[i].length());
    }

    printf("%.12lf\n", res);
    return 0;
}
