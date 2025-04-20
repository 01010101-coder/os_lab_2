#include <gtest/gtest.h>
#include "../include/arrayProcessor.h"
#include <vector>
#include <iostream>
#include <limits>

TEST(ArrayProcessorTest, HandlesAllPositiveElements) {
std::vector<int> arr = { 10, 20, 30, 40, 50 };
EXPECT_NO_THROW(ArrayProcessor::ProcessArray(arr));
EXPECT_EQ(arr, std::vector<int>({ 30, 30, 30, 30, 30 }));
}

TEST(ArrayProcessorTest, HandlesSingleZeroElement) {
std::vector<int> arr = { 0 };
EXPECT_NO_THROW(ArrayProcessor::ProcessArray(arr));
EXPECT_EQ(arr[0], 0);
}

TEST(ArrayProcessorTest, HandlesLargeNegativeNumbers) {
std::vector<int> arr = { -1000, -500, -200, -100 };
EXPECT_NO_THROW(ArrayProcessor::ProcessArray(arr));
// Ожидаем, что все элементы будут заменены на среднее значение -450
EXPECT_EQ(arr, std::vector<int>({ -450, -450, -450, -450 }));
}

TEST(ArrayProcessorTest, HandlesMixOfSmallAndLargeValues) {
std::vector<int> arr = { 1, 1000000, -1000000, 50, -50 };
EXPECT_NO_THROW(ArrayProcessor::ProcessArray(arr));
// Среднее значение этих чисел близко к 0
EXPECT_EQ(arr, std::vector<int>({ 0, 0, 0, 0, 0 }));
}

TEST(ArrayProcessorTest, HandlesFloatingPointAverage) {
std::vector<int> arr = { 1, 2, 3, 4, 5 };
EXPECT_NO_THROW(ArrayProcessor::ProcessArray(arr));
EXPECT_EQ(arr, std::vector<int>({ 3, 3, 3, 3, 3 }));
}

TEST(ArrayProcessorTest, HandlesNonContiguousValues) {
std::vector<int> arr = { 1, 100, 1000, 10000 };
EXPECT_NO_THROW(ArrayProcessor::ProcessArray(arr));
// Среднее значение для этого массива: (1 + 100 + 1000 + 10000) / 4 = 2775.25
EXPECT_EQ(arr, std::vector<int>({ 2775, 2775, 2775, 2775 }));
}

TEST(ArrayProcessorTest, HandlesEmptyArrayAfterProcess) {
std::vector<int> arr = {};
// Ожидаем, что пустой массив вызовет исключение EmptyArrayException
EXPECT_THROW(ArrayProcessor::ProcessArray(arr), ArrayProcessor::EmptyArrayException);
}


TEST(ArrayProcessorTest, HandlesArrayWithIdenticalMaxAndMin) {
std::vector<int> arr = { 5, 5, 5, 5, 5 };
EXPECT_NO_THROW(ArrayProcessor::ProcessArray(arr));
EXPECT_EQ(arr, std::vector<int>({ 5, 5, 5, 5, 5 }));
}

TEST(ArrayProcessorTest, HandlesArrayWithOnlyOneUniqueMaxOrMin) {
std::vector<int> arr = { 1, 5, 10, 5, 5 };
EXPECT_NO_THROW(ArrayProcessor::ProcessArray(arr));
EXPECT_EQ(arr, std::vector<int>({ 5, 5, 5, 5, 5 }));
}

TEST(ArrayProcessorTest, HandlesLargeArrayWithExtremeValues) {
std::vector<int> arr(10000, 1000000);
EXPECT_NO_THROW(ArrayProcessor::ProcessArray(arr));
EXPECT_EQ(arr, std::vector<int>(10000, 1000000));  // Все элементы остаются одинаковыми
}
