LOCAL_PATH := $(call my-dir)

# The path to the Firebase C++ SDK, in the project's root directory.
FIREBASE_CPP_SDK_DIR := ../../../firebase_cpp_sdk
 
APP_ABI := armeabi-v7a x86
STL := $(firstword $(subst _, ,$(APP_STL)))
FIREBASE_LIBRARY_PATH := $(FIREBASE_CPP_SDK_DIR)/libs/android/$(TARGET_ARCH_ABI)/$(STL)
 
include $(CLEAR_VARS)
LOCAL_MODULE := firebase_app
LOCAL_SRC_FILES := $(FIREBASE_LIBRARY_PATH)/libapp.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/$(FIREBASE_CPP_SDK_DIR)/include
include $(PREBUILT_STATIC_LIBRARY)
 
include $(CLEAR_VARS)
LOCAL_MODULE := firebase_feature
LOCAL_SRC_FILES := $(FIREBASE_LIBRARY_PATH)/libadmob.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/$(FIREBASE_CPP_SDK_DIR)/include
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp
LOCAL_SRC_FILES += $(CPP_FILES:$(LOCAL_PATH)/%=%)

LOCAL_SRC_FILES +=../../Classes/sqlite3.c

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END

LOCAL_STATIC_LIBRARIES := cocos2dx_static
LOCAL_STATIC_LIBRARIES += cocos2d_lua_static
LOCAL_CPP_FEATURES += exceptions
LOCAL_STATIC_LIBRARIES += firebase_app
LOCAL_STATIC_LIBRARIES += firebase_feature

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
$(call import-module,scripting/lua-bindings/proj.android)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
