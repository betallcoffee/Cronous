/*
 Author : betallcoffee
 */

#include "LevelMapLayer.h"

LevelMapLayer::~LevelMapLayer() {
	pLevelsDict_->release();
}

bool LevelMapLayer::init() {
	bool bRet = false;
	 
	do {
		CC_BREAK_IF(!CCLayer::init());
		this->setTouchEnabled(true);
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();		

		CCSprite *pMaps = CCSprite::create();
		pMaps->setAnchorPoint(ccp(0, 0));
		pMaps->setPosition(ccp(0, 0));
		int idxs[kNumOfMap_] = { 3, 1, 2, 3, 1 };
		char mapName[] = "map1.png";
		for (int i = 0; i < kNumOfMap_; i++) {
			mapName[3] = '0' + idxs[i];
			CCSprite *pMap = CCSprite::create(mapName);
			pMap->setAnchorPoint(ccp(0, 0));
			pMap->setPosition(ccp(0, 441 * i));
			pMaps->addChild(pMap);
		}
		this->addChild(pMaps);

		pLevelMenu_ = CCMenu::create();
		pLevelMenu_->setAnchorPoint(ccp(0, 0));
		pLevelMenu_->setPosition(ccp(0, 0));
		this->addChild(pLevelMenu_);

		pLevelsDict_ = CCDictionary::create();
		pLevelsDict_->retain();
		for (int i = 0; i < 9; i++) {
			CCMenuItemSprite *pLevelMenuItem = CCMenuItemImage::create("zjm_building_1.png", 
				"zjm_building_1.png", 
				"zjm_building_2.png",
				this, 
				menu_selector(LevelMapLayer::levelMenu));
			pLevelMenuItem->setPosition(ccp((i % 3) % 2 == 1 ? 140 : winSize.width - 130,
				130 * (i % 3)  + 442 * (i / 3) + 240));

			CCSize itemSize = pLevelMenuItem->getContentSize();
			CCLabelTTF *pNameLabel = CCLabelTTF::create("Hello World", "hycc.ttf", 20);
			pNameLabel->setPosition(ccp(itemSize.width/2 - 1, 35));
			pNameLabel->setDimensions(CCSizeMake(200, 0));
			pNameLabel->setHorizontalAlignment(kCCTextAlignmentCenter);
			pNameLabel->setVerticalAlignment(kCCVerticalTextAlignmentTop);
			pNameLabel->setColor(ccc3(255, 175, 51));
			pLevelMenuItem->addChild(pNameLabel);

			pLevelMenu_->addChild(pLevelMenuItem);
			pLevelsDict_->setObject(pLevelMenuItem, i);
		}

		currentMapIdx_ = 0;
		bRet = true;
	} while (false);

	return bRet;
}

void LevelMapLayer::registerWithTouchDispatcher() {
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, INT_MIN, true);
}

bool LevelMapLayer::ccTouchBegan(CCTouch* touch, CCEvent* event) {
	CCPoint touchP = touch->getLocation();
	startP_ = this->convertToNodeSpace(touchP);
	CCRect rect = CCRectMake(40, 140, 400, 470);
	if (rect.containsPoint(touchP)) {
		return true;
	} else {
		return false;
	}
}

void LevelMapLayer::ccTouchMoved(CCTouch* touch, CCEvent* event) {
	CCPoint touchP = touch->getLocation();
	CCPoint nodeP = this->convertToNodeSpace(touchP);
	CCPoint distanceP = ccpSub(nodeP, startP_);
	CCPoint position = this->getPosition();
	if (position.y + distanceP.y > 0) return;
	this->setPosition(ccp(position.x, position.y + distanceP.y));
}

void LevelMapLayer::ccTouchEnded(CCTouch* touch, CCEvent* event) {
}

void LevelMapLayer::levelMenu(CCObject *pSender) {
	CCLog("levelMenu select");
}