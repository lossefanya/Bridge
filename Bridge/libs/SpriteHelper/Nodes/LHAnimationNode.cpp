//  This file was generated by LevelHelper
//  http://www.levelhelper.org
//
//  LevelHelperLoader.mm
//  Created by Bogdan Vladu
//  Copyright 2011 Bogdan Vladu. All rights reserved.
////////////////////////////////////////////////////////////////////////////////
//
//  This software is provided 'as-is', without any express or implied
//  warranty.  In no event will the authors be held liable for any damages
//  arising from the use of this software.
//  Permission is granted to anyone to use this software for any purpose,
//  including commercial applications, and to alter it and redistribute it
//  freely, subject to the following restrictions:
//  The origin of this software must not be misrepresented; you must not
//  claim that you wrote the original software. If you use this software
//  in a product, an acknowledgment in the product documentation would be
//  appreciated but is not required.
//  Altered source versions must be plainly marked as such, and must not be
//  misrepresented as being the original software.
//  This notice may not be removed or altered from any source distribution.
//  By "software" the author refers to this code file and not the application
//  that was used to generate this file.
//
////////////////////////////////////////////////////////////////////////////////
#include "LHAnimationNode.h"
#include "SpriteHelperLoader.h"
#include "LHSettings.h"
#include "../Utilities/LHDictionary.h"
#include "../Utilities/LHArray.h"
#include "../Utilities/LHObject.h"
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
bool LHAnimationFrameInfo::initWithDictionary(LHDictionary* dictionary, LHSprite* sprite){
    
    if(NULL == dictionary)
        return false;
    
    delayPerUnit = dictionary->floatForKey("delayPerUnit");
    offset = dictionary->pointForKey("offset");
    
    notifications = NULL;
    
    if(dictionary->objectForKey("notifications"))
        notifications= new LHDictionary(dictionary->dictForKey("notifications"));
    
    spriteframeName = std::string(dictionary->stringForKey("spriteframe"));
    
    rect = dictionary->rectForKey("Frame");
    rect = CC_RECT_POINTS_TO_PIXELS(rect);
    
    rect = LHSettings::sharedInstance()->transformedTextureRect(rect, sprite->getImageFile());
    
    spriteFrameOffset = dictionary->pointForKey("TextureOffset");
    spriteFrameOffset.x *= CC_CONTENT_SCALE_FACTOR();
    spriteFrameOffset.y *= CC_CONTENT_SCALE_FACTOR();
    
    if(LHSettings::sharedInstance()->isHDImage(sprite->getImageFile())){
        spriteFrameOffset.x *= 2.0f;
        spriteFrameOffset.y *= 2.0f;
    }
    
    
    CCPoint tempOffset = spriteFrameOffset;
    
    tempOffset.x += offset.x;
    tempOffset.y -= offset.y;
    
    offset = tempOffset;
    
    rectIsRotated   = dictionary->boolForKey("IsRotated");
    
    spriteFrameSize = dictionary->sizeForKey("SpriteSize");
    spriteFrameSize.width *= CC_CONTENT_SCALE_FACTOR();
    spriteFrameSize.height*= CC_CONTENT_SCALE_FACTOR();
    
    if(LHSettings::sharedInstance()->isHDImage(sprite->getImageFile())){
        spriteFrameSize.width *= 2.0f;
        spriteFrameSize.height*= 2.0f;
    }

    
    return true;
}
//------------------------------------------------------------------------------
LHAnimationFrameInfo::~LHAnimationFrameInfo(){
    CCLog("LHSpriteFrame Dealloc %s\n", spriteframeName.c_str());
    delete notifications;
}
//------------------------------------------------------------------------------
LHAnimationFrameInfo::LHAnimationFrameInfo(){
    notifications = NULL;
}
//------------------------------------------------------------------------------
LHAnimationFrameInfo* LHAnimationFrameInfo::frameWithDictionary(LHDictionary* dictionary, LHSprite* sprite){
    
    LHAnimationFrameInfo *pobNode = new LHAnimationFrameInfo();
	if (pobNode && pobNode->initWithDictionary(dictionary, sprite))
    {
	    pobNode->autorelease();
        return pobNode;
    }
    CC_SAFE_DELETE(pobNode);
	return NULL;
    
}
//------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
LHAnimationNode::~LHAnimationNode()
{
    CCLog("LH Animation Dealloc %s %p", uniqueName.c_str(), this);
    delete frames;
    activeFrame = NULL;
}
////////////////////////////////////////////////////////////////////////////////
LHAnimationNode::LHAnimationNode(LHDictionary* dictionary, LHSprite* spr){
    
    frames= NULL;
    sprite= NULL;
    activeFrame= NULL;
    oldBatch= NULL;
    oldTexture= NULL;
    
    //this info will be from the spritehelper document
    //the info from the level is loaded by LHSprite
    
    uniqueName  = std::string(dictionary->stringForKey("UniqueName"));
    sheetName   = std::string(dictionary->stringForKey("SheetName"));
    restoreOriginalFrame = dictionary->boolForKey("RestoreOriginalFrame");
    repetitions = dictionary->intForKey("Repetitions");
    delayPerUnit= dictionary->floatForKey("DelayPerUnit");
    loop = dictionary->boolForKey("Loop");
    sprite = spr;
    oldRect = sprite->getTextureRect();
    
#if COCOS2D_VERSION >= 0x00020000
    oldSpriteFrame = sprite->displayFrame();
#else
    oldSpriteFrame = sprite->displayedFrame();
#endif
    oldSpriteFrame->retain();
    
    repetitionsPerformed = 0;
    currentFrame = 0;
    elapsedFrameTime = 0.0f;
    LHArray* framesInfo = dictionary->arrayForKey("Frames");
    
#if COCOS2D_VERSION >= 0x00020000
    frames = CCArray::create();
#else
    frames = CCArray::array();
#endif
    
    frames->retain();
    
    for(int i = 0; i< framesInfo->count(); ++i){
        
        LHDictionary* frmInfo = framesInfo->dictAtIndex(i);
        frames->addObject(LHAnimationFrameInfo::frameWithDictionary(frmInfo, sprite));
    }
    
    paused = true;
}
////////////////////////////////////////////////////////////////////////////////
void LHAnimationNode::setActiveFrameTexture()
{
    if(NULL == activeFrame) return;
    
#if COCOS2D_VERSION >= 0x00020100 || COCOS2D_VERSION == 0x00020003
    CCSpriteFrame* sprFrame = CCSpriteFrame::createWithTexture(sprite->getTexture(),
                                                               activeFrame->getRect(),
                                                               activeFrame->getRectIsRotated(),
                                                               activeFrame->getOffset(),
                                                               sprite->getContentSize());    
#elif COCOS2D_VERSION == 0x00020000
    CCSpriteFrame* sprFrame = CCSpriteFrame::create(sprite->getTexture(),
                                                    activeFrame->getRect(),
                                                    activeFrame->getRectIsRotated(),
                                                    activeFrame->getOffset(),
                                                    sprite->getContentSize());
#else
    CCSpriteFrame* sprFrame = CCSpriteFrame::frameWithTexture(sprite->getTexture(),
                                                              activeFrame->getRect(),
                                                              activeFrame->getRectIsRotated(),
                                                              activeFrame->getOffset(),
                                                              sprite->getContentSize());
#endif
    sprite->setDisplayFrame(sprFrame);
}

void LHAnimationNode::update(float dt)
{
    if(!activeFrame)
    {
        CCLog("ERROR: No active frame found in animation %s on sprite %s", uniqueName.c_str(), sprite->getUniqueName().c_str());
        return;
    }
    
    if(paused)
        return;
    
    elapsedFrameTime += dt;
    
    bool endedNotif = false;
    bool endedRep = false;
    bool frameChanged = false;
    
    if(activeFrame->getDelayPerUnit()*delayPerUnit <= elapsedFrameTime){
        elapsedFrameTime = 0.0f;
        ++currentFrame;
        
        if(currentFrame >= (int)frames->count()){
            
            //we should trigger a notification that the animation has ended
            endedNotif = true;
            if(loop){
                currentFrame = 0;
            }
            else
            {
                
                ++repetitionsPerformed;
                
                if(repetitionsPerformed >= repetitions)
                {
                    paused = true;
                    currentFrame = frames->count() -1;
                    endedRep = true;
                }
                else {
                    
                    if(restoreOriginalFrame || repetitionsPerformed < repetitions){
                        currentFrame = 0;
                    }
                    else {
                        currentFrame = frames->count() -1;
                    }
                }
            }
        }
        
        setFrame(currentFrame);
        frameChanged = true;
    }
    
    if(endedNotif){
        
#if COCOS2D_VERSION >= 0x00020100 || COCOS2D_VERSION == 0x00020003
        cocos2d::CCNotificationCenter::sharedNotificationCenter()->postNotification(LHAnimationHasEndedNotification, sprite);
#elif COCOS2D_VERSION == 0x00020000
        cocos2d::extension::CCNotificationCenter::sharedNotificationCenter()->postNotification(LHAnimationHasEndedNotification, sprite);
#else
        CCNotificationCenter::sharedNotifCenter()->postNotification(LHAnimationHasEndedNotification, sprite);
#endif
        
        if(endedRep){
            sprite->stopAnimation();

#if COCOS2D_VERSION >= 0x00020100 || COCOS2D_VERSION == 0x00020003
        cocos2d::CCNotificationCenter::sharedNotificationCenter()->postNotification(LHAnimationHasEndedAllRepetitionsNotification, sprite);
            
#elif COCOS2D_VERSION == 0x00020000
            
            cocos2d::extension::CCNotificationCenter::sharedNotificationCenter()->postNotification(LHAnimationHasEndedAllRepetitionsNotification, sprite);
            
#else
            
            CCNotificationCenter::sharedNotifCenter()->postNotification(LHAnimationHasEndedAllRepetitionsNotification, sprite);
#endif
            return;//animation is removed so dont go any further or else exc_bad_access since all objets are released
        }
    }
    
    
    if(frameChanged)
    {
        //check if this frame has any info and trigger a notification if it has
        //we dont trigger frame changed notifications for every frame because
        //it may impact performance - we trigger only where user is looking for info
        if(activeFrame->getNotifications() && activeFrame->getNotifications()->allKeys().size() > 0)
        {

#if COCOS2D_VERSION >= 0x00020100 || COCOS2D_VERSION == 0x00020003
            cocos2d::CCNotificationCenter::sharedNotificationCenter()->postNotification(LHAnimationFrameNotification, sprite);
            
#elif COCOS2D_VERSION >= 0x00020000
           
            cocos2d::extension::CCNotificationCenter::sharedNotificationCenter()->postNotification(LHAnimationFrameNotification, sprite);
#else
            
            CCNotificationCenter::sharedNotifCenter()->postNotification(LHAnimationFrameNotification, sprite);
#endif
        }
    }
}
//------------------------------------------------------------------------------
LHDictionary* LHAnimationNode::getUserDataForCurrentFrame()
{
    if(activeFrame){
        return activeFrame->getNotifications();
    }
    return NULL;
}

void LHAnimationNode::prepare()
{
    currentFrame = 0;
    repetitionsPerformed = 0;
    elapsedFrameTime = 0.0f;
    if(frames->count() > 0)
        activeFrame = (LHAnimationFrameInfo*)frames->objectAtIndex(0);
    else {
        activeFrame = NULL;
    }
    
    setActiveFrameTexture();
}
//------------------------------------------------------------------------------
void LHAnimationNode::play(){
    paused = false;
}
//------------------------------------------------------------------------------
void LHAnimationNode::restart(){
    prepare();
    play();
}
//------------------------------------------------------------------------------
int LHAnimationNode::getNumberOfFrames(){
    return frames->count();
}
//------------------------------------------------------------------------------
void LHAnimationNode::setFrame(int frm){
    if(frm >= 0 && frm < (int)frames->count()){
        currentFrame = frm;
        activeFrame = (LHAnimationFrameInfo*)frames->objectAtIndex(currentFrame);
        setActiveFrameTexture();
    }
}
//------------------------------------------------------------------------------
int LHAnimationNode::getCurrentFrame(){
    return currentFrame;
}
//------------------------------------------------------------------------------
void LHAnimationNode::nextFrame(){
    
    int curFrame = getCurrentFrame();
    curFrame +=1;
    
    if(curFrame >= 0 && curFrame < getNumberOfFrames()){
        setFrame(curFrame);
    }
}
//------------------------------------------------------------------------------
void LHAnimationNode::prevFrame(){
    
    int curFrame = getCurrentFrame();
    curFrame -=1;
    
    if(curFrame >= 0 && curFrame < (int)getNumberOfFrames()){
        setFrame(curFrame);
    }
}
//------------------------------------------------------------------------------
void LHAnimationNode::nextFrameAndRepeat(){
    
    int curFrame = getCurrentFrame();
    curFrame +=1;
    
    if(curFrame >= getNumberOfFrames()){
        curFrame = 0;
    }
    
    if(curFrame >= 0 && curFrame < getNumberOfFrames()){
        setFrame(curFrame);
    }
}
//------------------------------------------------------------------------------
void LHAnimationNode::prevFrameAndRepeat(){
    
    int curFrame = getCurrentFrame();
    curFrame -=1;
    
    if(curFrame < 0){
        curFrame = getNumberOfFrames() - 1;
    }
    
    if(curFrame >= 0 && curFrame < (int)getNumberOfFrames()){
        setFrame(curFrame);
    }
}
//------------------------------------------------------------------------------
bool LHAnimationNode::isAtLastFrame(){
    return (getNumberOfFrames()-1 == getCurrentFrame());
}
//------------------------------------------------------------------------------
void LHAnimationNode::restoreFrame(){
    if(!restoreOriginalFrame){
        return;
    }
    
    if(oldBatch){
        sprite->removeFromParentAndCleanup(false);
        sprite->setTexture(oldTexture);
        oldBatch->addChild(sprite,sprite->getZOrder());
    }
    else if(oldTexture){
        sprite->setTexture(oldTexture);
    }
    if(oldSpriteFrame){
        sprite->setDisplayFrame(oldSpriteFrame);
    }
//    sprite->setTextureRect(oldRect);
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void LHAnimationNode::setOldBatch(LHBatch* b){
    oldBatch = b;
    oldTexture = b->getTexture();
}
void LHAnimationNode::setOldTexture(CCTexture2D* tex){
    oldTexture = tex;
    oldBatch = NULL;
}
void LHAnimationNode::setOldRect(CCRect r){
    oldRect = r;
}
//------------------------------------------------------------------------------
float LHAnimationNode::totalTime(){
    float t = 0.0f;
    for(int i = 0; i < frames->count(); ++i)
    {
        LHAnimationFrameInfo* frm = (LHAnimationFrameInfo*)frames->objectAtIndex(i);
        t += delayPerUnit*frm->getDelayPerUnit();
    }
    return t;
}