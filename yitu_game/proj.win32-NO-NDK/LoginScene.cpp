#include "LoginScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "MainScene.h"
#include "SelectScene.h"

USING_NS_CC;

using namespace cocostudio::timeline;
using namespace ui;

Scene* LoginScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = LoginScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool LoginScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	this->rootNode = CSLoader::createNode("LoginScene.csb");

	Button* btn_login = (Button*) this->rootNode->getChildByName("btn_login");
	btn_login->addTouchEventListener(this, toucheventselector(LoginScene::on_btn_login_click));

	addChild(this->rootNode);
	return true;
}

void LoginScene::on_btn_login_click(Ref*, Widget::TouchEventType type)
{
	if (type != ui::Widget::TouchEventType::BEGAN)
	{
		return;
	}
	auto name = ((TextField*)this->rootNode->getChildByName("input_name"))->getStringValue();
	auto pwd = ((TextField*)this->rootNode->getChildByName("input_pwd"))->getStringValue();
	if (strcmp(name.c_str(), pwd.c_str()) == 0 && strcmp(name.c_str(), "admin") == 0)
	{

		auto main_scene = SelectScene::createScene();
		Director::getInstance()->replaceScene(main_scene);
	}
	else
	{
		auto main_scene = MainScene::createScene();
		Director::getInstance()->replaceScene(main_scene);

	}
}