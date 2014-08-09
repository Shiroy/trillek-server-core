#pragma once

#include <map>

#include "SocketSelector.h"

namespace Trillek
{
namespace Network
{

class AbstractSocket;

/**
 * @brief This class handle all incomming event from the network
 *
 * It dispatch all incomming event from the network to the right handler.
 * For example, if there is an incomming event from the acceptor socket, it will call the client accept method.
 * If it's an icommng event from a client, it will reads the datas.
 *
 * It will also manage the data to be sent on the network. If a socket is ready for writing, he'll call the write handler automaticaly.
 *
 * It's the socket manager. It composes all the sockets
 * @ref AbstractSocket
 */
class NetworkReactor
{
public:
    NetworkReactor();
    NetworkReactor(const NetworkReactor& o)=delete;
    ~NetworkReactor();

    ///Add a new socket to the reactor. If the socket already exists in, an exception will be triggered
    inline void AddSocket(AbstractSocket* new_socket);
    ///Permanantly delete a socket. It deletes the socket object too.
    inline void RemoveSocket(AbstractSocket* sock);

    ///This is the function to launch the network thread. After calling it, the main thread should not need to call any other methods.
    void operator()();

private:

    bool isServerShutdowning();

    std::map<int, AbstractSocket*> m_allSockets;

    SocketSelector m_selector;
};

}
}
