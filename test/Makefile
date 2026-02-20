# Just pass the command down to the next level
SUBDIRS := $(wildcard */.)

.PHONY: test clean $(SUBDIRS)

test clean: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)