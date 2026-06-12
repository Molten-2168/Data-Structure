/*
 * TÌM KIẾM (Searching Algorithms)
 * ==============================
 * Các giải thuật tìm kiếm phổ biến trên mảng một chiều:
 *   1. Tìm kiếm tuyến tính (Linear Search): Hoạt động trên mọi mảng.
 *   2. Tìm kiếm nhị phân (Binary Search): Chỉ hoạt động trên mảng ĐÃ SẮP XẾP.
 */

#include <stdio.h>
#include <string.h>

#ifdef _WIN32
    #define strcasecmp _stricmp // Khương thích đa nền tảng cho Windows
#else
    #include <strings.h>       // Cho strcasecmp trên POSIX (macOS, Linux)
#endif

// ========== 1. TÌM KIẾM TUYẾN TÍNH (LINEAR SEARCH) ==========
// Độ phức tạp thời gian: O(n) trung bình/xấu nhất, O(1) tốt nhất
// Độ phức tạp không gian: O(1)
int linear_search(int a[], int n, int x) {
    for (int i = 0; i < n; i++) {
        if (a[i] == x) return i; // Trả về chỉ số nếu tìm thấy
    }
    return -1; // Không tìm thấy
}

// ========== 2. TÌM KIẾM NHỊ PHÂN ĐỆ QUY (BINARY SEARCH RECURSIVE) ==========
// Độ phức tạp thời gian: O(log n)
// Độ phức tạp không gian: O(log n) cho stack đệ quy
int binary_search_recursive(int a[], int l, int r, int x) {
    if (l > r) return -1; // Trường hợp cơ sở: Khoảng tìm kiếm rỗng
    int m = l + (r - l) / 2; // Tránh tràn số khi l và r lớn
    
    if (a[m] == x) return m;
    if (x < a[m]) return binary_search_recursive(a, l, m - 1, x);
    return binary_search_recursive(a, m + 1, r, x);
}

// ========== 3. TÌM KIẾM NHỊ PHÂN VÒNG LẶP (BINARY SEARCH ITERATIVE) ==========
// Độ phức tạp thời gian: O(log n)
// Độ phức tạp không gian: O(1) - Khuyên dùng vì tiết kiệm bộ nhớ stack
int binary_search_iterative(int a[], int n, int x) {
    int l = 0, r = n - 1;
    while (l <= r) {
        int m = l + (r - l) / 2;
        if (a[m] == x) return m;
        if (x < a[m]) r = m - 1;
        else l = m + 1;
    }
    return -1;
}

// ========== 4. ỨNG DỤNG TÌM KIẾM TRÊN CẤU TRÚC SINH VIÊN ==========
typedef struct {
    int sid;
    char name[30];
    float gpa;
} Student;

// Tìm kiếm sinh viên theo mã số (Linear Search)
int search_student_by_id(Student s[], int n, int sid) {
    for (int i = 0; i < n; i++) {
        if (s[i].sid == sid) return i;
    }
    return -1;
}

// Tìm kiếm sinh viên theo tên (Không phân biệt chữ hoa/thường)
int search_student_by_name(Student s[], int n, const char *name) {
    for (int i = 0; i < n; i++) {
        if (strcasecmp(s[i].name, name) == 0) return i;
    }
    return -1;
}

int main() {
    int a[] = {2, 5, 8, 12, 16, 23, 38, 45, 56, 72};
    int n = sizeof(a) / sizeof(a[0]);

    printf("=== KIỂM TRA GIẢI THUẬT TÌM KIẾM (SEARCHING) ===\n\n");
    printf("Mang da sap xep: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n\n");

    int x = 23;
    printf("1. Tim kiem tuyen tinh: Gia tri %d -> Vi tri %d\n", x, linear_search(a, n, x));
    printf("2. Tim kiem nhi phan (De quy): Gia tri %d -> Vi tri %d\n", x, binary_search_recursive(a, 0, n - 1, x));
    printf("3. Tim kiem nhi phan (Vong lap): Gia tri %d -> Vi tri %d\n", x, binary_search_iterative(a, n, x));

    // Tìm kiếm sinh viên
    Student students[] = {
        {120, "Binh", 7.5}, 
        {121, "An", 7.5}, 
        {122, "Khoa", 8.5}
    };
    int sn = sizeof(students) / sizeof(students[0]);

    printf("\n--- Tim Kiem Sinh Vien ---\n");
    int idx_id = search_student_by_id(students, sn, 122);
    if (idx_id >= 0) {
        printf("Tim theo ID 122: Tim thay sinh vien '%s' voi GPA = %.2f\n", students[idx_id].name, students[idx_id].gpa);
    } else {
        printf("Tim theo ID 122: Không tìm thấy\n");
    }

    int idx_name = search_student_by_name(students, sn, "an");
    if (idx_name >= 0) {
        printf("Tim theo ten 'an': Tim thay sinh vien ID = %d, GPA = %.2f\n", students[idx_name].sid, students[idx_name].gpa);
    } else {
        printf("Tim theo ten 'an': Không tìm thấy\n");
    }

    return 0;
}
