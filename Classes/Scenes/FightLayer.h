/*
 Author : betallcoffee
 */

#ifndef __FIGHT_LAYER_H__
#define __FIGHT_LAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class FightLayer : public CCLayer {
public :
	virtual ~FightLayer();
	virtual bool init();
	CREATE_FUNC(FightLayer);

private :
	void fightInfo();

	CCSize winSize_;

};

#endif //__FIGHT_LAYER_H__
