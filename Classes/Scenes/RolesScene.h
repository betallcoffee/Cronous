/*
 Author : Tina
 */

#ifndef __ROLES_SCENE_H__
#define __ROLES_SCENE_H__

#include "cocos2d.h"

class LoadingLayer;

USING_NS_CC;

class RolesScene : public CCLayer {
public :
	~RolesScene();
	virtual bool init();
	static CCScene *scene();
	CREATE_FUNC(RolesScene);

private :
	void firstRoleMenu(CCObject *pSender);
	void secondRoleMenu(CCObject *pSender);
	void thirdRoleMenu(CCObject *pSender);
	void OKMenu(CCObject *pSender);
	void OKDlgMenu(CCObject *pSender);
	void replace(float dt);

	LoadingLayer *pLoadingLayer_;
	CCLabelTTF *pIntroLabel_;
	CCLabelTTF *pSkillLabel_;
	CCLabelTTF *pNameLabel_;
	CCMenuItemImage *pFirstRoleMenuItem_;
	CCMenuItemImage *pSecondRoleMenuItem_;
	CCMenuItemImage *pThirdRoleMenuItem_;
	CCMenuItemImage *pOKMenuItem_;
	CCSprite *pRoleFocus_;
	CCSprite *pRoleSelected_;
	CCTexture2D *pFirstRoleTexture_;
	CCTexture2D *pSecondRoleTexture_;
	CCTexture2D *pThirdRoleTexture_;

	int selectRole_;
};

#endif // __ROLES_SCENE_H__