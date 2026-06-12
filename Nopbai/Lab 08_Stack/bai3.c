/*
 * BÀI TẬP 3 - ĐẢO NGƯỢC CÁC PHẦN TỬ TRONG MẢNG DÙNG STACK
 * ======================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

typedef struct {
    int data[MAX];
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

bool push(Stack *s, int value) {
    if (is_full(s)) return false;
    s->data[++(s->top)] = value;
    return true;
}

int pop(Stack *s) {
    if (is_empty(s)) return -1;
    return s->data[(s->top)--];
}

int main() {
    printf("=== BAI TAP 3 ===\n");
    
    int a[] = {1, 2, 3, 4, 5};
    int n = sizeof(a) / sizeof(a[0]);
    
    // In mang ban dau
    printf("Input: a[] = {");
    for (int i = 0; i < n; i++) {
        printf("%d", a[i]);
        if (i < n - 1) printf(", ");
    }
    printf("}\n");

    // Khoi tao Stack
    Stack *s = create_stack();
    if (s == NULL) {
        printf("Loi khoi tao stack!\n");
        return 1;
    }

    // Dua cac phan tu cua mang vao stack (Push)
    for (int i = 0; i < n; i++) {
        push(s, a[i]);
    }

    // Lay cac phan tu tu stack tra nguoc ve mang (Pop)
    for (int i = 0; i < n; i++) {
        a[i] = pop(s);
    }

    // In mang sau khi dao nguoc
    printf("Output: ");
    for (int i = 0; i < n; i++) {
        printf("%d", a[i]);
        if (i < n - 1) printf(", ");
    }
    printf("\n");

    // Giai phong bo nho
    free(s);
    return 0;
}
