.SILENT: test tidy
.PHONY: test tidy
SHELL := /bin/bash
FILES=pyramid digits suffix taxi
CC=clang
LDLIBS=-lm -lcs1010
#LIB_HOME=~cs1010/lib
CFLAGS=@compile_flags.txt 

all: tidy
test: $(FILES)
	for question in $(FILES); do ./test.sh $$question; done

tidy: test
	clang-tidy -quiet *.c 2> /dev/null
clean:
	rm $(FILES)
# vim:noexpandtab
