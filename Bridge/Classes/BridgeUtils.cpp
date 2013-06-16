//
//  BridgeUtils.cpp
//  Bridge
//
//  Created by Young One Park on 13. 6. 2..
//
//

#include "BridgeUtils.h"

CCSprite* BridgeUtils::blankSprite(CCSize size)
{
	CCSprite *sprite = CCSprite::create();
    GLubyte *buffer = (GLubyte *)malloc(sizeof(GLubyte)*4);
    for (int i=0;i<4;i++) {buffer[i]=255;}
	CCTexture2D *texture = new CCTexture2D;
	texture->autorelease();
	texture->initWithData(buffer, kCCTexture2DPixelFormat_RGB5A1, 1, 1, size);
	sprite->setTexture(texture);
	sprite->setTextureRect(CCRect(0, 0, size.width, size.height));
	sprite->setOpacity(30);
	free(buffer);
	return sprite;
}

CCScene* BridgeUtils::wrap(CCLayer *layer)
{
	layer->setTag(1917);
	CCScene *scene = CCScene::create();
	scene->addChild(layer);
	return scene;
}
