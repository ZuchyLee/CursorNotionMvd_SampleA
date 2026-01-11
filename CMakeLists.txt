cmake_minimum_required(VERSION 3.16)

project(ProjectA LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# CommonModule (git submodule)
set(COMMON_MODULE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external/CursorNotionMvd_CommonModule")

add_subdirectory("${COMMON_MODULE_DIR}")

# --- Demo 1: ✅ 合規範例（透過 VehicleFactory 建立車輛） ---
add_executable(CarDemo_Good
    apps/car_demo_good/main.cpp
)
target_include_directories(CarDemo_Good PRIVATE
    "${COMMON_MODULE_DIR}/include"
)
target_link_libraries(CarDemo_Good PRIVATE AutomotiveCore)

# --- Demo 2: ❌ 故意違規範例（用於 Cursor + Notion Code Review 展示） ---
# 注意：此範例「刻意」違反 CommonModule 的使用規範：
# - 引用 external/.../src 內部檔案
# - 直接實例化實作類別（CarImpl / ElectricEngine）
add_executable(CarDemo_Bad
    apps/car_demo_bad/main.cpp
)
target_include_directories(CarDemo_Bad PRIVATE
    "${COMMON_MODULE_DIR}/include"
)

