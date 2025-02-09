# Cplus with CMake

# 🚀 CI/CD trên SSH Server với GitHub Actions - Tài Liệu Hướng Dẫn Chuẩn

## 🔥 Tổng Quan
CI/CD trên SSH Server với **GitHub Actions** giúp **tự động build, test, và deploy** ứng dụng khi bạn **push code lên GitHub**.

---

## 🛠 1. Chuẩn Bị Môi Trường
Trước khi thiết lập CI/CD, cần đảm bảo rằng **SSH Server** hoạt động bình thường.

### ✅ Yêu Cầu
- **Server SSH** đang chạy (Ubuntu, macOS, CentOS, v.v.).
- **SSH Key-based Authentication** (không dùng mật khẩu).
- **Git được cài đặt trên server** (`git pull` hoạt động bình thường).
- **Dịch vụ (service) có thể restart** (`systemctl restart myapp` hoặc `docker restart`).

### 📌 Kiểm tra SSH Server trên Server
```sh
sudo systemctl status ssh
```
Nếu chưa bật, hãy chạy:
```sh
sudo systemctl enable --now ssh
```
Hoặc trên macOS:
```sh
sudo systemsetup -setremotelogin on
```

---

## 🛠 2. Tạo SSH Key trên Máy Local
Chạy lệnh sau trên **máy cá nhân (local machine)**:
```sh
ssh-keygen -t rsa -b 4096 -C "your-email@example.com"
```
✅ Kết quả:
- **Private Key**: `~/.ssh/id_rsa` (**Dùng trong GitHub Actions**).
- **Public Key**: `~/.ssh/id_rsa.pub` (**Thêm vào server**).

---

## 🛠 3. Thêm Public Key vào Server
Chạy lệnh sau để copy Public Key vào server:
```sh
cat ~/.ssh/id_rsa.pub | ssh user@server-ip "mkdir -p ~/.ssh && cat >> ~/.ssh/authorized_keys"
```
Kiểm tra đăng nhập SSH **không cần mật khẩu**:
```sh
ssh user@server-ip
```
✅ Nếu SSH vào được **mà không cần mật khẩu**, bạn đã thiết lập đúng.

---

## 🛠 4. Thêm Private Key vào GitHub Secrets
Để **GitHub Actions** có thể SSH vào server, bạn cần lưu **Private Key (`id_rsa`)** vào GitHub Secrets.

1. **Vào GitHub → Repository của bạn → Settings → Secrets**.
2. Chọn **New repository secret**.
3. **Tên:** `SSH_PRIVATE_KEY`
4. **Giá trị:** Dán nội dung của **id_rsa** (`cat ~/.ssh/id_rsa`).

---

## 🛠 5. Cấu Hình GitHub Actions để CI/CD
Tạo file `.github/workflows/ci.yml` trong repository.

```yaml
name: CI/CD Pipeline

on:
  push:
    branches:
      - main  # Chạy khi push lên nhánh main

jobs:
  deploy:
    runs-on: ubuntu-latest

    steps:
      - name: Checkout repository
        uses: actions/checkout@v3

      - name: Setup SSH
        run: |
          mkdir -p ~/.ssh
          echo "${{ secrets.SSH_PRIVATE_KEY }}" > ~/.ssh/id_rsa
          chmod 600 ~/.ssh/id_rsa
          ssh-keyscan -H your-server-ip >> ~/.ssh/known_hosts

      - name: Deploy to Server
        run: |
          ssh user@your-server-ip "
          cd /path/to/app &&
          git pull origin main &&
          systemctl restart myapp"
```

---

## 🛠 6. Kiểm Tra & Chạy CI/CD
1. **Push code lên GitHub**
   ```sh
   git add .
   git commit -m "Thêm CI/CD với SSH"
   git push origin main
   ```
2. **Kiểm tra GitHub Actions**:
   - Vào **GitHub → Repository → Actions**.
   - Nếu thành công, code **đã được deploy lên server**.

---

## 🛠 7. Tích Hợp Test & Build (CI)
Nếu bạn muốn kiểm tra code trước khi deploy, hãy thêm các bước sau vào `ci.yml`:

```yaml
      - name: Run Tests
        run: |
          pytest
```
Hoặc nếu bạn build ứng dụng trước khi deploy:
```yaml
      - name: Build Application
        run: |
          make build
```

---

## 🛠 8. Restart Dịch Vụ Sau Khi Deploy
Nếu ứng dụng của bạn chạy bằng **Docker**, thay vì `systemctl restart`, hãy dùng:
```yaml
      - name: Restart Docker Container
        run: |
          ssh user@your-server-ip "
          cd /path/to/app &&
          git pull origin main &&
          docker-compose down &&
          docker-compose up -d"
```

---

## 📖 Tóm Tắt Các Bước
| **Bước** | **Mô tả** |
|----------|----------|
| **1. Kiểm tra SSH Server** | `sudo systemctl status ssh` |
| **2. Tạo SSH Key trên local** | `ssh-keygen -t rsa -b 4096` |
| **3. Thêm Public Key vào server** | `cat ~/.ssh/id_rsa.pub >> ~/.ssh/authorized_keys` |
| **4. Thêm Private Key vào GitHub Secrets** | `SSH_PRIVATE_KEY` |
| **5. Viết GitHub Actions Workflow** | `.github/workflows/ci.yml` |
| **6. Push code lên GitHub để chạy CI/CD** | `git push origin main` |
| **7. Kiểm tra Actions trên GitHub** | GitHub Actions Logs |
| **8. Mở rộng: Thêm bước Build & Test** | `pytest` hoặc `make build` |

✅ **Sau khi hoàn thành, GitHub Actions sẽ tự động pull code mới nhất và deploy lên server khi bạn push code.** 🚀
