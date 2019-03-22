/****************************************************************************
 Copyright (c) 2012 cocos2d-x.org
 Copyright (c) 2013-2016 Chukong Technologies Inc.
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

#include "ActionsTest.h"
#include "testResource.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"

#include "renderer/CCRenderer.h"
#include "renderer/CCCustomCommand.h"
#include "renderer/CCGroupCommand.h"

USING_NS_CC;
using namespace cocos2d::ui;

ActionsTests::ActionsTests()
{
    ADD_TEST_CASE(ActionMove);
    ADD_TEST_CASE(ActionMove3D);
    ADD_TEST_CASE(ActionRotate);
    ADD_TEST_CASE(ActionRotateBy3D);
    ADD_TEST_CASE(ActionScale);
    ADD_TEST_CASE(ActionSkew);
    ADD_TEST_CASE(ActionRotationalSkew);
    ADD_TEST_CASE(ActionRotationalSkewVSStandardSkew);
    ADD_TEST_CASE(ActionSkewRotateScale);
    ADD_TEST_CASE(ActionJump);
    ADD_TEST_CASE(ActionCardinalSpline);
    ADD_TEST_CASE(ActionCatmullRom);
    ADD_TEST_CASE(ActionBezier);
    ADD_TEST_CASE(ActionBlink);
    ADD_TEST_CASE(ActionFade);
    ADD_TEST_CASE(ActionTint);
    ADD_TEST_CASE(ActionAnimate);
    ADD_TEST_CASE(ActionSequence);
    ADD_TEST_CASE(ActionSequence2);
    ADD_TEST_CASE(ActionSequence3);
    ADD_TEST_CASE(ActionRemoveSelf);
    ADD_TEST_CASE(ActionSpawn);
    ADD_TEST_CASE(ActionSpawn2);
    ADD_TEST_CASE(ActionReverse);
    ADD_TEST_CASE(ActionDelayTime);
    ADD_TEST_CASE(ActionRepeat);
    ADD_TEST_CASE(ActionRepeatForever);
    ADD_TEST_CASE(ActionRotateToRepeat);
    ADD_TEST_CASE(ActionCallFunction);
    ADD_TEST_CASE(ActionCallFuncN);
    ADD_TEST_CASE(ActionCallFuncND);
    ADD_TEST_CASE(ActionReverseSequence);
    ADD_TEST_CASE(ActionReverseSequence2);
    ADD_TEST_CASE(ActionOrbit);
    ADD_TEST_CASE(ActionFollow);
    ADD_TEST_CASE(ActionFollowWithOffset);
    ADD_TEST_CASE(ActionTargeted);
    ADD_TEST_CASE(ActionTargetedReverse);
    ADD_TEST_CASE(ActionMoveStacked);
    ADD_TEST_CASE(ActionMoveJumpStacked);
    ADD_TEST_CASE(ActionMoveBezierStacked);
    ADD_TEST_CASE(ActionCardinalSplineStacked);
    ADD_TEST_CASE(ActionCatmullRomStacked);
    ADD_TEST_CASE(PauseResumeActions);
    ADD_TEST_CASE(ActionResize);
    ADD_TEST_CASE(ActionFloatTest);
    ADD_TEST_CASE(SequenceWithFinalInstant);
}

std::string ActionsDemo::title() const
{
    return "ActionsTest";
}

void ActionsDemo::onEnter()
{
    TestCase::onEnter();

    // Or you can create an sprite using a filename. only PNG is supported now. Probably TIFF too
    m_charPlayer1 = Sprite::create(s_pathCharPlayer10);
    m_charPlayer1->retain();

    m_charPlayer2 = Sprite::create(s_pathCharPlayer11);
    m_charPlayer2->retain();

    m_charPlayer3 = Sprite::create(s_pathCharPlayer12);
    m_charPlayer3->retain();

    addChild(m_charPlayer1, 1);
    addChild(m_charPlayer2, 2);
    addChild(m_charPlayer3, 3);

    m_charPlayer1->setPosition(VisibleRect::center().x, VisibleRect::bottom().y+VisibleRect::getVisibleRect().size.height/3);
    m_charPlayer2->setPosition(VisibleRect::center().x, VisibleRect::bottom().y+VisibleRect::getVisibleRect().size.height*2/3);
    m_charPlayer3->setPosition(VisibleRect::center().x, VisibleRect::bottom().y+VisibleRect::getVisibleRect().size.height/2);
}

void ActionsDemo::onExit()
{
    m_charPlayer1->release();
    m_charPlayer2->release();
    m_charPlayer3->release();

    TestCase::onExit();
}

void ActionsDemo::centerSprites(unsigned int numberOfSprites)
{
    auto s = Director::getInstance()->getWinSize();

    if( numberOfSprites == 0 )
    {
        m_charPlayer2->setVisible(false);
        m_charPlayer3->setVisible(false);
        m_charPlayer1->setVisible(false);
    } 
    else if ( numberOfSprites == 1 ) 
    {
        m_charPlayer2->setVisible(false);
        m_charPlayer3->setVisible(false);
        m_charPlayer1->setPosition(s.width/2, s.height/2);
    }
    else if( numberOfSprites == 2 ) 
    {        
        m_charPlayer3->setPosition(s.width/3, s.height/2);
        m_charPlayer2->setPosition(2*s.width/3, s.height/2);
        m_charPlayer1->setVisible(false);
    } 
    else if( numberOfSprites == 3 ) 
    {
        m_charPlayer1->setPosition(s.width/2, s.height/2);
        m_charPlayer2->setPosition(s.width/4, s.height/2);
        m_charPlayer3->setPosition(3 * s.width/4, s.height/2);
    }
}

void ActionsDemo::alignSpritesLeft(unsigned int numberOfSprites)
{
    auto s = Director::getInstance()->getWinSize();

    if( numberOfSprites == 1 ) 
    {
        m_charPlayer2->setVisible(false);
        m_charPlayer3->setVisible(false);
        m_charPlayer1->setPosition(60, s.height/2);
    } 
    else if( numberOfSprites == 2 ) 
    {        
        m_charPlayer3->setPosition(60, s.height/3);
        m_charPlayer2->setPosition(60, 2*s.height/3);
        m_charPlayer1->setVisible( false );
    } 
    else if( numberOfSprites == 3 ) 
    {
        m_charPlayer1->setPosition(60, s.height/2);
        m_charPlayer2->setPosition(60, 2*s.height/3);
        m_charPlayer3->setPosition(60, s.height/3);
    }
}

//------------------------------------------------------------------
//
//    ActionMove
//
//------------------------------------------------------------------
void ActionMove::onEnter()
{
    ActionsDemo::onEnter();

    centerSprites(3);

    auto s = Director::getInstance()->getWinSize();

    auto actionTo = MoveTo::create(2, Vec2(s.width-40, s.height-40));
    auto actionBy = MoveBy::create(2, Vec2(80,80));
    auto actionByBack = actionBy->reverse();

    m_charPlayer2->runAction( actionTo);
    m_charPlayer1->runAction( Sequence::create(actionBy, actionByBack, nullptr));
    m_charPlayer3->runAction(MoveTo::create(1, Vec2(40,40)));
}

std::string ActionMove::subtitle() const
{
    return "MoveTo / MoveBy";
}

//------------------------------------------------------------------
//
//    ActionMove3D
//
//------------------------------------------------------------------
void ActionMove3D::onEnter()
{
    ActionsDemo::onEnter();
    
    centerSprites(3);
    
    auto s = Director::getInstance()->getWinSize();
    
    m_charPlayer2->setPosition3D(Vec3(s.width-40, s.height-40, 0));
    m_charPlayer3->setPosition3D(Vec3(40, 40, 0));
    
    auto actionTo = MoveTo::create(2, Vec3(s.width-40, s.height-40, -100));
    auto actionBy = MoveBy::create(2, Vec3(80, 80, -100));
    auto actionByBack = actionBy->reverse();
    
    m_charPlayer2->runAction(actionTo);
    m_charPlayer1->runAction(Sequence::create(actionBy, actionByBack, nullptr));
    m_charPlayer3->runAction(MoveTo::create(1, Vec3(40, 40, -100)));
}

std::string ActionMove3D::subtitle() const
{
    return "MoveTo / MoveBy 3D";
}

//------------------------------------------------------------------
//
// ActionScale
//
//------------------------------------------------------------------
void ActionScale::onEnter()
{
    ActionsDemo::onEnter();

    centerSprites(3);

    auto actionTo = ScaleTo::create(2.0f, 0.5f);
    auto actionBy = ScaleBy::create(2.0f, 1.0f, 10.0f);
    auto actionBy2 = ScaleBy::create(2.0f, 5.0f, 1.0f);

    m_charPlayer1->runAction( actionTo);
    m_charPlayer2->runAction( Sequence::create(actionBy, actionBy->reverse(), nullptr));
    m_charPlayer3->runAction( Sequence::create(actionBy2, actionBy2->reverse(), nullptr));
}

std::string ActionScale::subtitle() const
{
    return "ScaleTo / ScaleBy";
}

//------------------------------------------------------------------
//
//    ActionSkew
//
//------------------------------------------------------------------
void ActionSkew::onEnter()
{
    ActionsDemo::onEnter();

    centerSprites(3);

    auto actionTo = SkewTo::create(2, 37.2f, -37.2f);
    auto actionToBack = SkewTo::create(2, 0, 0);
    auto actionBy = SkewBy::create(2, 0.0f, -90.0f);
    auto actionBy2 = SkewBy::create(2, 45.0f, 45.0f);
    auto actionByBack = actionBy->reverse();

    m_charPlayer2->runAction(Sequence::create(actionTo, actionToBack, nullptr));
    m_charPlayer1->runAction(Sequence::create(actionBy, actionByBack, nullptr));

    m_charPlayer3->runAction(Sequence::create(actionBy2, actionBy2->reverse(), nullptr));
}

std::string ActionSkew::subtitle() const
{
    return "SkewTo / SkewBy";
}

// ActionRotationalSkew
void ActionRotationalSkew::onEnter()
{
    ActionsDemo::onEnter();

    this->centerSprites(3);

    auto actionTo = RotateTo::create(2, 180, 180);
    auto actionToBack = RotateTo::create(2, 0, 0);
    auto actionBy = RotateBy::create(2, 0.0f, 360);
    auto actionByBack = actionBy->reverse();

    auto actionBy2 = RotateBy::create(2, 360, 0);
    auto actionBy2Back = actionBy2->reverse();

    m_charPlayer2->runAction( Sequence::create(actionBy, actionByBack, nullptr) );
    m_charPlayer1->runAction( Sequence::create(actionTo, actionToBack, nullptr) );
    m_charPlayer3->runAction( Sequence::create(actionBy2, actionBy2Back, nullptr) );
}

std::string ActionRotationalSkew::subtitle() const
{
    return "RotationalSkewTo / RotationalSkewBy";
}



//ActionRotationalSkewVSStandardSkew
void ActionRotationalSkewVSStandardSkew::onEnter()
{
    ActionsDemo::onEnter();

    m_charPlayer2->removeFromParentAndCleanup(true);
    m_charPlayer1->removeFromParentAndCleanup(true);
    m_charPlayer3->removeFromParentAndCleanup(true);

    auto s = Director::getInstance()->getWinSize();

    Size boxSize(100.0f, 100.0f);

    auto box = LayerColor::create(Color4B(255,255,0,255));
    box->setAnchorPoint(Vec2(0.5,0.5));
    box->setContentSize( boxSize );
    box->setIgnoreAnchorPointForPosition(false);
    box->setPosition(s.width/2, s.height - 100 - box->getContentSize().height/2);
    this->addChild(box);

    auto label = Label::createWithTTF("Standard cocos2d Skew", s_fontArial, 16.0f);
    label->setPosition(s.width/2, s.height - 100 + label->getContentSize().height);
    this->addChild(label);

    auto actionTo = SkewBy::create(2, 360, 0);
    auto actionToBack = SkewBy::create(2, -360, 0);

    box->runAction(Sequence::create(actionTo, actionToBack, nullptr));

    box = LayerColor::create(Color4B(255,255,0,255));
    box->setAnchorPoint(Vec2(0.5,0.5));
    box->setContentSize(boxSize);
    box->setIgnoreAnchorPointForPosition(false);
    box->setPosition(s.width/2, s.height - 250 - box->getContentSize().height/2);
    this->addChild(box);

    label = Label::createWithTTF("Rotational Skew", s_fontArial, 16.0f);
    label->setPosition(s.width/2, s.height - 250 + label->getContentSize().height/2);
    this->addChild(label);
    auto actionTo2 = RotateBy::create(2, 360, 0);
    auto actionToBack2 = RotateBy::create(2, -360, 0);
    box->runAction(Sequence::create(actionTo2, actionToBack2, nullptr));
}
std::string ActionRotationalSkewVSStandardSkew::subtitle() const
{
    return "Skew Comparison";
}

// ActionSkewRotateScale
void ActionSkewRotateScale::onEnter()
{
    ActionsDemo::onEnter();

    m_charPlayer2->removeFromParentAndCleanup(true);
    m_charPlayer1->removeFromParentAndCleanup(true);
    m_charPlayer3->removeFromParentAndCleanup(true);

    Size boxSize(100.0f, 100.0f);

    auto box = LayerColor::create(Color4B(255, 255, 0, 255));
    box->setAnchorPoint(Vec2(0, 0));
    box->setPosition(190, 110);
    box->setContentSize(boxSize);

    static float markrside = 10.0f;
    auto uL = LayerColor::create(Color4B(255, 0, 0, 255));
    box->addChild(uL);
    uL->setContentSize(Size(markrside, markrside));
    uL->setPosition(0.f, boxSize.height - markrside);
    uL->setAnchorPoint(Vec2(0, 0));

    auto uR = LayerColor::create(Color4B(0, 0, 255, 255));
    box->addChild(uR);
    uR->setContentSize(Size(markrside, markrside));
    uR->setPosition(boxSize.width - markrside, boxSize.height - markrside);
    uR->setAnchorPoint(Vec2(0, 0));
    addChild(box);

    auto actionTo = SkewTo::create(2, 0.f, 2.f);
    auto rotateTo = RotateTo::create(2, 61.0f);
    auto actionScaleTo = ScaleTo::create(2, -0.44f, 0.47f);

    auto actionScaleToBack = ScaleTo::create(2, 1.0f, 1.0f);
    auto rotateToBack = RotateTo::create(2, 0);
    auto actionToBack = SkewTo::create(2, 0, 0);

    box->runAction(Sequence::create(actionTo, actionToBack, nullptr));
    box->runAction(Sequence::create(rotateTo, rotateToBack, nullptr));
    box->runAction(Sequence::create(actionScaleTo, actionScaleToBack, nullptr));
}

std::string ActionSkewRotateScale::subtitle() const
{
    return "Skew + Rotate + Scale";
}

//------------------------------------------------------------------
//
//    ActionRotate
//
//------------------------------------------------------------------
void ActionRotate::onEnter()
{
    ActionsDemo::onEnter();

    centerSprites(3);

    auto actionTo = RotateTo::create( 2, 45);
    auto actionTo2 = RotateTo::create( 2, -45);
    auto actionTo0 = RotateTo::create(2 , 0);
    m_charPlayer2->runAction( Sequence::create(actionTo, actionTo0, nullptr));

    auto actionBy = RotateBy::create(2 ,  360);
    auto actionByBack = actionBy->reverse();
    m_charPlayer1->runAction( Sequence::create(actionBy, actionByBack, nullptr));

    m_charPlayer3->runAction( Sequence::create(actionTo2, actionTo0->clone(), nullptr));
}

std::string ActionRotate::subtitle() const
{
    return "RotateTo / RotateBy";
}

//------------------------------------------------------------------
//
//    ActionRotateBy3D
//
//------------------------------------------------------------------
void ActionRotateBy3D::onEnter()
{
    ActionsDemo::onEnter();

    centerSprites(3);

    auto actionBy1 = RotateBy::create(4, Vec3(360, 0, 0));
    auto actionBy2 = RotateBy::create(4, Vec3(0, 360, 0));
    auto actionBy3 = RotateBy::create(4 ,Vec3(0, 0, 360));

    m_charPlayer2->runAction( Sequence::create(actionBy1, actionBy1->reverse(), nullptr));
    m_charPlayer1->runAction( Sequence::create(actionBy2, actionBy2->reverse(), nullptr));
    m_charPlayer3->runAction( Sequence::create(actionBy3, actionBy3->reverse(), nullptr));
}

std::string ActionRotateBy3D::subtitle() const
{
    return "RotateBy in 3D";
}

//------------------------------------------------------------------
//
// ActionJump
//
//------------------------------------------------------------------
void ActionJump::onEnter()
{
    ActionsDemo::onEnter();

    centerSprites(3);

    auto actionTo = JumpTo::create(2, Vec2(300,300), 50, 4);
    auto actionBy = JumpBy::create(2, Vec2(300,0), 50, 4);
    auto actionUp = JumpBy::create(2, Vec2(0,0), 80, 4);
    auto actionByBack = actionBy->reverse();

    m_charPlayer2->runAction( actionTo);
    m_charPlayer1->runAction( Sequence::create(actionBy, actionByBack, nullptr));
    m_charPlayer3->runAction( RepeatForever::create(actionUp));
}
std::string ActionJump::subtitle() const
{
    return "JumpTo / JumpBy";
}

//------------------------------------------------------------------
//
// ActionBezier
//
//------------------------------------------------------------------
void ActionBezier::onEnter()
{
    ActionsDemo::onEnter();

    auto s = Director::getInstance()->getWinSize();

    //
    // startPosition can be any coordinate, but since the movement
    // is relative to the Bezier curve, make it (0,0)
    //

    centerSprites(3);

    // sprite 1
    ccBezierConfig bezier;
    bezier.controlPoint_1 = Vec2(0, s.height/2);
    bezier.controlPoint_2 = Vec2(300, -s.height/2);
    bezier.endPosition = Vec2(300,100);

    auto bezierForward = BezierBy::create(3, bezier);
    auto bezierBack = bezierForward->reverse();
    auto rep = RepeatForever::create(Sequence::create( bezierForward, bezierBack, nullptr));


    // sprite 2
    m_charPlayer2->setPosition(80,160);
	ccBezierConfig bezier2;
    bezier2.controlPoint_1 = Vec2(100, s.height/2);
    bezier2.controlPoint_2 = Vec2(200, -s.height/2);
    bezier2.endPosition = Vec2(240,160);

    auto bezierTo1 = BezierTo::create(2, bezier2);    

    // sprite 3
    m_charPlayer3->setPosition(400,160);
    auto bezierTo2 = BezierTo::create(2, bezier2);

    m_charPlayer1->runAction( rep);
    m_charPlayer2->runAction(bezierTo1);
    m_charPlayer3->runAction(bezierTo2);

}

std::string ActionBezier::subtitle() const
{
    return "BezierBy / BezierTo";
}

//------------------------------------------------------------------
//
// ActionBlink
//
//------------------------------------------------------------------
void ActionBlink::onEnter()
{
    ActionsDemo::onEnter();

    centerSprites(2);

    auto action1 = Blink::create(2, 10);
    auto action2 = Blink::create(2, 5);

    m_charPlayer2->runAction( action1);
    m_charPlayer3->runAction(action2);
}

std::string  ActionBlink::subtitle() const
{
    return "Blink";
}

//------------------------------------------------------------------
//
// ActionFade
//
//------------------------------------------------------------------
void ActionFade::onEnter()
{
    ActionsDemo::onEnter();

    centerSprites(2);

    m_charPlayer2->setOpacity( 0 );
    auto action1 = FadeIn::create(1.0f);
    auto action1Back = action1->reverse();

    auto action2 = FadeOut::create(1.0f);
    auto action2Back = action2->reverse();
    auto action2BackReverse = action2Back->reverse();
    auto action2BackReverseReverse = action2BackReverse->reverse();

    m_charPlayer2->setOpacity(122);
    m_charPlayer2->runAction( Sequence::create( action1, action1Back, nullptr));
    m_charPlayer3->setOpacity(122);
    m_charPlayer3->runAction( Sequence::create( action2, action2Back,action2BackReverse,action2BackReverseReverse, nullptr));
}

std::string  ActionFade::subtitle() const
{
    return "FadeIn / FadeOut";
}

//------------------------------------------------------------------
//
// ActionTint
//
//------------------------------------------------------------------

void ActionTint::onEnter()
{
    ActionsDemo::onEnter();

    centerSprites(2);

    auto action1 = TintTo::create(2, 255, 0, 255);
    auto action2 = TintBy::create(2, -127, -255, -127);
    auto action2Back = action2->reverse();

    m_charPlayer2->runAction( action1);
    m_charPlayer3->runAction( Sequence::create( action2, action2Back, nullptr));
}

std::string  ActionTint::subtitle() const
{
    return "TintTo / TintBy";
}

//------------------------------------------------------------------
//
// ActionAnimate
//
//------------------------------------------------------------------
void ActionAnimate::onEnter()
{
    ActionsDemo::onEnter();

    centerSprites(3);
/*
    //
    // Manual animation
    //
    auto animation = Animation::create();
    for( int i=1;i<15;i++)
    {
        char szName[100] = {0};
        sprintf(szName, "asset/char/chara_enemy_%02d.png", i);
        animation->addSpriteFrameWithFile(szName);
    }
    // should last 2.8 seconds. And there are 14 frames.
    animation->setDelayPerUnit(2.8f / 14.0f);
    animation->setRestoreOriginalFrame(true);

    auto action = Animate::create(animation);
    m_charPlayer1->runAction(Sequence::create(action, action->reverse(), nullptr));
    
    //
    // File animation
    //
    // With 2 loops and reverse
    auto cache = AnimationCache::getInstance();
    cache->addAnimationsWithFile("animations/animations-2.plist");
    auto animation2 = cache->getAnimation("dance_1");

    auto action2 = Animate::create(animation2);
    m_charPlayer2->runAction(Sequence::create(action2, action2->reverse(), nullptr));

    _frameDisplayedListener = EventListenerCustom::create(AnimationFrameDisplayedNotification, [](EventCustom * event){
        auto userData = static_cast<AnimationFrame::DisplayedEventInfo*>(event->getUserData());
        
         log("target %p with data %s", userData->target, Value(userData->userInfo).getDescription().c_str());
    });

    _eventDispatcher->addEventListenerWithFixedPriority(_frameDisplayedListener, -1);

    //
    // File animation
    //
    // with 4 loops
    auto animation3 = animation2->clone();
    animation3->setLoops(4);


    auto action3 = Animate::create(animation3);
    m_charPlayer3->runAction(action3);*/
}

void ActionAnimate::onExit()
{
    ActionsDemo::onExit();
    _eventDispatcher->removeEventListener(_frameDisplayedListener);
}

std::string ActionAnimate::title() const
{
    return "Animation";
}

std::string ActionAnimate::subtitle() const
{
    return "Center: Manual animation. Border: using file format animation";
}

//------------------------------------------------------------------
//
//    ActionSequence
//
//------------------------------------------------------------------
void ActionSequence::onEnter()
{
    ActionsDemo::onEnter();

    alignSpritesLeft(1);

    auto action = Sequence::create(
        MoveBy::create( 2, Vec2(240,0)),
        RotateBy::create( 2,  540),
        nullptr);

    m_charPlayer1->runAction(action);
}

std::string ActionSequence::subtitle() const
{
    return "Sequence: Move + Rotate";
}

//------------------------------------------------------------------
//
//    ActionSequence2
//
//------------------------------------------------------------------
void ActionSequence2::onEnter()
{
    ActionsDemo::onEnter();

    alignSpritesLeft(1);

    m_charPlayer1->setVisible(false);

    auto action = Sequence::create(
		Place::create(Vec2(200,200)),
		Show::create(),
		MoveBy::create(1, Vec2(100,0)),
		CallFunc::create( CC_CALLBACK_0(ActionSequence2::callback1,this)),
		CallFunc::create( CC_CALLBACK_0(ActionSequence2::callback2,this,m_charPlayer1)),
		CallFunc::create( CC_CALLBACK_0(ActionSequence2::callback3,this,m_charPlayer1,0xbebabeba)),
		nullptr);

    m_charPlayer1->runAction(action);
}

void ActionSequence2::callback1()
{
    auto s = Director::getInstance()->getWinSize();
    auto label = Label::createWithTTF("callback 1 called", s_fontArial, 16.0f);
    label->setPosition(s.width/4*1,s.height/2);

    addChild(label);
}

void ActionSequence2::callback2(Node* sender)
{
    auto s = Director::getInstance()->getWinSize();
    auto label = Label::createWithTTF("callback 2 called", s_fontArial, 16.0f);
    label->setPosition(s.width/4*2,s.height/2);

    addChild(label);
}

void ActionSequence2::callback3(Node* sender, long data)
{
    auto s = Director::getInstance()->getWinSize();
    auto label = Label::createWithTTF("callback 3 called", s_fontArial, 16.0f);
    label->setPosition(s.width/4*3,s.height/2);

    addChild(label);
}

std::string ActionSequence2::subtitle() const
{
    return "Sequence of InstantActions";
}

//------------------------------------------------------------------
//
//    ActionSequence3
//
//------------------------------------------------------------------
void ActionSequence3::onEnter()
{
    ActionsDemo::onEnter();

    alignSpritesLeft(1);

    // Uses Array API
    auto action1 = MoveBy::create(2, Vec2(240,0));
    auto action2 = RotateBy::create(2, 540);
    auto action3 = action1->reverse();
    auto action4 = action2->reverse();

    Vector<FiniteTimeAction*> array;
    array.pushBack(action1);
    array.pushBack(action2);
    array.pushBack(action3);
    array.pushBack(action4);
    auto action = Sequence::create(array);
    m_charPlayer1->runAction(action);
}

std::string ActionSequence3::subtitle() const
{
    return "Sequence: Using Array API";
}

//------------------------------------------------------------------
//
// ActionCallFuncN
//
//------------------------------------------------------------------
void ActionCallFuncN::onEnter()
{
    ActionsDemo::onEnter();

    centerSprites(1);

    auto action = Sequence::create(
        MoveBy::create(2.0f, Vec2(150,0)),
        CallFuncN::create( CC_CALLBACK_1(ActionCallFuncN::callback, this)),
        nullptr);

    m_charPlayer1->runAction(action);
}

std::string ActionCallFuncN::title() const
{
    return "CallFuncN";
}

std::string ActionCallFuncN::subtitle() const
{
    return "Grossini should jump after moving";
}

void ActionCallFuncN::callback(Node* sender )
{
    auto a = JumpBy::create(5, Vec2(0,0), 100, 5);
    sender->runAction(a);
}
//------------------------------------------------------------------
//
// ActionCallFuncND
// CallFuncND is no longer needed. It can simulated with std::bind()
//
//------------------------------------------------------------------
void ActionCallFuncND::onEnter()
{
    ActionsDemo::onEnter();

    centerSprites(1);

    auto action = Sequence::create(
        MoveBy::create(2.0f, Vec2(200,0)),
        CallFuncN::create( CC_CALLBACK_1(ActionCallFuncND::doRemoveFromParentAndCleanup, this, true)),
        nullptr);

    m_charPlayer1->runAction(action);
}

std::string ActionCallFuncND::title() const
{
    return "CallFuncND + auto remove";
}

std::string ActionCallFuncND::subtitle() const
{
    return "simulates CallFuncND with std::bind()";
}

void ActionCallFuncND::doRemoveFromParentAndCleanup(Node* sender, bool cleanup)
{
    m_charPlayer1->removeFromParentAndCleanup(cleanup);
}

//------------------------------------------------------------------
//
//    ActionCallFunction
//
//------------------------------------------------------------------
void ActionCallFunction::onEnter()
{
    ActionsDemo::onEnter();

    centerSprites(3);


	auto action1 = Sequence::create(
                        MoveBy::create(2, Vec2(200,0)),
                        CallFunc::create( std::bind(&ActionCallFunction::callback1, this) ),
                        CallFunc::create(
                             // lambda
                             [&](){
                                 auto s = Director::getInstance()->getWinSize();
                                 auto label = Label::createWithTTF("called:lambda callback", s_fontArial, 16.0f);
                                 label->setPosition(s.width/4*1,s.height/2-40);
                                 this->addChild(label);
                             }  ),
                        nullptr);

    auto action2 = Sequence::create(
                        ScaleBy::create(2 ,  2),
                        FadeOut::create(2),
                        CallFunc::create( std::bind(&ActionCallFunction::callback2, this, m_charPlayer2) ),
                        nullptr);

    auto action3 = Sequence::create(
                        RotateBy::create(3 , 360),
                        FadeOut::create(2),
                        CallFunc::create( std::bind(&ActionCallFunction::callback3, this, m_charPlayer3, 42) ),
                        nullptr);

    m_charPlayer1->runAction(action1);
    m_charPlayer2->runAction(action2);
    m_charPlayer3->runAction(action3);
}


void ActionCallFunction::callback1()
{
    auto s = Director::getInstance()->getWinSize();
    auto label = Label::createWithTTF("callback 1 called", s_fontArial, 16.0f);
    label->setPosition(s.width/4*1,s.height/2);

    addChild(label);
}

void ActionCallFunction::callback2(Node* sender)
{
    auto s = Director::getInstance()->getWinSize();
    auto label = Label::createWithTTF("callback 2 called", s_fontArial, 16.0f);
    label->setPosition(s.width/4*2,s.height/2);

    addChild(label);

	CCLOG("sender is: %p", sender);
}

void ActionCallFunction::callback3(Node* sender, long data)
{
    auto s = Director::getInstance()->getWinSize();
    auto label = Label::createWithTTF("callback 3 called", s_fontArial, 16.0f);
    label->setPosition(s.width/4*3,s.height/2);
    addChild(label);

	CCLOG("target is: %p, data is: %ld", sender, data);
}

std::string ActionCallFunction::subtitle() const
{
    return "Callbacks: CallFunc with std::function()";
}
//------------------------------------------------------------------
//
// ActionSpawn
//
//------------------------------------------------------------------

void ActionSpawn::onEnter()
{
    ActionsDemo::onEnter();

    alignSpritesLeft(1);

    auto action = Spawn::create(
        JumpBy::create(2, Vec2(300,0), 50, 4),
        RotateBy::create( 2,  720),
        nullptr);

    m_charPlayer1->runAction(action);
}

std::string ActionSpawn::subtitle() const
{
    return "Spawn: Jump + Rotate";
}

//------------------------------------------------------------------
//
// ActionSpawn2
//
//------------------------------------------------------------------

void ActionSpawn2::onEnter()
{
    ActionsDemo::onEnter();

    alignSpritesLeft(1);

    auto action1 = JumpBy::create(2, Vec2(300,0), 50, 4);
    auto action2 = RotateBy::create( 2,  720);

    Vector<FiniteTimeAction*> array;
    array.pushBack(action1);
    array.pushBack(action2);

    auto action = Spawn::create(array);
    m_charPlayer1->runAction(action);
}

std::string ActionSpawn2::subtitle() const
{
    return "Spawn: using the Array API";
}

//------------------------------------------------------------------
//
// ActionRepeatForever
//
//------------------------------------------------------------------
void ActionRepeatForever::onEnter()
{
    ActionsDemo::onEnter();

    centerSprites(1);

    auto action = Sequence::create(
        DelayTime::create(1),
        CallFunc::create( std::bind( &ActionRepeatForever::repeatForever, this, m_charPlayer1) ),
        nullptr);

    m_charPlayer1->runAction(action);
}

void ActionRepeatForever::repeatForever(Node* sender)
{
    auto repeat = RepeatForever::create( RotateBy::create(1.0f, 360) );

    sender->runAction(repeat);
}

std::string ActionRepeatForever::subtitle() const
{
    return "CallFuncN + RepeatForever";
}


//------------------------------------------------------------------
//
// ActionRotateToRepeat
//
//------------------------------------------------------------------
void ActionRotateToRepeat::onEnter()
{
    ActionsDemo::onEnter();

    centerSprites(2);

	auto act1 = RotateTo::create(1, 90);
	auto act2 = RotateTo::create(1, 0);
	auto seq = Sequence::create(act1, act2, nullptr);
	auto rep1 = RepeatForever::create(seq);
	auto rep2 = Repeat::create( seq->clone(), 10);

    m_charPlayer2->runAction(rep1);
    m_charPlayer3->runAction(rep2);
}

std::string ActionRotateToRepeat ::subtitle() const
{
    return "Repeat/RepeatForever + RotateTo";
}

//------------------------------------------------------------------
//
// ActionReverse
//
//------------------------------------------------------------------
void ActionReverse::onEnter()
{
    ActionsDemo::onEnter();

    alignSpritesLeft(1);

    auto jump = JumpBy::create(2, Vec2(300,0), 50, 4);
    auto action = Sequence::create( jump, jump->reverse(), nullptr);

    m_charPlayer1->runAction(action);
}

std::string ActionReverse::subtitle() const
{
    return "Reverse an action";
}


//------------------------------------------------------------------
//
// ActionDelayTime
//
//------------------------------------------------------------------
void ActionDelayTime::onEnter()
{
    ActionsDemo::onEnter();

    alignSpritesLeft(1);

    auto move = MoveBy::create(1, Vec2(150,0));
    auto action = Sequence::create( move, DelayTime::create(2), move, nullptr);

    m_charPlayer1->runAction(action);
}

std::string ActionDelayTime::subtitle() const
{
    return "DelayTime: m + delay + m";
}


//------------------------------------------------------------------
//
// ActionReverseSequence
//
//------------------------------------------------------------------
void ActionReverseSequence::onEnter()
{
    ActionsDemo::onEnter();

    alignSpritesLeft(1);

    auto move1 = MoveBy::create(1, Vec2(250,0));
    auto move2 = MoveBy::create(1, Vec2(0,50));
    auto seq = Sequence::create( move1, move2, move1->reverse(), nullptr);
    auto action = Sequence::create( seq, seq->reverse(), nullptr);

    m_charPlayer1->runAction(action);
}

std::string ActionReverseSequence::subtitle() const
{
    return "Reverse a sequence";
}


//------------------------------------------------------------------
//
// ActionReverseSequence2
//
//------------------------------------------------------------------
void ActionReverseSequence2::onEnter()
{
    ActionsDemo::onEnter();

    alignSpritesLeft(2);


    // Test:
    //   Sequence should work both with IntervalAction and InstantActions
	auto move1 = MoveBy::create(1, Vec2(250,0));
	auto move2 = MoveBy::create(1, Vec2(0,50));
	auto tog1 = ToggleVisibility::create();
	auto tog2 = ToggleVisibility::create();
	auto seq = Sequence::create( move1, tog1, move2, tog2, move1->reverse(), nullptr);
	auto action = Repeat::create(Sequence::create( seq, seq->reverse(), nullptr), 3);


    // Test:
    //   Also test that the reverse of Hide is Show, and vice-versa
    m_charPlayer3->runAction(action);

	auto move_chara = MoveBy::create(1, Vec2(100,0));
	auto move_chara2 = MoveBy::create(1, Vec2(50,0));
	auto hide = Hide::create();
	auto seq_chara = Sequence::create( move_chara, hide, move_chara2, nullptr);
	auto seq_back = seq_chara->reverse();
    m_charPlayer2->runAction( Sequence::create( seq_chara, seq_back, nullptr));
}
std::string ActionReverseSequence2::subtitle() const
{
    return "Reverse sequence 2";
}

//------------------------------------------------------------------
//
// ActionRepeat
//
//------------------------------------------------------------------
void ActionRepeat::onEnter()
{
    ActionsDemo::onEnter();

    alignSpritesLeft(2);


    auto a1 = MoveBy::create(1, Vec2(150,0));
    auto action1 = Repeat::create(
        Sequence::create( Place::create(Vec2(60,60)), a1, nullptr) , 
        3); 
    auto  action2 = RepeatForever::create(
        Sequence::create(a1->clone(), a1->reverse(), nullptr)
        );

    m_charPlayer3->runAction(action1);
    m_charPlayer2->runAction(action2);
}

std::string ActionRepeat::subtitle() const
{
    return "Repeat / RepeatForever actions";
}

//------------------------------------------------------------------
//
// ActionOrbit
//
//------------------------------------------------------------------
void ActionOrbit::onEnter()
{
    ActionsDemo::onEnter();

    Director::getInstance()->setProjection(Director::Projection::_2D);
    centerSprites(3);

    auto orbit1 = OrbitCamera::create(2,1, 0, 0, 180, 0, 0);
    auto action1 = Sequence::create(
        orbit1,
        orbit1->reverse(),
        nullptr);

    auto orbit2 = OrbitCamera::create(2,1, 0, 0, 180, -45, 0);
    auto action2 = Sequence::create(
        orbit2,
        orbit2->reverse(),
        nullptr);

    auto orbit3 = OrbitCamera::create(2,1, 0, 0, 180, 90, 0);
    auto action3 = Sequence::create(
        orbit3,
        orbit3->reverse(),
        nullptr);

    m_charPlayer3->runAction(RepeatForever::create(action1));
    m_charPlayer2->runAction(RepeatForever::create(action2));
    m_charPlayer1->runAction(RepeatForever::create(action3));

    auto move = MoveBy::create(3, Vec2(100,-100));
    auto move_back = move->reverse();
    auto seq = Sequence::create(move, move_back, nullptr);
    auto rfe = RepeatForever::create(seq);
    m_charPlayer3->runAction(rfe);
    m_charPlayer2->runAction(rfe->clone() );
    m_charPlayer1->runAction( rfe->clone() );
}

void ActionOrbit::onExit()
{
    ActionsDemo::onExit();
    
    Director::getInstance()->setProjection(Director::Projection::DEFAULT);
}

std::string ActionOrbit::subtitle() const
{
    return "OrbitCamera action";
}

//------------------------------------------------------------------
//
// ActionFollow
//
//------------------------------------------------------------------
void ActionFollow::onEnter()
{
    ActionsDemo::onEnter();

    centerSprites(1);
    auto s = Director::getInstance()->getWinSize();

    DrawNode* drawNode = DrawNode::create();
    float x = s.width*2 - 100;
    float y = s.height;
    
    Vec2 vertices[] = { Vec2(5,5), Vec2(x-5,5), Vec2(x-5,y-5), Vec2(5,y-5) };
    drawNode->drawPoly(vertices, 4, true,  Color4F(CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), 1));
    
    this->addChild(drawNode);

    m_charPlayer1->setPosition(-200, s.height / 2);
    auto move = MoveBy::create(2, Vec2(s.width * 3, 0));
    auto move_back = move->reverse();
    auto seq = Sequence::create(move, move_back, nullptr);
    auto rep = RepeatForever::create(seq);

    m_charPlayer1->runAction(rep);

    this->runAction(Follow::create(m_charPlayer1, Rect(0, 0, s.width * 2 - 100, s.height)));
}

std::string ActionFollow::subtitle() const
{
    return "Follow action";
}

//------------------------------------------------------------------
//
// ActionFollowWithOffset
//
//------------------------------------------------------------------
void ActionFollowWithOffset::onEnter()
{
    ActionsDemo::onEnter();
    
    centerSprites(1);
    auto s = Director::getInstance()->getWinSize();
    
    DrawNode* drawNode = DrawNode::create();
    float x = s.width*2 - 100;
    float y = s.height;
    
    Vec2 vertices[] = { Vec2(5,5), Vec2(x-5,5), Vec2(x-5,y-5), Vec2(5,y-5) };
    drawNode->drawPoly(vertices, 4, true,  Color4F(CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), 1));
    
    this->addChild(drawNode);
    
    m_charPlayer1->setPosition(-200, s.height / 2);
    auto move = MoveBy::create(2, Vec2(s.width * 3, 1));
    auto move_back = move->reverse();
    auto seq = Sequence::create(move, move_back, nullptr);
    auto rep = RepeatForever::create(seq);
    
    m_charPlayer1->runAction(rep);
    
    //sample offset values set
    float verticalOffset = -900;
    float horizontalOffset = 200;
    this->runAction(Follow::createWithOffset(m_charPlayer1, horizontalOffset,verticalOffset,Rect(0, 0, s.width * 2 - 100, s.height)));
}

std::string ActionFollowWithOffset::subtitle() const
{
    return "Follow action with horizontal and vertical offset";
}


void ActionTargeted::onEnter()
{
    ActionsDemo::onEnter();
    centerSprites(2);


    auto jump1 = JumpBy::create(2,Vec2::ZERO,100,3);
    auto jump2 = jump1->clone();
    auto rot1 = RotateBy::create(1, 360);
    auto rot2 = rot1->clone();

    auto t1 = TargetedAction::create(m_charPlayer3, jump2);
    auto t2 = TargetedAction::create(m_charPlayer3, rot2);

    auto seq = Sequence::create(jump1, t1, rot1, t2, nullptr);
    auto always = RepeatForever::create(seq);

    m_charPlayer2->runAction(always);
}

std::string ActionTargeted::title() const
{
    return "ActionTargeted";
}

std::string ActionTargeted::subtitle() const
{
    return "Action that runs on another target. Useful for sequences";
}


void ActionTargetedReverse::onEnter()
{
    ActionsDemo::onEnter();
    centerSprites(2);
    
    
    auto jump1 = JumpBy::create(2,Vec2::ZERO,100,3);
    auto jump2 = jump1->clone();
    auto rot1 = RotateBy::create(1, 360);
    auto rot2 = rot1->clone();
    
    auto t1 = TargetedAction::create(m_charPlayer3, jump2);
    auto t2 = TargetedAction::create(m_charPlayer3, rot2);
    
    auto seq = Sequence::create(jump1, t1->reverse(), rot1, t2->reverse(), nullptr);
    auto always = RepeatForever::create(seq);
    
    m_charPlayer2->runAction(always);
}

std::string ActionTargetedReverse::title() const
{
    return "ActionTargetedReverse";
}

std::string ActionTargetedReverse::subtitle() const
{
    return "Action that runs reversely on another target. Useful for sequences";
}

// ActionStacked

void ActionStacked::onEnter()
{
    ActionsDemo::onEnter();
        
    this->centerSprites(0);
    
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesEnded = CC_CALLBACK_2(ActionStacked::onTouchesEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    auto s = Director::getInstance()->getWinSize();
    this->addNewSpriteWithCoords(Vec2(s.width/2, s.height/2));
}

void ActionStacked::addNewSpriteWithCoords(Vec2 p)
{
    int idx = CCRANDOM_0_1() * 1501 / 454;
    int x = (idx%5) * 160;
    int y = (idx/5) * 180;
    
    
    auto sprite = Sprite::create("animations/animations01/Fire3.png", Rect(x,y,85,121));
    
    sprite->setPosition(p);
    this->addChild(sprite);
    
    this->runActionsInSprite(sprite);
}

void ActionStacked::runActionsInSprite(Sprite *sprite)
{
    // override me
}

void ActionStacked::onTouchesEnded(const std::vector<Touch*>& touches, Event* event)
{
    for ( auto &touch: touches ) {
        auto location = touch->getLocation();
        addNewSpriteWithCoords( location );
    }
}

std::string ActionStacked::title() const
{
    return "Override me";
}

std::string ActionStacked::subtitle() const
{
    return "Tap screen";
}

// ActionMoveStacked


void ActionMoveStacked::runActionsInSprite(Sprite *sprite)
{
    sprite->runAction(
        RepeatForever::create(
                Sequence::create(
                MoveBy::create(0.05f, Vec2(10,10)),
                MoveBy::create(0.05f, Vec2(-10,-10)),
       nullptr)));
    
    auto action = MoveBy::create(2.0f, Vec2(400,0));
    auto action_back = action->reverse();
    
    sprite->runAction(
      RepeatForever::create(
        Sequence::create(action, action_back, nullptr)
      ));
}


std::string ActionMoveStacked::title() const
{
    return "Stacked MoveBy/To actions";
}

// ActionMoveJumpStacked

void ActionMoveJumpStacked::runActionsInSprite(Sprite *sprite)
{
    sprite->runAction(
          RepeatForever::create(
            Sequence::create(
             MoveBy::create(0.05f, Vec2(10,2)),
             MoveBy::create(0.05f, Vec2(-10,-2)),
             nullptr)));
    
    auto jump = JumpBy::create(2.0f, Vec2(400,0), 100, 5);
    auto jump_back = jump->reverse();
    
    sprite->runAction(
      RepeatForever::create(
          Sequence::create(jump, jump_back, nullptr)
          ));
}

std::string ActionMoveJumpStacked::title() const
{
    return "tacked Move + Jump actions";
}

// ActionMoveBezierStacked

void ActionMoveBezierStacked::runActionsInSprite(Sprite *sprite)
{
    auto s = Director::getInstance()->getWinSize();
    
    // sprite 1
    ccBezierConfig bezier;
    bezier.controlPoint_1 = Vec2(0, s.height/2);
    bezier.controlPoint_2 = Vec2(300, -s.height/2);
    bezier.endPosition = Vec2(300,100);
    
    auto bezierForward = BezierBy::create(3, bezier);
    auto bezierBack = bezierForward->reverse();
    auto seq = Sequence::create(bezierForward, bezierBack, nullptr);
    auto rep = RepeatForever::create(seq);
    sprite->runAction(rep);
    
    sprite->runAction(
     RepeatForever::create(
      Sequence::create(
       MoveBy::create(0.05f, Vec2(10,0)),
       MoveBy::create(0.05f, Vec2(-10,0)),
       nullptr)));
}

std::string ActionMoveBezierStacked::title() const
{
    return "Stacked Move + Bezier actions";
}


// ActionCatmullRomStacked

void ActionCatmullRomStacked::onEnter()
{
    ActionsDemo::onEnter();
    
    this->centerSprites(2);
    
    auto s = Director::getInstance()->getWinSize();
    
    //
    // sprite 1 (By)
    //
    // startPosition can be any coordinate, but since the movement
    // is relative to the Catmull Rom curve, it is better to start with (0,0).
    //
    
    m_charPlayer2->setPosition(50,50);
    
    auto array = PointArray::create(20);
    
    array->addControlPoint(Vec2(0,0));
    array->addControlPoint(Vec2(80,80));
    array->addControlPoint(Vec2(s.width-80,80));
    array->addControlPoint(Vec2(s.width-80,s.height-80));
    array->addControlPoint(Vec2(80,s.height-80));
    array->addControlPoint(Vec2(80,80));
    array->addControlPoint(Vec2(s.width/2, s.height/2));
    
    auto action = CatmullRomBy::create(3, array);
    auto reverse = action->reverse();
    
    auto seq = Sequence::create(action, reverse, nullptr);
    
    m_charPlayer2->runAction(seq);
    
    m_charPlayer2->runAction(
        RepeatForever::create(
            Sequence::create(
                MoveBy::create(0.05f, Vec2(10,0)),
                MoveBy::create(0.05f, Vec2(-10,0)),
                nullptr)));
    
    auto drawNode1 = DrawNode::create();
    drawNode1->setPosition(Vec2(50,50));
    drawNode1->drawCatmullRom(array, 50, Color4F(1.0, 1.0, 0.0, 0.5));
    this->addChild(drawNode1);
    
    //
    // sprite 2 (To)
    //
    // The startPosition is not important here, because it uses a "To" action.
    // The initial position will be the 1st point of the Catmull Rom path
    //
    
    auto array2 = PointArray::create(20);
    
    array2->addControlPoint(Vec2(s.width/2, 30));
    array2->addControlPoint(Vec2(s.width-80,30));
    array2->addControlPoint(Vec2(s.width-80,s.height-80));
    array2->addControlPoint(Vec2(s.width/2,s.height-80));
    array2->addControlPoint(Vec2(s.width/2, 30));
    
    auto action2 = CatmullRomTo::create(3, array2);
    auto reverse2 = action2->reverse();
    
    auto seq2 = Sequence::create(action2, reverse2, nullptr);
    
    m_charPlayer3->runAction(seq2);
    
    m_charPlayer3->runAction(
        RepeatForever::create(
            Sequence::create(
                MoveBy::create(0.05f, Vec2(10,0)),
                MoveBy::create(0.05f, Vec2(-10,0)),
                nullptr)));
    
    auto drawNode2 = DrawNode::create();
    drawNode2->drawCatmullRom(array2, 50, Color4F(1.0, 0.0, 0.0, 0.5));
    this->addChild(drawNode2);
}

ActionCatmullRomStacked::~ActionCatmullRomStacked()
{
}

std::string ActionCatmullRomStacked::title() const
{
    return "Stacked MoveBy + CatmullRom actions";
}

std::string ActionCatmullRomStacked::subtitle() const
{
    return "MoveBy + CatmullRom at the same time in the same sprite";
}


// ActionCardinalSplineStacked

void ActionCardinalSplineStacked::onEnter()
{
    ActionsDemo::onEnter();
    
    this->centerSprites(2);
    
    auto s = Director::getInstance()->getWinSize();
    
    auto array = PointArray::create(20);
    
    array->addControlPoint(Vec2(0, 0));
    array->addControlPoint(Vec2(s.width/2-30,0));
    array->addControlPoint(Vec2(s.width/2-30,s.height-80));
    array->addControlPoint(Vec2(0, s.height-80));
    array->addControlPoint(Vec2(0, 0));
    
    
    //
    // sprite 1 (By)
    //
    // Spline with no tension (tension==0)
    //

    auto action = CardinalSplineBy::create(3, array, 0);
    auto reverse = action->reverse();
    
    auto seq = Sequence::create(action, reverse, nullptr);
    
    m_charPlayer2->setPosition(50,50);
    m_charPlayer2->runAction(seq);
    
    m_charPlayer2->runAction(
        RepeatForever::create(
            Sequence::create(
                MoveBy::create(0.05f, Vec2(10,0)),
                MoveBy::create(0.05f, Vec2(-10,0)),
                nullptr)));
    
    auto drawNode1 = DrawNode::create();
    drawNode1->setPosition(Vec2(50,50));
    drawNode1->drawCardinalSpline(array, 0, 100, Color4F(1.0, 0.0, 1.0, 1.0));
    this->addChild(drawNode1);
    
    //
    // sprite 2 (By)
    //
    // Spline with high tension (tension==1)
    //
    
    auto *action2 = CardinalSplineBy::create(3, array, 1);
    auto reverse2 = action2->reverse();
    
    auto seq2 = Sequence::create(action2, reverse2, nullptr);
    
    m_charPlayer3->setPosition(s.width/2,50);
    
    m_charPlayer3->runAction(seq2);
    
    m_charPlayer3->runAction(
        RepeatForever::create(
            Sequence::create(
                MoveBy::create(0.05f, Vec2(10,0)),
                MoveBy::create(0.05f, Vec2(-10,0)),
                nullptr)));
    
    auto drawNode2 = DrawNode::create();
    drawNode2->setPosition(Vec2(s.width/2,50));
    drawNode2->drawCardinalSpline(array, 1, 100, Color4F(0.0, 0.0, 1.0, 1.0));
    this->addChild(drawNode2);
}

ActionCardinalSplineStacked::~ActionCardinalSplineStacked()
{
}

std::string ActionCardinalSplineStacked::title() const
{
    return "Stacked MoveBy + CardinalSpline actions";
}

std::string ActionCardinalSplineStacked::subtitle() const
{
    return "CCMoveBy + CardinalSplineBy/To at the same time";
}

/** ActionCatmullRom
 */
void ActionCatmullRom::onEnter()
{
    ActionsDemo::onEnter();
    
    this->centerSprites(2);
    
    auto s = Director::getInstance()->getWinSize();
    
    //
    // sprite 1 (By)
    //
    // startPosition can be any coordinate, but since the movement
    // is relative to the Catmull Rom curve, it is better to start with (0,0).
    //
    
    m_charPlayer2->setPosition(50, 50);
    
    auto array = PointArray::create(20);
    
    array->addControlPoint(Vec2(0, 0));
    array->addControlPoint(Vec2(80, 80));
    array->addControlPoint(Vec2(s.width - 80, 80));
    array->addControlPoint(Vec2(s.width - 80, s.height - 80));
    array->addControlPoint(Vec2(80, s.height - 80));
    array->addControlPoint(Vec2(80, 80));
    array->addControlPoint(Vec2(s.width / 2, s.height / 2));
    
    auto action = CatmullRomBy::create(3, array);
    auto reverse = action->reverse();
    
    auto seq = Sequence::create(action, reverse, nullptr);
    
    m_charPlayer2->runAction(seq);
    
    auto drawNode1 = DrawNode::create();
    drawNode1->setPosition(Vec2(50,50));
    drawNode1->drawCatmullRom(array, 50, Color4F(1.0, 0.0, 1.0, 1.0));
    this->addChild(drawNode1);
    
    //
    // sprite 2 (To)
    //
    // The startPosition is not important here, because it uses a "To" action.
    // The initial position will be the 1st point of the Catmull Rom path
    //    
    
    auto array2 = PointArray::create(20);
    
    array2->addControlPoint(Vec2(s.width / 2, 30));
    array2->addControlPoint(Vec2(s.width  -80, 30));
    array2->addControlPoint(Vec2(s.width - 80, s.height - 80));
    array2->addControlPoint(Vec2(s.width / 2, s.height - 80));
    array2->addControlPoint(Vec2(s.width / 2, 30));
    
    auto action2 = CatmullRomTo::create(3, array2);
    auto reverse2 = action2->reverse();
    
    auto seq2 = Sequence::create(action2, reverse2, nullptr);
    
    m_charPlayer3->runAction(seq2);
    
    auto drawNode2 = DrawNode::create();
    drawNode2->drawCatmullRom(array2, 50, Color4F(0.0, 1.0, 1.0, 1.0));
    this->addChild(drawNode2);
}

ActionCatmullRom::~ActionCatmullRom()
{
}

std::string ActionCatmullRom::title() const
{
    return "CatmullRomBy / CatmullRomTo";
}

std::string ActionCatmullRom::subtitle() const
{
    return "Catmull Rom spline paths. Testing reverse too";
}

/** ActionCardinalSpline
 */
void ActionCardinalSpline::onEnter()
{
    ActionsDemo::onEnter();
    
    this->centerSprites(2);
    
    auto s = Director::getInstance()->getWinSize();
    
    auto array = PointArray::create(20);
    
    array->addControlPoint(Vec2(0, 0));
    array->addControlPoint(Vec2(s.width/2-30, 0));
    array->addControlPoint(Vec2(s.width/2-30, s.height-80));
    array->addControlPoint(Vec2(0, s.height-80));
    array->addControlPoint(Vec2(0, 0));
    
    //
    // sprite 1 (By)
    //
    // Spline with no tension (tension==0)
    //
    
    auto action = CardinalSplineBy::create(3, array, 0);
    auto reverse = action->reverse();
    
    auto seq = Sequence::create(action, reverse, nullptr);
    
    m_charPlayer2->setPosition(50, 50);
    m_charPlayer2->runAction(seq);
    
    auto drawNode1 = DrawNode::create();
    drawNode1->setPosition(Vec2(50,50));
    drawNode1->drawCardinalSpline(array, 0, 100, Color4F(1.0, 0.0, 1.0, 1.0));
    this->addChild(drawNode1);
    
    //
    // sprite 2 (By)
    //
    // Spline with high tension (tension==1)
    //
    
    auto action2 = CardinalSplineBy::create(3, array, 1);
    auto reverse2 = action2->reverse();
    
    auto seq2 = Sequence::create(action2, reverse2, nullptr);
    
    m_charPlayer3->setPosition(s.width/2, 50);
    m_charPlayer3->runAction(seq2);
    
    auto drawNode2 = DrawNode::create();
    drawNode2->setPosition(Vec2(s.width/2, 50));
    drawNode2->drawCardinalSpline(array, 1, 100, Color4F(1.0, 0.0, 1.0, 1.0));
    this->addChild(drawNode2);
}

ActionCardinalSpline::~ActionCardinalSpline()
{
}

std::string ActionCardinalSpline::title() const
{
    return "CardinalSplineBy / CardinalSplineTo";
}

std::string ActionCardinalSpline::subtitle() const
{
    return "Cardinal Spline paths. Testing different tensions for one array";
}

/** PauseResumeActions
 */

PauseResumeActions::PauseResumeActions()
{

}

PauseResumeActions::~PauseResumeActions()
{

}

void PauseResumeActions::onEnter()
{
    ActionsDemo::onEnter();
    
    this->centerSprites(3);
    
    m_charPlayer2->runAction(RepeatForever::create(RotateBy::create(3, 360)));
    m_charPlayer1->runAction(RepeatForever::create(RotateBy::create(3, -360)));
    m_charPlayer3->runAction(RepeatForever::create(RotateBy::create(3, 360)));
    
    this->schedule([&](float dt){
        log("Pausing");
        auto director = Director::getInstance();

        _pausedTargets = director->getActionManager()->pauseAllRunningActions();
    }
                   ,3 ,false ,0 ,"pause_key");

    this->schedule([&](float dt) {
        log("Resuming");
        auto director = Director::getInstance();
        director->getActionManager()->resumeTargets(_pausedTargets);
        _pausedTargets.clear();
    }
                   ,5 ,false ,0, "resume_key");
}

std::string PauseResumeActions::title() const
{
    return "PauseResumeActions";
}

std::string PauseResumeActions::subtitle() const
{
    return "All actions pause at 3s and resume at 5s";
}

//------------------------------------------------------------------
//
//    ActionResize
//    Works on all nodes where setContentSize is effective. 
//    But it's mostly useful for nodes where 9-slice is enabled
//
//------------------------------------------------------------------
void ActionResize::onEnter() 
{
    ActionsDemo::onEnter();

    m_charPlayer1->setVisible(false);
    m_charPlayer2->setVisible(false);
    m_charPlayer3->setVisible(false);

    Size widgetSize = getContentSize();

    Text* alert = Text::create("ImageView Content ResizeTo ResizeBy action. \nTop: ResizeTo/ResizeBy on a 9-slice ImageView  \nBottom: ScaleTo/ScaleBy on a 9-slice ImageView (for comparison)", s_fontArial, 14);
    alert->setColor(Color3B(159, 168, 176));
    alert->setPosition(Vec2(widgetSize.width / 2.0f,
                            widgetSize.height / 2.0f - alert->getContentSize().height * 1.125f));

    addChild(alert);

    // Create the imageview
    Vec2 offset(0.0f, 50.0f);
    ImageView* imageViewResize = ImageView::create("cocosui/buttonHighlighted.png");
    imageViewResize->setScale9Enabled(true);
    imageViewResize->setContentSize(Size(50, 40));
    imageViewResize->setPosition(Vec2((widgetSize.width / 2.0f) + offset.x,
                                (widgetSize.height / 2.0f) + offset.y));

    auto resizeDown = cocos2d::ResizeTo::create(2.8f, Size(50, 40));
    auto resizeUp = cocos2d::ResizeTo::create(2.8f, Size(300, 40));

    auto resizeByDown = cocos2d::ResizeBy::create(1.8f, Size(0, -30));
    auto resizeByUp = cocos2d::ResizeBy::create(1.8f, Size(0, 30));
    addChild(imageViewResize);
    auto rep = RepeatForever::create(Sequence::create(resizeUp, resizeDown, resizeByDown, resizeByUp, nullptr));
    imageViewResize->runAction(rep);

    // Create another imageview that scale to see the difference
    ImageView* imageViewScale = ImageView::create("cocosui/buttonHighlighted.png");
    imageViewScale->setScale9Enabled(true);
    imageViewScale->setContentSize(Size(50, 40));
    imageViewScale->setPosition(Vec2(widgetSize.width / 2.0f,
                                 widgetSize.height / 2.0f));

    auto scaleDownScale = cocos2d::ScaleTo::create(2.8f, 1.0f);
    auto scaleUpScale = cocos2d::ScaleTo::create(2.8f, 6.0f, 1.0f);

    auto scaleByDownScale = cocos2d::ScaleBy::create(1.8f, 1.0f, 0.25f);
    auto scaleByUpScale = cocos2d::ScaleBy::create(1.8f, 1.0f, 4.0f);
    addChild(imageViewScale);
    auto rep2 = RepeatForever::create(Sequence::create(scaleUpScale, scaleDownScale, scaleByDownScale, scaleByUpScale, nullptr));
    imageViewScale->runAction(rep2);
}

std::string ActionResize::subtitle() const 
{
    return "ResizeTo / ResizeBy";
}

//------------------------------------------------------------------
//
//    ActionRemoveSelf
//
//------------------------------------------------------------------
void ActionRemoveSelf::onEnter()
{
	ActionsDemo::onEnter();

	alignSpritesLeft(1);

	auto action = Sequence::create(
		MoveBy::create( 2, Vec2(240,0)),
		RotateBy::create( 2,  540),
		ScaleTo::create(1,0.1f),
		RemoveSelf::create(),
		nullptr);

	m_charPlayer1->runAction(action);
}

std::string ActionRemoveSelf::subtitle() const
{
	return "Sequence: Move + Rotate + Scale + RemoveSelf";
}

//------------------------------------------------------------------
//
//    ActionFloat
//
//------------------------------------------------------------------
void ActionFloatTest::onEnter()
{
    ActionsDemo::onEnter();

    centerSprites(3);

    auto s = Director::getInstance()->getWinSize();

    // create float action with duration and from to value, using lambda function we can easily animate any property of the Node.
    auto actionFloat = ActionFloat::create(2.f, 0, 3, [this](float value) {
        m_charPlayer2->setScale(value);
    });

    float grossiniY = m_charPlayer1->getPositionY();

    auto actionFloat1 = ActionFloat::create(3.f, grossiniY, grossiniY + 50, [this](float value) {
        m_charPlayer1->setPositionY(value);
    });

    auto actionFloat2 = ActionFloat::create(3.f, 3, 1, [this] (float value) {
        m_charPlayer3->setScale(value);
    });

    m_charPlayer2->runAction(actionFloat);
    m_charPlayer1->runAction(actionFloat1);
    m_charPlayer3->runAction(actionFloat2);
}

std::string ActionFloatTest::subtitle() const
{
    return "ActionFloat";
}



//------------------------------------------------------------------
//
// SequenceWithFinalInstant
//
//------------------------------------------------------------------
void SequenceWithFinalInstant::onEnter()
{
    TestCase::onEnter();

    _manager = new cocos2d::ActionManager();
    
    _target = cocos2d::Node::create();
    _target->setActionManager( _manager );
    _target->retain();
    _target->onEnter();

    bool called( false );
    const auto f
      ( [ &called ]() -> void
        {
          cocos2d::log("Callback called.");
          called = true;
        } );
    
    const auto action =
      cocos2d::Sequence::create
      (cocos2d::DelayTime::create(0.05),
       cocos2d::CallFunc::create(f),
       nullptr);

    _target->runAction(action);
    _manager->update(0);
    _manager->update(0.05 - FLT_EPSILON);

    if ( action->isDone() && !called )
        assert(false);
    
    _manager->update(FLT_EPSILON);

    if ( action->isDone() && !called )
        assert(false);
}

void SequenceWithFinalInstant::onExit()
{
    TestCase::onExit();
    _target->onExit();
    _target->release();
    _manager->release();
}

std::string SequenceWithFinalInstant::subtitle() const
{
    return "Instant action should not crash";
}
