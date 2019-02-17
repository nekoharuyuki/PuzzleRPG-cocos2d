/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "MotionStreakTest.h"
#include "testResource.h"

USING_NS_CC;

enum {
	kTagLabel = 1,
	kTagSprite1 = 2,
	kTagSprite2 = 3,
};

MotionStreakTests::MotionStreakTests()
{
    ADD_TEST_CASE(MotionStreakTest1);
    ADD_TEST_CASE(MotionStreakTest2);
}

//------------------------------------------------------------------
//
// MotionStreakTest1
//
//------------------------------------------------------------------

void MotionStreakTest1::onEnter()
{
    MotionStreakTest::onEnter();

    auto s = Director::getInstance()->getWinSize();
  
    // the root object just rotates around
    _root = Sprite::create(s_pathR1);
    addChild(_root, 1);
    _root->setPosition(Vec2(s.width/2, s.height/2));
  
    // the target object is offset from root, and the streak is moved to follow it
    _target = Sprite::create(s_pathR1);
    _root->addChild(_target);
    _target->setPosition(Vec2(s.width/4, 0));

    // create the streak object and add it to the scene
    _streak = MotionStreak::create(2, 3, 32, Color3B::GREEN, s_streak);
    addChild(_streak);
    // schedule an update on each frame so we can synchronize the streak with the target
    schedule(CC_SCHEDULE_SELECTOR(MotionStreakTest1::onUpdate));
  
    auto a1 = RotateBy::create(2, 360);

    auto action1 = RepeatForever::create(a1);
    auto motion = MoveBy::create(2, Vec2(100,0) );
    _root->runAction( RepeatForever::create(Sequence::create(motion, motion->reverse(), nullptr) ) );
    _root->runAction( action1 );

    auto colorAction = RepeatForever::create(Sequence::create(
        TintTo::create(0.2f, 255, 0, 0),
        TintTo::create(0.2f, 0, 255, 0),
        TintTo::create(0.2f, 0, 0, 255),
        TintTo::create(0.2f, 0, 255, 255),
        TintTo::create(0.2f, 255, 255, 0),
        TintTo::create(0.2f, 255, 0, 255),
        TintTo::create(0.2f, 255, 255, 255),
        nullptr));

    _streak->runAction(colorAction);
}

void MotionStreakTest1::onUpdate(float delta)
{
    _streak->setPosition( _target->convertToWorldSpace(Vec2::ZERO) );
}

std::string MotionStreakTest1::title() const
{
    return "MotionStreak test 1";
}

//------------------------------------------------------------------
//
// MotionStreakTest2
//
//------------------------------------------------------------------

void MotionStreakTest2::onEnter()
{
    MotionStreakTest::onEnter();

    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesMoved = CC_CALLBACK_2(MotionStreakTest2::onTouchesMoved, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    auto s = Director::getInstance()->getWinSize();
        
    // create the streak object and add it to the scene
    _streak = MotionStreak::create(3, 3, 64, Color3B::WHITE, s_streak );
    addChild(_streak);
    
    _streak->setPosition( Vec2(s.width/2, s.height/2) );
}

void MotionStreakTest2::onTouchesMoved(const std::vector<Touch*>& touches, Event* event)
{
    auto touchLocation = touches[0]->getLocation();
    
    _streak->setPosition( touchLocation );
}

std::string MotionStreakTest2::title() const
{
    return "MotionStreak test";
}

//------------------------------------------------------------------
//
// MotionStreakTest
//
//------------------------------------------------------------------

MotionStreakTest::MotionStreakTest(void)
{
}

MotionStreakTest::~MotionStreakTest(void)
{
}

std::string MotionStreakTest::title() const
{
    return "No title";
}

std::string MotionStreakTest::subtitle() const
{
    return "";
}

void MotionStreakTest::onEnter()
{
    TestCase::onEnter();

    auto s = Director::getInstance()->getWinSize();

    auto itemMode = MenuItemToggle::createWithCallback( CC_CALLBACK_1(MotionStreakTest::modeCallback, this),
        MenuItemFont::create("Use High Quality Mode"),
        MenuItemFont::create("Use Fast Mode"),
        nullptr);

    auto menuMode = Menu::create(itemMode, nullptr);
    addChild(menuMode);

    menuMode->setPosition(Vec2(s.width/2, s.height/4));
}

void MotionStreakTest::modeCallback(Ref *pSender)
{
    bool fastMode = _streak->isFastMode();
    _streak->setFastMode(! fastMode);
}
