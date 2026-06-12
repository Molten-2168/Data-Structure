/*
 * BÀI TẬP 7 - BIỂU DIỄN ĐA THỨC 2 BIẾN X, Y
 * ========================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Định nghĩa cấu trúc số hạng của đa thức 2 biến (x, y)
typedef struct Term {
    float coef;  // Hệ số
    int exp_x;   // Số mũ của x
    int exp_y;   // Số mũ của y
    struct Term *next;
} Term;

// Định nghĩa cấu trúc đa thức
typedef struct {
    Term *head;
} Polynomial2Var;

// Khởi tạo đa thức
Polynomial2Var* create_polynomial() {
    Polynomial2Var *poly = (Polynomial2Var *)malloc(sizeof(Polynomial2Var));
    if (poly != NULL) {
        poly->head = NULL;
    }
    return poly;
}

// Giải phóng đa thức
void free_polynomial(Polynomial2Var *poly) {
    Term *cur = poly->head;
    while (cur != NULL) {
        Term *temp = cur;
        cur = cur->next;
        free(temp);
    }
    free(poly);
}

// Chèn số hạng theo thứ tự từ điển: số mũ x giảm dần, nếu x bằng nhau thì số mũ y giảm dần
void insert_term(Polynomial2Var *poly, float coef, int exp_x, int exp_y) {
    if (coef == 0) return;
    
    Term *cur = poly->head;
    Term *prev = NULL;
    
    // So sánh thứ tự
    while (cur != NULL) {
        if (cur->exp_x < exp_x) {
            break;
        } else if (cur->exp_x == exp_x) {
            if (cur->exp_y < exp_y) {
                break;
            } else if (cur->exp_y == exp_y) {
                // Trùng số mũ của cả x và y -> cộng dồn hệ số
                cur->coef += coef;
                if (cur->coef == 0) {
                    if (prev == NULL) {
                        poly->head = cur->next;
                    } else {
                        prev->next = cur->next;
                    }
                    free(cur);
                }
                return;
            }
        }
        prev = cur;
        cur = cur->next;
    }
    
    // Tạo số hạng mới
    Term *new_term = (Term *)malloc(sizeof(Term));
    if (new_term != NULL) {
        new_term->coef = coef;
        new_term->exp_x = exp_x;
        new_term->exp_y = exp_y;
        new_term->next = cur;
        if (prev == NULL) {
            poly->head = new_term;
        } else {
            prev->next = new_term;
        }
    }
}

// In đa thức 2 biến ra màn hình
void display(Polynomial2Var *poly) {
    if (poly->head == NULL) {
        printf("0\n");
        return;
    }
    
    Term *cur = poly->head;
    bool is_first = true;
    
    while (cur != NULL) {
        float c = cur->coef;
        int ex = cur->exp_x;
        int ey = cur->exp_y;
        
        if (c > 0) {
            if (!is_first) printf(" + ");
        } else {
            if (!is_first) printf(" - ");
            else printf("-");
            c = -c;
        }
        
        // In hệ số
        if (c != 1 || (ex == 0 && ey == 0)) {
            printf("%.0f", c);
        }
        
        // In biến x
        if (ex > 0) {
            printf("x");
            if (ex != 1) {
                printf("^%d", ex);
            }
        }
        
        // In biến y
        if (ey > 0) {
            printf("y");
            if (ey != 1) {
                printf("^%d", ey);
            }
        }
        
        is_first = false;
        cur = cur->next;
    }
    printf("\n");
}

int main() {
    printf("=== BAI TAP 7 ===\n");
    
    Polynomial2Var *poly = create_polynomial();
    if (poly == NULL) {
        printf("Loi khoi tao đa thuc!\n");
        return 1;
    }
    
    // Chuẩn bị dữ liệu mẫu cho đa thức: 7x^3y^2 - 8x^2y + 3xy + 11x - 4
    insert_term(poly, 7, 3, 2);
    insert_term(poly, -8, 2, 1);
    insert_term(poly, 3, 1, 1);
    insert_term(poly, 11, 1, 0);
    insert_term(poly, -4, 0, 0);
    
    // Hiển thị đa thức
    printf("Da thuc P(x, y) = ");
    display(poly);
    
    // Giải phóng bộ nhớ
    free_polynomial(poly);
    
    return 0;
}
