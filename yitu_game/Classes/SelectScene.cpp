#include "SelectScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "MySupportFuncs.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* SelectScene::createScene()
{
	auto scene = Scene::create();
	auto layer = SelectScene::create();
	scene->addChild(layer);
	return scene;
}

bool SelectScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto rootNode = CSLoader::createNode("SelectScene.csb");


	ui::ScrollView* scv_items = (ui::ScrollView*)rootNode->getChildByName("scv_items");
	auto items_0 = scv_items->getChildByName("items_0");
	Point p_0 = items_0->getPosition();
	for (int i = 0; i < 9; i++)
	{
		p_0.y -= 50;
		auto lay_items = CSLoader::createNode("lay_item_4.csb");

		auto mySpCache = SpriteFrameCache::getInstance();

		auto list = lay_items->getChildren();

		for (int j = 1; j <= 4; j++)
		{
			int img_index = ((i + 1) * 4 + j) % 19;
			char* title = "img_s/img_";
			char* img_name = add_char_string(title, getNum(img_index), 10, getWeishu(img_index));
			log("img is :%s", img_name);
			char* end = ".jpg";
			img_name = add_char_string(img_name, end, 10 + getWeishu(img_index), 4);

			char* title_item = "img_item_";
			char* name_item = add_char_string(title_item, getNum(j), 9, 1);

			log("img is :%s | item is %s", img_name, name_item);

			auto item = (ui::ImageView*)lay_items->getChildByName(name_item);
			item->loadTexture(img_name, ui::TextureResType::PLIST);
		}
		lay_items->setPosition(p_0);
		lay_items->setScaleY(0.4);
		scv_items->addChild(lay_items);
	}

	auto list = scv_items->getChildren();

	addChild(rootNode);
	return true;
}
