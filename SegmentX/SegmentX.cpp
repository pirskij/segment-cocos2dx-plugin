//  SegmentX.h
//  Segment Cocos2dx SDK
//
//  Created by Andrey Pirskiy
//

#include "SegmentX.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "SegmentXAndroid.h"

#define COCOS2D_DEBUG 1

#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "SegmentXApple.h"
#endif

using namespace segment;

void SegmentX::setUserId(std::string_view userId, std::string_view key)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	SegmentXAndroid::setUserId(userId, key);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	SegmentXApple::setUserId(userId, key);
#endif
}

void SegmentX::start(std::string_view writeKey, bool debugMode)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	SegmentXAndroid::start(writeKey, debugMode);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	SegmentXApple::start(writeKey, debugMode);
#endif
}

void SegmentX::identify(std::string_view userId)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	SegmentXAndroid::identify(userId);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	SegmentXApple::identify(userId);
#endif
}

void SegmentX::identify(SegmentXTraits const& traits)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	SegmentXAndroid::identify(traits);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	SegmentXApple::identify(traits);
#endif
}

void SegmentX::identify(std::string_view userId, SegmentXTraits const& traits, SegmentXOptions const& opts)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	SegmentXAndroid::identify(userId, traits, opts);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	SegmentXApple::identify(userId, traits, opts);
#endif
}

void SegmentX::group(std::string_view groupId)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	SegmentXAndroid::group(groupId);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	SegmentXApple::group(groupId);
#endif
}

void SegmentX::group(std::string_view groupId, SegmentXTraits const& traits, SegmentXOptions const& opts)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	SegmentXAndroid::group(groupId, traits, opts);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	SegmentXApple::group(groupId, traits, opts);
#endif
}

void SegmentX::alias(std::string_view newId)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	SegmentXAndroid::alias(newId);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	SegmentXApple::alias(newId);
#endif
}

void SegmentX::alias(std::string_view newId, SegmentXOptions const& opts)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	SegmentXAndroid::alias(newId, opts);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	SegmentXApple::alias(newId, opts);
#endif
}

void SegmentX::screen(std::string_view name, SegmentXOptions const& opts)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	SegmentXAndroid::screen(name, opts);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	SegmentXApple::screen(name, opts);
#endif
}

void SegmentX::screen(std::string_view name, SegmentXProperties const& props, SegmentXOptions const& opts)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	SegmentXAndroid::screen(name, props, opts);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	SegmentXApple::screen(name, props, opts);
#endif
}

void SegmentX::screen(std::string_view category, std::string_view name, SegmentXProperties const& props, SegmentXOptions const& opts)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	SegmentXAndroid::screen(category, name, props, opts);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	SegmentXApple::screen(category, name, props, opts);
#endif
}

void SegmentX::track(std::string_view evt)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	SegmentXAndroid::track(evt);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	SegmentXApple::track(evt);
#endif
}

void SegmentX::track(std::string_view evt, SegmentXProperties const& props)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	SegmentXAndroid::track(evt, props);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	SegmentXApple::track(evt, props);
#endif
}

void SegmentX::track(std::string_view evt, SegmentXProperties const& props, SegmentXOptions const& opts)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	SegmentXAndroid::track(evt, props, opts);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	SegmentXApple::track(evt, props, opts);
#endif
}

void SegmentX::reset()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	SegmentXAndroid::reset();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	SegmentXApple::reset();
#endif
}
