#include <stdio.h>
#include <string.h>

int n, top;
char s[710], st[710];
char s1[710];

int main() {
    scanf("%d", &n);
    while (n--) {
        scanf("%s", s);
        int len = strlen(s);
        top = 0;
        for (int i = 0; i < len; i++) {
            switch (s[i]) {
                case '+': 
                case '-': {
                    while (top && st[top] != '(') printf("%c ", st[top--]);
                    st[++top] = s[i];
                    break;
                }
                case '*':
                case '/': {
                    while (!(!top || st[top] == '(' || st[top] == '-' || st[top] == '+')) printf("%c ", st[top--]);
                    st[++top] = s[i];
                    break;
                }
                case '(': {
                    st[++top] = s[i];
                    break;
                }
                case ')': {
                    while (st[top] != '(') printf("%c ", st[top--]);
                    top--;
                    break;
                }
                default: {
                    int cnt = 0;
                    while (i < len && ((s[i] >= '0' && s[i] <= '9') || s[i] == '.')) s1[cnt++] = s[i++];
                    i--;
                    s1[cnt] = '\0';
                    printf("%s ", s1);
                }
            }
        }
        while (top) printf("%c ", st[top--]);
        printf("\n");
    }
    return 0;
}