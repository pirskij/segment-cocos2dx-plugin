//
//  SegmentXProperties.h
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

#include <string.h>
#include <string_view>
#include <any>

namespace segment {

	class SegmentXProperties {
	public:
		SegmentXProperties();
		SegmentXProperties(int size);

		SegmentXProperties &putValue(double value);

		SegmentXProperties &putValue(std::string_view key, std::any const &value);

		SegmentXProperties &putRevenue(double revenue);

		SegmentXProperties &putCurrency(std::string_view currency);

		SegmentXProperties &putTitle(std::string_view title);

		SegmentXProperties &putName(std::string_view name);

		SegmentXProperties &putCategory(std::string_view category);

		SegmentXProperties &putSku(std::string_view sku);

		SegmentXProperties &putPrice(double price);

		SegmentXProperties &putProductId(std::string_view productId);

		SegmentXProperties &putOrderId(std::string_view orderId);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

		jobject getProps() const { return m_props; }

#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		void* getProps() const { return m_props; }
#endif

	private:
		void _init(int size);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		jobject m_props = nullptr;
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		void* m_props = nullptr;
#endif
	};
} // namespace segment
