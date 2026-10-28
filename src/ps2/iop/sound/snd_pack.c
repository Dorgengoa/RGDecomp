/* SPDX-License-Identifier: CC0-1.0 */
/* Game archive + .snd pack reader for the sound tools/tests, see snd_pack.h. */
#include "snd_pack.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static uint32_t rd32(const uint8_t *p) { return (uint32_t)p[0] | (uint32_t)p[1] << 8 | (uint32_t)p[2] << 16 | (uint32_t)p[3] << 24; }

static uint8_t *read_file(const char *path, uint32_t *size)
{
    FILE *f = fopen(path, "rb");
    if (!f)
        return NULL;
    fseek(f, 0, SEEK_END);
    long n = ftell(f);
    fseek(f, 0, SEEK_SET);
    uint8_t *d = n > 0 ? (uint8_t *)malloc((size_t)n) : NULL;
    if (d && fread(d, 1, (size_t)n, f) != (size_t)n) {
        free(d);
        d = NULL;
    }
    fclose(f);
    if (d && size)
        *size = (uint32_t)n;
    return d;
}

int snd_archive_open(snd_archive *a, const char *hd6_path, const char *dat_path)
{
    memset(a, 0, sizeof *a);
    uint32_t n = 0;
    uint8_t *d = read_file(hd6_path, &n);
    if (!d || n < 0x2C || memcmp(d, "HD6", 3) != 0) {
        free(d);
        return -1;
    }
    uint32_t tok_off = rd32(d + 4), tok_size = rd32(d + 8);
    uint32_t name_off = rd32(d + 0x14), name_size = rd32(d + 0x18);
    uint32_t count = rd32(d + 0x24), dir_off = rd32(d + 0x28);
    if ((uint64_t)tok_off + tok_size > n || (uint64_t)name_off + name_size > n || (uint64_t)dir_off + count * 8ull > n) {
        free(d);
        return -1;
    }
    /* token table: NUL-separated strings */
    int ntok = 0;
    for (uint32_t i = 0; i < tok_size; i++)
        if (d[tok_off + i] == 0)
            ntok++;
    const char **tok = (const char **)calloc((size_t)ntok + 1, sizeof *tok);
    if (!tok) {
        free(d);
        return -1;
    }
    int k = 0;
    tok[k++] = (const char *)d + tok_off;
    for (uint32_t i = 0; i + 1 < tok_size && k <= ntok; i++)
        if (d[tok_off + i] == 0)
            tok[k++] = (const char *)d + tok_off + i + 1;
    a->files = (snd_arc_file *)calloc(count ? count : 1, sizeof *a->files);
    if (!a->files) {
        free(tok);
        free(d);
        return -1;
    }
    for (uint32_t i = 0; i < count; i++) {
        const uint8_t *r = d + dir_off + i * 8;
        uint64_t v = (uint64_t)rd32(r) | (uint64_t)rd32(r + 4) << 32;
        uint32_t size = (uint32_t)(v >> 38) << 2;
        if (!size)
            continue;
        snd_arc_file *f = &a->files[a->nfiles];
        f->offset = ((v >> 18) & 0xFFFFF) * 2048ull;
        f->size = size;
        uint32_t p = (uint32_t)(v & 0x3FFFF);
        size_t len = 0;
        while (p < name_size) {
            uint32_t t = 0;
            int shift = 0;
            uint8_t b;
            do {
                b = d[name_off + p++];
                t |= (uint32_t)(b & 0x7F) << shift;
                shift += 7;
            } while ((b & 0x80) && p < name_size);
            if (t == 0)
                break;
            const char *s = (int)t < k ? tok[t] : "?";
            size_t sl = strlen(s);
            if (len + sl >= sizeof f->path)
                break;
            memcpy(f->path + len, s, sl);
            len += sl;
        }
        f->path[len] = 0;
        a->nfiles++;
    }
    free(tok);
    free(d);
    snprintf(a->dat_path, sizeof a->dat_path, "%s", dat_path);
    return 0;
}

void snd_archive_close(snd_archive *a)
{
    free(a->files);
    memset(a, 0, sizeof *a);
}

static int path_eq(const char *x, const char *y)
{
    for (; *x && *y; x++, y++) {
        char cx = *x == '/' ? '\\' : (char)tolower((unsigned char)*x);
        char cy = *y == '/' ? '\\' : (char)tolower((unsigned char)*y);
        if (cx != cy)
            return 0;
    }
    return *x == *y;
}

const snd_arc_file *snd_archive_find(const snd_archive *a, const char *path)
{
    for (int i = 0; i < a->nfiles; i++)
        if (path_eq(a->files[i].path, path))
            return &a->files[i];
    return NULL;
}

uint8_t *snd_archive_read(const snd_archive *a, const snd_arc_file *f)
{
    FILE *fp = fopen(a->dat_path, "rb");
    if (!fp)
        return NULL;
    uint8_t *d = (uint8_t *)malloc(f->size);
#if defined(_WIN32)
    int ok = d && _fseeki64(fp, (long long)f->offset, SEEK_SET) == 0;
#else
    int ok = d && fseeko(fp, (off_t)f->offset, SEEK_SET) == 0;
#endif
    if (ok)
        ok = fread(d, 1, f->size, fp) == f->size;
    fclose(fp);
    if (!ok) {
        free(d);
        return NULL;
    }
    return d;
}

uint8_t *snd_data_load(const char *data_dir, const char *path, uint32_t *size)
{
    static const char *names[] = {"DATA0_0", "DATA0_1", "DATA1_0", "DATA1_1"};
    for (int i = 0; i < 4; i++) {
        char h[600], dd[600];
        snprintf(h, sizeof h, "%s/%s.HD6", data_dir, names[i]);
        snprintf(dd, sizeof dd, "%s/%s.DAT", data_dir, names[i]);
        snd_archive a;
        if (snd_archive_open(&a, h, dd) < 0)
            continue;
        const snd_arc_file *f = snd_archive_find(&a, path);
        uint8_t *d = NULL;
        if (f) {
            d = snd_archive_read(&a, f);
            if (d && size)
                *size = f->size;
        }
        snd_archive_close(&a);
        if (d)
            return d;
    }
    return NULL;
}

int snd_pack_list(const uint8_t *d, uint32_t size, snd_pack_entry *out, int max)
{
    uint32_t off = 0;
    int n = 0;
    while (off + 0x50 <= size && n < max) {
        uint32_t hdr = rd32(d + off + 0x40), sz = rd32(d + off + 0x44), next = rd32(d + off + 0x48);
        if (sz == 0xFFFFFFFFu || hdr < 0x4C)
            break;
        if ((uint64_t)off + hdr + sz > size)
            break;
        snd_pack_entry *e = &out[n++];
        memcpy(e->name, d + off, 0x40);
        e->name[63] = 0;
        e->offset = off + hdr;
        e->size = sz;
        if (next == 0 || next == 0xFFFFFFFFu)
            break;
        off += next;
    }
    return n;
}

const snd_pack_entry *snd_pack_find(const snd_pack_entry *e, int n, const char *suffix)
{
    size_t sl = strlen(suffix);
    for (int i = 0; i < n; i++) {
        size_t nl = strlen(e[i].name);
        if (nl < sl)
            continue;
        int ok = 1;
        for (size_t k = 0; k < sl && ok; k++)
            ok = tolower((unsigned char)e[i].name[nl - sl + k]) == tolower((unsigned char)suffix[k]);
        if (ok)
            return &e[i];
    }
    return NULL;
}
