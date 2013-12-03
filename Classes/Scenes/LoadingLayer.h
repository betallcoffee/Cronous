/*
 Author : Tina
 */

#ifndef __LOADING_LAYER_H__
#define __LOADING_LAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class LoadingLayer : public CCLayerColor {
public :
	~LoadingLayer();

	 // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

	// implement the touch event delegate function;
	virtual void registerWithTouchDispatcher();

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

    // implement the "static node()" method manually
    CREATE_FUNC(LoadingLayer);

private :
	CCRepeatForever *pLoadingRepeat_;

};

#endif // __LOADING_LAYER_H_