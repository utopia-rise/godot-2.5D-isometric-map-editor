# Android.mk
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := godot-prebuilt
ifeq ($(TARGET_ARCH_ABI),x86)
    LOCAL_SRC_FILES := ../godot-cpp/bin/libgodot-cpp.android.release.x86.a
endif
ifeq ($(TARGET_ARCH_ABI),armeabi-v7a)
    LOCAL_SRC_FILES := ../godot-cpp/bin/libgodot-cpp.android.release.armv7.a
endif
ifeq ($(TARGET_ARCH_ABI),arm64-v8a)
    LOCAL_SRC_FILES := ../godot-cpp/bin/libgodot-cpp.android.release.arm64v8.a
endif
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libGodotIsoMapEditor.android.release.$(TARGET_ARCH_ABI)
LOCAL_CPPFLAGS := -std=c++14
LOCAL_CPP_FEATURES := rtti exceptions
LOCAL_LDLIBS := -llog

LOCAL_SRC_FILES := \
src/gdlibrary.cpp \
src/IsometricServer.cpp \
src/_IsometricServer.cpp \
src/positionable/IsometricPositionable.cpp \
src/positionable/IsometricMap.cpp \
src/positionable/IsometricTile.cpp \
src/positionable/IsometricPlaceholder.cpp \
src/positionable/StaticIsometricElement.cpp \
src/positionable/IsometricElement.cpp \
src/positionable/PlaceholderType.cpp \
src/containers/Grid3D.cpp \
src/editor/OutlineDrawer.cpp \

LOCAL_C_INCLUDES := \
../godot-cpp/godot_headers \
../godot-cpp/include/ \
../godot-cpp/include/core \
../godot-cpp/include/gen \
src \
src/containers \
src/helpers \
src/positionable \
src/editor \

LOCAL_STATIC_LIBRARIES := godot-prebuilt

include $(BUILD_SHARED_LIBRARY)
