LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

HYBRIS_PATH := $(LOCAL_PATH)/../../

LOCAL_SRC_FILES:= \
	camera_compatibility_layer.cpp

LOCAL_MODULE:= libcamera_compat_layer
LOCAL_MODULE_TAGS := optional

LOCAL_C_INCLUDES := \
	$(HYBRIS_PATH)/compat/surface_flinger \
	$(HYBRIS_PATH)/compat/input

LOCAL_SHARED_LIBRARIES := \
	libcutils \
	libcamera_client \
	libutils \
	libbinder \
	libhardware \
	libui \
	libgui

include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)

LOCAL_SRC_FILES:=		\
	test.cpp \

LOCAL_MODULE:= direct_camera_test
LOCAL_MODULE_TAGS := optional

LOCAL_C_INCLUDES := \
	bionic \
	bionic/libstdc++/include \
	external/gtest/include \
	external/stlport/stlport \
	external/skia/include/core \
	$(HYBRIS_PATH)/compat/surface_flinger \
	$(HYBRIS_PATH)/compat/input

LOCAL_SHARED_LIBRARIES := \
	libis_compat_layer \
	libsf_compat_layer \
	libcamera_compat_layer \
	libcutils \
	libcamera_client \
	libutils \
	libbinder \
	libhardware \
	libui \
	libgui \
	libEGL \
	libGLESv2



include $(BUILD_EXECUTABLE)
