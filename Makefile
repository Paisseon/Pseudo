SYSROOT = $(THEOS)/sdks/iPhoneOS14.4.sdk/
ARCHS = arm64
TARGET = iphone:clang:latest:11.0

FINALPACKAGE = 1
DEBUG = 0
THEOS_LEAN_AND_MEAN = 1

TOOL_NAME = pseudo
$(TOOL_NAME)_FILES = main.c
$(TOOL_NAME)_CFLAGS = -fobjc-arc
$(TOOL_NAME)_CODESIGN_FLAGS = -Sentitlements.plist
$(TOOL_NAME)_INSTALL_PATH = /usr/bin

include $(THEOS)/makefiles/common.mk
include $(THEOS_MAKE_PATH)/tool.mk
