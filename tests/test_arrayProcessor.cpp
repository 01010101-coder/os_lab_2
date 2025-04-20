#include <gtest/gtest.h>
#include "../include/arrayProcessor.h"
#include <vector>
#include <iostream>
#include <limits>

TEST(ArrayProcessorTest, HandlesEmptyArray) {
    std::vector<int> empty;
    EXPECT_THROW(ArrayProcessor::ProcessArray(empty), ArrayProcessor::EmptyArrayException);
}

TEST(ArrayProcessorTest, HandlesSingleElement) {
std::vector<int> arr = { 42 };
    EXPECT_NO_THROW(ArrayProcessor::ProcessArray(arr));
    EXPECT_EQ(arr[0], 42);
}

TEST(ArrayProcessorTest, HandlesNegativeNumbers) {
    std::vector<int> arr = { -5, 3, -7 };
    EXPECT_NO_THROW(ArrayProcessor::ProcessArray(arr));
    EXPECT_EQ(arr, std::vector<int>({ -5, -3, -3 }));
}

TEST(ArrayProcessorTest, HandlesLargeArray) {
    std::vector<int> arr(1500, 5);
    EXPECT_NO_THROW(ArrayProcessor::ProcessArray(arr));
    EXPECT_EQ(arr, std::vector<int>(1500, 5));
}