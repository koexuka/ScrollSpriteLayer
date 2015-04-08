//
//  ScrollSpriteLayer.cpp
//  JumpingMan
//
//  Created by koexuka on 2015/04/08.
//
//

#include "ScrollSpriteLayer.h"

ScrollSpriteLayer::ScrollSpriteLayer()
{
    _batchnode = NULL;
    _spriteList = NULL;
    _margin = 0.0f;
    _currentNumber = 0;
    _positionXOffset = 0.0f;
    _isAction = false;
}
ScrollSpriteLayer::~ScrollSpriteLayer()
{
    CC_SAFE_RELEASE_NULL(_batchnode);
    CC_SAFE_RELEASE_NULL(_spriteList);
}

bool ScrollSpriteLayer::init()
{
    if (!CCLayer::init())
    {
        return false;
    }
    
    return true;
}

void ScrollSpriteLayer::setDelegate(ScrollSpriteLayerDelegate *delegate)
{
    _delegate = delegate;
}

void ScrollSpriteLayer::changePositionY(float y)
{
    _batchnode->setPositionY(y);
}

void ScrollSpriteLayer::setCCSpriteBatchnode(CCSpriteBatchNode *batchnode)
{
    if (_batchnode!=batchnode)
    {
        CC_SAFE_RELEASE(_batchnode);
        CC_SAFE_RETAIN(batchnode);
        _batchnode = batchnode;
        
        this->addChild(_batchnode);
    }
}

void ScrollSpriteLayer::setSpriteList(CCArray *list)
{
    if (_spriteList!=list)
    {
        CC_SAFE_RELEASE(_spriteList);
        CC_SAFE_RETAIN(list);
        _spriteList = list;
    }
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCObject *obj;
    int i = 0;
    CCARRAY_FOREACH(_spriteList, obj)
    {
        CCSprite *sprite = dynamic_cast<CCSprite *>(obj);
        if (!sprite) { continue; }
        
        sprite->setPosition(ccp(size.width/2+(i++*(sprite->getContentSize().width+_margin)),
                                size.height/2));
        if (i==1)
        {
            _positionXOffset = sprite->getPositionX();
        }
        _batchnode->addChild(sprite);
    }
    
    _currentNumber = 0;
}

void ScrollSpriteLayer::setMargin(float margin)
{
    _margin = margin;
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCObject *obj;
    int i=0;
    CCARRAY_FOREACH(_spriteList, obj)
    {
        CCSprite *sprite = dynamic_cast<CCSprite *>(obj);
        if (!sprite) { continue; }
        
        sprite->setPositionX(size.width/2+(i++*(sprite->getContentSize().width+_margin)));
    }
}


void ScrollSpriteLayer::moveToSprite(unsigned int number)
{
    if (number>=_spriteList->count())
    {
        CCLOGERROR("moveToSprite():%d wrong number", number);
        return;
    }
    if (_isAction)
    {
        CCLOGERROR("moveToSprite() runAction is executing");
        return;
    }
    this->stopAllActions();
    
    _isAction = true;
    CCMoveTo *moveTo = CCMoveTo::create(0.2f,
                                        _getPositionFromNumber(number));
    this->runAction(CCSequence::create(moveTo,
                                       CCCallFunc::create(this, callfunc_selector(ScrollSpriteLayer::_moveToSpriteFinished)),
                                       NULL));
    _currentNumber = number;
}

CCSprite *ScrollSpriteLayer::getCurrentSprite()
{
    return dynamic_cast<CCSprite *>(_spriteList->objectAtIndex(_currentNumber));
}

void ScrollSpriteLayer::_moveToSpriteFinished()
{
    _isAction = false;
    if (_delegate)
    {
        _delegate->finishMoved();
    }
}

CCPoint ScrollSpriteLayer::_getPositionFromNumber(unsigned int number)
{
    CCSprite *sprite = dynamic_cast<CCSprite *>(_spriteList->objectAtIndex(number));
    if (!sprite)
    {
        CCLOGERROR("_getPositionFromNumber():%d sprite not found at index", number);
        return CCPointZero;
    }
    float diffX = _positionXOffset-sprite->getPositionX();
    return ccp(diffX,
               this->getPositionY());
}

