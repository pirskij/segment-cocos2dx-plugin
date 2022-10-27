//
//  SegmentXProperties.cpp
//  Segment Cocos2dx SDK
//
//  Created by Andrey Pirskiy
//

#include "SegmentXProperties.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include <platform/android/jni/JniHelper.h>
#endif
#include <any>

using namespace segment;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
jobject _putStringValue(jobject obj, const char* funcName, const char* strValue) {
	jobject ret = nullptr;
	cocos2d::JniMethodInfo jmiPutFunc;
	if (cocos2d::JniHelper::getMethodInfo(
		jmiPutFunc,
		"com/segment/analytics/Properties",
		funcName,
		"(Ljava/lang/String;)Lcom/segment/analytics/Properties;")) {
		jstring jValue = jmiPutFunc.env->NewStringUTF(strValue);
		ret = (jobject)jmiPutFunc.env->CallObjectMethod(obj, jmiPutFunc.methodID, jValue);
		jmiPutFunc.env->DeleteLocalRef(jValue);
	}

	return ret;
}

jobject _putDoubleValue(jobject obj, const char* funcName, double dValue) {
	jobject ret = nullptr;
	cocos2d::JniMethodInfo jmiPutFunc;
	if (cocos2d::JniHelper::getMethodInfo(
		jmiPutFunc,
		"com/segment/analytics/Properties",
		funcName,
		"(D)Lcom/segment/analytics/Properties;")) {
		ret = (jobject)jmiPutFunc.env->CallObjectMethod(obj, jmiPutFunc.methodID, dValue);
	}

	return ret;
}
#endif

SegmentXProperties::SegmentXProperties()
{
	_init(0);
}

SegmentXProperties::SegmentXProperties(int size)
{
	_init(size);
}

void SegmentXProperties::_init(int size)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo jmiInit;
	if (!cocos2d::JniHelper::getMethodInfo(jmiInit, "com/segment/analytics/Properties", "<init>", "()V")) {
		return;
	}

	m_props = (jobject)jmiInit.env->NewObject(jmiInit.classID, jmiInit.methodID);
#endif
}

SegmentXProperties& SegmentXProperties::putValue(double value)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	auto obj = _putDoubleValue(m_props, "putValue", value);
#endif

	return *this;
}

SegmentXProperties& SegmentXProperties::putValue(std::string_view key, std::any const &value)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo jmiPutFunc;
	if (cocos2d::JniHelper::getMethodInfo(
			jmiPutFunc,
			"com/segment/analytics/Properties",
			"putValue",
			"(Ljava/lang/String;Ljava/lang/Object;)Lcom/segment/analytics/Properties;"))
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

		m_props = (jobject)jmiPutFunc.env->CallObjectMethod(m_props, jmiPutFunc.methodID, jKey, jValue);
		jmiPutFunc.env->DeleteLocalRef(jKey);
		if (jValue != nullptr)
			jmiPutFunc.env->DeleteLocalRef(jValue);
	}
#endif

	return *this;
}

SegmentXProperties& SegmentXProperties::putRevenue(double revenue)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	auto obj = _putDoubleValue(m_props, "putRevenue", revenue);
#endif

	return *this;
}

SegmentXProperties& SegmentXProperties::putCurrency(std::string_view currency)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	auto obj = _putStringValue(m_props, "putCurrency", currency.data());
#endif

	return *this;
}

SegmentXProperties& SegmentXProperties::putTitle(std::string_view title)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	auto obj = _putStringValue(m_props, "putTitle", title.data());
#endif

	return *this;
}

SegmentXProperties& SegmentXProperties::putName(std::string_view name)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	auto obj = _putStringValue(m_props, "putName", name.data());
#endif

	return *this;
}

SegmentXProperties& SegmentXProperties::putCategory(std::string_view category)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	auto obj = _putStringValue(m_props, "putCategory", category.data());
#endif

	return *this;
}

SegmentXProperties& SegmentXProperties::putSku(std::string_view sku)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	auto obj = _putStringValue(m_props, "putSku", sku.data());
#endif

	return *this;
}

SegmentXProperties& SegmentXProperties::putPrice(double price)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	auto obj = _putDoubleValue(m_props, "putPrice", price);
#endif

	return *this;
}

SegmentXProperties& SegmentXProperties::putProductId(std::string_view productId)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	auto obj = _putStringValue(m_props, "putProductId", productId.data());
#endif

	return *this;
}

SegmentXProperties& SegmentXProperties::putOrderId(std::string_view orderId)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	auto obj = _putStringValue(m_props, "putOrderId", orderId.data());
#endif

	return *this;
}
