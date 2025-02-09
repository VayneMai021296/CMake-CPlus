cmake_minimum_required(VERSION 3.10)

# Tên dự án
project(main VERSION 1.0 LANGUAGES CXX)

# Định nghĩa tiêu chuẩn C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Thêm thư mục chứa file header
include_directories(Header)

# Thêm tệp nguồn và tạo executable
add_executable(MyExecutable 
    main.cpp 
    SourcesFile/std_unique_ptr.cpp 
    SourcesFile/virtual_destructor.cpp
)

# Đặt thư mục output
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)