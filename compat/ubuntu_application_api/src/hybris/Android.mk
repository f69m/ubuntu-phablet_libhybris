LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_CFLAGS += -std=gnu++0x

LOCAL_C_INCLUDES := \
	canonical/hybris/compat/ubuntu_application_api/include

LOCAL_SRC_FILES := \
	ubuntu_application_api_for_hybris.cpp \
	../default/default_ubuntu_application_ui.cpp \
	application_manager.cpp

LOCAL_MODULE := libubuntu_application_api
LOCAL_MODULE_TAGS := optional

LOCAL_SHARED_LIBRARIES := \
	libui \
	libbinder \
	libutils \
	libgui \
	libEGL \
	libGLESv2

include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)

LOCAL_CFLAGS += -std=gnu++0x

LOCAL_C_INCLUDES := \
	canonical/hybris/compat/ubuntu_application_api/include

LOCAL_SRC_FILES:= \
	test.cpp \

LOCAL_MODULE:= direct_ubuntu_application_api_for_hybris_test
LOCAL_MODULE_TAGS := optional

LOCAL_SHARED_LIBRARIES := \
	libui \
	libutils \
	libEGL \
	libGLESv2 \
	libubuntu_application_api

include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)

LOCAL_CFLAGS += -std=gnu++0x

LOCAL_C_INCLUDES := \
	canonical/hybris/compat/ubuntu_application_api/include

LOCAL_SRC_FILES:= \
	test_c_api.cpp \

LOCAL_MODULE:= direct_ubuntu_application_c_api_for_hybris_test
LOCAL_MODULE_TAGS := optional

LOCAL_SHARED_LIBRARIES := \
	libui \
	libutils \
	libEGL \
	libGLESv2 \
	libubuntu_application_api

include $(BUILD_EXECUTABLE)


include $(CLEAR_VARS)

LOCAL_CFLAGS += -std=gnu++0x

LOCAL_C_INCLUDES := \
	external/skia/include/core \
	frameworks/base/services \
	canonical/hybris/compat/ubuntu_application_api/include

LOCAL_SRC_FILES:= \
	application_manager.cpp \
	default_application_manager.cpp \

LOCAL_MODULE:= default_ubuntu_application_manager
LOCAL_MODULE_TAGS := optional

LOCAL_SHARED_LIBRARIES := \
	libbinder \
	libinput \
	libgui \
	libskia \
	libui \
	libutils \
	libEGL \
	libGLESv2 \
	libubuntu_application_api

include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)

LOCAL_CFLAGS += -std=gnu++0x

LOCAL_C_INCLUDES := \
	canonical/hybris/compat/ubuntu_application_api/include

LOCAL_SRC_FILES:= \
	application_manager.cpp \
	default_application_manager_test.cpp \

LOCAL_MODULE:= default_ubuntu_application_manager_test
LOCAL_MODULE_TAGS := optional

LOCAL_SHARED_LIBRARIES := \
	libbinder \
	libui \
	libutils \
	libEGL \
	libGLESv2 \
	libubuntu_application_api

include $(BUILD_EXECUTABLE)