# ScrollSpriteLayer
ScrollSpriteLayer for cocos2d-x

## How to use simply
```
ScrollSpriteLayer *scrollLayer = new ScrollSpriteLayer();
scrollLayer->init();

// use CCSpriteBatchnode
CCSpriteBatchnode *batchnode = new CCSpriteBatchNode();
batchnode->initWithFile("xxxx.png", kDefaultSpriteBatchCapacity);

// set CCSpriteBatchNode to ScrollSpriteLayer
scrollLayer->setCCSpriteBatchnode(batchnode);

// set sprite list 
CCArray *spriteList = CCArray::create(spriteA, spriteB, spriteC, ..., NULL);
scrollLayer->setSpriteList(spriteList);

// set margin between sprites (100px)
scrollLayer->setMargin(100);

// set Delegate if you need
scrollLayer->setDelegate(this);

// add ScrollSpriteLayer to this
this->addChild(scrollLayer);

CC_SAFE_RELASE_NULL(scrolLayer);
```