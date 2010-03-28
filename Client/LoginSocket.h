#ifndef LOGINSOCKET_H
#define LOGINSOCKET_H

#include "Threading.h"
#include "NetSock.h"
#include "NetMessages.h"
#include "Buffers.h"

class LoginSocket : public CThread
{
public:
	LoginSocket();
	~LoginSocket();

private:
};

#endif // LOGINSOCKET_H
