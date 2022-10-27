//
//  SegmentXTraits.mm
//  Segment Cocos2dx SDK
//
//  Created by Andrey Pirskiy
//

#include "SegmentXTraits.h"
#include <any>

using namespace segment;

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
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (m_traits == nil)
        m_traits = [[NSMutableDictionary alloc] initWithCapacity:size];
#endif
}

SegmentXTraits& SegmentXTraits::putValue(std::string_view key, std::any const &value)
{
    _init(10);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (value.has_value())
    {
        if (value.type() == typeid(int) || value.type() == typeid(int32_t))
        {
            int nVal = value.type() == typeid(int)
                ? std::any_cast<int>(value)
                : std::any_cast<int32_t>(value);

            [((NSMutableDictionary *)m_traits) setObject:[NSNumber numberWithInt:nVal]
                                                  forKey:[NSString stringWithUTF8String:key.data()]];
        }
        else if (value.type() == typeid(int64_t))
        {
            [((NSMutableDictionary *)m_traits) setObject:[NSNumber numberWithLongLong:std::any_cast<int64_t>(value)]
                                                  forKey:[NSString stringWithUTF8String:key.data()]];
        }
        else if (value.type() == typeid(bool))
        {
            BOOL bVal = std::any_cast<bool>(value) ? YES : NO;
            [((NSMutableDictionary *)m_traits) setObject:@(bVal)
                                                  forKey:[NSString stringWithUTF8String:key.data()]];

        }
        else if (value.type() == typeid(std::string))
        {
            [((NSMutableDictionary *)m_traits) setObject:[NSString stringWithUTF8String:std::any_cast<std::string>(value).c_str()]
                                                  forKey:[NSString stringWithUTF8String:key.data()]];
        }
        else if (value.type() == typeid(float))
        {
            [((NSMutableDictionary *)m_traits) setObject:[NSNumber numberWithFloat:std::any_cast<float>(value)]
                                                  forKey:[NSString stringWithUTF8String:key.data()]];
        }
        else if (value.type() == typeid(double))
        {
            [((NSMutableDictionary *)m_traits) setObject:[NSNumber numberWithDouble:std::any_cast<double>(value)]
                                                  forKey:[NSString stringWithUTF8String:key.data()]];
        }
    }
#endif

    return *this;
}

SegmentXTraits& SegmentXTraits::putUserId(std::string_view userId)
{
    _init(10);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    [((NSMutableDictionary *)m_traits) setObject:[NSString stringWithUTF8String:userId.data()]
                                          forKey:@"userId"];
#endif

    return *this;
}

SegmentXTraits& SegmentXTraits::putAnonymousId(std::string_view id)
{
    _init(10);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    [((NSMutableDictionary *)m_traits) setObject:[NSString stringWithUTF8String:id.data()]
                                          forKey:@"anonymousId"];
#endif

    return *this;
}

SegmentXTraits& SegmentXTraits::putAvatar(std::string_view avatar)
{
    _init(10);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    [((NSMutableDictionary *)m_traits) setObject:[NSString stringWithUTF8String:avatar.data()]
                                          forKey:@"avatar"];
#endif

    return *this;
}

SegmentXTraits& SegmentXTraits::putDescription(std::string_view descr)
{
    _init(10);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    [((NSMutableDictionary *)m_traits) setObject:[NSString stringWithUTF8String:descr.data()]
                                          forKey:@"description"];
#endif

    return *this;
}

SegmentXTraits& SegmentXTraits::putEmail(std::string_view email)
{
    _init(10);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    [((NSMutableDictionary *)m_traits) setObject:[NSString stringWithUTF8String:email.data()]
                                          forKey:@"email"];
#endif

    return *this;
}

SegmentXTraits& SegmentXTraits::putGender(std::string_view gender)
{
    _init(10);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    [((NSMutableDictionary *)m_traits) setObject:[NSString stringWithUTF8String:gender.data()]
                                          forKey:@"gender"];
#endif

    return *this;
}

SegmentXTraits& SegmentXTraits::putName(std::string_view name)
{
    _init(10);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    [((NSMutableDictionary *)m_traits) setObject:[NSString stringWithUTF8String:name.data()]
                                          forKey:@"name"];
#endif

    return *this;
}

SegmentXTraits& SegmentXTraits::putUserName(std::string_view userName)
{
    _init(10);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    [((NSMutableDictionary *)m_traits) setObject:[NSString stringWithUTF8String:userName.data()]
                                          forKey:@"username"];
#endif

    return *this;
}

SegmentXTraits& SegmentXTraits::putFirstName(std::string_view firstName)
{
    _init(10);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    [((NSMutableDictionary *)m_traits) setObject:[NSString stringWithUTF8String:firstName.data()]
                                          forKey:@"firstName"];
#endif

    return *this;
}

SegmentXTraits& SegmentXTraits::putLastName(std::string_view lastName)
{
    _init(10);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    [((NSMutableDictionary *)m_traits) setObject:[NSString stringWithUTF8String:lastName.data()]
                                          forKey:@"lastName"];
#endif

    return *this;
}

SegmentXTraits& SegmentXTraits::putPhone(std::string_view phone)
{
    _init(10);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    [((NSMutableDictionary *)m_traits) setObject:[NSString stringWithUTF8String:phone.data()]
                                          forKey:@"phone"];
#endif

    return *this;
}

SegmentXTraits& SegmentXTraits::putWebsite(std::string_view web)
{
    _init(10);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    [((NSMutableDictionary *)m_traits) setObject:[NSString stringWithUTF8String:web.data()]
                                          forKey:@"website"];
#endif

    return *this;
}
