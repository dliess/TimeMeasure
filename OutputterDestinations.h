#ifndef OUTPUTTER_DESTINATIONS_H
#define OUTPUTTER_DESTINATIONS_H

#include <iostream>

//File
#include <fstream>

//Udp
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h> // close()

namespace TimeMeasure
{

namespace Destination
{

class StdOut
{
public:
    void send(const std::string& msg)
    {
        std::cout << msg << std::flush;
    }
};

class File
{
public:
    ~File()
    {
        m_ofs.close();
    }
    bool open(const std::string filename)
    {
        m_ofs.open(filename, std::ofstream::out | std::ofstream::trunc);
        return m_ofs.is_open();
    }
    void send(const std::string& msg)
    {
        m_ofs << msg << std::flush;
    }
private:
    std::ofstream m_ofs;
};

class Udp
{
public:
    ~Udp() 
    {
        freeaddrinfo(m_addrinfo);
        close(m_socket);
    }
    bool connect(const std::string& addr, int port)
    {
        char decimal_port[16];
        snprintf(decimal_port, sizeof(decimal_port), "%d", port);
        decimal_port[sizeof(decimal_port) / sizeof(decimal_port[0]) - 1] = '\0';
        struct addrinfo hints;
        memset(&hints, 0, sizeof(hints));
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_DGRAM;
        hints.ai_protocol = IPPROTO_UDP;
        int r(getaddrinfo(addr.c_str(), decimal_port, &hints, &m_addrinfo));
        if(r != 0 || m_addrinfo == NULL)
        {
            std::cerr << "invalid address or port: \"" << addr << ":" << decimal_port << "\"";
            return false;
        }
        m_socket = socket(m_addrinfo->ai_family, SOCK_DGRAM | SOCK_CLOEXEC, IPPROTO_UDP);
        if(m_socket == -1)
        {
            freeaddrinfo(m_addrinfo);
            std::cerr << "could not create socket for: \"" << addr << ":" << decimal_port << "\"";
            return false;
        }
       int broadcastEnable = 1;
       int ret = setsockopt(m_socket, SOL_SOCKET, SO_BROADCAST, &broadcastEnable, sizeof(broadcastEnable));
       if(ret == -1)
       {
           std::cerr << "setsockopt failed: " << strerror(errno) << "\n";
           return false;
       }
       return true;
    }
    void send(const std::string& msg)
    {
        sendto(m_socket, msg.c_str(), msg.length(), 0, m_addrinfo->ai_addr, m_addrinfo->ai_addrlen);
    }
private:
    int                 m_socket;
    struct addrinfo *   m_addrinfo;
};

} // namespace Destination
} // namespace TimeMeasure

#endif