//
//  BridgeUtils.h
//  Bridge
//
//  Created by Young One Park on 13. 6. 2..
//
//

#ifndef __Bridge__BridgeUtils__
#define __Bridge__BridgeUtils__

#include "cocos2d.h"

using namespace cocos2d;

class BridgeUtils {
	
	
public:
	static CCSprite* blankSprite(CCSize size);
	static CCScene* wrap(CCLayer *layer);
};
#endif /* defined(__Bridge__BridgeUtils__) */
