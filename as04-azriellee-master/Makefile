.SILENT: test tidy memcheck
.PHONY: test tidy memcheck
SHELL := /bin/bash
FILES=selection mastermind
CC=clang
LDLIBS=-lm -lcs1010
CFLAGS=@compile_flags.txt 

all: tidy

test: $(FILES)
	for question in $(FILES); do ./test.sh $$question; done

memcheck:
	for question in $(FILES); do ./memcheck.sh $$question; done

tidy: test
	clang-tidy -quiet *.c 2> /dev/null

clean:
	rm $(FILES)
# vim:noexpandtab
