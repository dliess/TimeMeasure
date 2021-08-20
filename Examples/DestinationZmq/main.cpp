#include "Measurer.h"
#include "Histogram.h"
#include "OutputterDestinationsZmq.h"
#include "CyclicDataOutputterThread.h"
#include <fstream>
#include <vector>

using namespace TimeMeasure;

using DataHolderUs = Histogram<std::chrono::microseconds>;
using DataHolderMs = Histogram<std::chrono::milliseconds>;

template<unsigned int Id>
using MyMeasurerUs = Measurer<Id, DataHolderUs>;

template<unsigned int Id>
using MyMeasurerMs = Measurer<Id, DataHolderMs>;

int main()
{
    /*
     *   Setup all the data-holders(histograms in this case)
     */
    MyMeasurerUs<0>::instance().dataHolder().setHistogramRange(100);
    MyMeasurerUs<1>::instance().dataHolder().setHistogramRange(100);
    MyMeasurerUs<2>::instance().dataHolder().setHistogramRange(100);
    MyMeasurerUs<3>::instance().dataHolder().setHistogramRange(100);

    CyclicDataOutputterThread< DataHolderUs, Destination::Zmq >
    outThreadZmq({  &MyMeasurerUs<0>::instance().dataHolder(),
                    &MyMeasurerUs<1>::instance().dataHolder(),
                    &MyMeasurerUs<2>::instance().dataHolder(),
                    &MyMeasurerUs<3>::instance().dataHolder() });
    if(!outThreadZmq.destination().bind("tcp://127.0.0.1:12341"))
    {
        exit(1);
    }
    outThreadZmq.startThread(1000);


    /*
     *   Do the measurings
     */
    while(true)
    {
        MyMeasurerMs<0>::instance().sample();
        std::ofstream ofs;
        {
            MyMeasurerUs<1>::Guard measure;
            ofs.open("test.txt", std::ofstream::out | std::ofstream::trunc);
        }
        {
            MyMeasurerUs<2>::Guard measure;
            ofs << "Some dummy text";
        }
        {
            MyMeasurerUs<3>::Guard measure;
            ofs.close();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    return 0;
}