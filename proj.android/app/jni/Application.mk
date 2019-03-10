NDK_TOOLCHAIN_VERSION=clang
APP_STL := c++_static

APP_CPPFLAGS := -frtti -DCC_ENABLE_CHIPMUNK_INTEGRATION=1 -std=c++11 -fsigned-char
APP_LDFLAGS := -latomic
APP_ABI := armeabi-v7a

ifeq ($(NDK_DEBUG),1)
  APP_CPPFLAGS += -DNDEBUG=1
  APP_CPPFLAGS += -DCOCOS2D_DEBUG=1
  APP_OPTIM := debug
else
  APP_CPPFLAGS += -DNDEBUG
  APP_OPTIM := release
endif
