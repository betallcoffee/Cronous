/*
 Author : betallcoffee
 */

#ifndef __ET_MESSAGE_QUEUE_H__
#define __ET_MESSAGE_QUEUE_H__

#include <map>
#include "ETMacro.h"

struct sCallFuncEntry;
class ETMessage;

class ETMessageManager {
public :
	// Note: not thread safe, only invoke in main thread.
	static ETMessageManager *sharedInstance();

	void dispatchMessage();
	void sendMessage(ETMessage *msg, int category, void *source, ET_CallFuncN_t callFuncN);
	void removeCallFuncN(void *source, ET_CallFuncN_t callFuncN);

private :
	ETMessageManager();
	~ETMessageManager();

	typedef std::map<int, struct sCallFuncEntry*> Map_CallFunc_t;
	typedef std::map<int, struct sCallFuncEntry*>::iterator Map_CallFunc_Iter_t;
	typedef std::vector<int>* Vector_Int_t;
	typedef std::map<void*, Vector_Int_t> Map_Source_t;
	typedef Map_Source_t::iterator Map_Source_Iter_t;
	static ETMessageManager *pShareInstance_;
	Map_CallFunc_t callFuncs_;
	Map_Source_t sources_;
};

#endif // __ET_MESSAGE_QUEUE_H__
