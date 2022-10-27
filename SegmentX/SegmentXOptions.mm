//
//  SegmentXOptions.mm
//  Segment Cocos2dx SDK
//
//  Created by Andrey Pirskiy
//

#include "SegmentXOptions.h"

using namespace segment;

SegmentXOptions::SegmentXOptions()
{
    ;;
}

SegmentXOptions& SegmentXOptions::setIntegration(std::string_view integrationKey, bool enabled)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (m_opts == nil)
        m_opts = [[NSMutableDictionary alloc] initWithCapacity:5];
    
    BOOL bVal = enabled ? YES : NO;
    [((NSMutableDictionary *)m_opts) setObject:@(bVal)
                                        forKey:[NSString stringWithUTF8String:integrationKey.data()]];
#endif

    return *this;
}
