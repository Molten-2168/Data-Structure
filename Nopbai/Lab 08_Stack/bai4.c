/*
 * BÀI TẬP 4 - ĐẢO NGƯỢC CHUỖI KÝ TỰ DÙNG STACK
 * ===========================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX 500

typedef struct {
    char data[MAX];
    int top;
} CharStack;

CharStack* create_stack() {
    CharStack *s = (CharStack *)malloc(sizeof(CharStack));
    if (s != NULL) {
        s->top = -1;
    }
    return s;
}

bool is_empty(CharStack *s) {
    return s->top == -1;
}

bool is_full(CharStack *s) {
    return s->top == MAX - 1;
}

bool push(CharStack *s, char value) {
    if (is_full(s)) return false;
    s->data[++(s->top)] = value;
    return true;
}

char pop(CharStack *s) {
    if (is_empty(s)) return '\0';
    return s->data[(s->top)--];
}

int main() {
    printf("=== BAI TAP 4 ===\n");
    
    char s[] = "HELLO STUDENTS";
    printf("Input: s = \"%s\"\n", s);
    
    // Khoi tao Stack
    CharStack *stack = create_stack();
    if (stack == NULL) {
        printf("Loi khoi tao stack!\n");
        return 1;
    }

    // Dua cac ky tu trong chuoi vao stack (Push)
    int len = strlen(s);
    for (int i = 0; i < len; i++) {
        push(stack, s[i]);
    }

    // Lay cac ky tu tu stack ra (Pop) va dua vao lai chuoi
    for (int i = 0; i < len; i++) {
        s[i] = pop(stack);
    }

    // In chuoi sau khi dao nguoc
    printf("Output: \"%s\"\n", s);

    // Giai phong
    free(stack);
    return 0;
}
