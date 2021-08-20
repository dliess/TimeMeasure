#ifndef OUTPUTTER_DESTINATIONS_ZMQ_H
#define OUTPUTTER_DESTINATIONS_ZMQ_H

#include <iostream>
#include <zmq.hpp>
#include <string.h>

namespace TimeMeasure
{

namespace Destination
{


class Zmq
{
public:
    Zmq() :
        m_socket(m_context, zmq::socket_type::pub)
    {
    }
    bool bind(const std::string& bindAddr)
    {
        m_socket.bind(bindAddr);
        return true;
    }
    void send(const std::string& msg)
    {    
        m_socket.send(zmq::str_buffer("data"), zmq::send_flags::sndmore);
        m_socket.send(zmq::const_buffer(msg.data(), msg.size()));
    }
private:
    zmq::context_t m_context;
    zmq::socket_t m_socket;
};

} // namespace Destination
} // namespace TimeMeasure

#endif