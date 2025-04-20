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
        throw EmptyArrayException(); // Throw exception if array is empty
    }
}

void ArrayProcessor::FindMinMaxThread(const std::vector<int>& arr) {
    int min = arr[0], max = arr[0];

    // Iterate through the array and calculate min/max values
    for (int num : arr) {
        if (num < min) min = num;
        if (num > max) max = num;
    }

    // Output min/max values
    {
        std::lock_guard<std::mutex> lock(console_mutex);
        std::cout << "Min: " << min << "\nMax: " << max << std::endl;
    }

    // Store results in the static results struct
    results.min = min;
    results.max = max;
}

void ArrayProcessor::CalculateAverageThread(const std::vector<int>& arr) {
    double sum = 0;

    // Calculate the sum of the array elements
    for (int num : arr) {
        sum += num;
    }

    // Calculate the average and round it
    double average = sum / arr.size();
    int roundedAverage = static_cast<int>(std::round(average));

    // Output the average and the rounded value
    {
        std::lock_guard<std::mutex> lock(console_mutex);
        std::cout << "Average: " << std::fixed << std::setprecision(2) << average
                  << " (rounded to " << roundedAverage << ")" << std::endl;
    }

    // Store the rounded average in the static results struct
    results.average = roundedAverage;
}

void ArrayProcessor::ProcessArray(std::vector<int>& arr) {
    ValidateArray(arr); // Ensure the array is not empty

    // Create threads for min/max and average calculations
    std::thread minMaxThread(FindMinMaxThread, std::ref(arr));
    std::thread averageThread(CalculateAverageThread, std::ref(arr));

    // Wait for threads to finish
    minMaxThread.join();
    averageThread.join();

    // Replace all array elements with the rounded average value
    for (int& num : arr) {
        num = results.average;
    }
}
