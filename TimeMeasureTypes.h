#ifndef TIME_MEASURE_TYPES_H
#define TIME_MEASURE_TYPES_H

#include "Measurer.h"
#include "Histogram.h"
#include "CyclicDataOutputterThread.h"
#include <chrono>

namespace TimeMeasure
{

using HistogramUs  = Histogram<std::chrono::microseconds>;
using HistogramMs  = Histogram<std::chrono::milliseconds>;
using HistogramSec = Histogram<std::chrono::seconds>;

template<unsigned int Id>
using Measurer2HistUs = Measurer<Id, HistogramUs>;
template<unsigned int Id>
using Measurer2HistMs = Measurer<Id, HistogramMs>;
template<unsigned int Id>
using Measurer2HistSec = Measurer<Id, HistogramSec>;

template<class Dest>
using HistUsOutThread = CyclicDataOutputterThread< HistogramUs, Dest >;
template<class Dest>
using HistMsOutThread = CyclicDataOutputterThread< HistogramMs, Dest >;
template<class Dest>
using HistSecOutThread = CyclicDataOutputterThread< HistogramSec, Dest >;

}

#endif