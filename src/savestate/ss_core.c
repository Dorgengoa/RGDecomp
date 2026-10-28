/* SPDX-License-Identifier: CC0-1.0
 * Port save states: file format, save, load (rg_savestate.h,
 * docs/TEST-FIXTURES.md "Save states").
 *
 * File layout (little endian):
 *
 *   ss_fhdr                       magic "RGSTATE1", build id, region and image
 *                                 addresses, init fingerprint, rg_ss_meta,
 *                                 header hash
 *   { ss_shdr, payload } x nsect  name, address, size, encoding, stored bytes,
 *                                 hash of the decoded bytes
 *   "RGSEND!!"                    trailer (a truncated file is refused)
 *
 * Encoding 1 ("pages"): a bitmap of the non-zero 4 KB pages, then those pages.
 * A load reads and verifies EVERY section before it writes anything back, so
 * a corrupt, truncated or foreign file leaves the process untouched.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "ps2k_ss.h"
#include "rg_savestate.h"
#include "ss_internal.h"

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

/* 2 (2026-10-18): section "ram" (and the header's ram / ram_size) is the game heap
 * allocation (RG_CRT0_HEAP_ALLOC bytes, heap at +0x200), no longer a 32 MB EE-RAM image
 * (docs/NATIVE-CPU.md section 8).  Version-1 files are refused with a message. */
#define SS_VERSION 2
#define SS_PAGE 4096u
#define SS_MAX_HOOKS 16
#define SS_MAX_SECT 256

typedef struct ss_fhdr {
    char magic[8];
    uint32_t version, hdr_bytes;
    char build_id[40];
    uint32_t timestamp, size_of_image;
    uint32_t image_base, data_lo, data_hi;
    uint32_t ram, ram_size, arena, arena_size, heap, heap_size;
    uint64_t init_fp;
    uint32_t nsect, pad;
    rg_ss_meta meta;
    uint64_t hdr_hash;          /* ss_hash64 of the header with this field 0 */
} ss_fhdr;

typedef struct ss_shdr {
    char name[32];
    uint32_t addr, size;        /* where the decoded bytes go (addr 0: hook / table) */
    uint32_t enc, stored;       /* encoding, payload bytes that follow */
    uint64_t hash;              /* of the decoded bytes */
} ss_shdr;

static const char k_magic[8] = {'R', 'G', 'S', 'T', 'A', 'T', 'E', '1'};
static const char k_trailer[8] = {'R', 'G', 'S', 'E', 'N', 'D', '!', '!'};

static rg_ss_hook g_hooks[SS_MAX_HOOKS];
static int g_nhooks;
static char g_build_id[40];

int rg_ss_add_hook(const rg_ss_hook *h)
{
    if (!h || !h->name || strlen(h->name) > 26 || g_nhooks == SS_MAX_HOOKS)
        return -1;
    for (int i = 0; i < g_nhooks; i++)
        if (!strcmp(g_hooks[i].name, h->name))
            return -1;
    g_hooks[g_nhooks++] = *h;
    return 0;
}

/* ------------------------------------------------------------ build id */
const char *rg_ss_build_id(void)
{
    if (g_build_id[0])
        return g_build_id;
    const ss_image *im = ss_map_image();
    FILE *f = im->exe_path[0] ? fopen(im->exe_path, "rb") : NULL;
    if (!f)
        return "unknown";
    uint64_t h1 = 0x52474255494c44ull, h2 = 0x9a5d3c1b7e6f2a41ull, n = 0;
    static uint8_t buf[1 << 16];
    size_t got;
    while ((got = fread(buf, 1, sizeof buf, f)) > 0) {
        h1 = ss_hash64(buf, got, h1);
        h2 = ss_hash64(buf, got, h2 ^ n);
        n += got;
    }
    fclose(f);
    snprintf(g_build_id, sizeof g_build_id, "%016llx%016llx", (unsigned long long)h1,
             (unsigned long long)(h2 ^ n));
    return g_build_id;
}

/* ------------------------------------------------------------ writer */
typedef struct wr {
    FILE *f;
    int nsect;
    int failed;
} wr;

static void w_bytes(wr *w, const void *p, size_t n)
{
    if (!w->failed && fwrite(p, 1, n, w->f) != n)
        w->failed = 1;
}

/* a section from up to 8 pieces of memory, concatenated */
typedef struct piece {
    const uint8_t *p;
    size_t n;
} piece;

static int page_nonzero(const uint8_t *p, size_t n)
{
    const uint32_t *q = (const uint32_t *)p;
    size_t k = n / 4;
    for (size_t i = 0; i < k; i++)
        if (q[i])
            return 1;
    for (size_t i = k * 4; i < n; i++)
        if (p[i])
            return 1;
    return 0;
}

/* encode the concatenation of pieces (total `size` bytes, page-elided) */
static void w_section(wr *w, const char *name, uint32_t addr, const piece *pc, int npc)
{
    size_t size = 0;
    for (int i = 0; i < npc; i++)
        size += pc[i].n;
    uint8_t *flat = NULL;
    const uint8_t *src;
    if (npc == 1) {
        src = pc[0].p;
    } else {
        flat = (uint8_t *)malloc(size ? size : 1);
        if (!flat) {
            w->failed = 1;
            return;
        }
        size_t o = 0;
        for (int i = 0; i < npc; i++) {
            memcpy(flat + o, pc[i].p, pc[i].n);
            o += pc[i].n;
        }
        src = flat;
    }
    size_t npages = (size + SS_PAGE - 1) / SS_PAGE, bm = (npages + 7) / 8;
    uint8_t *bitmap = (uint8_t *)calloc(bm ? bm : 1, 1);
    size_t stored = bm;
    for (size_t i = 0; i < npages; i++) {
        size_t o = i * SS_PAGE, n = size - o < SS_PAGE ? size - o : SS_PAGE;
        if (page_nonzero(src + o, n)) {
            bitmap[i / 8] |= (uint8_t)(1u << (i % 8));
            stored += n;
        }
    }
    ss_shdr h;
    memset(&h, 0, sizeof h);
    snprintf(h.name, sizeof h.name, "%s", name);
    h.addr = addr;
    h.size = (uint32_t)size;
    h.enc = 1;
    h.stored = (uint32_t)stored;
    h.hash = ss_hash64(src, size, 0x5345435449ull);
    w_bytes(w, &h, sizeof h);
    w_bytes(w, bitmap, bm);
    for (size_t i = 0; i < npages; i++) {
        if (!(bitmap[i / 8] & (1u << (i % 8))))
            continue;
        size_t o = i * SS_PAGE, n = size - o < SS_PAGE ? size - o : SS_PAGE;
        w_bytes(w, src + o, n);
    }
    free(bitmap);
    free(flat);
    w->nsect++;
}

/* the captured static ranges (GAME + MODEL) */
static int static_ranges(ss_range *out, int cap)
{
    const ss_range *r;
    int n = ss_map_data_ranges(&r), k = 0;
    for (int i = 0; i < n; i++) {
        if (r[i].cls != SS_GAME && r[i].cls != SS_MODEL)
            continue;
        if (k && out[k - 1].hi == r[i].lo) {
            out[k - 1].hi = r[i].hi;
            continue;
        }
        if (k < cap)
            out[k] = r[i];
        k++;
    }
    return k;
}

static int region_check(char *err, size_t cap)
{
    if (!rg_ss_active()) {
        snprintf(err, cap, "save states are off in this process: %s",
                 rg_ss_error() ? rg_ss_error() : "rg_ss_init was not called");
        return -1;
    }
    if (!ps2k_fiber_arena_on()) {
        snprintf(err, cap, "guest threads do not run on the fixed-address fiber arena");
        return -1;
    }
    return 0;
}

static void fill_fhdr(ss_fhdr *h, const rg_ss_meta *meta, int nsect)
{
    const ss_image *im = ss_map_image();
    const ss_region_info *rg = ss_region();
    memset(h, 0, sizeof *h);
    memcpy(h->magic, k_magic, 8);
    h->version = SS_VERSION;
    h->hdr_bytes = sizeof *h;
    snprintf(h->build_id, sizeof h->build_id, "%s", rg_ss_build_id());
    h->timestamp = im->timestamp;
    h->size_of_image = im->size_of_image;
    h->image_base = (uint32_t)im->base;
    h->data_lo = (uint32_t)im->data_lo;
    h->data_hi = (uint32_t)im->data_hi;
    h->ram = (uint32_t)rg->ram;
    h->ram_size = (uint32_t)rg->ram_size;
    h->arena = (uint32_t)rg->arena;
    h->arena_size = (uint32_t)rg->arena_size;
    h->heap = (uint32_t)rg->heap;
    h->heap_size = (uint32_t)rg->heap_size;
    h->init_fp = ss_heap_init_fingerprint();
    h->nsect = (uint32_t)nsect;
    if (meta)
        h->meta = *meta;
    h->hdr_hash = 0;
    h->hdr_hash = ss_hash64(h, sizeof *h, 0x484452ull);
}

int rg_ss_save(const char *path, const rg_ss_meta *meta, char *err, size_t cap)
{
    char dummy[4];
    if (!err) {
        err = dummy;
        cap = sizeof dummy;
    }
    if (region_check(err, cap) != 0)
        return -1;
    for (int i = 0; i < g_nhooks; i++) {
        char why[200] = "";
        if (g_hooks[i].can_save && g_hooks[i].can_save(why, sizeof why) != 0) {
            snprintf(err, cap, "%s: cannot save now: %s", g_hooks[i].name, why);
            return -1;
        }
    }
    for (int i = 0; i < g_nhooks; i++)
        if (g_hooks[i].pre_save)
            g_hooks[i].pre_save();

    char tmp[600];
    snprintf(tmp, sizeof tmp, "%s.part", path);
    wr w = {fopen(tmp, "wb"), 0, 0};
    if (!w.f) {
        snprintf(err, cap, "cannot write %s", tmp);
        return -1;
    }
    ss_fhdr h;
    fill_fhdr(&h, meta, 0);
    w_bytes(&w, &h, sizeof h); /* rewritten with the section count at the end */

    /* hooks first: small, and a loader reads them before any raw bytes */
    for (int i = 0; i < g_nhooks; i++) {
        if (!g_hooks[i].save_size || !g_hooks[i].save)
            continue;
        size_t n = g_hooks[i].save_size();
        uint8_t *b = (uint8_t *)malloc(n ? n : 1);
        int got = b ? g_hooks[i].save(b, n) : -1;
        if (got < 0) {
            free(b);
            fclose(w.f);
            remove(tmp);
            snprintf(err, cap, "hook %s failed to save", g_hooks[i].name);
            return -1;
        }
        char nm[32];
        snprintf(nm, sizeof nm, "hook:%s", g_hooks[i].name);
        piece pc = {b, (size_t)got};
        w_section(&w, nm, 0, &pc, 1);
        free(b);
    }

    /* statics: the range table, then the bytes */
    {
        static ss_range rr[16384];
        int nr = static_ranges(rr, 16384);
        if (nr > 16384) {
            fclose(w.f);
            remove(tmp);
            snprintf(err, cap, "too many static ranges (%d)", nr);
            return -1;
        }
        uint32_t *tab = (uint32_t *)malloc(sizeof(uint32_t) * (1 + 2 * (size_t)nr));
        size_t total = 0;
        tab[0] = (uint32_t)nr;
        for (int i = 0; i < nr; i++) {
            tab[1 + 2 * i] = (uint32_t)rr[i].lo;
            tab[2 + 2 * i] = (uint32_t)rr[i].hi;
            total += rr[i].hi - rr[i].lo;
        }
        piece pt = {(const uint8_t *)tab, sizeof(uint32_t) * (1 + 2 * (size_t)nr)};
        w_section(&w, "statics.map", 0, &pt, 1);
        uint8_t *flat = (uint8_t *)malloc(total ? total : 1);
        size_t o = 0;
        for (int i = 0; i < nr; i++) {
            memcpy(flat + o, (const void *)rr[i].lo, rr[i].hi - rr[i].lo);
            o += rr[i].hi - rr[i].lo;
        }
        piece pd = {flat, total};
        w_section(&w, "statics", 0, &pd, 1);
        free(flat);
        free(tab);
    }

    /* the game heap (crt0's allocation, the provider range) */
    {
        const ss_region_info *rg = ss_region();
        piece pr = {(const uint8_t *)rg->ram, rg->ram_size};
        w_section(&w, "ram", (uint32_t)rg->ram, &pr, 1);
    }

    /* the state heap (allocator metadata at its start) */
    ss_heap_lock();
    {
        const ss_region_info *rg = ss_region();
        uintptr_t top = ss_heap_top();
        piece ph = {(const uint8_t *)rg->heap, top - rg->heap};
        w_section(&w, "heap", (uint32_t)rg->heap, &ph, 1);
    }
    ss_heap_unlock();

    /* fibers: the slot table and every suspended stack */
    {
        void *hp;
        size_t hn;
        ps2k_fiber_arena_header(&hp, &hn);
        piece pf = {(const uint8_t *)hp, hn};
        w_section(&w, "fibers", (uint32_t)(uintptr_t)hp, &pf, 1);
        uintptr_t st[96][2];
        int ns = ps2k_fiber_arena_stacks(st, 96);
        for (int i = 0; i < ns && i < 96; i++) {
            piece ps = {(const uint8_t *)st[i][0], st[i][1] - st[i][0]};
            w_section(&w, "stack", (uint32_t)st[i][0], &ps, 1);
        }
    }

    w_bytes(&w, k_trailer, 8);
    fill_fhdr(&h, meta, w.nsect);
    if (!w.failed && fseek(w.f, 0, SEEK_SET) == 0)
        w_bytes(&w, &h, sizeof h);
    if (fclose(w.f) != 0)
        w.failed = 1;
    if (w.failed) {
        remove(tmp);
        snprintf(err, cap, "write error on %s", tmp);
        return -1;
    }
    remove(path);
    if (rename(tmp, path) != 0) {
        snprintf(err, cap, "cannot rename %s to %s", tmp, path);
        return -1;
    }
    return 0;
}

/* ------------------------------------------------------------ reader */
typedef struct sect {
    ss_shdr h;
    uint8_t *data; /* decoded */
} sect;

static int read_hdr(FILE *f, ss_fhdr *h, char *err, size_t cap, const char *path)
{
    if (fread(h, 1, sizeof *h, f) != sizeof *h || memcmp(h->magic, k_magic, 8)) {
        snprintf(err, cap, "%s is not an rg-game save state", path);
        return -1;
    }
    if (h->version != SS_VERSION || h->hdr_bytes != sizeof *h) {
        snprintf(err, cap,
                 "%s: save state format %u, this build reads %u (format 2: the ram section is the "
                 "game heap, not a 32 MB EE-RAM image); regenerate it with tools/fixtures/regen.py",
                 path, (unsigned)h->version, (unsigned)SS_VERSION);
        return -1;
    }
    uint64_t want = h->hdr_hash;
    h->hdr_hash = 0;
    uint64_t got = ss_hash64(h, sizeof *h, 0x484452ull);
    h->hdr_hash = want;
    if (got != want) {
        snprintf(err, cap, "%s: header checksum mismatch (corrupt file)", path);
        return -1;
    }
    return 0;
}

static int check_build(const ss_fhdr *h, char *err, size_t cap, const char *path)
{
    if (!rg_ss_active()) {
        snprintf(err, cap, "save states are off in this process: %s",
                 rg_ss_error() ? rg_ss_error() : "rg_ss_init was not called");
        return -1;
    }
    const ss_image *im = ss_map_image();
    if (strcmp(h->build_id, rg_ss_build_id()) || h->timestamp != im->timestamp) {
        snprintf(err, cap,
                 "%s was saved by a different build of rg-game (state build %.32s, this exe %.32s). "
                 "Save states only load into the exact build that wrote them: regenerate the state "
                 "with tools/fixtures/regen.py (docs/TEST-FIXTURES.md)",
                 path, h->build_id, rg_ss_build_id());
        return -1;
    }
    const ss_region_info *rg = ss_region();
    if (h->image_base != (uint32_t)im->base || h->ram != (uint32_t)rg->ram ||
        h->arena != (uint32_t)rg->arena || h->heap != (uint32_t)rg->heap ||
        h->ram_size != (uint32_t)rg->ram_size || h->heap_size != (uint32_t)rg->heap_size ||
        h->arena_size != (uint32_t)rg->arena_size) {
        snprintf(err, cap,
                 "%s: the address layout differs (state: image %08x RAM %08x arena %08x heap %08x; "
                 "here: %08x %08x %08x %08x)",
                 path, (unsigned)h->image_base, (unsigned)h->ram, (unsigned)h->arena, (unsigned)h->heap,
                 (unsigned)im->base, (unsigned)rg->ram, (unsigned)rg->arena, (unsigned)rg->heap);
        return -1;
    }
    if (h->init_fp != ss_heap_init_fingerprint()) {
        snprintf(err, cap,
                 "%s: the saving process initialised differently (init allocation fingerprint "
                 "%016llx, here %016llx). Load with the options the state was saved with "
                 "(same RG_DATA contents, RG_GS_ASYNC, RG_CDVD_MODEL, RG_GPU kind, data dir)",
                 path, (unsigned long long)h->init_fp, (unsigned long long)ss_heap_init_fingerprint());
        return -1;
    }
    return 0;
}

int rg_ss_peek(const char *path, rg_ss_meta *meta, int check, char *err, size_t cap)
{
    char dummy[4];
    if (!err) {
        err = dummy;
        cap = sizeof dummy;
    }
    FILE *f = fopen(path, "rb");
    if (!f) {
        snprintf(err, cap, "cannot open %s", path);
        return -1;
    }
    ss_fhdr h;
    int rc = read_hdr(f, &h, err, cap, path);
    fclose(f);
    if (rc == 0 && meta)
        *meta = h.meta;
    if (rc == 0 && check)
        rc = check_build(&h, err, cap, path);
    return rc;
}

static int read_sect(FILE *f, sect *s, char *err, size_t cap, const char *path)
{
    if (fread(&s->h, 1, sizeof s->h, f) != sizeof s->h || s->h.enc != 1 || s->h.name[31]) {
        snprintf(err, cap, "%s: truncated or corrupt section table", path);
        return -1;
    }
    size_t size = s->h.size, npages = (size + SS_PAGE - 1) / SS_PAGE, bm = (npages + 7) / 8;
    if (s->h.stored < bm || s->h.stored > size + bm) {
        snprintf(err, cap, "%s: corrupt section %s", path, s->h.name);
        return -1;
    }
    uint8_t *bitmap = (uint8_t *)malloc(bm ? bm : 1);
    s->data = (uint8_t *)calloc(size ? size : 1, 1);
    if (!bitmap || !s->data || fread(bitmap, 1, bm, f) != bm) {
        free(bitmap);
        snprintf(err, cap, "%s: truncated section %s", path, s->h.name);
        return -1;
    }
    size_t used = bm;
    for (size_t i = 0; i < npages; i++) {
        if (!(bitmap[i / 8] & (1u << (i % 8))))
            continue;
        size_t o = i * SS_PAGE, n = size - o < SS_PAGE ? size - o : SS_PAGE;
        if (used + n > s->h.stored || fread(s->data + o, 1, n, f) != n) {
            free(bitmap);
            snprintf(err, cap, "%s: truncated section %s", path, s->h.name);
            return -1;
        }
        used += n;
    }
    free(bitmap);
    if (used != s->h.stored || ss_hash64(s->data, size, 0x5345435449ull) != s->h.hash) {
        snprintf(err, cap, "%s: section %s fails its checksum (corrupt file)", path, s->h.name);
        return -1;
    }
    return 0;
}

static int in_range(uintptr_t a, size_t n, uintptr_t lo, size_t sz)
{
    return a >= lo && a + n >= a && a + n <= lo + sz;
}

int rg_ss_load(const char *path, rg_ss_meta *meta, char *err, size_t cap)
{
    char dummy[4];
    if (!err) {
        err = dummy;
        cap = sizeof dummy;
    }
    if (region_check(err, cap) != 0)
        return -1;
    FILE *f = fopen(path, "rb");
    if (!f) {
        snprintf(err, cap, "cannot open %s", path);
        return -1;
    }
    ss_fhdr h;
    if (read_hdr(f, &h, err, cap, path) != 0 || check_build(&h, err, cap, path) != 0) {
        fclose(f);
        return -1;
    }
    if (h.nsect == 0 || h.nsect > SS_MAX_SECT) {
        fclose(f);
        snprintf(err, cap, "%s: bad section count %u", path, (unsigned)h.nsect);
        return -1;
    }
    /* 1. read and verify everything */
    sect *s = (sect *)calloc(h.nsect, sizeof *s);
    int ok = s != NULL;
    for (uint32_t i = 0; ok && i < h.nsect; i++)
        ok = read_sect(f, &s[i], err, cap, path) == 0;
    char tr[8];
    if (ok && (fread(tr, 1, 8, f) != 8 || memcmp(tr, k_trailer, 8))) {
        snprintf(err, cap, "%s: missing trailer (truncated file)", path);
        ok = 0;
    }
    fclose(f);

    /* 2. structural checks against this process */
    const ss_region_info *rg = ss_region();
    static ss_range rr[16384];
    int nr = static_ranges(rr, 16384);
    sect *smap = NULL, *sdata = NULL;
    for (uint32_t i = 0; ok && i < h.nsect; i++) {
        sect *x = &s[i];
        const char *nm = x->h.name;
        if (!strcmp(nm, "statics.map"))
            smap = x;
        else if (!strcmp(nm, "statics"))
            sdata = x;
        else if (!strcmp(nm, "ram"))
            ok = x->h.addr == rg->ram && x->h.size == rg->ram_size;
        else if (!strcmp(nm, "heap"))
            ok = x->h.addr == rg->heap && in_range(x->h.addr, x->h.size, rg->heap, rg->heap_size);
        else if (!strcmp(nm, "fibers") || !strcmp(nm, "stack"))
            ok = in_range(x->h.addr, x->h.size, rg->arena, rg->arena_size);
        else if (!strncmp(nm, "hook:", 5)) {
            int found = 0;
            for (int k = 0; k < g_nhooks; k++)
                if (!strcmp(nm + 5, g_hooks[k].name))
                    found = 1;
            if (!found) {
                snprintf(err, cap, "%s: section %s has no hook in this process", path, nm);
                ok = 0;
                break;
            }
        } else {
            snprintf(err, cap, "%s: unknown section %s", path, nm);
            ok = 0;
            break;
        }
        if (!ok && !err[0])
            snprintf(err, cap, "%s: section %s does not fit this process", path, nm);
    }
    if (ok && (!smap || !sdata)) {
        snprintf(err, cap, "%s: no statics section", path);
        ok = 0;
    }
    if (ok) {
        const uint32_t *tab = (const uint32_t *)smap->data;
        size_t total = 0;
        if (smap->h.size < 4 || tab[0] != (uint32_t)nr || smap->h.size != 4 + 8u * (uint32_t)nr)
            ok = 0;
        for (int i = 0; ok && i < nr; i++) {
            ok = tab[1 + 2 * i] == (uint32_t)rr[i].lo && tab[2 + 2 * i] == (uint32_t)rr[i].hi;
            total += rr[i].hi - rr[i].lo;
        }
        if (ok && total != sdata->h.size)
            ok = 0;
        if (!ok)
            snprintf(err, cap, "%s: the static data layout differs from this exe", path);
    }
    for (int k = 0; ok && k < g_nhooks; k++) {
        if (!g_hooks[k].load)
            continue;
        char nm[32];
        snprintf(nm, sizeof nm, "hook:%s", g_hooks[k].name);
        int found = 0;
        for (uint32_t i = 0; i < h.nsect; i++)
            if (!strcmp(s[i].h.name, nm))
                found = 1;
        if (!found) {
            snprintf(err, cap, "%s: no %s section", path, nm);
            ok = 0;
        }
    }
    if (!ok) {
        for (uint32_t i = 0; s && i < h.nsect; i++)
            free(s[i].data);
        free(s);
        return -1;
    }

    /* 3. write back: from here on a failure leaves the process unusable */
    for (int k = 0; k < g_nhooks; k++)
        if (g_hooks[k].pre_load)
            g_hooks[k].pre_load();
    {
        size_t o = 0;
        for (int i = 0; i < nr; i++) {
            memcpy((void *)rr[i].lo, sdata->data + o, rr[i].hi - rr[i].lo);
            o += rr[i].hi - rr[i].lo;
        }
    }
    int rc = 0;
    ss_heap_lock();
    for (uint32_t i = 0; i < h.nsect; i++) {
        sect *x = &s[i];
        if (!strcmp(x->h.name, "ram")) {
            memcpy((void *)(uintptr_t)x->h.addr, x->data, x->h.size);
        } else if (!strcmp(x->h.name, "heap")) {
            if (ss_heap_prepare(x->h.addr + x->h.size) != 0) {
                snprintf(err, cap, "cannot commit the state heap");
                rc = -1;
            } else {
                memcpy((void *)(uintptr_t)x->h.addr, x->data, x->h.size);
            }
        } else if (!strcmp(x->h.name, "fibers") || !strcmp(x->h.name, "stack")) {
            if (ps2k_fiber_arena_commit(x->h.addr, (uintptr_t)x->h.addr + x->h.size) != 0) {
                snprintf(err, cap, "cannot commit fiber memory at %08x", (unsigned)x->h.addr);
                rc = -1;
            } else {
                memcpy((void *)(uintptr_t)x->h.addr, x->data, x->h.size);
            }
        }
    }
    ss_heap_unlock();
    for (int k = 0; rc == 0 && k < g_nhooks; k++) {
        if (!g_hooks[k].load)
            continue;
        char nm[32];
        snprintf(nm, sizeof nm, "hook:%s", g_hooks[k].name);
        for (uint32_t i = 0; i < h.nsect; i++)
            if (!strcmp(s[i].h.name, nm) && g_hooks[k].load(s[i].data, s[i].h.size) != 0) {
                snprintf(err, cap, "hook %s refused the state", g_hooks[k].name);
                rc = -1;
            }
    }
    for (int k = 0; rc == 0 && k < g_nhooks; k++)
        if (g_hooks[k].post_load)
            g_hooks[k].post_load();
    for (uint32_t i = 0; i < h.nsect; i++)
        free(s[i].data);
    free(s);
    if (rc == 0 && meta)
        *meta = h.meta;
    return rc;
}
