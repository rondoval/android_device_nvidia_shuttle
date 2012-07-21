# Copyright (C) 2011 The CyanogenMod Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# This file is generated by device/nvidia/shuttle/setup-makefiles.sh

LOCAL_PATH := device/nvidia/shuttle

# Copy Google Apps
PRODUCT_COPY_FILES += \
	$(call find-copy-subdir-files,*,device/nvidia/shuttle/gapps/system/lib,system/lib) \
	$(call find-copy-subdir-files,*,device/nvidia/shuttle/gapps/system/etc,system/etc) \
	$(call find-copy-subdir-files,*,device/nvidia/shuttle/gapps/system/framework,system/framework) \
	$(call find-copy-subdir-files,*,device/nvidia/shuttle/gapps/system/tts,system/tts)	
#	$(call find-copy-subdir-files,*,device/nvidia/shuttle/gapps/system/usr,system/usr)

PRODUCT_PACKAGES += \
	ChromeBookmarksSyncAdapter \
	GenieWidget \
        GmsCore \
	GoogleBackupTransport \
	GoogleCalendarSyncAdapter \
	GoogleContactsSyncAdapter \
        GoogleEars \
	GoogleFeedback \
	GoogleLoginService \
	GooglePartnerSetup \
	GoogleServicesFramework \
	GoogleTTS \
	MediaUploader \
	NetworkLocation \
	OneTimeInitializer \
	Phonesky \
	SetupWizard \
	Talk \
        Velvet \
	VoiceSearchStub \
	YouTube \
	PlayMusic

