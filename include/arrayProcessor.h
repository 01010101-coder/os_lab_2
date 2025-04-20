#pragma once
#include <vector>
#include <stdexcept>
#include <string>
#include <mutex>
#include <cmath>
#include <iomanip>
#include <thread>

class ArrayProcessor {
public:
    static constexpr int kMinMaxSleepMs = 7;
    static constexpr int kAverageSleepMs = 12;

    class EmptyArrayException : public std::runtime_error {
    public:
        EmptyArrayException() : runtime_error("Operation on empty array") {}
    };

    class InvalidInputException : public std::runtime_error {
    public:
        InvalidInputException(const std::string& message) : runtime_error(message) {}
    };

    static void FindMinMaxThread(const std::vector<int>& arr);
    static void CalculateAverageThread(const std::vector<int>& arr);

    static void ProcessArray(std::vector<int>& arr);

private:
    static void ValidateArray(const std::vector<int>& arr);

    static std::mutex console_mutex;

    struct ThreadResults {
        int min = 0;
        int max = 0;
        int average = 0;
    };

    static ThreadResults results;
};
