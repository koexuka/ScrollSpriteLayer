//
//  ScrollSpriteLayer.h
//  JumpingMan
//
//  Created by koexuka on 2015/04/08.
//
//

#ifndef __JumpingMan__ScrollSpriteLayer__
#define __JumpingMan__ScrollSpriteLayer__

#include <stdio.h>
#include "cocos2d.h"

using namespace cocos2d;

class ScrollSpriteLayerDelegate
{
public:
    virtual void finishMoved() = 0;
};


class ScrollSpriteLayer: public CCLayer
{
public:
    ScrollSpriteLayer();
    ~ScrollSpriteLayer();
    
    virtual bool init();
    void setDelegate(ScrollSpriteLayerDelegate *delegate);
    
    void setCCSpriteBatchnode(CCSpriteBatchNode *batchnode);
    void setSpriteList(CCArray *list);
    void changePositionY(float y);
    void setMargin(float margin);
    
    CC_SYNTHESIZE(unsigned int, _currentNumber, CurrentNumber);
    CCSprite *getCurrentSprite();
    void moveToSprite(unsigned int number);
    
private:
    CCSpriteBatchNode *_batchnode;
    CCArray *_spriteList;
    float _margin;
    float _positionXOffset;
    bool _isAction;
    ScrollSpriteLayerDelegate *_delegate;

    void _moveToSpriteFinished();
    CCPoint _getPositionFromNumber(unsigned int number);
};

#endif /* defined(__JumpingMan__ScrollSpriteLayer__) */
