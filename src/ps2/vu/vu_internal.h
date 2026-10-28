/* SPDX-License-Identifier: CC0-1.0 */
/* Private interface between the VU interpreter (vu.c) and the block
 * translator (vu_block.c).  docs/VU.md "Block translator". */
#ifndef RG_PS2_VU_INTERNAL_H
#define RG_PS2_VU_INTERNAL_H

#include "vu.h"
#include "vu_decode.h"

/* one decoded pair, as the interpreter's decode cache holds it */
typedef struct dc_entry {
    vu_pair p;
    /* from the lower's vu_use: what the step needs */
    uint8_t writes_q, writes_p, is_branch;
    int8_t vi_w;
    /* the VF components the pair reads, as indexes into vf_ready[0][0..127]
     * (upper and lower merged, VF0 left out: it is never marked busy) */
    uint8_t n_rd, rd[32];
    /* the VF components it writes (upper then lower), same indexing */
    uint8_t n_wr, wr[8];
} dc_entry;

/* vu.c */
dc_entry *vu__dc_get(vu_state *vu, uint32_t pc);
void vu__commit_events(vu_state *vu, uint64_t now);
void vu__xgkick(vu_state *vu, uint32_t vi);
vu_stop vu__step(vu_state *vu);     /* the interpreter's pair step */
uint32_t vu__efu_latency(int op);

/* vu_block.c */
vu_stop vu__block_run(vu_state *vu, uint64_t max_cycles);
/* code pairs [first, first + n) (pair indexes, may wrap) changed */
void vu__block_invalidate(vu_state *vu, uint32_t first, uint32_t n);
int vu__blocks_default(void);
int vu__blocks_check_default(void);
int vu__stats_default(void);
void vu__stats_tick(vu_state *vu);

#endif
