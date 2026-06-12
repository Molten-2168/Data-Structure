/*
 * BÀI TẬP 7 - TÍNH GIÁ TRỊ BIỂU THỨC TRUNG TỐ (TOÁN HẠNG 1 CHỮ SỐ [0, 9])
 * =====================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX 200

// --- Cấu trúc Stack ký tự ---
typedef struct {
    char data[MAX];
    int top;
} CharStack;

CharStack* create_char_stack() {
    CharStack *s = (CharStack *)malloc(sizeof(CharStack));
    if (s != NULL) s->top = -1;
    return s;
}

bool is_char_empty(CharStack *s) { return s->top == -1; }
bool is_char_full(CharStack *s) { return s->top == MAX - 1; }

bool push_char(CharStack *s, char val) {
    if (is_char_full(s)) return false;
    s->data[++(s->top)] = val;
    return true;
}

char pop_char(CharStack *s) {
    if (is_char_empty(s)) return '\0';
    return s->data[(s->top)--];
}

char peek_char(CharStack *s) {
    if (is_char_empty(s)) return '\0';
    return s->data[s->top];
}

// --- Cấu trúc Stack số thực (double) để tính toán ---
typedef struct {
    double data[MAX];
    int top;
} DoubleStack;

DoubleStack* create_double_stack() {
    DoubleStack *s = (DoubleStack *)malloc(sizeof(DoubleStack));
    if (s != NULL) s->top = -1;
    return s;
}

bool is_double_empty(DoubleStack *s) { return s->top == -1; }
bool is_double_full(DoubleStack *s) { return s->top == MAX - 1; }

bool push_double(DoubleStack *s, double val) {
    if (is_double_full(s)) return false;
    s->data[++(s->top)] = val;
    return true;
}

double pop_double(DoubleStack *s) {
    if (is_double_empty(s)) return 0.0;
    return s->data[(s->top)--];
}

// --- Các hàm hỗ trợ chuyển đổi ---
bool is_operator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Chuyển đổi trung tố sang hậu tố
void infix_to_postfix(const char *infix, char *postfix) {
    CharStack *s = create_char_stack();
    if (s == NULL) return;

    int len = strlen(infix);
    int j = 0;

    for (int i = 0; i < len; i++) {
        char c = infix[i];

        if (isspace(c)) continue;

        if (isdigit(c)) {
            postfix[j++] = c;
            postfix[j++] = ' ';
        } else if (c == '(') {
            push_char(s, c);
        } else if (c == ')') {
            while (!is_char_empty(s) && peek_char(s) != '(') {
                postfix[j++] = pop_char(s);
                postfix[j++] = ' ';
            }
            pop_char(s); // Bỏ '('
        } else if (is_operator(c)) {
            while (!is_char_empty(s) && precedence(peek_char(s)) >= precedence(c)) {
                postfix[j++] = pop_char(s);
                postfix[j++] = ' ';
            }
            push_char(s, c);
        }
    }

    while (!is_char_empty(s)) {
        postfix[j++] = pop_char(s);
        postfix[j++] = ' ';
    }

    if (j > 0 && postfix[j - 1] == ' ') {
        postfix[j - 1] = '\0';
    } else {
        postfix[j] = '\0';
    }

    free(s);
}

// Tính giá trị của biểu thức hậu tố
double evaluate_postfix(const char *postfix) {
    DoubleStack *s = create_double_stack();
    if (s == NULL) return 0.0;

    int len = strlen(postfix);
    for (int i = 0; i < len; i++) {
        char c = postfix[i];

        if (isspace(c)) continue;

        // Nếu là chữ số (toán hạng)
        if (isdigit(c)) {
            push_double(s, c - '0');
        } 
        // Nếu là toán tử
        else if (is_operator(c)) {
            double op2 = pop_double(s);
            double op1 = pop_double(s);
            double res = 0.0;

            switch (c) {
                case '+': res = op1 + op2; break;
                case '-': res = op1 - op2; break;
                case '*': res = op1 * op2; break;
                case '/': 
                    if (op2 != 0) {
                        res = op1 / op2; 
                    } else {
                        printf("Loi: Chia cho 0!\n");
                    }
                    break;
            }
            push_double(s, res);
        }
    }

    double result = pop_double(s);
    free(s);
    return result;
}

int main() {
    printf("=== BAI TAP 7 ===\n");

    const char *infix = "(1 + (3 - 2)) * (5 - (1)) + 1 / 2";
    char postfix[MAX * 2];

    printf("Infix expression:   %s\n", infix);
    
    infix_to_postfix(infix, postfix);
    printf("Postfix expression: %s\n", postfix);

    double result = evaluate_postfix(postfix);
    printf("Result:             %.2f\n", result);

    return 0;
}
