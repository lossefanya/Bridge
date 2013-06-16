//
//  MessageLayer.cpp
//  Bridge
//
//  Created by Young One Park on 13. 6. 2..
//
//

#include "MessageLayer.h"

bool MessageLayer::init()
{
	if (!CCLayer::init()) {
		return false;
	}
	
	return true;
}

MessageLayer::~MessageLayer()
{
	
}