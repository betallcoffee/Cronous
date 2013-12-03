/*
 Author : betallcoffee
 */

#ifndef __PERSONAL_LAYER_H__
#define __PERSONAL_LAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class PersonalLayer : public CCLayerColor {
public :
	virtual ~PersonalLayer();
	virtual bool init();
	CREATE_FUNC(PersonalLayer);

private :
	CCSprite *pInfoBackground_;
};

#endif // __PERSONAL_LAYER_H__