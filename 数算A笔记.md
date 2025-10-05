# 数据结构与算法A

### 2025年秋季大二上

---

## 栈和队列

- 中缀表达式转后缀表达式

[原题链接(POJ)](http://dsa.openjudge.cn/2025dsachapter3/C/)

### 题目描述
人们熟悉的四则运算表达式称为中缀表达式，例如(23+34*45/(5+6+7))。在程序设计语言中，可以利用堆栈的方法把中缀表达式转换成保值的后缀表达式（又称逆波兰表示法），并最终变为计算机可以直接执行的指令，得到表达式的值。

给定一个中缀表达式，编写程序，利用堆栈的方法，计算表达式的值。
    
**输入**
第一行为测试数据的组数N
接下来的N行，每行是一个中缀表达式。表达式中只含数字、四则运算符和圆括号，操作数都是正整数，数和运算符、括号之间没有空格。中缀表达式的字符串长度不超过600。

**输出**
对每一组测试数据输出一行，为表达式的值

**样例输入**

    3
    3+5*8
    (3+5)*8
    (23+34*45/(5+6+7))

**样例输出**

    43
    64
    108

**提示**

注意：运算过程均为整数运算（除法运算'/'即按照C++定义的int除以int的结果，测试数据不会出现除数为0的情况），输出结果也为整数（可能为负）。
中间计算结果可能为负。

1. ==cpp==版本
   
```c++ {.line-numbers}
#include <iostream>
#include <string>
#include <stack>
#include <vector>
using namespace std;

struct node {
    int type;
    union {
        int data;
        char op;
    };
    node(int x) : type(0) {data = x;}
    node(char x) : type(1) {op = x;}
}; //这里使用type标记是data还是op，并使用了union语法

inline int priority(char x) {
    if (x == '+' || x == '-') return 0;
    else if (x == '*' || x == '/') return 1;
    else return -1;
} //计算优先级

int cal(int x, int y, char op) {
    if (op == '+') return x + y;
    else if (op == '-') return x - y;
    else if (op == '*') return x * y;
    else if (op == '/') return x / y;
} //对栈中元素进行操作

int main()
{
    int n;
    cin >> n;
    while(n--) {
        string input;
        cin >> input;
        vector<node> back_expression;
        int i = 0, len = input.size();
        stack<char> op;
        while(i < len) {
            if (isdigit(input[i])) {
                int temp = 0;
                while(i < len && isdigit(input[i])) {
                    temp = temp * 10 + (input[i] - '0');
                    i++;
                }
                back_expression.push_back(node(temp));
            } //读入num
            else if (input[i] == '(') {
                op.push(input[i]);
                i++;
            }
            else if (input[i] == ')') {
                while(op.top() != '(') {
                    back_expression.push_back(node(op.top()));
                    op.pop();
                }
                op.pop();
                i++;
            }
            else {
                while(!op.empty() && priority(op.top()) >= priority(input[i])) {
                    back_expression.push_back(node(op.top()));
                    op.pop();
                }
                op.push(input[i]);
                i++;
            }
        }
        while(!op.empty()) {
            back_expression.push_back(op.top());
            op.pop();
        }

        stack<int> result;
        for(auto item : back_expression) {
            if (item.type == 0) {
                result.push(item.data);
            }
            else if (item.type == 1) {
                int y = result.top();
                result.pop();
                int x = result.top();
                result.pop();
                result.push(cal(x, y, item.op));
            }
        } //计算后缀表达式
        cout << result.top() << endl;
    }
    return 0;
}
```
2. ==C==版本

```c {.line-numbers}
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
```
---
