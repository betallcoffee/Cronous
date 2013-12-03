/*
 Author : Tina
 */

#include "ETMessageQueue.h"

ETMessageQueue::ETMessageQueue() {
}

ETMessageQueue::~ETMessageQueue() {
}

bool ETMessageQueue::pushMessage(ETMessage *msg) {
	messages_.push(msg);
	return true;
}

ETMessage *ETMessageQueue::popMessage() {
	ETMessage *msg = messages_.front();
	messages_.pop();
	return msg;
}