/*
Author : betallcoffee
*/

#ifndef __STATUS_BAR_LAYER_H__
#define __STATUS_BAR_LAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class StatusBarLayer : public CCLayer {
public :
	virtual ~StatusBarLayer();
	virtual bool init();
	CREATE_FUNC(StatusBarLayer);

private :
	CCSprite *pExperience_;
};

#endif // __STATUS_BAR_LAYER_H__