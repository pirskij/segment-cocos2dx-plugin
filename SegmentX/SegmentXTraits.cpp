//
//  SegmentXTraits.cpp
//  Segment Cocos2dx SDK
//
//  Created by Andrey Pirskiy
//

#include "SegmentXTraits.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include <platform/android/jni/JniHelper.h>
#endif

using namespace segment;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
jobject _putTraitsStringValue(jobject obj, const char* funcName, const char* strValue) {
	jobject ret = nullptr;
	cocos2d::JniMethodInfo jmiPutFunc;
	if (cocos2d::JniHelper::getMethodInfo(
			jmiPutFunc,
			"com/segment/analytics/Traits",
			funcName,
			"(Ljava/lang/String;)Lcom/segment/analytics/Traits;")) {
		jstring jValue = jmiPutFunc.env->NewStringUTF(strValue);
		ret = (jobject)jmiPutFunc.env->CallObjectMethod(obj, jmiPutFunc.methodID, jValue);
		jmiPutFunc.env->DeleteLocalRef(jValue);
	}

	return ret;
}
#endif

SegmentXTraits::SegmentXTraits()
{
	_init(0);
}

SegmentXTraits::SegmentXTraits(int size)
{
	_init(size);
}

void SegmentXTraits::_init(int size)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo jmiInit;
	if (!cocos2d::JniHelper::getMethodInfo(jmiInit, "com/segment/analytics/Traits", "<init>", "()V")) {
		return;
	}

	m_traits = (jobject)jmiInit.env->NewObject(jmiInit.classID, jmiInit.methodID);
#endif
}

SegmentXTraits& SegmentXTraits::putValue(std::string_view key, std::any const &value)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo jmiPutFunc;
	if (cocos2d::JniHelper::getMethodInfo(
			jmiPutFunc,
			"com/segment/analytics/Traits",
			"putValue",
			"(Ljava/lang/String;Ljava/lang/Object;)Lcom/segment/analytics/Traits;"))
	{
		jstring jKey = jmiPutFunc.env->NewStringUTF(key.data());
		jobject jValue = nullptr;
		if (value.has_value())
		{
			if (value.type() == typeid(int) || value.type() == typeid(int32_t))
			{
				jclass jIntegerClass = jmiPutFunc.env->FindClass("java/lang/Integer");
				jmethodID jValueOfId = jmiPutFunc.env->GetStaticMethodID(jIntegerClass,
																		 "valueOf",
																		 "(I)Ljava/lang/Integer;");

				int nVal = value.type() == typeid(int)
						   ? std::any_cast<int>(value)
						   : std::any_cast<int32_t>(value);
				jValue = (jobject)jmiPutFunc.env->CallStaticObjectMethod(
						jIntegerClass, jValueOfId, nVal);
			}
			else if (value.type() == typeid(int64_t))
			{
				jclass jIntegerClass = jmiPutFunc.env->FindClass("java/lang/Long");
				jmethodID jValueOfId = jmiPutFunc.env->GetStaticMethodID(jIntegerClass,
																		 "valueOf",
																		 "(J)Ljava/lang/Long;");
				jValue = (jobject)jmiPutFunc.env->CallStaticObjectMethod(
						jIntegerClass, jValueOfId, std::any_cast<int64_t>(value));
			}
			else if (value.type() == typeid(bool))
			{
				jclass jBooleanClass = jmiPutFunc.env->FindClass("java/lang/Boolean");
				jmethodID jValueOfId = jmiPutFunc.env->GetStaticMethodID(jBooleanClass,
																		 "valueOf",
																		 "(Z)Ljava/lang/Boolean;");
				jValue = (jobject) jmiPutFunc.env->CallStaticObjectMethod(
						jBooleanClass, jValueOfId, std::any_cast<bool>(value));

			}
			else if (value.type() == typeid(std::string))
				jValue = (jobject)jmiPutFunc.env->NewStringUTF(std::any_cast<std::string>(value).c_str());
			else if (value.type() == typeid(float) ||
					 value.type() == typeid(double))
			{
				jclass jDoubleClass = jmiPutFunc.env->FindClass("java/lang/Double");
				jmethodID jValueOfId = jmiPutFunc.env->GetStaticMethodID(jDoubleClass,
																		 "valueOf",
																		 "(D)Ljava/lang/Double;");
				double dVal = value.type() == typeid(float)
							  ? std::any_cast<float>(value)
							  : std::any_cast<double>(value);
				jValue = (jobject)jmiPutFunc.env->CallStaticObjectMethod(
						jDoubleClass, jValueOfId, dVal);
			}
		}

		m_traits = (jobject)jmiPutFunc.env->CallObjectMethod(m_traits, jmiPutFunc.methodID, jKey, jValue);
		jmiPutFunc.env->DeleteLocalRef(jKey);
		if (jValue != nullptr)
			jmiPutFunc.env->DeleteLocalRef(jValue);
	}
#endif

	return *this;
}

SegmentXTraits& SegmentXTraits::putUserId(std::string_view userId)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	auto obj = _putTraitsStringValue(m_traits, "putUserId", userId.data());
#endif

	return *this;
}

SegmentXTraits& SegmentXTraits::putAnonymousId(std::string_view id)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	auto obj = _putTraitsStringValue(m_traits, "putAnonymousId", id.data());
#endif

	return *this;
}

SegmentXTraits& SegmentXTraits::putAvatar(std::string_view avatar)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	auto obj = _putTraitsStringValue(m_traits, "putAvatar", avatar.data());
#endif

	return *this;
}

SegmentXTraits& SegmentXTraits::putDescription(std::string_view descr)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	auto obj = _putTraitsStringValue(m_traits, "putDescription", descr.data());
#endif

	return *this;
}

SegmentXTraits& SegmentXTraits::putEmail(std::string_view email)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	auto obj = _putTraitsStringValue(m_traits, "putEmail", email.data());
#endif

	return *this;
}

SegmentXTraits& SegmentXTraits::putGender(std::string_view gender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	auto obj = _putTraitsStringValue(m_traits, "putGender", gender.data());
#endif

	return *this;
}

SegmentXTraits& SegmentXTraits::putName(std::string_view name)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	auto obj = _putTraitsStringValue(m_traits, "putName", name.data());
#endif

	return *this;
}

SegmentXTraits& SegmentXTraits::putUserName(std::string_view userName)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	auto obj = _putTraitsStringValue(m_traits, "putUsername", userName.data());
#endif

	return *this;
}

SegmentXTraits& SegmentXTraits::putFirstName(std::string_view firstName)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	auto obj = _putTraitsStringValue(m_traits, "putFirstName", firstName.data());
#endif

	return *this;
}

SegmentXTraits& SegmentXTraits::putLastName(std::string_view lastName)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	auto obj = _putTraitsStringValue(m_traits, "putLastName", lastName.data());
#endif

	return *this;
}

SegmentXTraits& SegmentXTraits::putPhone(std::string_view phone)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	auto obj = _putTraitsStringValue(m_traits, "putPhone", phone.data());
#endif

	return *this;
}

SegmentXTraits& SegmentXTraits::putWebsite(std::string_view web)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	auto obj = _putTraitsStringValue(m_traits, "putWebsite", web.data());
#endif

	return *this;
}
