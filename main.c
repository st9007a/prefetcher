#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <assert.h>

#define TEST_W 4096
#define TEST_H 4096

/* provide the implementations of naive_transpose,
 * sse_transpose, sse_prefetch_transpose
 */

#include "transpose.h"

static long diff_in_us(struct timespec t1, struct timespec t2)
{
    struct timespec diff;
    if (t2.tv_nsec-t1.tv_nsec < 0) {
        diff.tv_sec  = t2.tv_sec - t1.tv_sec - 1;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec + 1000000000;
    } else {
        diff.tv_sec  = t2.tv_sec - t1.tv_sec;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec;
    }
    return (diff.tv_sec * 1000000.0 + diff.tv_nsec / 1000.0);
}

int main()
{
    /* verify the result of 8x8 matrix */
    {
        int testin[64];
        int testout[64];
        int expected[64];

        for (int x = 0; x < 8; x++) {
            for (int y = 0; y < 8; y++) {
                testin[x * 8 + y] = x * 8 + y;
                expected[y * 8 + x] = x * 8 + y;
            }
        }

        for (int y = 0; y < 8; y++) {
            for (int x = 0; x < 8; x++)
                printf(" %2d", testin[y * 8 + x]);
            printf("\n");
        }
        printf("\n");
        transpose(testin, testout, 8, 8);
        for (int y = 0; y < 8; y++) {
            for (int x = 0; x < 8; x++)
                printf(" %2d", testout[y * 8 + x]);
            printf("\n");
        }
        assert(0 == memcmp(testout, expected, 64 * sizeof(int)) &&
               "Verification fails");
    }

    {
        struct timespec start, end;
        int *src  = (int *) malloc(sizeof(int) * TEST_W * TEST_H);
        int *out0 = (int *) malloc(sizeof(int) * TEST_W * TEST_H);
        int *out1 = (int *) malloc(sizeof(int) * TEST_W * TEST_H);
        int *out2 = (int *) malloc(sizeof(int) * TEST_W * TEST_H);

        srand(time(NULL));
        for (int y = 0; y < TEST_H; y++)
            for (int x = 0; x < TEST_W; x++)
                *(src + y * TEST_W + x) = rand();

        clock_gettime(CLOCK_REALTIME, &start);
        transpose(src, out0, TEST_W, TEST_H);
        clock_gettime(CLOCK_REALTIME, &end);
        printf("execution time: %ld us\n", diff_in_us(start, end));

        free(src);
        free(out0);
        free(out1);
        free(out2);
    }

    return 0;
}
