CFLAGS = --std gnu99 -O0 -Wall -Wextra

GIT_HOOKS := .git/hooks/applied

SRC = main.c

EXEC = navie_transpose \
	  sse_transpose \
	  sse_prefetch_transpose \
	  avx_transpose \
	  avx_prefetch_transpose

all: $(GIT_HOOKS) $(EXEC)

run: $(EXEC)
	@for method in $(EXEC); do \
		echo exec $$method; \
		./$$method; \
	done

naive_transpose: $(SRC) naive_transpose.c
	$(CC) $(CFLAGS) -o $@ $< $@.c

sse_%: $(SRC) sse_%.c
	$(CC) $(CFLAGS) -msse2 -o $@ $< $@.c

avx_%: $(SRC) avx_%.c
	$(CC) $(CFLAGS) -mavx2 -o $@ $< $@.c

$(GIT_HOOKS):
	@scripts/install-git-hooks
	@echo

clean:
	$(RM) main
