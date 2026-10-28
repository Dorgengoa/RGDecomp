/* SPDX-License-Identifier: CC0-1.0 */
/* CDVD model, disc half: data/MANIFEST.tsv -> LSN map, file lookup, sector reads.
 * See cdvd.h and docs/CDVD.md. */
#if !defined(_WIN32) && !defined(_FILE_OFFSET_BITS)
#define _FILE_OFFSET_BITS 64
#endif
#include "cdvd.h"

#include <ctype.h>
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

/* ---------------------------------------------------------------- logging */

static void default_log(void *ctx, int level, const char *msg) {
    (void)ctx;
    fprintf(stderr, "cdvd: %s%s\n", level == CDVD_LOG_ERROR ? "error: " : level == CDVD_LOG_WARN ? "warning: " : "",
            msg);
}

static cdvd_log_fn g_log = default_log;
static void *g_log_ctx;

void cdvd_set_log(cdvd_log_fn fn, void *ctx) {
    g_log = fn ? fn : default_log;
    g_log_ctx = fn ? ctx : NULL;
}

void cdvd_log(int level, const char *fmt, ...) {
    char buf[512];
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buf, sizeof buf, fmt, ap);
    va_end(ap);
    g_log(g_log_ctx, level, buf);
}

/* ---------------------------------------------------------------- host files */

static FILE *open_utf8(const char *path) {
#ifdef _WIN32
    int n = MultiByteToWideChar(CP_UTF8, 0, path, -1, NULL, 0);
    wchar_t *w;
    FILE *f;
    if (n <= 0) return NULL;
    w = (wchar_t *)malloc(sizeof(wchar_t) * (size_t)n);
    if (!w) return NULL;
    MultiByteToWideChar(CP_UTF8, 0, path, -1, w, n);
    f = _wfopen(w, L"rb");
    free(w);
    return f;
#else
    return fopen(path, "rb");
#endif
}

static int seek64(FILE *f, uint64_t off) {
#ifdef _WIN32
    return _fseeki64(f, (long long)off, SEEK_SET);
#else
    return fseeko(f, (off_t)off, SEEK_SET);
#endif
}

/* ---------------------------------------------------------------- disc */

typedef struct file_rec {
    char *path;
    uint64_t size;
    uint32_t image[2]; /* first sector of the copy on layer 0/1, CDVD_NO_LSN if none */
    uint8_t present[2]; /* a copy exists on layer 0/1 (an empty file has no sector) */
    FILE *fp;
    int open_failed;
} file_rec;

typedef struct extent {
    uint32_t start, count; /* image sectors */
    uint32_t file;
} extent;

struct cdvd_disc {
    char *dir;
    file_rec *files;
    size_t nfiles;
    extent *ext;
    size_t next;
    int dual;
    uint32_t l1_image_base; /* image sector of the layer-1 volume's sector 0 */
    uint32_t layer1_start;  /* LSN of layer 1 = l1_image_base + 16 */
    uint32_t image_sectors;
    uint32_t lsn_end;
    unsigned warned; /* unmapped-sector warnings issued */
};

/* Geometry of discs whose v1 manifest has no "# volume" lines, keyed by image SHA-1. */
static const struct {
    const char *sha1;
    uint32_t l0_blocks, l1_image_base, l1_blocks;
} k_known_discs[] = {
    /* Rogue Galaxy (USA) v1.01, SCUS-97490 (docs/EXTRACT.md) */
    {"87377e721be58e8b6a5a7501721563500d237df7", 1646704u, 1646688u, 1755520u},
};

static char *xstrdup(const char *s) {
    size_t n = strlen(s) + 1;
    char *p = (char *)malloc(n);
    if (p) memcpy(p, s, n);
    return p;
}

static int parse_u64(const char *s, uint64_t *out) {
    uint64_t v = 0;
    if (!*s) return 0;
    for (; *s; ++s) {
        if (*s < '0' || *s > '9') return 0;
        if (v > (UINT64_MAX - 9) / 10) return 0;
        v = v * 10 + (uint64_t)(*s - '0');
    }
    *out = v;
    return 1;
}

static int parse_u32(const char *s, uint32_t *out) {
    uint64_t v;
    if (!parse_u64(s, &v) || v >= 0xFFFFFFFFull) return 0;
    *out = (uint32_t)v;
    return 1;
}

/* Splits a line at tabs in place. Returns the field count (at most max). */
static int split_tabs(char *line, char **f, int max) {
    int n = 0;
    f[n++] = line;
    for (char *p = line; *p && n < max; ++p)
        if (*p == '\t') {
            *p = 0;
            f[n++] = p + 1;
        }
    return n;
}

static int cmp_extent(const void *a, const void *b) {
    const extent *x = (const extent *)a, *y = (const extent *)b;
    return x->start < y->start ? -1 : x->start > y->start;
}

static char *read_all(const char *path, size_t *len) {
    FILE *f = open_utf8(path);
    char *buf = NULL;
    size_t cap = 0, n = 0;
    if (!f) return NULL;
    for (;;) {
        if (n + 4096 + 1 > cap) {
            char *nb;
            cap = cap ? cap * 2 : 65536;
            nb = (char *)realloc(buf, cap);
            if (!nb) {
                free(buf);
                fclose(f);
                return NULL;
            }
            buf = nb;
        }
        size_t got = fread(buf + n, 1, cap - n - 1, f);
        n += got;
        if (got == 0) break;
    }
    if (ferror(f)) {
        free(buf);
        fclose(f);
        return NULL;
    }
    fclose(f);
    buf[n] = 0;
    *len = n;
    return buf;
}

#define FAIL(...)                                    \
    do {                                             \
        if (err && errlen) snprintf(err, errlen, __VA_ARGS__); \
        goto fail;                                   \
    } while (0)

cdvd_disc *cdvd_disc_open(const char *data_dir, char *err, size_t errlen) {
    cdvd_disc *d = (cdvd_disc *)calloc(1, sizeof *d);
    char *text = NULL, *mpath = NULL;
    size_t len = 0, cap_files = 0, lineno = 0;
    int have_header = 0, have_volume[2] = {0, 0};
    uint32_t vol_base[2] = {0, 0}, vol_blocks[2] = {0, 0};
    uint64_t source_size = 0;
    char sha1[64] = "";

    if (!d) FAIL("out of memory");
    d->dir = xstrdup(data_dir);
    mpath = (char *)malloc(strlen(data_dir) + 16);
    if (!d->dir || !mpath) FAIL("out of memory");
    sprintf(mpath, "%s/MANIFEST.tsv", data_dir);
    text = read_all(mpath, &len);
    if (!text) FAIL("cannot read %s (run rg-extract first; docs/EXTRACT.md)", mpath);

    for (char *line = text; line && *line;) {
        char *nl = strchr(line, '\n'), *f[8];
        int nf;
        if (nl) *nl = 0;
        ++lineno;
        if (nl > line && nl[-1] == '\r') nl[-1] = 0;
        if (line[0] == '#') {
            nf = split_tabs(line, f, 8);
            if (lineno == 1 && strncmp(line, "# rg-extract manifest v", 23) != 0)
                FAIL("%s: not an rg-extract manifest", mpath);
            if (nf >= 2 && !strcmp(f[0], "# source_size")) parse_u64(f[1], &source_size);
            if (nf >= 2 && !strcmp(f[0], "# source_sha1")) snprintf(sha1, sizeof sha1, "%s", f[1]);
            if (nf >= 4 && !strcmp(f[0], "# volume")) {
                uint32_t layer;
                if (!parse_u32(f[1], &layer) || layer > 1 || !parse_u32(f[2], &vol_base[layer]) ||
                    !parse_u32(f[3], &vol_blocks[layer]))
                    FAIL("%s:%u: bad volume line", mpath, (unsigned)lineno);
                have_volume[layer] = 1;
            }
            if (nf >= 1 && !strcmp(f[0], "# section")) break; /* converted outputs etc.: not on the disc */
        } else if (line[0]) {
            nf = split_tabs(line, f, 8);
            if (!have_header) {
                if (nf < 5 || strcmp(f[0], "path") || strcmp(f[1], "size") || strcmp(f[3], "lba") ||
                    strcmp(f[4], "copies"))
                    FAIL("%s:%u: unexpected header", mpath, (unsigned)lineno);
                have_header = 1;
            } else {
                file_rec r;
                memset(&r, 0, sizeof r);
                r.image[0] = r.image[1] = CDVD_NO_LSN;
                if (nf < 5 || !parse_u64(f[1], &r.size)) FAIL("%s:%u: malformed row", mpath, (unsigned)lineno);
                for (char *c = f[4]; *c;) {
                    char *comma = strchr(c, ',');
                    uint32_t layer, at;
                    if (comma) *comma = 0;
                    if (c[0] != 'L' || c[2] != ':' || (c[1] != '0' && c[1] != '1'))
                        FAIL("%s:%u: malformed copies '%s'", mpath, (unsigned)lineno, c);
                    layer = (uint32_t)(c[1] - '0');
                    r.present[layer] = 1;
                    if (strcmp(c + 3, "-") != 0) {
                        if (!parse_u32(c + 3, &at)) FAIL("%s:%u: malformed copies", mpath, (unsigned)lineno);
                        r.image[layer] = at;
                    }
                    c = comma ? comma + 1 : c + strlen(c);
                }
                r.path = xstrdup(f[0]);
                if (!r.path) FAIL("out of memory");
                if (d->nfiles == cap_files) {
                    file_rec *nf2;
                    cap_files = cap_files ? cap_files * 2 : 256;
                    nf2 = (file_rec *)realloc(d->files, cap_files * sizeof *nf2);
                    if (!nf2) {
                        free(r.path);
                        FAIL("out of memory");
                    }
                    d->files = nf2;
                }
                d->files[d->nfiles++] = r;
            }
        }
        line = nl ? nl + 1 : NULL;
    }
    if (!have_header) FAIL("%s: no file table", mpath);

    /* Layer geometry: the manifest's volume lines, else the known-disc table. */
    {
        int any_l1 = 0;
        for (size_t i = 0; i < d->nfiles; ++i)
            if (d->files[i].present[1]) any_l1 = 1;
        if (!have_volume[1]) {
            for (size_t k = 0; k < sizeof k_known_discs / sizeof k_known_discs[0]; ++k)
                if (!strcmp(sha1, k_known_discs[k].sha1)) {
                    have_volume[0] = have_volume[1] = 1;
                    vol_base[0] = 0;
                    vol_blocks[0] = k_known_discs[k].l0_blocks;
                    vol_base[1] = k_known_discs[k].l1_image_base;
                    vol_blocks[1] = k_known_discs[k].l1_blocks;
                }
        }
        if (any_l1 && !have_volume[1])
            FAIL("%s: layer-1 files but no layer-1 volume geometry (re-run rg-extract)", mpath);
        d->dual = have_volume[1];
        if (d->dual) {
            d->l1_image_base = vol_base[1];
            d->layer1_start = vol_base[1] + CDVD_L1_SYSTEM_AREA;
            if (have_volume[0] && vol_blocks[0] != d->layer1_start)
                cdvd_log(CDVD_LOG_WARN, "layer 0 has %u sectors but the layer-1 PVD is at %u; using %u as layer1_start",
                         (unsigned)vol_blocks[0], (unsigned)d->layer1_start, (unsigned)d->layer1_start);
        }
    }

    /* Extents in image space; both copies of a dual-layer file point at the one file. */
    d->ext = (extent *)calloc(d->nfiles * 2 + 1, sizeof *d->ext);
    if (!d->ext) FAIL("out of memory");
    for (size_t i = 0; i < d->nfiles; ++i) {
        file_rec *r = &d->files[i];
        uint64_t secs = (r->size + CDVD_SECTOR - 1) / CDVD_SECTOR;
        for (int l = 0; l < 2; ++l) {
            if (r->image[l] == CDVD_NO_LSN || secs == 0) continue;
            if (l == 1 && !d->dual) FAIL("%s: layer-1 copy on a single-layer disc", mpath);
            if (l == 1 && r->image[1] < d->l1_image_base + CDVD_L1_SYSTEM_AREA)
                FAIL("%s: '%s' layer-1 copy at %u is inside the layer-1 system area", mpath, r->path,
                     (unsigned)r->image[1]);
            if (secs > 0xFFFFFFFFull - r->image[l]) FAIL("%s: '%s' extends past 2^32 sectors", mpath, r->path);
            d->ext[d->next].start = r->image[l];
            d->ext[d->next].count = (uint32_t)secs;
            d->ext[d->next].file = (uint32_t)i;
            d->next++;
        }
    }
    qsort(d->ext, d->next, sizeof *d->ext, cmp_extent);
    for (size_t i = 1; i < d->next; ++i)
        if ((uint64_t)d->ext[i - 1].start + d->ext[i - 1].count > d->ext[i].start)
            FAIL("%s: '%s' and '%s' overlap on the disc", mpath, d->files[d->ext[i - 1].file].path,
                 d->files[d->ext[i].file].path);

    {
        uint64_t end = source_size / CDVD_SECTOR;
        if (d->next) {
            const extent *e = &d->ext[d->next - 1];
            if ((uint64_t)e->start + e->count > end) end = (uint64_t)e->start + e->count;
        }
        if (d->dual && (uint64_t)vol_base[1] + vol_blocks[1] - CDVD_L1_SYSTEM_AREA > end)
            end = (uint64_t)vol_base[1] + vol_blocks[1] - CDVD_L1_SYSTEM_AREA;
        if (end > 0xFFFFFFFFull - CDVD_L1_SYSTEM_AREA) FAIL("%s: disc too large", mpath);
        d->image_sectors = (uint32_t)end;
        d->lsn_end = d->image_sectors + (d->dual ? CDVD_L1_SYSTEM_AREA : 0);
    }
    free(text);
    free(mpath);
    return d;

fail:
    free(text);
    free(mpath);
    cdvd_disc_close(d);
    return NULL;
}

void cdvd_disc_close(cdvd_disc *d) {
    if (!d) return;
    for (size_t i = 0; i < d->nfiles; ++i) {
        if (d->files[i].fp) fclose(d->files[i].fp);
        free(d->files[i].path);
    }
    free(d->files);
    free(d->ext);
    free(d->dir);
    free(d);
}

int cdvd_disc_dual(const cdvd_disc *d) { return d->dual; }
uint32_t cdvd_disc_layer1_start(const cdvd_disc *d) { return d->dual ? d->layer1_start : 0; }
uint32_t cdvd_disc_lsn_end(const cdvd_disc *d) { return d->lsn_end; }
uint32_t cdvd_disc_image_sectors(const cdvd_disc *d) { return d->image_sectors; }

uint32_t cdvd_lsn_to_image(const cdvd_disc *d, uint32_t lsn) {
    return (d->dual && lsn >= d->layer1_start) ? lsn - CDVD_L1_SYSTEM_AREA : lsn;
}

uint32_t cdvd_image_to_lsn(const cdvd_disc *d, uint32_t image, int layer) {
    if (image == CDVD_NO_LSN) return CDVD_NO_LSN;
    return (d->dual && layer == 1) ? image + CDVD_L1_SYSTEM_AREA : image;
}

static void fill_info(const cdvd_disc *d, size_t i, cdvd_file_info *out) {
    const file_rec *r = &d->files[i];
    out->path = r->path;
    out->size = r->size;
    for (int l = 0; l < 2; ++l) {
        out->image[l] = r->image[l];
        out->lsn[l] = cdvd_image_to_lsn(d, r->image[l], l);
    }
}

size_t cdvd_disc_file_count(const cdvd_disc *d) { return d->nfiles; }

int cdvd_disc_file(const cdvd_disc *d, size_t i, cdvd_file_info *out) {
    if (i >= d->nfiles) return 0;
    fill_info(d, i, out);
    return 1;
}

/* "cdrom0:\BIN\NORMAL.BIN;1" -> "BIN/NORMAL.BIN". Returns 0 if it does not fit. */
static int normalise(const char *name, char *out, size_t cap) {
    size_t n = 0;
    const char *colon = strchr(name, ':');
    if (colon) name = colon + 1;
    while (*name == '\\' || *name == '/') ++name;
    for (; *name && *name != ';'; ++name) {
        char c = *name == '\\' ? '/' : *name;
        if (n + 1 >= cap) return 0;
        out[n++] = c;
    }
    out[n] = 0;
    return n > 0;
}

static int path_eq(const char *a, const char *b) {
    for (; *a && *b; ++a, ++b)
        if (toupper((unsigned char)*a) != toupper((unsigned char)*b)) return 0;
    return *a == *b;
}

int cdvd_disc_find(const cdvd_disc *d, const char *name, int layer, cdvd_file_info *out) {
    char want[512];
    if (layer < 0 || layer > 1 || !normalise(name, want, sizeof want)) return 0;
    if (!d->dual) layer = 0;
    for (size_t i = 0; i < d->nfiles; ++i)
        if (d->files[i].present[layer] && path_eq(d->files[i].path, want)) {
            fill_info(d, i, out);
            return 1;
        }
    return 0;
}

/* Index of the extent holding image sector s, or -1; *next_start is the first extent
 * start above s (UINT32_MAX if none). */
static long find_extent(const cdvd_disc *d, uint32_t s, uint32_t *next_start) {
    size_t lo = 0, hi = d->next;
    while (lo < hi) { /* first extent with start > s */
        size_t mid = (lo + hi) / 2;
        if (d->ext[mid].start <= s)
            lo = mid + 1;
        else
            hi = mid;
    }
    *next_start = lo < d->next ? d->ext[lo].start : 0xFFFFFFFFu;
    if (lo > 0) {
        const extent *e = &d->ext[lo - 1];
        if (s - e->start < e->count) return (long)(lo - 1);
    }
    return -1;
}

int cdvd_disc_map(const cdvd_disc *d, uint32_t lsn, const char **path, uint64_t *offset) {
    uint32_t img, next;
    long e;
    if (lsn >= d->lsn_end) return 0;
    img = cdvd_lsn_to_image(d, lsn);
    e = find_extent(d, img, &next);
    if (e < 0) return 0;
    if (path) *path = d->files[d->ext[e].file].path;
    if (offset) *offset = (uint64_t)(img - d->ext[e].start) * CDVD_SECTOR;
    return 1;
}

static FILE *file_handle(cdvd_disc *d, file_rec *r) {
    if (r->fp || r->open_failed) return r->fp;
    {
        size_t n = strlen(d->dir) + strlen(r->path) + 2;
        char *p = (char *)malloc(n);
        if (!p) return NULL;
        snprintf(p, n, "%s/%s", d->dir, r->path);
        r->fp = open_utf8(p);
        if (!r->fp) {
            r->open_failed = 1;
            cdvd_log(CDVD_LOG_ERROR, "cannot open %s: %s", p, strerror(errno));
        }
        free(p);
    }
    return r->fp;
}

static uint64_t (*g_io_clock)(void);
static cdvd_io_stats g_io;

void cdvd_set_io_clock(uint64_t (*now_ns)(void)) { g_io_clock = now_ns; }
void cdvd_get_io_stats(cdvd_io_stats *out) { *out = g_io; }

static int disc_read(cdvd_disc *d, uint32_t lsn, uint32_t count, void *buf, uint32_t *unmapped);

int cdvd_disc_read(cdvd_disc *d, uint32_t lsn, uint32_t count, void *buf, uint32_t *unmapped) {
    uint64_t t0 = g_io_clock ? g_io_clock() : 0;
    int rc = disc_read(d, lsn, count, buf, unmapped);
    g_io.reads++;
    g_io.sectors += count;
    if (g_io_clock) g_io.wall_ns += g_io_clock() - t0;
    return rc;
}

static int disc_read(cdvd_disc *d, uint32_t lsn, uint32_t count, void *buf, uint32_t *unmapped) {
    uint8_t *out = (uint8_t *)buf;
    uint32_t miss = 0;
    if (unmapped) *unmapped = 0;
    if (lsn >= d->lsn_end || count > d->lsn_end - lsn) return CDVD_E_RANGE;
    while (count) {
        uint32_t run = count, img, next, n;
        long e;
        /* The LSN -> image rule changes at layer1_start: never cross it in one run. */
        if (d->dual && lsn < d->layer1_start && run > d->layer1_start - lsn) run = d->layer1_start - lsn;
        img = cdvd_lsn_to_image(d, lsn);
        e = find_extent(d, img, &next);
        if (e >= 0) {
            const extent *x = &d->ext[e];
            file_rec *r = &d->files[x->file];
            uint64_t off = (uint64_t)(img - x->start) * CDVD_SECTOR;
            size_t want, have;
            FILE *fp;
            n = x->start + x->count - img;
            if (n > run) n = run;
            want = (size_t)n * CDVD_SECTOR;
            have = off >= r->size ? 0 : (r->size - off < want ? (size_t)(r->size - off) : want);
            fp = file_handle(d, r);
            if (!fp) return CDVD_E_IO;
            if (have && (seek64(fp, off) != 0 || fread(out, 1, have, fp) != have)) {
                cdvd_log(CDVD_LOG_ERROR, "read failed: %s at byte %llu (%s)", r->path, (unsigned long long)off,
                         feof(fp) ? "file shorter than the manifest says" : strerror(errno));
                clearerr(fp);
                return CDVD_E_IO;
            }
            if (have < want) memset(out + have, 0, want - have);
        } else {
            n = next - img < run ? next - img : run;
            memset(out, 0, (size_t)n * CDVD_SECTOR);
            miss += n;
            if (d->warned < 64) {
                ++d->warned;
                cdvd_log(CDVD_LOG_WARN, "LSN %u..%u (image sectors %u..%u) are in no file; read as zeros%s",
                         (unsigned)lsn, (unsigned)(lsn + n - 1), (unsigned)img, (unsigned)(img + n - 1),
                         d->warned == 64 ? " (further warnings suppressed)" : "");
            }
        }
        out += (size_t)n * CDVD_SECTOR;
        lsn += n;
        count -= n;
    }
    if (unmapped) *unmapped = miss;
    return CDVD_OK;
}
