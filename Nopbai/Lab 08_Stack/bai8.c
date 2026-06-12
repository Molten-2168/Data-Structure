/*
 * BÀI TẬP 8 - TÍNH GIÁ TRỊ BIỂU THỨC TRUNG TỐ SỐ THỰC (STACK SLL)
 * =============================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX 300

// --- Stack ký tự dùng SLL ---
typedef struct CharNode {
    char data;
    struct CharNode *next;
} CharNode;

typedef struct {
    CharNode *top;
} CharStack;

CharStack* create_char_stack() {
    CharStack *s = (CharStack *)malloc(sizeof(CharStack));
    if (s != NULL) s->top = NULL;
    return s;
}

bool is_char_empty(CharStack *s) { return s->top == NULL; }

void push_char(CharStack *s, char val) {
    CharNode *node = (CharNode *)malloc(sizeof(CharNode));
    if (node != NULL) {
        node->data = val;
        node->next = s->top;
        s->top = node;
    }
}

char pop_char(CharStack *s) {
    if (is_char_empty(s)) return '\0';
    CharNode *temp = s->top;
    char val = temp->data;
    s->top = s->top->next;
    free(temp);
    return val;
}

char peek_char(CharStack *s) {
    if (is_char_empty(s)) return '\0';
    return s->top->data;
}

void free_char_stack(CharStack *s) {
    while (!is_char_empty(s)) {
        pop_char(s);
    }
    free(s);
}

// --- Stack số thực dùng SLL ---
typedef struct FloatNode {
    double data;
    struct FloatNode *next;
} FloatNode;

typedef struct {
    FloatNode *top;
} FloatStack;

FloatStack* create_float_stack() {
    FloatStack *s = (FloatStack *)malloc(sizeof(FloatStack));
    if (s != NULL) s->top = NULL;
    return s;
}

bool is_float_empty(FloatStack *s) { return s->top == NULL; }

void push_float(FloatStack *s, double val) {
    FloatNode *node = (FloatNode *)malloc(sizeof(FloatNode));
    if (node != NULL) {
        node->data = val;
        node->next = s->top;
        s->top = node;
    }
}

double pop_float(FloatStack *s) {
    if (is_float_empty(s)) return 0.0;
    FloatNode *temp = s->top;
    double val = temp->data;
    s->top = s->top->next;
    free(temp);
    return val;
}

void free_float_stack(FloatStack *s) {
    while (!is_float_empty(s)) {
        pop_float(s);
    }
    free(s);
}

// --- Các hàm hỗ trợ tính toán ---
bool is_operator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Chuyển đổi trung tố sang hậu tố (hỗ trợ số thực)
void infix_to_postfix(const char *infix, char *postfix) {
    CharStack *s = create_char_stack();
    if (s == NULL) return;

    int len = strlen(infix);
    int j = 0;

    for (int i = 0; i < len; ) {
        char c = infix[i];

        if (isspace(c)) {
            i++;
            continue;
        }

        // Đọc toàn bộ số thực (bao gồm dấu chấm thập phân)
        if (isdigit(c) || c == '.') {
            while (i < len && (isdigit(infix[i]) || infix[i] == '.')) {
                postfix[j++] = infix[i++];
            }
            postfix[j++] = ' ';
        } else if (c == '(') {
            push_char(s, c);
            i++;
        } else if (c == ')') {
            while (!is_char_empty(s) && peek_char(s) != '(') {
                postfix[j++] = pop_char(s);
                postfix[j++] = ' ';
            }
            pop_char(s); // Bỏ dấu '('
            i++;
        } else if (is_operator(c)) {
            while (!is_char_empty(s) && precedence(peek_char(s)) >= precedence(c)) {
                postfix[j++] = pop_char(s);
                postfix[j++] = ' ';
            }
            push_char(s, c);
            i++;
        } else {
            i++;
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

    free_char_stack(s);
}

// Tính giá trị biểu thức hậu tố
double evaluate_postfix(const char *postfix) {
    FloatStack *s = create_float_stack();
    if (s == NULL) return 0.0;

    int len = strlen(postfix);
    for (int i = 0; i < len; ) {
        char c = postfix[i];

        if (isspace(c)) {
            i++;
            continue;
        }

        // Đọc số thực
        if (isdigit(c) || c == '.') {
            char *endptr;
            double val = strtod(&postfix[i], &endptr);
            push_float(s, val);
            i += (endptr - &postfix[i]);
        } else if (is_operator(c)) {
            double op2 = pop_float(s);
            double op1 = pop_float(s);
            double res = 0.0;

            switch (c) {
                case '+': res = op1 + op2; break;
                case '-': res = op1 - op2; break;
                case '*': res = op1 * op2; break;
                case '/': res = op1 / op2; break;
            }
            push_float(s, res);
            i++;
        } else {
            i++;
        }
    }

    double result = pop_float(s);
    free_float_stack(s);
    return result;
}

int main() {
    printf("=== BAI TAP 8 ===\n");

    const char *infix = "(1.5 + (3 - 2.5)) * (5.5 - (1.5)) + 1.2 / 2.0";
    char postfix[MAX * 2];

    printf("Infix expression:   %s\n", infix);
    
    infix_to_postfix(infix, postfix);
    printf("Postfix expression: %s\n", postfix);

    double result = evaluate_postfix(postfix);
    printf("Result:             %.4f\n", result);

    return 0;
}
