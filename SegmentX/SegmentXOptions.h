//
//  SegmentXOptions.h
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

namespace segment {

	class SegmentXOptions {
	public:
		SegmentXOptions();

		SegmentXOptions &setIntegration(std::string_view integrationKey, bool enabled);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		jobject getOptions() const { return m_opts; }
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		void* getOptions() const { return m_opts; }
#endif

	private:
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		jobject m_opts = nullptr;
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		void* m_opts = nullptr;
#endif
	};
} // namespace segment
