/*
 Author : betallcoffee
 */

#ifndef __ET_SOCKET_CLIENT_H__
#define __ET_SOCKET_CLIENT_H__

#include <pthread.h>
#include <string>
#include <queue>

#include "ETSocket.h"
#include "ETBuffer.h"
#include "ETMessageQueue.h"

class ETMessage;

class ETSocketClient {
public :
	ETSocketClient(const std::string &host, short port);
	~ETSocketClient();

	bool startClient();
	bool stopClient();

	ETMessage *pickMessage();
	void sendMessage(ETMessage *msg);

private :
	ETSocketClient(const ETSocketClient&);

	static void *sendThreadCallFunc(void *arg);
	static void *recvThreadCallFunc(void *arg);
	bool connectToServer();
	bool connectingLoop();
	bool startRecv();
	bool stopRecv();
	int select(fd_set *readfds, fd_set *writefds, fd_set *exceptfds);

	int sendThreadLoop();
	int sendLoop();
	int recvThreadLoop();

	std::string host_;
	std::string ip_;
	short port_;
	ETSocket socket_;
	bool isRunning_;

	// pthread for send message
	bool bSendStart_;
	pthread_t sendThread_;
	pthread_mutex_t sendMutex_;
	pthread_cond_t sendCond_;
	ETBuffer sendBuffer_;
	std::queue<ETMessage*> sendMsgQ_;

	// pthread for recv message
	bool bRecvStart_;
	pthread_t recvThread_;
	pthread_mutex_t recvMutex_;
	ETBuffer recvBuffer_;
	std::queue<ETMessage*> recvMsgQ_;

};

#endif // __ET_SOCKET_CLIENT_H__
