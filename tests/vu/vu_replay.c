/* SPDX-License-Identifier: CC0-1.0 */
/* VIFCAP1 replay test (docs/VU.md "Validation against PCSX2", docs/VALIDATION.md
 * item 5).
 *
 *   rg-vu-replay <capture.vifcap> [--control] [--verbose]
 *
 * A capture (tools/trace/vucap.py) holds, for one game frame recorded in
 * PCSX2: the VU1 state and VIF1 registers at the vsync before the frame's
 * VIF1 DMA kick (kinds 1, 2), the VIF word stream of the kicked DMA chain
 * (kind 3), PCSX2's VU1 data memory at the next vsync (kind 5, the expected
 * result), metadata (kind 6) and PCSX2's VU1 code memory at the next vsync
 * (kind 7: every MPG upload must land byte-exact). GIF output (kind 4) is not captured: the
 * PCSX2 GS dump needs the GUI hotkey. So the check is VU1 data memory after
 * the frame's programs against PCSX2's, plus structural checks on the PATH1
 * packets (every XGKICK packet ends in EOP, all words consumed, no runaway).
 *
 * Comparison classes per 32-bit word of VU1 memory:
 *   exact   identical bits;
 *   close   both finite floats of the same sign within 16 ulp, or integers
 *           differing by 1 (FTOI4 coordinates) -- docs/VU.md caveat 1;
 *   wrong   anything else.
 * Pass: no wrong word (close words are allowed), VU1 code memory identical,
 * and no structural error.  (Until the V3 W-lane rule was measured the bar
 * was <= 0.5% of the words PCSX2 changed; docs/VALIDATION.md section 5.)
 *
 * --control flips bit 30 of the first payload word of the last UNPACK in the
 * stream (title captures, which have no UNPACK: of the first MPG), a
 * deliberate fault that must FAIL.
 *
 * Exit: 0 pass, 1 fail, 77 skipped (no capture file given or found).
 */
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "vif.h"
#include "vu.h"

typedef struct rec { uint32_t kind, bytes; const uint8_t *p; } rec;

static uint8_t *g_file;
static rec g_rec[64];
static int g_nrec;

static int load(const char *path)
{
    FILE *f = fopen(path, "rb");
    long n;
    uint32_t i, cnt, off;
    if (!f) return 0;
    fseek(f, 0, SEEK_END);
    n = ftell(f);
    fseek(f, 0, SEEK_SET);
    g_file = (uint8_t *)malloc((size_t)n);
    if (fread(g_file, 1, (size_t)n, f) != (size_t)n) { fclose(f); return 0; }
    fclose(f);
    if (n < 12 || memcmp(g_file, "VIFCAP1\0", 8) != 0) return 0;
    memcpy(&cnt, g_file + 8, 4);
    off = 12;
    for (i = 0; i < cnt && g_nrec < 64; i++) {
        rec r;
        memcpy(&r.kind, g_file + off, 4);
        memcpy(&r.bytes, g_file + off + 4, 4);
        r.p = g_file + off + 8;
        off += 8 + r.bytes;
        if (off > (uint32_t)n) return 0;
        g_rec[g_nrec++] = r;
    }
    return 1;
}

static const rec *find(uint32_t kind)
{
    int i;
    for (i = 0; i < g_nrec; i++)
        if (g_rec[i].kind == kind) return &g_rec[i];
    return NULL;
}

static uint32_t rd32(const uint8_t *p) { uint32_t v; memcpy(&v, p, 4); return v; }

/* FNV-1a 64 over the PATH1 packets (bytes and VU address): the HASH line
 * lets two builds' interpreters be compared bit for bit (docs/VU.md
 * "Performance": rg-vu-replay vs rg-vu-replay-ref) */
static uint64_t fnv(uint64_t h, const void *p, size_t n)
{
    const uint8_t *b = (const uint8_t *)p;
    while (n--) h = (h ^ *b++) * 0x100000001B3ull;
    return h;
}
static uint64_t g_p1_hash = 0xCBF29CE484222325ull;

/* PATH1 sink: structural checks and the stream hash */
static struct { uint64_t packets, bytes, bad; } g_p1, g_p2;
static void p1_sink(void *u, const uint8_t *d, uint32_t bytes, uint32_t addr)
{
    (void)u;
    g_p1_hash = fnv(fnv(g_p1_hash, &addr, 4), d, bytes);
    g_p1.packets++;
    g_p1.bytes += bytes;
    if (bytes == 0 || (bytes & 15)) g_p1.bad++;
}
static void p2_sink(void *u, const uint8_t *d, uint32_t bytes)
{
    (void)u; (void)d;
    g_p2.packets++;
    g_p2.bytes += bytes;
    if (bytes & 15) g_p2.bad++;
}

static int is_float_like(uint32_t w)
{
    uint32_t e = (w >> 23) & 0xFF;
    return e != 0 && e != 0xFF;
}

static int close_word(uint32_t a, uint32_t b)
{
    if (is_float_like(a) && is_float_like(b) && ((a ^ b) >> 31) == 0) {
        uint32_t d = a > b ? a - b : b - a;
        return d <= 16;
    }
    {
        int32_t d = (int32_t)(a - b);
        return d == 1 || d == -1;
    }
}

int main(int argc, char **argv)
{
    static vu_state vu;
    static vif_state vif;
    const char *path = NULL;
    int control = 0, verbose = 0, i, reps = 1, rep;
    double best_ms = 1e30;
    const rec *r1, *r2, *r3, *r5, *r6;
    uint8_t before[0x4000];
    uint32_t nwords, k, exact = 0, close = 0, wrong = 0, changed = 0;
    uint32_t *words;
    size_t used;

    for (i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "--control")) control = 1;
        else if (!strcmp(argv[i], "--verbose")) verbose = 1;
        else if (!strcmp(argv[i], "--reps") && i + 1 < argc) reps = atoi(argv[++i]);
        else path = argv[i];
    }
    if (!path) path = getenv("RG_VIFCAP");
    if (!path || !load(path)) {
        printf("SKIP: no VIFCAP1 capture (%s)\n", path ? path : "pass a path or set RG_VIFCAP");
        return 77;
    }
    r1 = find(1); r2 = find(2); r3 = find(3); r5 = find(5); r6 = find(6);
    if (!r1 || !r2 || !r3 || !r5 || r1->bytes < 0x8000 + 0x200 + 32 + 16 + 32 || r5->bytes != 0x4000) {
        printf("FAIL: capture lacks kinds 1/2/3/5\n");
        return 1;
    }
    if (r6 && r6->bytes >= 24)
        printf("frame %u game vbl %u chain %08X (%u qwords)\n", rd32(r6->p), rd32(r6->p + 4),
               rd32(r6->p + 12), rd32(r6->p + 16));

    if (reps < 1) reps = 1;
    for (rep = 0; rep < reps; rep++) {
    clock_t t0;
    memset(&g_p1, 0, sizeof g_p1);
    memset(&g_p2, 0, sizeof g_p2);
    g_p1_hash = 0xCBF29CE484222325ull;
    vu_init(&vu, 1);
    vif_init(&vif, 1, &vu);
    vu.gif_sink = p1_sink;
    vif.gif_sink = p2_sink;
    {   /* kind 1: data, code, vf[32], vi[16] u16, acc, q p i r mac status clip tpc */
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
    {   /* kind 2: cl wl mode mask row[4] col[4] base ofst tops itops dbf */
        const uint8_t *p = r2->p;
        vif.cl = rd32(p); vif.wl = rd32(p + 4); vif.mode = rd32(p + 8); vif.mask = rd32(p + 12);
        for (k = 0; k < 4; k++) { vif.row[k] = rd32(p + 16 + 4 * k); vif.col[k] = rd32(p + 32 + 4 * k); }
        vif.base = rd32(p + 48); vif.ofst = rd32(p + 52); vif.tops = rd32(p + 56);
        vif.itops = rd32(p + 60); vif.dbf = rd32(p + 64);
    }
    memcpy(before, vu.mem, 0x4000);

    nwords = r3->bytes / 4;
    words = (uint32_t *)malloc((size_t)nwords * 4 + 16);
    memcpy(words, r3->p, (size_t)nwords * 4);
    if (control) {
        /* deliberate fault: flip one bit in the first payload word of the
         * LAST UNPACK in the stream (its data is not overwritten later in the
         * frame), else of the first MPG; the comparison must then fail */
        uint32_t pos = 0, cl = vif.cl, wl = vif.wl, hit = 0, cmd;
        long n;
        int pass;
        for (pass = 0; pass < 2 && !hit; pass++) {
            pos = 0; cl = vif.cl; wl = vif.wl;
            while (pos < nwords) {
                cmd = (words[pos] >> 24) & 0x7F;
                n = vif_payload_words(words[pos], cl, wl);
                if (n < 0) break;
                if (cmd == VIF_STCYCL) { cl = words[pos] & 0xFF; wl = (words[pos] >> 8) & 0xFF; }
                if (n > 0 && pass == 0 && cmd >= 0x60) hit = pos + 1;
                if (n > 0 && pass == 1 && cmd == VIF_MPG) {
                    hit = pos + 1;
                    break;
                }
                pos += 1 + (uint32_t)n;
            }
        }
        if (hit) words[hit] ^= 0x40000000u;
        printf("control: flipped bit 30 of stream word %u\n", hit);
    }
    t0 = clock();
    used = vif_write(&vif, words, nwords);
    {
        double ms = (double)(clock() - t0) * 1000.0 / CLOCKS_PER_SEC;
        if (ms < best_ms) best_ms = ms;
    }
    if (rep + 1 < reps) free(words);
    }
    if (reps > 1) printf("TIME vif_write best of %d: %.2f ms\n", reps, best_ms);
#ifdef RG_VU_HAS_BLOCKS
    printf("BLK blocks %d check %d: runs %llu pairs %llu interpreted %llu builds %llu variants %llu\n",
           vu.blocks, vu.blocks_check, (unsigned long long)vu.stats.blk_runs,
           (unsigned long long)vu.stats.blk_pairs, (unsigned long long)vu.stats.blk_interp_pairs,
           (unsigned long long)vu.stats.blk_builds, (unsigned long long)vu.stats.blk_variants);
#endif
    {
        uint64_t h = 0xCBF29CE484222325ull;
        h = fnv(h, vu.mem, sizeof vu.mem);
        h = fnv(h, vu.vf, sizeof vu.vf);
        h = fnv(h, &vu.acc, sizeof vu.acc);
        h = fnv(h, vu.vi, sizeof vu.vi);
        h = fnv(h, &vu.q, 4); h = fnv(h, &vu.p, 4); h = fnv(h, &vu.i, 4); h = fnv(h, &vu.r, 4);
        h = fnv(h, &vu.mac, 4); h = fnv(h, &vu.status, 4); h = fnv(h, &vu.clip, 4);
        h = fnv(h, &vu.tpc, 4); h = fnv(h, &vu.cycle, 8);
        printf("HASH path1 %016llX state %016llX pairs %llu cycles %llu stalls %llu quirks %llu\n",
               (unsigned long long)g_p1_hash, (unsigned long long)h,
               (unsigned long long)vu.stats.pairs, (unsigned long long)vu.stats.cycles,
               (unsigned long long)vu.stats.stall_cycles, (unsigned long long)vu.stats.int_branch_quirks);
    }

    for (k = 0; k < 0x4000; k += 4) {
        uint32_t got = rd32(vu.mem + k), want = rd32(r5->p + k), was = rd32(before + k);
        if (want != was) changed++;
        if (got == want) exact++;
        else if (close_word(got, want)) close++;
        else {
            wrong++;
            if (verbose && wrong <= 40)
                printf("  qw %03X.%u: got %08X want %08X (before %08X)\n", k >> 4, (k >> 2) & 3, got, want, was);
        }
    }
    printf("stream %u words, consumed %u; MSCAL %llu, MPG bytes %llu, unpack qw %llu, runaways %llu, invalid %llu\n",
           nwords, (unsigned)used, (unsigned long long)vif.stats.mscal, (unsigned long long)vif.stats.mpg_bytes,
           (unsigned long long)vif.stats.unpack_qwords, (unsigned long long)vif.stats.vu_runaways,
           (unsigned long long)vif.stats.invalid_cmds);
    printf("PATH1 %llu packets %llu bytes (bad %llu); PATH2 %llu packets %llu bytes\n",
           (unsigned long long)g_p1.packets, (unsigned long long)g_p1.bytes, (unsigned long long)g_p1.bad,
           (unsigned long long)g_p2.packets, (unsigned long long)g_p2.bytes);
    printf("VU1 memory vs PCSX2: %u exact, %u close, %u wrong (of 4096 words; %u changed in PCSX2 during the frame)\n",
           exact, close, wrong, changed);
    if (vif.error[0]) printf("vif error: %s\n", vif.error);
    if (vu.error[0]) printf("vu error: %s\n", vu.error);
    {
        const rec *r7 = find(7);
        uint32_t code_diff = 0;
        if (r7 && r7->bytes == 0x4000) {
            for (k = 0; k < 0x4000; k += 8)
                if (memcmp(vu.code + k, r7->p + k, 8)) code_diff++;
            printf("VU1 code memory vs PCSX2: %u of 2048 instruction pairs differ\n", code_diff);
        }
        if (code_diff) wrong += code_diff;
    }
    {
        int ok = used == nwords && vif.stats.vu_runaways == 0 && vif.stats.invalid_cmds == 0 && g_p1.bad == 0 &&
                 wrong == 0;
        printf("%s\n", ok ? "PASS" : "FAIL");
        free(words);
        return ok ? 0 : 1;
    }
}
