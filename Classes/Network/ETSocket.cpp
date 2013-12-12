/*
 Author : betallcoffee
 http://my.oschina.net/odison/blog/9439
 */

#ifdef WIN32
#pragma comment(lib,"WS2_32")
#endif

#include "ETMacro.h"
#include "ETSocket.h"

ETSocket::ETSocket()
: fd_(kInvalidSocket),
  cliPort_(-1){

}

ETSocket::~ETSocket() {
	close();
}

int ETSocket::getFD() {
	return fd_;
}

#ifdef WIN32
void ETSocket::startup() {
	/*
	http://msdn.microsoft.com/zh-cn/vstudio/ms741563(en-us,VS.85).aspx
	*/
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
 
	wVersionRequested = MAKEWORD( 2, 2 );
 
	err = WSAStartup( wVersionRequested, &wsaData );
	  /* Tell the user that we could not find a usable */
	  /* WinSock DLL.                                  */
	ASSERT(err == 0);
 
	/* Confirm that the WinSock DLL supports 2.2.*/
	/* Note that if the DLL supports versions greater    */
	/* than 2.2 in addition to 2.2, it will still return */
	/* 2.2 in wVersion since that is the version we      */
	/* requested.                                        */
 
	if ( LOBYTE( wsaData.wVersion ) != 2 ||
		HIBYTE( wsaData.wVersion ) != 2 ) {
		/* Tell the user that we could not find a usable */
		/* WinSock DLL.                                  */
		WSACleanup( );
		ASSERT(false);
	}
}

void ETSocket::cleanup() {
	WSACleanup();
}

#endif

int ETSocket::setNonblock() {
#ifdef WIN32
	u_long arg = 1;
	return ioctlsocket(fd_, FIONBIO, &arg);
#else
	/*
	http://www.kegel.com/dkftpbench/nonblocking.html
	*/
	int flags;

    /* If they have O_NONBLOCK, use the Posit way to do it */
#if defined(O_NONBLOCK)
    /* FIXME: O_NONBLOCK is defined but broken on SunOS 4.1.x and AIX 3.2.5. */
    if (-1 == (flags = fcntl(fd, F_GETFL, 0)))
        flags = 0;
    return fcntl(fd_, F_SETFL, flags | O_NONBLOCK);
#else
    /* Otherwise, use the old way of doing it */
    flags = 1;
    return ioctl(fd_, FIONBIO, &flags);
#endif
#endif
}

bool ETSocket::DNSParse(const std::string &domain, std::string &ip) {
	struct hostent *p = gethostbyname(domain.c_str());
	if (p == NULL) {
		int error = ETSocket::getError();
		ASSERT(false);
		return false;
	} else {
		char str[16];
		sprintf(str, 
		"%u.%u.%u.%u",
		(unsigned char)p->h_addr[0], 
		(unsigned char)p->h_addr[1], 
		(unsigned char)p->h_addr[2], 
		(unsigned char)p->h_addr[3]);
		ip = str;
		return true;
	}
}

int ETSocket::getError() {
#ifdef WIN32
	return WSAGetLastError();
#else
	return errno;
#endif
}

int ETSocket::socket(int family, int type, int protocol) {
	ASSERT(fd_ == kInvalidSocket);
	fd_ = ::socket(family, type, protocol);
	return fd_;
}

int ETSocket::connect(const std::string &ip, const short port) {
	struct sockaddr_in svraddr;
	svraddr.sin_family = AF_INET;
	svraddr.sin_addr.s_addr = inet_addr(ip.c_str());
	svraddr.sin_port = htons(port);
	return ::connect(fd_, (struct sockaddr*)&svraddr, sizeof(svraddr));
}

int ETSocket::bind(const std::string &ip, const short port) {
	struct sockaddr_in svraddr;
	svraddr.sin_family = AF_INET;
	svraddr.sin_addr.s_addr = INADDR_ANY;
	svraddr.sin_port = htons(port);
	return ::bind(fd_, (struct sockaddr*)&svraddr, sizeof(svraddr));
}

int ETSocket::listen(int backlog) {
	return ::listen(fd_, backlog);
}

int ETSocket::accept() {
	struct sockaddr_in cliaddr;
	int addrlen = sizeof(cliaddr);
	int ret = ::accept(fd_, reinterpret_cast<struct sockaddr*>(&cliaddr), reinterpret_cast<socklen_t *>(&addrlen));
	if (ret == 0) {
		cliIP_ = inet_ntoa(cliaddr.sin_addr);
		cliPort_ = ntohs(cliaddr.sin_port);
	}
	return ret;
}

int ETSocket::send(const char *data, int len, int flags) {
	return ::send(fd_, data, len, flags);
}

int ETSocket::recv(char * const data, int len, int flags) {
	return ::recv(fd_, data, len, flags);
}

int ETSocket::setsockopt(int level, int optname, const void *optval, int optlen) {
#ifdef WIN32
	return ::setsockopt(fd_, level, optname, static_cast<const char *>(optval), optlen);
#else
	return ::setsockopt(fd_, level, optname, optval, optlen);
#endif
}

int ETSocket::getsockopt(int level, int optname, void *optval, int *optlen) {
#ifdef WIN32
	return ::getsockopt(fd_, level, optname, static_cast<char *>(optval), optlen);
#else
	return ::getsockopt(fd_, level, optname, optval, reinterpret_cast<socklen_t *>(optlen));
#endif
}

int ETSocket::close() {
	ASSERT(fd_ != kInvalidSocket);
#ifdef WIN32
	if (fd_ != kInvalidSocket) {
		closesocket(fd_);
	}
#else
	if (fd_ != kInvalidSocket) {
		::close(fd_);
	}
#endif
	fd_ = kInvalidSocket;
	return 0;
}

