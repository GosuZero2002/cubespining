# Hình Lập Phương Xoay bằng mã ASCII

## Giới Thiệu
Dự án này tạo ra một **hình lập phương xoay 3D bằng ký tự ASCII** hiển thị trong terminal. Chương trình sử dụng **biến đổi 3D cơ bản**, bao gồm xoay và chiếu, để hiển thị hình lập phương quay liên tục.

## Tính Năng
- **Xoay 3D:** Hình lập phương xoay quanh các trục X, Y và Z.
- **Z-buffering:** Xử lý độ sâu để hiển thị mặt trước/mặt sau đúng thứ tự.
- **Hiển thị bằng ASCII:** Dùng các ký tự khác nhau để tạo hiệu ứng hiển thị các mặt của hình lập phương.
- **Tương thích đa nền tảng:** Chạy được trên cả **Windows** và **Linux/macOS**.

## Cách Hoạt Động
### 1. **Chuyển đổi 3D sang 2D**
Chương trình sử dụng **ma trận xoay** để biến đổi tọa độ 3D của hình lập phương thành mặt phẳng 2D để hiển thị trên console.

### 2. **Z-buffer để xử lý độ sâu**
Z-buffer giúp xác định điểm nào cần được hiển thị trước và tránh bị đè bởi các điểm phía sau.

### 3. **Hiển thị bằng ký tự ASCII**
Các ký tự (`0, ~, ", #, ;, +`) được sử dụng để biểu diễn các mặt của hình lập phương, giúp tạo hiệu ứng độ sâu và bóng tối.

### 4. **Xoay liên tục**
Hình lập phương xoay liên tục bằng cách tăng góc (`A, B, C`) sau mỗi khung hình.

## Yêu Cầu
- **Trình biên dịch C++** (GCC, Clang hoặc MSVC)
- **Cửa sổ Terminal/Console**

## Biên Dịch & Chạy Chương Trình
### **Linux/macOS**
```sh
g++ -o cube cube.cpp -std=c++11 -lpthread
./cube
```

### **Windows**
```sh
g++ -o cube.exe cube.cpp -std=c++11 -lpthread
cube.exe
```

## Điều Khiển
- **Không cần thao tác** - Hình lập phương tự động xoay.

## Tối Ưu Hiệu Suất
- Tốc độ hiển thị được điều chỉnh bằng `std::this_thread::sleep_for(std::chrono::milliseconds(30))`, đảm bảo hiển thị mượt mà với ~30-60 FPS.
- Giảm kích thước `width` và `height` có thể giúp chương trình chạy nhanh hơn trên máy yếu.

## Cải Tiến Trong Tương Lai
- Thêm điều khiển bằng bàn phím để thay đổi tốc độ xoay.
- Cải thiện hiệu ứng bóng để hiển thị đẹp hơn.
- Cho phép chọn kiểu ASCII khác nhau để hiển thị.

##Tài liệu tham khảo 
Ma trận quay : https://en.wikipedia.org/wiki/Rotation_matrix
