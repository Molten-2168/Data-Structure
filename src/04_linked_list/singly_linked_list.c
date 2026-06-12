/*
 * DANH SÁCH LIÊN KẾT ĐƠN (Singly Linked List)
 * ============================================
 * Định nghĩa: Là cấu trúc dữ liệu tuyến tính bao gồm các nút (Node).
 * Mỗi Node chứa dữ liệu (data) và con trỏ chỉ đến Node tiếp theo (next).
 * Ưu điểm: Kích thước linh hoạt, chèn/xóa phần tử nhanh O(1) khi biết vị trí.
 * Nhược điểm: Truy cập tuần tự O(n), tiêu tốn thêm bộ nhớ cho các liên kết con trỏ.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Định nghĩa cấu trúc Node
typedef struct Node {
    int data;
    struct Node *next;
} Node;

// Định nghĩa cấu trúc danh sách liên kết đơn
typedef struct {
    Node *head; // Con trỏ quản lý node đầu tiên
} SinglyLinkedList;

// --- Khởi tạo danh sách ---
SinglyLinkedList* create_list() {
    SinglyLinkedList *list = (SinglyLinkedList *)malloc(sizeof(SinglyLinkedList));
    if (list != NULL) {
        list->head = NULL;
    }
    return list;
}

// --- Tạo Node mới ---
Node* create_node(int data) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (node != NULL) {
        node->data = data;
        node->next = NULL;
    }
    return node;
}

// --- Kiểm tra danh sách rỗng ---
bool is_empty(SinglyLinkedList *list) {
    return list->head == NULL;
}

// --- Duyệt và hiển thị danh sách ---
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

// --- Tính chiều dài danh sách ---
int length(SinglyLinkedList *list) {
    int count = 0;
    Node *cur = list->head;
    while (cur != NULL) {
        count++;
        cur = cur->next;
    }
    return count;
}

// --- Tìm kiếm phần tử (Vòng lặp) ---
Node* search(SinglyLinkedList *list, int value) {
    Node *cur = list->head;
    while (cur != NULL) {
        if (cur->data == value) return cur;
        cur = cur->next;
    }
    return NULL;
}

// --- Tìm kiếm phần tử (Đệ quy) ---
Node* search_recursive(Node *cur, int value) {
    if (cur == NULL) return NULL;
    if (cur->data == value) return cur;
    return search_recursive(cur->next, value);
}

// --- Thêm Node vào đầu danh sách (O(1)) ---
void insert_head(SinglyLinkedList *list, Node *node) {
    if (node == NULL) return;
    node->next = list->head;
    list->head = node;
}

// --- Thêm Node vào cuối danh sách (O(n)) ---
void insert_tail(SinglyLinkedList *list, Node *node) {
    if (node == NULL) return;
    if (is_empty(list)) {
        list->head = node;
        return;
    }
    Node *cur = list->head;
    while (cur->next != NULL) {
        cur = cur->next;
    }
    cur->next = node;
}

// --- Thêm Node phía sau một giá trị chỉ định ---
void insert_after(SinglyLinkedList *list, int value, Node *node) {
    if (node == NULL) return;
    Node *cur = list->head;
    while (cur != NULL && cur->data != value) {
        cur = cur->next;
    }
    if (cur != NULL) {
        node->next = cur->next;
        cur->next = node;
    } else {
        printf("Khong tim thay gia tri %d de chen phia sau. Node da bi huy.\n", value);
        free(node); // Giải phóng node nếu không chèn được để tránh rò rỉ bộ nhớ
    }
}

// --- Thêm Node vào danh sách giữ nguyên thứ tự tăng dần (O(n)) ---
void insert_sorted(SinglyLinkedList *list, Node *node) {
    if (node == NULL) return;
    Node *cur = list->head;
    Node *prev = NULL;
    
    while (cur != NULL && cur->data < node->data) {
        prev = cur;
        cur = cur->next;
    }
    
    if (prev == NULL) { // Chen vao dau danh sach
        node->next = list->head;
        list->head = node;
    } else { // Chen vao giua hoac cuoi danh sach
        prev->next = node;
        node->next = cur;
    }
}

// --- Xóa Node ở đầu danh sách (O(1)) ---
void delete_head(SinglyLinkedList *list) {
    if (is_empty(list)) return;
    Node *temp = list->head;
    list->head = list->head->next;
    free(temp);
}

// --- Xóa Node ở cuối danh sách (O(n)) ---
void delete_tail(SinglyLinkedList *list) {
    if (is_empty(list)) return;
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

// --- Xóa Node theo giá trị cụ thể (O(n)) ---
void delete_by_value(SinglyLinkedList *list, int value) {
    Node *cur = list->head;
    Node *prev = NULL;
    
    while (cur != NULL && cur->data != value) {
        prev = cur;
        cur = cur->next;
    }
    
    if (cur == NULL) return; // Khong tim thay
    
    if (prev == NULL) { // Node can xoa o dau
        list->head = cur->next;
    } else {
        prev->next = cur->next;
    }
    free(cur);
}

// --- Xóa toàn bộ danh sách ---
void delete_all(SinglyLinkedList *list) {
    while (!is_empty(list)) {
        delete_head(list);
    }
}

// --- Sắp xếp danh sách (Selection Sort trên Danh Sách Liên Kết) ---
void selection_sort(SinglyLinkedList *list) {
    for (Node *i = list->head; i != NULL; i = i->next) {
        Node *min_node = i;
        for (Node *j = i->next; j != NULL; j = j->next) {
            if (j->data < min_node->data) {
                min_node = j;
            }
        }
        // Hoán đổi dữ liệu
        int temp = i->data;
        i->data = min_node->data;
        min_node->data = temp;
    }
}

// --- Giải phóng cấu trúc List ---
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

    // Khoi tao du lieu mau
    int init_data[] = {5, 3, 8, 1, 9};
    for (int i = 0; i < 5; i++) {
        insert_sorted(list, create_node(init_data[i]));
    }

    int choice;
    do {
        printf("\n=== SINGLY LINKED LIST MENU ===\n");
        printf("1. Chen dau (Insert Head)\n");
        printf("2. Chen cuoi (Insert Tail)\n");
        printf("3. Chen co thu tu (Insert Sorted)\n");
        printf("4. Chen sau phan tu (Insert After)\n");
        printf("5. Tim kiem phan tu (Search)\n");
        printf("6. Xoa phan tu dau (Delete Head)\n");
        printf("7. Xoa phan tu cuoi (Delete Tail)\n");
        printf("8. Xoa theo gia tri (Delete Value)\n");
        printf("9. Hien thi danh sach (Display)\n");
        printf("10. Sap xep (Sort)\n");
        printf("11. Tinh chieu dai (Length)\n");
        printf("0. Thoat (Exit)\n");
        printf("Lua chon cua ban: ");
        if (scanf("%d", &choice) != 1) {
            printf("Loi doc lua chon!\n");
            break;
        }

        int value, target;
        Node *found;
        switch (choice) {
            case 1:
                printf("Nhap gia tri chen dau: "); scanf("%d", &value);
                insert_head(list, create_node(value));
                break;
            case 2:
                printf("Nhap gia tri chen cuoi: "); scanf("%d", &value);
                insert_tail(list, create_node(value));
                break;
            case 3:
                printf("Nhap gia tri chen sap xep: "); scanf("%d", &value);
                insert_sorted(list, create_node(value));
                break;
            case 4:
                printf("Nhap gia tri can chen: "); scanf("%d", &value);
                printf("Nhap gia tri dung truoc: "); scanf("%d", &target);
                insert_after(list, target, create_node(value));
                break;
            case 5:
                printf("Nhap gia tri tim kiem: "); scanf("%d", &value);
                found = search(list, value);
                if (found != NULL) {
                    printf("Tim thay phan tu %d tai o nho %p\n", found->data, (void*)found);
                } else {
                    printf("Khong tim thay!\n");
                }
                break;
            case 6:
                delete_head(list);
                printf("Da xoa node dau.\n");
                break;
            case 7:
                delete_tail(list);
                printf("Da xoa node cuoi.\n");
                break;
            case 8:
                printf("Nhap gia tri can xoa: "); scanf("%d", &value);
                delete_by_value(list, value);
                break;
            case 9:
                display(list);
                break;
            case 10:
                selection_sort(list);
                printf("Da sap xep danh sach tang dan.\n");
                break;
            case 11:
                printf("Chieu dai danh sach: %d\n", length(list));
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
