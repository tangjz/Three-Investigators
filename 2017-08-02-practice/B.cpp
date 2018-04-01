#include <cstdio>
const int maxn = 61001;
int t, dep;
char buf[maxn], ch, *ptr;
bool isblank(char ch) {
	return ch == ' ' || ch == '\t' || ch == '\n';
}
int main() {
	scanf("%d", &t);
	ch = getchar();
	for(int Case = 1; Case <= t; ++Case) {
		printf("Case #%d:\n", Case);
		do {
			for( ; isblank(ch); ch = getchar());
			if(ch == '<') { // tag
				ptr = buf;
				for( ; ch != '>'; ch = getchar())
					*ptr++ = ch;
				*ptr++ = ch;
				ch = getchar();
				*ptr = '\0';
				dep -= buf[1] == '/';
				for(int i = 0; i < dep; ++i)
					putchar(' ');
				puts(buf);
				dep += buf[1] != '/' && *(ptr - 2) != '/';
			} else { // element
				ptr = buf;
				for( ; ch != '<'; ch = getchar())
					if(!isblank(ch))
						*ptr++ = ch;
					else if(ptr != buf && *(ptr - 1) != ' ')
						*ptr++ = ' ';
				ptr -= *(ptr - 1) == ' ';
				*ptr = '\0';
				for(int i = 0; i < dep; ++i)
					putchar(' ');
				puts(buf);
			}
		} while(dep > 0);
	}
	return 0;
}
