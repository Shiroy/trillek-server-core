#include "NetworkReactor.h"
#include "AbstractSocket.h"
#include <vector>

namespace Trillek
{
namespace Network
{

NetworkReactor* NetworkReactor::m_instance = nullptr;

NetworkReactor::NetworkReactor()
{

}

NetworkReactor::~NetworkReactor()
{
    for(auto it = m_allSockets.begin() ; it != m_allSockets.end() ; it++)
        delete it->second;

    m_allSockets.clear();
}

void NetworkReactor::AddSocket(AbstractSocket *new_socket)
{
    int descriptor = new_socket->getDescriptor();
    if(m_allSockets.find(descriptor) != m_allSockets.end())
        throw "NetworkReactor::addSocket : Attempt to add an already existing socket.";

    m_allSockets[descriptor] = new_socket;
}

inline void NetworkReactor::RemoveSocket(AbstractSocket *sock)
{
    m_selector.RemoveSocket(sock);
    m_allSockets.erase(sock->getDescriptor());
    delete sock;
}

void NetworkReactor::operator ()()
{
    std::vector<AbstractSocket*> ready_read, ready_write, ready_except;

    while (!isServerShutdowning())
    {
        ready_read.clear();
        ready_write.clear();
        ready_except.clear();

        if(m_selector.Select(ready_read, ready_write, ready_except, 100))
        {
            for(AbstractSocket* sock : ready_read)
            {
                if(sock->HandleRead() == -1)
                {
                    RemoveSocket(sock);
                }
            }

            for(AbstractSocket* sock : ready_write)
            {
                if(sock->HandleWrite() == -1)
                {
                    RemoveSocket(sock);
                }
            }

            for(AbstractSocket* sock : ready_write)
            {
                if(sock->HandleExcept() == -1)
                {
                    RemoveSocket(sock);
                }
            }
        }
    }
}

bool NetworkReactor::isServerShutdowning()
{
    return false;
}

NetworkReactor* NetworkReactor::GetInstance()
{
    if(m_instance == nullptr)
        m_instance = new NetworkReactor;
    return m_instance;
}

void NetworkReactor::DeleteInstance()
{
    if(m_instance != nullptr)
        delete m_instance;
    m_instance = nullptr;
}

}
}
