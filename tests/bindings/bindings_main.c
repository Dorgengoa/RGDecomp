/* SPDX-License-Identifier: CC0-1.0 */
/* ctest -L bindings: libvu0 (src/sce/vu0), the CRT bindings (src/crt) and the
 * override lanes (overrides/, compiled with the game flags).  Built twice:
 * rg-bindings-tests must pass, rg-bindings-tests-wrong (-DRG_BT_WRONG, one
 * flipped expectation per suite) must fail. */
#include <stdio.h>
#include <string.h>

int bt_checks;

int bt_sce_vu0(void);
int bt_crt(void);
#define BT_LANE(name) int bt_ovr_##name(void);
#include "lanes.inc"
#undef BT_LANE

static const struct {
    const char *name;
    int (*fn)(void);
} suites[] = {
    {"sce_vu0", bt_sce_vu0},
    {"crt", bt_crt},
#define BT_LANE(name) {"ovr_" #name, bt_ovr_##name},
#include "lanes.inc"
#undef BT_LANE
};

int main(int argc, char **argv)
{
    int fails = 0, ran = 0, skipped = 0;
    for (unsigned i = 0; i < sizeof suites / sizeof suites[0]; i++) {
        int f, before = bt_checks;
        if (argc > 1 && strcmp(argv[1], suites[i].name) != 0)
            continue;
        f = suites[i].fn();
        ran++;
        if (f == -77) { /* the suite cannot run here (vcallms without the retail ELF) */
            printf("%-14s skipped\n", suites[i].name);
            skipped++;
            continue;
        }
        printf("%-14s %4d checks, %d failed\n", suites[i].name, bt_checks - before, f);
        fails += f;
    }
    if (!ran) {
        printf("no suite named %s\n", argc > 1 ? argv[1] : "?");
        return 2;
    }
    if (skipped == ran) {
        printf("SKIP\n");
        return 77;
    }
    printf("%s\n", fails ? "FAIL" : "PASS");
    return fails != 0;
}
