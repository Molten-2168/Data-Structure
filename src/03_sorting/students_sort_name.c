/*
 * Bài tập 2: Sắp xếp danh sách sinh viên theo tên tăng dần (Selection Sort)
 * ========================================================================
 * Đọc dữ liệu từ file 'students.txt', sau đó sử dụng giải thuật Selection Sort
 * để sắp xếp danh sách sinh viên theo thứ tự bảng chữ cái tăng dần của tên.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

// Sắp xếp sinh viên theo tên tăng dần (Selection Sort)
// Độ phức tạp thời gian: O(n^2)
void sort_by_name_asc(Student s[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            // So sánh chuỗi phân biệt hoa thường (strcmp)
            if (strcmp(s[j].name, s[min_idx].name) < 0) {
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

    sort_by_name_asc(students, n);

    printf("\n=== DANH SÁCH SẮP XẾP THEO TÊN TĂNG DẦN (Selection Sort) ===\n");
    print_students(students, n);
    return 0;
}
