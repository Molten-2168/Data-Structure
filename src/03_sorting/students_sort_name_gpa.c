/*
 * Bài tập 3: Sắp xếp sinh viên theo tên tăng dần (không phân biệt hoa-thường),
 *           nếu trùng tên thì sắp xếp theo điểm GPA giảm dần (Selection Sort)
 * =========================================================================
 * Đọc dữ liệu từ file 'students.txt', sau đó sử dụng giải thuật Selection Sort
 * với tiêu chí so sánh kép:
 *   1. Tiêu chí chính: So sánh tên không phân biệt hoa thường (strcasecmp).
 *   2. Tiêu chí phụ: Nếu trùng tên, so sánh điểm GPA giảm dần.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
    #define strcasecmp _stricmp // Tương thích Windows
#else
    #include <strings.h>       // POSIX strcasecmp
#endif

typedef struct {
    int sid;
    char name[30];
    float gpa;
} Student;

// In danh sách sinh viên dưới dạng bảng
void print_students(Student s[], int n) {
    printf("| %-4s | %-12s | %-5s |\n", "ID", "Name", "GPA");
    printf("|------|--------------|-------|\n");
    for (int i = 0; i < n; i++) {
        printf("| %-4d | %-12s | %-5.2f |\n", s[i].sid, s[i].name, s[i].gpa);
    }
}

// Đọc dữ liệu sinh viên
int load_students(const char *filename, Student students[]) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        printf("Loi: Khong the mo file %s\n", filename);
        return 0;
    }
    int i = 0;
    while (fscanf(f, "%d %29s %f", &students[i].sid, students[i].name, &students[i].gpa) == 3) {
        i++;
    }
    fclose(f);
    return i;
}

// Sắp xếp kép: Tên tăng dần (không phân biệt hoa thường) + GPA giảm dần
void sort_by_name_gpa(Student s[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            // So sánh tên không phân biệt chữ hoa / chữ thường
            int cmp = strcasecmp(s[j].name, s[min_idx].name);
            
            // Trường hợp 1: Tên nhỏ hơn
            // Trường hợp 2: Tên trùng nhau (cmp == 0) và GPA lớn hơn (giảm dần)
            if (cmp < 0 || (cmp == 0 && s[j].gpa > s[min_idx].gpa)) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            Student temp = s[i];
            s[i] = s[min_idx];
            s[min_idx] = temp;
        }
    }
}

int main() {
    Student students[100];
    int n = load_students("students.txt", students);
    if (n == 0) {
        printf("Danh sach sinh vien rong hoac loi doc file.\n");
        return 1;
    }

    printf("=== DANH SÁCH SINH VIÊN BAN ĐẦU ===\n");
    print_students(students, n);

    sort_by_name_gpa(students, n);

    printf("\n=== DANH SÁCH SẮP XẾP TÊN TĂNG DẦN (KHÔNG CƠ CHỮ) + GPA GIẢM DẦN ===\n");
    print_students(students, n);
    return 0;
}
