/*
 * NGĂN XẾP SINH VIÊN (Student Stack)
 * =================================
 * Minh họa cài đặt Stack lưu trữ kiểu dữ liệu tự định nghĩa (struct Student).
 * Sử dụng cấu trúc mảng tĩnh để lưu các bản ghi học sinh.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    int sid;
    char name[30];
    float gpa;
} Student;

typedef struct {
    Student data[MAX];
    int top;
} StudentStack;

// --- Khởi tạo Stack ---
StudentStack* create_stack() {
    StudentStack *s = (StudentStack *)malloc(sizeof(StudentStack));
    if (s != NULL) {
        s->top = -1;
    }
    return s;
}

// --- Kiểm tra rỗng ---
bool is_empty(StudentStack *s) {
    return s->top == -1;
}

// --- Kiểm tra đầy ---
bool is_full(StudentStack *s) {
    return s->top == MAX - 1;
}

// --- Push: Thêm sinh viên ---
bool push(StudentStack *s, Student st) {
    if (is_full(s)) return false;
    s->data[++(s->top)] = st;
    return true;
}

// --- Pop: Lấy sinh viên ra ---
Student pop(StudentStack *s) {
    Student empty = {-1, "", 0.0};
    if (is_empty(s)) return empty;
    return s->data[(s->top)--];
}

// --- Peek: Xem sinh viên ở đỉnh ---
Student peek(StudentStack *s) {
    Student empty = {-1, "", 0.0};
    if (is_empty(s)) return empty;
    return s->data[s->top];
}

// --- In thông tin một sinh viên ---
void print_student(Student s) {
    printf("[%d | %s | %.2f]", s.sid, s.name, s.gpa);
}

// --- Hiển thị toàn bộ ngăn xếp sinh viên ---
void display(StudentStack *s) {
    if (is_empty(s)) {
        printf("Ngan xep rong!\n");
        return;
    }
    printf("Bottom -> ");
    for (int i = 0; i <= s->top; i++) {
        print_student(s->data[i]);
        printf(" ");
    }
    printf("<- Top\n");
}

int main() {
    StudentStack *s = create_stack();
    if (s == NULL) return 1;

    Student s1 = {123, "Thanh", 7.5};
    Student s2 = {124, "An",    8.4};
    Student s3 = {125, "Binh",  6.1};

    printf("=== KIỂM TRA NGĂN XẾP SINH VIÊN (STUDENT STACK) ===\n\n");
    printf("Day sinh vien vao stack (Push):\n");
    push(s, s1);
    push(s, s2);
    push(s, s3);
    display(s);

    printf("\nXem sinh vien o dinh (Peek): ");
    print_student(peek(s));
    printf("\n");

    printf("\nLay sinh vien o dinh ra (Pop): ");
    print_student(pop(s));
    printf("\n");
    display(s);

    printf("\nLay tiep sinh vien (Pop): ");
    print_student(pop(s));
    printf("\n");
    
    printf("Lay tiep sinh vien (Pop): ");
    print_student(pop(s));
    printf("\n");

    printf("Lay khi stack rong: ");
    Student empty_check = pop(s);
    print_student(empty_check);
    printf(" (Tra ve ma ID -1 mac dinh)\n");

    free(s);
    return 0;
}
