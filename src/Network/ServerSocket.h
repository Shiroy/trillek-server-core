#pragma once

#include "AbstractSocket.h"
#include "network"

namespace Trillek
{
namespace Network
{

class ServerSocket : public AbstractSocket
{
public:
    ServerSocket();
    ~ServerSocket() override;

    int getDescriptor() override;
    int HandleRead() override;
    int HandleWrite() override;
    int HandleExcept() override;

private:
    network::TCPConnection  m_server_socket;
};

}
}
