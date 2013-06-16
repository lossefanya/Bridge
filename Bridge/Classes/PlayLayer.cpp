//
//  PlayLayer.cpp
//  Bridge
//
//  Created by Young One Park on 13. 6. 2..
//
//

#include "PlayLayer.h"

static const float gap = 10.0f;

bool PlayLayer::init()
{
	if (!CCLayer::init()) {
		return false;
	}
	
	//set background
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	bg = CCSprite::create("p_back_01.png"); //SpriteHelperLoader::createSpriteWithName("p_back_01", "Play", "sprite.pshs");
	bg->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	this->addChild(bg);
	
	CCSize bgSize = bg->getContentSize();
	
	float widthScale = winSize.width / bgSize.width;
	float heightScale = winSize.height / bgSize.height;
	
	if (widthScale > heightScale) bg->setScale(heightScale);
	else bg->setScale(widthScale);

#define RelPos(x, y) ccp(bgSize.width * x, bgSize.height * y) //relative position
		
	//add parts
	CCSprite* goal = CCSprite::create("p_escape_01.png");
	goal->setPosition(RelPos(.5, .6));
	bg->addChild(goal);
	
	CCSprite* ground = CCSprite::create("p_ground_01.png");
	ground->setPosition(RelPos(.5, .4));
	bg->addChild(ground);
	
	CCMenu *leftUp = CCMenu::createWithItem(CCMenuItemSprite::create(CCSprite::create("p_button_01.png"), NULL, this, menu_selector(PlayLayer::leftUp)));
	leftUp->setPosition(RelPos(.05, .9));
	bg->addChild(leftUp);
	
	CCMenu *leftDown = CCMenu::createWithItem(CCMenuItemSprite::create(CCSprite::create("p_button_01.png"), NULL, this, menu_selector(PlayLayer::leftDown)));
	leftDown->setPosition(RelPos(.05, .1));
	bg->addChild(leftDown);
	
	CCMenu *rightUp = CCMenu::createWithItem(CCMenuItemSprite::create(CCSprite::create("p_button_01.png"), NULL, this, menu_selector(PlayLayer::rightUp)));
	rightUp->setPosition(RelPos(.95, .9));
	bg->addChild(rightUp);
	
	CCMenu *rightDown = CCMenu::createWithItem(CCMenuItemSprite::create(CCSprite::create("p_button_01.png"), NULL, this, menu_selector(PlayLayer::rightDown)));
	rightDown->setPosition(RelPos(.95, .1));
	bg->addChild(rightDown);
	
	platform = CCSprite::create("p_bridge_01.png"); //SpriteHelperLoader::createSpriteWithName("p_bridge_01", "Play", "sprite.pshs");
	platform->setPosition(leftDownPosition);
	bg->addChild(platform);
	
    return true;
}

PlayLayer::~PlayLayer()
{
	
}

void PlayLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
	spawn();
}

void PlayLayer::leftUp()
{
	platform->runAction(CCMoveTo::create(.3, leftUpPosition));
}

void PlayLayer::leftDown()
{
	platform->runAction(CCMoveTo::create(.3, leftDownPosition));
}

void PlayLayer::rightUp()
{
	platform->runAction(CCMoveTo::create(.3, rightUpPosition));
}

void PlayLayer::rightDown()
{
	platform->runAction(CCMoveTo::create(.3, rightDownPosition));
}

void PlayLayer::spawn()
{
    CCSize size = bg->getContentSize();
	CCPoint start;
	int i = (int)(CCRANDOM_0_1()*4);
	switch (i) {
		case 0:
			start = ccp(gap, 105);
			break;
		case 1:
			start = ccp(gap, 180);
			break;
		case 2:
			start = ccp(size.width - gap, 105);
			break;
		case 3:
			start = ccp(size.width - gap, 180);
			break;
		default:
			spawn();
			return;
			break;
	}
	CCSprite* puppy = CCSprite::create("walk001.png"); //SpriteHelperLoader::createSpriteWithName("walk001", "Play", "sprite.pshs");
	puppy->setAnchorPoint(ccp(.5, 0));
	puppy->setPosition(start);
	puppy->setFlipX(start.x == gap);
	bg->addChild(puppy);
	CCAnimation *animation = CCAnimation::create();
	animation->setDelayPerUnit(.5/4);
//	for (int i = 1; i < 5; i++) animation->addSpriteFrame(SpriteHelperLoader::createSpriteWithName(CCString::createWithFormat("walk0%02d", i)->getCString(), "Play", "sprite.pshs")->displayFrame());
	for (int i = 1; i < 5; i++) animation->addSpriteFrameWithFileName(CCString::createWithFormat("walk0%02d.png", i)->getCString());
	CCAnimate *action = CCAnimate::create(animation);
	puppy->runAction(CCRepeatForever::create(action));
	puppy->runAction(CCCallFuncND::create(this, callfuncND_selector(PlayLayer::move), NULL));
	//	puppy->runAction(CCMoveTo::create(5.0, ccp(size.width, 106)));
	//	puppy->runAction(CCSequence::create(CCMoveTo::create(5.0, ccp(abs(start.x - size.width), start.y)),
	//										CCCallFunc::create(this, callfunc_selector(PlayLayer::spawn)),
	//										CCCallFunc::create(puppy, callfunc_selector(CCSprite::removeFromParentAndCleanup)),
	//										NULL));
}

void PlayLayer::move(cocos2d::CCNode *obj, void *data)
{
	float distance = 35;
	float winWidth = bg->getContentSize().width;
	CCSprite *puppy = (CCSprite*)obj;
	CCPoint position = puppy->getPosition();
	
	//fail
	if ((position.x == distance * 3 + gap && (abs(115 - platform->getPosition().x) > 15 || abs(position.y - platform->getPosition().y) > 15)) ||
		(position.x == winWidth - distance * 3 - gap && (abs(284 - platform->getPosition().x) > 15 || abs(position.y - platform->getPosition().y) > 15))) {
		fail(puppy, NULL);
		return;
	}
	
	//success
	if (position.x == distance * 5 + gap || position.x == winWidth - distance * 5 - gap) {
		success(puppy, NULL);
		return;
	}
	
	CCPoint to;
	if (position.x < winWidth / 2) {
		to = ccp(position.x + distance, position.y);
	} else {
		to = ccp(position.x - distance, position.y);
	}
	puppy->runAction(CCSequence::create(CCDelayTime::create(.3),
										CCMoveTo::create(.2, to),
										CCCallFuncND::create(this, callfuncND_selector(PlayLayer::move), NULL),
										NULL));
	
}

void PlayLayer::fail(cocos2d::CCNode *obj, void *data)
{
	CCSprite *puppy = (CCSprite*)obj;
	CCAnimation *animation = CCAnimation::create();
	animation->setDelayPerUnit(.5/4);
//	for (int i = 1; i < 5; i++) animation->addSpriteFrame(SpriteHelperLoader::createSpriteWithName(CCString::createWithFormat("fall0%02d", i)->getCString(), "Play", "sprite.pshs")->displayFrame());
	for (int i = 1; i < 5; i++) animation->addSpriteFrameWithFileName(CCString::createWithFormat("fall0%02d.png", i)->getCString());
	CCAnimate *action = CCAnimate::create(animation);
	puppy->runAction(CCRepeatForever::create(action));
	puppy->runAction(CCSequence::create(CCEaseIn::create(CCMoveTo::create(.5, ccp(puppy->getPosition().x, 0)), 2),
										CCCallFunc::create(puppy, callfunc_selector(CCSprite::removeFromParentAndCleanup)),
										CCCallFunc::create(this, callfunc_selector(PlayLayer::spawn)),
										NULL));
}

void PlayLayer::success(cocos2d::CCNode *obj, void *data)
{
	obj->removeFromParentAndCleanup(true);
	spawn();
}
