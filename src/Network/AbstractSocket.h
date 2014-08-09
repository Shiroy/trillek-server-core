#pragma once

namespace Trillek
{
namespace Network
{

/**
 * @brief An abstraction class to allow the Reactor to handle all socket type
 *
 * This abstract class encapsulate all the socket type. To define a new socket typ, you must inherit this class and override the virtual functions.
 *
 * @ref NetworkReactor
 */
class AbstractSocket
{
public:
    AbstractSocket();
    virtual ~AbstractSocket()=0;

    ///This function is called by the reactor when the socket is ready for reading
    virtual int HandleRead()=0;
    ///This function is called by the reactor when the socket is ready for writing
    virtual int HandleWrite()=0;
    ///This function is called by the reactor when an exception occur.
    virtual int HandleExcept()=0;

    ///This must return the socket descriptor
    virtual int getDescriptor()=0;
};

}
}
