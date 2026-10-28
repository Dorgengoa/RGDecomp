/* SPDX-License-Identifier: CC0-1.0
 * Overlay manager tests on SYNTHETIC overlays (docs/OVERLAY.md "Tests").
 *   rg-ovl-tests <name>      exit 0 = pass
 * Two arena-mode overlays share the arena and a function address; a third
 * uses object mode (overlay data as C objects).  `*_control` variants are
 * deliberately wrong and must FAIL (ctest WILL_FAIL). */
#include "ovl.h"
#include "ovl_asm.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef RG_OVL_TEST_BIND
#include "hwbus.h"
int OverlayLoadFile_100410(int path, int load);
void rg_ovl_service_init(void *user);
#endif

static int g_fail;
#define CHECK(c)                                                              \
    do {                                                                      \
        if (!(c)) {                                                           \
            fprintf(stderr, "%s:%d: CHECK failed: %s\n", __FILE__, __LINE__, #c); \
            g_fail = 1;                                                       \
        }                                                                     \
    } while (0)

/* ------------------------------------------------------------ fixtures */
#define BASE 0x004E9E80u
#define ARENA_SIZE 0x400u
/* the generated arena defines rg_ovl_arena; the synthetic tests use their own */
static unsigned char t_arena[ARENA_SIZE] __attribute__((aligned(128)));

/* alpha: text 0x100 (0x4E9EC0..0x4E9FC0), data 0x40 @0x4E9FC0, bss 0x20 @0x4EA000
 * beta:  text 0x80  (0x4E9EC0..0x4E9F40), data 0x80 @0x4E9F40, bss 0x40 @0x4E9FC0
 * -> beta's data covers alpha's text tail, beta's bss covers alpha's data. */
#define A_DATA 0x004E9FC0u
#define A_BSS 0x004EA000u
#define B_DATA 0x004E9F40u
#define B_BSS 0x004E9FC0u
#define SHARED_FN 0x004E9F00u

static char g_log[256];
static void logc(const char *s) { strncat(g_log, s, sizeof g_log - strlen(g_log) - 1); }

static uint32_t *arena32(uint32_t addr) { return (uint32_t *)(t_arena + (addr - BASE)); }

static int ctor_saw_pristine, ctor_saw_bss_zero, ctor_saw_current;
static void a_c1(void)
{
    logc("1");
    ctor_saw_pristine = (*arena32(A_DATA) == 0xA0A0A001u);
    ctor_saw_bss_zero = (*arena32(A_BSS) == 0);
    ctor_saw_current = rg_ovl_current();
    *arena32(A_BSS + 4) = 0xC7C7C7C7u;          /* ctors may initialise bss */
}
static void a_c2(void) { logc("2"); }
static void a_c3(void) { logc("3"); }
static void b_c1(void) { logc("b"); }

static int a_f1(int x) { return x + 1; }
static int a_f2(int x, int y) { return x * y; }
static int b_f1(int x) { return x + 100; }
static float a_ff(float x) { return x * 2.0f; }
static float b_ff(float x) { return x * 3.0f; }
typedef struct { int a, b, c, d; } big_t;   /* sret on i686 */
static big_t a_big(int x) { big_t r = {x, x + 1, x + 2, x + 3}; return r; }

static const uint32_t a_image[0x10] = {
    0xA0A0A001u, 0xA0A0A002u, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xA0A0A0FFu};
static const uint32_t b_image[0x20] = {0xB0B0B001u, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xB0B0B0FFu};

static const rg_ovl_fn a_ctors[] = {a_c1, a_c2, a_c3};
static const rg_ovl_fn a_ctors_rev[] = {a_c3, a_c2, a_c1};   /* control */
static const rg_ovl_fn b_ctors[] = {b_c1};
static const rg_ovl_func a_funcs[] = {
    {0x004E9EC0u, "alpha_ff", (rg_ovl_fn)a_ff},
    {SHARED_FN, "alpha_f1", (rg_ovl_fn)a_f1},
    {0x004E9F40u, "alpha_f2", (rg_ovl_fn)a_f2},
    {0x004E9F80u, "alpha_big", (rg_ovl_fn)a_big}};
static const rg_ovl_func b_funcs[] = {
    {0x004E9EC0u, "beta_ff", (rg_ovl_fn)b_ff},
    {SHARED_FN, "beta_f1", (rg_ovl_fn)b_f1}};
static const rg_ovl_label a_labels[] = {
    {A_DATA, "alpha_D_004E9FC0"}, {A_DATA + 0x3C, "alpha_D_004E9FFC"}, {A_BSS, "alpha_bss"}};
static const rg_ovl_label b_labels[] = {{B_DATA, "beta_D_004E9F40"}, {B_BSS, "beta_bss"}};

/* object mode: gamma's data as two C objects + a bss object */
static unsigned char g_obj1[8] = {1, 2, 3, 4, 5, 6, 7, 8};
static unsigned char g_obj2[4] = {9, 9, 9, 9};
static unsigned char g_bss[16];
static const rg_ovl_object c_objects[] = {
    {0x004E9F00u, 8, g_obj1, "gamma_D_004E9F00"},
    {0x004E9F08u, 4, g_obj2, "gamma_D_004E9F08"},
    {0x004E9F10u, 16, g_bss, "gamma_bss"}};

static rg_ovl_desc t_descs[3] = {
    {"alpha", "ALPHA.BIN", 4, 6, BASE, 0x100, 0x40, 0x20, 0x004E9FFCu, 0x004EA000u,
     a_image, NULL, 0, a_ctors, 3, NULL, 0, a_funcs, 4, a_labels, 3},
    {"beta", "BETA.BIN", 3, 5, BASE, 0x80, 0x80, 0x40, 0x004E9FB8u, 0x004E9FBCu,
     b_image, NULL, 0, b_ctors, 1, NULL, 0, b_funcs, 2, b_labels, 2},
    {"gamma", "GAMMA.BIN", 2, 2, BASE, 0x40, 0xC, 0x10, 0, 0,
     NULL, c_objects, 3, NULL, 0, NULL, 0, NULL, 0, NULL, 0},
};

/* imports: like the generated ones; func_4E9F00 is called by MAIN by address */
static const rg_ovl_import t_imports[] = {
    {"func_4E9F00", SHARED_FN, -1, 0},
    {"func_4E9EC0", 0x004E9EC0u, -1, 0},
    {"func_4E9F80", 0x004E9F80u, -1, 0},
    {"slot_4E9F40", 0x004E9F40u, 0, 1},       /* data slot attributed to alpha */
    {"func_4E9FA0", 0x004E9FA0u, -1, 0},      /* no function anywhere */
};
RG_OVL_TRAMPOLINE(func_4E9F00, t_imports, 0)
RG_OVL_TRAMPOLINE(func_4E9EC0, t_imports, 1)
RG_OVL_TRAMPOLINE(func_4E9F80, t_imports, 2)
RG_OVL_TRAMPOLINE(slot_4E9F40, t_imports, 3)
RG_OVL_TRAMPOLINE(func_4E9FA0, t_imports, 4)
/* how MAIN code declares them (any signature: the trampoline is transparent) */
int func_4E9F00_c(int) __asm__(RG_OVL_ASM_SYM(func_4E9F00));
float func_4E9EC0_c(float) __asm__(RG_OVL_ASM_SYM(func_4E9EC0));
big_t func_4E9F80_c(int) __asm__(RG_OVL_ASM_SYM(func_4E9F80));
int slot_4E9F40_c(int, int) __asm__(RG_OVL_ASM_SYM(slot_4E9F40));
int func_4E9FA0_c(int) __asm__(RG_OVL_ASM_SYM(func_4E9FA0));

static rg_ovl_registry t_reg = {t_descs, 3, t_arena, BASE, ARENA_SIZE, t_imports, 5, "synthetic"};

static int n_reports;
static void quiet_report(void *u, int kind, int ovl, uint32_t addr, const char *msg)
{
    (void)u; (void)kind; (void)ovl; (void)addr; (void)msg;
    n_reports++;
}

static void setup(void)
{
    memset(t_arena, 0x5A, sizeof t_arena);      /* "previous contents" */
    rg_ovl_set_report(quiet_report, NULL);
    rg_ovl_set_fatal(0);
    rg_ovl_unknown_clear();
    n_reports = 0;
    g_log[0] = 0;
    if (rg_ovl_bind(&t_reg) != 0) {
        fprintf(stderr, "bind failed\n");
        exit(2);
    }
}

/* ------------------------------------------------------------ tests */
static void t_data_restore(void)
{
    setup();
    CHECK(rg_ovl_current() == -1);
    CHECK(rg_ovl_load(0) == 0);
    CHECK(*arena32(A_DATA) == 0xA0A0A001u && *arena32(A_DATA + 0x3C) == 0xA0A0A0FFu);
    *arena32(A_DATA) = 0xDEADBEEFu;             /* the game mutates its data */
    CHECK(rg_ovl_load(1) == 0);                 /* switch: beta's data/bss overwrite */
    CHECK(*arena32(B_DATA) == 0xB0B0B001u);
    CHECK(*arena32(A_DATA) == 0);               /* = beta's bss now (zeroed) */
    CHECK(rg_ovl_load(0) == 0);                 /* back: pristine again */
    CHECK(*arena32(A_DATA) == 0xA0A0A001u);
    *arena32(A_DATA + 4) = 1;
    CHECK(rg_ovl_load(0) == 0);                 /* reloading the resident one resets it too */
    CHECK(*arena32(A_DATA + 4) == 0xA0A0A002u);
    CHECK(rg_ovl_load_count(0) == 3 && rg_ovl_load_count(1) == 1 && rg_ovl_load_count(-1) == 4);
    /* the header is in the arena, as on the PS2 */
    CHECK(memcmp(t_arena, "MWo3", 4) == 0 && t_arena[4] == 6 && strcmp((char *)t_arena + 0x20, "alpha.bin") == 0);
    CHECK(*(uint32_t *)(t_arena + 0x18) == 0x004E9FFCu && *(uint32_t *)(t_arena + 0x14) == 0x20);
    /* text range cleared (retail overwrites it with code) */
    CHECK(t_arena[0x40] == 0 && t_arena[0x13F] == 0);
    /* beyond the overlay's bss: untouched (retail leaves it) */
    CHECK(t_arena[A_BSS + 0x20 - BASE] == 0x5A);
    CHECK(rg_ovl_load(7) == -1);
}

static void t_bss_zero(void)
{
    setup();
    rg_ovl_load(0);
    CHECK(*arena32(A_BSS) == 0 && *arena32(A_BSS + 0x1C) == 0);
    CHECK(*arena32(A_BSS + 4) == 0xC7C7C7C7u);  /* written by a ctor after the zeroing */
    *arena32(A_BSS) = 0x11111111u;
    *arena32(A_BSS + 0x1C) = 0x22222222u;
    rg_ovl_load(0);
    CHECK(*arena32(A_BSS) == 0 && *arena32(A_BSS + 0x1C) == 0);
}

static void t_ctor_order(void)
{
    setup();
    rg_ovl_load(0);
    CHECK(strcmp(g_log, "123") == 0);
    CHECK(ctor_saw_pristine && ctor_saw_bss_zero);
    CHECK(ctor_saw_current == 0);               /* resident while its ctors run */
    rg_ovl_load(1);
    rg_ovl_load(0);
    CHECK(strcmp(g_log, "123b123") == 0);       /* every load runs them again */
}

static void t_ctor_order_control(void)
{
    t_descs[0].ctors = a_ctors_rev;             /* deliberately wrong table order */
    t_ctor_order();
    t_descs[0].ctors = a_ctors;
}

static void t_resolver_current(void)
{
    setup();
    CHECK(rg_ovl_resolve_fn(SHARED_FN) == NULL);    /* nothing resident yet */
    rg_ovl_load(0);
    CHECK(rg_ovl_resolve_fn(SHARED_FN) == (rg_ovl_fn)a_f1);
    CHECK(rg_ovl_resident_ptr(0, A_DATA + 8) == t_arena + (A_DATA + 8 - BASE));
    CHECK(rg_ovl_resident_ptr(1, B_DATA) == NULL);      /* beta not resident */
    CHECK(rg_ovl_resident_ptr(0, 0x004E9F00u) == NULL); /* text, not data/bss */
    CHECK(rg_ovl_hwbus_resolve(NULL, "alpha", "alpha_bss", A_BSS) == t_arena + (A_BSS - BASE));
    CHECK(rg_ovl_hwbus_resolve(NULL, "beta", "beta_bss", B_BSS) == NULL);
    rg_ovl_load(1);
    CHECK(rg_ovl_resolve_fn(SHARED_FN) == (rg_ovl_fn)b_f1);
    CHECK(rg_ovl_hwbus_resolve(NULL, "BETA", "beta_bss", B_BSS) == t_arena + (B_BSS - BASE));
    CHECK(rg_ovl_hwbus_resolve(NULL, "alpha", "alpha_bss", A_BSS) == NULL);
}

static void t_shared_address(void)
{
    setup();
    CHECK(rg_ovl_lookup_fn(0, SHARED_FN) == (rg_ovl_fn)a_f1);
    CHECK(rg_ovl_lookup_fn(1, SHARED_FN) == (rg_ovl_fn)b_f1);
    CHECK(strcmp(rg_ovl_fn_name(0, SHARED_FN), "alpha_f1") == 0);
    CHECK(strcmp(rg_ovl_fn_name(1, SHARED_FN), "beta_f1") == 0);
    /* MAIN's call by address goes to whichever overlay is resident */
    rg_ovl_load(0);
    CHECK(func_4E9F00_c(41) == 42);
    CHECK(func_4E9EC0_c(1.5f) == 3.0f);         /* float arg + x87 return pass through */
    {
        big_t b = func_4E9F80_c(7);             /* struct return (hidden pointer) */
        CHECK(b.a == 7 && b.b == 8 && b.c == 9 && b.d == 10);
    }
    CHECK(slot_4E9F40_c(6, 7) == 42);           /* two stack args */
    rg_ovl_load(1);
    CHECK(func_4E9F00_c(41) == 141);
    CHECK(func_4E9EC0_c(1.5f) == 4.5f);
    CHECK(rg_ovl_unknown_count() == 0);
}

static void t_shared_address_control(void)
{
    setup();
    rg_ovl_load(1);
    CHECK(func_4E9F00_c(41) == 42);             /* wrong: alpha's answer with beta resident */
}

static void t_unknown(void)
{
    const rg_ovl_unknown *u;
    setup();
    CHECK(func_4E9F00_c(1) == 0);               /* before any load: stub, reported */
    u = rg_ovl_unknown_get(0);
    CHECK(u && u->kind == RG_OVL_REP_NOT_RESIDENT && u->addr == SHARED_FN && strcmp(u->name, "func_4E9F00") == 0);
    rg_ovl_load(0);
    CHECK(func_4E9FA0_c(5) == 0);               /* no such entry */
    CHECK(func_4E9FA0_c(5) == 0);
    u = rg_ovl_unknown_get(1);
    CHECK(u && u->kind == RG_OVL_REP_UNKNOWN_FN && u->ovl == 0 && u->addr == 0x004E9FA0u && u->count == 2);
    CHECK(rg_ovl_resolve_fn(0x004E9F04u) == NULL);  /* inside a function, not an entry */
    u = rg_ovl_unknown_get(2);
    CHECK(u && u->kind == RG_OVL_REP_UNKNOWN_FN && u->addr == 0x004E9F04u);
    rg_ovl_load(1);
    CHECK(slot_4E9F40_c(6, 7) == 0);            /* alpha-only slot with beta resident */
    CHECK(rg_ovl_unknown_count() == 5);         /* DOMAIN + UNKNOWN_FN for the slot */
    CHECK(rg_ovl_unknown_get(3)->kind == RG_OVL_REP_DOMAIN);
    CHECK(n_reports == 5);                      /* hook called once per distinct record */
    CHECK(rg_ovl_hwbus_resolve(NULL, "nosuch", "x", 0x004E9F00u) == NULL);
}

static void t_address_map(void)
{
    uint32_t off = 0;
    setup();
    CHECK(rg_ovl_host_ptr(BASE) == t_arena);
    CHECK(rg_ovl_host_ptr(BASE + ARENA_SIZE - 1) == t_arena + ARENA_SIZE - 1);
    CHECK(rg_ovl_host_ptr(BASE + ARENA_SIZE) == NULL && rg_ovl_host_ptr(BASE - 1) == NULL);
    CHECK(rg_ovl_ps2_addr(t_arena + 0x123) == BASE + 0x123);
    CHECK(rg_ovl_ps2_addr(&off) == 0);
    CHECK(strcmp(rg_ovl_label_at(0, A_DATA + 8, &off), "alpha_D_004E9FC0") == 0 && off == 8);
    CHECK(strcmp(rg_ovl_label_at(0, A_DATA + 0x3C, &off), "alpha_D_004E9FFC") == 0 && off == 0);
    CHECK(strcmp(rg_ovl_label_at(1, B_BSS + 2, &off), "beta_bss") == 0 && off == 2);
    CHECK(rg_ovl_label_at(0, 0x004E9E80u, &off) == NULL);
    CHECK(rg_ovl_find("Beta") == 1 && rg_ovl_find("nosuch") == -1);
    CHECK(rg_ovl_find_index(4) == 0 && rg_ovl_find_index(9) == -1);
    CHECK(rg_ovl_find_file("cdrom0:\\BIN\\ALPHA.BIN;1") == 0);
    CHECK(rg_ovl_find_file("cdrom1:\\BIN\\BETA.BIN;1") == 1);
    CHECK(rg_ovl_find_file("host0:BIN/beta.bin") == 1);
    CHECK(rg_ovl_find_file("cdrom0:\\BIN\\VIEWER.BIN;1") == -1);
}

static void t_object_mode(void)
{
    setup();
    rg_ovl_load(2);
    CHECK(g_obj1[0] == 1 && g_obj2[3] == 9 && g_bss[0] == 0);
    g_obj1[0] = 77;
    g_obj2[3] = 77;
    g_bss[15] = 77;
    rg_ovl_load(0);
    rg_ovl_load(2);
    CHECK(g_obj1[0] == 1 && g_obj2[3] == 9 && g_bss[15] == 0);
    CHECK(rg_ovl_resident_ptr(2, 0x004E9F0Au) == g_obj2 + 2);
    CHECK(rg_ovl_resident_ptr(2, 0x004E9F12u) == g_bss + 2);
    CHECK(rg_ovl_ps2_addr(g_obj1 + 3) == 0x004E9F03u);
}

static void t_bind_validation(void)
{
    rg_ovl_func bad[2] = {{0x004E9F00u, "x", NULL}, {0x004E9EC0u, "y", NULL}};
    rg_ovl_desc d = t_descs[1];
    rg_ovl_registry r = t_reg;
    setup();
    d.funcs = bad;
    d.nfuncs = 2;
    r.ovls = &d;
    r.novls = 1;
    CHECK(rg_ovl_bind(&r) == -1);               /* unsorted */
    d = t_descs[0];
    d.bss_size = 0x1000;                        /* larger than the arena */
    CHECK(rg_ovl_bind(&r) == -1);
    CHECK(rg_ovl_bind(&t_reg) == 0);
}

#ifdef RG_OVL_TEST_BIND
/* hwbus's RG_OVL_DATA backing + the OverlayLoadFile binding */
static void t_bind_hwbus(void)
{
    uint64_t before;
    setup();
    t_reg.arena = t_arena;
    rg_ovl_service_init(&t_reg);
    rg_ovl_set_report(quiet_report, NULL);
    rg_ovl_set_fatal(0);
    CHECK(OverlayLoadFile_100410((int)(intptr_t)"cdrom0:\\BIN\\ALPHA.BIN;1", (int)(intptr_t)t_arena) == 1);
    CHECK(rg_ovl_current() == 0 && strcmp(g_log, "123") == 0);
    /* RG_OVL_DATA(u32, alpha, alpha_D_004E9FC0, 0x4E9FC0, 4) */
    *(uint32_t *)rg_ovl_data_ptr("alpha", "alpha_D_004E9FC0", A_DATA, 4) = 0x12345678u;
    CHECK(*arena32(A_DATA + 4) == 0x12345678u);
    before = hwbus_ovl_unresolved();
    CHECK(OverlayLoadFile_100410((int)(intptr_t)"host0:BIN/BETA.BIN", (int)(intptr_t)t_arena) == 1);
    (void)rg_ovl_data_ptr("alpha", "alpha_D_004E9FC0", A_DATA, 4);   /* not resident */
    CHECK(hwbus_ovl_unresolved() == before + 1);
    /* OverlayLoad_1c3210 passing D_0044AF90's raw retail string address:
     * row cdrom1: (1), loader index 4 = alpha */
    CHECK(OverlayLoadFile_100410((int)(0x0045AD30u + 0x20u * (7 + 4)), (int)(intptr_t)t_arena) == 1);
    CHECK(rg_ovl_current() == 0);
}
#endif

/* ------------------------------------------------------------ main */
static const struct { const char *name; void (*fn)(void); } TESTS[] = {
    {"data_restore", t_data_restore},
    {"bss_zero", t_bss_zero},
    {"ctor_order", t_ctor_order},
    {"ctor_order_control", t_ctor_order_control},
    {"resolver_current", t_resolver_current},
    {"shared_address", t_shared_address},
    {"shared_address_control", t_shared_address_control},
    {"unknown", t_unknown},
    {"address_map", t_address_map},
    {"object_mode", t_object_mode},
    {"bind_validation", t_bind_validation},
#ifdef RG_OVL_TEST_BIND
    {"bind_hwbus", t_bind_hwbus},
#endif
};

int main(int argc, char **argv)
{
    size_t i;
    if (argc != 2) {
        fprintf(stderr, "usage: rg-ovl-tests <test>\n");
        return 2;
    }
    for (i = 0; i < sizeof TESTS / sizeof TESTS[0]; i++)
        if (strcmp(argv[1], TESTS[i].name) == 0) {
            TESTS[i].fn();
            printf("%s: %s\n", argv[1], g_fail ? "FAIL" : "PASS");
            return g_fail;
        }
    fprintf(stderr, "unknown test %s\n", argv[1]);
    return 2;
}
