/*
 Author : betallcoffee
 */

#ifndef __LOGIN_SCENE_H__
#define __LOGIN_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class LoadingLayer;

class LoginScene : public CCLayer {
public :
	 // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static CCScene* scene();

    // implement the "static node()" method manually
    CREATE_FUNC(LoginScene);

private :
	void initUI();
	void loadRes();

	void jiumiaoMenu(CCObject *pSender);
	void fireflyMenu(CCObject *pSender);
	void loginMenu(CCObject *pSender);

	void loginSchedule(float dt);

	CCEditBox *pUsernameEditBox_;
	CCEditBox *pPasswordEditBox_;

	LoadingLayer *pLoadingLayer_;
};

#endif // __LOGIN_SCENE_H__
