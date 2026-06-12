/*
 * BÀI TẬP 9 - MỞ RỘNG CÁC PHÉP TOÁN 1 NGÔI (sin, cos, sqrt, abs, minus)
 * ===================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>

#define MAX 500

// Mặc định pi
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

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

// --- Các hàm phụ trợ chuyển đổi ---
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == 's' || op == 'c' || op == 'q' || op == 'a' || op == 'm') return 3; // Hàm/toán tử 1 ngôi
    return 0;
}

const char* get_op_name(char op) {
    if (op == 's') return "sin";
    if (op == 'c') return "cos";
    if (op == 'q') return "sqrt";
    if (op == 'a') return "abs";
    if (op == 'm') return "minus";
    
    // An toàn trả về toán tử nhị phân dạng chuỗi
    static char buf[2] = {0};
    buf[0] = op;
    return buf;
}

// Chuyển đổi trung tố sang hậu tố hỗ trợ hàm 1 ngôi
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

        // Toán hạng (Số thực)
        if (isdigit(c) || c == '.') {
            while (i < len && (isdigit(infix[i]) || infix[i] == '.')) {
                postfix[j++] = infix[i++];
            }
            postfix[j++] = ' ';
        } 
        // Đọc tên hàm chữ cái (sin, cos, sqrt, abs, minus)
        else if (isalpha(c)) {
            char func[20];
            int f_len = 0;
            while (i < len && isalpha(infix[i])) {
                func[f_len++] = infix[i++];
            }
            func[f_len] = '\0';
            
            if (strcmp(func, "sin") == 0) push_char(s, 's');
            else if (strcmp(func, "cos") == 0) push_char(s, 'c');
            else if (strcmp(func, "sqrt") == 0) push_char(s, 'q');
            else if (strcmp(func, "abs") == 0) push_char(s, 'a');
            else if (strcmp(func, "minus") == 0) push_char(s, 'm');
        } 
        else if (c == '(') {
            push_char(s, c);
            i++;
        } 
        else if (c == ')') {
            while (!is_char_empty(s) && peek_char(s) != '(') {
                char op = pop_char(s);
                j += sprintf(&postfix[j], "%s ", get_op_name(op));
            }
            pop_char(s); // Bỏ dấu '('
            
            // Nếu sau dấu '(' có một tên hàm ở đỉnh Stack, ta lấy tên hàm ra hậu tố
            if (!is_char_empty(s)) {
                char top_op = peek_char(s);
                if (top_op == 's' || top_op == 'c' || top_op == 'q' || top_op == 'a' || top_op == 'm') {
                    j += sprintf(&postfix[j], "%s ", get_op_name(pop_char(s)));
                }
            }
            i++;
        } 
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
            while (!is_char_empty(s) && precedence(peek_char(s)) >= precedence(c)) {
                char op = pop_char(s);
                j += sprintf(&postfix[j], "%s ", get_op_name(op));
            }
            push_char(s, c);
            i++;
        } 
        else {
            i++;
        }
    }

    while (!is_char_empty(s)) {
        char op = pop_char(s);
        j += sprintf(&postfix[j], "%s ", get_op_name(op));
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
        } 
        // Đọc toán tử hoặc tên hàm
        else {
            char word[20];
            int w_len = 0;
            while (i < len && !isspace(postfix[i])) {
                word[w_len++] = postfix[i++];
            }
            word[w_len] = '\0';

            if (strcmp(word, "+") == 0) {
                double op2 = pop_float(s);
                double op1 = pop_float(s);
                push_float(s, op1 + op2);
            } else if (strcmp(word, "-") == 0) {
                double op2 = pop_float(s);
                double op1 = pop_float(s);
                push_float(s, op1 - op2);
            } else if (strcmp(word, "*") == 0) {
                double op2 = pop_float(s);
                double op1 = pop_float(s);
                push_float(s, op1 * op2);
            } else if (strcmp(word, "/") == 0) {
                double op2 = pop_float(s);
                double op1 = pop_float(s);
                push_float(s, op1 / op2);
            } else if (strcmp(word, "sin") == 0) {
                double op = pop_float(s);
                push_float(s, sin(op));
            } else if (strcmp(word, "cos") == 0) {
                double op = pop_float(s);
                push_float(s, cos(op));
            } else if (strcmp(word, "sqrt") == 0) {
                double op = pop_float(s);
                push_float(s, sqrt(op));
            } else if (strcmp(word, "abs") == 0) {
                double op = pop_float(s);
                push_float(s, fabs(op));
            } else if (strcmp(word, "minus") == 0) {
                double op = pop_float(s);
                push_float(s, -op);
            }
        }
    }

    double result = pop_float(s);
    free_float_stack(s);
    return result;
}

int main() {
    printf("=== BAI TAP 9 ===\n");

    // Thử nghiệm biểu thức chứa cả hàm 1 ngôi:
    // sin(M_PI / 2) + sqrt(16) - minus(5)
    // Giá trị mong đợi: sin(1.57079) + 4 - (-5) = 1 + 4 + 5 = 10.0
    char infix[MAX];
    sprintf(infix, "sin(%.10f / 2) + sqrt(16) - minus(5)", M_PI);
    
    char postfix[MAX * 2];

    printf("Infix expression:   %s\n", infix);
    
    infix_to_postfix(infix, postfix);
    printf("Postfix expression: %s\n", postfix);

    double result = evaluate_postfix(postfix);
    printf("Result:             %.4f\n", result);

    return 0;
}
