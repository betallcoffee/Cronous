/*
 Author : betallcoffee
 */

#include "StatusBarLayer.h"

StatusBarLayer::~StatusBarLayer() {
}

bool StatusBarLayer::init() {
	bool bRet = false;

	do {
		CC_BREAK_IF(!CCLayer::init());

		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		CCSprite *pBackground = CCSprite::create("zt_bkg.png");
		pBackground->setAnchorPoint(ccp(0.5, 0));
		pBackground->setPosition(ccp(winSize.width/2, -14));
		this->addChild(pBackground);

		pExperience_ = CCSprite::create("zt_exp_bar.png");
		pExperience_->setAnchorPoint(CCPointZero);
		pExperience_->setPosition(ccp(80, 20));
		pExperience_->setScaleX(0.5);
		this->addChild(pExperience_, 2);

		bRet = true;
	} while (false);

	return bRet;
}