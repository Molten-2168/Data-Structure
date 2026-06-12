/*
 * ĐỆ QUY (Recursion)
 * =================
 * Một hàm được gọi là đệ quy nếu bên trong thân hàm có lời gọi đến chính nó.
 * Mỗi giải thuật đệ quy luôn gồm 2 phần cơ bản:
 *   1. Trường hợp cơ sở (base case): Điều kiện dừng để tránh lặp vô hạn.
 *   2. Trường hợp đệ quy (recursive case): Lời gọi lại chính nó với kích thước bài toán nhỏ hơn.
 */

#include <stdio.h>

// 1. GIAI THỪA (Factorial): n! = n * (n-1)!
// Độ phức tạp: Thời gian O(n), Không gian stack O(n)
int factorial(int n) {
    if (n <= 1) return 1;           // Trường hợp cơ sở: 0! = 1! = 1
    return n * factorial(n - 1);    // Lời gọi đệ quy
}

// 2. FIBONACCI: F(n) = F(n-1) + F(n-2)
// Độ phức tạp: Thời gian O(2^n) - Có thể tối ưu bằng khử đệ quy hoặc Quy hoạch động
int fibonacci(int n) {
    if (n <= 1) return n;           // Trường hợp cơ sở: F(0) = 0, F(1) = 1
    return fibonacci(n - 1) + fibonacci(n - 2);
}

// 3. TỔNG DÃY SỐ TỪ 1 ĐẾN N
// Độ phức tạp: Thời gian O(n)
int sum_n(int n) {
    if (n == 0) return 0;
    return n + sum_n(n - 1);
}

// 4. LŨY THỪA: a^n
// Độ phức tạp: Thời gian O(n)
double power(double a, int n) {
    if (n == 0) return 1;
    if (n < 0) return 1.0 / power(a, -n); // Hỗ trợ số mũ âm
    return a * power(a, n - 1);
}

// 5. ƯỚC SỐ CHUNG LỚN NHẤT (GCD) - Thuật toán Euclid
// Độ phức tạp: Thời gian O(log(min(a, b)))
int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

// 6. THÁP HÀ NỘI (Tower of Hanoi)
// Giải bài toán chuyển n đĩa từ cọc src sang dst dùng aux làm trung gian.
// Độ phức tạp: Thời gian O(2^n)
void tower_of_hanoi(int n, char src, char aux, char dst) {
    if (n == 1) {
        printf("Chuyen dia 1 tu %c -> %c\n", src, dst);
        return;
    }
    // Bước 1: Chuyển n-1 đĩa từ src sang aux
    tower_of_hanoi(n - 1, src, dst, aux);
    // Bước 2: Chuyển đĩa lớn nhất (đĩa n) từ src sang dst
    printf("Chuyen dia %d tu %c -> %c\n", n, src, dst);
    // Bước 3: Chuyển n-1 đĩa từ aux sang dst
    tower_of_hanoi(n - 1, aux, src, dst);
}

// 7. IN SỐ THẬP PHÂN DƯỚI DẠNG NHỊ PHÂN
// Độ phức tạp: Thời gian O(log n)
void print_binary(int n) {
    if (n > 1) print_binary(n / 2);
    printf("%d", n % 2);
}

// 8. ĐẢO NGƯỢC MẢNG (Sử dụng đệ quy hai con trỏ)
// Độ phức tạp: Thời gian O(n)
void reverse_array(int a[], int l, int r) {
    if (l >= r) return;
    // Hoán vị 2 phần tử ở hai đầu
    int temp = a[l];
    a[l] = a[r];
    a[r] = temp;
    // Đệ quy thu hẹp khoảng cách hai đầu
    reverse_array(a, l + 1, r - 1);
}

int main() {
    printf("=== KIỂM TRA ĐỆ QUY (RECURSION) ===\n\n");
    printf("1. Giai thua: 5! = %d\n", factorial(5));
    printf("2. Fibonacci: F(10) = %d\n", fibonacci(10));
    printf("3. Tong tu 1 den 10: S(10) = %d\n", sum_n(10));
    printf("4. Luy thua: 2^10 = %.0f\n", power(2, 10));
    printf("5. UCLN: UCLN(36, 24) = %d\n", gcd(36, 24));

    printf("\n6. Bai toan Thap Ha Noi (3 dia):\n");
    tower_of_hanoi(3, 'A', 'B', 'C');

    printf("\n7. In bieu dien nhi phan cua 42: ");
    print_binary(42);
    printf("\n");

    int a[] = {1, 2, 3, 4, 5};
    int n = sizeof(a) / sizeof(a[0]);
    reverse_array(a, 0, n - 1);
    printf("8. Mang sau khi dao nguoc bang de quy: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");

    return 0;
}
