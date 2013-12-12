/*
 * GoodSprite.h
 *
 *  Created on: Dec 6, 2013
 *      Author: betallcoffee
 */

#ifndef __GOOD_SPRITE_H__
#define __GOOD_SPRITE_H__

#include "cocos2d.h"

USING_NS_CC;

class GoodSprite: public CCSprite {
public :
	GoodSprite();
	virtual ~GoodSprite();
	virtual bool init();
	CREATE_FUNC(GoodSprite);

private :
	CCSprite *pBackground_;
	CCSprite *pDataSprite_;
};

#endif /* __GOOD_SPRITE_H__ */
