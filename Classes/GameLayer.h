//
//  GameLayer.h
//  Asteroids
//
//  Created by Clawoo on 9/16/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef __GAMELAYER_H__
#define __GAMELAYER_H__

#include "cocos2d.h"
#include "Ship.h"
//#include <iostream>

USING_NS_CC;

class GameLayer : public cocos2d::Layer
{
public:
    ~GameLayer();
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  
    void update(float dt);
    
	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene();
    
	// implement the "static node()" method manually
//	LAYER_NODE_FUNC(GameLayer);
    CREATE_FUNC(GameLayer);
    
//    MutableArray<Touch *>* allTouchesFromSet(Set *touches);
    Vector<Touch *>* allTouchesFromSet(Set *touches);

    virtual void TouchesBegan(Set* touches, Event* event);
    virtual void TouchesMoved(Set* touches, Event* event);
    virtual void TouchesEnded(Set* touches, Event* event);

    void createAsteroidAt(cocos2d::CCPoint position , int size);
    void createBullet();
    void startLevel();
    void resetShip();
    void gameOver();
    void backButtonAction(CCObject* pSender);

private:
    Ship *ship_;
	// To determine rotation
	float previousTouchAngle_, currentTouchAngle_;
    
	// To determine movement/shooting
    cocos2d::CCPoint startTouchPoint_, endTouchPoint_;
    
    // Arrays used to keep track of all visible asteroids/bullets
    Vector<Sprite *> *asteroids_;
    Vector<Sprite *> *bullets_;
    
    // Used to determine the number of asteroids that appear
    int currentLevel_;
};

#endif // __GAMELAYER_H__
