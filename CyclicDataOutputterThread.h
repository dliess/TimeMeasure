#ifndef CYCLIC_DATA_OUTPUTTER_THREAD_H
#define CYCLIC_DATA_OUTPUTTER_THREAD_H

#include <vector>
#include <thread>
#include <iostream>
#include "OutputterDestinations.h"

namespace TimeMeasure
{

template<class DataHolder, class Dest = Destination::StdOut>
class CyclicDataOutputterThread
{
public:
    CyclicDataOutputterThread(std::vector< const DataHolder* >&& v);
    CyclicDataOutputterThread(CyclicDataOutputterThread&& other);
    CyclicDataOutputterThread(const CyclicDataOutputterThread& other) = delete;
    CyclicDataOutputterThread& operator=(CyclicDataOutputterThread&& other);
    ~CyclicDataOutputterThread();
    void startThread(unsigned int periodMs);
    Dest& destination();
private:
    std::vector< const DataHolder* > m_dataHolders;
    std::thread m_thread;
    static void threadHelper(CyclicDataOutputterThread* pObj){pObj->threadFn();};
    void threadFn();
    bool m_running{true};
    unsigned int m_periodMs{1000};
    Dest m_destination;
};

template<class DataHolder, class Dest>
CyclicDataOutputterThread<DataHolder, Dest>::CyclicDataOutputterThread(std::vector< const DataHolder* >&& v) : 
    m_dataHolders(std::move(v)),
    m_thread()
{
}

template<class DataHolder, class Dest>
CyclicDataOutputterThread<DataHolder, Dest>::CyclicDataOutputterThread(CyclicDataOutputterThread&& other) :
    m_dataHolders(std::move(other.m_dataHolders)),
    m_thread(std::move(other.m_thread)),
    m_running(other.m_running)
{}

template<class DataHolder, class Dest>
CyclicDataOutputterThread<DataHolder, Dest>& CyclicDataOutputterThread<DataHolder, Dest>::operator=(CyclicDataOutputterThread&& other)
{
    m_dataHolders = std::move(other.m_dataHolders);
    m_thread = std::move(other.m_thread);
    m_running = other.m_running;
    return *this;
}

template<class DataHolder, class Dest>
CyclicDataOutputterThread<DataHolder, Dest>::~CyclicDataOutputterThread()
{
    m_running = false;
    m_thread.join();
}

template<class DataHolder, class Dest>
void CyclicDataOutputterThread<DataHolder, Dest>::startThread(unsigned int periodMs)
{
    m_periodMs = periodMs;
    m_thread = std::thread(threadHelper, this);
}

template<class DataHolder, class Dest>
Dest& CyclicDataOutputterThread<DataHolder, Dest>::destination()
{
    return m_destination;
}

template<class DataHolder, class Dest>
void CyclicDataOutputterThread<DataHolder, Dest>::threadFn()
{
    while(m_running)
    {
        for(auto p : m_dataHolders)
        {
            m_destination.send(p->toGnuplotString());
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(m_periodMs));
    }
}

} // namespace TimeMeasure

#endif