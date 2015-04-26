#include "org_cocos2dx_cpp_AppActivity.h"
#include "cocostudio/CocoStudio.h"
#include "MainScene.h"
#include "jni.h"
USING_NS_CC;
extern "C"
{

	JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_AppActivity_on_1login_1finish
		(JNIEnv *, jobject, jboolean result)
	{
		log("on c++ %d", result);
		if (result || 1 == 1)
		{
			auto main_scene = MainScene::createScene();
			Director::getInstance()->replaceScene(main_scene);
		}
	}
}