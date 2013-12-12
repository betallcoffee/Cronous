/*
 Author : betallcoffee
 */

#include "ETSocketManager.h"
#include "ETMessageManager.h"

typedef struct sCallFuncEntry_ {
	void *pTarget_;
	ET_CallFuncN_t pCallFuncN_;
}sCallFuncEntry;

ETMessageManager *ETMessageManager::pShareInstance_ = NULL;

ETMessageManager::ETMessageManager() {
}

ETMessageManager::~ETMessageManager() {
}

ETMessageManager *ETMessageManager::sharedInstance() {
	if (pShareInstance_ == NULL) {
		pShareInstance_ = new ETMessageManager();
	}
	return pShareInstance_;
}

void ETMessageManager::dispatchMessage() {
	ETMessage *msg = ETSocketManager::sharedInstance()->getSocketClient()->pickMessage();

	if (msg) {
		int category = msg->getCategory();
		Map_CallFunc_Iter_t iter = callFuncs_.find(category);
		if (iter != callFuncs_.end()) {
			sCallFuncEntry *entry = iter->second;
			ASSERT(entry->pTarget_);
			ASSERT(entry->pCallFuncN_);
			// Note!!
			ET_CallFuncN_t pCallFuncN = entry->pCallFuncN_;
			entry->pTarget_->*pCallFuncN(NULL);
		}
	}
}

void ETMessageManager::sendMessage(ETMessage *msg, int category, void *source, ET_CallFuncN_t callFuncN) {
	ASSERT(msg);
	ASSERT(source);
	ASSERT(callFuncN);

	sCallFuncEntry *entry = new sCallFuncEntry();
	entry->pTarget_ = source;
	entry->pCallFuncN_ = callFuncN;
	callFuncs_[category] = entry;

	Map_Source_Iter_t iter = sources_.find(source);
	Vector_Int_t pVector;
	if (iter == sources_.end()) {
		pVector = new Vector_Int_t();
		sources_[source] = pVector;
	} else {
		pVector = iter->second;
	}

	pVector->push_back(category);
	ETSocketManager::sharedInstance()->getSocketClient()->sendMessage(msg);
}

void ETMessageManager::removeCallFuncN(void *source, ET_CallFuncN_t callFuncN) {
	ASSERT(source);
	ASSERT(callFuncN);
	Map_Source_Iter_t iter = sources_.find(source);
	if (iter != sources_.end()) {
		Vector_Int_t pVector = iter->second;
		delete pVector;
		sources_.erase(iter);
	}
}

