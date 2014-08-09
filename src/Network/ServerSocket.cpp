#include "ServerSocket.h"
#include "ClientSocket.h"
#include "NetworkReactor.h"

namespace Trillek
{
namespace Network
{

ServerSocket::ServerSocket() : AbstractSocket()
{
    network::NetworkAddress bind_addr;
    bind_addr.ip4("0.0.0.0");
    bind_addr.port(8080); //TODO : Do it in a more configurable way

    if(!m_server_socket.bind(bind_addr))
        throw "Cannot bind socket to port";
    if(!m_server_socket.listen(127)) //TODO : Do this also in a more configurable way :)
        throw "Cannot listen to port";
}

int ServerSocket::HandleRead()
{
    ClientSocket *cli_con = new ClientSocket(m_server_socket.accept());
    NetworkReactor::GetInstance()->AddSocket(cli_con);
}

int ServerSocket::HandleWrite()
{
    return 0;
}

int ServerSocket::HandleExcept()
{
    return 0;
}

int ServerSocket::getDescriptor()
{
    return static_cast<int>(m_server_socket.get_handle());
}

}
}
