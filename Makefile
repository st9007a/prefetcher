CFLAGS = --std gnu99 -O0 -Wall -Wextra

GIT_HOOKS := .git/hooks/applied

SRC = main.c
SRC_verify = verify.c

EXEC = naive_transpose \
	  sse_transpose \
	  sse_prefetch_transpose \
	  avx_transpose \
	  avx_prefetch_transpose

VERIFY = naive_transpose_verify \
	  sse_transpose_verify \
	  sse_prefetch_transpose_verify \
	  avx_transpose_verify \
	  avx_prefetch_transpose_verify

all: $(GIT_HOOKS) $(EXEC)

run: $(EXEC)
	@for method in $(EXEC); do \
		echo exec $$method; \
		./$$method; \
	done

verify: $(VERIFY)
	@for method in $(VERIFY); do \
		echo exec $$method; \
		./$$method; \
	done


naive_transpose: $(SRC) naive_transpose.c
	$(CC) $(CFLAGS) -o $@ $^

sse_%: $(SRC) sse_%.c
	$(CC) $(CFLAGS) -msse2 -o $@ $^

avx_%: $(SRC) avx_%.c
	$(CC) $(CFLAGS) -mavx2 -o $@ $^

naive_transpose_verify: $(SRC_verify) naive_transpose.c
	$(CC) $(CFLAGS) -o $@ $^

sse_%_verify: $(SRC_verify) sse_%.c
	$(CC) $(CFLAGS) -msse2 -o $@ $^

avx_%_verify: $(SRC_verify) avx_%.c
	$(CC) $(CFLAGS) -mavx2 -o $@ $^

$(GIT_HOOKS):
	@scripts/install-git-hooks
	@echo

clean:
	$(RM) $(EXEC) $(VERIFY)
