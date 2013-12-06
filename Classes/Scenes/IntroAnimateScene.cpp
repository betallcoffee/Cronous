/*
 Author : betallcoffee
 */

#include "IntroAnimateScene.h"
#include "RolesScene.h"

IntroAnimateScene::~IntroAnimateScene() {
	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("guild.plist");
	CCTextureCache::sharedTextureCache()->removeTextureForKey("guild.png");
}

CCScene *IntroAnimateScene::scene() {
	CCScene *scene;
	do {
		scene = CCScene::create();
		CC_BREAK_IF(scene == NULL);

		IntroAnimateScene *layer = IntroAnimateScene::create();
		CC_BREAK_IF(layer == NULL);

		scene->addChild(layer);
	} while (false);
	return scene;
}

bool IntroAnimateScene::init() {
	bool bRet = false;
	do {
		CC_BREAK_IF(!CCLayer::init());
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		CCSpriteFrameCache *pSpriteFrameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
		pSpriteFrameCache->addSpriteFramesWithFile("guild.plist");
		
		char bgkName[] = "bgk1.png";
		char wordName[] = "words0.png";
		bgks_[0] = CCSprite::createWithSpriteFrame(pSpriteFrameCache->spriteFrameByName(bgkName));
		bgks_[0]->setPosition(ccp(winSize.width/2, winSize.height/2));
		bgks_[0]->setVisible(false);
		this->addChild(bgks_[0]);

		words_[0] = CCSprite::createWithSpriteFrame(pSpriteFrameCache->spriteFrameByName(wordName));
		words_[0]->setPosition(ccp(winSize.width/2 - 60, winSize.height/2 + 160));
		words_[0]->setVisible(false);
		this->addChild(words_[0]);
		
		for (int i = 1; i < kNumOfBgk && i < kNumOfWord; i++) {
			char c = '0';
			wordName[5] = c + i;
			words_[i] = CCSprite::createWithSpriteFrame(pSpriteFrameCache->spriteFrameByName(wordName));
			words_[i]->setPosition(ccp(winSize.width/2 - 60, winSize.height/2 + 160));
			words_[i]->setVisible(false);
			this->addChild(words_[i]);

			bgkName[3] = c + i + 1;
			bgks_[i] = CCSprite::createWithSpriteFrame(pSpriteFrameCache->spriteFrameByName(bgkName));
			bgks_[i]->setPosition(ccp(winSize.width/2, winSize.height/2));
			bgks_[i]->setVisible(false);
			this->addChild(bgks_[i]);
		}
		bgks_[0]->setVisible(true);
		words_[1]->setPosition(ccp(winSize.width/2 - 10, winSize.height/2 + 90));

		isFirst_ = true;
		CCActionInterval *fadeIn = CCFadeIn::create(1.5);
		CCCallFunc *func = CCCallFunc::create(this, callfunc_selector(IntroAnimateScene::animateOneCallFunc));
		CCFiniteTimeAction *sequence = CCSequence::create(fadeIn, func, NULL);
		bgks_[0]->runAction(sequence);

		bRet = true;
	} while (false);
	return bRet;
}

void IntroAnimateScene::animateOneCallFunc() {
	if (isFirst_) {
		CCSprite *sprite = words_[0];
		sprite->setVisible(true);
		CCActionInterval *fadeIn = CCFadeIn::create(2.0);
		sprite->runAction(fadeIn);
		CCActionInterval *fadeOut = CCFadeOut::create(0.7);
		CCActionInterval *dely = CCDelayTime::create(0.7);
		CCActionInterval *moveTo = CCMoveTo::create(0.7, 
			ccp(sprite->getPosition().x, sprite->getPosition().y));
		CCCallFunc *func = CCCallFunc::create(this, callfunc_selector(IntroAnimateScene::animateOneCallFunc));
		CCFiniteTimeAction *sequence = CCSequence::create(fadeOut,
			dely,
			moveTo,
			func, NULL);
		isFirst_ = false;
		sprite->runAction(sequence);
	} else {
		CCSprite *sprite = words_[1];
		sprite->setVisible(true);
		CCActionInterval *delay = CCDelayTime::create(1.5);
		CCActionInterval *moveTo = CCMoveTo::create(0.7, 
			ccp(sprite->getPosition().x, sprite->getPosition().y));
		CCActionInterval *fadeOut = CCFadeOut::create(0.1);
		CCCallFunc *func = CCCallFunc::create(this, callfunc_selector(IntroAnimateScene::animateTwoCallFunc));
		CCFiniteTimeAction *sequence = CCSequence::create(delay,
			moveTo,
			fadeOut,
			func, NULL);
		sprite->runAction(sequence);
	}
}

void IntroAnimateScene::animateTwoCallFunc() {
	CCActionInterval *fadeOut = CCFadeOut::create(1.0);
	bgks_[0]->runAction(fadeOut);
	bgks_[1]->setVisible(true);
	CCActionInterval *fadeIn = CCFadeIn::create(1.0);
	bgks_[1]->runAction(fadeIn);

	CCSprite *sprite = words_[2];
	sprite->setVisible(true);
	CCActionInterval *delay = CCDelayTime::create(1.5);
	CCActionInterval *moveTo = CCMoveTo::create(0.7, 
		ccp(sprite->getPosition().x, sprite->getPosition().y));
	fadeOut = CCFadeOut::create(1.5);
	CCCallFunc *func = CCCallFunc::create(this, callfunc_selector(IntroAnimateScene::animateThreeCallFunc));
	CCFiniteTimeAction *sequence = CCSequence::create(delay, 
		moveTo,
		fadeOut,
		func, NULL);
	sprite->runAction(sequence);
}

void IntroAnimateScene::animateThreeCallFunc() {
	CCActionInterval *fadeOut = CCFadeOut::create(1.0);
	bgks_[1]->runAction(fadeOut);
	bgks_[2]->setVisible(true);
	CCActionInterval *fadeIn = CCFadeIn::create(2.5);
	bgks_[2]->runAction(fadeIn);

	CCSprite *sprite = words_[3];
	sprite->setVisible(true);
	CCActionInterval *delay = CCDelayTime::create(1.5);
	fadeOut = CCFadeOut::create(2);
	CCCallFunc *func = CCCallFunc::create(this, callfunc_selector(IntroAnimateScene::animateFourCallFunc));
	CCFiniteTimeAction *sequence = CCSequence::create(delay,
		fadeOut,
		func, NULL);
	sprite->runAction(sequence);
}

void IntroAnimateScene::animateFourCallFunc() {
	CCActionInterval *fadeOut = CCFadeOut::create(2.0);
	bgks_[2]->runAction(fadeOut);
	
	CCSprite *sprite = bgks_[3];
	sprite->setVisible(true);
	CCActionInterval *fadeIn = CCFadeIn::create(1.0);
	sprite->runAction(fadeIn);
	CCActionInterval *delay = CCDelayTime::create(2.0);
	fadeOut = CCFadeOut::create(2.5);
	CCCallFunc *func = CCCallFunc::create(this, callfunc_selector(IntroAnimateScene::selectRoleCallFunc));
	CCFiniteTimeAction *sequence = CCSequence::create(delay,
		fadeOut,
		func, NULL);
	sprite->runAction(sequence);
}

void IntroAnimateScene::selectRoleCallFunc() {
	CCDirector::sharedDirector()->replaceScene(RolesScene::scene());
}

void IntroAnimateScene::selectRoleMenu(CCObject *pSender) {
	this->selectRoleCallFunc();
}

