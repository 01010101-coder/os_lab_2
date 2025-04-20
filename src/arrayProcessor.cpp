#include "../include/arrayProcessor.h"
#include <algorithm>
#include <numeric>
#include <iostream>
#include <cmath>
#include <iomanip>
#include <thread>
#include <mutex>

std::mutex ArrayProcessor::console_mutex;

ArrayProcessor::ThreadResults ArrayProcessor::results;

void ArrayProcessor::ValidateArray(const std::vector<int>& arr) {
    if (arr.empty()) {
        throw std::runtime_error("Operation on empty array");
    }
}

void ArrayProcessor::FindMinMaxThread(const std::vector<int>& arr) {
    int min = arr[0], max = arr[0];

    for (int num : arr) {
        if (num < min) min = num;
        if (num > max) max = num;
        std::this_thread::sleep_for(std::chrono::milliseconds(kMinMaxSleepMs));
    }

    {
        std::lock_guard<std::mutex> lock(console_mutex);
        std::cout << "Min: " << min << "\nMax: " << max << std::endl;
    }

    results.min = min;
    results.max = max;
}

void ArrayProcessor::CalculateAverageThread(const std::vector<int>& arr) {
    double sum = 0;

    for (int num : arr) {
        sum += num;
        std::this_thread::sleep_for(std::chrono::milliseconds(kAverageSleepMs));
    }

    double average = sum / arr.size();
    int roundedAverage = static_cast<int>(std::round(average));

    {
        std::lock_guard<std::mutex> lock(console_mutex);
        std::cout << "Average: " << std::fixed << std::setprecision(2) << average
                  << " (rounded to " << roundedAverage << ")" << std::endl;
    }

    results.average = roundedAverage;
}

void ArrayProcessor::ProcessArray(std::vector<int>& arr) {
    ValidateArray(arr);

    // Create threads for min/max and average calculations
    std::thread minMaxThread(FindMinMaxThread, std::ref(arr));
    std::thread averageThread(CalculateAverageThread, std::ref(arr));

    // Wait for threads to finish
    minMaxThread.join();
    averageThread.join();

    // Modify the array by replacing min and max with the average
    for (int& num : arr) {
        if (num == results.min || num == results.max) {
            num = results.average;
        }
    }
}
