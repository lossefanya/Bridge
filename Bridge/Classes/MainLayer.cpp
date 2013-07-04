//
//  MainLayer.cpp
//  Bridge
//
//  Created by Young One Park on 13. 6. 2..
//
//

#include "MainLayer.h"
#include "FriendsLayer.h"
#include "MessageLayer.h"
#include "PlayLayer.h"

bool MainLayer::init()
{
	if (!CCLayer::init()) {
		return false;
	}
	
	//set background
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	
	CCSprite* statusBg = CCSprite::create("u_state_back_01.png");
	
	float gap = statusBg->getContentSize().height / 10;
	
	CCSprite* mainBg = CCSprite::create("u_back_01.png"); //SpriteHelperLoader::createSpriteWithName("p_back_01", "Play", "sprite.pshs");
	
	float width = mainBg->getContentSize().width;
	float height = statusBg->getContentSize().height + gap + mainBg->getContentSize().height;
	float widthScale = winSize.width / width;
	float heightScale = winSize.height / height;
	
	bg = CCLayer::create();
	bg->ignoreAnchorPointForPosition(false);
	bg->setAnchorPoint(ccp(.5, .5));
	bg->setContentSize(CCSize(width, height));
	bg->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	addChild(bg);
	
	if (widthScale > heightScale) bg->setScale(heightScale);
	else bg->setScale(widthScale);

	statusBg->setPosition(ccp(width / 2, height - statusBg->getContentSize().height / 2));
	bg->addChild(statusBg);
	mainBg->setPosition(ccp(width / 2, mainBg->getContentSize().height / 2));
	bg->addChild(mainBg);

	CCSprite* idBg = CCSprite::create("u_state_id_back_01.png");
	idBg->setAnchorPoint(ccp(0, 1));
	idBg->setPosition(RelPos(statusBg, .005, .967));
	statusBg->addChild(idBg);
	
	CCSprite* staminaBg = CCSprite::create("u_state_stamina_back_01.png");
	staminaBg->setAnchorPoint(ccp(0, 0));
	staminaBg->setPosition(RelPos(statusBg, .005, .033));
	statusBg->addChild(staminaBg);
	
	CCSprite* expBg = CCSprite::create("u_state_exp_back_01.png");
	expBg->setAnchorPoint(ccp(1, 1));
	expBg->setPosition(RelPos(statusBg, .995, .967));
	statusBg->addChild(expBg);
	
	CCSprite* cashBg = CCSprite::create("u_state_cash_back_01.png");
	cashBg->setAnchorPoint(ccp(1, 0));
	cashBg->setPosition(RelPos(statusBg, .995, .033));
	statusBg->addChild(cashBg);
	
	CCSprite* levBg = CCSprite::create("u_state_lev_back_01.png");
	levBg->setAnchorPoint(ccp(0, 0));
	levBg->setPosition(ccp(expBg->getPosition().x - expBg->getContentSize().width , cashBg->getPosition().y));
	statusBg->addChild(levBg);

	CCMenu* friendsBtn = Button(CCSprite::create("u_fri_icon_01.png"), menu_selector(MainLayer::popup));
	friendsBtn->setPosition(RelPos(mainBg, .77, .836));
	mainBg->addChild(friendsBtn);
	
	CCMenu* messageBtn = Button(CCSprite::create("u_let_icon_01.png"), menu_selector(MainLayer::popup));
	messageBtn->setPosition(RelPos(mainBg, .906, .836));
	mainBg->addChild(messageBtn);
	
	CCMenu* shopBtn = Button(CCSprite::create("u_shop_icon_01.png"), menu_selector(MainLayer::popup));
	shopBtn->setPosition(RelPos(mainBg, .77, .6));
	mainBg->addChild(shopBtn);

	CCMenu* settingBtn = Button(CCSprite::create("u_fuc_icon_01.png"), menu_selector(MainLayer::popup));
	settingBtn->setPosition(RelPos(mainBg, .906, .6));
	mainBg->addChild(settingBtn);
	
	CCMenu* startBtn = Button(CCSprite::create("u_game_start_01.png"), menu_selector(MainLayer::goPlay));
	startBtn->setPosition(RelPos(mainBg, .85, .245));
	mainBg->addChild(startBtn);
	
	return true;
}

MainLayer::~MainLayer()
{
	
}

void MainLayer::dismissPopup()
{
	getChildByTag(8282)->removeFromParent();
}

void MainLayer::popup()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCLayerColor* screen = CCLayerColor::create(ccc4(0, 0, 0, 100));
	screen->setTag(8282);
	addChild(screen);
	CCLayerColor* popup = CCLayerColor::create(ccc4(255, 255, 255, 255), bg->getContentSize().width * .8, bg->getContentSize().height * .8);
	popup->ignoreAnchorPointForPosition(false);
	popup->setScale(bg->getScale());
	popup->setAnchorPoint(ccp(.5, .5));
	popup->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	screen->addChild(popup);
	CCMenu* exitBtn = Button(CCSprite::create("com_cancel_01.png"), menu_selector(MainLayer::dismissPopup));
	exitBtn->setPosition(RelPos(popup, .9, .9));
	popup->addChild(exitBtn);
	
}

void MainLayer::goFriends()
{
//	CCDirector::sharedDirector()->pushScene(BridgeUtils::wrap(FriendsLayer::create()));
}

void MainLayer::goMessage()
{
//	CCDirector::sharedDirector()->pushScene(BridgeUtils::wrap(MessageLayer::create()));
}

void MainLayer::goShop()
{
	
}

void MainLayer::goSetting()
{
	
}

void MainLayer::goPlay()
{
	CCDirector::sharedDirector()->pushScene(BridgeUtils::wrap(PlayLayer::create()));

}


void MainLayer::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
	
}

CCSize MainLayer::cellSizeForTable(CCTableView *table)
{
	return CCSizeZero;
}

CCTableViewCell* MainLayer::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
	return NULL;
}

unsigned int MainLayer::numberOfCellsInTableView(CCTableView *table)
{
	return 0;
}
