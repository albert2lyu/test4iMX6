LOCAL_PATH := $(call my-dir)

# the library
# =============================================================
include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
            $(call all-subdir-java-files)

LOCAL_MODULE_TAGS := eng
#LOCAL_DEX_PREOPT := false
LOCAL_MODULE := blus

#
#LOCAL_MODULE_CLASS := JAVA_LIBRARIES
#LOCAL_JAVA_LIBRARIES := android.policy

# AIDL
#LOCAL_SRC_FILES += \
#	core/java/blus/hardware/ISpiService.aidl

include $(BUILD_JAVA_LIBRARY)

# The JNI component
include $(CLEAR_VARS)
include $(call all-makefiles-under,$(LOCAL_PATH))
