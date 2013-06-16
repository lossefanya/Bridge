//
//  BridgeAppDelegate.cpp
//  Bridge
//
//  Created by Young One Park on 13. 6. 6..
//  Copyright __MyCompanyName__ 2013년. All rights reserved.
//

#include "AppDelegate.h"

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "BridgeUtils.h"
#include "PlayLayer.h"

USING_NS_CC;
using namespace CocosDenshion;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

    CCSize screenSize = CCEGLView::sharedOpenGLView()->getFrameSize();
    float screenRatio = screenSize.width/screenSize.height; // 화면비율
    CCSize designSize = CCSizeMake(320, 320/screenRatio); //width 값 의미없음.
	CCEGLView::sharedOpenGLView()->setDesignResolutionSize(designSize.width, designSize.height, kResolutionNoBorder);

	std::vector<std::string> searchPaths;
	if (screenSize.height > 480) {
		CCSize resourceSize = CCSizeMake(640, 640/screenRatio);
		searchPaths.push_back("hd");
		searchPaths.push_back("");
		CCDirector::sharedDirector()->setContentScaleFactor(resourceSize.height/designSize.height);
	} else {
		CCSize resourceSize = CCSizeMake(320, 320/screenRatio);
		searchPaths.push_back("sd");
		searchPaths.push_back("");
		CCDirector::sharedDirector()->setContentScaleFactor(resourceSize.height/designSize.height);
	}
	CCFileUtils::sharedFileUtils()->setSearchPaths(searchPaths);

	
	pDirector->runWithScene(BridgeUtils::wrap(PlayLayer::create()));

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->pauseAllEffects();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->resumeAllEffects();
}
