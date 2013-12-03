/*
 Author : Tina
 */


#include "ETMacro.h"
#include "ETSocket.h"
#include "ETSocketClient.h"
#include "ETMessage.h"

ETSocketClient::ETSocketClient(const std::string &host, short port) 
: host_(host),
port_(port),
isRunning_(false),
bSendStart_(false),
bRecvStart_(false){
	pthread_mutex_init(&sendMutex_, NULL);
	pthread_cond_init(&sendCond_, NULL);
	pthread_mutex_init(&recvMutex_, NULL);
}

ETSocketClient::~ETSocketClient() {
	
}

bool ETSocketClient::startClient() {
	bool bRet = false;

	do {
		// init pthread for send
		isRunning_ = true;
		BREAK_IF(bSendStart_);
		ASSERT_BREAK(pthread_create(&sendThread_, NULL, sendThreadCallFunc, this) == 0);
		bSendStart_ = true;
	} while (false);

	return bRet;
}

bool ETSocketClient::stopClient() {
	bool bRet = false;
	isRunning_ = false;
	pthread_mutex_lock(&sendMutex_);
	while (sendMsgQ_.size()) {
		sendMsgQ_.pop();
	}
	pthread_mutex_unlock(&sendMutex_);
	pthread_cond_signal(&sendCond_);
	return bRet;
}

ETMessage *ETSocketClient::pickMessage() {
	ETMessage *msg = NULL;
	pthread_mutex_lock(&recvMutex_);
	if (recvMsgQ_.size()) {
		msg = recvMsgQ_.front();
		recvMsgQ_.pop();
	}
	pthread_mutex_unlock(&recvMutex_);
	return msg;
}

void ETSocketClient::sendMessage(ETMessage *msg) {
	pthread_mutex_lock(&sendMutex_);
	sendMsgQ_.push(msg);
	pthread_cond_signal(&sendCond_);
	pthread_mutex_unlock(&sendMutex_);
}

void *ETSocketClient::sendThreadCallFunc(void *arg) {
	int iRet = 0;
	ETSocketClient *self = static_cast<ETSocketClient *>(arg);
	do {	
		BREAK_IF(!self->connectToServer());
		BREAK_IF(!self->connectingLoop());
		ASSERT(self->startRecv());
		iRet = self->sendThreadLoop();
	} while (false);

	return (void *)iRet;
}

void *ETSocketClient::recvThreadCallFunc(void *arg) {
	int iRet = 0;
	ETSocketClient *self = static_cast<ETSocketClient *>(arg);
	iRet = self->recvThreadLoop();
	return (void *)iRet;
}

bool ETSocketClient::connectToServer() {
	bool bRet = false;

	do {
		BREAK_IF(!ETSocket::DNSParse(host_, ip_));
		BREAK_IF(socket_.socket(AF_INET, SOCK_STREAM, 0) == ETSocket::kInvalidSocket);
		socket_.setNonblock();	
		
		int ret = socket_.connect(ip_, port_);
		if (ret == 0) {
			bRet = true;
			return bRet;
		} else {
			int error = ETSocket::getError();
#ifdef WIN32
			if (error == WSAEWOULDBLOCK) {
#else
			if (error == EINPROGRESS ||
				error == EWOULDBLOCK) {
#endif
				bRet = true;
				return bRet;
			}
		}

		bRet = false;
	} while (false);

	socket_.close();
	return bRet;
}

bool ETSocketClient::connectingLoop() {
	bool bRet = false;
	
	while(isRunning_) {	
		int ret;
		fd_set readfds, writefds, exceptfds;
		ret = this->select(&readfds, &writefds, &exceptfds);
#ifdef WIN32
	/*
	http://msdn.microsoft.com/en-us/library/windows/desktop/ms737625(v=vs.85).aspx
	*/		
		if (ret > 0) {
			if (FD_ISSET(socket_.getFD(), &writefds)) {
				bRet = true;
				return bRet;
			} 
			BREAK_IF(FD_ISSET(socket_.getFD(), &exceptfds));	
		} else if (ret == SOCKET_ERROR) {
			int error = ETSocket::getError();
			BREAK_IF(error != WSAEINTR);
		}
#else
	/*
	http://cr.yp.to/docs/connect.html
	*/
		if (ret > 0) {
			if (FD_ISSET(socket_.getFD(), &writefds) {
				int error;
				int iRet = socket_.ETGetsockopt(SOL_SOCKET, SO_ERROR, &error, sizeof(error));
				BREAK_IF(iRet == SOCKET_ERROR || error);
				bRet = true;
				return bRet;
			}
		} else if (ret < 0) {
			int error = ETSocket::getError();
			BREAK_IF(error != EINTR);
		}
#endif

	}
	
	socket_.close();
	return bRet;
}

bool ETSocketClient::startRecv() {
	bool bRet = false;

	do {
		BREAK_IF(bRecvStart_);
		ASSERT_BREAK(pthread_create(&recvThread_, NULL, recvThreadCallFunc, this) == 0);
		bRecvStart_ = true;
		bRet = true;
		return bRet;
	} while (false);
	
	socket_.close();
	return bRet;
}

int ETSocketClient::select(fd_set *readfds, fd_set *writefds, fd_set *exceptfds) {
	struct timeval timeout;
	timeout.tv_sec = 0;
	timeout.tv_usec = 0;
	FD_ZERO(readfds);
	FD_SET(socket_.getFD(), readfds);
	FD_ZERO(writefds);
	FD_SET(socket_.getFD(), writefds);
	FD_ZERO(exceptfds);
	FD_SET(socket_.getFD(),&exceptfds);
	return ::select(socket_.getFD() + 1, readfds, writefds, exceptfds, &timeout);
}

int ETSocketClient::sendThreadLoop() {
	int iRet = 0;

	while(isRunning_) {
		pthread_mutex_lock(&sendMutex_);
		while (sendMsgQ_.size() == 0) {
			pthread_cond_wait(&sendCond_, &sendMutex_);
		}
		while (isRunning_ && sendMsgQ_.size()) {
			ETMessage *pMsg = sendMsgQ_.front();
			sendMsgQ_.pop();
			size_t size = socket_.send(pMsg->data(), pMsg->size(), 0);
			ASSERT(size != SOCKET_ERROR );
			pMsg->track(size);
			while (isRunning_ && pMsg->size()) {
				int ret = this->sendLoop();
				if (ret == 0) {
					size = socket_.send(pMsg->data(), pMsg->size(), 0);
					ASSERT(size != SOCKET_ERROR );
					pMsg->track(size);
				}
			}
		}
		pthread_mutex_unlock(&sendMutex_);
	};

	return iRet;
}

int ETSocketClient::sendLoop() {
	int iRet = -1;

	while(isRunning_) {
		fd_set readfds, writefds, exceptfds;
		int ret = this->select(&readfds, &writefds, &exceptfds);
		if (ret > 0 && FD_ISSET(socket_.getFD(), &writefds)) {
			iRet = 0;
			break;
		} else if (ret == SOCKET_ERROR) {
			int error = ETSocket::getError();
#ifdef WIN32
			if (error == WSAEINTR) {
#else
			if (error == EINTR) {
#endif
				continue;
			} else {
				iRet = error;
				break;
			}
		}
	}

	return iRet;
}

int ETSocketClient::recvThreadLoop() {
	int iRet = 0;

	while(isRunning_) {
		fd_set readfds, writefds, exceptfds;
		int ret = select(&readfds, &writefds, &exceptfds);
		if (ret > 0 && FD_ISSET(socket_.getFD(), &readfds)) {
			char buf[65536];
			size_t size = socket_.recv(buf, 65536, 0);
			if (size > 0) {
				recvBuffer_.write(buf, size);
				ETMessage *msg = ETMessage::createMessage(recvBuffer_);
				if (msg != NULL) {
					pthread_mutex_lock(&recvMutex_);
					recvMsgQ_.push(msg);
					pthread_mutex_unlock(&recvMutex_);
				}
			} else if (size == 0) {				
				break;
			}
		} else if (ret == SOCKET_ERROR ) {
			int error = ETSocket::getError();
#ifdef WIN32
			if (error == WSAEINTR) {
#else
			if (error == EINTR) {
#endif
				continue;
			} else {
				iRet = error;
				break;
			}
		}
	}

	return iRet;
}
