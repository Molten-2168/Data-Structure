/*
 * NGĂN XẾP (Stack) - Cài đặt bằng mảng tĩnh (Static Array)
 * ========================================================
 * Nguyên lý hoạt động: LIFO (Last In, First Out) - Vào sau ra trước.
 * Các thao tác cơ bản:
 *   - push: Thêm phần tử vào đỉnh ngăn xếp.
 *   - pop: Lấy phần tử ở đỉnh ngăn xếp ra ngoài.
 *   - peek: Xem giá trị ở đỉnh ngăn xếp mà không xóa nó.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Cấu trúc Stack lưu trữ các giá trị nguyên
typedef struct {
    int data[MAX];
    int top; // Chỉ số của phần tử ở đỉnh (Khởi đầu = -1)
} Stack;

// --- Khởi tạo Stack ---
Stack* create_stack() {
    Stack *s = (Stack *)malloc(sizeof(Stack));
    if (s != NULL) {
        s->top = -1;
    }
    return s;
}

// --- Kiểm tra Stack rỗng ---
bool is_empty(Stack *s) {
    return s->top == -1;
}

// --- Kiểm tra Stack đầy ---
bool is_full(Stack *s) {
    return s->top == MAX - 1;
}

// --- Push: Đưa phần tử lên đỉnh (O(1)) ---
bool push(Stack *s, int value) {
    if (is_full(s)) return false;
    s->data[++(s->top)] = value;
    return true;
}

// --- Pop: Lấy phần tử ở đỉnh ra ngoài (O(1)) ---
int pop(Stack *s) {
    if (is_empty(s)) return -1;
    return s->data[(s->top)--];
}

// --- Peek: Xem phần tử ở đỉnh (O(1)) ---
int peek(Stack *s) {
    if (is_empty(s)) return -1;
    return s->data[s->top];
}

// --- Hiển thị các phần tử từ đáy đến đỉnh ---
void display(Stack *s) {
    if (is_empty(s)) {
        printf("Stack rong\n");
        return;
    }
    printf("Bottom -> ");
    for (int i = 0; i <= s->top; i++) {
        printf("%d ", s->data[i]);
    }
    printf("<- Top\n");
}

// ========== ỨNG DỤNG 1: CHUYỂN THẬP PHÂN SANG NHỊ PHÂN ==========
// Chia liên tục cho 2, đẩy phần dư vào Stack rồi rút ra để in.
void decimal_to_binary(int n) {
    Stack *s = create_stack();
    if (s == NULL) return;
    
    int temp = n;
    while (temp > 0) {
        push(s, temp % 2);
        temp /= 2;
    }
    
    printf("So %d bieu dien nhi phan la: ", n);
    if (n == 0) printf("0");
    while (!is_empty(s)) {
        printf("%d", pop(s));
    }
    printf("\n");
    
    free(s);
}

// ========== ỨNG DỤNG 2: KIỂM TRA DẤU NGOẶC HỢP LỆ (PARENTHESES MATCHING) ==========
bool is_matching(char open, char close) {
    return (open == '(' && close == ')') ||
           (open == '{' && close == '}') ||
           (open == '[' && close == ']');
}

bool check_parentheses(const char *expr) {
    Stack *s = create_stack();
    if (s == NULL) return false;
    
    for (int i = 0; expr[i] != '\0'; i++) {
        char c = expr[i];
        if (c == '(' || c == '{' || c == '[') {
            push(s, c);
        } else if (c == ')' || c == '}' || c == ']') {
            if (is_empty(s) || !is_matching((char)pop(s), c)) {
                free(s);
                return false; // Sai logic ngoặc hoặc thiếu ngoặc mở tương ứng
            }
        }
    }
    
    bool valid = is_empty(s); // Hợp lệ nếu stack trống (các ngoặc mở đều được đóng)
    free(s);
    return valid;
}

int main() {
    Stack *s = create_stack();
    if (s == NULL) return 1;

    printf("=== KIỂM TRA STACK MẢNG TĨNH (ARRAY-BASED STACK) ===\n\n");
    push(s, 10);
    push(s, 20);
    push(s, 30);
    display(s);

    printf("Phan tu top hien tai: %d\n", peek(s));
    printf("Lay ra (Pop): %d\n", pop(s));
    display(s);

    printf("\n--- Ung dung 1: Doi co so nhi phan ---\n");
    decimal_to_binary(42);
    decimal_to_binary(1023);

    printf("\n--- Ung dung 2: Kiem tra dau ngoac ---\n");
    const char *expr1 = "{[()()]}";
    const char *expr2 = "{[(])}";
    printf("Bieu thuc '%s': %s\n", expr1, check_parentheses(expr1) ? "Hop le" : "Khong hop le");
    printf("Bieu thuc '%s': %s\n", expr2, check_parentheses(expr2) ? "Hop le" : "Khong hop le");

    free(s);
    return 0;
}
