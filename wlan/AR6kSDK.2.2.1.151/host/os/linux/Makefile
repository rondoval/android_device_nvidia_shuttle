#######################################################################################
#  AR6K Kernel Module makefile.
#
#    This makefile is invoked by the master makefile in the linux kernel, the linux kernel
#    source must be initially compiled.  The top level make will invoke the main linux kernel
#    makefile which will subsequently pick up this makefile.
#
#######################################################################################


REV ?= 2

# ATHENV
ifeq ($(ATH_ANDROID_ENV),yes)
EXTRA_CFLAGS += -D__linux__ -Wno-error -DANDROID_ECLAIR_ENV=1
endif
# ATHENV

EXTRA_CFLAGS += -I$(ATH_SRC_BASE)/include
EXTRA_CFLAGS += -I$(ATH_SRC_BASE)/../include
# TBDXXX....handle include/AR6002
EXTRA_CFLAGS += -I$(ATH_SRC_BASE)/../include/AR6002
EXTRA_CFLAGS += -I$(ATH_SRC_BASE)/wlan/include
EXTRA_CFLAGS += -I$(ATH_SRC_BASE)/os/linux/include
EXTRA_CFLAGS += -I$(ATH_SRC_BASE)/os/
EXTRA_CFLAGS += -I$(ATH_SRC_BASE)/bmi/include

EXTRA_CFLAGS += -DLINUX -DDEBUG -D__KERNEL__ \
                -DTCMD -DSEND_EVENT_TO_APP -DUSER_KEYS \
                -DNO_SYNC_FLUSH #\
                -DMULTIPLE_FRAMES_PER_INTERRUPT -DAR6000REV$(REV) \
                -DBLOCK_TX_PATH_FLAG \


# ATHENV
ifeq ($(ATH_ANDROID_ENV),yes)
  EXTRA_CFLAGS += -DANDROID_ENV $(ATH_ANDROID_BUILD_FLAGS)
endif
ifeq ($(ATH_EEPROM_FILE_USED),yes)
  EXTRA_CFLAGS += -DEEPROM_FILE_USED
endif
ifeq ($(ATH_SOFTMAC_USED),yes)
  EXTRA_CFLAGS += -DSOFTMAC_USED
endif
ifeq ($(ATH_FORCE_TCMD_MODE),yes)
  EXTRA_CFLAGS += -DFORCE_TCMD_MODE
endif
ifeq ($(ATH_FORCE_ART_MODE),yes)
  EXTRA_CFLAGS += -DFORCE_ART_MODE -DHTC_RAW_INTERFACE
  ATH_HTC_RAW_INT_ENV = yes
endif
# ATHENV

ifeq ($(ATH_HTC_RAW_INT_ENV),yes)
  EXTRA_CFLAGS += -DHTC_RAW_INTERFACE
endif

ifneq ($(ATH_OS_SUB_TYPE),linux_2_4)
# linux 2.6 and higher kernel module build settings
EXTRA_CFLAGS += -DKERNEL_2_6
obj-m += ar6000.o
-include $(ATH_SRC_BASE)/hif/$(ATH_HIF_TYPE)/Makefile
ar6000-objs += ../../htc2/AR6000/ar6k.o        \
			   ../../htc2/AR6000/ar6k_events.o \
               ../../htc2/htc_send.o       \
               ../../htc2/htc_recv.o       \
               ../../htc2/htc_services.o   \
               ../../htc2/htc.o     		  \
               ../../bmi/src/bmi.o            \
               ar6000_drv.o           			\
               ar6000_raw_if.o					\
               netbuf.o							\
               wireless_ext.o					\
               ioctl.o							\
               engine.o							\
               ../../miscdrv/common_drv.o		\
               ../../miscdrv/credit_dist.o					\
               ../../wmi/wmi.o                       \
               ../../wlan/src/wlan_node.o            \
               ../../wlan/src/wlan_recv_beacon.o     \
               ../../wlan/src/wlan_utils.o			 
# ATHENV
ifeq ($(ATH_ANDROID_ENV),yes)
  ar6000-objs += eeprom.o
endif
# ATHENV

endif

ifeq ($(ATH_OS_SUB_TYPE),linux_2_4)
# linux 2.4 kernel module build settings
EXTRA_CFLAGS += -DKERNEL_2_4

O_TARGET := ar6000.o
# need export line for module export
export-objs := ar6000_drv.o
-include $(ATH_SRC_BASE)/hif/$(ATH_HIF_TYPE)/Makefile
obj-y += $(ATH_SRC_BASE)/htc2/htc.o \
         $(ATH_SRC_BASE)/htc2/htc_send.o \
         $(ATH_SRC_BASE)/htc2/htc_recv.o  \
         $(ATH_SRC_BASE)/htc2/htc_services.o \
         $(ATH_SRC_BASE)/htc2/AR6000/ar6k.o  \
         $(ATH_SRC_BASE)/htc2/AR6000/ar6k_events.o  \
         $(ATH_SRC_BASE)/bmi/src/bmi.o \
         $(ATH_SRC_BASE)/wmi/wmi.o \
         $(ATH_SRC_BASE)/wlan/src/wlan_node.o \
         $(ATH_SRC_BASE)/wlan/src/wlan_recv_beacon.o \
         $(ATH_SRC_BASE)/wlan/src/wlan_utils.o \
         $(ATH_SRC_BASE)/os/linux/ar6000_drv.o \
         $(ATH_SRC_BASE)/os/linux/ar6000_raw_if.o \
         $(ATH_SRC_BASE)/os/linux/wireless_ext.o \
         $(ATH_SRC_BASE)/os/linux/ioctl.o 		\
         $(ATH_SRC_BASE)/os/linux/engine.o 		\
         $(ATH_SRC_BASE)/os/linux/netbuf.o     \
         $(ATH_SRC_BASE)/miscdrv/common_drv.o   \
         $(ATH_SRC_BASE)/miscdrv/credit_dist.o

obj-m += htc.o \
         htc_send.o \
         htc_recv.o \
         htc_services.o  \
         ar6k_events.o \
         ar6k.o \
         hif.o  \
         bmi.o  \
         wmi.o  \
         wlan_node.o \
         wlan_recv_beacon.o \
         wlan_utils.o \
         ar6000_drv.o \
         ar6000_raw_if.o \
         common_drv.o \
         credit_dist.o \
         netbuf.o     \
         wireless_ext.o \
         ioctl.o        \
         engine.o        \
         ar6000.o
              
include $(ATH_LINUXPATH)/Rules.make
endif
