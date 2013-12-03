/*
 Author : Tina
 */

#ifndef __ET_MESSAGE_QUEUE_H__
#define __ET_MESSAGE_QUEUE_H__

#include <queue>

class ETMessage;

class ETMessageQueue {
public :
	ETMessageQueue();
	~ETMessageQueue();

	bool isEmpty() { return messages_.empty(); }
	int size() { return messages_.size(); }
	bool pushMessage(ETMessage *msg);
	ETMessage *popMessage();
	
private :
	std::queue<ETMessage*> messages_;
};

#endif // __ET_MESSAGE_QUEUE_H__