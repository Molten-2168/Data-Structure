/*
 * BÀI TẬP 6 - BIỂU DIỄN ĐA THỨC 1 BIẾN X VÀ CÁC PHÉP TOÁN CỘNG/TRỪ
 * =============================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

// Định nghĩa cấu trúc của một số hạng (Term)
typedef struct Term {
    float coef; // Hệ số (coefficient)
    int exp;    // Số mũ (exponent)
    struct Term *next;
} Term;

// Định nghĩa cấu trúc đa thức
typedef struct {
    Term *head;
} Polynomial;

// Khởi tạo đa thức
Polynomial* create_polynomial() {
    Polynomial *poly = (Polynomial *)malloc(sizeof(Polynomial));
    if (poly != NULL) {
        poly->head = NULL;
    }
    return poly;
}

// Giải phóng bộ nhớ đa thức
void free_polynomial(Polynomial *poly) {
    Term *cur = poly->head;
    while (cur != NULL) {
        Term *temp = cur;
        cur = cur->next;
        free(temp);
    }
    free(poly);
}

// Thêm một số hạng vào đa thức theo thứ tự giảm dần của số mũ
void insert_term(Polynomial *poly, float coef, int exp) {
    if (coef == 0) return;
    
    Term *cur = poly->head;
    Term *prev = NULL;
    
    // Tìm vị trí thích hợp
    while (cur != NULL && cur->exp > exp) {
        prev = cur;
        cur = cur->next;
    }
    
    // Nếu đã có số hạng cùng số mũ, ta cộng dồn hệ số
    if (cur != NULL && cur->exp == exp) {
        cur->coef += coef;
        if (cur->coef == 0) {
            // Xóa số hạng nếu hệ số sau khi cộng dồn bằng 0
            if (prev == NULL) {
                poly->head = cur->next;
            } else {
                prev->next = cur->next;
            }
            free(cur);
        }
    } else {
        // Tạo số hạng mới và chèn vào giữa/đầu/cuối
        Term *new_term = (Term *)malloc(sizeof(Term));
        if (new_term != NULL) {
            new_term->coef = coef;
            new_term->exp = exp;
            new_term->next = cur;
            if (prev == NULL) {
                poly->head = new_term;
            } else {
                prev->next = new_term;
            }
        }
    }
}

// In đa thức ra màn hình
void display(Polynomial *poly) {
    if (poly->head == NULL) {
        printf("0\n");
        return;
    }
    
    Term *cur = poly->head;
    bool is_first = true;
    
    while (cur != NULL) {
        float c = cur->coef;
        int e = cur->exp;
        
        if (c > 0) {
            if (!is_first) printf(" + ");
        } else {
            if (!is_first) printf(" - ");
            else printf("-");
            c = -c; // Lấy trị tuyệt đối để in
        }
        
        // In hệ số
        if (e == 0) {
            printf("%.0f", c); // in số thực dạng nguyên nếu coef là số nguyên
        } else {
            if (c != 1) {
                printf("%.0f", c);
            }
            printf("x");
            if (e != 1) {
                printf("^%d", e);
            }
        }
        
        is_first = false;
        cur = cur->next;
    }
    printf("\n");
}

// Cộng hai đa thức: P3 = P1 + P2
Polynomial* add(Polynomial *p1, Polynomial *p2) {
    Polynomial *p3 = create_polynomial();
    if (p3 == NULL) return NULL;
    
    // Sao chép từ P1 sang P3
    Term *cur = p1->head;
    while (cur != NULL) {
        insert_term(p3, cur->coef, cur->exp);
        cur = cur->next;
    }
    
    // Cộng các số hạng từ P2 vào P3
    cur = p2->head;
    while (cur != NULL) {
        insert_term(p3, cur->coef, cur->exp);
        cur = cur->next;
    }
    
    return p3;
}

// Trừ hai đa thức: P3 = P1 - P2
Polynomial* subtract(Polynomial *p1, Polynomial *p2) {
    Polynomial *p3 = create_polynomial();
    if (p3 == NULL) return NULL;
    
    // Sao chép từ P1 sang P3
    Term *cur = p1->head;
    while (cur != NULL) {
        insert_term(p3, cur->coef, cur->exp);
        cur = cur->next;
    }
    
    // Trừ các số hạng từ P2 vào P3 (nhân hệ số với -1)
    cur = p2->head;
    while (cur != NULL) {
        insert_term(p3, -cur->coef, cur->exp);
        cur = cur->next;
    }
    
    return p3;
}

// Tính giá trị của đa thức tại x = x0
double evaluate(Polynomial *poly, double x) {
    double result = 0.0;
    Term *cur = poly->head;
    while (cur != NULL) {
        result += cur->coef * pow(x, cur->exp);
        cur = cur->next;
    }
    return result;
}

int main() {
    printf("=== BAI TAP 6 ===\n");
    
    // Tạo đa thức 1: P1(x) = 6x^3 + 9x^2 + 7x + 1
    Polynomial *p1 = create_polynomial();
    insert_term(p1, 6, 3);
    insert_term(p1, 9, 2);
    insert_term(p1, 7, 1);
    insert_term(p1, 1, 0);
    printf("P1(x) = "); display(p1);
    
    // Tạo đa thức 2: P2(x) = x^3 - 5x^2 - 2
    Polynomial *p2 = create_polynomial();
    insert_term(p2, 1, 3);
    insert_term(p2, -5, 2);
    insert_term(p2, -2, 0);
    printf("P2(x) = "); display(p2);
    
    // Cộng hai đa thức
    Polynomial *sum = add(p1, p2);
    printf("P1(x) + P2(x) = "); display(sum);
    
    // Trừ hai đa thức
    Polynomial *diff = subtract(p1, p2);
    printf("P1(x) - P2(x) = "); display(diff);
    
    // Tính giá trị đa thức tại x = 1
    double x_val = 1.0;
    printf("\nTinh gia tri tai x = %.0f:\n", x_val);
    printf("- P1(%.0f) = %.2f\n", x_val, evaluate(p1, x_val));
    printf("- P2(%.0f) = %.2f\n", x_val, evaluate(p2, x_val));
    printf("- (P1 + P2)(%.0f) = %.2f\n", x_val, evaluate(sum, x_val));
    printf("- (P1 - P2)(%.0f) = %.2f\n", x_val, evaluate(diff, x_val));
    
    // Giải phóng bộ nhớ
    free_polynomial(p1);
    free_polynomial(p2);
    free_polynomial(sum);
    free_polynomial(diff);
    
    return 0;
}
