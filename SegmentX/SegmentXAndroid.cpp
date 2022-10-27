//  SegmentXAndroid.cpp
//  Segment Cocos2dx SDK
//
//  Created by Andrey Pirskiy
//

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include <util/helpers/android/AndroidHelper.h>
#include "SegmentXAndroid.h"
#include "SegmentXProperties.h"
#include "SegmentXOptions.h"
#include "SegmentXTraits.h"
#include "SegmentX.h"

using namespace segment;

bool SegmentXAndroid::s_bInited = false;

namespace {
/*
 * Get application context
 *  */
    cocos2d::JniMethodInfo _getContext()
    {
        cocos2d::JniMethodInfo jmiContext;
        if (!cocos2d::JniHelper::getStaticMethodInfo(jmiContext,
                                                    "org/cocos2dx/lib/Cocos2dxActivity",
                                                    "getContext", "()Landroid/content/Context;"))
        {
            CCLOGERROR("%s", "SegmentXAndroid::_getContext() - Can`t get application context");
        }
        return jmiContext;
    }

/*
 * Segment Analytics.with(Context ctx)
 *  */
    cocos2d::JniMethodInfo _getAnalyticsInstance()
    {
        cocos2d::JniMethodInfo jmiInstance;

        if (!cocos2d::JniHelper::getStaticMethodInfo(jmiInstance,
                                                     "com/segment/analytics/Analytics",
                                                     "with",
                                                     "(Landroid/content/Context;)Lcom/segment/analytics/Analytics;"))
        {
            CCLOGERROR("%s", "SegmentXAndroid::_getAnalyticsInstance() - 'Segment Analytics library' is not loaded");
        }

        return jmiInstance;
    }
}

namespace {
    static std::string s_strWriteKey;
    static std::string s_strUserIdKey = "userId";
    static std::string s_strUserId;
    static bool s_bDebugMode = false;

    void _startInUIThread(std::string_view writeKey)
    {
        cocos2d::JniMethodInfo jmiInit;
        if (!cocos2d::JniHelper::getMethodInfo(jmiInit,
                                               "com/segment/analytics/Analytics$Builder",
                                               "<init>",
                                               "(Landroid/content/Context;Ljava/lang/String;)V"))
        {
            CCLOGERROR("%s", "SegmentXAndroid::start - 'Segment Analytics library' is not loaded");
            return;
        }

        auto jmiContext = _getContext();
        auto joContext = jmiContext.env->CallStaticObjectMethod(jmiContext.classID, jmiContext.methodID);

        auto jstrWriteKey = jmiInit.env->NewStringUTF(writeKey.data());

        // instance of 'new Analytics.Builder(Context ctx, String key)'
        auto joBuilder = jmiInit.env->NewObject(jmiInit.classID, jmiInit.methodID,
                                                            joContext, jstrWriteKey);

        /*auto useMethodId = jmiInit.env->GetMethodID(jmiInit.classID,
                                                      "use",
                                                      "(Lcom/segment/analytics/integrations/Integration$Factory;)Lcom/segment/analytics/Analytics$Builder;");

        auto integrationCls = jmiInit.env->FindClass("com/segment/analytics/android/integrations/appsflyer/AppsflyerIntegration");
        auto factoryFieldID = jmiInit.env->GetStaticFieldID(integrationCls, "FACTORY", "Lcom/segment/analytics/integrations/Integration$Factory;");
        auto appsFlyerFactory = jmiInit.env->GetStaticObjectField(integrationCls, factoryFieldID);

        // call 'Builder.use' method
        jmiInit.env->CallObjectMethod(joBuilder, useMethodId, appsFlyerFactory);*/

        /*integrationCls = jmiInit.env->FindClass("com/segment/analytics/android/integrations/mixpanel/MixpanelIntegration");
        factoryFieldID = jmiInit.env->GetStaticFieldID(integrationCls, "FACTORY", "Lcom/segment/analytics/integrations/Integration$Factory;");
        auto mixPanelFactory = jmiInit.env->GetStaticObjectField(integrationCls, factoryFieldID);

        // call 'Builder.use' method
        jmiInit.env->CallObjectMethod(joBuilder, useMethodId, mixPanelFactory);*/

        if (s_bDebugMode) {
            auto logMethodId = jmiInit.env->GetMethodID(jmiInit.classID,
                                                        "logLevel",
                                                        "(Lcom/segment/analytics/Analytics$LogLevel;)Lcom/segment/analytics/Analytics$Builder;");

            auto enumCls = jmiInit.env->FindClass("com/segment/analytics/Analytics$LogLevel");
            auto verboseFieldID = jmiInit.env->GetStaticFieldID(enumCls, "VERBOSE", "Lcom/segment/analytics/Analytics$LogLevel;");
            auto verboseField = jmiInit.env->GetStaticObjectField(enumCls, verboseFieldID);

            // call 'Builder.logLevel' method
            jmiInit.env->CallObjectMethod(joBuilder, logMethodId, verboseField);
        }

        auto taleMethodId = jmiInit.env->GetMethodID(jmiInit.classID,
                                                     "trackApplicationLifecycleEvents",
                                                     "()Lcom/segment/analytics/Analytics$Builder;");

        // call 'Builder.trackApplicationLifecycleEvents' method
        jmiInit.env->CallObjectMethod(joBuilder, taleMethodId);


       /* auto taiMethodId = jmiInit.env->GetMethodID(jmiInit.classID,
                                                     "trackAttributionInformation",
                                                     "()Lcom/segment/analytics/Analytics$Builder;");

        // call 'Builder.trackAttributionInformation' method
        jmiInit.env->CallObjectMethod(joBuilder, taiMethodId);*/

        auto buildMethodId = jmiInit.env->GetMethodID(jmiInit.classID, "build", "()Lcom/segment/analytics/Analytics;");

        // call 'Builder.build()' method
        auto joAnal = jmiInit.env->CallObjectMethod(joBuilder, buildMethodId);

        auto analCls = jmiInit.env->FindClass("com/segment/analytics/Analytics");

        auto ssiMethodId = jmiInit.env->GetStaticMethodID(analCls,
                                                          "setSingletonInstance",
                                                          "(Lcom/segment/analytics/Analytics;)V");

        // Set Analytics singleton instance from built analytics object
        jmiInit.env->CallStaticVoidMethod(analCls, ssiMethodId, joAnal);

        jmiInit.env->DeleteLocalRef(joAnal);
        jmiInit.env->DeleteLocalRef(joBuilder);
        jmiInit.env->DeleteLocalRef(jstrWriteKey);
        jmiInit.env->DeleteLocalRef(jmiInit.classID);
        jmiContext.env->DeleteLocalRef(joContext);
        jmiContext.env->DeleteLocalRef(jmiContext.classID);
        cocos2d::log("SegmentXAndroid::start - SUCCESS");
    }
};

void SegmentXAndroid::setUserId(std::string_view userId, std::string_view key)
{
    s_strUserId = userId;
    if (!key.empty())
        s_strUserIdKey = key;

    identify(s_strUserId);
}

void SegmentXAndroid::start(std::string_view writeKey, bool debugMode)
{
    s_strWriteKey = writeKey;
    s_bDebugMode = debugMode;
    cocos2d::JniHelper::performFunctionInUIThread([]() { _startInUIThread(s_strWriteKey); });
}

void SegmentXAndroid::identify(std::string_view userId)
{
    SegmentXTraits traits;
    SegmentXOptions opts;
    //opts.setIntegration("All", true);
    //opts.setIntegration("AppsFlyer", true);

    identify(userId, traits, opts);
}

void SegmentXAndroid::identify(SegmentXTraits const& traits)
{
    SegmentXOptions opts;
    //opts.setIntegration("All", true);
    //opts.setIntegration("AppsFlyer", true);

    identify("", traits, opts);
}

void SegmentXAndroid::identify(std::string_view userId, SegmentXTraits const& traits, SegmentXOptions const& opts)
{
    auto jmiAnal = _getAnalyticsInstance();
    auto jmiContext = _getContext();
    auto joContext = jmiContext.env->CallStaticObjectMethod(jmiContext.classID, jmiContext.methodID);

    auto joAnal = jmiAnal.env->CallStaticObjectMethod(jmiAnal.classID, jmiAnal.methodID, joContext);
    if (joAnal == nullptr)
        return;

    auto jstrUserId = jmiAnal.env->NewStringUTF(userId.data());
    auto traitsTmp = traits;
    if (!userId.empty() && !s_strUserIdKey.empty())
        traitsTmp.putValue(s_strUserIdKey, userId);

    auto methodId = jmiAnal.env->GetMethodID(jmiAnal.classID, "identify",
            "(Ljava/lang/String;Lcom/segment/analytics/Traits;Lcom/segment/analytics/Options;)V");

    jmiAnal.env->CallVoidMethod(joAnal, methodId, jstrUserId, traitsTmp.getTraits(), opts.getOptions());

    jmiAnal.env->DeleteLocalRef(joAnal);
    if (jstrUserId != nullptr)
        jmiAnal.env->DeleteLocalRef(jstrUserId);
    jmiAnal.env->DeleteLocalRef(jmiAnal.classID);
    jmiContext.env->DeleteLocalRef(joContext);
    jmiContext.env->DeleteLocalRef(jmiContext.classID);
}

void SegmentXAndroid::group(std::string_view groupId)
{
    SegmentXTraits traits;
    SegmentXOptions opts;
    //opts.setIntegration("All", true);
    //opts.setIntegration("AppsFlyer", true);

    group(groupId, traits, opts);
}

void SegmentXAndroid::group(std::string_view groupId, SegmentXTraits const& traits, SegmentXOptions const& opts)
{
    auto jmiAnal = _getAnalyticsInstance();
    auto jmiContext = _getContext();
    auto joContext = jmiContext.env->CallStaticObjectMethod(jmiContext.classID, jmiContext.methodID);

    auto joAnal = jmiAnal.env->CallStaticObjectMethod(jmiAnal.classID, jmiAnal.methodID, joContext);
    if (joAnal == nullptr)
        return;

    auto jstrGroupId = jmiAnal.env->NewStringUTF(groupId.data());

    auto methodId = jmiAnal.env->GetMethodID(jmiAnal.classID, "group",
            "(Ljava/lang/String;Lcom/segment/analytics/Traits;Lcom/segment/analytics/Options;)V");

    auto traitsTmp = traits;
    if (!s_strUserId.empty() && !s_strUserIdKey.empty())
        traitsTmp.putValue(s_strUserIdKey, s_strUserId);

    jmiAnal.env->CallVoidMethod(joAnal, methodId, jstrGroupId, traitsTmp.getTraits(), opts.getOptions());

    jmiAnal.env->DeleteLocalRef(joAnal);
    jmiAnal.env->DeleteLocalRef(jstrGroupId);
    jmiAnal.env->DeleteLocalRef(jmiAnal.classID);
    jmiContext.env->DeleteLocalRef(joContext);
    jmiContext.env->DeleteLocalRef(jmiContext.classID);
}

void SegmentXAndroid::alias(std::string_view newId)
{
    SegmentXOptions opts;
    //opts.setIntegration("All", true);
    //opts.setIntegration("AppsFlyer", true);

    alias(newId, opts);
}

void SegmentXAndroid::alias(std::string_view newId, SegmentXOptions const& opts)
{
    auto jmiAnal = _getAnalyticsInstance();
    auto jmiContext = _getContext();
    auto joContext = jmiContext.env->CallStaticObjectMethod(jmiContext.classID, jmiContext.methodID);

    auto joAnal = jmiAnal.env->CallStaticObjectMethod(jmiAnal.classID, jmiAnal.methodID, joContext);
    if (joAnal == nullptr)
        return;

    auto jstrNewId = jmiAnal.env->NewStringUTF(newId.data());

    auto methodId = jmiAnal.env->GetMethodID(jmiAnal.classID, "alias",
            "(Ljava/lang/String;Lcom/segment/analytics/Options;)V");

    jmiAnal.env->CallVoidMethod(joAnal, methodId, jstrNewId, opts.getOptions());

    jmiAnal.env->DeleteLocalRef(joAnal);
    jmiAnal.env->DeleteLocalRef(jstrNewId);
    jmiAnal.env->DeleteLocalRef(jmiAnal.classID);
    jmiContext.env->DeleteLocalRef(joContext);
    jmiContext.env->DeleteLocalRef(jmiContext.classID);
}

void SegmentXAndroid::screen(std::string_view name, SegmentXOptions const& opts)
{
    SegmentXProperties props;
    screen("", name, props, opts);
}

void SegmentXAndroid::screen(std::string_view name, SegmentXProperties const& props, SegmentXOptions const& opts)
{
    screen("", name, props, opts);
}

void SegmentXAndroid::screen(std::string_view category, std::string_view name, SegmentXProperties const& props, SegmentXOptions const& opts)
{
    auto jmiAnal = _getAnalyticsInstance();
    auto jmiContext = _getContext();
    auto joContext = jmiContext.env->CallStaticObjectMethod(jmiContext.classID, jmiContext.methodID);

    auto joAnal = jmiAnal.env->CallStaticObjectMethod(jmiAnal.classID, jmiAnal.methodID, joContext);
    if (joAnal == nullptr)
        return;

    jstring jstrCategory = nullptr;
    if (!category.empty())
        jstrCategory = jmiAnal.env->NewStringUTF(category.data());

    auto jstrName = jmiAnal.env->NewStringUTF(name.data());

    auto methodId = jmiAnal.env->GetMethodID(
            jmiAnal.classID,
            "screen",
            "(Ljava/lang/String;Ljava/lang/String;Lcom/segment/analytics/Properties;Lcom/segment/analytics/Options;)V");

    auto propsTmp = props;
    if (!s_strUserId.empty() && !s_strUserIdKey.empty())
        propsTmp.putValue(s_strUserIdKey, s_strUserId);

    jmiAnal.env->CallVoidMethod(joAnal, methodId, jstrCategory, jstrName, propsTmp.getProps(), opts.getOptions());

    jmiAnal.env->DeleteLocalRef(joAnal);
    jmiAnal.env->DeleteLocalRef(jstrName);
    if (jstrCategory != nullptr)
        jmiAnal.env->DeleteLocalRef(jstrCategory);
    jmiAnal.env->DeleteLocalRef(jmiAnal.classID);
    jmiContext.env->DeleteLocalRef(joContext);
    jmiContext.env->DeleteLocalRef(jmiContext.classID);
}

void SegmentXAndroid::track(std::string_view evt)
{
    SegmentXProperties props;

    track(evt, props);
}

void SegmentXAndroid::track(std::string_view evt, SegmentXProperties const& props)
{
    SegmentXOptions opts;

    track(evt, props, opts);
}

void SegmentXAndroid::track(std::string_view evt, SegmentXProperties const& props, SegmentXOptions const& opts)
{
    auto jmiAnal = _getAnalyticsInstance();
    auto jmiContext = _getContext();
    auto joContext = jmiContext.env->CallStaticObjectMethod(jmiContext.classID, jmiContext.methodID);

    auto joAnal = jmiAnal.env->CallStaticObjectMethod(jmiAnal.classID, jmiAnal.methodID, joContext);
    if (joAnal == nullptr)
        return;
    auto jstrEvt = jmiAnal.env->NewStringUTF(evt.data());

    auto methodId = jmiAnal.env->GetMethodID(jmiAnal.classID, "track",
                                                "(Ljava/lang/String;Lcom/segment/analytics/Properties;Lcom/segment/analytics/Options;)V");

    auto propsTmp = props;
    if (!s_strUserId.empty() && !s_strUserIdKey.empty())
        propsTmp.putValue(s_strUserIdKey, s_strUserId);

    jmiAnal.env->CallVoidMethod(joAnal, methodId, jstrEvt, propsTmp.getProps(), opts.getOptions());

    jmiAnal.env->DeleteLocalRef(joAnal);
    jmiAnal.env->DeleteLocalRef(jstrEvt);
    jmiAnal.env->DeleteLocalRef(jmiAnal.classID);
    jmiContext.env->DeleteLocalRef(joContext);
    jmiContext.env->DeleteLocalRef(jmiContext.classID);
}

void SegmentXAndroid::reset()
{
    auto jmiAnal = _getAnalyticsInstance();
    auto jmiContext = _getContext();
    auto joContext = jmiContext.env->CallStaticObjectMethod(jmiContext.classID, jmiContext.methodID);

    auto joAnal = jmiAnal.env->CallStaticObjectMethod(jmiAnal.classID, jmiAnal.methodID, joContext);
    if (joAnal == nullptr)
        return;

    auto methodId = jmiAnal.env->GetMethodID(jmiAnal.classID, "reset", "()V");

    jmiAnal.env->CallVoidMethod(joAnal, methodId);

    jmiAnal.env->DeleteLocalRef(joAnal);
    jmiAnal.env->DeleteLocalRef(jmiAnal.classID);
    jmiContext.env->DeleteLocalRef(joContext);
    jmiContext.env->DeleteLocalRef(jmiContext.classID);
}
#endif
