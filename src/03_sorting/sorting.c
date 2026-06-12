/*
 * SẮP XẾP (Sorting Algorithms)
 * ============================
 * Các thuật toán sắp xếp cơ bản (O(n^2)) và nâng cao (O(n log n)):
 *   1. Bubble Sort (Sắp xếp nổi bọt)
 *   2. Selection Sort (Sắp xếp chọn)
 *   3. Insertion Sort (Sắp xếp chèn)
 *   4. Merge Sort (Sắp xếp trộn)
 *   5. Quick Sort (Sắp xếp nhanh)
 */

#include <stdio.h>
#include <stdlib.h>

// Hàm hoán vị hai giá trị nguyên
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// In các phần tử trong mảng kèm theo thông báo
void print_array(int a[], int n, const char *msg) {
    printf("%-25s: ", msg);
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

// ========== 1. BUBBLE SORT - O(n^2) ==========
// Ổn định (Stable): Có.
void bubble_sort(int a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                swap(&a[j], &a[j + 1]);
            }
        }
    }
}

// Phiên bản Bubble Sort tối ưu (Dừng sớm nếu mảng đã được sắp xếp)
// Độ phức tạp tốt nhất: O(n)
void bubble_sort_optimized(int a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int swapped = 0;
        for (int j = 0; j < n - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                swap(&a[j], &a[j + 1]);
                swapped = 1;
            }
        }
        if (!swapped) break; // Mảng đã sắp xếp xong, dừng vòng lặp
    }
}

// ========== 2. SELECTION SORT - O(n^2) ==========
// Ổn định: Không.
void selection_sort(int a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (a[j] < a[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            swap(&a[i], &a[min_idx]);
        }
    }
}

// ========== 3. INSERTION SORT - O(n^2) ==========
// Ổn định: Có. Thích hợp cho mảng có kích thước nhỏ hoặc đã gần được sắp xếp (O(n)).
void insertion_sort(int a[], int n) {
    for (int i = 1; i < n; i++) {
        int key = a[i];
        int j = i - 1;
        // Di chuyển các phần tử lớn hơn key về sau một vị trí
        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}

// ========== 4. MERGE SORT - O(n log n) ==========
// Ổn định: Có. Sử dụng tài nguyên bổ sung O(n) bộ nhớ phụ.
void merge(int a[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    // Cấp phát động để tránh lỗi giới hạn kích thước mảng tĩnh (VLA)
    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    if (L == NULL || R == NULL) {
        printf("Loi: Khong du bo nho cap phat!\n");
        return;
    }

    for (int i = 0; i < n1; i++) L[i] = a[l + i];
    for (int j = 0; j < n2; j++) R[j] = a[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            a[k++] = L[i++];
        } else {
            a[k++] = R[j++];
        }
    }

    while (i < n1) a[k++] = L[i++];
    while (j < n2) a[k++] = R[j++];

    free(L);
    free(R);
}

void merge_sort(int a[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        merge_sort(a, l, m);
        merge_sort(a, m + 1, r);
        merge(a, l, m, r);
    }
}

// ========== 5. QUICK SORT - O(n log n) ==========
// Ổn định: Không. Trường hợp xấu nhất (mảng đã sắp xếp và chọn chốt tệ): O(n^2).
// Phân hoạch Lomuto
int partition(int a[], int l, int r) {
    int pivot = a[r]; // Chọn phần tử cuối cùng làm chốt
    int i = l - 1;
    for (int j = l; j < r; j++) {
        if (a[j] <= pivot) {
            i++;
            swap(&a[i], &a[j]);
        }
    }
    swap(&a[i + 1], &a[r]);
    return i + 1;
}

void quick_sort(int a[], int l, int r) {
    if (l < r) {
        int p = partition(a, l, r);
        quick_sort(a, l, p - 1);
        quick_sort(a, p + 1, r);
    }
}

int main() {
    printf("=== KIỂM TRA GIẢI THUẬT SẮP XẾP (SORTING) ===\n\n");

    int orig[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(orig) / sizeof(orig[0]);

    // Bản sao mảng để test từng thuật toán
    int temp[n];

    // 1. Bubble Sort
    for (int i = 0; i < n; i++) temp[i] = orig[i];
    bubble_sort(temp, n);
    print_array(temp, n, "1. Bubble Sort");

    // 1b. Bubble Sort Optimized
    for (int i = 0; i < n; i++) temp[i] = orig[i];
    bubble_sort_optimized(temp, n);
    print_array(temp, n, "1b. Bubble Sort Toi Uu");

    // 2. Selection Sort
    for (int i = 0; i < n; i++) temp[i] = orig[i];
    selection_sort(temp, n);
    print_array(temp, n, "2. Selection Sort");

    // 3. Insertion Sort
    for (int i = 0; i < n; i++) temp[i] = orig[i];
    insertion_sort(temp, n);
    print_array(temp, n, "3. Insertion Sort");

    // 4. Merge Sort
    for (int i = 0; i < n; i++) temp[i] = orig[i];
    merge_sort(temp, 0, n - 1);
    print_array(temp, n, "4. Merge Sort");

    // 5. Quick Sort
    for (int i = 0; i < n; i++) temp[i] = orig[i];
    quick_sort(temp, 0, n - 1);
    print_array(temp, n, "5. Quick Sort");

    return 0;
}
