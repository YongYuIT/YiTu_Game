#include "MainScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "MySupportFuncs.h"
#include<math.h>
#include<stdlib.h>
#include<time.h>
USING_NS_CC;

using namespace cocostudio::timeline;
using namespace ui;

Scene* MainScene::createScene()
{
	auto scene = Scene::create();
	auto layer = MainScene::create();
	scene->addChild(layer);
	return scene;
}

bool MainScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	this->setKeypadEnabled(true);

	this->rootNode = CSLoader::createNode("MainScene.csb");
	this->rootNode->getChildByName("txt_success")->setVisible(false);
	this->sps = new cocos2d::Node*[17];
	this->original_position = new Point[16];
	sps[0] = this->rootNode->getChildByName("img_target");
	sps[0]->setVisible(false);


	auto listener = EventListenerTouchOneByOne::create();


	for (int i = 1; i <= 16; i++)
	{
		cocos2d::log("--------->%d", i);
		char* num = add_char_string("sp_", getNum(i), 3, getWeishu(i));
		this->sps[i] = this->rootNode->getChildByName(num);
		original_position[i - 1] = sps[i]->getPosition();
		this->sps[i]->setVisible(false);
	}

	listener->onTouchBegan = [this](Touch* touch, Event* event)
	{
		Point p = Director::getInstance()->convertToGL(touch->getLocationInView());

		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		if (target->getBoundingBox().containsPoint(p))
		{
			Point** p_next = new Point*[4];
			p_next[0] = new Point(p.x, p.y);
			p_next[0]->x += 110;
			p_next[1] = new Point(p.x, p.y);
			p_next[1]->x -= 110;
			p_next[2] = new Point(p.x, p.y);
			p_next[2]->y += 110;
			p_next[3] = new Point(p.x, p.y);
			p_next[3]->y -= 110;

			auto back_func = [this]()
			{
				bool is_success = true;
				for (int i = 1; i <= 16; i++)
				{
					if (!sps[i]->getBoundingBox().containsPoint(this->original_position[i - 1]))
					{
						cocos2d::log("at %d error! current sp is (%f,%f)", i, sps[i]->getPosition().x, sps[i]->getPosition().y);
						cocos2d::log("original_position is (%f,%f)", i, original_position->x, original_position->y);
						is_success = false;
					}
				}
				cocos2d::log("-------------------");
				if (is_success)
					this->rootNode->getChildByName("txt_success")->setVisible(true);
			};
			CallFunc* call_back = CallFunc::create(back_func);

			for (int i = 1; i <= 16; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					if (sps[i]->getBoundingBox().containsPoint(*p_next[j]))
					{
						if (!sps[i]->isVisible())
						{
							Point p_now = target->getPosition();
							target->runAction(Sequence::create(MoveTo::create(0.5, sps[i]->getPosition()), DelayTime::create(0.1), call_back, NULL));
							sps[i]->runAction(MoveTo::create(0.01, p_now));
						}
					}
				}
			}
			return true;
		}
		return false;
	};
	listener->setSwallowTouches(true);

	for (int i = 1; i <= 16; i++)
	{
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(), sps[i]);
	}

	auto amin = CSLoader::createTimeline("Anim_show_page.csb");
	int* times = new int(0);
	auto amin_back = [times, amin, this]
	{
		if ((*times) <= 5)
		{
			(*times)++;
		}
		else
		{
			this->rootNode->stopAction(amin);
			auto amin_node = this->rootNode->getChildByName("anim_img");
			amin_node->setVisible(false);
			for (int i = 0; i < 17; i++)
			{
				this->sps[i]->setVisible(true);
			}
			srand((int)time(0));
		}
	};
	amin->setLastFrameCallFunc(amin_back);
	this->rootNode->runAction(amin);
	amin->gotoFrameAndPlay(0, 60, true);
	Button* btn_start = (Button*)this->rootNode->getChildByName("lay_diffcult_menu")->getChildByName("btn_start");
	btn_start->addTouchEventListener(this, toucheventselector(MainScene::on_btn_start_click));
	Button* btn_restart = (Button*)this->rootNode->getChildByName("lay_diffcult_menu")->getChildByName("btn_restart");
	btn_restart->addTouchEventListener(this, toucheventselector(MainScene::on_btn_restart_click));

	addChild(rootNode);
	return true;
}

void MainScene::auto_move_next(int current_steps, int total_steps, int last)
{
	if (current_steps == total_steps)
		return;
	Point p = sps[4]->getPosition();
	Point point_next;
	point_next.x = p.x;
	point_next.y = p.y;
	int num = rand() % 4;
	if (num == 0)
	{
		if (last == 1)
		{
			auto_move_next(current_steps, total_steps, last);
			return;
		}
		point_next.x += 120;
	}
	if (num == 1)
	{
		if (last == 0)
		{
			auto_move_next(current_steps, total_steps, last);
			return;
		}
		point_next.x -= 120;
	}
	if (num == 2)
	{
		if (last == 3)
		{
			auto_move_next(current_steps, total_steps, last);
			return;
		}
		point_next.y += 120;
	}
	if (num == 3)
	{
		if (last == 2)
		{
			auto_move_next(current_steps, total_steps, last);
			return;
		}
		point_next.y -= 120;
	}
	Node* sp = NULL;
	for (int j = 1; j < 17; j++)
	{
		if (sps[j]->getBoundingBox().containsPoint(point_next))
		{
			sp = sps[j];
		}
	}
	if (sp == NULL)
	{
		auto_move_next(current_steps, total_steps, num);
	}
	else
	{
		Point unvisable = sps[4]->getPosition();
		Point visable = sp->getPosition();
		auto back_func = [this, current_steps, total_steps, num]()
		{
			int current = current_steps + 1;
			this->auto_move_next(current, total_steps, num);
		};
		CallFunc* call_back = CallFunc::create(back_func);
		sps[4]->runAction(MoveTo::create(0, visable));
		sp->runAction(Sequence::create(MoveTo::create(0.3, unvisable), DelayTime::create(0.2), call_back, NULL));
	}
}

void MainScene::on_btn_start_click(Ref*, ui::Widget::TouchEventType type)
{
	if (type != ui::Widget::TouchEventType::BEGAN)
	{
		return;
	}
	CheckBox* cbx_easy = (CheckBox*)this->rootNode->getChildByName("lay_diffcult_menu")->getChildByName("cbx_easy");
	CheckBox* cbx_nomal = (CheckBox*)this->rootNode->getChildByName("lay_diffcult_menu")->getChildByName("cbx_nomal");
	CheckBox* cbx_hard = (CheckBox*)this->rootNode->getChildByName("lay_diffcult_menu")->getChildByName("cbx_hard");
	if (cbx_easy->isSelected())
	{
		game_start(5);
		return;
	}
	if (cbx_nomal->isSelected())
	{
		game_start(10);
		return;
	}
	if (cbx_hard->isSelected())
	{
		game_start(20);
		return;
	}
}

void MainScene::on_btn_restart_click(Ref*, ui::Widget::TouchEventType type)
{
	if (type != ui::Widget::TouchEventType::BEGAN)
	{
		return;
	}
	for (int i = 1; i <= 16; i++)
	{
		sps[i]->setPosition(original_position[i - 1]);
		this->rootNode->getChildByName("txt_success")->setVisible(false);
	}
}

void MainScene::game_start(int steps)
{
	//使右上角的精灵闪烁后消失----------------start
	Blink* bl = Blink::create(2.0, 15);
	auto back_func = [this, steps]()
	{
		this->sps[4]->setVisible(false);
		auto_move_next(0, steps, 0);
	};
	CallFunc* call_back = CallFunc::create(back_func);
	Action* actions = Sequence::create(bl, call_back, NULL);
	this->sps[4]->runAction(actions);
	//使右上角的精灵闪烁后消失----------------end
}

void MainScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	cocos2d::log("----------->%d", keyCode);
	if (keyCode == EventKeyboard::KeyCode::KEY_BACK)//back键
	{

	}
}