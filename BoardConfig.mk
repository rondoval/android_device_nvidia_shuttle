#
# Copyright (C) 2011 The Android Open-Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

# These two variables are set first, so they can be overridden
# by BoardConfigVendor.mk
BOARD_USES_GENERIC_AUDIO := true
USE_CAMERA_STUB := false

# Default values, possibly overridden by BoardConfigVendor.mk
TARGET_BOARD_INFO_FILE := device/nvidia/shuttle/board-info.txt

# Use the non-open-source parts, if they're present
-include vendor/nvidia/shuttle/BoardConfigVendor.mk

BOARD_USES_AUDIO_LEGACY := false
TARGET_USES_OLD_LIBSENSORS_HAL := false

#TARGET_NO_RECOVERY := true
TARGET_NO_BOOTLOADER := true
TARGET_BOOTLOADER_BOARD_NAME := p10an01

# Keymapping 
BOARD_CUSTOM_RECOVERY_KEYMAPPING := ../../device/nvidia/shuttle/recovery_keys.c

TARGET_CPU_ABI := armeabi-v7a
TARGET_CPU_ABI2 := armeabi
TARGET_CPU_SMP := true
TARGET_ARCH := arm
TARGET_ARCH_VARIANT := armv7-a
TARGET_ARCH_VARIANT_CPU := cortex-a9
TARGET_ARCH_VARIANT_FPU := vfpv3-d16
#TARGET_HAVE_TEGRA_ERRATA_657451 := true
ARCH_ARM_HAVE_TLS_REGISTER := true

#COMMON_GLOBAL_CFLAGS += -DICS_AUDIO_BLOB
#Stock CMDLINE
BOARD_KERNEL_CMDLINE := panic=10 mem=512M@0M nvmem=128M@512M vmalloc=256M video=tegrafb console=ttyS0,115200n8 usbcore.old_scheme_first=1 mtdparts=tegra_nand:2048K@6784K(misc),7168K@9344K(recovery),8192K@17024K(boot),448512K@25728K(system),32768K@474752K(cache),4096K@508032K(staging),11136K@512640K(userdata)
BOARD_KERNEL_BASE := 0x10000000
BOARD_KERNEL_PAGESIZE := 2048

TARGET_NO_RADIOIMAGE := true
TARGET_BOARD_PLATFORM := tegra
TARGET_TEGRA_VERSION := t25
TARGET_BOOTLOADER_BOARD_NAME := shuttle

# Try to build the kernel
TARGET_KERNEL_SOURCE := kernel/nvidia/shuttle
TARGET_KERNEL_CONFIG := tegra_shuttle_defconfig

WIFI_MODULES:
	make -C device/nvidia/shuttle/wlan/AR6kSDK.2.2.1.151/ ANDROID_ENV=1 ANDROID=1 ATH_LINUXPATH=$(KERNEL_OUT) ATH_CROSS_COMPILE_TYPE=$(ARM_EABI_TOOLCHAIN)/arm-eabi-
	mv device/nvidia/shuttle/wlan/AR6kSDK.2.2.1.151/host/.output/tegra-sdio/image/ar6000.ko $(ANDROID_PRODUCT_OUT)/system/lib/hw/wlan
# TODO: change kernel cfg
#	arm-eabi-strip $(ANDROID_PRODUCT_OUT)/system/lib/hw/wlan/ar6000.ko

TARGET_KERNEL_MODULES := WIFI_MODULES

BOARD_EGL_CFG := device/nvidia/shuttle/files/egl.cfg

BOARD_USES_OVERLAY := true
USE_OPENGL_RENDERER := true

TARGET_OTA_ASSERT_DEVICE := n01,shuttle,P10AN01

# Boot animation
TARGET_SCREEN_HEIGHT := 600
TARGET_SCREEN_WIDTH := 1024


BOARD_BOOTIMAGE_PARTITION_SIZE := 8388608
BOARD_RECOVERYIMAGE_PARTITION_SIZE := 7340032
BOARD_SYSTEMIMAGE_PARTITION_SIZE := 459276288
BOARD_USERDATAIMAGE_PARTITION_SIZE := 15728640
BOARD_FLASH_BLOCK_SIZE := 131072

# Wifi related defines
BOARD_WPA_SUPPLICANT_DRIVER := WEXT
WPA_SUPPLICANT_VERSION      := VER_0_8_X
BOARD_WPA_SUPPLICANT_PRIVATE_LIB := lib_driver_cmd_atheros
BOARD_HOSTAPD_DRIVER        := AR6000
BOARD_WLAN_DEVICE           := ar6002
WIFI_DRIVER_MODULE_PATH     := "/system/lib/hw/wlan/ar6000.ko"
WIFI_DRIVER_MODULE_NAME		:= "ar6000"
WIFI_DRIVER_MODULE_ARG		:= ""
WIFI_DRIVER_LOADER_DELAY	:= 3000000

# 3G
BOARD_MOBILEDATA_INTERFACE_NAME := "ppp0"

# Sensors
BOARD_USES_GENERIC_INVENSENSE := false

#BT
BOARD_HAVE_BLUETOOTH := true
#BOARD_HAVE_BLUETOOTH_BCM := true

#GPS
BOARD_HAVE_GPS := true


#Other tweaks
BOARD_USE_SCREENCAP := true
PRODUCT_CHARACTERISTICS := tablet
BOARD_USES_SECURE_SERVICES := true

# Use a smaller subset of system fonts to keep image size lower
SMALLER_FONT_FOOTPRINT := true

# Skip droiddoc build to save build time
BOARD_SKIP_ANDROID_DOC_BUILD := true

TARGET_RECOVERY_PRE_COMMAND := "setrecovery boot-recovery recovery"
BOARD_HDMI_MIRROR_MODE := Scale

# Setting this to avoid boot locks on the system from using the "misc" partition.
BOARD_HAS_NO_MISC_PARTITION := true

BOARD_HAS_NO_SELECT_BUTTON := true

BOARD_VOLD_MAX_PARTITIONS := 11

BOARD_NO_ALLOW_DEQUEUE_CURRENT_BUFFER := true

# Use nicer font rendering
BOARD_USE_SKIA_LCDTEXT := true

# Avoid generating of ldrcc instructions
NEED_WORKAROUND_CORTEX_A9_745320 := true

TARGET_RELEASETOOLS_EXTENSIONS := device/nvidia/shuttle
