//
//  ScoresLayer.cpp
//  Asteroids
//
//  Created by Clawoo on 9/18/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "ScoresLayer.h"
#include "TitleLayer.h"

USING_NS_CC;

CCScene* ScoresLayer::scene()
{
	// 'scene' is an autorelease object
	Scene *scene = Scene::create();
	
	// 'layer' is an autorelease object
	Layer *layer = ScoresLayer::create();
    
	// add layer as a child to scene
	scene->addChild(layer);
    
	// return the scene
	return scene;
}

bool ScoresLayer::init()
{
	if ( !Layer::init() )
	{
		return false;
	}
    
    // Get window size
    Size windowSize = Director::sharedDirector()->getWinSize();
    
    LabelTTF *title = LabelTTF::create("high scores", "Courier", 32.0);
    
    title->setPosition(ccp(windowSize.width / 2, windowSize.height - title->getContentSize().height));
    
    // Add to layer
    this->addChild(title, 1);
    
    LabelTTF *scoresLabel = LabelTTF::create("None","Courier", 16.0,Size(windowSize.width, windowSize.height/3), TextHAlignment::CENTER);
    scoresLabel->setPosition(ccp(windowSize.width/2, windowSize.height/2));

    MenuItemFont *backButton = MenuItemFont::create("back", this, menu_selector(ScoresLayer::backButtonAction));
    
    Menu *menu = Menu::create(backButton, NULL);
    menu->setPosition(ccp(windowSize.width/2, scoresLabel->getPosition().y - scoresLabel->getContentSize().height));
    
    this->addChild(menu, 2);
    
    return true;
}

void ScoresLayer::backButtonAction(CCObject* pSender)
{
    CCDirector::sharedDirector()->replaceScene(TitleLayer::scene());
}
