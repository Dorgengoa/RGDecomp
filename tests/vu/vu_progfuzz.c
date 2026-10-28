/* SPDX-License-Identifier: CC0-1.0 */
/* rg-vu-progfuzz / rg-vu-progfuzz-ref: random VU1 programs (vu_fuzzgen.h)
 * run through vu_run with random budgets, restarts and code re-uploads,
 * folding everything a program can observe after every call (stop reason,
 * data memory, VF/VI/ACC/Q/P/I/R, MAC/status/clip, pc/TPC, cycle count,
 * pair/stall/quirk counts, PATH1 packets) into one hash.  Built once on the
 * live src/ps2/vu (blocks on, or off with RG_VU_BLOCKS=0) and once on the
 * pre-optimisation copy in tests/vu/ref; ctest vu.progfuzz_same.* requires
 * the same FUZZHASH line (docs/VU.md "Block translator").
 *
 *   rg-vu-progfuzz [ITERATIONS] [SEED] */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vu.h"
#include "vu_fuzzgen.h"

static uint64_t fnv(uint64_t h, const void *p, size_t n)
{
    const uint8_t *b = (const uint8_t *)p;
    while (n--) h = (h ^ *b++) * 0x100000001B3ull;
    return h;
}

static uint64_t fold(uint64_t h, const vu_state *v, int stop, const sinkh *sk)
{
    h = fnv(h, &stop, sizeof stop);
    h = fnv(h, v->mem, sizeof v->mem);
    h = fnv(h, v->vf, sizeof v->vf);
    h = fnv(h, &v->acc, sizeof v->acc);
    h = fnv(h, v->vi, sizeof v->vi);
    h = fnv(h, &v->q, 4); h = fnv(h, &v->p, 4); h = fnv(h, &v->i, 4); h = fnv(h, &v->r, 4);
    h = fnv(h, &v->mac, 4); h = fnv(h, &v->status, 4); h = fnv(h, &v->clip, 4);
    h = fnv(h, &v->pc, 4); h = fnv(h, &v->tpc, 4); h = fnv(h, &v->running, sizeof v->running);
    h = fnv(h, &v->cycle, 8);
    h = fnv(h, &v->stats.pairs, 8); h = fnv(h, &v->stats.stall_cycles, 8);
    h = fnv(h, &v->stats.int_branch_quirks, 8); h = fnv(h, &v->stats.q_early_reads, 8);
    h = fnv(h, &v->stats.xgkicks, 8);
    h = fnv(h, &sk->h, 8);
    return h;
}

int main(int argc, char **argv)
{
    static vu_state A;
    static uint32_t code[2 * 2048];
    int iters = argc > 1 ? atoi(argv[1]) : 2000, it;
    uint64_t h = 0xCBF29CE484222325ull, pairs = 0, quirks = 0, blk = 0;
    g_rng = argc > 2 ? (uint32_t)strtoul(argv[2], NULL, 0) : 0x2468ACEu;
    if (!g_rng) g_rng = 1;

    for (it = 0; it < iters; it++) {
        sinkh sk = {0xCBF29CE484222325ull, 0};
        uint32_t n, call;
#ifdef RG_VU_HAS_BLOCKS
        vu_release(&A);
#endif
        fuzz_setup(&A, code, &n);
        A.gif_sink = sink;
        A.gif_user = &sk;
        vu_start(&A, 0);
        for (call = 0; call < 40; call++) {
            vu_stop s = vu_run(&A, fuzz_budget());
            uint32_t rat = 0, rnn = 0, spc = 0;
            int rs = 0;
            h = fold(h, &A, (int)s, &sk);
            if (!fuzz_next(s, n, code, &rat, &rnn, &rs, &spc)) break;
            if (rnn) vu_load_code(&A, rat * 8, code + 2 * rat, rnn * 8);
            if (rs == 1) vu_continue(&A);
            else if (rs == 2) vu_start(&A, spc);
        }
        pairs += A.stats.pairs;
        quirks += A.stats.int_branch_quirks;
#ifdef RG_VU_HAS_BLOCKS
        blk += A.stats.blk_pairs;
#endif
    }
    printf("FUZZHASH %016llX iterations %d pairs %llu quirks %llu\n", (unsigned long long)h, iters,
           (unsigned long long)pairs, (unsigned long long)quirks);
#ifdef RG_VU_HAS_BLOCKS
    printf("BLK blocks %d: pairs translated %llu\n", A.blocks, (unsigned long long)blk);
#endif
    (void)blk;
    return 0;
}
