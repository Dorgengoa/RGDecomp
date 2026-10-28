/* SPDX-License-Identifier: CC0-1.0
 * Tests over the REAL generated registry (tools/gen_overlay_registry.py at the
 * pinned snapshot), compiled RG_OVL_TABLE_ONLY (no game symbols: function
 * pointers are 0, data words are the raw retail words), plus the generated
 * arena (label offsets).  docs/OVERLAY.md "Tests".
 *   rg-ovl-real-tests <name>     (real_registry | real_registry_control | arena | bin_data)
 * bin_data compares each overlay's pristine .data with the retail .BIN when
 * RG_OVL_BIN_DIR (compile-time) or $RG_DATA/BIN has them; else exit 77 (skip). */
#include "ovl.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern const rg_ovl_registry rg_ovl_generated_registry;

static int g_fail;
#define CHECK(c)                                                              \
    do {                                                                      \
        if (!(c)) {                                                           \
            fprintf(stderr, "%s:%d: CHECK failed: %s\n", __FILE__, __LINE__, #c); \
            g_fail = 1;                                                       \
        }                                                                     \
    } while (0)

/* Retail MWo3 headers (data/BIN/<OV>.BIN +0x04..+0x1F) and the decomp's counts:
 * functions = C units per overlay (game/MANIFEST.tsv), i.e. symbols.txt
 * entries minus the 0x40 nop pad `<ov>_entry` (and TITLE's ten jump-table
 * case labels inside TitleOptionsCursorMoveCb). */
static const struct {
    const char *name;
    int index;
    uint32_t id, text, data, bss, ctor, dtor;
    int nctors, nfuncs;
} EXPECT[5] = {
    /* title: 96 symbols.txt entries + 3 C-only entries (title_FUN_004e9ff0/
     * 4eaa80/4eab00, gen_overlay_registry.py; docs/BRINGUP.md) */
    {"title", 2, 2, 0x7540, 0x500, 0x280, 0x004F18A0, 0x004F18B0, 4, 99},
    {"insmenu", 6, 3, 0xF8C0, 0xA00, 0x180, 0x004FA140, 0x004FA148, 2, 364},
    {"normal", 3, 5, 0x3AE40, 0x2300, 0x1200, 0x00526F60, 0x00526FA4, 17, 658},
    {"factory", 4, 6, 0x215C0, 0x4880, 0xF00, 0x0050FC50, 0x0050FCA8, 22, 408},
    {"insect", 5, 7, 0x39C40, 0x2300, 0x280, 0x00525D60, 0x00525DA4, 17, 743},
};

static const char *nm(const char *s) { return s ? s : ""; }

static const rg_ovl_import *find_import(const rg_ovl_registry *r, const char *name)
{
    int i;
    for (i = 0; i < r->nimports; i++)
        if (strcmp(r->imports[i].name, name) == 0)
            return &r->imports[i];
    return NULL;
}

static void check_registry(const rg_ovl_registry *r)
{
    int i, k, ncall = 0, nslot = 0;
    CHECK(rg_ovl_bind(r) == 0);
    CHECK(r->novls == 5 && r->arena_base == 0x004E9E80u && r->arena_size == 0x3E380u);
    for (i = 0; i < 5 && i < r->novls; i++) {
        const rg_ovl_desc *d = &r->ovls[i];
        CHECK(strcmp(d->name, EXPECT[i].name) == 0);
        CHECK(d->index == EXPECT[i].index && d->id == EXPECT[i].id);
        CHECK(d->text_size == EXPECT[i].text && d->data_size == EXPECT[i].data && d->bss_size == EXPECT[i].bss);
        CHECK(d->ctor_start == EXPECT[i].ctor && d->dtor_start == EXPECT[i].dtor);
        CHECK(d->nctors == EXPECT[i].nctors && (d->dtor_start - d->ctor_start) / 4 == (uint32_t)d->nctors);
        CHECK(d->ndtors == 0);
        CHECK(d->nfuncs == EXPECT[i].nfuncs);
        CHECK(d->data_image != NULL);
        for (k = 0; k < d->nfuncs; k++) {
            CHECK(d->funcs[k].addr >= 0x004E9F00u && d->funcs[k].addr < d->load + 0x40 + d->text_size);
            CHECK(strncmp(d->funcs[k].name, d->name, strlen(d->name)) == 0 ||
                  strncmp(d->funcs[k].name, "func_", 5) == 0);
        }
        /* the .ctors table in the pristine image points at the lifted ctors' retail addresses */
        {
            uint32_t off = (d->ctor_start - (d->load + 0x40 + d->text_size)) / 4;
            CHECK(d->data_image[off] >= d->load && d->data_image[off] < d->ctor_start);
            CHECK(d->data_image[off + d->nctors] == 0);     /* the empty .dtors list */
        }
    }
    CHECK(rg_ovl_find_index(2) == 0 && rg_ovl_find_index(3) == 2 && rg_ovl_find_index(6) == 1);
    CHECK(rg_ovl_find_file("cdrom0:\\BIN\\NORMAL.BIN;1") == 2);
    CHECK(rg_ovl_find_file("cdrom1:\\BIN\\INSECT.BIN;1") == 4);
    CHECK(rg_ovl_find_file("cdrom0:\\BIN\\LAUNCHER.BIN;1") == -1);   /* stubs: not registered */

    /* every MAIN -> overlay import names a function entry */
    for (i = 0; i < r->nimports; i++) {
        const rg_ovl_import *im = &r->imports[i];
        int hits = 0;
        if (im->kind == 1) {
            nslot++;
            CHECK(im->domain >= 0 && rg_ovl_fn_name(im->domain, im->addr) != NULL);
        } else {
            ncall++;
            CHECK(im->domain == -1);
        }
        for (k = 0; k < r->novls; k++)
            hits += rg_ovl_fn_name(k, im->addr) != NULL;
        CHECK(hits >= 1);
    }
    /* 2efa6b43 + data2c d784320c: 206 call names + 66 data2c slot names.
     * Interim snapshot b09ccfa1 (data C in the snapshot, docs/LINK.md): the
     * data2c slots are the overlays' own names (static bindings, no import)
     * and the datareloc stage adds the func_<ADDR> imports of raw arena words
     * whose address is a function in several overlays: >= 206 calls. */
    CHECK(ncall >= 206 && (nslot == 66 || nslot == 0));
    /* MainLoop's mode tables: D_0047E230/38/40[1] are TITLE's session init/step/exit;
     * 0x004F0820 is a different function in INSECT */
    CHECK(strcmp(nm(rg_ovl_fn_name(0, 0x004F0CB0u)), "title_TitleSessionInit_4f0cb0") == 0);
    CHECK(strcmp(nm(rg_ovl_fn_name(0, 0x004F0820u)), "title_TitleSessionShutdown_4f0820") == 0);
    CHECK(strcmp(nm(rg_ovl_fn_name(4, 0x004F0820u)), "insect_InsectBattleCalcWinStats_4f0820") == 0);
    if (nslot) {
        const rg_ovl_import *a = find_import(r, "title_FUN_004f0cb0");
        CHECK(a && a->domain == 0 && a->addr == 0x004F0CB0u);
    }
    /* MAIN's direct NORMAL calls (FieldHud* wrappers) */
    {
        const rg_ovl_import *c = find_import(r, "func_4F6AB0");
        CHECK(c && c->addr == 0x004F6AB0u && rg_ovl_fn_name(2, c->addr) != NULL);
    }
    /* resident-overlay resolution (table mode: names, the arena is not linked) */
    CHECK(rg_ovl_load(0) == 0 && rg_ovl_current() == 0);
    CHECK(rg_ovl_resident_ptr(2, 0x00527020u) == NULL);   /* NORMAL not resident */
    CHECK(rg_ovl_load(2) == 0 && rg_ovl_current() == 2);
    {
        uint32_t off = 0;
        const char *l = rg_ovl_label_at(2, 0x005273C2u, &off);
        CHECK(l && strcmp(l, "normal_D_00527020") == 0 && off == 0x3A2);   /* the ally-suggest state */
        l = rg_ovl_label_at(2, 0x00527020u, &off);
        CHECK(l && strcmp(l, "normal_D_00527020") == 0 && off == 0);
    }
}

static void t_real_registry(void)
{
    check_registry(&rg_ovl_generated_registry);
}

/* deliberately wrong: one function entry moved by 4 bytes -> must FAIL */
static void t_real_registry_control(void)
{
    static rg_ovl_desc descs[5];
    static rg_ovl_func funcs[4096];
    rg_ovl_registry r = rg_ovl_generated_registry;
    const rg_ovl_desc *t = &r.ovls[0];
    int k;
    memcpy(descs, r.ovls, sizeof descs);
    for (k = 0; k < t->nfuncs && k < 4096; k++) {
        funcs[k] = t->funcs[k];
        if (funcs[k].addr == 0x004F0CB0u)
            funcs[k].addr = 0x004F0CB4u;        /* TitleSessionInit, off by one insn */
    }
    descs[0].funcs = funcs;
    r.ovls = descs;
    check_registry(&r);
}

#ifdef RG_OVL_TEST_ARENA
extern unsigned char rg_ovl_arena[], rg_ovl_arena_end[];
extern unsigned char title_D_004F1400[], title_bss[], normal_D_00527020[], normal_D_00524D08[];
extern unsigned char insect_D_00524D08[], D_00527020[], D_005273B8[], D_00528200[];
extern unsigned char data2c_overlay_load_base[], factory_D_00510010[];
static void t_arena(void)
{
    unsigned char *a = rg_ovl_arena;
    CHECK(((uintptr_t)a & 127) == 0);
    CHECK(rg_ovl_arena_end - a == 0x3E380);
    CHECK(title_D_004F1400 - a == 0x004F1400 - 0x004E9E80);
    CHECK(title_bss - a == 0x004F1900 - 0x004E9E80);
    CHECK(normal_D_00527020 - a == 0x00527020 - 0x004E9E80);
    /* MAIN's names alias NORMAL's bss; the arena end is retail's heap start */
    CHECK(D_00527020 == normal_D_00527020 && D_005273B8 - a == 0x005273B8 - 0x004E9E80);
    CHECK(D_00528200 == rg_ovl_arena_end && data2c_overlay_load_base == a);
    /* the NORMAL/INSECT name collision is gone: same address, two names, one byte */
    CHECK(normal_D_00524D08 == insect_D_00524D08);
    CHECK(factory_D_00510010 - a == 0x00510010 - 0x004E9E80);
    /* arena-mode load through the real descriptors, with the linked arena */
    {
        rg_ovl_registry r = rg_ovl_generated_registry;
        const rg_ovl_desc *n;
        r.arena = a;
        CHECK(rg_ovl_bind(&r) == 0);
        CHECK(rg_ovl_load(2) == 0);
        n = rg_ovl_desc_at(2);
        CHECK(memcmp(a, "MWo3", 4) == 0 && strcmp((char *)a + 0x20, "normal.bin") == 0);
        CHECK(memcmp(a + (0x00524D00 - 0x004E9E80), n->data_image, n->data_size) == 0);
        CHECK(rg_ovl_resident_ptr(2, 0x005273C2u) == D_00527020 + 0x3A2);
        CHECK(rg_ovl_hwbus_resolve(NULL, "normal", "D_00527020", 0x00527020u) == D_00527020);
        normal_D_00527020[0x3AE] = 1;           /* FieldHudInitOnce's store */
        CHECK(rg_ovl_load(4) == 0 && rg_ovl_load(2) == 0);
        CHECK(normal_D_00527020[0x3AE] == 0);   /* bss zeroed on reload */
    }
}
#endif

static void t_bin_data(void)
{
    static const char *files[5] = {"TITLE.BIN", "INSMENU.BIN", "NORMAL.BIN", "FACTORY.BIN", "INSECT.BIN"};
    char dir[512], path[600];
    const rg_ovl_registry *r = &rg_ovl_generated_registry;
    int i, found = 0;
#ifdef RG_OVL_BIN_DIR
    snprintf(dir, sizeof dir, "%s", RG_OVL_BIN_DIR);
#else
    dir[0] = 0;
#endif
    if (getenv("RG_DATA"))
        snprintf(dir, sizeof dir, "%s/BIN", getenv("RG_DATA"));
    for (i = 0; i < 5; i++) {
        const rg_ovl_desc *d = &r->ovls[i];
        FILE *f;
        unsigned char *b;
        long n;
        snprintf(path, sizeof path, "%s/%s", dir, files[i]);
        f = fopen(path, "rb");
        if (!f)
            continue;
        found++;
        fseek(f, 0, SEEK_END);
        n = ftell(f);
        fseek(f, 0, SEEK_SET);
        b = (unsigned char *)malloc((size_t)n);
        CHECK(fread(b, 1, (size_t)n, f) == (size_t)n);
        fclose(f);
        CHECK((uint32_t)n == 0x40 + d->text_size + d->data_size);
        /* table mode: the pristine image is the raw retail .data, byte for byte */
        CHECK(memcmp(b + 0x40 + d->text_size, d->data_image, d->data_size) == 0);
        CHECK(*(uint32_t *)(b + 0x14) == d->bss_size && *(uint32_t *)(b + 0x18) == d->ctor_start);
        free(b);
    }
    if (!found) {
        printf("bin_data: no retail BINs under %s -- SKIP\n", dir);
        exit(77);
    }
}

int main(int argc, char **argv)
{
    static const struct { const char *n; void (*f)(void); } T[] = {
        {"real_registry", t_real_registry},
        {"real_registry_control", t_real_registry_control},
#ifdef RG_OVL_TEST_ARENA
        {"arena", t_arena},
#endif
        {"bin_data", t_bin_data},
    };
    size_t i;
    if (argc != 2)
        return 2;
    rg_ovl_set_fatal(0);
    for (i = 0; i < sizeof T / sizeof T[0]; i++)
        if (strcmp(argv[1], T[i].n) == 0) {
            T[i].f();
            printf("%s: %s\n", argv[1], g_fail ? "FAIL" : "PASS");
            return g_fail;
        }
    return 2;
}
