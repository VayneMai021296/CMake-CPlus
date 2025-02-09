# Cplus with CMake, How to make configuration CI/CD with github Action on MacOS and WindowOS

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

# 🚀 Hướng Dẫn Thiết Lập SSH GitHub Actions Trên Windows

## 🔥 1. Cài đặt OpenSSH trên Windows
Windows 10/11 đã tích hợp **OpenSSH Server**, nhưng có thể cần kích hoạt.

### ✅ Kiểm tra OpenSSH đã cài đặt chưa
Mở **PowerShell (Administrator)** và chạy:
```powershell
Get-WindowsCapability -Online | Where-Object Name -like 'OpenSSH*'
```
Nếu kết quả hiển thị:
```
OpenSSH.Server~~~~0.0.1.0
OpenSSH.Client~~~~0.0.1.0
```
👉 **SSH đã được cài đặt**.

### 🛠 Cài đặt OpenSSH Server nếu chưa có
```powershell
Add-WindowsFeature -Name OpenSSH.Server
```
Sau đó, kiểm tra trạng thái SSH Server:
```powershell
Get-Service sshd
```
Nếu chưa chạy, hãy bật:
```powershell
Start-Service sshd
Set-Service -Name sshd -StartupType Automatic
```
✅ **Bây giờ Windows đã bật SSH Server!**

---

## 🔥 2. Kiểm tra Địa Chỉ IP của Windows
Chạy lệnh sau trong **PowerShell** để lấy IP:
```powershell
ipconfig
```
Ví dụ, Windows có IP **192.168.1.150**.

---

## 🔥 3. Tạo SSH Key trên Máy Local
Chạy lệnh sau trên **máy local** (Linux, Mac, hoặc Windows WSL):
```sh
ssh-keygen -t rsa -b 4096 -C "your-email@example.com"
```
✅ Kết quả:
- **Private Key**: `~/.ssh/id_rsa` (**Dùng trong GitHub Actions**).
- **Public Key**: `~/.ssh/id_rsa.pub` (**Thêm vào Windows Server**).

---

## 🔥 4. Thêm Public Key vào Windows Server
**Trên Windows**, mở **PowerShell** và chạy:
```powershell
New-Item -ItemType Directory -Path $env:USERPROFILE\.ssh -Force
```
Chạy tiếp:
```powershell
notepad $env:USERPROFILE\.ssh\authorized_keys
```
Dán nội dung của **id_rsa.pub** vào file này và lưu lại.

---

## 🔥 5. Thêm Private Key vào GitHub Secrets
1. Vào **GitHub → Repository của bạn → Settings → Secrets**.
2. Chọn **New repository secret**.
3. **Tên:** `SSH_PRIVATE_KEY`
4. **Giá trị:** Dán nội dung của **id_rsa** (`cat ~/.ssh/id_rsa` trên local).

---

## 🔥 6. Cấu Hình GitHub Actions Để Deploy Lên Windows
Tạo file `.github/workflows/ci.yml`:

```yaml
name: CI/CD Pipeline for Windows

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

      - name: Setup SSH for Windows
        run: |
          mkdir -p ~/.ssh
          echo "${{ secrets.SSH_PRIVATE_KEY }}" > ~/.ssh/id_rsa
          chmod 600 ~/.ssh/id_rsa
          ssh-keyscan -H 192.168.1.150 >> ~/.ssh/known_hosts

      - name: Deploy to Windows Server
        run: |
          ssh user@192.168.1.150 "
          cd C:/path/to/app &&
          git pull origin main &&
          net stop MyAppService &&
          net start MyAppService"
```
👉 **Giải thích:**
- **Setup SSH**: Thiết lập key và kết nối SSH từ GitHub Actions vào Windows.
- **Deploy to Windows**: SSH vào Windows và thực hiện:
  - `git pull` để cập nhật code.
  - `net stop` và `net start` để restart dịch vụ Windows.

---

## 🔥 7. Kiểm Tra Kết Nối SSH
Trên **local**, thử SSH vào Windows:
```sh
ssh user@192.168.1.150
```
✅ Nếu kết nối thành công mà **không cần nhập mật khẩu**, bạn đã thiết lập đúng.

---

## 🔥 8. Push Code Để Kiểm Tra CI/CD
1. **Push code lên GitHub**
   ```sh
   git add .
   git commit -m "Setup SSH deploy for Windows"
   git push origin main
   ```
2. **Kiểm tra GitHub Actions**:
   - Vào **GitHub → Actions**.
   - Nếu thành công, ứng dụng trên **Windows đã được cập nhật**.

---

## 📖 Tóm Tắt Các Bước
| **Bước** | **Mô tả** |
|----------|----------|
| **1. Cài OpenSSH trên Windows** | `Start-Service sshd` |
| **2. Kiểm tra IP của Windows** | `ipconfig` |
| **3. Tạo SSH Key trên local** | `ssh-keygen -t rsa -b 4096` |
| **4. Thêm Public Key vào Windows** | Dán vào `authorized_keys` |
| **5. Thêm Private Key vào GitHub Secrets** | `SSH_PRIVATE_KEY` |
| **6. Viết GitHub Actions Workflow** | `.github/workflows/ci.yml` |
| **7. Push code lên GitHub để chạy CI/CD** | `git push origin main` |
| **8. Kiểm tra Actions trên GitHub** | GitHub Actions Logs |

✅ **Sau khi hoàn thành, GitHub Actions sẽ tự động pull code mới nhất và deploy lên Windows khi bạn push code.** 🚀



