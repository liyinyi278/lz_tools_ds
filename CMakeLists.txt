cmake_minimum_required(VERSION 3.12...3.28 FATAL_ERROR)

# 项目配置
project(
    vscode-config-template
    VERSION 1.0
    LANGUAGES C CXX
)

# C++标准配置
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# C标准配置
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

#源文件收集（可选：替换为显式列表）
file(GLOB_RECURSE SOURCES
    "src/*.cpp"
    "src/*.c"
)

# 源文件收集（显式列表）
# set(SOURCES
#     "src/main.cpp"
# )

# 目标名称
set(TARGET_NAME ${PROJECT_NAME})
# 二进制目录
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
# 设置可执行文件输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
# 如果有动态库，可设置：
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# 编译选项：默认构建类型（Debug）
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Build type (Debug/Release)" FORCE)
endif()

# 生成可执行文件
add_executable(${TARGET_NAME} ${SOURCES})
target_include_directories(${TARGET_NAME} PRIVATE include)

# 编译警告配置（关键补充）
# target_compile_options(${TARGET_NAME} PRIVATE
#     # GCC/Clang 警告
#     $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-Wall -Wextra -Wpedantic>
#     # MSVC 警告
#     $<$<CXX_COMPILER_ID:MSVC>:/W4 >
#     # C编译器警告（与C++规则一致，可合并）
#     $<$<OR:$<C_COMPILER_ID:GNU>,$<C_COMPILER_ID:Clang>>:-Wall -Wextra -Wpedantic>
#     $<$<C_COMPILER_ID:MSVC>:/W4 >
# )





