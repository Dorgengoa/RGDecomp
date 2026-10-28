/* SPDX-License-Identifier: CC0-1.0 */
/* GS model test driver: rg-gs-tests <name>; exit 0 = pass. */
#include "gs_test_util.h"

int g_fail;

int main(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "usage: rg-gs-tests <test>\n");
        return 2;
    }
    const char *n = argv[1];
    int found = test_swizzle(n) || test_xfer(n) || test_clut(n) || test_pixel(n) ||
                test_prim(n) || test_gif(n) || test_display(n) || test_sinks(n);
    if (!found) {
        fprintf(stderr, "unknown test %s\n", n);
        return 2;
    }
    if (g_fail) {
        fprintf(stderr, "%s: FAIL (%d checks)\n", n, g_fail);
        return 1;
    }
    printf("%s: PASS\n", n);
    return 0;
}
