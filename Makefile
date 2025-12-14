DAYS = day01 day02 day03 day04 day05 day06 day07 day08 day09 day10 day11 day12

PART ?= part_1

CFLAGS =

all:
	@echo "Use: make dayXX or make dayXX PART=part_X"

$(DAYS):
	@make -s -C ./$@ $(PART)

clean:
	@for d in $(DAYS); do \
	    $(MAKE)  -C $$d clean; \
	done
	$(MAKE) -s -C libft fclean
	$(MAKE) -s -C dynamic_arrays fclean

.PHONY: all build run clean $(DAYS)