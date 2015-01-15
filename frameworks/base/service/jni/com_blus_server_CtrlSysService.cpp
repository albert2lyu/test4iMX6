/*
 * Copyright (C) 2014 The Android Open Source Project
 *
 */

#define LOG_TAG "CtrlSys_JNI"
#include "utils/Log.h"

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>

#include <android/log.h>
#include "JNIHelp.h"
#include "utils/misc.h"

#include <jni.h>
#include <ctrlsys.h>

#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG , LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO  , LOG_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN  , LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR  , LOG_TAG, __VA_ARGS__)


using namespace android;

// ----------------------------------------------------------------------------
//static char RBuffer[BUF_MAX_SIZE];
//static char TBuffer[BUF_MAX_SIZE];
struct ctrlsys_control_device_t *sctrlsysDevice = NULL;


//============================================================================
static inline int ctrlsys_control_open(const struct hw_module_t* module, struct ctrlsys_control_device_t** device)
{
    return module->methods->open(module,
                                 CTRLSYS_HARDWARE_MODULE_ID, (struct hw_device_t**) device);
}

// ----------------------------------------------------------------------------
/*
 * Class:
 * Method:    Ctrlsys_init
 * Signature: ()Z
 */
static jboolean ctrlsys_init(JNIEnv *env, jclass clazz)
{
    ctrlsys_module_t* module;

    if (hw_get_module(CTRLSYS_HARDWARE_MODULE_ID, (const hw_module_t**) &module) == 0)
    {
        LOGI("CtrlSysService JNI: CtrlSys Stub found.");
        if (ctrlsys_control_open(&module->common, &sctrlsysDevice) == 0)
        {
            LOGI("CtrlSysService JNI: Got Stub operations.");
            return true;
        }
    }

    LOGE("CtrlSysService JNI: Get Stub operations failed.");
    return false;
}

/*
 * Class:
 * Method:    _operateFile
 * Signature: (Ljava/lang/String;[BILjava/lang/String;)I
 */
static jint ctrlsys_operateFile(JNIEnv *env, jclass clazz, jstring _file, jbyteArray _buf, jint _len, jstring _way)
{
    char *pbuf = 0;
    int flag  = 0;
    int len =_len;
    char* pway = (char*) env->GetStringUTFChars(_way, 0);
    char* pfile =(char*) env->GetStringUTFChars(_file, 0);
    pbuf = (char*)malloc(100);
    memset(pbuf, 0, 100);

    if(sctrlsysDevice == NULL)
    {
        LOGE("CtrlSysDevice JNI: sctrlsysDevice was not fetched correctly.");
        return -1;
    }
    else
    {
        //jstring js = (jstring)(env->GetObjectArrayElement( _buf, 0));
        //pbuf = (char*) (env->GetStringUTFChars( js, 0));

        env->GetByteArrayRegion(_buf, 0, len, (jbyte*)pbuf);

        flag = sctrlsysDevice->operateFile(pfile, pbuf, len, pway);

        env->SetByteArrayRegion(_buf, 0, len,(jbyte*)pbuf);

        LOGI("CtrlSysDevice Operate file:%s success.",pfile);
        free(pbuf);
        return flag;
    }

}

// ---------------------------------------------------------------------------
//
/*
 * Array of methods.
 *
 * Each entry has three fields: the name of the method, the method
 * signature, and a pointer to the native implementation.
 */
static const JNINativeMethod gMethods[] =
{
    { "_init", "()Z", (void*) ctrlsys_init },
    { "_operateFile", "(Ljava/lang/String;[BILjava/lang/String;)I", (void*) ctrlsys_operateFile },
};

static int registerMethods(JNIEnv* env)
{
    static const char* const kClassName = "com/blus/server/CtrlSysService";
    jclass clazz;

    /* look up the class */
    clazz = env->FindClass(kClassName);
    if (clazz == NULL)
    {
        LOGE("Can't find class %s\n", kClassName);
        return -1;
    }

    /* register all the methods */
    if (env->RegisterNatives(clazz, gMethods, sizeof(gMethods) / sizeof(gMethods[0])) != JNI_OK)
    {
        LOGE("Failed registering methods for %s\n", kClassName);
        return -1;
    }
    LOGI("Register Method succes!\n");

    /* fill out the rest of the ID cache */
    return 0;
}

int register_android_server_CtrlSysService(JNIEnv *env)
{
    return registerMethods(env);
}
// ----------------------------------------------------------------------------
#if 0
/*
 * This is called by the VM when the shared library is first loaded.
 */
jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
    JNIEnv* env = NULL;
    jint result = -1;

    if (vm->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK)
    {
        LOGE("ERROR: GetEnv failed\n");
        goto bail;
    }
    assert(env != NULL);

    if (registerMethods(env) != 0)
    {
        LOGE("ERROR: PlatformLibrary native registration failed\n");
        goto bail;
    }

    /* success -- return valid version number */
    result = JNI_VERSION_1_4;

bail:
    return result;
}
#endif

