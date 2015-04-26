#include "FirstPageScene.h"
#include "LoginScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* FirstPage::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = FirstPage::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool FirstPage::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto rootNode = CSLoader::createNode("FirstPageScene.csb");

	auto txt_welcome = (ui::TextBMFont*)rootNode->getChildByName("txt_welcome");
	MoveTo* move_to = MoveTo::create(5.0, Point(800, 0));
	ScaleBy* sca_to = ScaleBy::create(2.5, 2.0, 2.0);
	Blink* bl = Blink::create(5.0, 20);

	this->text_welcome_final = (ui::Text*)rootNode->getChildByName("text_welcome_final");

	auto back_func = [&]()
	{

		this->text_welcome_final->setVisible(true);
		Blink* bl_final = Blink::create(3.0, 10);

		auto final_func = [&]()
		{

			auto scene = LoginScene::createScene();

			Director::getInstance()->replaceScene(scene);
		};
		CallFunc* call_final = CallFunc::create(final_func);

		this->text_welcome_final->runAction(Sequence::create(bl_final, call_final, NULL));
	};



	CallFunc* call_back = CallFunc::create(back_func);

	Action* actions = Sequence::create(Spawn::create(move_to, sca_to, bl, NULL), call_back, NULL);
	txt_welcome->runAction(actions);
	addChild(rootNode);

	return true;
}
