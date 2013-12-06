/*
 Author : betallcoffee
 */

#ifndef __HOME_SCENE_H__
#define __HOME_SCENE_H__

#include "cocos2d.h"

class LevelMapLayer;
class StatusBarLayer;
class FightLayer;
class PersonalLayer;

USING_NS_CC;

class HomeScene : public CCLayer {
public :
	~HomeScene();
	virtual bool init();
	static CCScene *scene();
	CREATE_FUNC(HomeScene);

private :
	void initTitle();
	void initLevelBtn();
	void initStatusBar();
	void initTabBar();

	void composeMenu(CCObject *pSender);
	void friendsMenu(CCObject *pSender);
	void personalMenu(CCObject *pSender);
	void fightMenu(CCObject *pSender);
	void mailMenu(CCObject *pSender);
	void homeMenu(CCObject *pSender);
	void rechargeMenu(CCObject *pSender);

	CCMenuItemImage *pComposeMenuItem_;
    CCMenuItemImage *pFriendsMenuItem_;
	CCMenuItemImage *pPersonalMenuItem_;
	CCMenuItemImage *pRechargeMenuItem_;
	CCMenuItemImage *pHomeMenuItem_;
	CCMenuItemImage *pMailMenuItem_;
    CCMenuItemImage *pFightMenuItem_;
    CCMenu *pTabMenus_;

	LevelMapLayer *pLevelMapLayer_;
	StatusBarLayer *pStatusBarLayer_;
	FightLayer *pFightLayer_;
	PersonalLayer *pPersonalLayer_;

	CCLayer *pCurLayer_;
};

#endif // __HOME_SCENE_H__
