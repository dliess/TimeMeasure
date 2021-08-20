#include <iostream>
#include <zmq.hpp>
#include <string_view>

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        std::cout << "Usage: appName <server-address>\n";
        return -1;
    }

    zmq::context_t context;
    zmq::socket_t socket(context, zmq::socket_type::sub);
    socket.connect(argv[1]);
    socket.set(zmq::sockopt::subscribe, "data");
    while(true)
    {
        zmq::message_t keyBuf;
        auto res = socket.recv(keyBuf);
        if (!res) { std::cerr << "No received topic\n"; return -1; }

        zmq::message_t msgBuf;
		auto res1 = socket.recv(msgBuf, zmq::recv_flags::none);
		if (!res1) { std::cerr << "No received message\n"; return -1; }
        std::cout << std::string(static_cast<const char*>(msgBuf.data()), msgBuf.size());
    }
    return 0;
}