/*
 Author : betallcoffee
 */

#include "LoginScene.h"
#include "StartScene.h"

CCScene *StartScene::scene() {
	CCScene *scene;
	do {
		// 'scene' is an autorelease object.
		scene = CCScene::create();
		CC_BREAK_IF(!scene);

		// 'layer' is an autorelease object.
		StartScene *layer = StartScene::create();
		CC_BREAK_IF(!layer);

		// add 'layer' as child to 'scene'
		scene->addChild(layer);
	} while (0);

	return scene;
}

// on 'init' you need to initialize your instance
bool StartScene::init() {
	bool bRet = false;

	do {
		// super init first
		CC_BREAK_IF(!CCLayer::init());

		CCSize winSize = CCDirector::sharedDirector()->getWinSize();

		CCSprite *logo = CCSprite::create("Default.png");
		logo->setPosition(ccp(winSize.width*0.5, winSize.height*0.5));
		this->addChild(logo);

		CCFadeOut *fadeOut = CCFadeOut::create(2.0f);
		CCCallFunc *endCall = CCCallFunc::create(this, SEL_CallFunc(&StartScene::replace));
		CCFiniteTimeAction *action = CCSequence::create(fadeOut, endCall, NULL);
		logo->runAction(action);

	//	ETSocketManager::sharedInstance()->connectToServer();

		bRet = true;
	} while (0);
	
	return bRet;
}

void StartScene::replace() {
	CCDirector::sharedDirector()->replaceScene(LoginScene::scene());
}
