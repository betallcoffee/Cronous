/*
 Author : betallcoffee
 */

#include "PersonalLayer.h"
#include "GoodSprite.h"

PersonalLayer::~PersonalLayer() {
}

bool PersonalLayer::init() {
	bool bRet = false;

	do {
		CC_BREAK_IF(!CCLayerColor::init());

		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		this->setContentSize(winSize);

		pInfoBackground_ = CCSprite::create("personalinfo_bkg.png");
		pInfoBackground_->setPosition(ccp(winSize.width/2, winSize.height/2));
		this->addChild(pInfoBackground_);

		bRet = true;
	} while(false);

	return bRet;
}
