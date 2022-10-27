//
//  SegmentXProperties.mm
//  Segment Cocos2dx SDK
//
//  Created by Andrey Pirskiy
//

#include "SegmentXProperties.h"
#include <any>

using namespace segment;

SegmentXProperties::SegmentXProperties()
{
    ;;
}

SegmentXProperties::SegmentXProperties(int size)
{
    _init(size);
}

void SegmentXProperties::_init(int size)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (m_props == nil)
        m_props = [[NSMutableDictionary alloc] initWithCapacity:size];
#endif
}

SegmentXProperties& SegmentXProperties::putValue(double value)
{
    _init(10);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    [((NSMutableDictionary *)m_props) setObject:[NSNumber numberWithDouble:value]
                                         forKey:@"value"];
#endif

	return *this;
}

SegmentXProperties& SegmentXProperties::putValue(std::string_view key, std::any const &value)
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

            [((NSMutableDictionary *)m_props) setObject:[NSNumber numberWithInt:nVal]
                                                 forKey:[NSString stringWithUTF8String:key.data()]];
        }
        else if (value.type() == typeid(int64_t))
        {
            [((NSMutableDictionary *)m_props) setObject:[NSNumber numberWithLongLong:std::any_cast<int64_t>(value)]
                                                 forKey:[NSString stringWithUTF8String:key.data()]];
        }
        else if (value.type() == typeid(bool))
        {
            BOOL bVal = std::any_cast<bool>(value) ? YES : NO;
            [((NSMutableDictionary *)m_props) setObject:@(bVal)
                                                 forKey:[NSString stringWithUTF8String:key.data()]];

        }
        else if (value.type() == typeid(std::string))
        {
            [((NSMutableDictionary *)m_props) setObject:[NSString stringWithUTF8String:std::any_cast<std::string>(value).c_str()]
                                                 forKey:[NSString stringWithUTF8String:key.data()]];
        }
        else if (value.type() == typeid(float))
        {
            [((NSMutableDictionary *)m_props) setObject:[NSNumber numberWithFloat:std::any_cast<float>(value)]
                                                 forKey:[NSString stringWithUTF8String:key.data()]];
        }
        else if (value.type() == typeid(double))
        {
            [((NSMutableDictionary *)m_props) setObject:[NSNumber numberWithDouble:std::any_cast<double>(value)]
                                                 forKey:[NSString stringWithUTF8String:key.data()]];
        }
    }
#endif

    return *this;
}

SegmentXProperties& SegmentXProperties::putRevenue(double revenue)
{
    _init(10);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    [((NSMutableDictionary *)m_props) setObject:[NSNumber numberWithDouble:revenue]
                                         forKey:@"revenue"];
#endif

    return *this;
}

SegmentXProperties& SegmentXProperties::putCurrency(std::string_view currency)
{
    _init(10);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    [((NSMutableDictionary *)m_props) setObject:[NSString stringWithUTF8String:currency.data()]
                                         forKey:@"currency"];
#endif

    return *this;
}

SegmentXProperties& SegmentXProperties::putTitle(std::string_view title)
{
    _init(10);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    [((NSMutableDictionary *)m_props) setObject:[NSString stringWithUTF8String:title.data()]
                                         forKey:@"title"];
#endif

    return *this;
}

SegmentXProperties& SegmentXProperties::putName(std::string_view name)
{
    _init(10);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    [((NSMutableDictionary *)m_props) setObject:[NSString stringWithUTF8String:name.data()]
                                         forKey:@"name"];
#endif

    return *this;
}

SegmentXProperties& SegmentXProperties::putCategory(std::string_view category)
{
    _init(10);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    [((NSMutableDictionary *)m_props) setObject:[NSString stringWithUTF8String:category.data()]
                                         forKey:@"category"];
#endif

    return *this;
}

SegmentXProperties& SegmentXProperties::putSku(std::string_view sku)
{
    _init(10);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    [((NSMutableDictionary *)m_props) setObject:[NSString stringWithUTF8String:sku.data()]
                                         forKey:@"sku"];
#endif

    return *this;
}

SegmentXProperties& SegmentXProperties::putPrice(double price)
{
    _init(10);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    [((NSMutableDictionary *)m_props) setObject:[NSNumber numberWithDouble:price]
                                         forKey:@"price"];
#endif

    return *this;
}

SegmentXProperties& SegmentXProperties::putProductId(std::string_view productId)
{
    _init(10);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    [((NSMutableDictionary *)m_props) setObject:[NSString stringWithUTF8String:productId.data()]
                                         forKey:@"product_id"];
#endif

    return *this;
}

SegmentXProperties& SegmentXProperties::putOrderId(std::string_view orderId)
{
    _init(10);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    [((NSMutableDictionary *)m_props) setObject:[NSString stringWithUTF8String:orderId.data()]
                                         forKey:@"order_id"];
#endif

    return *this;
}
