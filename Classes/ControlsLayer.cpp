//
//  ControlsLayer.cpp
//  Asteroids
//
//  Created by Clawoo on 9/18/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "ControlsLayer.h"
#include "TitleLayer.h"

USING_NS_CC;

Scene* ControlsLayer::scene()
{
	// 'scene' is an autorelease object
	Scene *scene = Scene::create();
	
	// 'layer' is an autorelease object
	ControlsLayer *layer = ControlsLayer::create();
    
	// add layer as a child to scene
	scene->addChild(layer);
    
	// return the scene
	return scene;
}

bool ControlsLayer::init()
{
	if ( !CCLayer::init() )
	{
		return false;
	}
    
    // Get window size
    CCSize windowSize = CCDirector::sharedDirector()->getWinSize();
    
    LabelTTF *title = LabelTTF::create("how to play", "Courier", 32.0);

    
    title->setPosition(ccp(windowSize.width / 2, windowSize.height - title->getContentSize().height));
    
    // Add to layer
    this->addChild(title, 1);
    
    LabelTTF *controlsLabel = LabelTTF::create("tap = shoot\npinch = rotate\nswipe = move",
    											"Courier",
    											16.0,
    											Size(windowSize.width, windowSize.height / 3),
    											TextHAlignment::CENTER);
    controlsLabel->setPosition(CCPointMake(windowSize.width/2, windowSize.height/2));
    this->addChild(controlsLabel);
    
    MenuItemFont *backButton = MenuItemFont::create("back", this, menu_selector(ControlsLayer::backButtonAction));
    
    Menu *menu = Menu::create(backButton, NULL);

    menu->setPosition(ccp(windowSize.width/2, controlsLabel->getPosition().y - controlsLabel->getContentSize().height));
    
    this->addChild(menu, 2);
    
    return true;
}

void ControlsLayer::backButtonAction(CCObject* pSender)
{
    CCDirector::sharedDirector()->replaceScene(TitleLayer::scene());
}
