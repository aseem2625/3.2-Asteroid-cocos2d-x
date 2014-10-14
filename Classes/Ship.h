//
//  Ship.h
//  Asteroids
//
//  Created by Clawoo on 9/16/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef __SHIP_H__
#define __SHIP_H__

#include "cocos2d.h"

USING_NS_CC;

class Ship : public cocos2d::CCSprite
{
public:
    virtual void update(float dt);
	static Ship* spriteWithFile(const char *pszFileName);
    CC_SYNTHESIZE(Point, velocity_, Velocity);
	// implement the "static node()" method manually
//	LAYER_NODE_FUNC(Ship);
//    CREATE_FUNC(Ship);
};

#endif // __SHIP_H__
