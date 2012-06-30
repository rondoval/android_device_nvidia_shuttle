#This file adds prebuilt apks to system. Follow the example to add more apks.

LOCAL_PATH := $(call my-dir)

#YouTube
include $(CLEAR_VARS)

LOCAL_MODULE := YouTube
LOCAL_SRC_FILES := $(LOCAL_MODULE).apk
LOCAL_MODULE_CLASS := APPS
LOCAL_CERTIFICATE := PRESIGNED
LOCAL_MODULE_SUFFIX := $(COMMON_ANDROID_PACKAGE_SUFFIX)
LOCAL_MODULE_TAGS := optional

include $(BUILD_PREBUILT)

include $(CLEAR_VARS)

# PlayMusic
LOCAL_MODULE := PlayMusic
LOCAL_SRC_FILES := $(LOCAL_MODULE).apk
LOCAL_MODULE_CLASS := APPS
LOCAL_CERTIFICATE := PRESIGNED
LOCAL_MODULE_SUFFIX := $(COMMON_ANDROID_PACKAGE_SUFFIX)
LOCAL_MODULE_TAGS := optional

include $(BUILD_PREBUILT)

#ChromeBookmarksSyncAdapter
include $(CLEAR_VARS)

LOCAL_MODULE := ChromeBookmarksSyncAdapter
LOCAL_SRC_FILES := $(LOCAL_MODULE).apk
LOCAL_MODULE_CLASS := APPS
LOCAL_CERTIFICATE := PRESIGNED
LOCAL_MODULE_SUFFIX := $(COMMON_ANDROID_PACKAGE_SUFFIX)
LOCAL_MODULE_TAGS := optional

include $(BUILD_PREBUILT)

include $(CLEAR_VARS)

# GalleryGoogle.apk
LOCAL_MODULE := GalleryGoogle
LOCAL_SRC_FILES := $(LOCAL_MODULE).apk
LOCAL_MODULE_CLASS := APPS
LOCAL_CERTIFICATE := PRESIGNED
LOCAL_MODULE_SUFFIX := $(COMMON_ANDROID_PACKAGE_SUFFIX)
LOCAL_MODULE_TAGS := optional

include $(BUILD_PREBUILT)

#GenieWidget.apk
include $(CLEAR_VARS)

LOCAL_MODULE := GenieWidget
LOCAL_SRC_FILES := $(LOCAL_MODULE).apk
LOCAL_MODULE_CLASS := APPS
LOCAL_CERTIFICATE := PRESIGNED
LOCAL_MODULE_SUFFIX := $(COMMON_ANDROID_PACKAGE_SUFFIX)
LOCAL_MODULE_TAGS := optional

include $(BUILD_PREBUILT)

# GoogleBackupTransport.apk
include $(CLEAR_VARS)

LOCAL_MODULE := GoogleBackupTransport
LOCAL_SRC_FILES := $(LOCAL_MODULE).apk
LOCAL_MODULE_CLASS := APPS
LOCAL_CERTIFICATE := PRESIGNED
LOCAL_MODULE_SUFFIX := $(COMMON_ANDROID_PACKAGE_SUFFIX)
LOCAL_MODULE_TAGS := optional

include $(BUILD_PREBUILT)

# GoogleCalendarSyncAdapter.apk
include $(CLEAR_VARS)

LOCAL_MODULE := GoogleCalendarSyncAdapter
LOCAL_SRC_FILES := $(LOCAL_MODULE).apk
LOCAL_MODULE_CLASS := APPS
LOCAL_CERTIFICATE := PRESIGNED
LOCAL_MODULE_SUFFIX := $(COMMON_ANDROID_PACKAGE_SUFFIX)
LOCAL_MODULE_TAGS := optional

include $(BUILD_PREBUILT)

# GoogleContactsSyncAdapter.apk
include $(CLEAR_VARS)

LOCAL_MODULE := GoogleContactsSyncAdapter
LOCAL_SRC_FILES := $(LOCAL_MODULE).apk
LOCAL_MODULE_CLASS := APPS
LOCAL_CERTIFICATE := PRESIGNED
LOCAL_MODULE_SUFFIX := $(COMMON_ANDROID_PACKAGE_SUFFIX)
LOCAL_MODULE_TAGS := optional

include $(BUILD_PREBUILT)

#GoogleFeedback.apk
include $(CLEAR_VARS)

LOCAL_MODULE := GoogleFeedback
LOCAL_SRC_FILES := $(LOCAL_MODULE).apk
LOCAL_MODULE_CLASS := APPS
LOCAL_CERTIFICATE := PRESIGNED
LOCAL_MODULE_SUFFIX := $(COMMON_ANDROID_PACKAGE_SUFFIX)
LOCAL_MODULE_TAGS := optional

include $(BUILD_PREBUILT)

#GoogleLoginService.apk
include $(CLEAR_VARS)

LOCAL_MODULE := GoogleLoginService
LOCAL_SRC_FILES := $(LOCAL_MODULE).apk
LOCAL_MODULE_CLASS := APPS
LOCAL_CERTIFICATE := PRESIGNED
LOCAL_MODULE_SUFFIX := $(COMMON_ANDROID_PACKAGE_SUFFIX)
LOCAL_MODULE_TAGS := optional

include $(BUILD_PREBUILT)

#GooglePartnerSetup.apk
include $(CLEAR_VARS)

LOCAL_MODULE := GooglePartnerSetup
LOCAL_SRC_FILES := $(LOCAL_MODULE).apk
LOCAL_MODULE_CLASS := APPS
LOCAL_CERTIFICATE := PRESIGNED
LOCAL_MODULE_SUFFIX := $(COMMON_ANDROID_PACKAGE_SUFFIX)
LOCAL_MODULE_TAGS := optional

include $(BUILD_PREBUILT)

#GoogleQuickSearchBox.apk
include $(CLEAR_VARS)

LOCAL_MODULE := GoogleQuickSearchBox
LOCAL_SRC_FILES := $(LOCAL_MODULE).apk
LOCAL_MODULE_CLASS := APPS
LOCAL_CERTIFICATE := PRESIGNED
LOCAL_MODULE_SUFFIX := $(COMMON_ANDROID_PACKAGE_SUFFIX)
LOCAL_MODULE_TAGS := optional

include $(BUILD_PREBUILT)

#GoogleServicesFramework.apk
include $(CLEAR_VARS)

LOCAL_MODULE := GoogleServicesFramework
LOCAL_SRC_FILES := $(LOCAL_MODULE).apk
LOCAL_MODULE_CLASS := APPS
LOCAL_CERTIFICATE := PRESIGNED
LOCAL_MODULE_SUFFIX := $(COMMON_ANDROID_PACKAGE_SUFFIX)
LOCAL_MODULE_TAGS := optional

include $(BUILD_PREBUILT)

#GoogleTTS.apk
include $(CLEAR_VARS)

LOCAL_MODULE := GoogleTTS
LOCAL_SRC_FILES := $(LOCAL_MODULE).apk
LOCAL_MODULE_CLASS := APPS
LOCAL_CERTIFICATE := PRESIGNED
LOCAL_MODULE_SUFFIX := $(COMMON_ANDROID_PACKAGE_SUFFIX)
LOCAL_MODULE_TAGS := optional

include $(BUILD_PREBUILT)

# MarketUpdater.apk
include $(CLEAR_VARS)

LOCAL_MODULE := MarketUpdater
LOCAL_SRC_FILES := $(LOCAL_MODULE).apk
LOCAL_MODULE_CLASS := APPS
LOCAL_CERTIFICATE := PRESIGNED
LOCAL_MODULE_SUFFIX := $(COMMON_ANDROID_PACKAGE_SUFFIX)
LOCAL_MODULE_TAGS := optional

include $(BUILD_PREBUILT)

#MediaUploader.apk
include $(CLEAR_VARS)

LOCAL_MODULE := MediaUploader
LOCAL_SRC_FILES := $(LOCAL_MODULE).apk
LOCAL_MODULE_CLASS := APPS
LOCAL_CERTIFICATE := PRESIGNED
LOCAL_MODULE_SUFFIX := $(COMMON_ANDROID_PACKAGE_SUFFIX)
LOCAL_MODULE_TAGS := optional

include $(BUILD_PREBUILT)

#NetworkLocation.apk
include $(CLEAR_VARS)

LOCAL_MODULE := NetworkLocation
LOCAL_SRC_FILES := $(LOCAL_MODULE).apk
LOCAL_MODULE_CLASS := APPS
LOCAL_CERTIFICATE := PRESIGNED
LOCAL_MODULE_SUFFIX := $(COMMON_ANDROID_PACKAGE_SUFFIX)
LOCAL_MODULE_TAGS := optional

include $(BUILD_PREBUILT)

#OneTimeInitializer.apk
include $(CLEAR_VARS)

LOCAL_MODULE := OneTimeInitializer
LOCAL_SRC_FILES := $(LOCAL_MODULE).apk
LOCAL_MODULE_CLASS := APPS
LOCAL_CERTIFICATE := PRESIGNED
LOCAL_MODULE_SUFFIX := $(COMMON_ANDROID_PACKAGE_SUFFIX)
LOCAL_MODULE_TAGS := optional

include $(BUILD_PREBUILT)

#Phonesky.apk
include $(CLEAR_VARS)

LOCAL_MODULE := Phonesky
LOCAL_SRC_FILES := $(LOCAL_MODULE).apk
LOCAL_MODULE_CLASS := APPS
LOCAL_CERTIFICATE := PRESIGNED
LOCAL_MODULE_SUFFIX := $(COMMON_ANDROID_PACKAGE_SUFFIX)
LOCAL_MODULE_TAGS := optional

include $(BUILD_PREBUILT)

#SetupWizard.apk
include $(CLEAR_VARS)

LOCAL_MODULE := SetupWizard
LOCAL_SRC_FILES := $(LOCAL_MODULE).apk
LOCAL_MODULE_CLASS := APPS
LOCAL_CERTIFICATE := PRESIGNED
LOCAL_MODULE_SUFFIX := $(COMMON_ANDROID_PACKAGE_SUFFIX)
LOCAL_MODULE_TAGS := optional

include $(BUILD_PREBUILT)

#Talk.apk
include $(CLEAR_VARS)

LOCAL_MODULE := Talk
LOCAL_SRC_FILES := $(LOCAL_MODULE).apk
LOCAL_MODULE_CLASS := APPS
LOCAL_CERTIFICATE := PRESIGNED
LOCAL_MODULE_SUFFIX := $(COMMON_ANDROID_PACKAGE_SUFFIX)
LOCAL_MODULE_TAGS := optional

include $(BUILD_PREBUILT)

#VoiceSearch.apk
include $(CLEAR_VARS)

LOCAL_MODULE := VoiceSearch
LOCAL_SRC_FILES := $(LOCAL_MODULE).apk
LOCAL_MODULE_CLASS := APPS
LOCAL_CERTIFICATE := PRESIGNED
LOCAL_MODULE_SUFFIX := $(COMMON_ANDROID_PACKAGE_SUFFIX)
LOCAL_MODULE_TAGS := optional

include $(BUILD_PREBUILT)
