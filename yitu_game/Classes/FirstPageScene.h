#ifndef __FIRST_PAGE_SCENE__
#define __FIRST_PAGE_SCENE__

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
USING_NS_CC;

class FirstPage : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(FirstPage);
private:
	ui::Text* text_welcome_final;
};

#endif // __HELLOWORLD_SCENE_H__