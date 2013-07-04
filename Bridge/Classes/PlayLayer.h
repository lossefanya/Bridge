//
//  PlayLayer.h
//  Bridge
//
//  Created by Young One Park on 13. 6. 2..
//
//

#ifndef __Bridge__PlayLayer__
#define __Bridge__PlayLayer__

#include "BridgeHeader.h"

class PlayLayer : public CCLayer {
	CCSprite* bg;
	CCSprite* platform;
	CCPoint leftUpPosition;
	CCPoint leftDownPosition;
	CCPoint rightUpPosition;
	CCPoint rightDownPosition;
	float movingTime;
	
private:
	void leftUp();
	void leftDown();
	void rightUp();
	void rightDown();
	
	void spawn();
	void move(CCNode* obj, void* data);
	void fail(CCNode* obj, void* data);
	void success(CCNode* obj, void* data);
	
	void pop();

public:
	CREATE_FUNC(PlayLayer)
    virtual bool init();
	virtual ~PlayLayer();
	void onEnterTransitionDidFinish();
};

#endif /* defined(__Bridge__PlayLayer__) */
