/*
 * Copyright (C) 2014 The Android Open Source Project
 *
 */

#define LOG_TAG "CtrlSys_Hal"

//#include <hardware/hardware.h>

//#include <fcntl.h>
//#include <errno.h>

//#include <cutils/log.h>
//#include <cutils/atomic.h>
//#include <android/log.h>

//#include <sys/types.h>
//#include <sys/stat.h>
//#include <fcntl.h>
//#include <sys/ioctl.h>
//#include <unistd.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <linux/types.h>

#include <ctrlsys.h>

#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG , LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO  , LOG_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN  , LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR  , LOG_TAG, __VA_ARGS__)


/*

 */
int _operateFile(char* file, char* buf, int len, char* way)
{
    int fd=0;

    fd = open(file, O_RDWR);
    if(fd < 0)
    {
        LOGE("Could not open (write-only) SysFs attribute \"%s\" (%s).", file, strerror(errno));
        return errno;
    }
    LOGI("open success :%s",file);

    if(strncmp(way, "w", 1) == 0)
    {
        write(fd, buf, len);
    }
    else if(strncmp(way, "r", 1) == 0)
    {
        read(fd, buf, len);
    }
    else
    {
        LOGE("the cmd is error");
        close(fd);
        return 0;
    }

    close(fd);
    return 0;
}

//==================================================================

static int ctrlsys_device_close(struct hw_device_t* device)
{
    struct ctrlsys_control_device_t* ctx = (struct ctrlsys_control_device_t*) device;
    if (ctx)
    {
        free(ctx);
    }
    return 0;
}
static int ctrlsys_device_open(const struct hw_module_t* module, const char* name, struct hw_device_t** device)
{
    struct ctrlsys_control_device_t *dev;
    LOGI("CtrlSys device starting open in HAL");

    dev = (struct ctrlsys_control_device_t *) malloc(sizeof(*dev));
    if(dev<=0)
    {
        LOGE("fail malloc CtrlSys device in HAL");
        return -1;
    }

    memset(dev, 0, sizeof(*dev));

    dev->common.tag = HARDWARE_DEVICE_TAG;
    dev->common.version = 0;
    dev->common.module = (struct hw_module_t*)module;
    dev->common.close = ctrlsys_device_close;

    dev->operateFile = _operateFile;

    *device = &dev->common;
    LOGI("CtrlSys device open in HAL");

success:
    return 0;
}

static struct hw_module_methods_t ctrlsys_module_methods =
{ open: ctrlsys_device_open };

struct ctrlsys_module_t HAL_MODULE_INFO_SYM =
{
common:
    {
tag :
HARDWARE_MODULE_TAG, version_major : 1, version_minor : 0, id :
CTRLSYS_HARDWARE_MODULE_ID, name : "CtrlSys Stub"
, author : "The blus Open Source Project"
        , methods
:
        &ctrlsys_module_methods,
    }
    /* supporting APIs go here */
};

