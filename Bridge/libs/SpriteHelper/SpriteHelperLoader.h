//  This file was generated with SpriteHelper
//  http://www.spritehelper.org
//
//  SpriteHelperLoader.h
//  Created by Bogdan Vladu
//  Copyright 2011 Bogdan Vladu. All rights reserved.
//
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
//
//  Version history
//  v1.0 first draft for SpriteHelper 1.8
////////////////////////////////////////////////////////////////////////////////

#ifndef __SPRITE_HELPER_LOADER__
#define __SPRITE_HELPER_LOADER__

#include "cocos2d.h"
#include "Box2D.h"

using namespace cocos2d;

#include "LHBatch.h"
#include "LHSprite.h"
#include "Nodes/LHContactInfo.h"
#include "Utilities/LHDictionary.h"


class SpriteHelperLoader {
	
public:

    typedef LHSprite* (*SHBatchSpriteConstructor)(LHDictionary *dict, LHBatch* batch);
    typedef LHSprite* (*SHFileSpriteConstructor)(LHDictionary* dict);

    static void setBox2dWorld(b2World* world);
    
    static LHSprite* createSpriteWithName(const std::string& name,
                                          const std::string& sheetName,
                                          const std::string& SH_FileName,
                                          cocos2d::CCNode* node = NULL,
                                          SHFileSpriteConstructor customConstructor = NULL);
    
    static LHBatch* createBatchWithSheetName(const std::string& sheetName,
                                             const std::string& SH_FileName,
                                             cocos2d::CCNode* node = NULL);
    
    
    //necessary info is taking from the LHBatch instance
    //make sure the batch belongs to the same SH Sheet as the sprite name
    LHSprite* createBatchSpriteWithName(const std::string& spriteName,
                                        LHBatch* batch,
                                        SHBatchSpriteConstructor customConstructor = NULL);
    
    ////////////////////////////////////////////////////////////////////////////////
    
    static void setMeterRatio(float ratio);
    static float meterRatio();
    static float pixelsToMeterRatio();
    static float pointsToMeterRatio();
    static b2Vec2 pixelToMeters(cocos2d::CCPoint point);
    static b2Vec2 pointsToMeters(cocos2d::CCPoint point);
    static cocos2d::CCPoint metersToPoints(b2Vec2 vec);
    static cocos2d::CCPoint metersToPixels(b2Vec2 vec);
    
    ////////////////////////////////////////////////////////////////////////////////
    
    //COLLISION HANDLING
    //see API Documentation on the website to see how to use this
    static void useSpriteHelperCollisionHandling();
    
    //method will be called twice per fixture, once at start and once at end of the collision".
    //because bodies can be formed from multiple fixture method may be called as many times as different fixtures enter in contact.
    
    //e.g. a car enters in collision with a stone, the stone first touched the bumper, (triggers collision 1)
    //then the stone enters under the car and touches the under part of the car (trigger collision 2)
    static void registerBeginOrEndCollisionCallbackBetweenTagA(int tagSpriteA,
                                                               int tagSpriteB,
                                                               cocos2d::CCObject* obj,
                                                               cocos2d::SEL_CallFuncO selector);
    
    static void cancelBeginOrEndCollisionCallbackBetweenTagA(int tagSpriteA,
                                                             int tagSpriteB);
    
    
    //this methods will be called durring the lifetime of the collision - many times
    static void registerPreCollisionCallbackBetweenTagA(int tagSpriteA,
                                                        int tagSpriteB,
                                                        cocos2d::CCObject* obj,
                                                        cocos2d::SEL_CallFuncO selector);
    
    static void cancelPreCollisionCallbackBetweenTagA(int tagSpriteA,
                                                      int tagSpriteB);
    
    static void registerPostCollisionCallbackBetweenTagA(int tagSpriteA,
                                                         int tagSpriteB,
                                                         cocos2d::CCObject* obj,
                                                         cocos2d::SEL_CallFuncO selector);
    
    static void cancelPostCollisionCallbackBetweenTagA(int tagSpriteA,
                                                       int tagSpriteB);
    
    
    static std::string stringFromInt(const int& i){
        std::stringstream st;
        st << i;
        return st.str();
    }

};

#endif

