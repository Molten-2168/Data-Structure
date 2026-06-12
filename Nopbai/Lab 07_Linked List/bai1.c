/*
 * BÀI TẬP 1 - DANH SÁCH LIÊN KẾT ĐƠN KÝ TỰ CHỮ HOA
 * ===============================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

// Định nghĩa cấu trúc Node
typedef struct Node {
    char data;
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

// Tạo Node mới (tự động chuyển ký tự thành chữ hoa)
Node* create_node(char data) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (node != NULL) {
        node->data = toupper((unsigned char)data);
        node->next = NULL;
    }
    return node;
}

// Kiểm tra danh sách rỗng
bool is_empty(SinglyLinkedList *list) {
    return list->head == NULL;
}

// Thêm một phần tử vào đầu danh sách
void insert_head(SinglyLinkedList *list, Node *node) {
    if (node == NULL) return;
    node->next = list->head;
    list->head = node;
}

// Xóa một node ở đầu danh sách
void delete_head(SinglyLinkedList *list) {
    if (is_empty(list)) return;
    Node *temp = list->head;
    list->head = list->head->next;
    free(temp);
}

// In ra màn hình tất cả các phần tử
void display(SinglyLinkedList *list) {
    if (is_empty(list)) {
        printf("Danh sach rong!\n");
        return;
    }
    printf("List: ");
    Node *cur = list->head;
    while (cur != NULL) {
        printf("%c -> ", cur->data);
        cur = cur->next;
    }
    printf("NULL\n");
}

// Tìm kiếm một phần tử trong danh sách
Node* search(SinglyLinkedList *list, char value) {
    char upper_val = toupper((unsigned char)value);
    Node *cur = list->head;
    while (cur != NULL) {
        if (cur->data == upper_val) return cur;
        cur = cur->next;
    }
    return NULL;
}

// Xóa tất cả các node trong danh sách
void delete_all(SinglyLinkedList *list) {
    while (!is_empty(list)) {
        delete_head(list);
    }
}

// Giải phóng bộ nhớ danh sách
void free_list(SinglyLinkedList *list) {
    delete_all(list);
    free(list);
}

int main() {
    SinglyLinkedList *list = create_list();
    if (list == NULL) {
        printf("Loi khoi tao danh sach!\n");
        return 1;
    }

    int choice;
    char val;
    Node *found;

    do {
        printf("\n=== BAI TAP 1 MENU ===\n");
        printf("1. Them ky tu vao dau (Insert Head)\n");
        printf("2. Xoa ky tu o dau (Delete Head)\n");
        printf("3. In danh sach (Display)\n");
        printf("4. Tim kiem ky tu (Search)\n");
        printf("5. Xoa tat ca node (Delete All)\n");
        printf("0. Thoat (Exit)\n");
        printf("Lua chon cua ban: ");
        if (scanf("%d", &choice) != 1) {
            printf("Lua chon khong hop le!\n");
            // Clear buffer
            while (getchar() != '\n');
            continue;
        }
        // Consuming newline
        while (getchar() != '\n');

        switch (choice) {
            case 1:
                printf("Nhap ky tu chu hoa: ");
                scanf("%c", &val);
                insert_head(list, create_node(val));
                printf("Da them '%c' vao dau danh sach.\n", toupper((unsigned char)val));
                break;
            case 2:
                if (!is_empty(list)) {
                    char deleted = list->head->data;
                    delete_head(list);
                    printf("Da xoa node dau (%c).\n", deleted);
                } else {
                    printf("Danh sach rong, khong the xoa!\n");
                }
                break;
            case 3:
                display(list);
                break;
            case 4:
                printf("Nhap ky tu can tim: ");
                scanf("%c", &val);
                found = search(list, val);
                if (found != NULL) {
                    printf("Tim thay ky tu '%c' tai dia chi %p\n", found->data, (void*)found);
                } else {
                    printf("Khong tim thay ky tu '%c' trong danh sach.\n", toupper((unsigned char)val));
                }
                break;
            case 5:
                delete_all(list);
                printf("Da xoa tat ca cac node.\n");
                break;
            case 0:
                printf("Dang thoat va giai phong bo nho...\n");
                break;
            default:
                printf("Lua chon khong hop le!\n");
        }
    } while (choice != 0);

    free_list(list);
    return 0;
}
