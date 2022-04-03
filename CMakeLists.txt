cmake_minimum_required(VERSION 3.23)
project(sspice)

set(CMAKE_C_FLAGS "-std=c99")

include_directories("./include")

#add_library(server SHARED src/serverListener.c)
#add_library(simulator SHARED src/ngspiceSim.c)

FILE(GLOB csources src/*.c)
add_executable(${PROJECT_NAME} ${csources}) 
target_compile_definitions(${PROJECT_NAME} PRIVATE)
target_link_libraries(${PROJECT_NAME} ngspice)