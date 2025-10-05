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
};

inline int priority(char x) {
    if (x == '+' || x == '-') return 0;
    else if (x == '*' || x == '/') return 1;
    else return -1;
}

int cal(int x, int y, char op) {
    if (op == '+') return x + y;
    else if (op == '-') return x - y;
    else if (op == '*') return x * y;
    else if (op == '/') return x / y;
}

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
            }
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
        }
        cout << result.top() << endl;
    }
    return 0;
}