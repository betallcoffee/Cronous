/*
 Author : betallcoffee
 */

#include "RolesScene.h"
#include "LoadingLayer.h"
#include "HomeScene.h"

RolesScene::~RolesScene() {
	pRoleFocus_->release();
	CCTextureCache::sharedTextureCache()->removeTextureForKey("selectrole_bkg.png");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("common_pop_text_bkg.png");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("qs_0001.png");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("qs_0002.png");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("qs_0003.png");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("common_pop_bkg.png");
}

CCScene *RolesScene::scene() {
	CCScene *scene;

	do {
		scene = CCScene::create();
		CC_BREAK_IF(scene == NULL);

		RolesScene *layer = RolesScene::create();
		CC_BREAK_IF(layer == NULL);

		scene->addChild(layer);
	} while(false);

	return scene;
}

bool RolesScene::init() {
	bool bRet = false;

	do {
		CC_BREAK_IF(!CCLayer::init());

		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		CCSprite *pBackground = CCSprite::create("selectrole_bkg.png");
		pBackground->setPosition(ccp(winSize.width/2, winSize.height/2));
		this->addChild(pBackground);

		pOKMenuItem_ = CCMenuItemImage::create("common_btn_ok_1.png",
			"common_btn_ok_2.png",
			"common_btn_ok_3.png",
			this,
			menu_selector(RolesScene::OKMenu));
		CCMenu *pOKMenu = CCMenu::create(pOKMenuItem_, NULL);
		pOKMenu->setPosition(winSize.width/2, 100);
		this->addChild(pOKMenu);

		pIntroLabel_ = CCLabelTTF::create("Fuck Fuck Fuck Fuck", 
			"hycc.ttf",
			23,
			CCSizeMake(450, 58),
			kCCTextAlignmentCenter);
		pIntroLabel_->setAnchorPoint(ccp(0, 0));
		pIntroLabel_->setPosition(ccp(50, 245));
		pIntroLabel_->setColor(ccc3(134, 105, 59));
		pIntroLabel_->setDimensions(CCSizeMake(300, 0));
		pIntroLabel_->setHorizontalAlignment(kCCTextAlignmentLeft);
		pIntroLabel_->setVerticalAlignment(kCCVerticalTextAlignmentTop);
		this->addChild(pIntroLabel_);

		pFirstRoleMenuItem_ = CCMenuItemImage::create("common_item_bkg.png",
			"common_item_bkg1.png",
			this,
			menu_selector(RolesScene::firstRoleMenu));
		pFirstRoleMenuItem_->setScale(1.0);
		CCSize roleSize = pFirstRoleMenuItem_->getContentSize();
		CCSprite *pRole = CCSprite::create("qs_0001.png");
		pRole->setAnchorPoint(ccp(0.5, 0.5));
		pRole->setScale(0.18);
		pRole->setPosition(ccp(roleSize.width/2, roleSize.height/2));
		pFirstRoleMenuItem_->addChild(pRole);

		pSecondRoleMenuItem_ = CCMenuItemImage::create("common_item_bkg.png",
			"common_item_bkg1.png",
			this,
			menu_selector(RolesScene::secondRoleMenu));
		pSecondRoleMenuItem_->setScale(1.0);
		roleSize = pSecondRoleMenuItem_->getContentSize();
		pRole = CCSprite::create("qs_0002.png");
		pRole->setAnchorPoint(ccp(0.5, 0.5));
		pRole->setScale(0.18);
		pRole->setPosition(ccp(roleSize.width/2, roleSize.height/2));
		pSecondRoleMenuItem_->addChild(pRole);

		pThirdRoleMenuItem_ = CCMenuItemImage::create("common_item_bkg.png",
			"common_item_bkg1.png",
			this,
			menu_selector(RolesScene::thirdRoleMenu));
		pThirdRoleMenuItem_->setScale(1.0);
		roleSize = pThirdRoleMenuItem_->getContentSize();
		pRole = CCSprite::create("qs_0003.png");
		pRole->setAnchorPoint(ccp(0.5, 0.5));
		pRole->setScale(0.18);
		pRole->setPosition(ccp(roleSize.width/2, roleSize.height/2));
		pThirdRoleMenuItem_->addChild(pRole);

		CCMenu *pRoleMenus = CCMenu::create(pFirstRoleMenuItem_,
			pSecondRoleMenuItem_,
			pThirdRoleMenuItem_, NULL);
		pRoleMenus->alignItemsHorizontallyWithPadding(30);
		pRoleMenus->setPosition(ccp(winSize.width/2, winSize.height/2 - 218));
		this->addChild(pRoleMenus);

		pRoleFocus_ = CCSprite::create("common_item_bkg.png");
		pRoleFocus_->retain();
		pRoleFocus_->setScale(1.0);

		pRoleSelected_ = CCSprite::create("qs_0001.png");
		pRoleSelected_->setPosition(ccp(winSize.width/2, winSize.height/2 + 100));
		this->addChild(pRoleSelected_);

		pFirstRoleTexture_ = CCTextureCache::sharedTextureCache()->addImage("qs_0001.png");
		pSecondRoleTexture_ = CCTextureCache::sharedTextureCache()->addImage("qs_0002.png");
		pThirdRoleTexture_ = CCTextureCache::sharedTextureCache()->addImage("qs_0003.png");

		selectRole_ = 0;
		bRet = true;
	} while (false);

	return bRet;
}

void RolesScene::firstRoleMenu(CCObject *pSender) {
	if (selectRole_ == 1) {
		return;
	}
	pIntroLabel_->setString("�����ʥ����ɮ��ӵ�и�����߷���");
	CCSize size = pFirstRoleMenuItem_->getContentSize();
	pRoleFocus_->removeFromParent();
	pRoleFocus_->setPosition(ccp(size.width/2, size.height/2));
	pFirstRoleMenuItem_->addChild(pRoleFocus_, 1);
	pRoleSelected_->setTexture(pFirstRoleTexture_);
	selectRole_ = 1;
}

void RolesScene::secondRoleMenu(CCObject *pSender) {
	if (selectRole_ == 2) {
		return;
	}
	pIntroLabel_->setString("����֮������սʿ��ӵ�и߹���");
	CCSize size = pSecondRoleMenuItem_->getContentSize();
	pRoleFocus_->removeFromParent();
	pRoleFocus_->setPosition(ccp(size.width/2, size.height/2));
	pSecondRoleMenuItem_->addChild(pRoleFocus_, 1);
	pRoleSelected_->setTexture(pSecondRoleTexture_);
	selectRole_ = 2;
}

void RolesScene::thirdRoleMenu(CCObject *pSender) {
	if (selectRole_ == 3) {
		return;
	}
	pIntroLabel_->setString("��ħͳ˧����ʿ��ӵ�и��ٶȣ������ֹ���");
	CCSize size = pThirdRoleMenuItem_->getContentSize();
	pRoleFocus_->removeFromParent();
	pRoleFocus_->setPosition(ccp(size.width/2, size.height/2));
	pThirdRoleMenuItem_->addChild(pRoleFocus_, 1);
	pRoleSelected_->setTexture(pThirdRoleTexture_);
	selectRole_ = 3;
}

void RolesScene::OKMenu(CCObject *pSender) {
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCSprite *pDialog = CCSprite::create("common_pop_bkg.png");
	pDialog->setPosition(ccp(winSize.width/2, winSize.height/2));
	this->addChild(pDialog, 3);
	CCSize dlgSize = pDialog->getContentSize();

	CCLabelTTF *pRoleNameLabel = CCLabelTTF::create("Nick Name", "hzgb.ttf", 25);
	pRoleNameLabel->setPosition(ccp(dlgSize.width/2 + 1, dlgSize.height/2 - 39));
	pRoleNameLabel->setColor(ccc3(27, 18, 6));
	pDialog->addChild(pRoleNameLabel, 6);

	CCLabelTTF *pRoleNameLabelt= CCLabelTTF::create("Nick Name", "hzgb.ttf", 25);
	pRoleNameLabelt->setPosition(ccp(dlgSize.width/2 - 1, dlgSize.height/2 - 38));
	pRoleNameLabelt->setColor(ccc3(236, 190, 108));
	pDialog->addChild(pRoleNameLabelt, 6);

	CCMenuItemImage *pOKDlgMenuItem = CCMenuItemImage::create("common_btn_ok_1.png",
			"common_btn_ok_2.png",
			"common_btn_ok_3.png",
			this,
			menu_selector(RolesScene::OKDlgMenu));
	pOKDlgMenuItem->setScale(1.3);
	CCMenu *pOKDlgMenu = CCMenu::create(pOKDlgMenuItem, NULL);
	pOKDlgMenu->setPosition(dlgSize.width/2, 70);
	pDialog->addChild(pOKDlgMenu, 4);
}

void RolesScene::OKDlgMenu(CCObject *pSender) {
	pLoadingLayer_ = LoadingLayer::create();
	CC_ASSERT(pLoadingLayer_);
	this->addChild(pLoadingLayer_);
	this->scheduleOnce(schedule_selector(RolesScene::replace), 1.0);
}

void RolesScene::replace(float dt) {
	pLoadingLayer_->removeFromParent();
	pLoadingLayer_ = NULL;
	CCDirector::sharedDirector()->replaceScene(HomeScene::scene());
}
