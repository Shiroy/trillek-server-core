#pragma once

#include <vector>
#include <list>

namespace Trillek
{
namespace Network
{

class AbstractSocket;

/**
 * @brief This class allow to manage multiple socket simultaneously without blocking.
 */
class SocketSelector
{
public:
    SocketSelector();

    ///Add a socket to observ. read, write and except indicate what events are observed.
    void AddSocket(AbstractSocket* socket, bool read=false, bool write=false, bool except=false);
    ///Stop observing a socket
    void RemoveSocket(AbstractSocket* socket);

    ///Check each socket and return true if a socket is ready for reading or writing or for an exception. If it return true, one of the 3 vectors is not empty and contains the socket descriptor. These vector are not cleared by this functions.
    bool Select(std::vector<AbstractSocket*> &ready_read_sockets, std::vector<AbstractSocket*> &ready_write_sockets, std::vector<AbstractSocket*> &ready_except_sockets, unsigned int wait_time_in_usec);

private:
    std::list<AbstractSocket*> m_read_sockets, m_write_sockets, m_except_sockets;
};

}
}
