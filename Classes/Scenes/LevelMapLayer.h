/*
 Author : Tina
 */

#ifndef __LEVEL_MAP_LAYER_H__
#define __LEVEL_MAP_LAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class LevelMapLayer : public CCLayer {
public :
	virtual ~LevelMapLayer();
	virtual bool init();
	CREATE_FUNC(LevelMapLayer);

	virtual void registerWithTouchDispatcher();
    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
    virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
    virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);

private :
	void levelMenu(CCObject *pSender);

	static const int kNumOfMap_ = 5;
	int currentMapIdx_;
	CCDictionary *pLevelsDict_;
	CCPoint startP_;
	CCMenu *pLevelMenu_;
};

#endif // __LEVEL_MAP_LAYER_H__