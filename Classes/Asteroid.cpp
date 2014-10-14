//
//  Asteroid.cpp
//  Asteroids
//
//  Created by Clawoo on 9/18/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "Asteroid.h"

USING_NS_CC;

Asteroid* Asteroid::spriteWithFile(const char *pszFileName)
{
    Asteroid *pobSprite = new Asteroid();
    if (pobSprite && pobSprite->initWithFile(pszFileName))
    {
        pobSprite->scheduleUpdate();
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
	return NULL;
}

void Asteroid::update(float dt)
{
    // Rotate (based on time interval between each frame)
    this->setRotation(this->getRotation() + (float)dt * 15);
    
    // Move
    this->setPosition(ccp(this->getPositionX() + velocity_.x, this->getPositionY() + velocity_.y));
    
    CCSize windowSize = CCDirector::sharedDirector()->getWinSize();
    
    // If object moves off the bounds of the screen, make it appear on the other side
    if (this->getPositionX() < 0)
    {
        this->setPosition(ccp(windowSize.width, this->getPositionY()));
    }
    else if (this->getPositionX() > windowSize.width)
    {
        this->setPosition(ccp(0, this->getPositionY()));
    }
    
    if (this->getPosition().y < 0)
    {
        this->setPosition(ccp(this->getPosition().x, windowSize.height));
    }
    else if (this->getPosition().y > windowSize.height)
    {
        this->setPosition(ccp(this->getPosition().x, 0));
    }
}

// Super-basic AABB collision detection
bool Asteroid::collidesWith(Sprite *obj)
{
    // Create two rectangles with CGRectMake, using each sprite's x/y position and width/height
    Rect ownRect = Rect(this->getPosition().x - this->getContentSize().width / 2,
                                this->getPosition().y - this->getContentSize().height / 2, 
                                this->getContentSize().width, 
                                this->getContentSize().height);
    
    Rect otherRect = Rect(obj->getPosition().x - obj->getContentSize().width / 2,
                                obj->getPosition().y - obj->getContentSize().height / 2, 
                                obj->getContentSize().width, 
                                obj->getContentSize().height);
    
    // Feed the results into CGRectIntersectsRect() which tells if the rectangles intersect (obviously)
//    return Rect::RectIntersectsRect(ownRect, otherRect);
    return ownRect.Rect::intersectsRect(otherRect);





}
