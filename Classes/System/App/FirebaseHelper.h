//
//  FirebaseHelper.hpp
//  PuzzleRPG-mobile
//
//  Created by neko on 2018/09/09.
//

#ifndef __FIREBASE_HELPER_H__
#define __FIREBASE_HELPER_H__

#ifdef __USE_FIREBASE__

#include "firebase/admob/types.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
extern "C" {
#include <objc/objc.h>
}  // extern "C"
#endif

// Returns a variable that describes the ad parent for the app. On Android
// this will be a JObject pointing to the Activity. On iOS, it's an ID pointing
// to the root view of the view controller.
firebase::admob::AdParent getAdParent();

#endif // __USE_FIREBASE__
#endif // __FIREBASE_HELPER_H__
