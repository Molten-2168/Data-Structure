/*
 * BÀI TẬP 2 - DANH SÁCH LIÊN KẾT ĐƠN SỐ NGUYÊN DƯƠNG
 * ==================================================
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

// Tạo Node mới (chỉ nhận số nguyên dương)
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

// Kiểm tra danh sách rỗng
bool is_empty(SinglyLinkedList *list) {
    return list->head == NULL;
}

// Thêm từng phần tử vào đầu danh sách
void insert_head(SinglyLinkedList *list, Node *node) {
    if (node == NULL) return;
    node->next = list->head;
    list->head = node;
}

// Xóa một node ở cuối danh sách
void delete_tail(SinglyLinkedList *list) {
    if (is_empty(list)) {
        printf("Danh sach rong, khong the xoa!\n");
        return;
    }
    if (list->head->next == NULL) {
        free(list->head);
        list->head = NULL;
        return;
    }
    Node *cur = list->head;
    while (cur->next->next != NULL) {
        cur = cur->next;
    }
    free(cur->next);
    cur->next = NULL;
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
        printf("%d -> ", cur->data);
        cur = cur->next;
    }
    printf("NULL\n");
}

// Đếm số lượng các phần tử trong danh sách
int countItems(SinglyLinkedList *list) {
    int count = 0;
    Node *cur = list->head;
    while (cur != NULL) {
        count++;
        cur = cur->next;
    }
    return count;
}

// Trả về thông tin của node thứ i trong danh sách (index bắt đầu từ 0)
// Nếu index không hợp lệ, trả về -1 (hoặc một giá trị báo lỗi khác)
int getItem(SinglyLinkedList *list, int index) {
    if (index < 0 || is_empty(list)) return -1;
    Node *cur = list->head;
    int count = 0;
    while (cur != NULL) {
        if (count == index) {
            return cur->data;
        }
        count++;
        cur = cur->next;
    }
    return -1; // Index vượt quá độ dài danh sách
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
    SinglyLinkedList *list = create_list();
    if (list == NULL) {
        printf("Loi khoi tao danh sach!\n");
        return 1;
    }

    int choice, val, idx;

    do {
        printf("\n=== BAI TAP 2 MENU ===\n");
        printf("1. Them vao dau (Insert Head)\n");
        printf("2. Xoa o cuoi (Delete Tail)\n");
        printf("3. In danh sach (Display)\n");
        printf("4. Dem so phan tu (countItems)\n");
        printf("5. Lay gia tri tai chi so (getItem)\n");
        printf("0. Thoat (Exit)\n");
        printf("Lua chon cua ban: ");
        if (scanf("%d", &choice) != 1) {
            printf("Lua chon khong hop le!\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1:
                printf("Nhap so nguyen duong: ");
                if (scanf("%d", &val) == 1) {
                    Node *node = create_node(val);
                    if (node != NULL) {
                        insert_head(list, node);
                        printf("Da them %d vao dau danh sach.\n", val);
                    }
                } else {
                    printf("Loi nhap du lieu!\n");
                }
                break;
            case 2:
                delete_tail(list);
                printf("Da thuc hien xoa node cuoi.\n");
                break;
            case 3:
                display(list);
                break;
            case 4:
                printf("So luong phan tu trong danh sach: %d\n", countItems(list));
                break;
            case 5:
                printf("Nhap chi so index can lay (tu 0): ");
                if (scanf("%d", &idx) == 1) {
                    int result = getItem(list, idx);
                    if (result != -1) {
                        printf("Gia tri tai index %d la: %d\n", idx, result);
                    } else {
                        printf("Index %d khong hop le hoac danh sach rong!\n", idx);
                    }
                } else {
                    printf("Loi nhap chi so!\n");
                }
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

    free_list(list);
    return 0;
}
