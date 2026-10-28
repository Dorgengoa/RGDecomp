/* SPDX-License-Identifier: CC0-1.0
 * Native module table tests (src/native/ovl, docs/OVERLAY.md section 8) on two
 * SYNTHETIC modules.   rg-ovl-native-tests <name>   exit 0 = pass
 *   data_restore   load restores .data from the image, switch keeps the other
 *                  module's segment untouched, reload restores again
 *   bss_ctors      .bss zeroed before the ctors run, ctors in table order on every
 *                  load, the module is active while its ctors run
 *   imports        one import, two modules: dispatch follows the active module
 *                  through the trampoline (int, x87 float, 16-byte sret, 2 args);
 *                  a data-slot import of another module is reported (DOMAIN);
 *                  an import the active module lacks / no module: reported, stub 0
 *   bind           OverlayLoadFile_100410 by retail path strings; find_file;
 *                  an arena registry and an import with an address are rejected
 *   *_control      deliberately wrong (must FAIL) */
#include "ovl.h"
#include "ovl_gen.h"
#include "rg_trace.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int OverlayLoadFile_100410(int path, int load);
void rg_ovl_service_init(void *user);

static int g_fail, g_control;
#define CHECK(c)                                                              \
    do {                                                                      \
        if (!(c)) {                                                           \
            fprintf(stderr, "%s:%d: CHECK failed: %s\n", __FILE__, __LINE__, #c); \
            g_fail = 1;                                                       \
        }                                                                     \
    } while (0)

/* ---- two modules: alpha (data 16 words, bss 32 bytes), beta (data 8, bss 64) ---- */
static unsigned char alpha_seg[64 + 32] __attribute__((aligned(128)));
static unsigned char beta_seg[32 + 64] __attribute__((aligned(128)));
static const uint32_t alpha_img[16] = {0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7,
                                       0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, (uint32_t)(uintptr_t)alpha_seg};
static const uint32_t beta_img[8] = {0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7};

static int g_order[16], g_norder;
static uint32_t g_seen_bss, g_seen_data;
static int g_seen_cur;
static void alpha_c0(void)
{
    g_order[g_norder++] = 1;
    memcpy(&g_seen_bss, alpha_seg + 64 + 4, 4);
    memcpy(&g_seen_data, alpha_seg + 4, 4);
    g_seen_cur = rg_ovl_current();
    alpha_seg[64 + 4] = 0x55;               /* a ctor's bss write survives the load */
}
static void alpha_c1(void) { g_order[g_norder++] = 2; }
static void beta_c0(void) { g_order[g_norder++] = 10; }
static const rg_ovl_fn alpha_ctors[] = {alpha_c0, alpha_c1};
static const rg_ovl_fn alpha_ctors_rev[] = {alpha_c1, alpha_c0};
static const rg_ovl_fn beta_ctors[] = {beta_c0};

/* the shared import: different prototypes per module are the caller's business;
 * here every module's entry has the caller's prototype */
typedef struct { int a, b, c, d; } quad;
static int a_int(int x, int y) { return x * 100 + y; }
static int b_int(int x, int y) { return -(x * 100 + y); }
static float a_flt(float x) { return x * 2.0f; }
static float b_flt(float x) { return x * 3.0f; }
static quad a_quad(int x) { quad q = {x, x + 1, x + 2, x + 3}; return q; }
static quad b_quad(int x) { quad q = {-x, -x - 1, -x - 2, -x - 3}; return q; }
static int a_only(void) { return 7; }

static const rg_ovl_fn imp_int[2] = {(rg_ovl_fn)a_int, (rg_ovl_fn)b_int};
static const rg_ovl_fn imp_flt[2] = {(rg_ovl_fn)a_flt, (rg_ovl_fn)b_flt};
static const rg_ovl_fn imp_quad[2] = {(rg_ovl_fn)a_quad, (rg_ovl_fn)b_quad};
static const rg_ovl_fn imp_only[2] = {(rg_ovl_fn)a_only, 0};
static const rg_ovl_fn imp_slot[2] = {(rg_ovl_fn)a_only, (rg_ovl_fn)a_only};
const rg_ovl_import t_imports[] = {
    {"func_int", 0, -1, 0, imp_int},
    {"func_flt", 0, -1, 0, imp_flt},
    {"func_quad", 0, -1, 0, imp_quad},
    {"func_only", 0, -1, 0, imp_only},
    {"slot_alpha", 0, 0, 1, imp_slot},
};
RG_OVL_TRAMPOLINE(t_func_int, t_imports, 0)
RG_OVL_TRAMPOLINE(t_func_flt, t_imports, 1)
RG_OVL_TRAMPOLINE(t_func_quad, t_imports, 2)
RG_OVL_TRAMPOLINE(t_func_only, t_imports, 3)
RG_OVL_TRAMPOLINE(t_slot_alpha, t_imports, 4)

static rg_ovl_desc t_descs[2] = {
    {"alpha", "ALPHA.BIN", 2, 2, 0, 0, 64, 32, 0, 0, alpha_img, 0, 0, alpha_ctors, 2, 0, 0, 0, 0, 0, 0, alpha_seg},
    {"beta", "BETA.BIN", 3, 5, 0, 0, 32, 64, 0, 0, beta_img, 0, 0, beta_ctors, 1, 0, 0, 0, 0, 0, 0, beta_seg},
};
static const rg_ovl_registry t_reg = {t_descs, 2, 0, 0, 0, t_imports, 5, "test"};

static int g_reports;
static int g_last_kind;
static void on_report(void *u, int kind, int ovl, uint32_t addr, const char *msg)
{
    (void)u; (void)ovl; (void)addr; (void)msg;
    g_reports++;
    g_last_kind = kind;
}

static void setup(void)
{
    rg_ovl_set_report(on_report, NULL);
    rg_ovl_unknown_clear();
    g_reports = 0;
    g_norder = 0;
    if (rg_ovl_bind(&t_reg) != 0) {
        fprintf(stderr, "bind failed\n");
        exit(2);
    }
}

static uint32_t w32(const unsigned char *p) { uint32_t v; memcpy(&v, p, 4); return v; }

static void t_data_restore(void)
{
    setup();
    memset(alpha_seg, 0xEE, sizeof alpha_seg);
    memset(beta_seg, 0xDD, sizeof beta_seg);
    CHECK(rg_ovl_load(0) == 0);
    CHECK(rg_ovl_current() == 0);
    CHECK(w32(alpha_seg) == 0xA0 && w32(alpha_seg + 56) == 0xAE);
    CHECK(w32(alpha_seg + 60) == (uint32_t)(uintptr_t)alpha_seg);   /* relocated word */
    CHECK(beta_seg[0] == 0xDD);                  /* the other module is not touched */
    alpha_seg[0] = 0x99;                         /* the game changes its data */
    CHECK(rg_ovl_load(1) == 0);
    CHECK(rg_ovl_current() == 1 && w32(beta_seg + 28) == 0xB7);
    CHECK(alpha_seg[0] == 0x99);                 /* separate segments: no clobber */
    CHECK(rg_ovl_load(0) == 0);
    CHECK(w32(alpha_seg) == (g_control ? 0x99u : 0xA0u));   /* reload restores .data */
    CHECK(rg_ovl_load_count(0) == 2 && rg_ovl_load_count(1) == 1 && rg_ovl_load_count(-1) == 3);
    CHECK(rg_ovl_load(5) == -1);
}

static void t_bss_ctors(void)
{
    setup();
    if (g_control)
        t_descs[0].ctors = alpha_ctors_rev;
    memset(alpha_seg, 0x77, sizeof alpha_seg);
    rg_ovl_load(0);
    CHECK(g_norder == 2 && g_order[0] == 1 && g_order[1] == 2);
    CHECK(g_seen_bss == 0);                      /* bss zero before the ctors */
    CHECK(g_seen_data == 0xA1);                  /* data restored before the ctors */
    CHECK(g_seen_cur == 0);                      /* active while its ctors run */
    CHECK(alpha_seg[64 + 4] == 0x55);            /* the ctor's bss write survives */
    CHECK(alpha_seg[64 + 31] == 0);
    rg_ovl_load(1);
    rg_ovl_load(0);                              /* every load runs the ctors again */
    CHECK(g_norder == 5 && g_order[2] == 10 && g_order[3] == 1 && g_order[4] == 2);
    t_descs[0].ctors = alpha_ctors;
}

static void t_import_dispatch(void)
{
    int (*fi)(int, int) = (int (*)(int, int))t_func_int;
    float (*ff)(float) = (float (*)(float))t_func_flt;
    quad (*fq)(int) = (quad (*)(int))t_func_quad;
    int (*fo)(void) = (int (*)(void))t_func_only;
    int (*fs)(void) = (int (*)(void))t_slot_alpha;
    quad q;
    setup();
    rg_ovl_set_fatal(0);
    CHECK(fo() == 0 && g_reports == 1 && g_last_kind == RG_OVL_REP_NOT_RESIDENT);
    rg_ovl_load(0);
    CHECK(fi(3, 4) == 304);
    CHECK(ff(1.5f) == 3.0f);
    q = fq(10);
    CHECK(q.a == 10 && q.d == 13);
    CHECK(fo() == 7);
    CHECK(fs() == 7 && g_reports == 1);
    rg_ovl_load(g_control ? 0 : 1);
    CHECK(fi(3, 4) == -304);
    CHECK(ff(1.5f) == 4.5f);
    q = fq(10);
    CHECK(q.a == -10 && q.d == -13);
    CHECK(fo() == 0 && g_last_kind == RG_OVL_REP_UNKNOWN_FN);
    CHECK(fs() == 7 && g_last_kind == RG_OVL_REP_DOMAIN);
    CHECK(rg_ovl_unknown_count() == 3);
    CHECK(rg_ovl_unknown_get(1) && rg_ovl_unknown_get(1)->name &&
          !strcmp(rg_ovl_unknown_get(1)->name, "func_only"));
    CHECK(rg_ovl_unknown_get(1) && rg_ovl_unknown_get(1)->addr == 0);
    rg_ovl_set_fatal(1);
}

static void t_bind(void)
{
    static rg_ovl_import bad_imp[1] = {{"func_x", 0x004E9F00u, -1, 0, imp_int}};
    static const rg_ovl_registry arena_reg = {t_descs, 2, (unsigned char *)alpha_seg, 0x004E9E80u, 0x100u, 0, 0, "x"};
    static const rg_ovl_registry addr_reg = {t_descs, 2, 0, 0, 0, bad_imp, 1, "x"};
    setup();
    CHECK(rg_ovl_find_file("cdrom0:\\BIN\\BETA.BIN;1") == 1);
    CHECK(rg_ovl_find_file("host0:BIN/alpha.bin") == 0);
    CHECK(rg_ovl_find_file("cdrom0:\\BIN\\GAMMA.BIN;1") == -1);
    CHECK(rg_ovl_find_index(3) == 1 && rg_ovl_find("ALPHA") == 0);
    CHECK(OverlayLoadFile_100410((int)(intptr_t)"cdrom1:\\BIN\\BETA.BIN;1", 0x1234) == 1);
    CHECK(rg_ovl_current() == (g_control ? 0 : 1));
    rg_ovl_set_report(on_report, NULL);
    CHECK(rg_ovl_bind(&arena_reg) == -1);
    CHECK(rg_ovl_bind(&addr_reg) == -1);
    rg_ovl_service_init((void *)&t_reg);
    CHECK(rg_ovl_bound() == &t_reg && rg_ovl_current() == -1);
}

/* trace_map.c (compiled into this test) over the module table: the active module's segment
 * sits at its retail data start = RG_TRACE_ARENA_BASE + 0x40 header + text_size (as the arena
 * manager's data_vram()); text and past-.bss are
 * unmapped; host pointers into any module's segment map back.  Control: text_size 0 (an
 * old-generator registry) -> no mapping. */
static void t_trace_map(void)
{
    static rg_ovl_desc d[2];
    static rg_ovl_registry reg;
    const uint32_t A = RG_TRACE_ARENA_BASE + RG_OVL_HDR_SIZE;    /* + text_size = data start */
    uint32_t av = 0, pa = 0, bad = 0;
    unsigned char buf[8];
    memcpy(d, t_descs, sizeof d);
    d[0].text_size = g_control ? 0 : 0x100;
    d[1].text_size = 0x80;
    reg = t_reg;
    reg.ovls = d;
    rg_ovl_set_report(on_report, NULL);
    CHECK(rg_ovl_bind(&reg) == 0);
    CHECK(rg_trace_host_ptr(A + 0x104, NULL) == NULL);          /* nothing loaded */
    CHECK(rg_ovl_load(0) == 0);
    CHECK(rg_trace_host_ptr(A + 0x104, &av) == alpha_seg + 4 && av == 96 - 4);
    CHECK(rg_trace_host_ptr(A + 0x100 + 64 + 31, NULL) == alpha_seg + 95);   /* last bss byte */
    CHECK(rg_trace_host_ptr(A + 0x100 + 96, NULL) == NULL);     /* past .bss */
    CHECK(rg_trace_host_ptr(A + 0x10, NULL) == NULL);           /* text range */
    CHECK(rg_trace_read(A + 0x100, buf, 8, &bad) == 0 && w32(buf) == 0xA0 && w32(buf + 4) == 0xA1);
    CHECK(rg_ovl_load(1) == 0);
    CHECK(rg_trace_host_ptr(A + 0x88, NULL) == beta_seg + 8);
    CHECK(rg_trace_host_ptr(A + 0x104, NULL) == NULL);         /* alpha's data: beta is active */
    CHECK(rg_trace_host_ptr(A + 0x80 + 96, NULL) == NULL);
    CHECK(rg_trace_ps2_addr(alpha_seg + 5, &pa) == 0 && pa == A + 0x105);   /* not active: still maps */
    CHECK(rg_trace_ps2_addr(beta_seg + 1, &pa) == 0 && pa == A + 0x81);
    CHECK(rg_trace_read(A + 0x80 + 90, buf, 8, &bad) == -1 && bad == A + 0x80 + 96);
}

int main(int argc, char **argv)
{
    const char *t = argc > 1 ? argv[1] : "";
    size_t n = strlen(t);
    char base[64];
    if (n > 8 && !strcmp(t + n - 8, "_control")) {
        g_control = 1;
        n -= 8;
    }
    if (n >= sizeof base)
        return 2;
    memcpy(base, t, n);
    base[n] = 0;
    if (!strcmp(base, "data_restore")) t_data_restore();
    else if (!strcmp(base, "bss_ctors")) t_bss_ctors();
    else if (!strcmp(base, "imports")) t_import_dispatch();
    else if (!strcmp(base, "bind")) t_bind();
    else if (!strcmp(base, "trace_map")) t_trace_map();
    else {
        fprintf(stderr, "unknown test %s\n", t);
        return 2;
    }
    if (!g_fail)
        printf("ok %s\n", t);
    return g_fail;
}
