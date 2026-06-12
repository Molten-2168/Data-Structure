/*
 * NGĂN XẾP (Stack) - Cài đặt bằng Danh sách liên kết đơn
 * ========================================================
 * Khác với mảng tĩnh, ngăn xếp dùng danh sách liên kết không bị giới hạn 
 * kích thước tối đa và tận dụng bộ nhớ Heap động linh hoạt.
 * Node ở đỉnh Stack đóng vai trò là Head của danh sách liên kết đơn.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Định nghĩa cấu trúc Node
typedef struct Node {
    int data;
    struct Node *next;
} Node;

// Định nghĩa cấu trúc Stack
typedef struct {
    Node *top; // Con trỏ tới phần tử ở đỉnh ngăn xếp
} Stack;

// --- Khởi tạo Node mới ---
Node* create_node(int data) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (node != NULL) {
        node->data = data;
        node->next = NULL;
    }
    return node;
}

// --- Khởi tạo Stack ---
Stack* create_stack() {
    Stack *s = (Stack *)malloc(sizeof(Stack));
    if (s != NULL) {
        s->top = NULL;
    }
    return s;
}

// --- Kiểm tra Stack rỗng ---
bool is_empty(Stack *s) {
    return s->top == NULL;
}

// --- Push: Thêm phần tử vào đỉnh (O(1)) ---
void push(Stack *s, Node *node) {
    if (node == NULL) return;
    node->next = s->top;
    s->top = node;
}

// --- Pop: Lấy phần tử khỏi đỉnh (O(1)) ---
Node* pop(Stack *s) {
    if (is_empty(s)) return NULL;
    Node *temp = s->top;
    s->top = s->top->next;
    return temp; // Trả về con trỏ tới Node để bên ngoài tự giải phóng hoặc sử dụng tiếp
}

// --- Peek: Xem phần tử đỉnh (O(1)) ---
Node* peek(Stack *s) {
    return s->top;
}

// --- Hiển thị các phần tử từ đỉnh xuống đáy ---
void display(Stack *s) {
    if (is_empty(s)) {
        printf("Stack rong!\n");
        return;
    }
    printf("Top -> ");
    Node *cur = s->top;
    while (cur != NULL) {
        printf("%d -> ", cur->data);
        cur = cur->next;
    }
    printf("NULL\n");
}

// --- Giải phóng Stack ---
void free_stack(Stack *s) {
    while (!is_empty(s)) {
        Node *temp = pop(s);
        free(temp);
    }
    free(s);
}

int main() {
    Stack *s = create_stack();
    if (s == NULL) return 1;

    int values[] = {7, 2, 5, 8, 4};
    int n = sizeof(values) / sizeof(values[0]);

    printf("=== KIỂM TRA STACK LIÊN KẾT ĐƠN (LINKED LIST STACK) ===\n\n");
    printf("Day gia tri vao stack (Push): ");
    for (int i = 0; i < n; i++) {
        printf("%d ", values[i]);
        push(s, create_node(values[i]));
    }
    printf("\n");
    display(s);

    // Thao tác Pop
    Node *popped = pop(s);
    if (popped != NULL) {
        printf("\nLay ra (Pop): %d\n", popped->data);
        free(popped); // Giải phóng bộ nhớ của Node bị gỡ ra
    }
    display(s);

    // Thao tác Peek
    Node *top_node = peek(s);
    if (top_node != NULL) {
        printf("\nXem dinh (Peek): %d\n", top_node->data);
    }

    free_stack(s);
    return 0;
}
