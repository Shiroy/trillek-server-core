#include "SocketSelector.h"
#include "AbstractSocket.h"

#if __linux
#include <sys/select.h>
#elif WIN32
//TODO : Add the right include here
#endif

namespace Trillek
{
namespace Network
{

SocketSelector::SocketSelector()
{

}

void SocketSelector::AddSocket(AbstractSocket *socket, bool read, bool write, bool except)
{
    if(read)
    {
        m_read_sockets.push_back(socket);
        m_read_sockets.unique(); //Remove duplicate values
    }
    if(write)
    {
        m_write_sockets.push_back(socket);
        m_write_sockets.unique();
    }
    if(except)
    {
        m_except_sockets.push_back(socket);
        m_except_sockets.unique();
    }
}

void SocketSelector::RemoveSocket(AbstractSocket *socket)
{
    m_read_sockets.remove(socket);
    m_write_sockets.remove(socket);
    m_except_sockets.remove(socket);
}

bool SocketSelector::Select(std::vector<AbstractSocket*> &ready_read_sockets, std::vector<AbstractSocket*> &ready_write_sockets, std::vector<AbstractSocket*> &ready_except_sockets, unsigned int wait_time_in_usec)
{
    fd_set read, write, except;

#ifdef __linux
    int max_descriptor = 0;
#endif

    for(AbstractSocket* sock : m_read_sockets)
    {
        int descriptor = sock->getDescriptor();
        FD_SET(descriptor, &read);
#ifdef __linux
        max_descriptor = std::max(max_descriptor, descriptor);
#endif
    }

    for(AbstractSocket* sock : m_write_sockets)
    {
        int descriptor = sock->getDescriptor();
        FD_SET(descriptor, &write);
#ifdef __linux
        max_descriptor = std::max(max_descriptor, descriptor);
#endif
    }

    for(AbstractSocket* sock : m_except_sockets)
    {
        int descriptor = sock->getDescriptor();
        FD_SET(descriptor, &except);
#ifdef __linux
        max_descriptor = std::max(max_descriptor, descriptor);
#endif
    }

    timeval timeout_timer;
    timeout_timer.tv_usec = wait_time_in_usec;

#ifdef __linux
    int nb_socket_ready = ::select(max_descriptor+1, &read, &write, &except, &timeout_timer);
#else
    int nb_socket_ready = ::select(0, &read, &write, &except, &timeout_timer); //TODO : Check this
#endif

    if(nb_socket_ready == 0)
        return false;

    for(AbstractSocket* sock: m_read_sockets)
    {
        if(FD_ISSET(sock->getDescriptor(), &read))
            ready_read_sockets.push_back(sock);
    }

    for(AbstractSocket* sock: m_write_sockets)
    {
        if(FD_ISSET(sock->getDescriptor(), &write))
            ready_write_sockets.push_back(sock);
    }

    for(AbstractSocket* sock: m_except_sockets)
    {
        if(FD_ISSET(sock->getDescriptor(), &except))
            ready_except_sockets.push_back(sock);
    }

    return true;
}

}
}
