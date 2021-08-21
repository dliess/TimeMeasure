#ifndef OUTPUTTER_DESTINATIONS_ZMQ_H
#define OUTPUTTER_DESTINATIONS_ZMQ_H

#include <iostream>
#include <zmq.hpp>
#include <string.h>
#include <memory>

namespace TimeMeasure
{

namespace Destination
{


class Zmq
{
public:
    void bind(const std::string& bindAddr)
    {
        m_pSocket = std::make_unique<zmq::socket_t>(m_context, zmq::socket_type::pub);
        m_pSocket->bind(bindAddr);
    }
    void send(const std::string& msg)
    {    
        m_pSocket->send(zmq::str_buffer("data"), zmq::send_flags::sndmore);
        m_pSocket->send(zmq::const_buffer(msg.data(), msg.size()));
    }
private:
    zmq::context_t m_context;
    std::unique_ptr<zmq::socket_t> m_pSocket;
};

} // namespace Destination
} // namespace TimeMeasure

#endif