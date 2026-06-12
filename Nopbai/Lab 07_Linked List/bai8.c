/*
 * BÀI TẬP 8 - TÌM PHẦN TỬ LỚN NHẤT VÀ NHỎ NHẤT TRONG DANH SÁCH LIÊN KẾT ĐƠN
 * ======================================================================
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

// Thêm Node vào đầu danh sách
void insert_head(SinglyLinkedList *list, Node *node) {
    if (node == NULL) return;
    node->next = list->head;
    list->head = node;
}

// In danh sách ra màn hình
void display(SinglyLinkedList *list) {
    if (is_empty(list)) {
        printf("Danh sach rong!\n");
        return;
    }
    printf("List: ");
    Node *cur = list->head;
    while (cur != NULL) {
        printf("%d -> ", cur->data);
        cur = cur->next;
    }
    printf("NULL\n");
}

// Tìm giá trị lớn nhất trong danh sách
bool find_max(SinglyLinkedList *list, int *max_val) {
    if (is_empty(list)) return false;
    
    Node *cur = list->head;
    *max_val = cur->data;
    cur = cur->next;
    
    while (cur != NULL) {
        if (cur->data > *max_val) {
            *max_val = cur->data;
        }
        cur = cur->next;
    }
    return true;
}

// Tìm giá trị nhỏ nhất trong danh sách
bool find_min(SinglyLinkedList *list, int *min_val) {
    if (is_empty(list)) return false;
    
    Node *cur = list->head;
    *min_val = cur->data;
    cur = cur->next;
    
    while (cur != NULL) {
        if (cur->data < *min_val) {
            *min_val = cur->data;
        }
        cur = cur->next;
    }
    return true;
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
    printf("=== BAI TAP 8 ===\n");
    
    SinglyLinkedList *list = create_list();
    if (list == NULL) {
        printf("Loi khoi tao danh sach!\n");
        return 1;
    }
    
    // Khoi tao du lieu mau
    int values[] = {12, 45, 2, 89, 23, 7, 56};
    int n = sizeof(values) / sizeof(values[0]);
    for (int i = 0; i < n; i++) {
        insert_head(list, create_node(values[i]));
    }
    
    // Hien thi danh sach
    display(list);
    
    // Tim max, min
    int max_val, min_val;
    if (find_max(list, &max_val) && find_min(list, &min_val)) {
        printf("Gia tri lon nhat (Max) trong danh sach: %d\n", max_val);
        printf("Gia tri nho nhat (Min) trong danh sach: %d\n", min_val);
    } else {
        printf("Danh sach rong, khong the tim thay Max/Min!\n");
    }
    
    free_list(list);
    return 0;
}
