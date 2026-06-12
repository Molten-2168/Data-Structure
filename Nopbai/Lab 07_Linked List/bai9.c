/*
 * BÀI TẬP 9 - DANH SÁCH LIÊN KẾT ĐÔI VÀ HOÁN VỊ ĐỐI XỨNG CÁC PHẦN TỬ
 * ================================================================
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

// Thêm một node vào đầu danh sách
void insert_head(DoublyLinkedList *list, Node *node) {
    if (node == NULL) return;
    
    if (is_empty(list)) {
        list->head = node;
        list->tail = node;
    } else {
        node->next = list->head;
        list->head->prev = node;
        list->head = node;
    }
}

// Thêm một node vào cuối danh sách (để hỗ trợ khởi tạo dữ liệu theo thứ tự)
void insert_tail(DoublyLinkedList *list, Node *node) {
    if (node == NULL) return;
    
    if (is_empty(list)) {
        list->head = node;
        list->tail = node;
    } else {
        node->prev = list->tail;
        list->tail->next = node;
        list->tail = node;
    }
}

// In danh sách ra màn hình
void display(DoublyLinkedList *list) {
    if (is_empty(list)) {
        printf("Danh sach rong!\n");
        return;
    }
    Node *cur = list->head;
    while (cur != NULL) {
        printf("%d", cur->data);
        if (cur->next != NULL) {
            printf(" <=> ");
        }
        cur = cur->next;
    }
    printf("\n");
}

// Hoán vị (interchange) giá trị (value) của node đầu tiên với node cuối cùng, 
// node thứ hai với node kế cuối, v.v.
void interchange_symmetric(DoublyLinkedList *list) {
    if (is_empty(list) || list->head == list->tail) return;
    
    Node *left = list->head;
    Node *right = list->tail;
    
    while (left != NULL && right != NULL && left != right && left->prev != right) {
        // Hoán đổi dữ liệu
        int temp = left->data;
        left->data = right->data;
        right->data = temp;
        
        // Di chuyển con trỏ
        left = left->next;
        right = right->prev;
    }
}

// Xóa tất cả các node trong danh sách
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
    printf("=== BAI TAP 9 ===\n");
    
    DoublyLinkedList *list = create_list();
    if (list == NULL) {
        printf("Loi khoi tao danh sach!\n");
        return 1;
    }
    
    // Khoi tao du lieu mau: 5 <=> 2 <=> 8 <=> 1 <=> 3 <=> 7
    int values[] = {5, 2, 8, 1, 3, 7};
    int n = sizeof(values) / sizeof(values[0]);
    for (int i = 0; i < n; i++) {
        insert_tail(list, create_node(values[i]));
    }
    
    printf("Danh sach ban dau: ");
    display(list);
    
    // Thuc hien hoan vi doi xung
    interchange_symmetric(list);
    
    printf("Danh sach sau khi hoan vi doi xung: ");
    display(list);
    
    free_list(list);
    return 0;
}
