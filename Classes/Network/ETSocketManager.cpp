/*
 Author : Tina
 */

#include <stdio.h>
#include "ETSocketManager.h"
#include "ETSocket.h"

ETSocketManager *ETSocketManager::pSharedInstance_ = NULL;

ETSocketManager::ETSocketManager() {
	ETSocket::startup();
}

ETSocketManager::~ETSocketManager() {
	ETSocket::cleanup();
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
