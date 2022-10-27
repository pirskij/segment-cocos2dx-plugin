//
//  SegmentXOptions.cpp
//  Segment Cocos2dx SDK
//
//  Created by Andrey Pirskiy
//

#include "SegmentXOptions.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include <platform/android/jni/JniHelper.h>
#endif

using namespace segment;

SegmentXOptions::SegmentXOptions()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo jmiInit;
	if (!cocos2d::JniHelper::getMethodInfo(jmiInit, "com/segment/analytics/Options", "<init>", "()V")) {
		return;
	}

	m_opts = (jobject)jmiInit.env->NewObject(jmiInit.classID, jmiInit.methodID);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#endif
}

SegmentXOptions& SegmentXOptions::setIntegration(std::string_view integrationKey, bool enabled)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo jmiFunc;
	if (cocos2d::JniHelper::getMethodInfo(
			jmiFunc,
			"com/segment/analytics/Options",
			"setIntegration",
			"(Ljava/lang/String;Z)Lcom/segment/analytics/Options;")) {
		jstring jKey = jmiFunc.env->NewStringUTF(integrationKey.data());
		jobject ret = (jobject)jmiFunc.env->CallObjectMethod(m_opts, jmiFunc.methodID, jKey, enabled);
		jmiFunc.env->DeleteLocalRef(jKey);
	}
#endif

	return *this;
}
