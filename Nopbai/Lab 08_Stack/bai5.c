/*
 * BÀI TẬP 5 - BIỂU DIỄN TỪNG BƯỚC CHUYỂN ĐỔI VÀ TÍNH GIÁ TRỊ BIỂU THỨC
 * ===================================================================
 */

#include <stdio.h>

void show_infix_to_postfix_trace() {
    printf("\n=== CÂU A: TỪNG BƯỚC CHUYỂN INFIX SANG POSTFIX ===\n");
    printf("Biểu thức trung tố (Infix): 3 - 2 * (10 - 6 * (4 + 1)) - 2\n\n");
    
    printf("+-------+----------------------------------+-----------------------+---------------------------------+\n");
    printf("| Token | Hành động                        | Stack                 | Output Postfix                  |\n");
    printf("+-------+----------------------------------+-----------------------+---------------------------------+\n");
    printf("| 3     | Xuất số hạng                     | [ ]                   | 3                               |\n");
    printf("| -     | Đẩy toán tử vào Stack            | [ - ]                 | 3                               |\n");
    printf("| 2     | Xuất số hạng                     | [ - ]                 | 3 2                             |\n");
    printf("| *     | Đẩy toán tử (ưu tiên cao hơn)    | [ - * ]               | 3 2                             |\n");
    printf("| (     | Đẩy dấu ngoặc mở                 | [ - * ( ]             | 3 2                             |\n");
    printf("| 10    | Xuất số hạng                     | [ - * ( ]             | 3 2 10                          |\n");
    printf("| -     | Đẩy toán tử vào Stack            | [ - * ( - ]           | 3 2 10                          |\n");
    printf("| 6     | Xuất số hạng                     | [ - * ( - ]           | 3 2 10 6                        |\n");
    printf("| *     | Đẩy toán tử (ưu tiên cao hơn)    | [ - * ( - * ]         | 3 2 10 6                        |\n");
    printf("| (     | Đẩy dấu ngoặc mở                 | [ - * ( - * ( ]       | 3 2 10 6                        |\n");
    printf("| 4     | Xuất số hạng                     | [ - * ( - * ( ]       | 3 2 10 6 4                      |\n");
    printf("| +     | Đẩy toán tử vào Stack            | [ - * ( - * ( + ]     | 3 2 10 6 4                      |\n");
    printf("| 1     | Xuất số hạng                     | [ - * ( - * ( + ]     | 3 2 10 6 4 1                    |\n");
    printf("| )     | Lấy toán tử ra cho đến '('       | [ - * ( - * ]         | 3 2 10 6 4 1 +                  |\n");
    printf("| )     | Lấy toán tử ra cho đến '('       | [ - * ]               | 3 2 10 6 4 1 + * -              |\n");
    printf("| -     | Lấy * và - ra, đẩy - mới vào     | [ - ]                 | 3 2 10 6 4 1 + * - * -          |\n");
    printf("| 2     | Xuất số hạng                     | [ - ]                 | 3 2 10 6 4 1 + * - * - 2        |\n");
    printf("| Hết   | Lấy toàn bộ trong Stack ra       | [ ]                   | 3 2 10 6 4 1 + * - * - 2 -      |\n");
    printf("+-------+----------------------------------+-----------------------+---------------------------------+\n");
    printf("Kết quả biểu thức hậu tố: 3 2 10 6 4 1 + * - * - 2 -\n\n");
}

void show_postfix_evaluation_trace_a() {
    printf("=== CÂU B: TỪNG BƯỚC TÍNH GIÁ TRỊ BIỂU THỨC HẬU TỐ TRÊN ===\n");
    printf("Biểu thức hậu tố: 3 2 10 6 4 1 + * - * - 2 -\n\n");
    
    printf("+-------+------------------------------------------+--------------------------------------+\n");
    printf("| Token | Hành động                                | Stack (Đáy -> Đỉnh)                  |\n");
    printf("+-------+------------------------------------------+--------------------------------------+\n");
    printf("| 3     | Đẩy 3 vào Stack                          | [ 3 ]                                |\n");
    printf("| 2     | Đẩy 2 vào Stack                          | [ 3, 2 ]                             |\n");
    printf("| 10    | Đẩy 10 vào Stack                         | [ 3, 2, 10 ]                         |\n");
    printf("| 6     | Đẩy 6 vào Stack                          | [ 3, 2, 10, 6 ]                      |\n");
    printf("| 4     | Đẩy 4 vào Stack                          | [ 3, 2, 10, 6, 4 ]                   |\n");
    printf("| 1     | Đẩy 1 vào Stack                          | [ 3, 2, 10, 6, 4, 1 ]                |\n");
    printf("| +     | Lấy 1, 4. Tính 4 + 1 = 5, đẩy vào        | [ 3, 2, 10, 6, 5 ]                   |\n");
    printf("| *     | Lấy 5, 6. Tính 6 * 5 = 30, đẩy vào       | [ 3, 2, 10, 30 ]                     |\n");
    printf("| -     | Lấy 30, 10. Tính 10 - 30 = -20, đẩy vào  | [ 3, 2, -20 ]                        |\n");
    printf("| *     | Lấy -20, 2. Tính 2 * -20 = -40, đẩy vào  | [ 3, -40 ]                           |\n");
    printf("| -     | Lấy -40, 3. Tính 3 - (-40) = 43, đẩy vào | [ 43 ]                               |\n");
    printf("| 2     | Đẩy 2 vào Stack                          | [ 43, 2 ]                            |\n");
    printf("| -     | Lấy 2, 43. Tính 43 - 2 = 41, đẩy vào     | [ 41 ]                               |\n");
    printf("+-------+------------------------------------------+--------------------------------------+\n");
    printf("Giá trị tính toán cuối cùng: 41\n\n");
}

void show_postfix_evaluation_trace_b() {
    printf("=== CÂU C: TỪNG BƯỚC TÍNH GIÁ TRỊ BIỂU THỨC HẬU TỐ: 10 3 1 2 + * - ===\n\n");
    
    printf("+-------+------------------------------------------+--------------------------------------+\n");
    printf("| Token | Hành động                                | Stack (Đáy -> Đỉnh)                  |\n");
    printf("+-------+------------------------------------------+--------------------------------------+\n");
    printf("| 10    | Đẩy 10 vào Stack                         | [ 10 ]                               |\n");
    printf("| 3     | Đẩy 3 vào Stack                          | [ 10, 3 ]                            |\n");
    printf("| 1     | Đẩy 1 vào Stack                          | [ 10, 3, 1 ]                         |\n");
    printf("| 2     | Đẩy 2 vào Stack                          | [ 10, 3, 1, 2 ]                      |\n");
    printf("| +     | Lấy 2, 1. Tính 1 + 2 = 3, đẩy vào        | [ 10, 3, 3 ]                         |\n");
    printf("| *     | Lấy 3, 3. Tính 3 * 3 = 9, đẩy vào        | [ 10, 9 ]                            |\n");
    printf("| -     | Lấy 9, 10. Tính 10 - 9 = 1, đẩy vào      | [ 1 ]                                |\n");
    printf("+-------+------------------------------------------+--------------------------------------+\n");
    printf("Giá trị tính toán cuối cùng: 1\n\n");
}

int main() {
    show_infix_to_postfix_trace();
    show_postfix_evaluation_trace_a();
    show_postfix_evaluation_trace_b();
    return 0;
}
