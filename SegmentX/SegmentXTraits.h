//
//  SegmentXTraits.h
//  Segment Cocos2dx SDK
//
//  Created by Andrey Pirskiy
//

#pragma once

#include <cocos2d.h>
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#endif
#include <string_view>
#include <any>

namespace segment {

	class SegmentXTraits {
	public:
		SegmentXTraits();
		SegmentXTraits(int size);

		SegmentXTraits &putValue(std::string_view key, std::any const &value);

		SegmentXTraits &putUserId(std::string_view userId);

		SegmentXTraits &putAnonymousId(std::string_view id);

		SegmentXTraits &putAvatar(std::string_view avatar);

		SegmentXTraits &putDescription(std::string_view descr);

		SegmentXTraits &putEmail(std::string_view email);

		SegmentXTraits &putGender(std::string_view gender);

		SegmentXTraits &putName(std::string_view name);

		SegmentXTraits &putUserName(std::string_view userName);

		SegmentXTraits &putFirstName(std::string_view firstName);

		SegmentXTraits &putLastName(std::string_view lastName);

		SegmentXTraits &putPhone(std::string_view phone);

		SegmentXTraits &putWebsite(std::string_view web);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

		jobject getTraits() const { return m_traits; }

#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		void* getTraits() const { return m_traits; }
#endif

	private:
		void _init(int size);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		jobject m_traits = nullptr;
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		void* m_traits = nullptr;
#endif
	};
} // namespace segment
