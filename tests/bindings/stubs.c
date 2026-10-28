/* SPDX-License-Identifier: CC0-1.0 */
/* Link stubs for the bindings tests: what src/runtime provides in the game
 * link (sbrk over game RAM, guest exit) and MSL .bss the crt reads. */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define ARENA (8u << 20)
static unsigned char arena[ARENA] __attribute__((aligned(16)));
static size_t brk_off = 4; /* deliberately misaligned start */
size_t bt_sbrk_limit = ARENA;

void *sbrk(intptr_t incr)
{
    if ((incr > 0 && brk_off + (size_t)incr > bt_sbrk_limit) || (incr < 0 && (size_t)-incr > brk_off))
        return (void *)-1;
    void *old = arena + brk_off;
    brk_off += incr;
    return old;
}

int bt_exit_code = -1;
void rg_ps2_exit(int code)
{
    bt_exit_code = code;
}

struct { void *head; int32_t pad[3]; } D_004853D0;
