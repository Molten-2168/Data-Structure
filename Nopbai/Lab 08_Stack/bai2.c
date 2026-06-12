/*
 * BÀI TẬP 2 - NGĂN XẾP CÀI ĐẶT BẰNG DANH SÁCH LIÊN KẾT ĐƠN (SỐ NGUYÊN DƯƠNG)
 * =========================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Định nghĩa cấu trúc Node
typedef struct Node {
    int data;
    struct Node *next;
} Node;

// Định nghĩa cấu trúc Stack
typedef struct {
    Node *top; // Con trỏ quản lý node ở đỉnh ngăn xếp
} Stack;

// Khởi tạo Node mới
Node* create_node(int data) {
    if (data <= 0) {
        printf("Loi: Chi chap nhan so nguyen duong (> 0)!\n");
        return NULL;
    }
    Node *node = (Node *)malloc(sizeof(Node));
    if (node != NULL) {
        node->data = data;
        node->next = NULL;
    }
    return node;
}

// Khởi tạo Stack
Stack* create_stack() {
    Stack *s = (Stack *)malloc(sizeof(Stack));
    if (s != NULL) {
        s->top = NULL;
    }
    return s;
}

// Kiểm tra Stack rỗng
bool is_empty(Stack *s) {
    return s->top == NULL;
}

// Thêm phần tử vào đỉnh Stack
void push(Stack *s, Node *node) {
    if (node == NULL) return;
    node->next = s->top;
    s->top = node;
}

// Lấy phần tử khỏi đỉnh Stack
Node* pop(Stack *s) {
    if (is_empty(s)) {
        return NULL;
    }
    Node *temp = s->top;
    s->top = s->top->next;
    return temp;
}

// Xem phần tử ở đỉnh Stack
Node* peek(Stack *s) {
    return s->top;
}

// Hiển thị các phần tử từ đỉnh xuống đáy
void display(Stack *s) {
    if (is_empty(s)) {
        printf("Ngan xep rong!\n");
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

// Giải phóng Stack
void free_stack(Stack *s) {
    while (!is_empty(s)) {
        Node *temp = pop(s);
        free(temp);
    }
    free(s);
}

int main() {
    Stack *s = create_stack();
    if (s == NULL) {
        printf("Loi khoi tao ngan xep!\n");
        return 1;
    }

    int choice, val;
    Node *node_ptr;

    do {
        printf("\n=== BAI TAP 2 MENU (STACK DANH SACH LIEN KET) ===\n");
        printf("1. Day phan tu vao ngan xep (Push)\n");
        printf("2. Lay phan tu ra khoi ngan xep (Pop)\n");
        printf("3. Xem phan tu o dinh ngan xep (Peek)\n");
        printf("4. Hien thi toan bo ngan xep (Display)\n");
        printf("0. Thoat (Exit)\n");
        printf("Lua chon cua ban: ");
        if (scanf("%d", &choice) != 1) {
            printf("Lua chon khong hop le!\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1:
                printf("Nhap so nguyen duong can them: ");
                if (scanf("%d", &val) == 1) {
                    Node *new_node = create_node(val);
                    if (new_node != NULL) {
                        push(s, new_node);
                        printf("Da them %d vao ngan xep.\n", val);
                    }
                } else {
                    printf("Loi doc du lieu!\n");
                }
                break;
            case 2:
                node_ptr = pop(s);
                if (node_ptr != NULL) {
                    printf("Phan tu lay ra (Pop): %d\n", node_ptr->data);
                    free(node_ptr);
                } else {
                    printf("Ngan xep rong, khong the Pop!\n");
                }
                break;
            case 3:
                node_ptr = peek(s);
                if (node_ptr != NULL) {
                    printf("Phan tu o dinh (Peek): %d\n", node_ptr->data);
                } else {
                    printf("Ngan xep rong!\n");
                }
                break;
            case 4:
                display(s);
                break;
            case 0:
                printf("Dang thoat va giai phong bo nho...\n");
                break;
            default:
                printf("Lua chon khong hop le!\n");
        }
        // Clear buffer
        while (getchar() != '\n');
    } while (choice != 0);

    free_stack(s);
    return 0;
}
