/*
 * BÀI TẬP 5 - TẠO HAI DANH SÁCH LIÊN KẾT ĐƠN CHẴN VÀ LẺ TỪ MẢNG
 * ==========================================================
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
void display(SinglyLinkedList *list, const char *name) {
    if (is_empty(list)) {
        printf("%s = NULL\n", name);
        return;
    }
    printf("%s = ", name);
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
    printf("=== BAI TAP 5 ===\n");
    int a[] = {5, 3, 8, 2, 7};
    int n = sizeof(a) / sizeof(a[0]);

    printf("Input: a[] = {");
    for (int i = 0; i < n; i++) {
        printf("%d", a[i]);
        if (i < n - 1) printf(", ");
    }
    printf("}\n");

    SinglyLinkedList *list1 = create_list(); // Chứa các số chẵn
    SinglyLinkedList *list2 = create_list(); // Chứa các số lẻ

    if (list1 == NULL || list2 == NULL) {
        printf("Loi khoi tao danh sach!\n");
        return 1;
    }

    // Tách các số chẵn vào list1 và số lẻ vào list2 (sắp xếp tăng dần)
    for (int i = 0; i < n; i++) {
        Node *node = create_node(a[i]);
        if (node != NULL) {
            if (a[i] % 2 == 0) {
                insert_sorted(list1, node);
            } else {
                insert_sorted(list2, node);
            }
        }
    }

    // Hiển thị kết quả
    display(list1, "list1 (so chan)");
    display(list2, "list2 (so le)");

    // Giải phóng bộ nhớ
    free_list(list1);
    free_list(list2);

    return 0;
}
