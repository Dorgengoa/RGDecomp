/* SPDX-License-Identifier: CC0-1.0 */
/* rg-vu-blkfuzz: differential fuzzer of the VU1 block translator against the
 * interpreter (docs/VU.md "Block translator").
 *
 *   rg-vu-blkfuzz [ITERATIONS] [SEED] [--check]
 *
 * Every iteration builds a random program (every upper and lower opcode
 * class, random dest masks, register numbers drawn from a small set so that
 * results feed each other and stall, I/E/D/T bits, short branches, JR/JALR
 * through VI), random registers, flags and data memory, then drives two VU1
 * states through the same sequence: vu_run with random cycle budgets (so
 * runs stop inside blocks and resume with a branch pending), MSCNT
 * continuations after an E bit, and partial code re-uploads between runs.
 * State A runs the interpreter (blocks = 0), state B the translator
 * (blocks = 1; with --check also the per-block lockstep check).  After every
 * call the two must agree on everything the interpreter keeps: stop reason,
 * data memory, VF/VI/ACC/Q/P/I/R, MAC/status/clip, pc/TPC, the cycle count
 * and statistics, and the pipeline state (VF ready times as max(ready,
 * cycle), the flag queue, Q/P in flight, the branch-quirk VI log), and the
 * PATH1 packets.  Exit 0 = no difference and the translator ran (its pair
 * count is printed); 1 = a difference (the first is printed). */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vu.h"

#include "vu_fuzzgen.h"

static int differs(const vu_state *a, const vu_state *b, const sinkh *sa, const sinkh *sb, const char **why)
{
    unsigned k, c;
#define D(cond, name) do { if (cond) { *why = name; return 1; } } while (0)
    D(memcmp(a->mem, b->mem, sizeof a->mem), "data memory");
    D(memcmp(a->vf, b->vf, sizeof a->vf), "VF");
    D(memcmp(&a->acc, &b->acc, sizeof a->acc), "ACC");
    D(memcmp(a->vi, b->vi, sizeof a->vi), "VI");
    D(a->q != b->q || a->p != b->p || a->i != b->i || a->r != b->r, "Q/P/I/R");
    D(a->mac != b->mac, "MAC");
    D(a->status != b->status, "status");
    D(a->clip != b->clip, "clip");
    D(a->pc != b->pc || a->tpc != b->tpc || a->running != b->running, "pc/tpc/running");
    D(a->cycle != b->cycle, "cycle");
    for (k = 0; k < 32; k++)
        for (c = 0; c < 4; c++) {
            uint64_t x = a->vf_ready[k][c] > a->cycle ? a->vf_ready[k][c] : a->cycle;
            uint64_t y = b->vf_ready[k][c] > b->cycle ? b->vf_ready[k][c] : b->cycle;
            D(x != y, "vf_ready");
        }
    D(a->fq_n != b->fq_n, "flag queue length");
    for (k = 0; k < a->fq_n; k++) {
        const vu_flag_event *x = &a->fq[(a->fq_head + k) & 15], *y = &b->fq[(b->fq_head + k) & 15];
        D(x->t != y->t || x->kind != y->kind || x->value != y->value, "flag queue entry");
    }
    D(a->q_busy != b->q_busy || a->q_next != b->q_next || a->q_next_flags != b->q_next_flags ||
      (a->q_busy && a->q_done != b->q_done), "Q pipeline");
    D(a->p_busy != b->p_busy || a->p_next != b->p_next || (a->p_busy && a->p_done != b->p_done), "P pipeline");
    D(a->branch_pending != b->branch_pending || a->ebit_pending != b->ebit_pending ||
      (a->branch_pending && a->branch_target != b->branch_target), "branch/ebit pending");
    for (k = 0; k < 4; k++) {
        int ra = a->vih_reg[(a->vih_pos + k) & 3], rb = b->vih_reg[(b->vih_pos + k) & 3];
        D(ra != rb || (ra >= 0 && a->vih_old[(a->vih_pos + k) & 3] != b->vih_old[(b->vih_pos + k) & 3]), "VI history");
    }
    D(a->prev_vi_write != b->prev_vi_write, "prev_vi_write");
    D(a->stats.pairs != b->stats.pairs || a->stats.cycles != b->stats.cycles ||
      a->stats.stall_cycles != b->stats.stall_cycles || a->stats.xgkicks != b->stats.xgkicks ||
      a->stats.xgkick_bytes != b->stats.xgkick_bytes || a->stats.int_branch_quirks != b->stats.int_branch_quirks ||
      a->stats.q_early_reads != b->stats.q_early_reads || a->stats.runs != b->stats.runs, "stats");
    D(sa->h != sb->h || sa->n != sb->n, "PATH1 packets");
    D(strcmp(a->error, b->error), "error text");
#undef D
    return 0;
}

int main(int argc, char **argv)
{
    static vu_state A, B;
    static uint32_t code[2 * 2048];
    int iters = argc > 1 ? atoi(argv[1]) : 2000, it, check = 0, control = 0, i;
    uint64_t blk_pairs = 0, blk_interp = 0, total_pairs = 0, quirks = 0, stops[5] = {0};
    for (i = 1; i < argc; i++)
        if (!strcmp(argv[i], "--check")) check = 1;
        else if (!strcmp(argv[i], "--control")) control = 1;
    g_rng = argc > 2 && argv[2][0] != '-' ? (uint32_t)strtoul(argv[2], NULL, 0) : 0x12345u;
    if (!g_rng) g_rng = 1;

    for (it = 0; it < iters; it++) {
        sinkh sa = {0xCBF29CE484222325ull, 0}, sb = {0xCBF29CE484222325ull, 0};
        uint32_t n, call, seed_it = g_rng;
        const char *why = NULL;

        vu_release(&A);
        vu_release(&B);
        fuzz_setup(&A, code, &n);
        A.blocks = 0;
        A.blocks_check = 0;
        memcpy(&B, &A, sizeof B);
        B.blk = NULL;
        B.blocks = 1;
        B.blocks_check = check;
        A.gif_sink = B.gif_sink = sink;
        A.gif_user = &sa;
        B.gif_user = &sb;

        vu_start(&A, 0);
        vu_start(&B, 0);
        for (call = 0; call < 40; call++) {
            uint64_t bud = fuzz_budget();
            vu_stop sa_ = vu_run(&A, bud), sb_ = vu_run(&B, bud);
            if (control && it == iters / 2 && call == 0) B.stats.stall_cycles++; /* must be caught */
            uint32_t rat = 0, rnn = 0, spc = 0;
            int rs = 0;
            if (sa_ != sb_) why = "stop reason";
            else if (differs(&A, &B, &sa, &sb, &why)) {}
            if (why) {
                printf("FAIL iteration %d (rng 0x%08X) call %u: %s differs (stop %d)\n", it, seed_it, call, why, (int)sa_);
                return 1;
            }
            stops[sa_ < 5 ? sa_ : 4]++;
            if (!fuzz_next(sa_, n, code, &rat, &rnn, &rs, &spc)) break;
            if (rnn) {
                vu_load_code(&A, rat * 8, code + 2 * rat, rnn * 8);
                vu_load_code(&B, rat * 8, code + 2 * rat, rnn * 8);
            }
            if (rs == 1) { vu_continue(&A); vu_continue(&B); }
            else if (rs == 2) { vu_start(&A, spc); vu_start(&B, spc); }
        }
        blk_pairs += B.stats.blk_pairs;
        blk_interp += B.stats.blk_interp_pairs;
        total_pairs += A.stats.pairs;
        quirks += A.stats.int_branch_quirks;
    }
    printf("rg-vu-blkfuzz: %d iterations, %llu pairs, translated %llu (%.1f %%), interpreted fallback %llu, "
           "quirks %llu, stops idle/ebit/cycles/dbit %llu/%llu/%llu/%llu%s\n",
           iters, (unsigned long long)total_pairs, (unsigned long long)blk_pairs,
           total_pairs ? 100.0 * (double)blk_pairs / (double)total_pairs : 0.0,
           (unsigned long long)blk_interp, (unsigned long long)quirks,
           (unsigned long long)stops[0], (unsigned long long)stops[1], (unsigned long long)stops[2],
           (unsigned long long)stops[3], check ? " (lockstep check on)" : "");
    if (!blk_pairs) {
        printf("FAIL: the translator never ran\n");
        return 1;
    }
    printf("PASS\n");
    return 0;
}
