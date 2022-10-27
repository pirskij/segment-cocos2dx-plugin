//
//  SegmentXApple.mm
//  Segment Cocos2dx SDK
//
//  Created by Andrey Pirskiy
//

#include "SegmentXApple.h"
#include "SegmentXProperties.h"
#include "SegmentXOptions.h"
#include "SegmentXTraits.h"
#import <Analytics/SEGAnalytics.h>
#import <AdSupport/AdSupport.h>

using namespace segment;

/* Null, because instance will be initialized on demand. */
SegmentXApple* SegmentXApple::instance = 0;
namespace
{
    std::string s_strUserId;
    std::string s_strUserIdKey = "userId";
}

SegmentXApple* SegmentXApple::getInstance() {
    if (instance == 0) {
        instance = new SegmentXApple();
    }
    
    return instance;
}

SegmentXApple::SegmentXApple() {}

void SegmentXApple::setUserId(std::string_view userId, std::string_view key)
{
    s_strUserId = userId;
    if (!key.empty())
        s_strUserIdKey = key;
    
    identify(s_strUserId);
}

void SegmentXApple::start(std::string_view writeKey, bool debugMode)
{
    if (debugMode)
        [SEGAnalytics debug:YES];

    SEGAnalyticsConfiguration *configuration = [SEGAnalyticsConfiguration
                                                configurationWithWriteKey: [NSString stringWithUTF8String:writeKey.data()]];
    configuration.trackApplicationLifecycleEvents = YES; // Enable this to record certain application events automatically!

    configuration.flushAt = 1;
    if (@available(iOS 14, *)) {
        // Enable advertising collection
        configuration.enableAdvertisingTracking = YES;
        // Set the block to be called when the advertisingID is needed
        // NOTE: In iOS 14, you'll need to manually do authorization elsewhere and only when it has been authorized, return the advertisingIdentifier to segment via the block below
        configuration.adSupportBlock = ^{
            return [[[ASIdentifierManager sharedManager] advertisingIdentifier] UUIDString];
        };
    }
    [SEGAnalytics setupWithConfiguration:configuration];
}

void SegmentXApple::identify(std::string_view userId)
{
    SegmentXTraits traits(1);
    SegmentXOptions opts;
    identify(userId, traits, opts);
}

void SegmentXApple::identify(SegmentXTraits const& traits)
{
    SegmentXOptions opts;
    identify("", traits, opts);
}

void SegmentXApple::identify(std::string_view userId, SegmentXTraits const& traits, SegmentXOptions const& opts)
{
    NSMutableDictionary* nstraits = (NSMutableDictionary *)traits.getTraits();
    if (!s_strUserId.empty() && userId.empty())
    {
        [nstraits setObject:[NSString stringWithUTF8String:s_strUserId.c_str()]
                     forKey:[NSString stringWithUTF8String:s_strUserIdKey.c_str()]];
    }

    NSMutableDictionary* nsopts = (NSMutableDictionary *)opts.getOptions();
    
    [[SEGAnalytics sharedAnalytics] identify:[NSString stringWithUTF8String:userId.data()]
                                      traits:nstraits
                                     options:nsopts];
}

void SegmentXApple::group(std::string_view groupId)
{
    SegmentXTraits traits(1);
    SegmentXOptions opts;
    group(groupId, traits, opts);
}

void SegmentXApple::group(std::string_view groupId, SegmentXTraits const& traits, SegmentXOptions const& opts)
{
    NSMutableDictionary* nstraits = (NSMutableDictionary *)traits.getTraits();
    if (!s_strUserId.empty())
    {
        [nstraits setObject:[NSString stringWithUTF8String:s_strUserId.c_str()]
                     forKey:[NSString stringWithUTF8String:s_strUserIdKey.c_str()]];
    }
    NSMutableDictionary* nsopts = (NSMutableDictionary *)opts.getOptions();
    
    [[SEGAnalytics sharedAnalytics] group:[NSString stringWithUTF8String:groupId.data()]
                                   traits:nstraits
                                  options:nsopts];
}

void SegmentXApple::alias(std::string_view newId)
{
    SegmentXOptions opts;
    alias(newId, opts);
}

void SegmentXApple::alias(std::string_view newId, SegmentXOptions const& opts)
{
    NSMutableDictionary* nsopts = (NSMutableDictionary *)opts.getOptions();
    
    [[SEGAnalytics sharedAnalytics] alias:[NSString stringWithUTF8String:newId.data()]
                                  options:nsopts];
}

void SegmentXApple::screen(std::string_view name, SegmentXOptions const& opts)
{
    SegmentXProperties props(1);
    screen(name, props, opts);
}

void SegmentXApple::screen(std::string_view name, SegmentXProperties const& props, SegmentXOptions const& opts)
{
    NSMutableDictionary* nsprops = (NSMutableDictionary *)props.getProps();
    if (!s_strUserId.empty())
    {
        [nsprops setObject:[NSString stringWithUTF8String:s_strUserId.c_str()]
                    forKey:[NSString stringWithUTF8String:s_strUserIdKey.c_str()]];
    }
    
    NSMutableDictionary* nsopts = (NSMutableDictionary *)opts.getOptions();
    
    [[SEGAnalytics sharedAnalytics] screen:[NSString stringWithUTF8String:name.data()]
                                properties:nsprops
                                   options:nsopts];
}

void SegmentXApple::screen(std::string_view category, std::string_view name, SegmentXProperties const& props, SegmentXOptions const& opts)
{
    NSMutableDictionary* nsprops = (NSMutableDictionary *)props.getProps();
    [nsprops setObject:[NSString stringWithUTF8String:category.data()]
                forKey:@"category"];
    if (!s_strUserId.empty())
    {
        [nsprops setObject:[NSString stringWithUTF8String:s_strUserId.c_str()]
                    forKey:[NSString stringWithUTF8String:s_strUserIdKey.c_str()]];
    }
    
    NSMutableDictionary* nsopts = (NSMutableDictionary *)opts.getOptions();
    
    [[SEGAnalytics sharedAnalytics] screen:[NSString stringWithUTF8String:name.data()]
                                properties:nsprops
                                   options:nsopts];
}

void SegmentXApple::track(std::string_view evt)
{
    SegmentXProperties props(1);
    track(evt, props);
}

void SegmentXApple::track(std::string_view evt, SegmentXProperties const& props)
{
    SegmentXOptions opts;
    track(evt, props, opts);
}

void SegmentXApple::track(std::string_view evt, SegmentXProperties const& props, SegmentXOptions const& opts)
{
    NSMutableDictionary* nsprops = (NSMutableDictionary *)props.getProps();
    if (!s_strUserId.empty())
    {
        [nsprops setObject:[NSString stringWithUTF8String:s_strUserId.c_str()]
                    forKey:[NSString stringWithUTF8String:s_strUserIdKey.c_str()]];
    }

    NSMutableDictionary* nsopts = (NSMutableDictionary *)opts.getOptions();
    
    [[SEGAnalytics sharedAnalytics]  track:[NSString stringWithUTF8String:evt.data()]
                                properties:nsprops
                                   options:nsopts];
}

void SegmentXApple::reset()
{
    [[SEGAnalytics sharedAnalytics] reset];
}

