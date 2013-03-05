# Resolution values for bootanimation
TARGET_SCREEN_HEIGHT := 1024
TARGET_SCREEN_WIDTH := 600

# Release name
PRODUCT_RELEASE_NAME := shuttle

# Inherit some common cyanogenmod stuff.
$(call inherit-product, vendor/cm/config/common_full_tablet_wifionly.mk)

# Inherit device configuration for Advent Vega.
$(call inherit-product, device/nvidia/shuttle/full_shuttle.mk)

## Device identifier. This must come after all inclusions
PRODUCT_DEVICE := shuttle
PRODUCT_NAME := cm_shuttle
PRODUCT_BRAND := shuttle
PRODUCT_MODEL := Advent Vega
PRODUCT_MANUFACTURER := shuttle
PRODUCT_BUILD_PROP_OVERRIDES += PRODUCT_NAME=EeePad BUILD_FINGERPRINT=asus/WW_epad/EeePad:4.0.3/IML74K/WW_epad-9.4.3.30-20120604:user/release-keys PRIVATE_BUILD_DESC="WW_epad-user 4.0.3 IML74K WW_epad-9.4.3.30-20120604 release-keys"
