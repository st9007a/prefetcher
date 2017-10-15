CFLAGS = -msse2 --std gnu99 -O0 -Wall -Wextra

GIT_HOOKS := .git/hooks/applied

SRC = main.c

EXEC = navie_transpose \
	  sse_transpose \
	  sse_prefetch_transpose

all: $(GIT_HOOKS) $(EXEC)

%_transpose: $(SRC) %_transpose.c
	$(CC) $(CFLAGS) -o $@ $< $@.c

$(GIT_HOOKS):
	@scripts/install-git-hooks
	@echo

clean:
	$(RM) main
