#include "Measurer.h"
#include "CyclicDataOutputterThread.h"
#include <fstream>
#include <vector>
#include "Histogram.h"

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
    MyMeasurerMs<0>::instance().dataHolder().setHistogramRange(20);
    MyMeasurerUs<1>::instance().dataHolder().setHistogramRange(100);
    MyMeasurerUs<2>::instance().dataHolder().setHistogramRange(100);
    MyMeasurerUs<3>::instance().dataHolder().setHistogramRange(100);


    /*
     *   Setup all the outputters
     */
    CyclicDataOutputterThread< DataHolderUs, Destination::StdOut >
    outThreadStdOut({ &MyMeasurerUs<2>::instance().dataHolder(),
                      &MyMeasurerUs<3>::instance().dataHolder() });
    outThreadStdOut.startThread(100);

    CyclicDataOutputterThread< DataHolderMs, Destination::File >
    outThreadFile({ &MyMeasurerMs<0>::instance().dataHolder() });
    if(!outThreadFile.destination().open("dumpFile"))
    {
        exit(1);
    }
    outThreadFile.startThread(100);

    CyclicDataOutputterThread< DataHolderUs, Destination::Udp >
    outThreadUdp({  &MyMeasurerUs<1>::instance().dataHolder(),
                    &MyMeasurerUs<2>::instance().dataHolder(),
                    &MyMeasurerUs<3>::instance().dataHolder() });
    if(!outThreadUdp.destination().connect("127.0.0.1", 12341))
    {
        exit(1);
    }
    outThreadUdp.startThread(100);


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