# Exercise-1:
- Lập trình ứng dụng có chức năng tương tự lệnh `tasklist` của Windows. Hai cột thông tin bắt buộc là `Image Name` & `PID`.
- Mô tả:
  - Cấu trúc muốn liệt kê: Image Name, PID.
# Exercise-2:
- Lập trình ứng dụng có chức năng tương tự lệnh `taskkill` của Windows. Hỗ trợ 2 phương thức terminate process (theo Image name hoặc theo ProcessID), chỉ định phương thức qua tham số truyền vào chương trình.
- Mô tả:
  - Sử dụng WindowsAPI -> `TerminateProcess(){}`.
# Exercise-3:
- Viết chương trình mô phỏng cuộc thi chạy đua xử lý giữa 3 Thread:
  - Thread 1: đếm số từ trong file 1.txt.
  - Thread 2: đếm số file có trong thư mục hiện tại.
  - Thread 3: đếm số thread của process `explorer.exe`.
- Hiển thị ra màn hình thứ tự giải của 3 thread theo thời gian hoàn thành. Ví dụ:
```powershell
Thread 2: Giải nhất
Thread 1: Giải nhì
Thread 3: Giải ba
```
- Mô tả:
  - C1: Sử dụng WindowsAPI -> `GetThreadTimes(){}`.
  - C2: GetExitCodeThread(), getTicketCount(). 