LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/FirstPageScene.cpp \
                   ../../Classes/MainScene.cpp \
                   ../../Classes/LoginScene.cpp \
                   ../../Classes/MySupportFuncs.cpp \
                   ../../Classes/org_cocos2dx_cpp_AppActivity.cpp \
                   ../../Classes/SelectScene.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_STATIC_LIBRARIES := cocos2dx_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,./prebuilt-mk)