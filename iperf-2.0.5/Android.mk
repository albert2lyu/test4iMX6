LOCAL_PATH := $(call my-dir)


include $(CLEAR_VARS)


LOCAL_SRC_FILES := \
    compat/delay.cpp \
    compat/error.c \
    compat/gettimeofday.c \
    compat/inet_ntop.c \
    compat/inet_pton.c \
    compat/signal.c \
    compat/snprintf.c \
    compat/string.c \
    compat/Thread.c


LOCAL_SRC_FILES += \
    src/Client.cpp \
    src/Extractor.c \
    src/gnu_getopt.c \
    src/gnu_getopt_long.c \
    src/Launch.cpp \
    src/List.cpp \
    src/Listener.cpp \
    src/Locale.c \
    src/main.cpp \
    src/PerfSocket.cpp \
    src/ReportCSV.c \
    src/ReportDefault.c \
    src/Reporter.c \
    src/Server.cpp \
    src/service.c \
    src/Settings.cpp \
    src/SocketAddr.c \
    src/sockets.c \
    src/stdio.c \
    src/tcp_window_size.c


LOCAL_C_INCLUDES += \
    $(LOCAL_PATH) \
    $(LOCAL_PATH)/include


LOCAL_CFLAGS += -Wno-format-security


LOCAL_CFLAGS += -DHAVE_CONFIG_H
LOCAL_LDLIBS += -lpthread


LOCAL_SHARED_LIBRARIES := libc libm libcutils libnetutils


LOCAL_MODULE_TAGS := optional
LOCAL_MODULE := iperf


include $(BUILD_EXECUTABLE)

