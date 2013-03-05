/*
 * Copyright (C) 2012 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define LOG_TAG "Shuttle PowerHAL"
#include <utils/Log.h>

#include <hardware/hardware.h>
#include <hardware/power.h>

static void sysfs_write(const char *path,const char *s)
{
    char buf[80];
    int len;
    int fd = open(path, O_WRONLY);

    if (fd < 0) {
        strerror_r(errno, buf, sizeof(buf));
        ALOGE("Error opening %s: %s\n", path, buf);
        return;
    }

    len = write(fd, s, strlen(s));
    if (len < 0) {
        strerror_r(errno, buf, sizeof(buf));
        ALOGE("Error writing to %s: %s\n", path, buf);
    }

    close(fd);
}

static void sysfs_read(const char *path, char *s,int maxlen)
{
    char buf[80];
    int len;
    int fd = open(path, O_RDONLY);

    if (fd < 0) {
        strerror_r(errno, buf, sizeof(buf));
        ALOGE("Error opening %s: %s\n", path, buf);
        return;
    }

    len = read(fd, s, maxlen);
    if (len < 0) {
        strerror_r(errno, buf, sizeof(buf));
        ALOGE("Error reading from %s: %s\n", path, buf);
    }

    s[len]=0;
    close(fd);
}

/* Maximum speed detected */
static char max_speed[64];
static int last_on = -1;

/* Setting names */
static const char SYSFS_MAX_SPEED[] = "/sys/devices/system/cpu/cpu0/cpufreq/scaling_max_freq";
static const char SYSFS_MIN_SPEED[] = "/sys/devices/system/cpu/cpu0/cpufreq/scaling_min_freq";

static void shuttle_power_init(struct power_module *module)
{
    /* init the vatiables */
    strcpy(max_speed,"1000000");
}

static void shuttle_power_set_interactive(struct power_module *module, int on)
{
    /* Do not apply the same changes twice */
    if (last_on == on) {
        return;
    }

    /* Save the original frequency if disabling screen */
    if (!on) {
        sysfs_read(SYSFS_MAX_SPEED, max_speed, sizeof(max_speed) - 1);
    }

    /*
     * Lower maximum frequency to minimum when screen is off.  CPU 0 and 1 share a
     * cpufreq policy.
     */
    char min_speed[64];
    sysfs_read(SYSFS_MIN_SPEED, min_speed, sizeof(min_speed) - 1);
    sysfs_write(SYSFS_MAX_SPEED, on ? max_speed : min_speed);

/*    sysfs_write("/sys/devices/system/cpu/cpufreq/interactive/boost_factor",
                on ? "0" : "2"); */ /* pointless since min speed = max speed in standby */

}

static void shuttle_power_hint(struct power_module *module, power_hint_t hint,
                            void *data)
{
    /* dummy */
}

static struct hw_module_methods_t power_module_methods = {
    .open = NULL,
};

struct power_module HAL_MODULE_INFO_SYM = {
    .common = {
        .tag = HARDWARE_MODULE_TAG,
        .module_api_version = POWER_MODULE_API_VERSION_0_2,
        .hal_api_version = HARDWARE_HAL_API_VERSION,
        .id = POWER_HARDWARE_MODULE_ID,
        .name = "Shuttle Power HAL",
        .author = "The Android Open Source Project",
        .methods = &power_module_methods,
    },

    .init = shuttle_power_init,
    .setInteractive = shuttle_power_set_interactive,
    .powerHint = shuttle_power_hint,
};
