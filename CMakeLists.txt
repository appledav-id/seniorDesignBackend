cmake_minimum_required(VERSION 3.16)
project(sspice)

set(CMAKE_C_FLAGS "-std=c99")

include_directories("./include")

# old way of doing it, im trying a different way now to be more concise
#add_library(server SHARED src/serverListener.c)
#add_library(simulator SHARED src/ngspiceSim.c)

add_library(ngspice SHARED IMPORTED)
set_target_properties(ngspice PROPERTIES IMPORTED_LOCATION "/usr/local/lib/libngspice.so")

# group up all the c files
FILE(GLOB csources src/*.c)
add_executable(${PROJECT_NAME} ${csources}) 

target_compile_definitions(${PROJECT_NAME} PUBLIC)
target_link_libraries(${PROJECT_NAME} PUBLIC ngspice)
