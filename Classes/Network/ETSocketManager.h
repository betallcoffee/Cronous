/*
 Author : Tina
 */

#ifndef __ET_SOCKET_MANAGER_H__
#define __ET_SOCKET_MANAGER_H__

#include "ETSocketClient.h"

class ETSocketManager {
public :
	static ETSocketManager *sharedInstance();
	void connectToServer();
	ETSocketClient *getSocketClient() { return pSocketClient_; }

private :
	ETSocketManager();
	~ETSocketManager();

	static ETSocketManager *pSharedInstance_;
	ETSocketClient *pSocketClient_;
};

#endif // __ET_SOCKET_MANAGER_H_
