This document provides setup instructions for setting up and testing bluetooth on
a Fedora Core 9 system.

9/25/2008


Setting up Fedora Core 9
========================

You can try to install FC9 via a DVD onto a hard-drive based system or
create a liveUSB disk (if you use the same PC for testing other versions of
linux).


Install to HD from DVD install:

   You can install FC9 from here:  http://fedoraproject.org/get-fedora


Install FC9-liveCD to USB disk (create a liveUSB):

   **** MAKE SURE YOUR PC CAN BOOT TO USB DISKS, older PCs may not support this in their BIOS ******

   A 4GB USB drive will be sufficient although 8GB is recommended.
   
   **** Limitations:
         Using LiveUSB has some limitations:
             1. USB flash drives have limited writes (typically 100,000).  The swap partition is disabled on
                a liveUSB.  If you expect to do local compilation and editing you should use a hardisk install
                or use a USB-based harddisk (laptop drive size would be okay).
             2. USB HD access is slower than USB disk.  But I have not noticed any terrible slowdowns.

   *** If your USB disk has U3 support (Sandisk Cruzer), you must disable it.  The disk contains a utility to disable
   U3 support.  As an added check, you should also re-format the drive (as FAT) after your disable U3.


   A windowsPC Utility is available to install a liveCD ISO image directly onto a USB disk and make the disk
   bootable. See: https://fedorahosted.org/liveusb-creator

   This method requires a liveCD ISO file for FC9.  FC9 is the current version that 
   support LiveUSB's persistent data storage.  You can install applications, new tools, SDKs etc..

   You can find the FC9 liveCD here:

            http://fedoraproject.org/get-fedora

   When using the utility, you can setup a persistent area.  I recommend at least 2GB (max).

  
Checking and installing packages:
=================================

To compile our SDK, certain development packages must be installed.

Log in as superuser

execute the following:

   yum install yum-utils rpmdevtools
   yum install kernel-devel  
   yum install gtk2-devel
   yum install dbus-glib-devel
   yum install bluez-utils-gstreamer
   yum install openssl-devel             
   yum install libpcap-devel 
   yum install bluez-libs-devel

Some useful utilities:

   yum install telnet-server
   yum install iperf

For compilation of newer BlueZ utilities and BlueZ stack:

   yum install byacc
   yum install flex
   yum install bison


Setting up and BUILDING OLCA 
=============================

1. Export ATH_BUILD_TYPE=LOCAL_FC9_i686
   Export ATH_BUS_TYPE=SDIO
   
   The default kernel path is set to:

       ATH_LINUXPATH=/lib/modules/2.6.25-14.fc9.i686/build

2. Set your WORKAREA and build normally.  


Testing AR6K
============

1. Unload sdhci (MMC-stack standard host driver)
   
   as root, execute  "rmmod sdhci"

2. Set NETIF, WORKAREA, ATH_PLATFORM variables and execute the load script (same procedure as FC3).


