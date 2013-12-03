/*
 Author : betallcoffee
 */

#include "HomeScene.h"
#include "LevelMapLayer.h"
#include "StatusBarLayer.h"
#include "FightLayer.h"
#include "PersonalLayer.h"

HomeScene::~HomeScene() {
	CCTextureCache::sharedTextureCache()->removeUnusedTextures();
}

CCScene *HomeScene::scene() {
	CCScene *scene;
	
	do {
		scene = CCScene::create();
		CC_BREAK_IF(scene == NULL);

		HomeScene *layer = HomeScene::create();
		CC_BREAK_IF(layer == NULL);

		scene->addChild(layer);
	} while (false);

	return scene;
}

bool HomeScene::init() {
	bool bRet = false;

	do {
		CC_BREAK_IF(!CCLayer::init());

		pLevelMapLayer_ = NULL;
	    pStatusBarLayer_ = NULL;
	    pFightLayer_ = NULL;
	    pPersonalLayer_ = NULL;
		pCurLayer_ = NULL;

		this->initTitle();
		this->initLevelBtn();

		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		CCSprite *pBorder = CCSprite::create("zjm_bkg.png");
		pBorder->setPosition(ccp(winSize.width/2, winSize.height/2));
		this->addChild(pBorder);

		this->initStatusBar();
		this->initTabBar();

		pCurLayer_ = pLevelMapLayer_;
		bRet = true;
	} while (false);

	return bRet;
}

void HomeScene::initTitle() {
}

void HomeScene::initLevelBtn() {
	pLevelMapLayer_ = LevelMapLayer::create();
	pLevelMapLayer_->setAnchorPoint(CCPointZero);
	this->addChild(pLevelMapLayer_, 0);
}

void HomeScene::initStatusBar() {
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	pStatusBarLayer_ = StatusBarLayer::create();
	pStatusBarLayer_->setPosition(ccp(0, winSize.height - 100));
	this->addChild(pStatusBarLayer_, 1);
}

void HomeScene::initTabBar() {
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	pComposeMenuItem_ = CCMenuItemImage::create("zjm_hc_1.png", 
		"zjm_hc_2.png", 
		this,
		menu_selector(HomeScene::composeMenu));
	pComposeMenuItem_->setPosition(ccp(70, winSize.height - 165));

	pFriendsMenuItem_ = CCMenuItemImage::create("zjm_employfriends_1.png",
		"zjm_employfriends_2.png",
		this,
		menu_selector(HomeScene::friendsMenu));
	pFriendsMenuItem_->setPosition(ccp(winSize.width - 60, winSize.height - 165));

	pPersonalMenuItem_ = CCMenuItemImage::create("zjm_personal_1.png",
		"zjm_personal_2.png",
		this,
		menu_selector(HomeScene::personalMenu));
	pPersonalMenuItem_->setAnchorPoint(ccp(0.5, 0.5));
	pPersonalMenuItem_->setPosition(ccp(winSize.width/2, winSize.height - 165));

	pRechargeMenuItem_ = CCMenuItemImage::create("zjm_linkrecharge_1.png",
		"zjm_linkrecharge_2.png",
		this,
		menu_selector(HomeScene::rechargeMenu));
	pRechargeMenuItem_->setAnchorPoint(ccp(0, 0));
	pRechargeMenuItem_->setPosition(ccp(50, 25));

	pHomeMenuItem_ = CCMenuItemImage::create("zjm_linkhome_1.png",
		"zjm_linkhome_2.png",
		this,
		menu_selector(HomeScene::homeMenu));
	pHomeMenuItem_->setAnchorPoint(ccp(1, 0));
	pHomeMenuItem_->setPosition(ccp(winSize.width - 45, 25));

	pMailMenuItem_ = CCMenuItemImage::create("zjm_mail_1.png",
		"zjm_mail_2.png",
		this,
		menu_selector(HomeScene::mailMenu));
	pMailMenuItem_->setAnchorPoint(ccp(0, 0));
	pMailMenuItem_->setPosition(ccp(150, 25));

	pFightMenuItem_ = CCMenuItemImage::create("zjm_arena_1.png",
		"zjm_arena_2.png",
		this,
		menu_selector(HomeScene::fightMenu));
	pFightMenuItem_->setAnchorPoint(ccp(0, 0));
	pFightMenuItem_->setPosition(ccp(240, 25));

	pTabMenus_ = CCMenu::create(pComposeMenuItem_,
		pFriendsMenuItem_,
		pPersonalMenuItem_,
		pRechargeMenuItem_,
		pHomeMenuItem_,
		pMailMenuItem_,
		pFightMenuItem_, NULL);
	pTabMenus_->setAnchorPoint(ccp(0, 0));
    pTabMenus_->setPosition(ccp(0, 0));

    this->addChild(pTabMenus_,6,1878);
}

void HomeScene::composeMenu(CCObject *pSender) {
}

void HomeScene::friendsMenu(CCObject *pSender) {
}

void HomeScene::personalMenu(CCObject *pSender) {
	pComposeMenuItem_->setVisible(false);
	pFriendsMenuItem_->setVisible(false);
	pCurLayer_->setVisible(false);

	if(pPersonalLayer_ == NULL) {
		pPersonalLayer_ = PersonalLayer::create();
		this->addChild(pPersonalLayer_);
	}
	pPersonalLayer_->setVisible(true);
	pCurLayer_ = pPersonalLayer_;
}

void HomeScene::fightMenu(CCObject *pSender) {
	pComposeMenuItem_->setVisible(false);
	pFriendsMenuItem_->setVisible(false);
	pCurLayer_->setVisible(false);

	if(pFightLayer_ == NULL) {
		pFightLayer_ = FightLayer::create();
		this->addChild(pFightLayer_);
	}
	pFightLayer_->setVisible(true);
	pCurLayer_ = pFightLayer_;
}

void HomeScene::mailMenu(CCObject *pSender) {
}

void HomeScene::homeMenu(CCObject *pSender) {
	pComposeMenuItem_->setVisible(true);
	pFriendsMenuItem_->setVisible(true);
	pCurLayer_->setVisible(false);
	pLevelMapLayer_->setVisible(true);
	pCurLayer_ = pLevelMapLayer_;
}

void HomeScene::rechargeMenu(CCObject *pSender) {
}
