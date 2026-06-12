/*
 * HÀNG ĐỢI (Queue) - Cài đặt bằng Mảng vòng (Circular Array)
 * ==========================================================
 * Nguyên lý hoạt động: FIFO (First In, First Out) - Vào trước ra trước.
 * Các thao tác cơ bản:
 *   - enqueue: Thêm phần tử vào cuối hàng đợi (rear).
 *   - dequeue: Lấy phần tử ở đầu hàng đợi ra ngoài (front).
 *   - peek/front: Xem giá trị ở đầu hàng đợi.
 * Tại sao dùng mảng vòng? 
 *   Nếu dùng mảng thông thường, sau khi dequeue, các ô đầu sẽ bị bỏ trống
 *   gây lãng phí bộ nhớ. Mảng vòng giải quyết bằng cách nối đuôi chỉ số: 
 *   index = (index + 1) % MAX.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX 5 // Để kích thước nhỏ để dễ kiểm tra cơ chế mảng vòng

typedef struct {
    int data[MAX];
    int front; // Chỉ số đầu hàng
    int rear;  // Chỉ số cuối hàng
    int size;  // Số lượng phần tử hiện tại
} Queue;

// --- Khởi tạo Hàng đợi ---
Queue* create_queue() {
    Queue *q = (Queue *)malloc(sizeof(Queue));
    if (q != NULL) {
        q->front = 0;
        q->rear = 0;
        q->size = 0;
    }
    return q;
}

// --- Kiểm tra rỗng ---
bool is_empty(Queue *q) {
    return q->size == 0;
}

// --- Kiểm tra đầy ---
bool is_full(Queue *q) {
    return q->size == MAX;
}

// --- Enqueue: Thêm vào cuối hàng (O(1)) ---
bool enqueue(Queue *q, int value) {
    if (is_full(q)) {
        printf("Loi: Hang doi day! Khong the enqueue %d\n", value);
        return false;
    }
    q->data[q->rear] = value;
    q->rear = (q->rear + 1) % MAX; // Tăng vòng chỉ số rear
    q->size++;
    return true;
}

// --- Dequeue: Lấy ra từ đầu hàng (O(1)) ---
int dequeue(Queue *q) {
    if (is_empty(q)) {
        printf("Loi: Hang doi rong!\n");
        return -1;
    }
    int value = q->data[q->front];
    q->front = (q->front + 1) % MAX; // Tăng vòng chỉ số front
    q->size--;
    return value;
}

// --- Peek: Xem đầu hàng ---
int peek(Queue *q) {
    if (is_empty(q)) return -1;
    return q->data[q->front];
}

// --- Hiển thị hàng đợi từ Front đến Rear ---
void display(Queue *q) {
    if (is_empty(q)) {
        printf("Queue rong\n");
        return;
    }
    printf("Front -> ");
    for (int i = 0; i < q->size; i++) {
        int idx = (q->front + i) % MAX;
        printf("%d ", q->data[idx]);
    }
    printf("<- Rear (Kich thuoc hien tai: %d/%d)\n", q->size, MAX);
}

int main() {
    Queue *q = create_queue();
    if (q == NULL) return 1;

    printf("=== KIỂM TRA HÀNG ĐỢI MẢNG VÒNG (CIRCULAR ARRAY QUEUE) ===\n\n");
    enqueue(q, 10);
    enqueue(q, 20);
    enqueue(q, 30);
    enqueue(q, 40);
    display(q);

    printf("Lay ra (Dequeue): %d\n", dequeue(q));
    printf("Lay ra (Dequeue): %d\n", dequeue(q));
    display(q);

    // Chèn tiếp để test cơ chế xoay vòng
    printf("\n--- Test xoay vong chi so mảng ---\n");
    enqueue(q, 50);
    enqueue(q, 60);
    enqueue(q, 70); // Lúc này rear quay về các ô trống cũ
    display(q);

    // Thử chèn khi đầy
    enqueue(q, 80);

    // Dọn dẹp hàng đợi
    printf("\nLam rong hang doi:\n");
    while (!is_empty(q)) {
        printf("Dequeued: %d\n", dequeue(q));
    }
    display(q);

    free(q);
    return 0;
}
