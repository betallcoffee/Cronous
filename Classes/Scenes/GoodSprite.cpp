/*
 * GoodSprite.cpp
 *
 *  Created on: Dec 6, 2013
 *      Author: betallcoffee
 */

#include "GoodSprite.h"

GoodSprite::GoodSprite()
: pBackground_(NULL),
  pDataSprite_(NULL){

}

GoodSprite::~GoodSprite() {
}

bool GoodSprite::init() {
	bool bRet = false;

	do {
		CC_BREAK_IF(!CCSprite::init());

		pBackground_ = CCSprite::create("common_item_bkg.png");
		pBackground_->setAnchorPoint(CCPointZero);
		this->addChild(pBackground_);
		this->setContentSize(pBackground_->getContentSize());

		bRet = true;
	} while (false);

	return bRet;
}

