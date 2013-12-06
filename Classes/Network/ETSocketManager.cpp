/*
 Author : betallcoffee
 */

#include <stdio.h>
#include "ETSocketManager.h"
#include "ETSocket.h"

ETSocketManager *ETSocketManager::pSharedInstance_ = NULL;

ETSocketManager::ETSocketManager()
: pSocketClient_(NULL){
#ifdef WIN32
	ETSocket::startup();
#endif
}

ETSocketManager::~ETSocketManager() {
#ifdef WIN32
	ETSocket::cleanup();
#endif
}

ETSocketManager *ETSocketManager::sharedInstance() {
	if (pSharedInstance_ == NULL) {
		pSharedInstance_ = new ETSocketManager();
	}
	return pSharedInstance_;
}

void ETSocketManager::connectToServer() {
	pSocketClient_ = new ETSocketClient("jiumiaoshanyou3.1251001050.lbs.twsapp.com", 31009);
	//pSocketClient_ = new ETSocketClient("183.60.242.26", 31009);
	pSocketClient_->startClient();
}
