#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "transpose.h"

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

    return 0;
}
