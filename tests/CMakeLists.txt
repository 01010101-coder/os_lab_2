add_executable(UnitTests test_arrayProcessor.cpp)
target_include_directories(UnitTests PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(UnitTests PRIVATE arrayProcessor gtest_main)

add_test(NAME ArrayProcessorTests COMMAND UnitTests)