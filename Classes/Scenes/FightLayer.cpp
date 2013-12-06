/*
 Author : betallcoffee
 */

#include "cocos-ext.h"
#include "GUI/CCControlExtension/CCScale9Sprite.h"

#include "FightLayer.h"

USING_NS_CC_EXT;

FightLayer::~FightLayer() {
}

bool FightLayer::init() {
	bool bRet = false;

	do {
		CC_BREAK_IF(!CCLayer::init());

		winSize_ = CCDirector::sharedDirector()->getWinSize();
		CCSprite *pBackground = CCSprite::create("arenawindow_bkg.png");
		pBackground->setPosition(ccp(winSize_.width/2, winSize_.height/2 - 5));
		this->addChild(pBackground);
		this->fightInfo();

		bRet = true;
	} while (false);

	return bRet;
}


void FightLayer::fightInfo() {
	char fightInfo[100] = "";
	sprintf(fightInfo, ":100 ");
	CCLabelTTF *pInfoLabel = CCLabelTTF::create(fightInfo,
		"hycc.ttf",
		22, 
		CCSizeMake(400, 0),
		kCCTextAlignmentCenter);
	pInfoLabel->setColor(ccc3(255, 219, 160));
	pInfoLabel->setPosition(ccp(winSize_.width/2, 600));
	this->addChild(pInfoLabel);

	CCScale9Sprite *pItem =	CCScale9Sprite::create("arena_item_bkg.png");
	pItem->setContentSize(CCSizeMake(410, 85));
	pItem->setAnchorPoint(ccp(0.5, 1));
	pItem->setPosition(ccp(0, -82));

	CCSprite *pBorder = CCSprite::create("common_qs_bkg_4.png");
	pBorder->setPosition(ccp(265, 38));
	pBorder->setScale(1.0);

	CCSprite *pHeader = CCSprite::create("qs_0001.png");
	pHeader->setAnchorPoint(CCPointZero);
	pHeader->setScale(0.18);

	pBorder->addChild(pHeader);
	pItem->addChild(pBorder);
	this->addChild(pItem);
}
