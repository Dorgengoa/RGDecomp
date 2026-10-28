/* SPDX-License-Identifier: CC0-1.0 */
/* rg-vucensus: disassemble every VU microcode block the retail ELF uploads
 * (census/platform_vu1.tsv lists the packets) and print the opcode census as
 * Markdown (docs/VU.md).
 *
 *   rg-vucensus [--elf PATH] [--tsv PATH] [--dis DIR] [--md FILE]
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vif.h"
#include "vu.h"
#include "vu_decode.h"
#include "vu_retail.h"

#ifndef RG_SOURCE_DIR
#define RG_SOURCE_DIR "."
#endif

typedef struct block {
    uint32_t packet, dest, bytes;
    int vu;                 /* 0 / 1 */
    uint8_t *code;
    uint64_t hash;
    int dup_of;             /* -1 = unique */
    char sha1[16];
} block;

static block g_blk[256];
static int g_nblk;
static uint32_t g_cur_packet;
static int g_cur_vu;

static uint64_t fnv(const uint8_t *p, uint32_t n)
{
    uint64_t h = 1469598103934665603ull;
    while (n--) { h ^= *p++; h *= 1099511628211ull; }
    return h;
}

static void on_mpg(void *user, uint32_t addr, const uint8_t *code, uint32_t bytes)
{
    block *b;
    (void)user;
    if (g_nblk >= 256) return;
    b = &g_blk[g_nblk++];
    memset(b, 0, sizeof *b);
    b->packet = g_cur_packet;
    b->dest = addr;
    b->bytes = bytes;
    b->vu = g_cur_vu;
    b->code = (uint8_t *)malloc(bytes);
    memcpy(b->code, code, bytes);
    b->hash = fnv(code, bytes);
    b->dup_of = -1;
}

typedef struct opstat { const char *name; int upper; unsigned long n; int progs; int last_prog; } opstat;
static opstat g_ops[256];
static int g_nops;

static void count(const char *name, int upper, int prog)
{
    int i;
    for (i = 0; i < g_nops; i++)
        if (g_ops[i].upper == upper && strcmp(g_ops[i].name, name) == 0) break;
    if (i == g_nops) {
        char *s = (char *)malloc(strlen(name) + 1);
        strcpy(s, name);
        g_ops[i].name = s;
        g_ops[i].upper = upper;
        g_ops[i].n = 0;
        g_ops[i].progs = 0;
        g_ops[i].last_prog = -1;
        g_nops++;
    }
    g_ops[i].n++;
    if (g_ops[i].last_prog != prog) { g_ops[i].progs++; g_ops[i].last_prog = prog; }
}

static int cmp_ops(const void *a, const void *b)
{
    const opstat *x = (const opstat *)a, *y = (const opstat *)b;
    if (x->upper != y->upper) return y->upper - x->upper;
    if (x->n != y->n) return x->n < y->n ? 1 : -1;
    return strcmp(x->name, y->name);
}

int main(int argc, char **argv)
{
    const char *elfp = rg_retail_elf_path();
    const char *tsv = RG_SOURCE_DIR "/census/platform_vu1.tsv";
    const char *disdir = NULL, *mdp = NULL;
    rg_elf elf;
    vu_census_row *rows;
    int nrows, i, nuniq = 0;
    unsigned long tot_pairs = 0;
    FILE *md = stdout;
    /* hazard pattern counters (static, over unique blocks) */
    unsigned long h_ibit_i = 0, h_ibit = 0, h_e_in_delay = 0, h_br_in_delay = 0, h_quirk = 0,
                  h_q_early = 0, h_dt = 0, h_m = 0, h_invalid = 0, h_e = 0, h_flagread_close = 0,
                  h_lower_reads_upper_w = 0, h_both_write = 0;

    for (i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "--elf") && i + 1 < argc) elfp = argv[++i];
        else if (!strcmp(argv[i], "--tsv") && i + 1 < argc) tsv = argv[++i];
        else if (!strcmp(argv[i], "--dis") && i + 1 < argc) disdir = argv[++i];
        else if (!strcmp(argv[i], "--md") && i + 1 < argc) mdp = argv[++i];
        else { fprintf(stderr, "usage: %s [--elf P] [--tsv P] [--dis DIR] [--md FILE]\n", argv[0]); return 2; }
    }
    if (rg_elf_load(&elf, elfp)) { fprintf(stderr, "cannot read ELF %s\n", elfp); return 77; }
    nrows = vu_census_load(tsv, &rows);
    if (nrows < 0) { fprintf(stderr, "cannot read %s\n", tsv); return 1; }

    /* replay every distinct MPG packet through a VIF */
    for (i = 0; i < nrows; i++) {
        static vu_state vu;
        static vif_state vif;
        uint32_t pk;
        const uint32_t *w;
        size_t nw;
        int j, seen = 0;
        if (strcmp(rows[i].kind, "mpg")) continue;
        pk = (uint32_t)strtoul(rows[i].addr, NULL, 16);
        for (j = 0; j < i; j++)
            if (!strcmp(rows[j].kind, "mpg") && (uint32_t)strtoul(rows[j].addr, NULL, 16) == pk) seen = 1;
        if (seen) continue;
        g_cur_vu = strstr(rows[i].vu, "VU0") ? 0 : 1;
        g_cur_packet = pk;
        vu_init(&vu, g_cur_vu);
        vif_init(&vif, g_cur_vu, &vu);
        vif.mpg_hook = on_mpg;
        w = rg_vif_packet(&elf, pk, &nw);
        if (!w) { fprintf(stderr, "packet 0x%X not in ELF\n", pk); continue; }
        vif_write(&vif, w, nw);
        if (vif.stats.invalid_cmds) fprintf(stderr, "packet 0x%X: %s\n", pk, vif.error);
        vif_free(&vif);
    }

    for (i = 0; i < g_nblk; i++) {
        int j, r;
        for (j = 0; j < i; j++)
            if (g_blk[j].dup_of < 0 && g_blk[j].hash == g_blk[i].hash && g_blk[j].bytes == g_blk[i].bytes) {
                g_blk[i].dup_of = j;
                break;
            }
        for (r = 0; r < nrows; r++)
            if (!strcmp(rows[r].kind, "mpg") && (uint32_t)strtoul(rows[r].addr, NULL, 16) == g_blk[i].packet &&
                rows[r].dest == g_blk[i].dest)
                memcpy(g_blk[i].sha1, rows[r].sha1, sizeof g_blk[i].sha1);
        if (g_blk[i].dup_of < 0) nuniq++;
    }

    for (i = 0; i < g_nblk; i++) {
        block *b = &g_blk[i];
        uint32_t k, npairs = b->bytes / 8;
        FILE *df = NULL;
        vu_pair prev;
        vu_use prev_lu;
        int have_prev = 0, last_div = -100, last_fmac = -100;
        if (b->dup_of >= 0) continue;
        if (disdir) {
            char path[512];
            snprintf(path, sizeof path, "%s/vu%d_%06X_%04X_%s.txt", disdir, b->vu, b->packet, b->dest, b->sha1);
            df = fopen(path, "w");
        }
        for (k = 0; k < npairs; k++) {
            uint32_t lw, uw, pc = b->dest + k * 8;
            vu_pair p;
            vu_use uu, lu;
            memcpy(&lw, b->code + k * 8, 4);
            memcpy(&uw, b->code + k * 8 + 4, 4);
            vu_decode_pair(lw, uw, &p);
            vu_upper_use(&p.up, &uu);
            vu_lower_use(&p.lo, &lu);
            count(vu_upper_name(&p.up), 1, i);
            count(vu_lower_name(p.lo.op), 0, i);
            tot_pairs++;
            if (p.up.kind == VU_U_INVALID || p.lo.op == VU_L_INVALID) h_invalid++;
            if (p.up.bits & VU_B_I) { h_ibit++; if (uu.reads_i) h_ibit_i++; }
            if (p.up.bits & VU_B_E) { h_e++; if (have_prev && prev_lu.is_branch) h_e_in_delay++; }
            if (p.up.bits & (VU_B_D | VU_B_T)) h_dt++;
            if (p.up.bits & VU_B_M) h_m++;
            if (lu.is_branch && have_prev && prev_lu.is_branch) h_br_in_delay++;
            if (lu.is_cond_branch && have_prev && !prev_lu.is_branch && prev_lu.vi_w > 0 &&
                (prev_lu.vi_w == lu.vi_r0 || prev_lu.vi_w == lu.vi_r1)) {
                h_quirk++;
                count(vu_lower_name(prev.lo.op), 2, i);
            }
            if (p.lo.op == VU_L_DIV || p.lo.op == VU_L_SQRT || p.lo.op == VU_L_RSQRT) last_div = (int)k;
            if (p.lo.op == VU_L_WAITQ) last_div = -100;
            if (uu.uses_q && (int)k - last_div < 7) h_q_early++;
            if ((p.up.kind <= VU_U_MSUB || p.up.kind == VU_U_MUL || p.up.kind == VU_U_OPMULA ||
                 p.up.kind == VU_U_OPMSUB || p.up.kind == VU_U_CLIP))
                last_fmac = (int)k;
            if ((p.lo.op >= VU_L_FCEQ && p.lo.op <= VU_L_FCGET && p.lo.op != VU_L_FCSET && p.lo.op != VU_L_FSSET) &&
                (int)k - last_fmac < 4)
                h_flagread_close++;
            {
                unsigned q;
                for (q = 0; q < lu.n_vf_r; q++)
                    if (uu.vf_w && lu.vf_r[q] == uu.vf_w && (lu.vf_r_mask[q] & uu.vf_w_mask)) h_lower_reads_upper_w++;
                if (uu.vf_w && uu.vf_w == lu.vf_w && (uu.vf_w_mask & lu.vf_w_mask)) h_both_write++;
            }
            if (df) {
                char line[160];
                vu_disasm_pair(&p, pc, line, sizeof line);
                fprintf(df, "%04X: %08X %08X  %s\n", pc, uw, lw, line);
            }
            prev = p;
            prev_lu = lu;
            have_prev = 1;
        }
        (void)prev;
        if (df) fclose(df);
    }

    qsort(g_ops, (size_t)g_nops, sizeof g_ops[0], cmp_ops);
    if (mdp) {
        md = fopen(mdp, "w");
        if (!md) { fprintf(stderr, "cannot write %s\n", mdp); return 1; }
    }
    fprintf(md, "<!-- generated by rg-vucensus from %s -->\n\n", elfp);
    fprintf(md, "Blocks uploaded: %d (%d unique by content), %lu instruction pairs in unique blocks.\n\n",
            g_nblk, nuniq, tot_pairs);
    fprintf(md, "| VU | packet | dest | pairs | sha1 (census) |\n| --- | --- | --- | --- | --- |\n");
    for (i = 0; i < g_nblk; i++)
        if (g_blk[i].dup_of < 0)
            fprintf(md, "| VU%d | 0x%06X | 0x%04X | %u | %s |\n", g_blk[i].vu, g_blk[i].packet, g_blk[i].dest,
                    g_blk[i].bytes / 8, g_blk[i].sha1);
    fprintf(md, "\n#### Upper opcodes\n\n| opcode | uses | blocks |\n| --- | --- | --- |\n");
    for (i = 0; i < g_nops; i++)
        if (g_ops[i].upper == 1) fprintf(md, "| %s | %lu | %d |\n", g_ops[i].name, g_ops[i].n, g_ops[i].progs);
    fprintf(md, "\n#### Lower opcodes\n\n| opcode | uses | blocks |\n| --- | --- | --- |\n");
    for (i = 0; i < g_nops; i++)
        if (g_ops[i].upper == 0) fprintf(md, "| %s | %lu | %d |\n", g_ops[i].name, g_ops[i].n, g_ops[i].progs);
    fprintf(md, "\n#### Static hazard patterns (unique blocks, straight-line scan)\n\n| pattern | sites |\n| --- | --- |\n");
    fprintf(md, "| invalid upper or lower encodings | %lu |\n", h_invalid);
    fprintf(md, "| I bit (LOI) pairs | %lu |\n", h_ibit);
    fprintf(md, "| I bit pairs whose upper reads I | %lu |\n", h_ibit_i);
    fprintf(md, "| E bit pairs | %lu |\n", h_e);
    fprintf(md, "| E bit in a branch delay slot | %lu |\n", h_e_in_delay);
    fprintf(md, "| branch in a branch delay slot | %lu |\n", h_br_in_delay);
    fprintf(md, "| cond. branch reading a VI the previous lower op wrote | %lu |\n", h_quirk);
    fprintf(md, "| upper reads Q < 7 pairs after DIV/SQRT/RSQRT (no WAITQ) | %lu |\n", h_q_early);
    fprintf(md, "| flag read < 4 pairs after an FMAC/CLIP | %lu |\n", h_flagread_close);
    fprintf(md, "| lower reads a VF field the paired upper writes | %lu |\n", h_lower_reads_upper_w);
    fprintf(md, "| upper and lower write the same VF field | %lu |\n", h_both_write);
    fprintf(md, "| D/T bits | %lu |\n| M bits | %lu |\n", h_dt, h_m);
    fprintf(md, "\nWriters at the 'cond. branch reading a VI the previous lower op wrote' sites:");
    for (i = 0; i < g_nops; i++)
        if (g_ops[i].upper == 2) fprintf(md, " %s x%lu;", g_ops[i].name, g_ops[i].n);
    fprintf(md, "\n");
    if (md != stdout) fclose(md);
    rg_elf_free(&elf);
    free(rows);
    return 0;
}
