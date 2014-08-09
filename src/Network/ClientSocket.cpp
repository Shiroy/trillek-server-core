#include "ClientSocket.h"

namespace Trillek
{
namespace Network
{

ClientSocket::ClientSocket(network::TCPConnection &&c) : AbstractSocket(), m_con(c)
{

}

ClientSocket::~ClientSocket()
{

}

int ClientSocket::getDescriptor()
{
    return static_cast<int>(m_con.get_handle());
}

int ClientSocket::HandleRead()
{
    return 0;
}

int ClientSocket::HandleWrite()
{
    return 0;
}

int ClientSocket::HandleExcept()
{
    return 0;
}

}
}
