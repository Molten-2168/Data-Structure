/*
 * BÀI TẬP 6 - CHUYỂN ĐỔI BIỂU THỨC TRUNG TỐ SANG HẬU TỐ (KÝ TỰ ĐẠI DIỆN)
 * ======================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX 200

typedef struct {
    char data[MAX];
    int top;
} Stack;

Stack* create_stack() {
    Stack *s = (Stack *)malloc(sizeof(Stack));
    if (s != NULL) {
        s->top = -1;
    }
    return s;
}

bool is_empty(Stack *s) {
    return s->top == -1;
}

bool is_full(Stack *s) {
    return s->top == MAX - 1;
}

bool push(Stack *s, char value) {
    if (is_full(s)) return false;
    s->data[++(s->top)] = value;
    return true;
}

char pop(Stack *s) {
    if (is_empty(s)) return '\0';
    return s->data[(s->top)--];
}

char peek(Stack *s) {
    if (is_empty(s)) return '\0';
    return s->data[s->top];
}

// Kiểm tra có phải toán tử không
bool is_operator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// Độ ưu tiên toán tử
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Chuyển đổi trung tố sang hậu tố
void infix_to_postfix(const char *infix, char *postfix) {
    Stack *s = create_stack();
    if (s == NULL) return;
    
    int len = strlen(infix);
    int j = 0;
    
    for (int i = 0; i < len; i++) {
        char c = infix[i];
        
        // Bỏ qua khoảng trắng
        if (isspace(c)) continue;
        
        // Nếu là chữ hoặc số (operand)
        if (isalnum(c)) {
            postfix[j++] = c;
            postfix[j++] = ' '; // Thêm dấu cách giữa các token
        }
        // Nếu là ngoặc mở
        else if (c == '(') {
            push(s, c);
        }
        // Nếu là ngoặc đóng
        else if (c == ')') {
            while (!is_empty(s) && peek(s) != '(') {
                postfix[j++] = pop(s);
                postfix[j++] = ' ';
            }
            pop(s); // Xóa dấu '(' khỏi Stack
        }
        // Nếu là toán tử
        else if (is_operator(c)) {
            while (!is_empty(s) && precedence(peek(s)) >= precedence(c)) {
                postfix[j++] = pop(s);
                postfix[j++] = ' ';
            }
            push(s, c);
        }
    }
    
    // Lấy các toán tử còn lại trong stack
    while (!is_empty(s)) {
        postfix[j++] = pop(s);
        postfix[j++] = ' ';
    }
    
    // Loại bỏ dấu cách thừa ở cuối và kết thúc chuỗi
    if (j > 0 && postfix[j - 1] == ' ') {
        postfix[j - 1] = '\0';
    } else {
        postfix[j] = '\0';
    }
    
    free(s);
}

int main() {
    printf("=== BAI TAP 6 ===\n");
    
    const char *infix = "(A * (B + C) - D * E)";
    char postfix[MAX * 2];
    
    printf("Input (infix):   %s\n", infix);
    infix_to_postfix(infix, postfix);
    printf("Output (postfix): %s\n", postfix);
    
    return 0;
}
