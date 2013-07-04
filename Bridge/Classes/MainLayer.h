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

class MainLayer : public CCLayer, public cocos2d::extension::CCTableViewDataSource, public cocos2d::extension::CCTableViewDelegate {
	CCLayer* bg;
	CCTableView* tableView;
	
public:
	CREATE_FUNC(MainLayer)
    virtual bool init();
	virtual ~MainLayer();
	
    //tableview abstruct
    virtual void scrollViewDidScroll(CCScrollView* view) {};
    virtual void scrollViewDidZoom(CCScrollView* view) {}
    virtual void tableCellTouched(CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
    virtual CCSize cellSizeForTable(CCTableView *table);
    virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(CCTableView *table);
	
private:
	void dismissPopup();
	void popup();
	void goFriends();
	void goMessage();
	void goShop();
	void goSetting();
	void goPlay();
};

#endif /* defined(__Bridge__MainLayer__) */
