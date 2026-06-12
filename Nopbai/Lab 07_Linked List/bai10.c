/*
 * BÀI TẬP 10 - CHÈN SẮP XẾP VÀ DUYỆT HAI CHIỀU TRÊN DANH SÁCH LIÊN KẾT ĐÔI
 * ======================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Định nghĩa cấu trúc Node của danh sách liên kết đôi
typedef struct Node {
    int data;
    struct Node *prev;
    struct Node *next;
} Node;

// Định nghĩa cấu trúc danh sách liên kết đôi
typedef struct {
    Node *head;
    Node *tail;
} DoublyLinkedList;

// Khởi tạo danh sách
DoublyLinkedList* create_list() {
    DoublyLinkedList *list = (DoublyLinkedList *)malloc(sizeof(DoublyLinkedList));
    if (list != NULL) {
        list->head = NULL;
        list->tail = NULL;
    }
    return list;
}

// Tạo Node mới
Node* create_node(int data) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (node != NULL) {
        node->data = data;
        node->prev = NULL;
        node->next = NULL;
    }
    return node;
}

// Kiểm tra danh sách rỗng
bool is_empty(DoublyLinkedList *list) {
    return list->head == NULL;
}

// Chèn Node vào danh sách liên kết đôi theo thứ tự tăng dần
void insert_sorted(DoublyLinkedList *list, Node *node) {
    if (node == NULL) return;
    
    // TH1: Danh sách rỗng
    if (is_empty(list)) {
        node->prev = NULL;
        node->next = NULL;
        list->head = node;
        list->tail = node;
        return;
    }
    
    // TH2: Chèn vào đầu danh sách (nhỏ hơn phần tử đầu hiện tại)
    if (node->data <= list->head->data) {
        node->next = list->head;
        node->prev = NULL;
        list->head->prev = node;
        list->head = node;
        return;
    }
    
    // TH3: Chèn vào cuối danh sách (lớn hơn phần tử cuối hiện tại)
    if (node->data >= list->tail->data) {
        node->prev = list->tail;
        node->next = NULL;
        list->tail->next = node;
        list->tail = node;
        return;
    }
    
    // TH4: Chèn vào giữa danh sách
    Node *cur = list->head;
    while (cur != NULL && cur->data < node->data) {
        cur = cur->next;
    }
    
    // Chèn node vào trước cur
    node->next = cur;
    node->prev = cur->prev;
    cur->prev->next = node;
    cur->prev = node;
}

// Duyệt và in danh sách từ đầu đến cuối (Forward)
void display_forward(DoublyLinkedList *list) {
    if (is_empty(list)) {
        printf("Danh sach rong!\n");
        return;
    }
    printf("Forward (head -> tail): ");
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

// Duyệt và in danh sách từ cuối về đầu (Backward)
void display_backward(DoublyLinkedList *list) {
    if (is_empty(list)) {
        printf("Danh sach rong!\n");
        return;
    }
    printf("Backward (tail -> head): ");
    Node *cur = list->tail;
    while (cur != NULL) {
        printf("%d", cur->data);
        if (cur->prev != NULL) {
            printf(" -> ");
        }
        cur = cur->prev;
    }
    printf("\n");
}

// Xóa tất cả các node
void delete_all(DoublyLinkedList *list) {
    Node *cur = list->head;
    while (cur != NULL) {
        Node *temp = cur;
        cur = cur->next;
        free(temp);
    }
    list->head = NULL;
    list->tail = NULL;
}

// Giải phóng danh sách
void free_list(DoublyLinkedList *list) {
    delete_all(list);
    free(list);
}

int main() {
    printf("=== BAI TAP 10 ===\n");
    
    int a[] = {5, 3, 8, 2, 7};
    int n = sizeof(a) / sizeof(a[0]);
    
    printf("Input: a[] = {");
    for (int i = 0; i < n; i++) {
        printf("%d", a[i]);
        if (i < n - 1) printf(", ");
    }
    printf("}\n\n");
    
    DoublyLinkedList *list = create_list();
    if (list == NULL) {
        printf("Loi khoi tao danh sach!\n");
        return 1;
    }
    
    // Lần lượt lấy từng phần tử a[i] thêm vào DLL theo thứ tự tăng dần
    for (int i = 0; i < n; i++) {
        insert_sorted(list, create_node(a[i]));
    }
    
    // In theo chiều xuôi
    display_forward(list);
    
    // In theo chiều ngược
    display_backward(list);
    
    free_list(list);
    return 0;
}
