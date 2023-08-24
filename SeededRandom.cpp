#include "SeededRandom.h"

#include <cmath>
#include <algorithm>

double SeededRandom::NextDouble() {
    const long long new_seed = 16807 * currentSeed;
    ++useCount;
    currentSeed = new_seed % 0x7FFFFFFF;
    return static_cast<double>(currentSeed) / 2147483646.0;
}


float SeededRandom::get_Value() {
	const long long new_seed = 16807 * currentSeed;
    ++useCount;
    currentSeed = new_seed % 0x7FFFFFFF;
    return static_cast<float>(static_cast<double>(currentSeed) * 4.6566129e-10);
}

float SeededRandom::NextNormal() {
    const long long multiplied_seed = 16807 * currentSeed;
    useCount += 2;
    const long long remainder = multiplied_seed % 0x7FFFFFFF;
    const float normalized_value = static_cast<float>(remainder) * 4.6566129e-10f;
    currentSeed = 16807 * remainder % 0x7FFFFFFF;
    const double scaled_value = static_cast<double>(normalized_value) * -2.0;
    const double random_value = (scaled_value < 0.0) ? static_cast<double>(normalized_value) * -2.0 : sqrt(scaled_value);
    const auto scaled_random_value = static_cast<float>(random_value * NextDouble());
    const auto normalized_result = static_cast<float>(static_cast<double>(scaled_random_value) * 0.125 + 0.5);
    return std::clamp(normalized_result, 0.0f, 1.0f);
}

int SeededRandom::Next() {
    long long new_seed = 16807 * currentSeed;
    ++useCount;
    new_seed %= 0x7FFFFFFFUL;
    currentSeed = new_seed;
    return static_cast<int>(new_seed);
}


int SeededRandom::NormalRange(const int min, const int max) {
    return static_cast<int>(static_cast<float>(max - min) * NextNormal()) + min;
}


float SeededRandom::NormalRange_Float(const float min, const float max) {
    return (max - min) * NextNormal() + min;
}


int SeededRandom::Range(const int min, const int max) {
    int lower_bound = min;
    int upper_bound = max;
    if (min > max) {
        std::swap(lower_bound, upper_bound);
    }
    if (lower_bound == upper_bound) {
        return lower_bound;
    }
    ++useCount;
    const long long multiplied_seed = 16807 * currentSeed;
    const long long remainder = multiplied_seed % 0x7FFFFFFF;
    currentSeed = remainder;
    return lower_bound + static_cast<int>(remainder) % (upper_bound - lower_bound);
}

float SeededRandom::Range_Float(float min, float max) {
    if (min > max) {
        std::swap(min, max);
    }
    const long long multiplied_seed = 16807 * currentSeed;
    ++useCount;
    currentSeed = multiplied_seed % 0x7FFFFFFF;
    const auto normalized_value = static_cast<float>(static_cast<double>(currentSeed) * 4.6566129e-10);
    return normalized_value * (max - min) + min;
}


void SeededRandom::ReportUseCount() {
    printf("Random has been used %i times since last set seed.", useCount);
}


void SeededRandom::SetSeed(const unsigned int seed) {
    if (reportUsecountFlag)
        ReportUseCount();

    useCount = 0;
    initialSeed = seed;
    currentSeed = seed;
}


void SeededRandom::SetSeed_Long(const long long seed) {
    if (reportUsecountFlag)
        ReportUseCount();

    useCount = 0;
    const long long absolute_value = abs(seed);
    initialSeed = absolute_value;
    currentSeed = absolute_value;
}


void SeededRandom::ctor(const long long seed) {
    long long check = -seed;
    if (seed >= 1)
        check = seed;

    initialSeed = check;
    currentSeed = check;
}


void SeededRandom::ctor_Int(const int seed) {
    ctor(seed);
}


int SeededRandom::sign() {
	const int64_t new_seed = 16807 * currentSeed;
    ++useCount;
    currentSeed = new_seed % 0x7FFFFFFF;
    if (static_cast<double>(currentSeed) * 4.6566129e-10 >= 0.5)
        return -1;
    return 1;
}
