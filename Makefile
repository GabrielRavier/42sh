##
## EPITECH PROJECT, 2020
## mysh
## File description:
## Makefile for this project
##

# We use `override` to enable setting part of CFLAGS on the command line
# This makes the compiler generate dependency files, which will solve any header-related dependency problems we could have had
override CFLAGS += -MMD -MP -MF $@.d

# We need to be able to include the libmy include files
override CFLAGS += -Iinclude

# We need to be able to link to libmy, and link to it
override LDFLAGS += -Llib $(CFLAGS)

LIBMY_CONFIGURATION := USE_LIBC_FILE=0 HAS_LIBC_ALLOC=1 HAS_LIBC_READ=1 HAS_LIBC_WRITE=1 HAS_LIBC_EXECVE=1 HAS_LIBC_OPEN=1 HAS_LIBC_CLOSE=1 HAS_LIBC_ISATTY=1 HAS_LIBC_LSEEK=0 HAS_LIBC_FSTAT=1 HAS_LIBC__EXIT=0 HAS_LIBC_REALLOC=0
override CFLAGS += -DLIBMY_USE_LIBC_FILE=0

.PHONY: all clean fclean re libmy

.PREVIOUS: obj/%.o

BINARY_NAME := mysh

all: $(BINARY_NAME)

# Sources for this project
SOURCE_FILES := main error shell/read_character shell/init shell/do_line/do_line shell/process shell/lex/lex shell/lex/get_word lexical_word_list/free lexical_word_list/init
# shell/execute shell/builtins shell/builtins/env shell/builtins/setenv shell/builtins/unsetenv shell/builtins/cd shell/builtins/exit

OBJECT_FILES := $(addprefix obj/, $(addsuffix .o, $(SOURCE_FILES)))

$(BINARY_NAME): libmy $(OBJECT_FILES)
	$(CC) $(LDFLAGS) -o $@ $(OBJECT_FILES) -lmy

obj/%.o: src/%.c libmy
	mkdir --parents obj/shell/do_line
	mkdir --parents obj/shell/builtins
	mkdir --parents obj/shell/lex
	mkdir --parents obj/lexical_word_list
	$(CC) -c $< -o $@ $(CFLAGS)

# Just build the entire libmy when we need these headers
libmy:
	$(MAKE) --directory=lib/my $(LIBMY_CONFIGURATION)

# Include dependencies for the object files
include $(wildcard obj/*.d)

# Remove all object files
clean:
	rm --recursive --force obj
	$(MAKE) --directory=lib/my clean $(LIBMY_CONFIGURATION)

# Remove all object, binary and other produced files
fclean: clean
	rm --force $(BINARY_NAME)
	$(MAKE) --directory=lib/my fclean $(LIBMY_CONFIGURATION)

# "Remakes" the project. This rule is shit and won't work properly with parallel make, but it's not like I'm using this target, and neither is Marvin using parallel Make (afaik)
re: clean all
	$(MAKE) --directory=lib/my re $(LIBMY_CONFIGURATION)

# Runs tests
tests_run:
	$(MAKE) fclean
	$(MAKE) CFLAGS="$(CFLAGS) --coverage"
	$(MAKE) --directory=lib/my tests_binary USE_LIBC_FILE=0 HAS_LIBC_ALLOC=1 HAS_LIBC_READ=1 HAS_LIBC_WRITE=1 HAS_LIBC_EXECVE=1 HAS_LIBC_OPEN=1 HAS_LIBC_CLOSE=1 HAS_LIBC_ISATTY=1 HAS_LIBC_LSEEK=1 HAS_LIBC_FSTAT=1 HAS_LIBC__EXIT=1 HAS_LIBC_REALLOC=1
	./tests/libmy/test.sh & wait