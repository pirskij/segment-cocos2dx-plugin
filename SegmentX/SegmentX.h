//
//  SegmentX.h
//  Segment Cocos2dx SDK
//
//  Created by Andrey Pirskiy
//

#pragma once

#include <cocos2d.h>
#include "ForwardDeclare.h"
#include <iostream>

namespace segment {
	class SegmentX {
	public:
		static void setUserId(std::string_view userId, std::string_view key = "");

		static void start(std::string_view writeKey, bool debugMode);

		static void identify(std::string_view userId);

		static void identify(SegmentXTraits const& traits);

		static void identify(std::string_view userId, SegmentXTraits const& traits, SegmentXOptions const& opts);

		static void group(std::string_view groupId);

		static void group(std::string_view groupId, SegmentXTraits const& traits, SegmentXOptions const& opts);

		static void alias(std::string_view newId);

		static void alias(std::string_view newId, SegmentXOptions const& opts);

		static void screen(std::string_view name, SegmentXOptions const& opts);

		static void screen(std::string_view name, SegmentXProperties const& props, SegmentXOptions const& opts);

		static void screen(std::string_view category, std::string_view name, SegmentXProperties const& props, SegmentXOptions const& opts);

		static void track(std::string_view evt);

		static void track(std::string_view evt, SegmentXProperties const& props);

		static void track(std::string_view evt, SegmentXProperties const& props, SegmentXOptions const& opts);

		static void reset();
	};
} // namespace segment