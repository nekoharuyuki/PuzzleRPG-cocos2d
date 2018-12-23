LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

REL_ROOT_DIR := ../../..

# The path to the Firebase C++ SDK in the project's root directory.
# FIREBASE_CPP_SDK_DIR := $(LOCAL_PATH)/$(REL_ROOT_DIR)/firebase_cpp_sdk
 
# APP_ABI := armeabi-v7a x86
# STL := $(firstword $(subst _, ,$(APP_STL)))
# FIREBASE_LIBRARY_PATH := $(FIREBASE_CPP_SDK_DIR)/libs/android/$(TARGET_ARCH_ABI)/$(STL)
 
# LOCAL_MODULE := firebase_app
# LOCAL_SRC_FILES := $(FIREBASE_LIBRARY_PATH)/libapp.a
# LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/$(FIREBASE_CPP_SDK_DIR)/include
# include $(PREBUILT_STATIC_LIBRARY)
 
# LOCAL_MODULE := firebase_feature
# LOCAL_SRC_FILES := $(FIREBASE_LIBRARY_PATH)/libadmob.a
# LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/$(FIREBASE_CPP_SDK_DIR)/include
# include $(PREBUILT_STATIC_LIBRARY)

$(call import-add-path,$(LOCAL_PATH)/$(REL_ROOT_DIR)/cocos2d)
$(call import-add-path,$(LOCAL_PATH)/$(REL_ROOT_DIR)/cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/$(REL_ROOT_DIR)/cocos2d/cocos)
$(call import-add-path,$(LOCAL_PATH)/$(REL_ROOT_DIR)/cocos2d/cocos/audio/include)

LOCAL_MODULE := MyGame_shared

LOCAL_MODULE_FILENAME := libMyGame

LOCAL_SRC_FILES := hellocpp/main.cpp \

CLASSES_SRC_FILES := $(shell find $(LOCAL_PATH)/$(REL_ROOT_DIR)/Classes -name *.cpp)
LOCAL_SRC_FILES += $(CLASSES_SRC_FILES:$(LOCAL_PATH)/%=%)
LOCAL_SRC_FILES += $(LOCAL_PATH)/$(REL_ROOT_DIR)/Classes/Libs/sqlite/sqlite3.c

LOCAL_C_INCLUDES := $(shell find $(LOCAL_PATH)/$(REL_ROOT_DIR)/Classes -type d)

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END

LOCAL_STATIC_LIBRARIES := cocos2dx_static
# LOCAL_STATIC_LIBRARIES += firebase_app
# LOCAL_STATIC_LIBRARIES += firebase_feature

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-add-path, $(LOCAL_PATH)/$(REL_ROOT_DIR)/cocos2d)
$(call import-module, cocos)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
