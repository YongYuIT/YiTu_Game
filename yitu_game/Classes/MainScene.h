#ifndef __MAIN_SCENE__
#define __MAIN_SCENE__

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
USING_NS_CC;

class MainScene : public Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(MainScene);
private:
	//LoadingBar* lob_life;
	Node* rootNode;
	Node** sps;
	Point* original_position;
	void auto_move_next(int current_steps, int total_steps, int last);
	void on_btn_start_click(Ref*, ui::Widget::TouchEventType type);
	void on_btn_restart_click(Ref*, ui::Widget::TouchEventType type);
	void game_start(int steps);
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
};

#endif // __HELLOWORLD_SCENE_H__
