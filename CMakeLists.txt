# Dòng này xác định phiên bản CMake tối thiểu cần thiết để xây dựng dự án
# Phiên bản 3.10 hoặc cao hơn là cần thiết để hỗ trợ các tính năng CMake hiện đại và C++17
# Nếu không có dòng này, việc biên dịch có thể thất bại trên các phiên bản CMake cũ 
# không có các chức năng cần thiết
cmake_minimum_required(VERSION 3.10)

# Tên dự án
# Khai báo tên dự án là "main", với phiên bản 1.0 và ngôn ngữ được sử dụng là C++
project(main VERSION 1.0 LANGUAGES CXX)

# Thay đổi từ C++11 thành C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Yêu cầu bắt buộc phải sử dụng C++17, nếu không có sẽ báo lỗi
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Xác định hệ điều hành
if(APPLE)
    message(STATUS "Compiling on macOS 🎯")
    set(CMAKE_SYSTEM_NAME Darwin)
    set(CMAKE_OSX_DEPLOYMENT_TARGET "11.0")  # Hỗ trợ từ macOS 11 trở lên
    set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic")
    
    # Thiết lập kiến trúc Universal (Intel + Apple Silicon)
    set(CMAKE_OSX_ARCHITECTURES "x86_64;arm64")
    
    # RPATH để tránh lỗi thiếu thư viện khi chạy app
    set(CMAKE_INSTALL_RPATH "@loader_path/../lib")
endif()

# Thêm đường dẫn đến thư mục Header để compiler có thể tìm thấy các file header
include_directories(Header)

# Tạo file thực thi có tên là MyExecutable từ các file nguồn:
# - main.cpp (file chính)
# - std_unique_ptr.cpp (trong thư mục SourcesFile)
# - virtual_destructor.cpp (trong thư mục SourcesFile)
add_executable(MyExecutable 
    main.cpp 
    SourcesFile/std_unique_ptr.cpp 
    SourcesFile/virtual_destructor.cpp
)

# Chỉ định thư mục output cho file thực thi
# ${CMAKE_BINARY_DIR} là đường dẫn đến thư mục build
# File thực thi sẽ được tạo trong thư mục build/bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)