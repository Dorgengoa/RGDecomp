/* Toolchain smoke test: the build must produce a 32-bit (i686) executable
 * that runs, with SSE math.  Exit status 0 = pass. */
#include <stdio.h>
#include <stdint.h>

int main(void)
{
    volatile float a = 16777216.0f, b = 1.0f;
    float sum = a + b; /* SSE single precision: rounds back to 2^24 */
#if defined(_WIN64)
    /* x64 (strategy A, docs/X64-PLAN.md): 64-bit pointers, but the whole image below 2 GB */
    int ok = sizeof(void *) == 8 && sizeof(long) == 4 && sum == 16777216.0f &&
             (uintptr_t)&main < 0x80000000u;
#else
    int ok = sizeof(void *) == 4 && sizeof(long) == 4 && sum == 16777216.0f;
#endif
    printf("rg-smoke: sizeof(void*)=%u sizeof(long)=%u sse_float_ok=%d -> %s\n",
           (unsigned)sizeof(void *), (unsigned)sizeof(long),
           sum == 16777216.0f, ok ? "PASS" : "FAIL");
    return ok ? 0 : 1;
}
