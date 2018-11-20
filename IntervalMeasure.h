#ifndef INTERVAL_MEASURE_H
#define INTERVAL_MEASURE_H

#include <chrono>
#include "Histogram.h"

namespace Analyze
{

template<unsigned int I, unsigned int MaxRange>
class IntervalMeasure
{
public:
    IntervalMeasure();
    ~IntervalMeasure();
    static const Histogram< IntervalMeasure<I, MaxRange>, MaxRange >& getHistogram();
private:
    std::chrono::time_point<std::chrono::steady_clock> m_startTime;
    static Histogram< IntervalMeasure<I, MaxRange>, MaxRange > histogram;
};

template<unsigned int I, unsigned int MaxRange>
IntervalMeasure<I, MaxRange>::IntervalMeasure() :
    m_startTime(std::chrono::steady_clock::now())
{
}

template<unsigned int I, unsigned int MaxRange>
IntervalMeasure<I, MaxRange>::~IntervalMeasure()
{
    const auto diff = std::chrono::steady_clock::now() - m_startTime;
    const auto diffMs = std::chrono::duration_cast<std::chrono::milliseconds>(diff);
    histogram.insert(diffMs);
}

} // namespace Analyze

#endif