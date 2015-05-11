LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/iconv/include)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/iconv/libcharset)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/iconv/lib)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/iconv/libcharset/include)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/iconv/srclib)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/iconv)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
					../../Classes/AppDelegate.cpp \
					../../Classes/GameScene.cpp \
					../../Classes/MainMenu.cpp \
					../../Classes/MidMenu.cpp \
					../../Classes/MoveTiled.cpp \
					../../Classes/GameOver.cpp \
					../../Classes/HelloWorldScene.cpp
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += iconv_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
$(call import-module,audio/android)
$(call import-module,iconv)