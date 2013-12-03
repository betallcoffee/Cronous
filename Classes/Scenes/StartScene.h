/*
 Author : Tina
 */

#ifndef __START_SCENE_H__
#define __START_SCENE_H__

#include "cocos2d.h"
#include "ETSocketManager.h"

USING_NS_CC;

class StartScene : public CCLayer {
public :
	 // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static CCScene* scene();

    // implement the "static node()" method manually
    CREATE_FUNC(StartScene);

private :
	void replace();
};

#endif // __START_SCENE_H__
