cmake_minimum_required(VERSION 3.10)
project(dproton)


add_executable(${PROJECT_NAME} main.c read_write.c)

target_link_libraries(${PROJECT_NAME} m)
