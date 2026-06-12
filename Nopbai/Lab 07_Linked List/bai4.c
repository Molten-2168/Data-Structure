/*
 * BÀI TẬP 4 - QUẢN LÝ SINH VIÊN BẰNG DANH SÁCH LIÊN KẾT ĐƠN (SẮP XẾP THEO MSSV)
 * =========================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Định nghĩa cấu trúc Student
typedef struct {
    char id[20];
    char name[50];
    float gpa;
} Student;

// Định nghĩa cấu trúc Node
typedef struct Node {
    Student data;
    struct Node *next;
} Node;

// Định nghĩa cấu trúc danh sách liên kết đơn
typedef struct {
    Node *head;
} StudentList;

// Khởi tạo danh sách
StudentList* create_list() {
    StudentList *list = (StudentList *)malloc(sizeof(StudentList));
    if (list != NULL) {
        list->head = NULL;
    }
    return list;
}

// Tạo Node mới
Node* create_node(const char *id, const char *name, float gpa) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (node != NULL) {
        // Sao chép thông tin sinh viên
        strncpy(node->data.id, id, sizeof(node->data.id) - 1);
        node->data.id[sizeof(node->data.id) - 1] = '\0';
        
        strncpy(node->data.name, name, sizeof(node->data.name) - 1);
        node->data.name[sizeof(node->data.name) - 1] = '\0';
        
        node->data.gpa = gpa;
        node->next = NULL;
    }
    return node;
}

// Kiểm tra danh sách rỗng
bool is_empty(StudentList *list) {
    return list->head == NULL;
}

// Thêm sinh viên vào danh sách theo thứ tự tăng dần của mã số sinh viên (id)
void insert_sorted(StudentList *list, Node *node) {
    if (node == NULL) return;
    Node *cur = list->head;
    Node *prev = NULL;

    // So sánh chuỗi id tăng dần
    while (cur != NULL && strcmp(cur->data.id, node->data.id) < 0) {
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

// Tìm kiếm một sinh viên với mã số id
Node* search_by_id(StudentList *list, const char *id) {
    Node *cur = list->head;
    while (cur != NULL) {
        if (strcmp(cur->data.id, id) == 0) {
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}

// In ra màn hình tất cả thông tin tất cả các sinh viên trong danh sách
void display(StudentList *list) {
    if (is_empty(list)) {
        printf("Danh sach sinh vien rong!\n");
        return;
    }
    printf("\n=== DANH SACH SINH VIEN (XEP TANG DAN THEO MSSV) ===\n");
    printf("%-15s %-30s %-5s\n", "MSSV", "Ho va Ten", "GPA");
    printf("----------------------------------------------------\n");
    Node *cur = list->head;
    while (cur != NULL) {
        printf("%-15s %-30s %-5.2f\n", cur->data.id, cur->data.name, cur->data.gpa);
        cur = cur->next;
    }
    printf("----------------------------------------------------\n");
}

// Xóa tất cả sinh viên
void delete_all(StudentList *list) {
    while (!is_empty(list)) {
        Node *temp = list->head;
        list->head = list->head->next;
        free(temp);
    }
}

// Giải phóng danh sách
void free_list(StudentList *list) {
    delete_all(list);
    free(list);
}

// Hàm hỗ trợ loại bỏ ký tự xuống dòng từ fgets
void trim_newline(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

int main() {
    StudentList *list = create_list();
    if (list == NULL) {
        printf("Loi khoi tao danh sach!\n");
        return 1;
    }

    // Khoi tao mot so du lieu mau
    insert_sorted(list, create_node("B20DCCN005", "Nguyen Van A", 3.2));
    insert_sorted(list, create_node("B20DCCN001", "Tran Thi B", 3.8));
    insert_sorted(list, create_node("B20DCCN009", "Le Hoang C", 2.9));

    int choice;
    char id[20], name[50];
    float gpa;
    Node *found;

    do {
        printf("\n=== BAI TAP 4 MENU ===\n");
        printf("1. Them sinh vien (Insert Sorted by ID)\n");
        printf("2. Tim kiem sinh vien theo MSSV (Search ID)\n");
        printf("3. Hien thi tat ca sinh vien (Display)\n");
        printf("0. Thoat (Exit)\n");
        printf("Lua chon cua ban: ");
        if (scanf("%d", &choice) != 1) {
            printf("Lua chon khong hop le!\n");
            while (getchar() != '\n');
            continue;
        }
        // Consume character newline
        while (getchar() != '\n');

        switch (choice) {
            case 1:
                printf("Nhap MSSV (ID): ");
                fgets(id, sizeof(id), stdin);
                trim_newline(id);
                
                printf("Nhap Ho va Ten: ");
                fgets(name, sizeof(name), stdin);
                trim_newline(name);
                
                printf("Nhap diem GPA: ");
                if (scanf("%float", &gpa) != 1) {
                    printf("Loi nhap GPA!\n");
                    while (getchar() != '\n');
                    break;
                }
                while (getchar() != '\n'); // Clear remaining input

                insert_sorted(list, create_node(id, name, gpa));
                printf("Da them sinh vien %s vao danh sach.\n", name);
                break;
            case 2:
                printf("Nhap MSSV can tim: ");
                fgets(id, sizeof(id), stdin);
                trim_newline(id);
                found = search_by_id(list, id);
                if (found != NULL) {
                    printf("Tim thay sinh vien:\n");
                    printf("- MSSV: %s\n- Ho Ten: %s\n- GPA: %.2f\n", 
                           found->data.id, found->data.name, found->data.gpa);
                } else {
                    printf("Khong tim thay sinh vien co MSSV '%s'.\n", id);
                }
                break;
            case 3:
                display(list);
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
