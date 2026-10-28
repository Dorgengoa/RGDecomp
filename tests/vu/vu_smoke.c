/* SPDX-License-Identifier: CC0-1.0 */
/* Whole-program smoke tests on the RETAIL microcode (ctest -L vu).
 *
 * Needs the retail ELF (RG_ELF, default ../work/SCUS_974.90; read only);
 * exits 77 (skipped) without it.  Inputs are synthetic, so these tests prove
 * that every retail program runs to its E bit through our VIF + VU with no
 * undecodable instruction, that each XGKICK emits a well-formed GIF packet,
 * and that runs are deterministic.  They do NOT prove the output is what a
 * PS2 computes: that needs captured packets (docs/VU.md, "Validation").
 */
#include <stdlib.h>

#include "vif.h"
#include "vu_decode.h"
#include "vu_retail.h"
#include "vu_test.h"

#ifndef RG_SOURCE_DIR
#define RG_SOURCE_DIR "."
#endif

int g_fail;
static rg_elf g_elf;
static vu_census_row *g_rows;
static int g_nrows;
static int g_control;
static int g_verbose;

/* ------------------------------------------------------------ helpers */

static uint64_t fnv(uint64_t h, const void *p, size_t n)
{
    const uint8_t *b = (const uint8_t *)p;
    while (n--) { h ^= *b++; h *= 1099511628211ull; }
    return h;
}

static uint32_t g_seed;
static uint32_t rnd(void) { g_seed = g_seed * 1664525u + 1013904223u; return g_seed >> 8; }

/* GIF output capture + structural check */
typedef struct cap {
    uint64_t hash;
    unsigned kicks, bad, bytes;
    unsigned prims;        /* GIF tags with PRE set */
} cap;

static int gif_well_formed(const uint8_t *d, uint32_t n)
{
    uint32_t off = 0;
    while (off + 16 <= n) {
        uint32_t lo, hi, nloop, eop, flg, nreg, q;
        memcpy(&lo, d + off, 4);
        memcpy(&hi, d + off + 4, 4);
        nloop = lo & 0x7FFF; eop = (lo >> 15) & 1;
        flg = (hi >> 26) & 3; nreg = (hi >> 28) & 15;
        if (!nreg) nreg = 16;
        q = flg == 0 ? nloop * nreg : flg == 1 ? (nloop * nreg + 1) / 2 : nloop;
        off += 16 * (1 + q);
        if (eop) return off == n;
    }
    return 0;
}

static void on_kick(void *user, const uint8_t *d, uint32_t n, uint32_t addr)
{
    cap *c = (cap *)user;
    (void)addr;
    c->kicks++;
    c->bytes += n;
    c->hash = fnv(c->hash, d, n);
    if (!gif_well_formed(d, n)) c->bad++;
    {
        uint32_t hi;
        memcpy(&hi, d + 4, 4);
        if ((hi >> 14) & 1) c->prims++;
    }
}

static int load_packet(vif_state *vif, uint32_t addr)
{
    size_t n;
    const uint32_t *w = rg_vif_packet(&g_elf, addr, &n);
    if (!w) return -1;
    vif_write(vif, w, n);
    return 0;
}

static int setup(void)
{
    char tsv[512];
    if (rg_elf_load(&g_elf, rg_retail_elf_path())) {
        printf("SKIP: retail ELF not found at %s (set RG_ELF)\n", rg_retail_elf_path());
        return 77;
    }
    snprintf(tsv, sizeof tsv, "%s/census/platform_vu1.tsv", RG_SOURCE_DIR);
    g_nrows = vu_census_load(tsv, &g_rows);
    if (g_nrows <= 0) { printf("FAIL: cannot read %s\n", tsv); return 1; }
    return 0;
}

/* ------------------------------------------------------------ census */

static int g_blocks, g_invalid;
static uint64_t g_hashes[128];
static int g_nh;

static void census_hook(void *user, uint32_t addr, const uint8_t *code, uint32_t bytes)
{
    uint64_t h = fnv(1469598103934665603ull, code, bytes);
    uint32_t k;
    int i;
    (void)user; (void)addr;
    g_blocks++;
    for (i = 0; i < g_nh; i++) if (g_hashes[i] == h) break;
    if (i == g_nh && g_nh < 128) g_hashes[g_nh++] = h;
    for (k = 0; k < bytes; k += 8) {
        vu_pair p;
        uint32_t lw, uw;
        memcpy(&lw, code + k, 4);
        memcpy(&uw, code + k + 4, 4);
        vu_decode_pair(lw, uw, &p);
        if (p.up.kind == VU_U_INVALID || p.lo.op == VU_L_INVALID) g_invalid++;
    }
}

static void t_census(void)
{
    int i, j;
    for (i = 0; i < g_nrows; i++) {
        static vu_state vu;
        static vif_state vif;
        uint32_t pk;
        int seen = 0;
        if (strcmp(g_rows[i].kind, "mpg")) continue;
        pk = (uint32_t)strtoul(g_rows[i].addr, NULL, 16);
        for (j = 0; j < i; j++)
            if (!strcmp(g_rows[j].kind, "mpg") && (uint32_t)strtoul(g_rows[j].addr, NULL, 16) == pk) seen = 1;
        if (seen) continue;
        vu_init(&vu, strstr(g_rows[i].vu, "VU0") ? 0 : 1);
        vif_init(&vif, vu.id, &vu);
        vif.mpg_hook = census_hook;
        CHECK(load_packet(&vif, pk) == 0);
        CHECK(vif.stats.invalid_cmds == 0);
        CHECK(vif_idle(&vif));
        vif_free(&vif);
    }
    printf("blocks %d, unique %d, undecodable pairs %d\n", g_blocks, g_nh, g_invalid);
    CHECK(g_blocks == 66);
    CHECK(g_nh == 62);
    CHECK(g_invalid == 0);
}

/* ------------------------------------------------------------ VU0 SRT */

/* MatFromSRTVu0 / MatRotateVu0 call vcallms 0x0 with scale in vf1, angles in
 * vf2 and translation in vf3; the matrix comes back in vf4..vf7. */
static void run_vu0(vu_state *vu, const float s[3], const float r[3], const float t[3], float m[4][4])
{
    int i, j;
    setv(vu, 1, s[0], s[1], s[2], 0);
    setv(vu, 2, r[0], r[1], r[2], 0);
    setv(vu, 3, t[0], t[1], t[2], 0);
    vu_start(vu, 0);
    CHECK(vu_run(vu, 100000) == VU_STOP_EBIT);
    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++) m[i][j] = vu->vf[4 + i].f[j];
}

static void rot_axis(int axis, double a, double R[3][3])
{
    double c = cos(a), s = sin(a);
    int i, j;
    for (i = 0; i < 3; i++) for (j = 0; j < 3; j++) R[i][j] = i == j;
    if (axis == 0) { R[1][1] = c; R[1][2] = s; R[2][1] = -s; R[2][2] = c; }
    if (axis == 1) { R[0][0] = c; R[0][2] = -s; R[2][0] = s; R[2][2] = c; }
    if (axis == 2) { R[0][0] = c; R[0][1] = s; R[1][0] = -s; R[1][1] = c; }
}

static void mat3_mul(double A[3][3], double B[3][3], double C[3][3])
{
    double T[3][3];
    int i, j, k;
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++) {
            T[i][j] = 0;
            for (k = 0; k < 3; k++) T[i][j] += A[i][k] * B[k][j];
        }
    memcpy(C, T, sizeof T);
}

static void t_vu0_srt(void)
{
    static vu_state vu;
    static vif_state vif;
    static const float angles[][3] = {
        {0, 0, 0}, {0.5f, 0, 0}, {0, -1.2f, 0}, {0, 0, 2.5f}, {0.3f, 0.7f, -1.1f},
        {-2.9f, 1.4f, 0.2f}, {3.0f, -3.0f, 1.0f}, {0.01f, 0.02f, 0.03f},
    };
    static const int orders[6][3] = {{0,1,2},{0,2,1},{1,0,2},{1,2,0},{2,0,1},{2,1,0}};
    const float s[3] = {1, 1, 1}, t[3] = {10, -20, 30};
    double worst_orth = 0, best_err[12];
    unsigned a, o;
    int tr, best = -1;
    vu_init(&vu, 0);
    vif_init(&vif, 0, &vu);
    CHECK(load_packet(&vif, 0x445810) == 0);
    for (o = 0; o < 12; o++) best_err[o] = 0;
    for (a = 0; a < sizeof angles / sizeof angles[0]; a++) {
        float m[4][4], m2[4][4];
        int i, j;
        run_vu0(&vu, s, angles[a], t, m);
        run_vu0(&vu, s, angles[a], t, m2);
        CHECK(memcmp(m, m2, sizeof m) == 0); /* deterministic */
        CHECK(m[3][0] == 10 && m[3][1] == -20 && m[3][2] == 30 && m[3][3] == 1);
        for (i = 0; i < 3; i++)
            for (j = 0; j < 3; j++) {
                double d = 0;
                int k;
                for (k = 0; k < 3; k++) d += (double)m[i][k] * m[j][k];
                d -= i == j;
                if (fabs(d) > worst_orth) worst_orth = fabs(d);
            }
        /* compare against all 6 Euler orders x (row/column vector) */
        for (o = 0; o < 6; o++)
            for (tr = 0; tr < 2; tr++) {
                double R[3][3], X[3][3], err = 0;
                int k;
                for (i = 0; i < 3; i++) for (j = 0; j < 3; j++) R[i][j] = i == j;
                for (k = 0; k < 3; k++) {
                    rot_axis(orders[o][k], angles[a][orders[o][k]], X);
                    mat3_mul(R, X, R);
                }
                for (i = 0; i < 3; i++)
                    for (j = 0; j < 3; j++) {
                        double v = tr ? R[j][i] : R[i][j];
                        if (fabs(v - m[i][j]) > err) err = fabs(v - m[i][j]);
                    }
                if (err > best_err[o * 2 + tr]) best_err[o * 2 + tr] = err;
            }
    }
    for (o = 0; o < 12; o++)
        if (best < 0 || best_err[o] < best_err[best]) best = (int)o;
    printf("VU0 SRT: max |R R^T - I| = %.2e; best Euler convention %d (order %d%d%d, %s) max err %.2e\n",
           worst_orth, best, orders[best / 2][0], orders[best / 2][1], orders[best / 2][2],
           best & 1 ? "transposed" : "row", best_err[best]);
    CHECK(worst_orth < 1e-4);
    CHECK(best_err[best] < 1e-4);  /* one standard convention fits every angle set */
    /* scale is applied */
    {
        float m[4][4];
        const float s2[3] = {2, 3, 4}, r0[3] = {0, 0, 0};
        run_vu0(&vu, s2, r0, t, m);
        CHECK(fabsf(m[0][0] - 2) < 1e-6f && fabsf(m[1][1] - 3) < 1e-6f && fabsf(m[2][2] - 4) < 1e-6f);
    }
    vif_free(&vif);
}

/* ------------------------------------------------------------ VU1 variants */

typedef struct variant { char name[16]; uint32_t k[3]; } variant;

static int parse_variants(variant *v, int max)
{
    int i, n = 0;
    for (i = 0; i < g_nrows && n < max; i++) {
        const char *d;
        variant x;
        int j, dup = 0;
        if (strcmp(g_rows[i].kind, "variant")) continue;
        memset(&x, 0, sizeof x);
        snprintf(x.name, sizeof x.name, "%s", g_rows[i].addr);
        d = g_rows[i].detail;
        for (j = 0; j < 3; j++) {
            char key[4];
            const char *p;
            snprintf(key, sizeof key, "k%d=", j);
            p = strstr(d, key);
            if (p && strncmp(p + 3, "0x", 2) == 0) x.k[j] = (uint32_t)strtoul(p + 3, NULL, 16);
        }
        for (j = 0; j < n; j++)
            if (!memcmp(v[j].k, x.k, sizeof x.k)) dup = 1;
        if (!dup) v[n++] = x;
    }
    return n;
}

/* the second-level pieces (0x960 / 0x10E0 / 0x1900 / 0x2100 / 0x18E0) are
 * chosen per material at run time; the smoke test uploads, for each slot, the
 * largest retail block that targets it */
static void upload_second_level(vif_state *vif, uint32_t head)
{
    static const uint32_t pk[] = {0x438C70, 0x43B4F0, 0x43D110};
    /* heads whose material lists (0x449E10/50/90) name 0x10E0+0x18E0 pieces */
    static const uint32_t extra[][2] = {
        {0x440970, 0x440C20}, {0x441660, 0x441840}, {0x4425F0, 0x4427E0}};
    unsigned i;
    for (i = 0; i < sizeof pk / sizeof pk[0]; i++) load_packet(vif, pk[i]);
    for (i = 0; i < sizeof extra / sizeof extra[0]; i++)
        if (extra[i][0] == head) load_packet(vif, extra[i][1]);
}

static void synth_input(vu_state *vu, uint32_t seed, uint32_t n)
{
    uint32_t *m = (uint32_t *)vu->mem;
    unsigned k;
    g_seed = seed;
    for (k = 0; k < 0x4000 / 4; k++) {
        uint32_t r = rnd();
        /* half small integers, half floats in (-4, 4) whose low 16 bits are
         * zero, so that an ILW of any word yields a small count */
        if (r & 1) m[k] = (r >> 1) & 3;
        else m[k] = F((float)((int)(r >> 1) % 4000) / 1000.0f) & 0xFFFF0000u;
    }
    /* The batch layout every head program (0x320) reads, worked out from
     * the retail disassembly:
     *   qw 0       GIF tag template copied to the output (A+D, NLOOP 2)
     *   qw 76.x    output offset from TOP
     *   qw 86.yzw  second GIF tag template (PACKED, NREG 3: ST RGBAQ XYZF2);
     *              its x word (NLOOP|EOP) comes from header z
     *   TOP+0      header (x: A+D data, y: vertex count n, z: n | EOP,
     *              w: offset of array 2), TOP+1 (x, y: offsets of arrays 3, 4)
     *   TOP+2..    vertex arrays
     * The vertex loops are unrolled (by two in most programs), so the test
     * tries a few vertex counts and keeps the first one that terminates. */
    m[0] = 2; m[1] = 0x10000000u; m[2] = 0xE; m[3] = 0;
    m[76 * 4] = 0x60;
    m[86 * 4 + 1] = 0x30000000u; m[86 * 4 + 2] = 0x412; m[86 * 4 + 3] = 0;
    {
        static const uint32_t tops[2] = {0x100, 0x280};
        for (k = 0; k < 2; k++) {
            uint32_t *h = m + tops[k] * 4;
            h[0] = 0x123; h[1] = n; h[2] = n | 0x8000; h[3] = n;
            h[4] = 2 * n; h[5] = 3 * n;
        }
    }
}

typedef struct run_result {
    vu_stop stop;
    uint64_t pairs, hash;
    cap c;
} run_result;

static void run_variant(const variant *v, uint32_t seed, uint32_t nverts, int batches, run_result *rr)
{
    static vu_state vu;
    static vif_state vif;
    uint32_t w[8];
    int b, n;
    memset(rr, 0, sizeof *rr);
    rr->c.hash = 1469598103934665603ull;
    vu_init(&vu, 1);
    vif_init(&vif, 1, &vu);
    vif.vu_cycle_budget = 300000;
    synth_input(&vu, seed, nverts);
    upload_second_level(&vif, v->k[0]);
    for (b = 0; b < 3; b++) if (v->k[b]) CHECK(load_packet(&vif, v->k[b]) == 0);
    vu.gif_sink = on_kick;
    vu.gif_user = &rr->c;
    n = 0;
    w[n++] = 0x03000000u | 0x100;   /* BASE */
    w[n++] = 0x02000000u | 0x180;   /* OFFSET */
    w[n++] = 0x14000064u;           /* MSCAL 0x320: the init call (E bit at once) */
    vif_write(&vif, w, (size_t)n);
    for (b = 0; b < batches; b++) {
        w[0] = 0x17000000u;         /* MSCNT */
        vif_write(&vif, w, 1);
        rr->stop = vif.stats.vu_runaways ? VU_STOP_CYCLES : VU_STOP_EBIT;
    }
    rr->pairs = vu.stats.pairs;
    rr->hash = fnv(rr->c.hash, vu.mem, sizeof vu.mem);
    rr->hash = fnv(rr->hash, vu.vf, sizeof vu.vf);
    rr->hash = fnv(rr->hash, vu.vi, sizeof vu.vi);
    if (vif.stats.vu_runaways) rr->stop = VU_STOP_CYCLES;
    if (g_verbose && rr->stop == VU_STOP_CYCLES) {
        int r;
        printf("  runaway: pc=0x%04X top=0x%X vi:", vu.pc, vu.top);
        for (r = 0; r < 16; r++) printf(" %X", vu.vi[r]);
        printf("\n");
    }
    vif_free(&vif);
}

static void t_variants(void)
{
    variant v[64];
    int n = parse_variants(v, 64), i, finished = 0, kicked = 0;
    CHECK(n >= 12);
    for (i = 0; i < n; i++) {
        static const uint32_t counts[] = {4, 8, 2, 12, 16, 24, 32};
        run_result a, b;
        unsigned c;
        for (c = 0; c < sizeof counts / sizeof counts[0]; c++) {
            run_variant(&v[i], 1234u + (unsigned)i, counts[c], 2, &a);
            if (a.stop == VU_STOP_EBIT) break;
        }
        if (c == sizeof counts / sizeof counts[0]) c--;
        run_variant(&v[i], 1234u + (unsigned)i + (g_control ? 1u : 0u), counts[c], 2, &b);
        if (g_verbose || a.hash != b.hash || a.c.bad)
            printf("%-8s n=%-2u k=%06X/%06X/%06X stop=%d pairs=%llu kicks=%u bytes=%u bad=%u prims=%u hash=%016llx/%016llx\n",
                   v[i].name, counts[c], v[i].k[0], v[i].k[1], v[i].k[2], a.stop, (unsigned long long)a.pairs,
                   a.c.kicks, a.c.bytes, a.c.bad, a.c.prims,
                   (unsigned long long)a.hash, (unsigned long long)b.hash);
        CHECK(a.hash == b.hash);        /* deterministic */
        CHECK(a.c.bad == 0);            /* every XGKICK is well-formed */
        if (a.stop == VU_STOP_EBIT) finished++;
        if (a.c.kicks) kicked++;
    }
    printf("%d distinct variants: %d finished every batch at the E bit, %d emitted GIF packets\n",
           n, finished, kicked);
    CHECK(finished == n);
    /* kind 4 (head 0x4425F0) kicks nothing on this synthetic input */
    CHECK(kicked >= n - 1);
}

typedef struct { const char *name; void (*fn)(void); } test_t;
static const test_t k_tests[] = {
    {"census", t_census},
    {"vu0_srt", t_vu0_srt},
    {"variants", t_variants},
};

int main(int argc, char **argv)
{
    unsigned i;
    int ran = 0, rc;
    const char *want = argc > 1 ? argv[1] : NULL;
    if (getenv("RG_VU_VERBOSE")) g_verbose = 1;
    if (want && !strcmp(want, "variants_control")) {
        g_control = 1;
        want = "variants";
    }
    rc = setup();
    if (rc) return rc;
    for (i = 0; i < sizeof k_tests / sizeof k_tests[0]; i++) {
        int before = g_fail;
        if (want && strcmp(want, k_tests[i].name)) continue;
        k_tests[i].fn();
        printf("%s %s\n", g_fail == before ? "ok  " : "FAIL", k_tests[i].name);
        ran++;
    }
    rg_elf_free(&g_elf);
    free(g_rows);
    if (!ran) { printf("no test named %s\n", want); return 2; }
    return g_fail ? 1 : 0;
}
