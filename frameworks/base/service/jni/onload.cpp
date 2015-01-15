/*
 * Copyright (C) 2009 The Android Open Source Project
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

#include "JNIHelp.h"
#include "utils/Log.h"
#include "utils/misc.h"

#include "utils/Log.h"

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <android/log.h>
#include <jni.h>


#define LOG__TAG "BlusPlatform"
#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, LOG__TAG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG , LOG__TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO  , LOG__TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN  , LOG__TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR  , LOG__TAG, __VA_ARGS__)

int register_android_server_SPIService(JNIEnv *env);
int register_android_server_CtrlSysService(JNIEnv *env);

using namespace android;

extern "C" jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
    JNIEnv* env = NULL;
    jint result = -1;

    if (vm->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK)
    {
        LOGE("ERROR: GetEnv failed!");
        return result;
    }
    assert(env != NULL);

    if(register_android_server_SPIService(env) !=0)
    {
        LOGE("ERROR: PlatformLibrary native registration failed\n");
        return result;
    }
    if(register_android_server_CtrlSysService(env) !=0)
    {
        LOGE("ERROR: PlatformLibrary native registration failed\n");
        return result;
    }

    return JNI_VERSION_1_4;
}
