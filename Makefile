# Get a list of all subdirectories that contain a Makefile
SOURCE_DIR := source
TEST_DIR := test

SUBDIRS := $(wildcard $(SOURCE_DIR)/Makefile)
SUBDIRS := $(patsubst %/Makefile,%,$(SUBDIRS))

SUBDIRS := $(wildcard $(TEST_DIR)/Makefile)
SUBDIRS := $(patsubst %/Makefile,%,$(SUBDIRS))


.PHONY: all clean test clean_test

all:
	@echo "------------------------------------------"
	@echo "Building VxWorks module: $@"
	@echo "------------------------------------------"
	$(MAKE) -C $(SOURCE_DIR) all
	@echo "Building of source artifacts done"

clean:
	@echo "------------------------------------------"
	@echo "Cleaning VxWorks module: $@"
	@echo "------------------------------------------"
	$(MAKE) -C $(SOURCE_DIR) clean
	@echo "Cleaning of source artifacts done"

test:
	@echo "------------------------------------------"
	@echo "Running unit tests for: $@"
	@echo "------------------------------------------"
	$(MAKE) -C $(TEST_DIR) test
	@echo "All tests completed"

clean_test:
	@echo "------------------------------------------"
	@echo "Cleaning test artifacts for: $@"
	@echo "------------------------------------------"
	$(MAKE) -C $(TEST_DIR) clean
	@echo "Cleaning of test artifacts done"