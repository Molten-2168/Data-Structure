/*
 * BÀI TẬP 3 - CHÈN CÓ THỨ TỰ TĂNG DẦN TỪ MẢNG VÀO DANH SÁCH LIÊN KẾT ĐƠN
 * ====================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Định nghĩa cấu trúc Node
typedef struct Node {
    int data;
    struct Node *next;
} Node;

// Định nghĩa cấu trúc danh sách liên kết đơn
typedef struct {
    Node *head;
} SinglyLinkedList;

// Khởi tạo danh sách
SinglyLinkedList* create_list() {
    SinglyLinkedList *list = (SinglyLinkedList *)malloc(sizeof(SinglyLinkedList));
    if (list != NULL) {
        list->head = NULL;
    }
    return list;
}

// Tạo Node mới
Node* create_node(int data) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (node != NULL) {
        node->data = data;
        node->next = NULL;
    }
    return node;
}

// Kiểm tra danh sách rỗng
bool is_empty(SinglyLinkedList *list) {
    return list->head == NULL;
}

// Thêm Node vào danh sách giữ nguyên thứ tự tăng dần
void insert_sorted(SinglyLinkedList *list, Node *node) {
    if (node == NULL) return;
    Node *cur = list->head;
    Node *prev = NULL;

    while (cur != NULL && cur->data < node->data) {
        prev = cur;
        cur = cur->next;
    }

    if (prev == NULL) { // Chèn vào đầu danh sách
        node->next = list->head;
        list->head = node;
    } else { // Chèn vào giữa hoặc cuối danh sách
        prev->next = node;
        node->next = cur;
    }
}

// In ra màn hình tất cả các phần tử
void display(SinglyLinkedList *list) {
    if (is_empty(list)) {
        printf("Danh sach rong!\n");
        return;
    }
    printf("num_list = ");
    Node *cur = list->head;
    while (cur != NULL) {
        printf("%d", cur->data);
        if (cur->next != NULL) {
            printf(" -> ");
        }
        cur = cur->next;
    }
    printf("\n");
}

// Xóa tất cả các node trong danh sách
void delete_all(SinglyLinkedList *list) {
    while (!is_empty(list)) {
        Node *temp = list->head;
        list->head = list->head->next;
        free(temp);
    }
}

// Giải phóng danh sách
void free_list(SinglyLinkedList *list) {
    delete_all(list);
    free(list);
}

int main() {
    printf("=== BAI TAP 3 ===\n");
    int a[] = {5, 3, 8, 2, 7};
    int n = sizeof(a) / sizeof(a[0]);

    printf("Input: a[] = {");
    for (int i = 0; i < n; i++) {
        printf("%d", a[i]);
        if (i < n - 1) printf(", ");
    }
    printf("}\n");

    SinglyLinkedList *list = create_list();
    if (list == NULL) {
        printf("Loi khoi tao danh sach!\n");
        return 1;
    }

    // Chèn từng phần tử từ mảng a[] vào danh sách theo thứ tự tăng dần
    for (int i = 0; i < n; i++) {
        Node *node = create_node(a[i]);
        if (node != NULL) {
            insert_sorted(list, node);
        }
    }

    // Hiển thị kết quả
    display(list);

    free_list(list);
    return 0;
}
