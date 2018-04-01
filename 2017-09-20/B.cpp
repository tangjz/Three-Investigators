#include<bits/stdc++.h>
using namespace std;

const int maxn = 200100;

#define ll long long

struct point{
	int x, y;
	void input() { scanf("%d%d", &x, &y); }
	point(int x = 0, int y = 0): x(x), y(y) {}
	void output() { printf("%d %d\n", x, y); }
	bool operator < (const point &R) const{
		return x == R.x ? y < R.y : x < R.x;
	}
	point operator - (const point &R) const{
		return point(x - R.x, y - R.y);
	}
}p[maxn];
int n;
int sta[maxn];

ll cross(point a, point b){
	return (ll)a.x * b.y - (ll)b.x * a.y;
}

ll cross(point a, point b, point c){
	return cross(b - a, c - a);
}

ll area(point a, point b, point c){
	return abs(cross(a, b, c));
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) p[i].input();
	sort(p + 1, p + n + 1);
	int top = 0;
	for(int i = 1; i <= n; ++i){
		while(top > 1 && cross(p[sta[top - 1]], p[sta[top]], p[i]) <= 0)
			--top;
		sta[++top] = i;
	}
	int tmp = top;
	for(int i = n - 1; i >= 1; --i){
		while(top > tmp && cross(p[sta[top - 1]], p[sta[top]], p[i]) <= 0)
			--top;
		sta[++top] = i;
	}
	if(top > 1) --top;
	ll ans = -1;
	point a, b, c;
	for(int i = 1; i <= top; ++i)
		for(int j = i; j <= top; ++j)
			for(int k = j; k <= top; ++k)
				if(area(p[sta[i]], p[sta[j]], p[sta[k]]) > ans){
					ans = area(p[sta[i]], p[sta[j]], p[sta[k]]);
					a = p[sta[i]];
					b = p[sta[j]];
					c = p[sta[k]];
				}
	a.output();
	b.output();
	c.output();
	return 0;
}
