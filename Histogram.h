#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include <cstdint>
#include <vector>
#include <string>

namespace Analyze
{

template<class UserClass, unsigned int MaxRange>
class Histogram
{
public:
    Histogram();
    void insert(uint32_t element);
    std::string getName() const;
    std::string getCsv() const;
private:
    std::vector<uint32_t> m_histogram;
};

template<class UserClass, unsigned int MaxRange>
Histogram<UserClass, MaxRange>::Histogram()
{
    m_histogram.reserve(MaxRange+1);
}


template<class UserClass, unsigned int MaxRange>
void Histogram<UserClass, MaxRange>::insert(uint32_t element)
{
    if(element < MaxRange)
    {
       m_histogram[element]++;
    }
    else
    {
        m_histogram[MaxRange]++;
    }
}

template<class UserClass, unsigned int MaxRange>
std::string Histogram<UserClass, MaxRange>::getName() const
{

}

template<class UserClass, unsigned int MaxRange>
std::string Histogram<UserClass, MaxRange>::getCsv() const
{
    
}


} // namespace Analyze

#endif