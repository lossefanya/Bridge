//
//  MainLayer.h
//  Bridge
//
//  Created by Young One Park on 13. 6. 2..
//
//

#ifndef __Bridge__MainLayer__
#define __Bridge__MainLayer__

#include "BridgeHeader.h"

class MainLayer : public CCLayer {
	
	
public:
	CREATE_FUNC(MainLayer)
    virtual bool init();
	virtual ~MainLayer();
};

#endif /* defined(__Bridge__MainLayer__) */