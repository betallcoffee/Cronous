/*
Author : betallcoffee
*/

//#include "json.h"

#include "LoginScene.h"
#include "LoadingLayer.h"
#include "IntroAnimateScene.h"

//#include "ETSocketManager.h"
//#include "ETMessage.h"

CCScene *LoginScene::scene() {
	CCScene *scene = NULL;
	do {
		// 'scene' is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(!scene);

		// 'layer' is an autorelease object
		LoginScene *layer = LoginScene::create();
		CC_BREAK_IF(!layer);

		// add 'layer' as a child to 'scene'
		scene->addChild(layer);
	} while (0);
	
	return scene;
}

// on 'init' you need to initialize your instance
bool LoginScene::init() {
	bool bRet = false;
	do {
		// super init first.
		CC_BREAK_IF(!CCLayer::init());

		this->loadRes();
		this->initUI();
		
		bRet = true;
	} while (0);
	return bRet;
}

void LoginScene::loadRes() {
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ui_login.plist");
}

void LoginScene::initUI() {
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	CCSprite *pBackgroud = CCSprite::createWithSpriteFrameName("login_bkg.png");
	pBackgroud->setPosition(ccp(winSize.width*0.5, winSize.height*0.5));
	this->addChild(pBackgroud);

	CCMenuItemImage *pJiumiaoItem = CCMenuItemImage::create("ns-1.png", "ns-2.png", this, menu_selector(LoginScene::jiumiaoMenu));
	pJiumiaoItem->setPosition(ccp(winSize.width - 120, winSize.height - 55));
	CCMenuItemImage *pFireflyItem = CCMenuItemImage::create("ff-1.png", "ff-2.png", this, menu_selector(LoginScene::fireflyMenu));
	pFireflyItem->setPosition(ccp(winSize.width - 45, winSize.height - 55));
	CCMenu *pURLMenu = CCMenu::create(pJiumiaoItem, pFireflyItem, NULL);
	pURLMenu->setPosition(CCPointZero);
	pURLMenu->setAnchorPoint(CCPointZero);
	this->addChild(pURLMenu);

	CCSprite *pLoginInputSprite = CCSprite::createWithSpriteFrameName("login_input.png");
	pLoginInputSprite->setPosition(ccp(winSize.width*0.5, winSize.height*0.5 - 90));
	this->addChild(pLoginInputSprite);
	
	CCMenuItemImage *pLoginBtnItem = CCMenuItemImage::create();
	pLoginBtnItem->setNormalSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("login_login_1.png"));
	pLoginBtnItem->setSelectedSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("login_login_2.png"));
	pLoginBtnItem->setTarget(this, menu_selector(LoginScene::loginMenu));

	CCMenu *pMainMenu = CCMenu::create();
	pMainMenu->alignItemsHorizontally();
	pMainMenu->setPosition(ccp(winSize.width*0.5 - 30, winSize.height*0.5 - 260));
	pMainMenu->setTouchEnabled(true);
	pMainMenu->addChild(pLoginBtnItem);
	pLoginInputSprite->addChild(pMainMenu);

	pUsernameTextField_ = CCTextFieldTTF::textFieldWithPlaceHolder("username", "Arial", 34);
	pUsernameTextField_->setPosition(ccp(winSize.width*0.5 - 10, 96));
	pUsernameTextField_->setFontSize(12);
	pUsernameTextField_->setColor(ccc3(158, 122, 83));
	pUsernameTextField_->attachWithIME();
	pLoginInputSprite->addChild(pUsernameTextField_, 2);

	pPasswordTextField_ = CCTextFieldTTF::textFieldWithPlaceHolder("password", "Arial", 34);
	pPasswordTextField_->setPosition(ccp(winSize.width*0.5 - 22, 45));
	pPasswordTextField_->setFontSize(8);
	pPasswordTextField_->setColor(ccc3(158, 122, 83));
	pLoginInputSprite->addChild(pPasswordTextField_, 2);

	CCLabelTTF *pVersion = CCLabelTTF::create("betallcoffee", "hycc.ttf", 34);
	pVersion->setColor(ccc3(28, 42, 52));
	pVersion->setPosition(ccp(winSize.width*0.5, winSize.height*0.5 - 250));
	this->addChild(pVersion);
}

void LoginScene::jiumiaoMenu(CCObject *pSender) {
}

void LoginScene::fireflyMenu(CCObject *pSender) {
}

void LoginScene::loginMenu(CCObject *pSender) {
	CCLog("login press");
	pLoadingLayer_ = LoadingLayer::create();
	CC_ASSERT(pLoadingLayer_);
	this->addChild(pLoadingLayer_);
	this->schedule(schedule_selector(LoginScene::loginSchedule));
	return;
	if (strcmp(pUsernameTextField_->getString(), "") && strcmp(pPasswordTextField_->getString(), "")) {
		const char *pUsername = pUsernameTextField_->getString();
		const char *pPassword = pPasswordTextField_->getString();

		int i = 0, uIllegal = 0, pIllegal = 0;
		while (pUsername[i] != '\0') {
			if ((pUsername[i] >= '0' && pUsername[i] <= '9') ||
				(pUsername[i] >= 'a' && pUsername[i] <= 'z') ||
				(pUsername[i] >= 'A' && pUsername[i] <= 'Z')) {
				i++;
			} else {
				i++;
				uIllegal++;
			}
		}
		while (pPassword[i] != '\0') {
			if ((pPassword[i] >= '0' && pPassword[i] <= '9') ||
				(pPassword[i] >= 'a' && pPassword[i] <= 'z') ||
				(pPassword[i] >= 'A' && pPassword[i] <= 'Z')) {
				i++;
			} else {
				i++;
				pIllegal++;
			}
		}

		if (uIllegal > 0 || pIllegal > 0){
			CCLog("!");
		} else {
			pLoadingLayer_ = LoadingLayer::create();
			CC_ASSERT(pLoadingLayer_);
			this->addChild(pLoadingLayer_);
//			Json::FastWriter jsonWriter;
//			Json::Value person;
//			person["username"] = pUsername;
//			person["password"] = pPassword;
//			std::string data = jsonWriter.write(person);
//			CCLog("login data : %s", data.c_str());
		//	ETMessage *msg = new ETMessage(101, data);
		//	ETSocketManager::sharedInstance()->getSocketClient()->sendMessage(msg);
			CCLog("login menu send login message.");
			this->schedule(schedule_selector(LoginScene::loginSchedule));
		}
	} else {
		CCLog("username and password empty.");
	}
}

void LoginScene::loginSchedule(float dt) {
	//ETMessage *msg = ETSocketManager::sharedInstance()->getSocketClient()->pickMessage();
	//if (msg != NULL) {
		//std::string content = msg->content();
		//CCLog("login result:%s", content.c_str());
		pLoadingLayer_->removeFromParent();
		pLoadingLayer_ = NULL;
		this->unschedule(schedule_selector(LoginScene::loginSchedule));
		CCDirector::sharedDirector()->replaceScene(IntroAnimateScene::scene());
//	}
}
