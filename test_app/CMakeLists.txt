cmake_minimum_required(VERSION 3.8)

project(test_librsync_project)
add_executable(test_librsync_project main.cpp)

target_include_directories(test_librsync_project PUBLIC ../src)
target_link_libraries(test_librsync_project ../build_dir/Debug/rsync)
