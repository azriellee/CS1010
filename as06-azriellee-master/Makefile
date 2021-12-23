.SILENT: test tidy
.PHONY: compile test tidy
SHELL := /bin/bash
FILES=contact social
CC=clang
LDLIBS=-lm -lcs1010
CFLAGS=@compile_flags.txt

all: compile tidy

compile: $(FILES) life

test: $(FILES)
	for question in $(FILES); do ./test.sh $$question; done
	echo "life: not tested.  Read Questions.md for instructions."

tidy: test
	clang-tidy -quiet *.c 2> /dev/null
clean:
	rm $(FILES) life
# vim:noexpandtab
