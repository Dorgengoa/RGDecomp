/* SPDX-License-Identifier: CC0-1.0 */
/* rg-nr-vutrace: VU1 microprogram census and corpus tool for the native
 * renderer lane (docs/NATIVE-RENDER.md "Tools").  Never part of the game.
 *
 *   rg-nr-vutrace CAPTURE.vifcap [--cov OUT.tsv] [--runs OUT.tsv]
 *                 [--corpus OUT.bin] [--corpus-pc 0x328,0x330] [--dis A-B]
 *
 * Replays one VIFCAP1 capture (tools/trace/vucap.py; docs/VU.md "Replay test")
 * through the VIF1 + VU1 interpreter, stepping every program pair by pair
 * (block translator off), and records
 *   --cov   per executed pc: the MPG upload resident there (upload id), and
 *           the number of times the pair ran.  Uploads are listed as
 *           "U id dest bytes word0 word1" lines so a script can match them
 *           to the retail packets (tools/native/render_vucov.py).
 *   --runs  one line per MSCAL/MSCNT: entry pc, pairs, cycles, XGKICKs and the
 *           upload ids resident at the piece addresses 0x320, 0x960, 0x10E0,
 *           0x1900, 0x2620, 0x39D0 (the dominant model program's layout).
 *   --corpus  for runs whose entry pc is in --corpus-pc: the complete VU1
 *           state before the run (data memory, VF, VI, ACC, Q, P, I, top,
 *           itop) and every PATH1 packet it kicked; the input of the native
 *           microprogram checks (render_nmcheck).
 * The VIF bookkeeping of MSCAL/MSCNT is the same as src/ps2/vif/vif.c
 * start_vu (TOP/ITOP/DBF).
 */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vif.h"
#include "vu.h"
#include "vu_decode.h"

typedef struct rec { uint32_t kind, bytes; const uint8_t *p; } rec;
static uint8_t *g_file;
static rec g_rec[64];
static int g_nrec;

static uint32_t rd32(const uint8_t *p) { uint32_t v; memcpy(&v, p, 4); return v; }

static int load(const char *path)
{
    FILE *f = fopen(path, "rb");
    long n;
    uint32_t i, cnt, off;
    if (!f) return 0;
    fseek(f, 0, SEEK_END); n = ftell(f); fseek(f, 0, SEEK_SET);
    g_file = (uint8_t *)malloc((size_t)n);
    if (fread(g_file, 1, (size_t)n, f) != (size_t)n) { fclose(f); return 0; }
    fclose(f);
    if (n < 12 || memcmp(g_file, "VIFCAP1\0", 8) != 0) return 0;
    cnt = rd32(g_file + 8); off = 12;
    for (i = 0; i < cnt && g_nrec < 64; i++) {
        rec r;
        r.kind = rd32(g_file + off); r.bytes = rd32(g_file + off + 4); r.p = g_file + off + 8;
        off += 8 + r.bytes;
        if (off > (uint32_t)n) return 0;
        g_rec[g_nrec++] = r;
    }
    return 1;
}
static const rec *find(uint32_t kind)
{
    int i;
    for (i = 0; i < g_nrec; i++) if (g_rec[i].kind == kind) return &g_rec[i];
    return NULL;
}

/* resident upload per code pair; upload 0 = the capture's initial code */
#define MAXUP 65536
static int g_res[2048];
static struct { uint32_t dest, bytes, w0, w1, w2, w3, h; } g_up[MAXUP];
static int g_nup = 1;
static uint32_t g_cov[MAXUP > 4096 ? 4096 : 4096][1]; /* unused placeholder */
typedef struct cov { int up; uint32_t pc; uint64_t n; } cov;
static cov *g_covs; static size_t g_ncov, g_capcov;
static uint64_t g_hits[2048];  /* per pc for the current residency */

static void flush_pc(uint32_t pair)
{
    if (!g_hits[pair]) return;
    if (g_ncov == g_capcov) { g_capcov = g_capcov ? g_capcov * 2 : 4096; g_covs = (cov *)realloc(g_covs, g_capcov * sizeof(cov)); }
    g_covs[g_ncov].up = g_res[pair]; g_covs[g_ncov].pc = pair * 8; g_covs[g_ncov].n = g_hits[pair];
    g_ncov++;
    g_hits[pair] = 0;
}

static void on_mpg(void *user, uint32_t addr, const uint8_t *code, uint32_t bytes)
{
    uint32_t a;
    (void)user;
    if (g_nup >= MAXUP) return;
    g_up[g_nup].dest = addr; g_up[g_nup].bytes = bytes;
    g_up[g_nup].w0 = bytes >= 4 ? rd32(code) : 0; g_up[g_nup].w1 = bytes >= 8 ? rd32(code + 4) : 0;
    g_up[g_nup].w2 = bytes >= 12 ? rd32(code + 8) : 0; g_up[g_nup].w3 = bytes >= 16 ? rd32(code + 12) : 0;
    { uint32_t h = 2166136261u, j; for (j = 0; j < bytes; j++) h = (h ^ code[j]) * 16777619u; g_up[g_nup].h = h; }
    for (a = addr; a < addr + bytes && a < 0x4000; a += 8) { flush_pc(a / 8); g_res[a / 8] = g_nup; }
    g_nup++;
}

/* PATH1 capture for the corpus */
static uint8_t *g_p1buf; static size_t g_p1n, g_p1cap; static uint32_t g_p1cnt;
static int g_capture;
static void p1_sink(void *u, const uint8_t *d, uint32_t bytes, uint32_t addr)
{
    (void)u;
    if (!g_capture) return;
    if (g_p1n + bytes + 8 > g_p1cap) { g_p1cap = (g_p1n + bytes + 8) * 2; g_p1buf = (uint8_t *)realloc(g_p1buf, g_p1cap); }
    memcpy(g_p1buf + g_p1n, &addr, 4); memcpy(g_p1buf + g_p1n + 4, &bytes, 4);
    memcpy(g_p1buf + g_p1n + 8, d, bytes);
    g_p1n += 8 + bytes; g_p1cnt++;
}
static void p2_sink(void *u, const uint8_t *d, uint32_t bytes) { (void)u; (void)d; (void)bytes; }

int main(int argc, char **argv)
{
    static vu_state vu;
    static vif_state vif;
    const char *dis = NULL;
    const char *path = NULL, *covp = NULL, *runsp = NULL, *corp = NULL;
    uint32_t cpc[16]; int ncpc = 0;
    FILE *covf = NULL, *runf = NULL, *corf = NULL;
    const rec *r1, *r2, *r3;
    uint32_t nwords, pos = 0, k;
    uint32_t *words;
    unsigned runno = 0;
    int i;

    for (i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "--cov") && i + 1 < argc) covp = argv[++i];
        else if (!strcmp(argv[i], "--runs") && i + 1 < argc) runsp = argv[++i];
        else if (!strcmp(argv[i], "--corpus") && i + 1 < argc) corp = argv[++i];
        else if (!strcmp(argv[i], "--dis") && i + 1 < argc) dis = argv[++i];
        else if (!strcmp(argv[i], "--corpus-pc") && i + 1 < argc) {
            char *s = argv[++i];
            while (*s && ncpc < 16) { cpc[ncpc++] = (uint32_t)strtoul(s, &s, 0); if (*s == ',') s++; }
        } else path = argv[i];
    }
    if (!path || !load(path)) { fprintf(stderr, "usage: rg-nr-vutrace CAPTURE [--cov F] [--runs F] [--corpus F --corpus-pc a,b]\n"); return 2; }
    if (!ncpc) { cpc[ncpc++] = 0x328; cpc[ncpc++] = 0x330; }
    r1 = find(1); r2 = find(2); r3 = find(3);
    if (!r1 || !r2 || !r3) { fprintf(stderr, "capture lacks kinds 1/2/3\n"); return 1; }

    vu_init(&vu, 1);
    vu.blocks = 0;
    vif_init(&vif, 1, &vu);
    vu.gif_sink = p1_sink; vu.gif_user = &vu;
    vif.gif_sink = p2_sink;
    vif.mpg_hook = on_mpg;
    {
        const uint8_t *p = r1->p;
        memcpy(vu.mem, p, 0x4000);
        vu_load_code(&vu, 0, p + 0x4000, 0x4000);
        p += 0x8000;
        memcpy(vu.vf, p, 0x200); p += 0x200;
        for (k = 0; k < 16; k++) { uint16_t v; memcpy(&v, p + 2 * k, 2); vu.vi[k] = v; }
        p += 32;
        memcpy(&vu.acc, p, 16); p += 16;
        vu.q = rd32(p); vu.p = rd32(p + 4); vu.i = rd32(p + 8); vu.r = rd32(p + 12);
        vu.mac = rd32(p + 16); vu.status = rd32(p + 20); vu.clip = rd32(p + 24); vu.tpc = rd32(p + 28);
        vu.vf[0].u[0] = vu.vf[0].u[1] = vu.vf[0].u[2] = 0; vu.vf[0].u[3] = 0x3F800000u;
        vu.vi[0] = 0;
    }
    {
        const uint8_t *p = r2->p;
        vif.cl = rd32(p); vif.wl = rd32(p + 4); vif.mode = rd32(p + 8); vif.mask = rd32(p + 12);
        for (k = 0; k < 4; k++) { vif.row[k] = rd32(p + 16 + 4 * k); vif.col[k] = rd32(p + 32 + 4 * k); }
        vif.base = rd32(p + 48); vif.ofst = rd32(p + 52); vif.tops = rd32(p + 56);
        vif.itops = rd32(p + 60); vif.dbf = rd32(p + 64);
    }
    g_up[0].dest = 0; g_up[0].bytes = 0x4000;
    if (covp) covf = fopen(covp, "w");
    if (runsp) { runf = fopen(runsp, "w"); if (runf) fprintf(runf, "run\tentry\tpairs\tcycles\tkicks\tu320\tu960\tu10E0\tu1900\tu2620\tu39D0\ttop\n"); }
    if (corp) { corf = fopen(corp, "wb"); if (corf) fwrite("NRCORP1\0", 1, 8, corf); }

    nwords = r3->bytes / 4;
    words = (uint32_t *)r3->p;
    while (pos < nwords) {
        uint32_t code = words[pos], cmd = (code >> 24) & 0x7F;
        long n = vif_payload_words(code, vif.cl, vif.wl);
        if (n < 0) { fprintf(stderr, "bad VIF code %08X at %u\n", code, pos); break; }
        if ((cmd == VIF_MSCAL || cmd == VIF_MSCALF || cmd == VIF_MSCNT) && vif_idle(&vif)) {
            uint32_t entry;
            uint64_t p0 = vu.stats.pairs, c0 = vu.stats.cycles, x0 = vu.stats.xgkicks;
            unsigned steps = 0;
            int cap;
            vif.stats.cmds[cmd]++;
            vif.itop = vif.itops; vu.itop = (uint16_t)vif.itop;
            vif.top = vif.tops; vu.top = (uint16_t)vif.top;
            vif.dbf ^= 1; vif.tops = vif.base + (vif.dbf ? vif.ofst : 0);
            entry = cmd == VIF_MSCNT ? vu.tpc : (code & 0xFFFF) * 8;
            cap = 0;
            for (k = 0; k < (uint32_t)ncpc; k++) if (cpc[k] == entry) cap = 1;
            if (corf && cap) {
                /* header: run, entry, top, itop, q, p, i, 0, then the lower
                 * words of the first two pairs at the piece addresses 0x320,
                 * 0x960, 0x10E0, 0x1900, 0x39D0 (which retail block is
                 * resident: render_nmcheck's piece table) */
                static const uint32_t piece[5] = {0x320, 0x960, 0x10E0, 0x1900, 0x39D0};
                uint32_t hdr[18] = {runno, entry, vu.top, vu.itop, vu.q, vu.p, vu.i, 0};
                for (k = 0; k < 5; k++) { hdr[8 + 2 * k] = rd32(vu.code + piece[k]); hdr[9 + 2 * k] = rd32(vu.code + piece[k] + 8); }
                fwrite("RUN1", 1, 4, corf);
                fwrite(hdr, 4, 18, corf);
                fwrite(vu.mem, 1, 0x4000, corf);
                fwrite(vu.vf, 1, 0x200, corf);
                fwrite(&vu.acc, 1, 16, corf);
                fwrite(vu.vi, 2, 16, corf);
            }
            g_capture = corf && cap; g_p1n = 0; g_p1cnt = 0;
            if (cmd == VIF_MSCNT) vu_continue(&vu); else vu_start(&vu, entry);
            while (vu.running && steps < 4000000) {
                uint32_t pc = vu.pc & 0x3FF8;
                g_hits[pc / 8]++;
                vu_step(&vu);
                steps++;
            }
            vu_drain(&vu);
            if (g_capture) {
                fwrite(&g_p1cnt, 4, 1, corf);
                fwrite(&g_p1n, 4, 1, corf);
                fwrite(g_p1buf, 1, g_p1n, corf);
            }
            g_capture = 0;
            if (runf)
                fprintf(runf, "%u\t%04X\t%llu\t%llu\t%llu\t%d\t%d\t%d\t%d\t%d\t%d\t%u\n", runno, entry,
                        (unsigned long long)(vu.stats.pairs - p0), (unsigned long long)(vu.stats.cycles - c0),
                        (unsigned long long)(vu.stats.xgkicks - x0), g_res[0x320 / 8], g_res[0x960 / 8],
                        g_res[0x10E0 / 8], g_res[0x1900 / 8], g_res[0x2620 / 8], g_res[0x39D0 / 8], vu.top);
            runno++;
            pos += 1;
            continue;
        }
        vif_write(&vif, words + pos, 1 + (uint32_t)n);
        pos += 1 + (uint32_t)n;
    }
    for (k = 0; k < 2048; k++) flush_pc(k);
    if (dis) { /* --dis A-B: disassemble VU1 code memory as it is at the end */
        unsigned a0 = 0, a1 = 0, pc; char buf[160]; vu_pair pr;
        sscanf(dis, "%x-%x", &a0, &a1);
        for (pc = a0 & ~7u; pc < a1 && pc < 0x4000; pc += 8) {
            vu_decode_pair(rd32(vu.code + pc), rd32(vu.code + pc + 4), &pr);
            vu_disasm_pair(&pr, pc, buf, sizeof buf);
            printf("%04X: %08X %08X  %s\n", pc, rd32(vu.code + pc + 4), rd32(vu.code + pc), buf);
        }
    }
    if (covf) {
        for (i = 0; i < g_nup; i++)
            fprintf(covf, "U\t%d\t%04X\t%u\t%08X\t%08X\t%08X\t%08X\t%08X\n", i, g_up[i].dest, g_up[i].bytes, g_up[i].w0, g_up[i].w1, g_up[i].w2, g_up[i].w3, g_up[i].h);
        for (k = 0; k < g_ncov; k++) fprintf(covf, "C\t%d\t%04X\t%llu\n", g_covs[k].up, g_covs[k].pc, (unsigned long long)g_covs[k].n);
        fclose(covf);
    }
    if (runf) fclose(runf);
    if (corf) fclose(corf);
    fprintf(stderr, "runs %u, uploads %d, pairs %llu, kicks %llu, stream %u/%u words\n", runno, g_nup,
            (unsigned long long)vu.stats.pairs, (unsigned long long)vu.stats.xgkicks, pos, nwords);
    (void)g_cov;
    return 0;
}
