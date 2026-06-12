/*
 * BÀI TẬP 1 - NGĂN XẾP CÀI ĐẶT BẰNG MẢNG (SỐ NGUYÊN DƯƠNG)
 * ========================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

// Định nghĩa cấu trúc Stack
typedef struct {
    int data[MAX];
    int top; // Chỉ số đỉnh ngăn xếp (-1 khi rỗng)
} Stack;

// Khởi tạo Stack
Stack* create_stack() {
    Stack *s = (Stack *)malloc(sizeof(Stack));
    if (s != NULL) {
        s->top = -1;
    }
    return s;
}

// Kiểm tra Stack rỗng
bool is_empty(Stack *s) {
    return s->top == -1;
}

// Kiểm tra Stack đầy
bool is_full(Stack *s) {
    return s->top == MAX - 1;
}

// Đẩy phần tử vào đỉnh Stack (chỉ nhận số nguyên dương)
bool push(Stack *s, int value) {
    if (value <= 0) {
        printf("Loi: Chi chap nhan so nguyen duong (> 0)!\n");
        return false;
    }
    if (is_full(s)) {
        printf("Loi: Ngan xep da day!\n");
        return false;
    }
    s->data[++(s->top)] = value;
    return true;
}

// Lấy phần tử ở đỉnh Stack ra ngoài
int pop(Stack *s) {
    if (is_empty(s)) {
        return -1;
    }
    return s->data[(s->top)--];
}

// Xem giá trị phần tử ở đỉnh Stack
int peek(Stack *s) {
    if (is_empty(s)) {
        return -1;
    }
    return s->data[s->top];
}

// Hiển thị các phần tử từ đáy đến đỉnh
void display(Stack *s) {
    if (is_empty(s)) {
        printf("Ngan xep rong!\n");
        return;
    }
    printf("Bottom -> ");
    for (int i = 0; i <= s->top; i++) {
        printf("%d ", s->data[i]);
    }
    printf("<- Top\n");
}

int main() {
    Stack *s = create_stack();
    if (s == NULL) {
        printf("Loi khoi tao ngan xep!\n");
        return 1;
    }

    int choice, val;

    do {
        printf("\n=== BAI TAP 1 MENU (STACK MANG TIEU CHUAN) ===\n");
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
                    if (push(s, val)) {
                        printf("Da them %d vao ngan xep.\n", val);
                    }
                } else {
                    printf("Loi doc du lieu!\n");
                }
                break;
            case 2:
                val = pop(s);
                if (val != -1) {
                    printf("Phan tu lay ra (Pop): %d\n", val);
                } else {
                    printf("Ngan xep rong, khong the Pop!\n");
                }
                break;
            case 3:
                val = peek(s);
                if (val != -1) {
                    printf("Phan tu o dinh (Peek): %d\n", val);
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

    free(s);
    return 0;
}
