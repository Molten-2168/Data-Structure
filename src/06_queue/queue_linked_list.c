/*
 * HÀNG ĐỢI (Queue) - Cài đặt bằng Danh sách liên kết đơn
 * =======================================================
 * Cài đặt này duy trì hai con trỏ quản lý đầu và cuối hàng đợi:
 *   - front: Trỏ đến Node đầu hàng (nơi lấy ra - Dequeue).
 *   - rear: Trỏ đến Node cuối hàng (nơi thêm vào - Enqueue).
 * Giúp cho cả hai thao tác Enqueue và Dequeue đều đạt độ phức tạp O(1).
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Định nghĩa Node
typedef struct Node {
    int data;
    struct Node *next;
} Node;

// Định nghĩa cấu trúc Queue
typedef struct {
    Node *front; // Đầu hàng đợi
    Node *rear;  // Cuối hàng đợi
} Queue;

// --- Khởi tạo Node mới ---
Node* create_node(int data) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (node != NULL) {
        node->data = data;
        node->next = NULL;
    }
    return node;
}

// --- Khởi tạo Hàng đợi ---
Queue* create_queue() {
    Queue *q = (Queue *)malloc(sizeof(Queue));
    if (q != NULL) {
        q->front = NULL;
        q->rear = NULL;
    }
    return q;
}

// --- Kiểm tra rỗng ---
bool is_empty(Queue *q) {
    return q->front == NULL;
}

// --- Enqueue: Thêm vào cuối hàng (O(1)) ---
void enqueue(Queue *q, Node *node) {
    if (node == NULL) return;
    if (is_empty(q)) {
        // Hàng đợi rỗng thì node mới chính là cả đầu và cuối hàng
        q->front = q->rear = node;
    } else {
        q->rear->next = node;
        q->rear = node; // Cập nhật con trỏ rear chỉ đến node mới
    }
}

// --- Dequeue: Lấy ra từ đầu hàng (O(1)) ---
Node* dequeue(Queue *q) {
    if (is_empty(q)) return NULL;
    
    Node *temp = q->front;
    q->front = q->front->next; // Chuyển front sang node tiếp theo
    
    if (q->front == NULL) {
        // Nếu hàng đợi rỗng sau khi dequeue, đặt cả rear bằng NULL
        q->rear = NULL;
    }
    return temp; // Trả về node bị dequeue để bên ngoài xử lý và free
}

// --- Peek: Xem đầu hàng ---
Node* peek(Queue *q) {
    return q->front;
}

// --- Hiển thị hàng đợi ---
void display(Queue *q) {
    if (is_empty(q)) {
        printf("Queue rong\n");
        return;
    }
    printf("Front -> ");
    Node *cur = q->front;
    while (cur != NULL) {
        printf("%d -> ", cur->data);
        cur = cur->next;
    }
    printf("NULL <- Rear\n");
}

// --- Giải phóng hàng đợi ---
void free_queue(Queue *q) {
    while (!is_empty(q)) {
        Node *temp = dequeue(q);
        free(temp);
    }
    free(q);
}

int main() {
    Queue *q = create_queue();
    if (q == NULL) return 1;

    printf("=== KIỂM TRA HÀNG ĐỢI DÙNG DANH SÁCH LIÊN KẾT (LINKED LIST QUEUE) ===\n\n");
    enqueue(q, create_node(10));
    enqueue(q, create_node(20));
    enqueue(q, create_node(30));
    display(q);

    Node *popped = dequeue(q);
    if (popped != NULL) {
        printf("Lay ra (Dequeue): %d\n", popped->data);
        free(popped);
    }
    display(q);

    enqueue(q, create_node(40));
    enqueue(q, create_node(50));
    display(q);

    Node *front_node = peek(q);
    if (front_node != NULL) {
        printf("Xem dau hang (Peek): %d\n", front_node->data);
    }

    free_queue(q);
    return 0;
}
