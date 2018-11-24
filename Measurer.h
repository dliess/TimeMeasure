#ifndef MEASURER_H
#define MEASURER_H

#include <chrono>

namespace TimeMeasure
{

template<unsigned int Id, class DataHolder>
class Measurer
{
public:
    static Measurer& instance();
    void reset();
    void sample();
    Measurer(const Measurer&) = delete;
    Measurer& operator=(const Measurer&) = delete;
    DataHolder& dataHolder();
    class Guard
    {
    public:
        Guard() { Measurer::instance().reset();
                  Measurer::instance().sample(); }
        ~Guard() { Measurer::instance().sample(); }
        Guard(const Guard&) = delete;
        Guard& operator=(const Guard&) = delete;
    };
private:
    Measurer();
    std::chrono::time_point<std::chrono::steady_clock> m_lastTimePoint;
    bool m_firstCall; 
    DataHolder m_dataHolder;
};

template<unsigned int Id, class DataHolder>
Measurer<Id, DataHolder>& Measurer<Id, DataHolder>::instance()
{
    static Measurer<Id, DataHolder> instance;
    return instance;
}

template<unsigned int Id, class DataHolder>
Measurer<Id, DataHolder>::Measurer() :
    m_lastTimePoint(),
    m_firstCall(true),
    m_dataHolder(Id)
{
}

template<unsigned int Id, class DataHolder>
void Measurer<Id, DataHolder>::reset()
{
    m_firstCall = true;
}

template<unsigned int Id, class DataHolder>
void Measurer<Id, DataHolder>::sample()
{
    if(m_firstCall)
    {
        m_firstCall = false;
        m_lastTimePoint = std::chrono::steady_clock::now();
        return;
    }
    const auto now = std::chrono::steady_clock::now();
    const auto diff = now - m_lastTimePoint;
    m_lastTimePoint = now;
    m_dataHolder.insert(std::chrono::duration_cast<typename DataHolder::SamplePeriod>(diff).count());
}

template<unsigned int Id, class DataHolder>
DataHolder& Measurer<Id, DataHolder>::dataHolder()
{
    return m_dataHolder;
}


} // namespace TimeMeasure

#endif