//
//  BridgeHeader.h
//  Bridge
//
//  Created by Young One Park on 13. 6. 2..
//
//

#ifndef Bridge_BridgeHeader_h
#define Bridge_BridgeHeader_h

#include "cocos2d.h"
#include "cocos-ext.h"
#include "BridgeUtils.h"
#include "SpriteHelperLoader.h"

USING_NS_CC;
USING_NS_CC_EXT;

#define RelPos(p, x, y) ccp(p->getContentSize().width * x, p->getContentSize().height * y) //relative position
#define Button(sprite, selector) CCMenu::createWithItem(CCMenuItemSprite::create(sprite, NULL, this, selector))

#endif
