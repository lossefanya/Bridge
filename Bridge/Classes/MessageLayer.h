//
//  MessageLayer.h
//  Bridge
//
//  Created by Young One Park on 13. 6. 2..
//
//

#ifndef __Bridge__MessageLayer__
#define __Bridge__MessageLayer__

#include "BridgeHeader.h"

class MessageLayer : public CCLayer {
	
	
public:
	CREATE_FUNC(MessageLayer)
    virtual bool init();
	virtual ~MessageLayer();
};

#endif /* defined(__Bridge__MessageLayer__) */
