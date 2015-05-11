//
//  MenuScene.h
//  LinkLinker
//
//  Created by jun on 13-8-11.
//
//

#ifndef __LinkLinker__MenuScene__
#define __LinkLinker__MenuScene__

#include "cocos2d.h"

class MenuScene : public cocos2d::CCLayer
{
public:
	MenuScene();
	~MenuScene();
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::Scene* scene();
    
    // a selector callback
    void menuCloseCallback(Ref* pSender);
    // preprocessor macro for "static create()" constructor ( node() deprecated )
	CREATE_FUNC(MenuScene);
    
private:
    bool isEnter;
};


#endif /* defined(__LinkLinker__MenuScene__) */
