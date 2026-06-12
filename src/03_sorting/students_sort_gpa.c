/*
 * Bài tập 1: Sắp xếp danh sách sinh viên theo điểm GPA giảm dần (Bubble Sort)
 * =========================================================================
 * Đọc dữ liệu từ file 'students.txt', lưu vào mảng struct Student, sau đó
 * áp dụng giải thuật Bubble Sort để sắp xếp theo GPA giảm dần.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int sid;
    char name[30];
    float gpa;
} Student;

// In danh sách sinh viên dưới dạng bảng đẹp mắt
void print_students(Student s[], int n) {
    printf("| %-4s | %-12s | %-5s |\n", "ID", "Name", "GPA");
    printf("|------|--------------|-------|\n");
    for (int i = 0; i < n; i++) {
        printf("| %-4d | %-12s | %-5.2f |\n", s[i].sid, s[i].name, s[i].gpa);
    }
}

// Đọc dữ liệu từ file văn bản
int load_students(const char *filename, Student students[]) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        printf("Loi: Khong the mo file %s\n", filename);
        return 0;
    }
    int i = 0;
    // Đọc theo định dạng: Mã_số Tên GPA
    while (fscanf(f, "%d %29s %f", &students[i].sid, students[i].name, &students[i].gpa) == 3) {
        i++;
    }
    fclose(f);
    return i;
}

// Sắp xếp sinh viên theo điểm GPA giảm dần (Bubble Sort)
// Độ phức tạp thời gian: O(n^2)
void sort_by_gpa_desc(Student s[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (s[j].gpa < s[j + 1].gpa) {
                // Hoán vị nguyên cấu trúc
                Student temp = s[j];
                s[j] = s[j + 1];
                s[j + 1] = temp;
            }
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

    sort_by_gpa_desc(students, n);

    printf("\n=== DANH SÁCH SẮP XẾP THEO GPA GIẢM DẦN (Bubble Sort) ===\n");
    print_students(students, n);
    return 0;
}
