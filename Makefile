DAYS = day01 day02 day03 day04 day05 day06

PART ?= part_2

all:
	@echo "Use: make dayXX or make dayXX PART=part_X"

$(DAYS):
	@make -s -C ./$@ $(PART)

clean:
	@for d in $(DAYS); do \
	    $(MAKE) -s -C $$d clean; \
	done

.PHONY: all build run clean $(DAYS)