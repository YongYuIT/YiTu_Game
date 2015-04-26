#ifndef __TEST_SCENE__
#define __TEST_SCENE__

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
USING_NS_CC;

class testScene : public Layer
{
public:
	Node* rootNode;
	Node** sps;
	Point* original_position;
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(testScene);
	void auto_move_next(int current_steps, int total_steps, int last);
	void on_btn_start_click(Ref*, ui::Widget::TouchEventType type);
	void on_btn_restart_click(Ref*, ui::Widget::TouchEventType type);
	void game_start(int steps);
private:
};
#endif 
