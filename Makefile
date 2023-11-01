#
#  Makefile
#  Simple GNU Makefile to build and install the project
#
#  Copyright 2023 Sage I. Hendricks
#
#  Licensed under the Apache License, Version 2.0 (the "License");
#  you may not use this file except in compliance with the License.
#  You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
#  Unless required by applicable law or agreed to in writing, software
#  distributed under the License is distributed on an "AS IS" BASIS,
#  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#  See the License for the specific language governing permissions and
#  limitations under the License.
#

PROJECT_NAME := Leaf Context Editor
PROJECT_VERSION := 0.3.1.3-dev 
# VERSION in the form MAJOR.MINOR.PATCH.BUILD-AUDIENCE
# Example for Developer Build, version 2.14 patch 3
# 2.14.3.841-dev
# Example for Stable Release, version 2.15 patch 0
# 2.15.0.857


# Important Directories
BUILD_DIR  := ./build
SOURCE_DIR := ./source
DESTDIR    := /usr/local

INCLUDE_DIR := $(SOURCE_DIR)/include
LIBRARY_DIR := $(SOURCE_DIR)/lib


# Important Files
LED_EXEC := led.exe
LED_SOURCE_FILENAMES := main.c utilities.c settings_struct.c input_output.c interpreter.c
LED_SOURCE_FILES := $(foreach filename,$(LED_SOURCE_FILENAMES),$(SOURCE_DIR)/$(filename))
LED_OBJECT_FILES := $(foreach filename,$(LED_SOURCE_FILES),$(BUILD_DIR)/$(filename).o)


# Compiler and Linker Options
CC := gcc
LD := gcc

INCLUDE_FLAGS := -I$(INCLUDE_DIR) -I$(SOURCE_DIR)
LIBRARY_FLAGS := -L$(LIBRARY_DIR)

C_FLAGS := $(INCLUDE_FLAGS) -O3 -ansi -pedantic -Wpedantic -Wall -Werror
LINKER_FLAGS := $(LIBRARY_FLAGS)


# Build
.PHONY: build
build: $(BUILD_DIR)/$(LED_EXEC)

$(BUILD_DIR)/$(LED_EXEC): $(LED_OBJECT_FILES)
	mkdir -pv $(dir $@)
	$(LD) -o $@ $(LINKER_FLAGS) $(LED_SOURCE_FILES)


$(BUILD_DIR)/$(SOURCE_DIR)/%.c.o: $(SOURCE_DIR)/%.c
	mkdir -pv $(dir $@)
	$(CC) -c -o $@ $(C_FLAGS) $<


# Clean
.PHONY: clean
clean:
	rm -rfv $(BUILD_DIR)


# Install
.PHONY: install
install: $(DESTDIR)/bin/$(LED_EXEC)


$(DESTDIR)/bin/$(LED_EXEC): $(BUILD_DIR)/$(LED_EXEC)
	mkdir -pv $(dir $@)
	cp -fv $< $@


# Uninstall
.PHONY: uninstall
uninstall:
	rm -fv $(DESTDIR)/bin/$(LED_EXEC)


