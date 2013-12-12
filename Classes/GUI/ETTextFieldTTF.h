/*
 * ETTextFieldTTF.h
 *
 *  Created on: Dec 11, 2013
 *      Author: betallcoffee
 */

#ifndef __ET_TEXT_FIELD_TTF_H__
#define __ET_TEXT_FIELD_TTF_H__

#include <text_input_node/CCTextFieldTTF.h>
#include <touch_dispatcher/CCTouchDelegateProtocol.h>

class ETTextFieldTTF: public cocos2d::CCTextFieldTTF,
		public cocos2d::CCTouchDelegate {
public:
	ETTextFieldTTF();
	virtual ~ETTextFieldTTF();
};

#endif /* __ET_TEXT_FIELD_TTF_H__ */
