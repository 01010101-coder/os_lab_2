add_library(arrayProcessor STATIC arrayProcessor.cpp)
target_include_directories(arrayProcessor PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_executable(os_lab_2 main.cpp)
target_link_libraries(os_lab_2 arrayProcessor)