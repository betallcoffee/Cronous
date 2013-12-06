/*
 Author : betallcoffee
 */

#ifndef __ET_SOCKET_H__
#define __ET_SOCKET_H__

#ifdef WIN32
#include <WinSock2.h>
#else
#include <sys/ioctl.h>
#include <netdb.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#endif

#include <string>

class ETSocket {
public :
	ETSocket();
	~ETSocket();

	int getFD();
	void setNonblock();

#ifdef WIN32
	static void startup();
	static void cleanup();
#endif
	static bool DNSParse(const std::string &domain, std::string &ip);
	static int getError();

	int socket(int family, int type, int protocol);
	int connect(const std::string &ip, const short port);
	int bind(const std::string &ip, const short port);
	int listen(int backlog);
	int accept();
	int send(const char *data, int len, int flags);
	int recv(char * const data, int len, int flags);
	int close();
	int setsockopt(int level, int optname, const void *optval, int optlen);
	int getsockopt(int level, int optname, void *optval, int *optlen);
	
	static const int kInvalidSocket = -1;

private :
	int fd_;
	std::string cliIP_;
	unsigned short cliPort_;
};

#endif // __ET_SOCKET_H__
