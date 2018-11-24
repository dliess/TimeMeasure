# TimeMeasure

# This header-only library provides easy to use time-interval histogram creation and streaming to varios destinations(StdOut, File, Udp)

# Types
* Measurer:
    Every measurer is a class-type by its own and is used as a singleton.
    It is defined by an Id and the DataHolder type.
    It is used to measure the time-duration between two
    time-points by its "sample() call".
* DataHolder:
    The Object where the measured data gets feed in(e.g. a Histogram). It has a one-to-one relation with the Measurer.
* CyclicDataOutputterThread:
    A Thread to output the DataHolders data in an asynchronous manner. The destination can be determined by a template parameter.

#Usage
* Setup DataHolder(at this time only Histograms are implemented) of the Measurers that will be used. For simplicity we will use a typedef for the Histogram class

using HistogramUs = Histogram< std::chrono::microseconds >;

TimeMeasure::Measurer< 0, HistogramUs >::instance().setHistogramRange(200);

* Create and setup Outputter-Thread object
CyclicDataOutputterThread< HistogramUs, Destination::StdOut/File/Udp > outThread(TimeMeasure::Measurer< 0, HistogramUs >::instance().dataHolder());
outThread.destination().connect("ip", port);
outThread.startThread(output-period in ms)

* Instrument your code with the measuring points
** Interal measure with the Guard object
{
    TimeMeasure::Measurer< 0, HistogramUs >::Guard guard;
    // Stuff you want to measure
}
** Repetition period measure 
TimeMeasure::Measurer< 0, HistogramUs >::instance().sample()

# Visualization with feedgnuplot

## for Destination:StdOut
./TimeMeasureExample | feedgnuplot ...

## for Destination:File
tail -f1 "dumpfile" | feedgnuplot ...

## for Destination:Udp
nc -u "ip" -k -p "port number" -l | feedgnuplot ...

## feedgnuplot options
feedgnuplot --domain --dataid --autolegend --stream  --curvestyleall 'with boxes fill solid 1.0' --extracmds 'set logscale y'

### to show in terminal add
--extracmds 'set terminal dumb'