#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include <cstdint>
#include <vector>
#include <string>
#include <sstream>

namespace TimeMeasure
{

template< class Period >
class Histogram
{
public:
    Histogram(unsigned int id);
    ~Histogram();
    Histogram& setHistogramRange(unsigned int range);
    void insert(uint32_t element);
    std::string toGnuplotString() const;
    using SamplePeriod = Period;
private:
    unsigned int m_id;
    unsigned int m_range;
    std::vector<uint32_t> m_histogramData;
    uint32_t              m_rest;
};

template< class Period >
Histogram<Period>::Histogram(unsigned int id) :
    m_id(id),
    m_range(0),
    m_rest(0)
{
}

template< class Period >
Histogram<Period>& Histogram<Period>::setHistogramRange(unsigned int range)
{
    m_range = range;
    m_histogramData.resize(range, 0);
    return *this;
}

template< class Period >
Histogram<Period>::~Histogram()
{
}


template< class Period >
void Histogram<Period>::insert(uint32_t element)
{
    if(element < m_range)
    {
       m_histogramData[element]++;
    }
    else
    {
        m_rest++;
    }
}

template< class Period >
std::string Histogram<Period>::toGnuplotString() const
{
    std::stringstream ss;
    for(unsigned int i = 0; i < m_range; ++i)
    {
        if(m_histogramData[i] != 0)
        {
            ss << i << ", " << m_id << ", " << m_histogramData[i] << std::endl;
        }
    }
    ss << m_range << ", " << m_id << ", " << m_rest << std::endl;
    return ss.str();
}

} // namespace TimeMeasure

#endif