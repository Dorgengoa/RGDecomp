/* SPDX-License-Identifier: CC0-1.0 */
/* Game memory the native renderer's walkers read in place (docs/NATIVE-RENDER.md
 * "Remembered packets").
 *
 * The DMA walkers (nr_const.c, nr_fx.c, nr_mesh.c, nr_im.c) follow tag addresses the game
 * wrote.  A packet pointer that outlived its memory (the 1025b shop-close crash: a light
 * packet named after the frame's packet stack was reused) holds garbage tags, and a REF to
 * 0x3F800000 faulted.  nr_game_ptr is the walkers' host(): NULL for null / scratchpad
 * addresses (as before) and, on Windows, for addresses that are not committed readable memory
 * (one VirtualQuery per region, cached until the next frame): the walk then fails like any
 * other unknown layout instead of faulting.  In normal play every address passes, so output
 * and run hashes are unchanged.
 *
 * Poison mode (RG_NR_POISON=1 report, =2 abort at the first hit): DrawListFrameBegin_1425d0
 * (override) fills a frame packet stack's dead contents with a poison pattern before the game
 * resets it (nr_poison_stack); every walker checks the qwords it reads as tags against the
 * pattern (nr_poisoned), so a read of a packet that was not live (a stale pointer the copy
 * fixes missed) is reported loudly ("nr: POISON ...", counted in the stats line).  Memory the
 * game has already rewritten reads as live data (the 1025b case itself); a walk through such data
 * shows up as a refused read instead (both count in poisoncheck.py).  The game's
 * own reads of dead memory see the pattern too, so poison runs are diagnostic only (their run
 * hash may differ).  Regression: tools/fixtures/poisoncheck.py (ctest fixtures.poison). */
#ifndef RG_NR_MEM_H
#define RG_NR_MEM_H

#include <stdint.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

/* host pointer for [a, a + bytes) when it is game memory a walker may read, else NULL */
const uint8_t *nr_game_ptr(uint32_t a, uint32_t bytes);
/* forget the cached readable regions (nr_frame_begin: memory may have been freed) */
void nr_game_mem_frame(void);

/* poison mode: 0 off, 1 report, 2 abort on the first poisoned read */
int nr_poison_mode(void);
/* the 16-byte poison qword (a DMA END tag the builders never write + a marker) */
enum { NR_POISON_W0 = 0x7EADDEADu, NR_POISON_W1 = 0xDEAD7EADu, NR_POISON_W2 = 0x5EEDDEADu, NR_POISON_W3 = 0xDEAD5EEDu };
/* fill [base, base + qwords * 16) with the poison qword (no-op when poison mode is off) */
void nr_poison_stack(uint32_t base, uint32_t qwords);
/* 1 (and reported as a hit by `who` at a) when the qword at p is the poison qword */
int nr_poisoned(const uint8_t *p, const char *who, uint32_t a);
static inline int nr_poison_check(const uint8_t *p, const char *who, uint32_t a)
{
    extern int g_nr_poison_mode;
    return g_nr_poison_mode > 0 && nr_poisoned(p, who, a);
}
void nr_mem_stats(FILE *f);

#ifdef __cplusplus
}
#endif
#endif
