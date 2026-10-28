/* SPDX-License-Identifier: CC0-1.0
 * rg-trace-tests: unit tests for src/trace (docs/TRACE-PORT.md "Tests").
 *
 *   rg-trace-tests hash                         print "<len> <hex>" per fixed buffer (xcheck.py)
 *   rg-trace-tests image <regions> <out.tsv> <image.bin>
 *                                               PCSX2-semantics run over a synthetic
 *                                               32 MB EE image (xcheck.py re-derives it)
 *   rg-trace-tests deref <tmpdir>               host pointers, slots, map, notes
 *   rg-trace-tests parse <tmpdir>               region/portcfg grammar
 *   rg-trace-tests symtab                       generated table (gen_port_symtab.py)
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rg_trace.h"

static int g_fail;
#define CHECK(c)                                                              \
    do {                                                                      \
        if (!(c)) {                                                           \
            fprintf(stderr, "%s:%d: CHECK failed: %s\n", __FILE__, __LINE__, #c); \
            g_fail = 1;                                                       \
        }                                                                     \
    } while (0)

/* ---------------------------------------------------------------- hash */
static int t_hash(void)
{
    static const size_t lens[] = {0, 1, 3, 63, 64, 127, 128, 129, 255, 256, 257, 1000, 4096, 0xB570, 0x100000};
    static uint8_t buf[0x100000];
    for (size_t i = 0; i < sizeof buf; i++)
        buf[i] = (uint8_t)(i * 131u + 7u + (i >> 9));
    char hx[17];
    for (size_t k = 0; k < sizeof lens / sizeof lens[0]; k++) {
        rg_trace_hash_hex(hx, buf, lens[k]);
        printf("%u\t%s\n", (unsigned)lens[k], hx);
    }
    rg_trace_hash_hex(hx, "ptr:00000000", 12);
    printf("ptr:00000000\t%s\n", hx);
    return 0;
}

/* ---------------------------------------------------------------- image */
static uint32_t g_x = 0x9E3779B9u;
static uint32_t xs(void)
{
    g_x ^= g_x << 13;
    g_x ^= g_x >> 17;
    g_x ^= g_x << 5;
    return g_x;
}

static void put32(uint8_t *p, uint32_t v)
{
    p[0] = (uint8_t)v;
    p[1] = (uint8_t)(v >> 8);
    p[2] = (uint8_t)(v >> 16);
    p[3] = (uint8_t)(v >> 24);
}

static int t_image(const char *regions, const char *out, const char *img)
{
    uint8_t *ee = (uint8_t *)malloc(RG_TRACE_EE_RAM_SIZE);
    if (!ee)
        return 1;
    for (uint32_t i = 0; i < RG_TRACE_EE_RAM_SIZE; i += 4)
        put32(ee + i, (i & 0x3000) != 0x3000 ? xs() : 0); /* zero stretches too */
    put32(ee + RG_TRACE_GAME_VBL_ADDR, 4242);
    put32(ee + 0x00449858, 0x00480000);   /* deref +0xA8 (RandState-like) */
    put32(ee + 0x00483820, 0);            /* null */
    put32(ee + 0x00483824, 0x01FFFFF0);   /* runs past RAM -> marker */
    put32(ee + 0x00483828, 0x80480010);   /* kseg0: masked */
    put32(ee + 0x0048382C, 0x01FFFF00);   /* fits exactly at the end */
    FILE *f = fopen(img, "wb");
    if (!f || fwrite(ee, 1, RG_TRACE_EE_RAM_SIZE, f) != RG_TRACE_EE_RAM_SIZE) {
        fprintf(stderr, "cannot write %s\n", img);
        return 1;
    }
    fclose(f);
    rg_trace_clear_symbols();
    rg_trace_set_arena(NULL, 0, 0);
    rg_trace_set_ram(ee, 0, RG_TRACE_EE_RAM_SIZE);
    rg_trace_config c;
    rg_trace_default_config(&c);
    c.out = out;
    c.regions = regions;
    c.ps2_pointers = 1;
    if (rg_trace_open(&c) != 0)
        return 1;
    rg_trace_sample(120, 0x2328fa47u, 7);
    rg_trace_close("image test");
    const rg_trace_stats *st = rg_trace_get_stats();
    CHECK(st->vbl_from_game == 1 && st->last_vbl == 4242 && st->emitted == 1);
    rg_trace_set_ram(NULL, 0, 0);
    free(ee);
    return g_fail;
}

/* ---------------------------------------------------------------- deref */
static uint8_t objA[64];
static void *ptrs[4];
static void *ptrs2[2];
static uint8_t arena[0x1000];

static void expect_bytes(rg_trace_regions *rs, const char *name, const void *want, int n, int note)
{
    rg_trace_region *g = rg_trace_region_find(rs, name);
    CHECK(g != NULL);
    if (!g)
        return;
    uint8_t buf[256];
    char why[160];
    int untr = 0;
    int got = rg_trace_region_bytes(g, 0, buf, sizeof buf, why, sizeof why, &untr);
    if (got != n || (n >= 0 && memcmp(buf, want, (size_t)n)) || (note != (why[0] != 0))) {
        fprintf(stderr, "region %s: got %d bytes (want %d), why='%s'\n", name, got, n, why);
        g_fail = 1;
    }
}

static int write_file(const char *path, const char *text)
{
    FILE *f = fopen(path, "w");
    if (!f)
        return -1;
    fputs(text, f);
    fclose(f);
    return 0;
}

static int t_deref(const char *dir)
{
    char rpath[512], cpath[512], tpath[512];
    snprintf(rpath, sizeof rpath, "%s/deref_regions.cfg", dir);
    snprintf(cpath, sizeof cpath, "%s/deref_port.cfg", dir);
    snprintf(tpath, sizeof tpath, "%s/deref.tsv", dir);
    write_file(rpath,
               "ee sym:A      0x00400000 0x00400040\n"
               "ee sym:Ptrs   0x00400100 0x00400110\n"
               "ee sym:ViaA   *0x00400100+4 8\n"
               "ee sym:Null   *0x00400104 4\n"
               "ee sym:Heap   *0x00400108 16\n"
               "ee sym:Bogus  *0x0040010C 4\n"
               "ee sym:Span   0x0040003C 0x00400104   # crosses the gap after A\n"
               "ee sym:Arena  0x004E9E80 0x004E9E90\n"
               "ee sym:Raw    *0x00400200 8\n"
               "ee sym:Ps2    *0x00400204 4\n"
               "iop iop       0 0x200000\n");
    write_file(cpath, "ptrs sym:Ptrs 0,4 8 ,12\nps2ptr sym:Ps2\nexclude ^iop$ never\n");

    uint8_t *ram = (uint8_t *)calloc(1, RG_TRACE_EE_RAM_SIZE);
    static uint8_t outside[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    for (int i = 0; i < 64; i++)
        objA[i] = (uint8_t)(i * 3 + 1);
    for (int i = 0; i < 16; i++)
        ram[0x00600000 + i] = (uint8_t)(0xC0 + i);
    for (int i = 0; i < 16; i++)
        arena[i] = (uint8_t)(0x50 + i);
    ptrs[0] = objA + 8;
    ptrs[1] = NULL;
    ptrs[2] = ram + 0x00600000;
    ptrs[3] = (void *)(uintptr_t)0x12; /* not a mapped host page */
    ptrs2[0] = outside;                /* readable, outside the map */
    ptrs2[1] = (void *)(uintptr_t)0x00600000; /* a PS2 address value (ps2ptr) */

    rg_trace_clear_symbols();
    CHECK(rg_trace_add_symbol(0x00400000, sizeof objA, objA, "objA") == 0);
    CHECK(rg_trace_add_symbol(0x00400100, (uint32_t)sizeof ptrs, ptrs, "ptrs") == 0);
    CHECK(rg_trace_add_symbol(0x00400200, (uint32_t)sizeof ptrs2, ptrs2, "ptrs2") == 0);
    CHECK(rg_trace_add_symbol(0x00400020, 4, objA, "overlap") != 0); /* overlaps objA: refused */
    CHECK(rg_trace_symbol_count() == 3);
    rg_trace_set_ram(ram, RG_TRACE_HEAP_START, RG_TRACE_EE_RAM_SIZE);
    rg_trace_set_arena(arena, RG_TRACE_ARENA_BASE, sizeof arena);

    /* forward / reverse map */
    uint32_t pa = 0;
    CHECK(rg_trace_host_ptr(0x00400010, NULL) == objA + 0x10);
    CHECK(rg_trace_host_ptr(0x00400040, NULL) == NULL);         /* gap */
    CHECK(rg_trace_host_ptr(0x00100000, NULL) == NULL);         /* below the RAM window */
    CHECK(rg_trace_host_ptr(0x00600004, NULL) == ram + 0x00600004);
    CHECK(rg_trace_host_ptr(0x004E9E84, NULL) == arena + 4);
    CHECK(rg_trace_ps2_addr(objA + 5, &pa) == 0 && pa == 0x00400005);
    CHECK(rg_trace_ps2_addr(arena + 8, &pa) == 0 && pa == 0x004E9E88);
    CHECK(rg_trace_ps2_addr(ram + 0x01000000, &pa) == 0 && pa == 0x01000000);
    CHECK(rg_trace_ps2_addr(ram + 0x00100000, &pa) != 0);       /* RAM below the window */
    CHECK(rg_trace_ps2_addr(outside, &pa) != 0);

    rg_trace_regions rs = {0};
    char err[256];
    CHECK(rg_trace_regions_load(&rs, rpath, err, sizeof err) == 0);
    CHECK(rg_trace_portcfg_load(&rs, cpath, err, sizeof err) == 0);
    rg_trace_region *pr = rg_trace_region_find(&rs, "sym:Ptrs");
    CHECK(pr && pr->nslots == 4 && pr->slots[3] == 12);

    uint8_t want[16];
    expect_bytes(&rs, "sym:A", objA, 64, 0);
    if (sizeof(void *) == 4) {
        /* slots: objA+8 -> 0x00400008, NULL stays 0, heap -> 0x00600000, 0x12 untranslated */
        put32(want, 0x00400008);
        put32(want + 4, 0);
        put32(want + 8, 0x00600000);
        put32(want + 12, 0x12);
        expect_bytes(&rs, "sym:Ptrs", want, 16, 0);
        expect_bytes(&rs, "sym:ViaA", objA + 12, 8, 0);
        expect_bytes(&rs, "sym:Null", "ptr:00000000", 12, 0);
        expect_bytes(&rs, "sym:Heap", ram + 0x00600000, 16, 0);
        expect_bytes(&rs, "sym:Bogus", "ptr:?00000012", 13, 0);
        expect_bytes(&rs, "sym:Raw", outside, 8, 1); /* read raw, with a note */
#ifndef _WIN32
        (void)outside;
#endif
    }
    expect_bytes(&rs, "sym:Span", NULL, -1, 1);
    expect_bytes(&rs, "sym:Arena", arena, 16, 0);
    expect_bytes(&rs, "sym:Ps2", ram + 0x00600000, 4, 0);
    expect_bytes(&rs, "iop", NULL, -1, 1);

    /* the same through the recorder: notes + rows */
    rg_trace_config c;
    rg_trace_default_config(&c);
    c.out = tpath;
    c.regions = rpath;
    c.portcfg = cpath;
    c.vbl_addr = 0x00400000; /* objA[0..3] as the counter */
    c.stop_vbl = 1;          /* objA's first word is far above 1: stops at once */
    CHECK(rg_trace_open(&c) == 0);
    CHECK(rg_trace_sample(5, 0x1234, 5) == 1); /* stop-vbl reached */
    CHECK(!rg_trace_is_open());
    const rg_trace_stats *st = rg_trace_get_stats();
    CHECK(st->emitted == 1 && st->unmapped_skips == 2 && st->vbl_from_game == 1);
    FILE *f = fopen(tpath, "r");
    char line[512];
    int rows = 0, unm = 0, note = 0, stop = 0;
    while (f && fgets(line, sizeof line, f)) {
        if (line[0] != '#')
            rows++;
        if (!strncmp(line, "# unmapped\t5\tsym:Span", 21) || !strncmp(line, "# unmapped\t5\tiop\t", 17))
            unm++;
        if (!strncmp(line, "# note\t5\tsym:Raw\t", 16))
            note++;
        if (!strncmp(line, "# stop\tstop-vbl", 15))
            stop++;
    }
    if (f)
        fclose(f);
    CHECK(rows == 2 + 11 - 2);  /* @cycle @vbl + 11 regions - 2 unmapped */
    CHECK(unm == 2 && stop == 1);
    CHECK(note == (sizeof(void *) == 4));
    rg_trace_regions_free(&rs);
    rg_trace_set_ram(NULL, 0, 0);
    rg_trace_set_arena(NULL, 0, 0);
    rg_trace_clear_symbols();
    free(ram);
    return g_fail;
}

/* ---------------------------------------------------------------- parse */
static int t_parse(const char *dir)
{
    char a[512], b[512], p[512], err[256];
    snprintf(a, sizeof a, "%s/parse_a.cfg", dir);
    snprintf(b, sizeof b, "%s/parse_b.cfg", dir);
    snprintf(p, sizeof p, "%s/parse_port.cfg", dir);
    write_file(a, "# comment\n"
                  "ee  r1  0x100 0x300 0x100   # chunked\n"
                  "ee  r2  1_000 0o2000\n"
                  "include parse_b.cfg\n"
                  "spr s   0 0x4000\n"
                  "ee  d   *0x10+0x8 0b100\n"
                  "ee  e   *0x20 4\n");
    write_file(b, "ee  inc 0x10 0x15 0x4\n");
    rg_trace_regions rs = {0};
    CHECK(rg_trace_regions_load(&rs, a, err, sizeof err) == 0);
    CHECK(rs.n == 8);
    if (rs.n == 8) {
        CHECK(!strcmp(rs.r[0].name, "r1@00000100") && rs.r[0].start == 0x100 && rs.r[0].end == 0x200);
        CHECK(!strcmp(rs.r[1].name, "r1@00000200"));
        CHECK(!strcmp(rs.r[2].name, "r2") && rs.r[2].start == 1000 && rs.r[2].end == 1024);
        CHECK(!strcmp(rs.r[3].name, "inc@00000010") && rs.r[4].start == 0x14 && rs.r[4].end == 0x15);
        CHECK(rs.r[5].space == RG_TRACE_SPACE_SPR);
        CHECK(rs.r[6].deref && rs.r[6].ptr == 0x10 && rs.r[6].off == 8 && rs.r[6].end == 4);
    }
    write_file(p, "ptrs nosuch 0\n");
    CHECK(rg_trace_portcfg_load(&rs, p, err, sizeof err) != 0 && strstr(err, "nosuch"));
    write_file(p, "bogus r2\n");
    CHECK(rg_trace_portcfg_load(&rs, p, err, sizeof err) != 0);
    write_file(p, "ptrs r2\n");
    CHECK(rg_trace_portcfg_load(&rs, p, err, sizeof err) != 0);
    rg_trace_regions_free(&rs);
    /* Python int(x, 0) rejects a leading-zero decimal */
    write_file(a, "ee x 010 0x20\n");
    CHECK(rg_trace_regions_load(&rs, a, err, sizeof err) != 0);
    rg_trace_regions_free(&rs);
    write_file(a, "ee x 0x10\n");
    CHECK(rg_trace_regions_load(&rs, a, err, sizeof err) != 0);
    rg_trace_regions_free(&rs);
    return g_fail;
}

/* ---------------------------------------------------------------- symtab */
int rg_trace_register_symtab_fixture(void);
extern unsigned char D_00481000[16];
extern unsigned int D_00481010[4];
extern void *D_00481020;
extern unsigned char D_004E9E00[0x80];

static int t_symtab(void)
{
    rg_trace_clear_symbols();
    CHECK(rg_trace_register_symtab_fixture() == 0);
    CHECK(rg_trace_symbol_count() == 4);
    const rg_trace_sym *s = rg_trace_symbol_at(0x00481014);
    CHECK(s && s->addr == 0x00481010 && s->host == (void *)D_00481010 && s->size == 0x10);
    CHECK(rg_trace_host_ptr(0x00481014, NULL) == (uint8_t *)D_00481010 + 4);
    CHECK(rg_trace_host_ptr(0x00481000, NULL) == D_00481000);
    CHECK(rg_trace_host_ptr(0x00481020, NULL) == (void *)&D_00481020);
    s = rg_trace_symbol_at(0x004E9E7F);
    CHECK(s && s->host == D_004E9E00 && s->size == 0x80); /* clipped at the arena */
    CHECK(rg_trace_symbol_at(0x004E9E80) == NULL);
    CHECK(rg_trace_symbol_at(0x00490000) == NULL);        /* non-sym: region not taken */
    rg_trace_clear_symbols();
    return g_fail;
}

int main(int argc, char **argv)
{
    const char *t = argc > 1 ? argv[1] : "";
    int rc;
    if (!strcmp(t, "hash"))
        rc = t_hash();
    else if (!strcmp(t, "image") && argc > 4)
        rc = t_image(argv[2], argv[3], argv[4]);
    else if (!strcmp(t, "deref") && argc > 2)
        rc = t_deref(argv[2]);
    else if (!strcmp(t, "parse") && argc > 2)
        rc = t_parse(argv[2]);
    else if (!strcmp(t, "symtab"))
        rc = t_symtab();
    else {
        fprintf(stderr, "usage: rg-trace-tests hash|image R OUT IMG|deref DIR|parse DIR|symtab\n");
        return 2;
    }
    if (strcmp(t, "hash"))
        printf("%s: %s\n", t, rc ? "FAIL" : "PASS");
    return rc ? 1 : 0;
}
