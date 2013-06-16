//  This file was generated with SpriteHelper
//  http://spritehelper.wordpress.com
//
//  SpriteHelperLoader.mm
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

#include "SpriteHelperLoader.h"
#include "LHSettings.h"
#include "LHContactNode.h"
#include "SHDocumentLoader.h"
////////////////////////////////////////////////////////////////////////////////

void SpriteHelperLoader::setBox2dWorld(b2World* world){
    LHSettings::sharedInstance()->setActiveBox2dWorld(world);
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
LHSprite* SpriteHelperLoader::createSpriteWithName(const std::string& name,
                                                   const std::string& sheetName,
                                                   const std::string& SH_FileName,
                                                   cocos2d::CCNode* node,
                                                   SHFileSpriteConstructor customConstructor){
    
    
    LHDictionary* dictionary = SHDocumentLoader::sharedInstance()->dictionaryForSpriteNamed(name,sheetName,SH_FileName);


    LHSprite* sprite = NULL;
    
    if(customConstructor != NULL){
        sprite =  (*customConstructor)(dictionary); //spriteWithDictionary
    }
    else{
        sprite = LHSprite::spriteWithDictionary(dictionary);
    }
    
    if(sprite){      
        sprite->setShSceneName(SH_FileName);
    }

    if(sprite && node)
        node->addChild(sprite);
    return sprite;
    
}
//------------------------------------------------------------------------------
LHBatch* SpriteHelperLoader::createBatchWithSheetName(const std::string& sheetName,
                                                      const std::string& SH_FileName,
                                                      cocos2d::CCNode* node)
{
    LHBatch* batch = LHBatch::batchWithSheetName(sheetName, SH_FileName);
    
    if(batch && node)
        node->addChild(batch);
    return batch;
}
//------------------------------------------------------------------------------
//LHSprite* SpriteHelperLoader::createBatchSpriteWithName(const std::string& spriteName, LHBatch* batch){
//
//    return SpriteHelperLoader::createBatchSpriteWithName(spriteName,
//                                                         batch,
//                                                         &LHSprite::batchSpriteWithDictionary);
//}
//------------------------------------------------------------------------------
LHSprite* SpriteHelperLoader::createBatchSpriteWithName(const std::string& spriteName,
                                                        LHBatch* batch,
                                                        SHBatchSpriteConstructor customConstructor){
    
    CCAssert(batch!=0, "Batch must not be nil");
    
    LHDictionary* dictionary = SHDocumentLoader::sharedInstance()->dictionaryForSpriteNamed(spriteName,
                                                                                            batch->getUniqueName(),
                                                                                            batch->getSHFile());
    LHSprite* sprite = NULL;
    if(customConstructor != NULL){
        sprite =  (*customConstructor)(dictionary, batch);
    }
    else{
        sprite =  LHSprite::batchSpriteWithDictionary(dictionary, batch);
    }
    
    if(sprite){
        sprite->setShSceneName(batch->getSHFile());
    }
    return sprite;
}
////////////////////////////////////////////////////////////////////////////////
void SpriteHelperLoader::setMeterRatio(float ratio){
    LHSettings::sharedInstance()->setLhPtmRatio(ratio);
}
//------------------------------------------------------------------------------
float SpriteHelperLoader::meterRatio(){
	return LHSettings::sharedInstance()->lhPtmRatio();
}
//------------------------------------------------------------------------------
float SpriteHelperLoader::pixelsToMeterRatio(){
    return LHSettings::sharedInstance()->lhPtmRatio()*LHSettings::sharedInstance()->convertRatio().x;
}
//------------------------------------------------------------------------------
float SpriteHelperLoader::pointsToMeterRatio(){
    return LHSettings::sharedInstance()->lhPtmRatio();
}
//------------------------------------------------------------------------------
b2Vec2 SpriteHelperLoader::pixelToMeters(CCPoint point){
    return b2Vec2(point.x / SpriteHelperLoader::pixelsToMeterRatio(),
                  point.y / SpriteHelperLoader::pixelsToMeterRatio());
}
//------------------------------------------------------------------------------
b2Vec2 SpriteHelperLoader::pointsToMeters(CCPoint point){
    return b2Vec2(point.x / LHSettings::sharedInstance()->lhPtmRatio(),
                  point.y / LHSettings::sharedInstance()->lhPtmRatio());
}
//------------------------------------------------------------------------------
CCPoint SpriteHelperLoader::metersToPoints(b2Vec2 vec){
    return CCPointMake(vec.x*LHSettings::sharedInstance()->lhPtmRatio(),
                       vec.y*LHSettings::sharedInstance()->lhPtmRatio());
}
//------------------------------------------------------------------------------
CCPoint SpriteHelperLoader::metersToPixels(b2Vec2 vec){
    return ccpMult(CCPointMake(vec.x, vec.y), SpriteHelperLoader::pixelsToMeterRatio());
}
////////////////////////////////////////////////////////////////////////////////
void SpriteHelperLoader::useSpriteHelperCollisionHandling(){

    b2World* world = LHSettings::sharedInstance()->getActiveBox2dWorld();
    CCAssert(world!=0, "\n\nERROR: Box2d World must not be nil - Please call [SpriteHelperLoader setBox2dWorld:world]; before registering for collision.\n\n");
    
    if(LHSettings::sharedInstance()->activeContactNode() != NULL)
    {
        LHSettings::sharedInstance()->activeContactNode()->release();
        LHSettings::sharedInstance()->setActiveContactNode(NULL);
    }
        
    if(LHSettings::sharedInstance()->activeContactNode() == NULL)
    {
        LHContactNode* contactNode = LHContactNode::contactNodeWithWorld(world);
        LHSettings::sharedInstance()->setActiveContactNode(contactNode);
    }
}
//------------------------------------------------------------------------------
void SpriteHelperLoader::registerBeginOrEndCollisionCallbackBetweenTagA(int tagA,
                                                                       int tagB,
                                                                       CCObject* obj,
                                                                       SEL_CallFuncO selector){
    if(NULL == LHSettings::sharedInstance()->activeContactNode()){
        CCLog("LevelHelper WARNING: Please call registerBeginOrEndCollisionCallbackBetweenTagA after useSpriteHelperCollisionHandling");
        return;
    }
    
    LHSettings::sharedInstance()->activeContactNode()->registerBeginOrEndCollisionCallbackBetweenTagA(tagA, tagB, obj, selector);
    
}
//------------------------------------------------------------------------------
void SpriteHelperLoader::cancelBeginOrEndCollisionCallbackBetweenTagA(int tagA,
                                                                     int tagB){
    if(NULL == LHSettings::sharedInstance()->activeContactNode()){
        CCLog("LevelHelper WARNING: Please call cancelBeginOrEndCollisionCallbackBetweenTagA after useSpriteHelperCollisionHandling");
        return;
    }
    
    LHSettings::sharedInstance()->activeContactNode()->cancelBeginOrEndCollisionCallbackBetweenTagA((int)tagA, (int)tagB);
}
//------------------------------------------------------------------------------
void SpriteHelperLoader::registerPreCollisionCallbackBetweenTagA(int tagA,
                                                                int tagB,
                                                                CCObject* obj,
                                                                SEL_CallFuncO selector)
{
    if(NULL == LHSettings::sharedInstance()->activeContactNode()){
        CCLog("LevelHelper WARNING: Please call registerPreColisionCallbackBetweenTagA after useSpriteHelperCollisionHandling");
        return;
    }
    LHSettings::sharedInstance()->activeContactNode()->registerPreCollisionCallbackBetweenTagA(tagA, tagB, obj, selector);
}
//------------------------------------------------------------------------------
void SpriteHelperLoader::cancelPreCollisionCallbackBetweenTagA(int tagA,
                                                              int tagB)
{
    if(NULL == LHSettings::sharedInstance()->activeContactNode()){
        CCLog("LevelHelper WARNING: Please call registerPreColisionCallbackBetweenTagA after useSpriteHelperCollisionHandling");
        return;
    }
    LHSettings::sharedInstance()->activeContactNode()->cancelPreCollisionCallbackBetweenTagA((int)tagA, (int)tagB);
}
//------------------------------------------------------------------------------
void SpriteHelperLoader::registerPostCollisionCallbackBetweenTagA(int tagA,
                                                                 int tagB,
                                                                 CCObject* obj,
                                                                 SEL_CallFuncO selector)
{
    if(NULL == LHSettings::sharedInstance()->activeContactNode()){
        CCLog("LevelHelper WARNING: Please call registerPostColisionCallbackBetweenTagA after useSpriteHelperCollisionHandling");
        return;
    }
    LHSettings::sharedInstance()->activeContactNode()->registerPostCollisionCallbackBetweenTagA(tagA, tagB, obj, selector);
}
//------------------------------------------------------------------------------
void SpriteHelperLoader::cancelPostCollisionCallbackBetweenTagA(int tagA,
                                                               int tagB)
{
    if(NULL == LHSettings::sharedInstance()->activeContactNode()){
        CCLog("LevelHelper WARNING: Please call registerPreColisionCallbackBetweenTagA after useSpriteHelperCollisionHandling");
        return;
    }
    LHSettings::sharedInstance()->activeContactNode()->cancelPostCollisionCallbackBetweenTagA((int)tagA,(int)tagB);
}
//------------------------------------------------------------------------------
