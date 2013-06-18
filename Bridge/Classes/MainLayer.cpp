//
//  MainLayer.cpp
//  Bridge
//
//  Created by Young One Park on 13. 6. 2..
//
//

#include "MainLayer.h"

#define RelPos(x, y) ccp(bg->getContentSize().width * x, bg->getContentSize().height * y) //relative position

bool MainLayer::init()
{
	if (!CCLayer::init()) {
		return false;
	}
	
	//set background
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	bg = CCSprite::create("u_back_01.png"); //SpriteHelperLoader::createSpriteWithName("p_back_01", "Play", "sprite.pshs");
	bg->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	this->addChild(bg);
	
	CCSize bgSize = bg->getContentSize();
	
	float widthScale = winSize.width / bgSize.width;
	float heightScale = winSize.height / bgSize.height;
	
	if (widthScale > heightScale) bg->setScale(heightScale);
	else bg->setScale(widthScale);

	return true;
}

MainLayer::~MainLayer()
{
	
}