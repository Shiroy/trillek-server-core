#pragma once

#include "network"
#include "AbstractSocket.h"

namespace Trillek
{
namespace Network
{

class ClientSocket : public AbstractSocket
{
public:
    ClientSocket(network::TCPConnection &&c);
    ~ClientSocket() override;

    int getDescriptor() override;
    int HandleRead() override;
    int HandleWrite() override;
    int HandleExcept() override;

private:
    network::TCPConnection &m_con;
};

}
}
