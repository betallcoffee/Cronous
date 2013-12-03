/*
 Author : Tina
 */

#ifndef __INTRO_ANIMATE_SCENE_H__
#define __INTRO_ANIMATE_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class IntroAnimateScene : public CCLayer {
public :
	~IntroAnimateScene();
	virtual bool init();
	static CCScene *scene();
	CREATE_FUNC(IntroAnimateScene);

private :
	void animateOneCallFunc();
	void animateTwoCallFunc();
	void animateThreeCallFunc();
	void animateFourCallFunc();
	void selectRoleCallFunc();
	void selectRoleMenu(CCObject *pSender);

	static const int kNumOfBgk = 4;
	static const int kNumOfWord = 4;
	CCSprite *bgks_[kNumOfBgk];
	CCSprite *words_[kNumOfWord];
	bool isFirst_;
};

#endif // __INTRO_ANIMATE_SCENE_H_