/*
 Author : Tina
 */

#include "LoadingLayer.h"

LoadingLayer::~LoadingLayer() {
	CC_SAFE_RELEASE_NULL(pLoadingRepeat_);
}

bool LoadingLayer::init() {
	bool bRet = false;
	
	do {
		if (!CCLayerColor::initWithColor(ccc4(0, 0, 0, 100))) {
			return false;
		}
		this->setTouchEnabled(true);

		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		CCSpriteFrameCache *pFrameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
		
		pFrameCache->addSpriteFramesWithFile("loading.plist");
		CCArray *pLoadFrames = CCArray::create();
		char frameName[16] = {0};
		for (int i = 1; i <= 12; i++) {
			sprintf(frameName, "load%d.png", i);
			CCSpriteFrame *frame = pFrameCache->spriteFrameByName(frameName);
			pLoadFrames->addObject(frame);
		}

		CCSprite *pLoadSprite = CCSprite::createWithSpriteFrameName("load1.png");
		pLoadSprite->setPosition(ccp(winSize.width*0.5, winSize.height*0.5));
		this->addChild(pLoadSprite);

		CCAnimation *pLoadingAnimation = CCAnimation::createWithSpriteFrames(pLoadFrames, 0.1f);
		CCActionInterval *pLoadingAction = CCAnimate::create(pLoadingAnimation);
		pLoadingRepeat_ = CCRepeatForever::create(pLoadingAction);
		pLoadSprite->runAction(pLoadingRepeat_);
		CC_SAFE_RETAIN(pLoadingRepeat_);

		bRet = true;
	} while (0);

	return bRet;
}

void LoadingLayer::registerWithTouchDispatcher() {
	CCLayer::registerWithTouchDispatcher();
}

bool LoadingLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) {
	bool bRet = false;
	bRet = true;
	return bRet;
}

void LoadingLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent) {
}

void LoadingLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) {
}
