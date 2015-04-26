#include "LoginScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "MainScene.h"
#include "SelectScene.h"
#include "android\jni\JniHelper.h"
#include "jni.h"

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
		/*auto main_scene = MainScene::createScene();
		Director::getInstance()->replaceScene(main_scene);*/
		auto main_scene = SelectScene::createScene();
		Director::getInstance()->replaceScene(main_scene);
	}
	else
	{
		JniMethodInfo info;
		bool isHave = JniHelper::getStaticMethodInfo(info, "org/cocos2dx/cpp/AppActivity", "getCurrentActivityObj", "()Ljava/lang/Object;");
		if (isHave)
		{
			auto activityObj = info.env->CallStaticObjectMethod(info.classID, info.methodID);
			cocos2d::log("----------->find!");
			isHave = JniHelper::getMethodInfo(info, "org/cocos2dx/cpp/AppActivity", "do_login", "(Ljava/lang/String;Ljava/lang/String;)V");
			if (isHave)
			{
				jstring jname = info.env->NewStringUTF(name.c_str());
				jstring jpwd = info.env->NewStringUTF(pwd.c_str());
				info.env->CallVoidMethod(activityObj, info.methodID, jname, jpwd);
				cocos2d::log("----------->find!");
			}
			else
			{
				cocos2d::log("----------->not find!");
			}
		}
		else
		{
			cocos2d::log("----------->not find!");
		}
	}
}