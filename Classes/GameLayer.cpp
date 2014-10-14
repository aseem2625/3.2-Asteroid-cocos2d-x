//
//  GameLayer.cpp
//  Asteroids
//
//  Created by Clawoo on 9/16/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>


#include "GameLayer.h"
#include "GameConfig.h"
#include "Asteroid.h"
#include "Bullet.h"
#include "TitleLayer.h"

using namespace std;

USING_NS_CC;

GameLayer::~GameLayer()
{
//    CC_SAFE_RELEASE_NULL(asteroids_);
    asteroids_->~Vector();

//    CC_SAFE_RELEASE_NULL(bullets_);
    bullets_->~Vector();
}

CCScene* GameLayer::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();
	
	// 'layer' is an autorelease object
	GameLayer *layer = GameLayer::create();
    
	// add layer as a child to scene
	scene->addChild(layer);
    
	// return the scene
	return scene;
}

bool GameLayer::init()
{
	if ( !CCLayer::init() )
	{
		return false;
	}
    
//    setIsTouchEnabled(true);
    setTouchEnabled(true);
    
    // Get window size
    CCSize windowSize = CCDirector::sharedDirector()->getWinSize();
    
    // Create ship object, position it, then add to layer
    ship_ = (Ship *)Ship::spriteWithFile("ship.png");
    ship_->setPosition(ccp(windowSize.width / 2, windowSize.height / 2));
    this->addChild(ship_);
    
//    asteroids_ = new MutableArray<CCSprite *>();
    asteroids_ = new Vector<CCSprite *>();
//    bullets_ = new CCMutableArray<CCSprite *>();
    bullets_ = new Vector<CCSprite *>();

    currentLevel_ = 0;
    
    this->startLevel();
    
    this->scheduleUpdate();
    
	return true;
}

void GameLayer::update(float dt)
{
//    if (asteroids_->count() == 0)
      if (asteroids_->size() == 0)

    {
        currentLevel_++;
        this->startLevel();
    }
    
    // Array that keeps asteroids that need to be removed
//    CCMutableArray<CCSprite *> *asteroidsToDelete = new CCMutableArray<CCSprite *>();
    Vector<Sprite *> *asteroidsToDelete = new Vector<Sprite *>();
//    asteroidsToDelete->autorelease();
    asteroidsToDelete->~Vector();
    
    // Array that keeps asteroids that need to be split in half
//    CCMutableArray<CCSprite *> *asteroidsToSplit = new CCMutableArray<CCSprite *>();
    Vector<Sprite *> *asteroidsToSplit = new Vector<Sprite *>();
//    asteroidsToSplit->autorelease();
    asteroidsToSplit->~Vector();
    
    // Array that keeps expired or otherwise exploded bullets that need to be removed
//    CCMutableArray<CCSprite *> *bulletsToDelete = new CCMutableArray<CCSprite *>();
    Vector<CCSprite *> *bulletsToDelete = new Vector<CCSprite *>();
//    bulletsToDelete->autorelease();
    bulletsToDelete->~Vector();
    
//    CCMutableArray<CCSprite *>::CCMutableArrayIterator it, jt;
    Vector<Sprite *>::iterator it, jt;
    int i=0;
    // Check for collisions vs. asteroids
    for (it = asteroids_->begin(); it != asteroids_->end(); it++)

    {
        Asteroid *a = (Asteroid *) *it;
        CCLog("asteroid #%d", i++);
        
        // Check if asteroid hits ship
        if (a->collidesWith(ship_))
        {
            // Game over, man!
            this->gameOver();
            return;
        }
        
        // Check if asteroid hits bullet, or if bullet is expired
        for (jt = bullets_->begin(); jt != bullets_->end(); jt++)
        {
            Bullet *b = (Bullet *) *jt;
            
            if (b->getExpired())
            {
                // Remove the bullet from organizational array
//                bulletsToDelete->addObject(b);
                bulletsToDelete->pushBack(b);
                
                // Remove bullet sprite from layer
                this->removeChild(b, false);
            }
            else if (a->collidesWith(b))
            {
                // Remove the asteroid the bullet collided with
//                asteroidsToDelete->addObject(a);
            	asteroidsToDelete->pushBack(a);
                // Remove asteroid sprite from layer
                this->removeChild(a, false);
                
                // Remove the bullet the asteroid collided with
//                bulletsToDelete->addObject(b);
                bulletsToDelete->pushBack(b);
                // Remove bullet sprite from layer
                this->removeChild(b, false);

                if (a->getSize() < kAsteroidSmall)
                {
//                    asteroidsToSplit->addObject(a);
                	asteroidsToSplit->pushBack(a);
                }
            }
        }
    }
    
    // split the larger asteroids that were hit by bullets
    for (it = asteroidsToSplit->begin(); it != asteroidsToSplit->end(); it++)
    {
        Asteroid *a = (Asteroid *)*it;
        for (int i = 0; i < 2; i++)
        {
            this->createAsteroidAt(a->getPosition(), a->getSize()+1);
        }
    }

    //    asteroids_->removeObjectsInArray(asteroidsToDelete);

    Vector <Sprite*>::iterator mp, mc;

    for (mp = asteroids_->begin(); mp != asteroids_->end(); mp++)
    {
        for (mc = asteroidsToDelete->begin(); mc != asteroidsToDelete->end(); mc++)
        {
//        	if(asteroids_->at(mp)==asteroidsToDelete->at(mc))
//        		asteroids_->
            	if(mp==mc)
        	{
        		asteroidsToDelete->erase(mc);
        	}
        }
    }


//    std::shared_ptr<Vector<Sprite*>>  vec0 = std::make_shared<Vector<Sprite*>>();


    //    bullets_->removeObjectsInArray(bulletsToDelete);


    Vector <Sprite*>::iterator mp2, mc2;

    for (mp2 = bullets_->begin(); mp2 != bullets_->end(); mp2++)
    {
        for (mc2 = bulletsToDelete->begin(); mc2 != bulletsToDelete->end(); mc2++)
        {
//        	if(bullets_->at(mp2)==bulletsToDelete->at(mc2))
        	if(mp2==mc2)
        	{
        		bulletsToDelete->erase(mp2);
        	}
        }
    }


/*    for (auto mp2 : bullets_)
    {
        for (auto mc2 : bulletsToDelete)
        {
//        	if(asteroids_->at(mp)==asteroidsToDelete->at(mc))
//        		asteroids_->
            	if(mp2==mc2)
        	{
//            		bulletsToDelete->erase(mc);
            		mp2->release();
        	}
        }
    }*/

//    asteroids_->erase()

}

Vector<Touch *>* GameLayer::allTouchesFromSet(Set *touches)
{
    Vector<Touch *> *arr = new Vector<Touch *>();
    
    SetIterator it;
    
	for( it = touches->begin(); it != touches->end(); it++) 
    {
//        arr->addObject((Touch *)*it);
        arr->pushBack((Touch *)*it);
    }
    return arr;
}

void GameLayer::TouchesBegan(Set* touches, Event* event)
{
    // This method is passed an NSSet of touches called (of course) "touches"
    // We need to convert it to an array first
    Vector<Touch *> *allTouches = this->allTouchesFromSet(touches);
    //Touch* fingerOne = (Touch *)allTouches->getObjectAtIndex(0);
    Touch* fingerOne = (Touch *)allTouches->at(0);
    
    // Convert each UITouch object to a CGPoint, which has x/y coordinates we can actually use
    Point pointOne = fingerOne->getLocationInView();
    

    // The touch points are always in "portrait" coordinates - convert to landscape
    pointOne = CCDirector::sharedDirector()->convertToGL(pointOne);
    
    // We store the starting point of the touch so we can determine whether the touch is a swipe or tap.
    // A tap shouldn't move, so we compare the distance of the starting/ending touches, and if the distance is
    // small enough (we account for a bit of movement, just in case), the input is considered a tap
    startTouchPoint_ = pointOne;
    if (allTouches->size() > 1)
    {
//        Touch *fingerTwo = allTouches->getObjectAtIndex(1);
        Touch *fingerTwo = allTouches->at(1);
        // Convert each UITouch object to a CGPoint, which has x/y coordinates we can actually use
        Point pointTwo = fingerTwo->getLocationInView();
        
        // The touch points are always in "portrait" coordinates - convert to landscape
        pointTwo = CCDirector::sharedDirector()->convertToGL(pointTwo);
        
        // Initialize the variables used to store the angle of rotation derived from the user's fingers
        currentTouchAngle_ = previousTouchAngle_ = CC_RADIANS_TO_DEGREES(atan2(pointOne.x - pointTwo.x, pointOne.y - pointTwo.y));
    }
}

void GameLayer::TouchesMoved(Set* touches, Event* event)
{
    // This method is passed an NSSet of touches called (of course) "touches"
    // We need to convert it to an array first
    Vector<Touch *> *allTouches = this->allTouchesFromSet(touches);

    // Only run the following code if there is more than one touch
    if (allTouches->size() > 1)
    {
        // We're going to track the first two touches (i.e. first two fingers)
        // Create "UITouch" objects representing each touch
        Touch *fingerOne = allTouches->at(0);
        Touch *fingerTwo = allTouches->at(1);
        
        // Convert each UITouch object to a CGPoint, which has x/y coordinates we can actually use
        Point pointOne = fingerOne->getLocationInView();

        Point pointTwo = fingerTwo->getLocationInView();
        
        // The touch points are always in "portrait" coordinates - you will need to convert them if in landscape (which we are)
        pointOne = CCDirector::sharedDirector()->convertToGL(pointOne);
        pointTwo = CCDirector::sharedDirector()->convertToGL(pointTwo);
        
        // Get the angle that's created by the user's two fingers
        currentTouchAngle_ = CC_RADIANS_TO_DEGREES(atan2(pointOne.x - pointTwo.x, pointOne.y - pointTwo.y));
        
        // Compare with the previous angle, to decide whether the change is positive or negative.
        float difference = currentTouchAngle_ - previousTouchAngle_;
        
        // The ship is then rotated by that difference
        ship_->setRotation(ship_->getRotation() + difference);
        
        // Store the current angle variable to be used again on the next loop iteration
        previousTouchAngle_ = currentTouchAngle_;
    }
}

void GameLayer::TouchesEnded(Set* touches, Event* event)
{
    // This method is passed an NSSet of touches called (of course) "touches"
    // We need to convert it to an array first
    Vector<Touch *> *allTouches = this->allTouchesFromSet(touches);
    
    if (allTouches->size() == 1)
    {
        Touch* fingerOne = (Touch *)allTouches->at(0);
        
        // Convert each UITouch object to a CGPoint, which has x/y coordinates we can actually use
//        Point pointOne = fingerOne->getLocationInView(fingerOne->view());
        Point pointOne = fingerOne->getLocationInView();

        // The touch points are always in "portrait" coordinates - convert to landscape
        pointOne = CCDirector::sharedDirector()->convertToGL(pointOne);
        
        // Set the variable that stores the ending touch point
        endTouchPoint_ = pointOne;

        // Get the distance that the user's finger moved during this touch
        float distance = sqrt(pow(endTouchPoint_.x - startTouchPoint_.x, 2) + pow(endTouchPoint_.y - startTouchPoint_.y, 2));
        
        // If the distance moved (in pixels) is small enough, consider the gesture a tap
        if (distance < 5)
        {
            this->createBullet();
        }
        // Otherwise, it's a swipe
        else
        {
            // Use distance of swipe as a multiplier for the ship velocity (longer swipe, go faster)
            ship_->setVelocity(ccp(cos(CC_DEGREES_TO_RADIANS(ship_->getRotation())) * distance / 100, 
                                   -sin(CC_DEGREES_TO_RADIANS(ship_->getRotation())) * distance / 100));
        }
    }
}

void GameLayer::createAsteroidAt(Point position , int size)
{
    const char *imageFile;
    
    switch (size) {
        case kAsteroidLarge:
            imageFile = "asteroid-large.png";
            break;
        case kAsteroidMedium:
            imageFile = "asteroid-medium.png";
            break;
        case kAsteroidSmall:
            imageFile = "asteroid-small.png";
            break;
            
        default:
            break;
    }
    
    Asteroid *a = Asteroid::spriteWithFile(imageFile);
    a->setSize(size);
    a->setPosition(position);
    
    // Random numbers 
    a->setVelocity(ccp((float)(arc4random() % 100) / 100 - 1, (float)(arc4random() % 100) / 100 - 1));
    
    // Add asteroid to organization array
    asteroids_->pushBack(a);
    
    // Add asteroid to layer
    this->addChild(a);
}

void GameLayer::createBullet()
{
    Bullet *b = Bullet::spriteWithFile("bullet.png");
    
    // Set the bullet's position by starting w/ the ship's position, then adding the rotation vector, so the bullet appears to come from the ship's nose
    
    b->setPosition(ccp(ship_->getPosition().x + cos(CC_DEGREES_TO_RADIANS(ship_->getRotation())) * ship_->getContentSize().width, 
                       ship_->getPosition().y - sin(CC_DEGREES_TO_RADIANS(ship_->getRotation())) * ship_->getContentSize().height));
    
    // Set the bullet's velocity to be in the same direction as the ship is pointing, plus whatever the ship's velocity is
    b->setVelocity(ccp(cos(CC_DEGREES_TO_RADIANS(ship_->getRotation())) * 2 + ship_->getVelocity().x, 
                       -sin(CC_DEGREES_TO_RADIANS(ship_->getRotation())) * 2 + ship_->getVelocity().y));
    
    // Add bullet to organizational array
    //bullets_->addObject(b);
    bullets_->pushBack(b);
     
    // Add bullet to layer
    this->addChild(b);
}

void GameLayer::startLevel()
{
    // Reset the ship's position, which also removes all bullets
    this->resetShip();
    
    // Get window size
    CCSize windowSize = CCDirector::sharedDirector()->getWinSize();
    
    // Create asteroids based on level number
	for (int i = 0; i < (currentLevel_ + 2); i++)
	{
		// Random numbers
		CCPoint randomPointOnScreen = ccp((float)(arc4random() % 100) / 100 * windowSize.width, (float)(arc4random() % 100) / 100 * windowSize.height);
        
        this->createAsteroidAt(randomPointOnScreen, kAsteroidLarge);
	}
}

void GameLayer::resetShip()
{
    Vector<Sprite *>::iterator it;
    
    for (it = bullets_->begin(); it != bullets_->end(); it++)
    {
        Bullet *b = (Bullet *)*it;
        this->removeChild(b, true);
    }
    
//    bullets_->removeAllObjects();
      bullets_->clear();
}

void GameLayer::gameOver()
{
    this->resetShip();
    this->unscheduleUpdate();
    
    ship_->setVisible(false);
    

    Size windowSize = Director::sharedDirector()->getWinSize();
    
    LabelTTF *title = LabelTTF::create("game over", "Courier", 64.0);
    title->setPosition(ccp(windowSize.width / 2, windowSize.height/2));
    this->addChild(title, 1);
    
    MenuItemFont *backButton = MenuItemFont::create("back to title", this, menu_selector(GameLayer::backButtonAction));
    
    Menu *menu = Menu::create(backButton, NULL);
    menu->setPosition(ccp(windowSize.width/2, title->getPositionY() - title->getContentSize().height));
    
    this->addChild(menu, 2);
}

void GameLayer::backButtonAction(CCObject* pSender)
{
    Director::sharedDirector()->replaceScene(TitleLayer::scene());
}
