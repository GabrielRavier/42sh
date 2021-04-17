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

LIBMY_CONFIGURATION := USE_LIBC_FILE=0 HAS_LIBC_ALLOC=1 HAS_LIBC_READ=1 HAS_LIBC_WRITE=1 HAS_LIBC_EXECVE=1 HAS_LIBC_OPEN=1 HAS_LIBC_CLOSE=1 HAS_LIBC_ISATTY=1 HAS_LIBC_LSEEK=0 HAS_LIBC_FSTAT=1 HAS_LIBC__EXIT=0 HAS_LIBC_REALLOC=0 HAS_LIBC_GETPID=1
override CFLAGS += -DLIBMY_USE_LIBC_FILE=0

.PHONY: all clean fclean re libmy

.PREVIOUS: obj/%.o

BINARY_NAME := mysh

all: $(BINARY_NAME)

# Sources for this project
SOURCE_FILES := main
SOURCE_FILES += shell/read_character shell/process shell/fork shell/pipe shell/heredoc shell/flush_child_fds
SOURCE_FILES += shell/init/init shell/init/fds
SOURCE_FILES += shell/builtin/find shell/builtin/run
SOURCE_FILES += shell/builtin/commands/cd shell/builtin/commands/env shell/builtin/commands/exit shell/builtin/commands/printenv shell/builtin/commands/setenv shell/builtin/commands/unsetenv
SOURCE_FILES += shell/do_line/do_line
SOURCE_FILES += shell/execute/execute
SOURCE_FILES += shell/lex/lex shell/lex/get_word
SOURCE_FILES += shell/parse_tree/from_lex_tree shell/parse_tree/free
SOURCE_FILES += shell/proc/add shell/proc/wait_current shell/proc/print
SOURCE_FILES += fd/move fd/copy
SOURCE_FILES += shell_char/xstrdup shell_char/strlen shell_char/cstrchr shell_char/cstrcmp_ignore_quote shell_char/xstrdup_to_c shell_char/xdup_strv_to_c shell_char/strcmp
SOURCE_FILES += lexical_word_list/init lexical_word_list/free
# shell/builtins shell/builtins/env shell/builtins/setenv shell/builtins/unsetenv shell/builtins/cd shell/builtins/exit

OBJECT_FILES := $(addprefix obj/, $(addsuffix .o, $(SOURCE_FILES)))

$(BINARY_NAME): libmy $(OBJECT_FILES)
	$(CC) $(LDFLAGS) -o $@ $(OBJECT_FILES) -lmy

obj/%.o: src/%.c libmy
	@mkdir --parents obj/shell/init
	@mkdir --parents obj/shell/do_line
	@mkdir --parents obj/shell/execute
	@mkdir --parents obj/shell/lex
	@mkdir --parents obj/shell/parse_tree
	@mkdir --parents obj/shell/proc
	@mkdir --parents obj/shell/builtin/commands
	@mkdir --parents obj/fd
	@mkdir --parents obj/lexical_word_list
	@mkdir --parents obj/shell_char
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
	$(MAKE) --directory=lib/my tests_binary USE_LIBC_FILE=0 HAS_LIBC_ALLOC=1 HAS_LIBC_READ=1 HAS_LIBC_WRITE=1 HAS_LIBC_EXECVE=1 HAS_LIBC_OPEN=1 HAS_LIBC_CLOSE=1 HAS_LIBC_ISATTY=1 HAS_LIBC_LSEEK=1 HAS_LIBC_FSTAT=1 HAS_LIBC__EXIT=1 HAS_LIBC_REALLOC=1 HAS_LIBC_GETPID=1
	$(MAKE) CFLAGS="$(CFLAGS) --coverage"
	./tests/libmy/test.sh & ./tests/mysh/test.sh & wait
