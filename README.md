# CẤU TRÚC DỮ LIỆU VÀ GIẢI THUẬT (DATA STRUCTURES & ALGORITHMS)
## Giáo trình Học thuật & Thực hành Biên soạn bởi Đại học Hoa Sen

Tài liệu này là cẩm nang học thuật toàn diện về môn **Cấu trúc dữ liệu và Giải thuật (DSA)** được triển khai bằng ngôn ngữ lập trình **C**. Tài liệu được tổ chức một cách khoa học từ lý thuyết nền tảng, mã nguồn tối ưu hóa, đến các bài tập thực hành thực tế, giúp người học dễ dàng tự nghiên cứu và nắm vững kiến thức.

---

## MỤC LỤC

1. [Giới thiệu Chung về DSA](#1-giới-thiệu-chung-về-dsa)
2. [Đệ quy (Recursion)](#2-đệ-quy-recursion)
3. [Tìm kiếm (Searching)](#3-tìm-kiếm-searching)
4. [Sắp xếp (Sorting)](#4-sắp-xếp-sorting)
5. [Danh sách Liên kết Đơn (Singly Linked List)](#5-danh-sách-liên-kết-đơn-singly-linked-list)
6. [Ngăn xếp (Stack)](#6-ngăn-xếp-stack)
7. [Hàng đợi (Queue)](#7-hàng-đợi-queue)
8. [Hướng dẫn Biên dịch & Chạy mã nguồn](#8-hướng-dẫn-biên-dịch--chạy-mã-nguồn)
9. [Cấu trúc Thư mục Dự án](#9-cấu-trúc-thư-mục-dự-án)
10. [Tài liệu Tham khảo](#10-tài-liệu-tham-khảo)

---

## 1. GIỚI THIỆU CHUNG VỀ DSA

### 1.1 Cấu trúc dữ liệu (Data Structure) là gì?
Cấu trúc dữ liệu là cách thức tổ chức, quản lý và lưu trữ dữ liệu trong bộ nhớ máy tính sao cho dữ liệu có thể được truy xuất và thao tác một cách hiệu quả nhất.

**Phân loại:**
*   **Tuyến tính (Linear):** Các phần tử dữ liệu được sắp xếp tuần tự nối tiếp nhau.
    *   *Ví dụ:* Mảng (Array), Danh sách liên kết (Linked List), Ngăn xếp (Stack), Hàng đợi (Queue).
*   **Phi tuyến (Non-linear):** Các phần tử dữ liệu liên kết với nhau theo cấu trúc phân nhánh hoặc lưới.
    *   *Ví dụ:* Cây (Tree), Đồ thị (Graph).

### 1.2 Giải thuật (Algorithm) là gì?
Giải thuật là một tập hợp hữu hạn các bước chỉ dẫn rõ ràng để giải quyết một bài toán cụ thể. Một giải thuật tốt cần đạt được sự tối ưu về tài nguyên hệ thống thông qua việc đánh giá:
1.  **Độ phức tạp thời gian (Time Complexity):** Lượng thời gian giải thuật cần để chạy hết chương trình, được ký hiệu thông qua **Big O Notation** (Ví dụ: $O(1)$, $O(\log n)$, $O(n)$, $O(n \log n)$, $O(n^2)$).
2.  **Độ phức tạp không gian (Space Complexity):** Lượng bộ nhớ bổ sung cần thiết trong quá trình giải thuật vận hành.

---

## 2. ĐỆ QUY (RECURSION)

### 2.1 Khái niệm
Đệ quy là kỹ thuật lập trình trong đó một hàm tự gọi lại chính nó để giải quyết bài toán lớn bằng cách chia nhỏ thành các bài toán cùng dạng có kích thước bé hơn.

Một hàm đệ quy chuẩn mực bắt buộc phải có hai phần:
1.  **Trường hợp cơ sở (Base Case):** Điều kiện dừng của đệ quy. Thiếu điều kiện này sẽ dẫn đến lỗi tràn bộ nhớ Stack (Stack Overflow).
2.  **Trường hợp đệ quy (Recursive Case):** Lời gọi hàm tự quy về chính nó với tham số được thu hẹp về phía trường hợp cơ sở.

> [!WARNING]
> Sử dụng đệ quy quá sâu sẽ tiêu tốn bộ nhớ Stack để lưu trạng thái của hàm. Hãy luôn cân nhắc sử dụng phiên bản khử đệ quy (vòng lặp) khi hiệu năng là ưu tiên hàng đầu.

### 2.2 Các bài toán điển hình trong mã nguồn
*   **Giai thừa (Factorial):** $n! = n \times (n-1)!$ với trường hợp cơ sở $0! = 1! = 1$. Độ phức tạp: $O(n)$ thời gian, $O(n)$ không gian.
*   **Dãy số Fibonacci:** $F(n) = F(n-1) + F(n-2)$. Giải thuật đệ quy ngây thơ có độ phức tạp thời gian rất lớn là $O(2^n)$.
*   **Ước chung lớn nhất (GCD):** Áp dụng thuật toán Euclid đệ quy $gcd(a, b) = gcd(b, a \pmod b)$.
*   **Tháp Hà Nội (Tower of Hanoi):** Giải pháp chia để trị huyền thoại để chuyển $n$ đĩa giữa các cọc. Số bước di chuyển tối thiểu là $2^n - 1$.

👉 **Mã nguồn chi tiết:** [recursion.c](file:///Users/musual/Documents/Data-Structure/src/01_recursion/recursion.c)

---

## 3. TÌM KIẾM (SEARCHING)

Các giải thuật tìm kiếm được thiết kế nhằm xác định vị trí của một phần tử mục tiêu ($x$) trong một tập hợp dữ liệu.

### 3.1 Tìm kiếm tuyến tính (Linear Search)
Duyệt qua từng phần tử của mảng từ đầu đến cuối cho đến khi tìm thấy phần tử mong muốn hoặc hết mảng.
*   **Độ phức tạp thời gian:** $O(n)$
*   **Độ phức tạp không gian:** $O(1)$
*   **Yêu cầu mảng:** Không cần sắp xếp trước.

### 3.2 Tìm kiếm nhị phân (Binary Search)
Áp dụng chiến lược chia để trị trên một mảng **đã sắp xếp**. Tại mỗi bước, so sánh giá trị trung vị (mid) với giá trị cần tìm để loại bỏ một nửa không gian tìm kiếm.
*   **Độ phức tạp thời gian:** $O(\log n)$
*   **Độ phức tạp không gian:** $O(1)$ đối với vòng lặp, $O(\log n)$ đối với đệ quy.
*   **Yêu cầu mảng:** Bắt buộc phải được sắp xếp trước.

### 3.3 Bảng so sánh giải thuật tìm kiếm

| Tiêu chí | Tìm kiếm Tuyến tính | Tìm kiếm Nhị phân |
| :--- | :--- | :--- |
| **Độ phức tạp tốt nhất** | $O(1)$ | $O(1)$ |
| **Độ phức tạp trung bình/xấu** | $O(n)$ | $O(\log n)$ |
| **Độ phức tạp không gian** | $O(1)$ | $O(1)$ (Lặp) / $O(\log n)$ (Đệ quy) |
| **Yêu cầu dữ liệu** | Tùy ý | Đã sắp xếp |
| **Cấu trúc phù hợp** | Mảng, Danh sách liên kết | Chỉ hiệu quả trên Mảng (truy cập ngẫu nhiên $O(1)$) |

👉 **Mã nguồn chi tiết:** [searching.c](file:///Users/musual/Documents/Data-Structure/src/02_searching/searching.c)

---

## 4. SẮP XẾP (SORTING)

Sắp xếp là quá trình tổ chức các phần tử dữ liệu theo một thứ tự xác định (tăng dần hoặc giảm dần).

### 4.1 Các giải thuật cơ bản ($O(n^2)$)
1.  **Bubble Sort (Sắp xếp nổi bọt):** So sánh các cặp phần tử kề nhau và đổi chỗ nếu sai thứ tự. Các phần tử lớn hơn sẽ từ từ "nổi" về cuối mảng.
2.  **Selection Sort (Sắp xếp chọn):** Tìm phần tử nhỏ nhất trong phần chưa sắp xếp, sau đó hoán đổi nó với phần tử đầu tiên của phân đoạn chưa sắp xếp đó.
3.  **Insertion Sort (Sắp xếp chèn):** Xây dựng mảng đã sắp xếp dần dần bằng cách chèn phần tử hiện tại vào đúng vị trí thích hợp của nó trong danh sách con đã sắp xếp trước đó.

### 4.2 Các giải thuật nâng cao ($O(n \log n)$)
1.  **Merge Sort (Sắp xếp trộn):** Chia đôi mảng liên tục cho đến khi mỗi mảng con chỉ còn 1 phần tử, sau đó trộn các mảng con đã sắp xếp lại với nhau. Cần thêm $O(n)$ bộ nhớ phụ.
2.  **Quick Sort (Sắp xếp nhanh):** Chọn một phần tử làm chốt (pivot), phân hoạch mảng thành hai phần (nhỏ hơn chốt bên trái, lớn hơn chốt bên phải) và đệ quy sắp xếp hai phần đó. Trường hợp xấu nhất xảy ra khi chọn chốt tồi có độ phức tạp $O(n^2)$.

### 4.3 Bảng so sánh hiệu năng các giải thuật sắp xếp

| Giải thuật | Thời gian Tốt nhất | Thời gian Trung bình | Thời gian Xấu nhất | Không gian bổ sung | Tính ổn định (Stable) |
| :--- | :---: | :---: | :---: | :---: | :---: |
| **Bubble Sort** | $O(n)$ *(tối ưu)* | $O(n^2)$ | $O(n^2)$ | $O(1)$ | **Có** |
| **Selection Sort**| $O(n^2)$ | $O(n^2)$ | $O(n^2)$ | $O(1)$ | Không |
| **Insertion Sort**| $O(n)$ | $O(n^2)$ | $O(n^2)$ | $O(1)$ | **Có** |
| **Merge Sort** | $O(n \log n)$ | $O(n \log n)$ | $O(n \log n)$ | $O(n)$ | **Có** |
| **Quick Sort** | $O(n \log n)$ | $O(n \log n)$ | $O(n^2)$ | $O(\log n)$ | Không |

> [!NOTE]
> **Tính ổn định (Stability)** có nghĩa là nếu hai phần tử có giá trị bằng nhau, vị trí tương đối của chúng trước và sau khi sắp xếp sẽ được giữ nguyên.

👉 **Mã nguồn thuật toán sắp xếp gốc:** [sorting.c](file:///Users/musual/Documents/Data-Structure/src/03_sorting/sorting.c)

### 4.4 Các bài tập ứng dụng thực tế (Quản lý sinh viên)
Trong thực tế, ta thường sắp xếp các đối tượng phức tạp (structs) thay vì mảng số nguyên đơn thuần. Các bài tập sau sử dụng tệp dữ liệu đầu vào [students.txt](file:///Users/musual/Documents/Data-Structure/src/03_sorting/students.txt):
*   **Bài tập 1: Sắp xếp theo GPA giảm dần (Bubble Sort)**
    👉 Mã nguồn: [students_sort_gpa.c](file:///Users/musual/Documents/Data-Structure/src/03_sorting/students_sort_gpa.c)
*   **Bài tập 2: Sắp xếp theo Tên tăng dần (Selection Sort)**
    👉 Mã nguồn: [students_sort_name.c](file:///Users/musual/Documents/Data-Structure/src/03_sorting/students_sort_name.c)
*   **Bài tập 3: Sắp xếp đa tiêu chí - Tên tăng dần (không phân biệt hoa/thường) & GPA giảm dần khi trùng tên (Selection Sort)**
    👉 Mã nguồn: [students_sort_name_gpa.c](file:///Users/musual/Documents/Data-Structure/src/03_sorting/students_sort_name_gpa.c)

---

## 5. DANH SÁCH LIÊN KẾT ĐƠN (SINGLY LINKED LIST)

### 5.1 Khái niệm
Danh sách liên kết đơn là một cấu trúc dữ liệu động gồm chuỗi các nút (Node). Mỗi Node được phân bổ độc lập trên bộ nhớ Heap và kết nối với nhau thông qua con trỏ `next`.

```
Node [data | next] ---> Node [data | next] ---> NULL (Cuối danh sách)
```

### 5.2 So sánh Mảng và Danh sách liên kết

| Tiêu chí | Mảng tĩnh (Array) | Danh sách liên kết (Linked List) |
| :--- | :--- | :--- |
| **Kích thước** | Cố định khi khai báo | Động, co giãn linh hoạt khi chạy chương trình |
| **Truy cập phần tử** | Ngẫu nhiên qua chỉ số $O(1)$ | Tuần tự từ đầu $O(n)$ |
| **Chèn / Xóa ở đầu** | Chậm $O(n)$ (phải dịch chuyển mảng) | Nhanh $O(1)$ |
| **Chèn / Xóa ở cuối** | Nhanh $O(1)$ (nếu mảng còn chỗ) | Chậm $O(n)$ (phải duyệt đến cuối mảng) |
| **Bộ nhớ** | Tối ưu, chỉ chứa dữ liệu | Tốn thêm bộ nhớ lưu địa chỉ con trỏ `next` |

👉 **Mã nguồn thực hành:** [singly_linked_list.c](file:///Users/musual/Documents/Data-Structure/src/04_linked_list/singly_linked_list.c)

---

## 6. NGĂN XẾP (STACK)

### 6.1 Khái niệm & Cơ chế
Stack hoạt động theo nguyên lý **LIFO (Last In, First Out)** - Phần tử nào được đẩy vào cuối cùng sẽ là phần tử đầu tiên được lấy ra khỏi ngăn xếp.

```
       |   |
Push   | 3 |   Pop
  |    | 2 |    |
  v    | 1 |    v
     +-----+
```

### 6.2 Các thao tác cơ bản
*   `push(x)`: Đặt phần tử $x$ lên đỉnh ngăn xếp.
*   `pop()`: Loại bỏ và trả về phần tử đang nằm ở đỉnh ngăn xếp.
*   `peek()` / `get_top()`: Xem thông tin phần tử ở đỉnh ngăn xếp mà không loại bỏ nó.
*   `is_empty()`: Kiểm tra ngăn xếp có trống hay không.

### 6.3 Ứng dụng thực tế
1.  Quản lý ngăn xếp cuộc gọi trong lập trình (Call Stack).
2.  Chức năng Hoàn tác/Làm lại (Undo/Redo) trong các phần mềm soạn thảo.
3.  Thuật toán duyệt đồ thị theo chiều sâu (DFS).
4.  Chuyển đổi hệ cơ số (Thập phân sang Nhị phân).
5.  Kiểm tra tính hợp lệ của biểu thức chứa các loại dấu ngoặc mở/đóng.

👉 **Mã nguồn cài đặt Stack bằng mảng tĩnh + Ứng dụng thực tế:** [stack_array.c](file:///Users/musual/Documents/Data-Structure/src/05_stack/stack_array.c)  
👉 **Mã nguồn cài đặt Stack bằng Danh sách liên kết đơn:** [stack_linked_list.c](file:///Users/musual/Documents/Data-Structure/src/05_stack/stack_linked_list.c)  
👉 **Mã nguồn Stack lưu trữ dữ liệu Struct Student:** [stack_student.c](file:///Users/musual/Documents/Data-Structure/src/05_stack/stack_student.c)

---

## 7. HÀNG ĐỢI (QUEUE)

### 7.1 Khái niệm & Cơ chế
Queue hoạt động theo nguyên lý **FIFO (First In, First Out)** - Phần tử nào đi vào hàng đợi trước tiên sẽ được lấy ra phục vụ trước tiên (tương tự như việc xếp hàng mua vé).

```
Enqueue ---> [ 3 | 2 | 1 ] ---> Dequeue
              Rear    Front
```

### 7.2 Cơ chế mảng vòng (Circular Array)
Khi cài đặt hàng đợi bằng mảng tĩnh thông thường, việc rút phần tử (dequeue) sẽ làm con trỏ `front` dịch chuyển về phía sau, để lại các ô nhớ trống phía trước không thể tái sử dụng, dẫn đến hiện tượng tràn giả. 

Để khắc phục, ta sử dụng **Mảng Vòng (Circular Array)** bằng cách sử dụng toán tử chia lấy dư `%` để liên kết chỉ số cuối cùng quay trở lại chỉ số 0:
*   Chỉ số tiếp theo của rear: `rear = (rear + 1) % MAX`
*   Chỉ số tiếp theo của front: `front = (front + 1) % MAX`

👉 **Mã nguồn cài đặt Queue mảng vòng:** [queue_array.c](file:///Users/musual/Documents/Data-Structure/src/06_queue/queue_array.c)  
👉 **Mã nguồn cài đặt Queue danh sách liên kết:** [queue_linked_list.c](file:///Users/musual/Documents/Data-Structure/src/06_queue/queue_linked_list.c)

---

## 8. HƯỚNG DẪN BIÊN DỊCH & CHẠY MÃ NGUỒN

Tất cả các chương trình đều được viết bằng chuẩn ngôn ngữ C tiêu chuẩn nên bạn có thể dễ dàng biên dịch trên macOS, Linux bằng `gcc/clang` hoặc Windows bằng `MinGW/MSVC`.

### 8.1 Trên macOS / Linux
Mở terminal và di chuyển tới thư mục chứa file nguồn mong muốn.

```bash
# Biên dịch chương trình đệ quy
clang -Wall -Wextra -o recursion src/01_recursion/recursion.c
./recursion

# Biên dịch chương trình tìm kiếm
clang -Wall -Wextra -o searching src/02_searching/searching.c
./searching

# Lưu ý quan trọng khi chạy các chương trình sắp xếp sinh viên:
# Bạn phải di chuyển vào thư mục 'src/03_sorting/' trước khi chạy để chương trình 
# có thể tìm thấy tệp dữ liệu 'students.txt'.
cd src/03_sorting
clang -Wall -Wextra -o students_sort_gpa students_sort_gpa.c
./students_sort_gpa
```

### 8.2 Trên Windows (sử dụng gcc của MinGW)
Mở Command Prompt hoặc PowerShell:

```powershell
gcc -Wall -o recursion.exe src/01_recursion/recursion.c
.\recursion.exe
```

---

## 9. CẤU TRÚC THƯ MỤC DỰ ÁN

```
Data-Structure/
├── README.md                          <- Tài liệu học thuật hướng dẫn này
├── labs/                              <- Tài liệu đề bài/lab PDF gốc HSU
│   ├── 01_NMLT_Lab.pdf
│   ├── 02_NMLT_Lab.pdf
│   ├── 03_NMLT_Lab.pdf
│   ├── CTDL_Lab 02_Đệ quy.pdf
│   ├── CTDL_Lab 04_Tìm kiếm.pdf
│   ├── CTDL_Lab 05_Sắp xếp I.pdf
│   ├── CTDL_Lab 07_Danh sách liên kết.pdf
│   ├── CTDL_Lab 08_Ngăn xếp.pdf
│   └── CTDL_Lab 09_Hàng đợi.pdf
└── src/                               <- Thư mục chứa toàn bộ mã nguồn
    ├── 01_recursion/
    │   └── recursion.c                <- Các ví dụ và bài toán đệ quy
    ├── 02_searching/
    │   └── searching.c                <- Giải thuật tìm kiếm nhị phân & tuyến tính
    ├── 03_sorting/
    │   ├── sorting.c                  <- 5 giải thuật sắp xếp cơ bản + nâng cao
    │   ├── students.txt               <- Dữ liệu sinh viên mẫu đầu vào
    │   ├── students_sort_gpa.c        <- BT1: Bubble sort GPA sinh viên
    │   ├── students_sort_name.c       <- BT2: Selection sort tên sinh viên
    │   └── students_sort_name_gpa.c   <- BT3: Sắp xếp tên và GPA (Trùng tên)
    ├── 04_linked_list/
    │   └── singly_linked_list.c       <- Danh sách liên kết đơn tương tác Menu
    ├── 05_stack/
    │   ├── stack_array.c              <- Stack mảng + kiểm tra dấu ngoặc
    │   ├── stack_linked_list.c        <- Stack danh sách liên kết động
    │   └── stack_student.c            <- Stack lưu trữ cấu trúc Student
    └── 06_queue/
        ├── queue_array.c              <- Queue mảng vòng (Circular Array)
        └── queue_linked_list.c        <- Queue danh sách liên kết
```

---

## 10. TÀI LIỆU THAM KHẢO

1.  **Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein** - *Introduction to Algorithms*, 4th Edition, MIT Press, 2022.
2.  **Brian W. Kernighan, Dennis M. Ritchie** - *The C Programming Language*, 2nd Edition, Prentice Hall, 1988.
3.  **Robert Sedgewick, Kevin Wayne** - *Algorithms*, 4th Edition, Addison-Wesley, 2011.
4.  **Khoa Công nghệ thông tin** - *Tài liệu môn Cấu trúc dữ liệu*, Đại học Hoa Sen.
5.  [GeeksforGeeks - Data Structures and Algorithms Guide](https://www.geeksforgeeks.org/data-structures/)
