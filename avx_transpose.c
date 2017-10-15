#include <immintrin.h>
#include "transpose.h"

void transpose(int *src, int *dst, int w, int h)
{
    for (int x = 0; x < w; x += 8) {
        for (int y = 0; y < h; y += 8) {
            __m256i I0 = _mm256_loadu_si256((__m256i *)(src + (y + 0) * w + x));
            __m256i I1 = _mm256_loadu_si256((__m256i *)(src + (y + 1) * w + x));
            __m256i I2 = _mm256_loadu_si256((__m256i *)(src + (y + 2) * w + x));
            __m256i I3 = _mm256_loadu_si256((__m256i *)(src + (y + 3) * w + x));
            __m256i I4 = _mm256_loadu_si256((__m256i *)(src + (y + 4) * w + x));
            __m256i I5 = _mm256_loadu_si256((__m256i *)(src + (y + 5) * w + x));
            __m256i I6 = _mm256_loadu_si256((__m256i *)(src + (y + 6) * w + x));
            __m256i I7 = _mm256_loadu_si256((__m256i *)(src + (y + 7) * w + x));
            __m256i T0 = _mm256_unpacklo_epi32(I0, I1);
            __m256i T1 = _mm256_unpackhi_epi32(I0, I1);
            __m256i T2 = _mm256_unpacklo_epi32(I2, I3);
            __m256i T3 = _mm256_unpackhi_epi32(I2, I3);
            __m256i T4 = _mm256_unpacklo_epi32(I4, I5);
            __m256i T5 = _mm256_unpackhi_epi32(I4, I5);
            __m256i T6 = _mm256_unpacklo_epi32(I6, I7);
            __m256i T7 = _mm256_unpackhi_epi32(I6, I7);
            I0 = (__m256i)_mm256_shuffle_ps(T0, T2, _MM_SHUFFLE(1, 0, 1, 0));
            I1 = (__m256i)_mm256_shuffle_ps(T0, T2, _MM_SHUFFLE(3, 2, 3, 2));
            I2 = (__m256i)_mm256_shuffle_ps(T1, T3, _MM_SHUFFLE(1, 0, 1, 0));
            I3 = (__m256i)_mm256_shuffle_ps(T1, T3, _MM_SHUFFLE(3, 2, 3, 2));
            I4 = (__m256i)_mm256_shuffle_ps(T4, T6, _MM_SHUFFLE(1, 0, 1, 0));
            I5 = (__m256i)_mm256_shuffle_ps(T4, T6, _MM_SHUFFLE(3, 2, 3, 2));
            I6 = (__m256i)_mm256_shuffle_ps(T5, T7, _MM_SHUFFLE(1, 0, 1, 0));
            I7 = (__m256i)_mm256_shuffle_ps(T5, T7, _MM_SHUFFLE(3, 2, 3, 2));
            T0 = _mm256_permute2f128_si256(I0, I4, 0x20);
            T1 = _mm256_permute2f128_si256(I1, I5, 0x20);
            T2 = _mm256_permute2f128_si256(I2, I6, 0x20);
            T3 = _mm256_permute2f128_si256(I3, I7, 0x20);
            T4 = _mm256_permute2f128_si256(I0, I4, 0x31);
            T5 = _mm256_permute2f128_si256(I1, I5, 0x31);
            T6 = _mm256_permute2f128_si256(I2, I6, 0x31);
            T7 = _mm256_permute2f128_si256(I3, I7, 0x31);
            _mm256_storeu_si256((__m256i *)(dst + ((x + 0) * h) + y), T0);
            _mm256_storeu_si256((__m256i *)(dst + ((x + 1) * h) + y), T1);
            _mm256_storeu_si256((__m256i *)(dst + ((x + 2) * h) + y), T2);
            _mm256_storeu_si256((__m256i *)(dst + ((x + 3) * h) + y), T3);
            _mm256_storeu_si256((__m256i *)(dst + ((x + 4) * h) + y), T4);
            _mm256_storeu_si256((__m256i *)(dst + ((x + 5) * h) + y), T5);
            _mm256_storeu_si256((__m256i *)(dst + ((x + 6) * h) + y), T6);
            _mm256_storeu_si256((__m256i *)(dst + ((x + 7) * h) + y), T7);
        }
    }
}
