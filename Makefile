# This file contains a make script for the BrainBrawler application
#
# Author: Josh McIntyre
#

# This block defines makefile variables
UI_FILES=src/ui/*.cpp
CORE_FILES=src/core/*.cpp
CRYPTO_FILES=src/crypto/*.cpp
RES_FILES=res/*txt
PY_FILES=src/py/*.py
TEST_FILES=tests/*.cpp
TEST_PY_FILES=tests/*.py
INCLUDE_CORE=src/core
INCLUDE_CRYPTO=src/crypto
INCLUDE_UI=src/ui
INCLUDE_TESTS=tests/

BUILD_DIR=bin
BUILD_BIN=brainbrawler
BUILD_TEST_BIN=test_brainbrawler

CC=g++
FLAGS=-Werror -I$(INCLUDE_CORE) -I$(INCLUDE_CRYPTO) -I$(INCLUDE_UI) -I$(INCLUDE_TESTS)

# This rule builds the utility
build: $(CORE_FILES) $(CRYPTO_FILES) $(UI_FILES)
	mkdir -p $(BUILD_DIR)
	$(CC) $(FLAGS) -o $(BUILD_DIR)/$(BUILD_BIN) $(CORE_FILES) $(UI_FILES) $(CRYPTO_FILES)
	cp $(PY_FILES) $(BUILD_DIR)
	cp $(RES_FILES) $(BUILD_DIR)

# This rule builds the unit tests
tests: $(TEST_FILES) $(CORE_FILES) $(CRYPTO_FILES)
	mkdir -p $(BUILD_DIR)
	$(CC) $(FLAGS) -o $(BUILD_DIR)/$(BUILD_TEST_BIN) $(TEST_FILES) $(CORE_FILES) $(CRYPTO_FILES)
	cp $(TEST_PY_FILES) $(BUILD_DIR)

# This rule cleans the build directory
clean: $(BUILD_DIR)
	rm $(BUILD_DIR)/* 
	rmdir $(BUILD_DIR)
