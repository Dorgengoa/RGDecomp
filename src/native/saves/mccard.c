/* SPDX-License-Identifier: CC0-1.0 */
/* PS2 memory card model over a host directory. See mccard.h and docs/PADMC.md.
 * Written from the game's libmc call sites (game/src/main/file/Mc*.c) and public
 * descriptions of the PS2 card file system; no GPL code. */
#include "mccard.h"

#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <direct.h>
#include <io.h>
#else
#include <dirent.h>
#include <unistd.h>
#endif

#define HOST_PATH_MAX 2048
/* Suffix of the temp files and directories of the crash-safe writes. enc_name always
 * escapes '%', so no card name maps to a host name holding "%~". */
#define TMP_SUFFIX "%~tmp"

/* ---- host file system helpers --------------------------------------------------- */
static int h_mkdir(const char *p)
{
#ifdef _WIN32
    return _mkdir(p);
#else
    return mkdir(p, 0777);
#endif
}

static int h_rmdir(const char *p)
{
#ifdef _WIN32
    return _rmdir(p);
#else
    return rmdir(p);
#endif
}

/* 1 = dir, 0 = file, -1 = missing */
static int h_kind(const char *p, long long *size)
{
#ifdef _WIN32
    struct _stat64 st;
    if (_stat64(p, &st) != 0)
        return -1;
    if (size)
        *size = (long long)st.st_size;
    return (st.st_mode & _S_IFDIR) ? 1 : 0;
#else
    struct stat st;
    if (stat(p, &st) != 0)
        return -1;
    if (size)
        *size = (long long)st.st_size;
    return S_ISDIR(st.st_mode) ? 1 : 0;
#endif
}

typedef void (*h_list_fn)(const char *name, void *u);
static int h_list(const char *dir, h_list_fn fn, void *u)
{
#ifdef _WIN32
    char pat[HOST_PATH_MAX];
    snprintf(pat, sizeof pat, "%s/*", dir);
    struct _finddata_t fd;
    intptr_t h = _findfirst(pat, &fd);
    if (h == -1)
        return -1;
    do {
        if (strcmp(fd.name, ".") && strcmp(fd.name, ".."))
            fn(fd.name, u);
    } while (_findnext(h, &fd) == 0);
    _findclose(h);
    return 0;
#else
    DIR *d = opendir(dir);
    if (!d)
        return -1;
    struct dirent *e;
    while ((e = readdir(d)) != NULL)
        if (strcmp(e->d_name, ".") && strcmp(e->d_name, ".."))
            fn(e->d_name, u);
    closedir(d);
    return 0;
#endif
}

typedef struct namelist {
    char **v;
    int n, cap;
} namelist;

static void nl_add(const char *name, void *u)
{
    namelist *l = (namelist *)u;
    if (l->n == l->cap) {
        int nc = l->cap ? l->cap * 2 : 16;
        char **nv = (char **)realloc(l->v, (size_t)nc * sizeof *nv);
        if (!nv)
            return;
        l->v = nv;
        l->cap = nc;
    }
    l->v[l->n++] = strdup(name);
}

static int nl_cmp(const void *a, const void *b) { return strcmp(*(char *const *)a, *(char *const *)b); }

static void nl_free(namelist *l)
{
    for (int i = 0; i < l->n; i++)
        free(l->v[i]);
    free(l->v);
    memset(l, 0, sizeof *l);
}

static void h_rmtree_contents(const char *dir)
{
    namelist l = {0};
    h_list(dir, nl_add, &l);
    for (int i = 0; i < l.n; i++) {
        char p[HOST_PATH_MAX];
        snprintf(p, sizeof p, "%s/%s", dir, l.v[i]);
        if (h_kind(p, NULL) == 1) {
            h_rmtree_contents(p);
            h_rmdir(p);
        } else {
            remove(p);
        }
    }
    nl_free(&l);
}

/* atomic replace of dst by src (both on the same volume) */
static int h_replace(const char *src, const char *dst)
{
#ifdef _WIN32
    return MoveFileExA(src, dst, MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH) ? 0 : -1;
#else
    return rename(src, dst);
#endif
}

/* Crash-safe file write: <path>%~tmp, then renamed over <path>. A crash of the
 * process leaves either the old or the new file (and maybe a stale temp, which the
 * next load deletes). durable = 1 also forces the temp file to the disk before the
 * rename (survives power loss too), which costs 0.1-0.7 s per file on a spinning disk
 * while the game waits. */
static mccard_io_stats IO; /* host I/O counters (RG_MC_TRACE, libmc.c) */

void mccard_get_io_stats(mccard_io_stats *out) { *out = IO; }

static int h_write_atomic(const char *path, const void *data, size_t n, int durable)
{
    IO.files_written++;
    IO.bytes_written += (uint32_t)n;
    char tmp[HOST_PATH_MAX + 8];
    snprintf(tmp, sizeof tmp, "%s%s", path, TMP_SUFFIX);
    FILE *f = fopen(tmp, "wb");
    if (!f)
        return -1;
    int ok = (n == 0 || fwrite(data, 1, n, f) == n) && fflush(f) == 0;
#ifdef _WIN32
    if (ok && durable)
        ok = _commit(_fileno(f)) == 0;
#else
    if (ok && durable)
        ok = fsync(fileno(f)) == 0;
#endif
    if (fclose(f) != 0)
        ok = 0;
    if (!ok || h_replace(tmp, path) != 0) {
        remove(tmp);
        return -1;
    }
    return 0;
}

/* whole host file into memory (NULL + *n = 0 when missing or empty) */
static uint8_t *h_slurp(const char *path, uint32_t *n)
{
    IO.files_read++;
    *n = 0;
    FILE *f = fopen(path, "rb");
    if (!f)
        return NULL;
    uint8_t *b = NULL;
    uint32_t len = 0, cap = 0;
    for (;;) {
        if (len == cap) {
            uint32_t nc = cap ? cap * 2 : 65536;
            uint8_t *nb = (uint8_t *)realloc(b, nc);
            if (!nb)
                break;
            b = nb;
            cap = nc;
        }
        size_t got = fread(b + len, 1, cap - len, f);
        if (got == 0)
            break;
        len += (uint32_t)got;
    }
    fclose(f);
    *n = len;
    return b;
}

/* growable text buffer (metadata, index) */
typedef struct sbuf {
    char *p;
    size_t n, cap;
} sbuf;
static void sb_printf(sbuf *b, const char *fmt, ...)
{
    va_list ap;
    for (;;) {
        size_t room = b->cap - b->n;
        va_start(ap, fmt);
        int k = b->p ? vsnprintf(b->p + b->n, room, fmt, ap) : -1;
        va_end(ap);
        if (k >= 0 && (size_t)k < room) {
            b->n += (size_t)k;
            return;
        }
        size_t nc = b->cap ? b->cap * 2 : 4096;
        if (k >= 0 && b->n + (size_t)k + 1 > nc)
            nc = b->n + (size_t)k + 1;
        char *np = (char *)realloc(b->p, nc);
        if (!np)
            return;
        b->p = np;
        b->cap = nc;
    }
}

static void h_mkdirs(const char *path)
{
    char t[HOST_PATH_MAX];
    snprintf(t, sizeof t, "%s", path);
    for (char *p = t + 1; *p; p++) {
        if (*p == '/' || *p == '\\') {
            char c = *p;
            *p = 0;
            if (!(p > t && p[-1] == ':'))
                h_mkdir(t);
            *p = c;
        }
    }
    h_mkdir(t);
}

/* ---- name encoding: PS2 name <-> host name ---------------------------------------- */
static const char HEX[] = "0123456789ABCDEF";

static int reserved_base(const char *n)
{
    static const char *k[] = {"CON", "PRN", "AUX", "NUL"};
    char b[8];
    int i = 0;
    while (n[i] && n[i] != '.' && i < 7) {
        b[i] = (char)toupper((unsigned char)n[i]);
        i++;
    }
    if (n[i] && n[i] != '.')
        return 0;
    b[i] = 0;
    for (int j = 0; j < 4; j++)
        if (!strcmp(b, k[j]))
            return 1;
    if (i == 4 && (!strncmp(b, "COM", 3) || !strncmp(b, "LPT", 3)) && b[3] >= '1' && b[3] <= '9')
        return 1;
    return 0;
}

/* meta = 1 also escapes spaces (metadata lines are space separated) */
static void enc_name(const char *in, char *out, int meta)
{
    int n = (int)strlen(in);
    int o = 0;
    int resv = reserved_base(in);
    for (int i = 0; i < n; i++) {
        unsigned char b = (unsigned char)in[i];
        int esc = b < 0x20 || b >= 0x7F || strchr("<>:\"/\\|?*%", b) != NULL;
        if (meta && b == ' ')
            esc = 1;
        if (i == n - 1 && (b == '.' || b == ' '))
            esc = 1;
        if (i == 0 && resv)
            esc = 1;
        if (esc) {
            out[o++] = '%';
            out[o++] = HEX[b >> 4];
            out[o++] = HEX[b & 15];
        } else {
            out[o++] = (char)b;
        }
    }
    out[o] = 0;
}

static int hexv(char c)
{
    if (c >= '0' && c <= '9')
        return c - '0';
    c = (char)toupper((unsigned char)c);
    if (c >= 'A' && c <= 'F')
        return c - 'A' + 10;
    return -1;
}

static void dec_name(const char *in, char *out, int outlen)
{
    int o = 0;
    for (int i = 0; in[i] && o < outlen - 1; i++) {
        if (in[i] == '%' && hexv(in[i + 1]) >= 0 && hexv(in[i + 2]) >= 0) {
            out[o++] = (char)(hexv(in[i + 1]) * 16 + hexv(in[i + 2]));
            i += 2;
        } else {
            out[o++] = in[i];
        }
    }
    out[o] = 0;
}

/* encode every component of a card path ("/A/B" -> "/A/B" escaped) */
static void enc_path(const char *path, char *out, int outlen, int meta)
{
    int o = 0;
    const char *p = path;
    out[0] = 0;
    while (*p) {
        if (*p == '/') {
            if (o < outlen - 1)
                out[o++] = '/';
            p++;
            continue;
        }
        char comp[MC_PATH_MAX], enc[MC_PATH_MAX * 3];
        int n = 0;
        while (*p && *p != '/' && n < MC_PATH_MAX - 1)
            comp[n++] = *p++;
        comp[n] = 0;
        enc_name(comp, enc, meta);
        int l = (int)strlen(enc);
        if (o + l >= outlen - 1)
            break;
        memcpy(out + o, enc, (size_t)l);
        o += l;
    }
    out[o] = 0;
}

/* ---- card state ------------------------------------------------------------------- */
typedef struct ment {
    char *path; /* absolute card path; "/" = root */
    int is_dir;
    uint16_t attr;
    mc_datetime ctime, mtime;
    uint32_t size;
    uint32_t seq;
} ment;

typedef struct mcard {
    int present, formatted, changed;
    char host[HOST_PATH_MAX];
    char meta[HOST_PATH_MAX];
    ment *e;
    int n, cap;
    uint32_t next_seq;
    char cwd[MC_PATH_MAX];
    mc_dirent *it;
    int it_n, it_pos;
} mcard;

typedef struct mfd {
    int used;
    int port;
    char *path;
    FILE *f;        /* read-only descriptors */
    uint8_t *buf;   /* write descriptors: the file's contents, committed on flush / close */
    uint32_t len, cap;
    int wdirty;     /* buf differs from the host file */
    int gone;       /* the card was ejected under it: every call fails with NOCARD */
    int mode;
    uint32_t pos;
    int dirty;      /* metadata changed */
} mfd;

#define MAX_FDS_CAP 64

static struct {
    mccard_config cfg;
    char root[HOST_PATH_MAX];
    char broot[HOST_PATH_MAX];
    mcard card[MC_PORTS];
    mfd fd[MAX_FDS_CAP];
    int inited;
    struct {
        int port, countdown, result;
    } fault;
} M;

void mccard_default_config(mccard_config *c)
{
    memset(c, 0, sizeof *c);
    c->slot_policy[0] = MC_SLOT_AUTO;
    c->slot_policy[1] = MC_SLOT_IF_EXISTS;
    c->free_clusters = 8000;
    c->max_fds = 16;
    c->backup_keep = 5;
}

const char *mccard_slot_name(int port)
{
    return port == 1 ? "card2" : "card1";
}

static void now_time(mc_datetime *t)
{
    if (M.cfg.clock) {
        M.cfg.clock(M.cfg.clock_user, t);
        return;
    }
    memset(t, 0, sizeof *t);
    t->year = 2006;
    t->month = 1;
    t->day = 31;
    t->hour = 12;
}

static void card_clear(mcard *c)
{
    for (int i = 0; i < c->n; i++)
        free(c->e[i].path);
    free(c->e);
    free(c->it);
    c->e = NULL;
    c->n = c->cap = 0;
    c->it = NULL;
    c->it_n = c->it_pos = 0;
}

static ment *find(mcard *c, const char *path)
{
    for (int i = 0; i < c->n; i++)
        if (!strcmp(c->e[i].path, path))
            return &c->e[i];
    return NULL;
}

static ment *add_ent(mcard *c, const char *path, int is_dir)
{
    if (c->n == c->cap) {
        int nc = c->cap ? c->cap * 2 : 32;
        ment *ne = (ment *)realloc(c->e, (size_t)nc * sizeof *ne);
        if (!ne)
            return NULL;
        c->e = ne;
        c->cap = nc;
    }
    ment *m = &c->e[c->n++];
    memset(m, 0, sizeof *m);
    m->path = strdup(path);
    m->is_dir = is_dir;
    m->attr = (uint16_t)(is_dir ? MC_ATTR_DEFAULT_DIR : MC_ATTR_DEFAULT_FILE);
    now_time(&m->ctime);
    m->mtime = m->ctime;
    m->seq = c->next_seq++;
    return m;
}

static void del_ent(mcard *c, ment *m)
{
    int i = (int)(m - c->e);
    free(m->path);
    memmove(&c->e[i], &c->e[i + 1], (size_t)(c->n - i - 1) * sizeof *m);
    c->n--;
}

static void parent_of(const char *path, char *out)
{
    snprintf(out, MC_PATH_MAX, "%s", path);
    char *s = strrchr(out, '/');
    if (!s || s == out)
        strcpy(out, "/");
    else
        *s = 0;
}

static const char *base_of(const char *path)
{
    const char *s = strrchr(path, '/');
    return s ? s + 1 : path;
}

static int is_child(const char *dir, const char *path)
{
    if (!strcmp(path, "/"))
        return 0;
    char par[MC_PATH_MAX];
    parent_of(path, par);
    return !strcmp(par, dir);
}

static int nchildren(mcard *c, const char *dir)
{
    int k = 0;
    for (int i = 0; i < c->n; i++)
        if (is_child(dir, c->e[i].path))
            k++;
    return k;
}

static uint32_t used_clusters(mcard *c)
{
    uint32_t used = 0;
    for (int i = 0; i < c->n; i++) {
        ment *m = &c->e[i];
        if (!m->is_dir) {
            used += (m->size + 1023u) / 1024u;
        } else {
            uint32_t ents = 2u + (uint32_t)nchildren(c, m->path);
            uint32_t cl = (ents + 1u) / 2u;
            used += strcmp(m->path, "/") ? cl : cl - 1u;
        }
    }
    return used;
}

static uint32_t card_free(mcard *c)
{
    if (!c->present || !c->formatted)
        return 0;
    uint32_t u = used_clusters(c);
    return u >= M.cfg.free_clusters ? 0 : M.cfg.free_clusters - u;
}

/* clusters a new entry in `dir` costs the directory itself */
static uint32_t dir_growth(mcard *c, const char *dir)
{
    int ents = 2 + nchildren(c, dir);
    return (ents % 2 == 0) ? 1u : 0u;
}

/* ---- metadata ---------------------------------------------------------------------- */
static void dt_hex(const mc_datetime *t, char *out)
{
    uint8_t b[8];
    memcpy(b, t, 8);
    for (int i = 0; i < 8; i++) {
        out[i * 2] = HEX[b[i] >> 4];
        out[i * 2 + 1] = HEX[b[i] & 15];
    }
    out[16] = 0;
}

static int hex_dt(const char *s, mc_datetime *t)
{
    uint8_t b[8];
    for (int i = 0; i < 8; i++) {
        int h = hexv(s[i * 2]), l = hexv(s[i * 2 + 1]);
        if (h < 0 || l < 0)
            return -1;
        b[i] = (uint8_t)(h * 16 + l);
    }
    memcpy(t, b, 8);
    return 0;
}

static void host_of(int port, const char *card_path, char *out);

/* icon.sys title (offset 0xC0, Shift-JIS, second line at the byte offset in +6) as
 * printable ASCII: full-width letters, digits and common punctuation map to ASCII,
 * anything else to '?'. */
static void icon_title(const uint8_t *s, uint32_t n, char *out, size_t outlen)
{
    size_t o = 0;
    out[0] = 0;
    if (n < 0x104 || memcmp(s, "PS2D", 4) != 0)
        return;
    unsigned brk = (unsigned)(s[6] | s[7] << 8);
    const uint8_t *t = s + 0xC0;
    for (unsigned i = 0; i < 0x44 && t[i] && o + 5 < outlen;) {
        if (i == brk && i && o) {
            while (o && out[o - 1] == ' ')
                o--;
            out[o++] = ' ', out[o++] = '/', out[o++] = ' ';
        }
        unsigned b = t[i];
        if (b < 0x80) {
            out[o++] = (char)(b >= 0x20 && b < 0x7F ? b : '?');
            i++;
            continue;
        }
        if (i + 1 >= 0x44)
            break;
        unsigned w = b << 8 | t[i + 1];
        char ch = '?';
        if (w == 0x8140)
            ch = ' ';
        else if (w >= 0x824F && w <= 0x8258)
            ch = (char)('0' + w - 0x824F);
        else if (w >= 0x8260 && w <= 0x8279)
            ch = (char)('A' + w - 0x8260);
        else if (w >= 0x8281 && w <= 0x829A)
            ch = (char)('a' + w - 0x8281);
        else {
            static const struct {
                uint16_t w;
                char c;
            } P[] = {{0x8141, ','}, {0x8142, '.'}, {0x8143, ','}, {0x8144, '.'}, {0x8146, ':'},
                     {0x8147, ';'}, {0x8148, '?'}, {0x8149, '!'}, {0x815B, '-'}, {0x815C, '-'},
                     {0x815D, '-'}, {0x815E, '/'}, {0x8160, '~'}, {0x8165, '\''}, {0x8166, '\''},
                     {0x8167, '"'}, {0x8168, '"'}, {0x8169, '('}, {0x816A, ')'}, {0x816D, '['},
                     {0x816E, ']'}, {0x817B, '+'}, {0x817C, '-'}, {0x8181, '='}, {0x8183, '<'},
                     {0x8184, '>'}, {0x8190, '$'}, {0x8193, '%'}, {0x8194, '#'}, {0x8195, '&'},
                     {0x8196, '*'}, {0x8197, '@'}};
            for (size_t k = 0; k < sizeof P / sizeof P[0]; k++)
                if (P[k].w == w)
                    ch = P[k].c;
        }
        out[o++] = ch;
        i += 2;
    }
    while (o && out[o - 1] == ' ')
        o--;
    out[o] = 0;
}

/* <root>/card<N>.txt: one line per top-level directory, for people browsing saves */
static void save_index(int port)
{
    mcard *c = &M.card[port];
    char path[HOST_PATH_MAX + 8];
    snprintf(path, sizeof path, "%s/%s.txt", M.root, mccard_slot_name(port));
    sbuf b = {0};
    sb_printf(&b, "# Memory card slot %d (%s/). Written by the port on every change; edits are lost.\n",
              port + 1, mccard_slot_name(port));
    if (!c->formatted) {
        sb_printf(&b, "# (unformatted)\n");
    } else {
        sb_printf(&b, "# free %u KB of %u KB\n", (unsigned)card_free(c), (unsigned)M.cfg.free_clusters);
        sb_printf(&b, "# directory                        modified (card clock)  size     title (icon.sys)\n");
        for (int i = 0; i < c->n; i++) {
            ment *m = &c->e[i];
            if (!m->is_dir || !is_child("/", m->path))
                continue;
            uint32_t kb = 0;
            char title[160] = "";
            for (int j = 0; j < c->n; j++)
                if (is_child(m->path, c->e[j].path) && !c->e[j].is_dir)
                    kb += (c->e[j].size + 1023u) / 1024u;
            char ip[MC_PATH_MAX + 16], hp[HOST_PATH_MAX];
            snprintf(ip, sizeof ip, "%s/icon.sys", m->path);
            if (find(c, ip)) {
                host_of(port, ip, hp);
                uint32_t n;
                uint8_t *d = h_slurp(hp, &n);
                if (d)
                    icon_title(d, n, title, sizeof title);
                free(d);
            } else {
                snprintf(title, sizeof title, "(no icon.sys: broken or unfinished save)");
            }
            const mc_datetime *t = &m->mtime;
            sb_printf(&b, "%-34s %04u-%02u-%02u %02u:%02u:%02u    %4u KB  %s\n", base_of(m->path), t->year,
                      t->month, t->day, t->hour, t->min, t->sec, (unsigned)kb, title);
        }
    }
    if (b.p)
        h_write_atomic(path, b.p, b.n, 0);
    free(b.p);
}

static void save_meta(int port)
{
    mcard *c = &M.card[port];
    if (!c->present)
        return;
    IO.meta_saves++;
    sbuf b = {0};
    sb_printf(&b, "RGMC 1\nformatted %d\nseq %u\n", c->formatted, (unsigned)c->next_seq);
    for (int i = 0; i < c->n; i++) {
        ment *m = &c->e[i];
        char ct[17], mt[17], ep[MC_PATH_MAX * 3];
        dt_hex(&m->ctime, ct);
        dt_hex(&m->mtime, mt);
        enc_path(m->path, ep, sizeof ep, 1);
        sb_printf(&b, "E %u %c %04X %s %s %s\n", (unsigned)m->seq, m->is_dir ? 'd' : 'f', m->attr, ct, mt, ep);
    }
    if (b.p)
        h_write_atomic(c->meta, b.p, b.n, 0);
    free(b.p);
    save_index(port);
}

typedef struct meta_rec {
    char *path;
    uint32_t seq;
    uint16_t attr;
    mc_datetime ct, mt;
} meta_rec;

typedef struct meta_set {
    meta_rec *v;
    int n, cap;
    int formatted; /* -1 = no file */
    uint32_t seq;
} meta_set;

static void load_meta(const char *file, meta_set *ms)
{
    memset(ms, 0, sizeof *ms);
    ms->formatted = -1;
    FILE *f = fopen(file, "rb");
    if (!f)
        return;
    char line[MC_PATH_MAX * 3 + 128];
    while (fgets(line, sizeof line, f)) {
        size_t l = strlen(line);
        while (l && (line[l - 1] == '\n' || line[l - 1] == '\r'))
            line[--l] = 0;
        int v;
        unsigned u;
        if (sscanf(line, "formatted %d", &v) == 1) {
            ms->formatted = v ? 1 : 0;
        } else if (sscanf(line, "seq %u", &u) == 1) {
            ms->seq = u;
        } else if (line[0] == 'E' && line[1] == ' ') {
            unsigned seq, attr;
            char kind, ct[32], mt[32], ep[MC_PATH_MAX * 3];
            if (sscanf(line, "E %u %c %x %31s %31s %3071s", &seq, &kind, &attr, ct, mt, ep) != 6)
                continue;
            if (ms->n == ms->cap) {
                int nc = ms->cap ? ms->cap * 2 : 32;
                meta_rec *nv = (meta_rec *)realloc(ms->v, (size_t)nc * sizeof *nv);
                if (!nv)
                    break;
                ms->v = nv;
                ms->cap = nc;
            }
            meta_rec *r = &ms->v[ms->n];
            memset(r, 0, sizeof *r);
            char dp[MC_PATH_MAX];
            dec_name(ep, dp, sizeof dp);
            r->path = strdup(dp);
            r->seq = seq;
            r->attr = (uint16_t)attr;
            if (hex_dt(ct, &r->ct) || hex_dt(mt, &r->mt)) {
                free(r->path);
                continue;
            }
            ms->n++;
        }
    }
    fclose(f);
}

static void free_meta(meta_set *ms)
{
    for (int i = 0; i < ms->n; i++)
        free(ms->v[i].path);
    free(ms->v);
}

static meta_rec *meta_find(meta_set *ms, const char *path)
{
    for (int i = 0; i < ms->n; i++)
        if (!strcmp(ms->v[i].path, path))
            return &ms->v[i];
    return NULL;
}

static void scan_dir(mcard *c, meta_set *ms, const char *card_dir, const char *host_dir)
{
    namelist l = {0};
    h_list(host_dir, nl_add, &l);
    qsort(l.v, (size_t)l.n, sizeof *l.v, nl_cmp);
    for (int i = 0; i < l.n; i++) {
        char hp[HOST_PATH_MAX], name[MC_PATH_MAX], cp[MC_PATH_MAX];
        snprintf(hp, sizeof hp, "%s/%s", host_dir, l.v[i]);
        if (strstr(l.v[i], "%~")) { /* a crash-safe write that never finished */
            if (h_kind(hp, NULL) == 1) {
                h_rmtree_contents(hp);
                h_rmdir(hp);
            } else {
                remove(hp);
            }
            continue;
        }
        dec_name(l.v[i], name, sizeof name);
        if (strlen(name) >= MC_NAME_MAX || strchr(name, '/'))
            continue;
        snprintf(cp, sizeof cp, "%s/%s", strcmp(card_dir, "/") ? card_dir : "", name);
        long long sz = 0;
        int k = h_kind(hp, &sz);
        if (k < 0)
            continue;
        ment *m = add_ent(c, cp, k == 1);
        if (!m)
            continue;
        m->size = k == 1 ? 0 : (uint32_t)sz;
        meta_rec *r = meta_find(ms, cp);
        if (r) {
            m->seq = r->seq;
            m->attr = r->attr;
            m->ctime = r->ct;
            m->mtime = r->mt;
            m->seq = r->seq;
        }
        if (k == 1)
            scan_dir(c, ms, cp, hp);
    }
    nl_free(&l);
}

static int commit_fd(mfd *d);

enum { FD_COMMIT, FD_GONE, FD_DROP };
/* FD_COMMIT: write pending data and free (shutdown); FD_GONE: drop pending data and
 * keep the descriptor as a dead handle (eject); FD_DROP: drop and free (format, reload) */
static void close_port_fds(int port, int how)
{
    for (int i = 0; i < MAX_FDS_CAP; i++) {
        mfd *d = &M.fd[i];
        if (!d->used || !(port < 0 || d->port == port))
            continue;
        if (how == FD_COMMIT && !d->gone)
            commit_fd(d);
        if (d->f)
            fclose(d->f);
        free(d->buf);
        if (how == FD_GONE) {
            d->f = NULL;
            d->buf = NULL;
            d->len = d->cap = 0;
            d->wdirty = 0;
            d->gone = 1;
            continue;
        }
        free(d->path);
        memset(d, 0, sizeof *d);
    }
}

static int load_card(int port, int policy)
{
    mcard *c = &M.card[port];
    card_clear(c);
    memset(c, 0, sizeof *c);
    strcpy(c->cwd, "/");
    snprintf(c->host, sizeof c->host, "%s/%s", M.root, mccard_slot_name(port));
    snprintf(c->meta, sizeof c->meta, "%s/%s.card", M.root, mccard_slot_name(port));
    {
        /* earlier layout: <root>/slot0 (card in slot 1), slot0.card */
        char old[HOST_PATH_MAX], oldm[HOST_PATH_MAX];
        snprintf(old, sizeof old, "%s/slot%d", M.root, port);
        snprintf(oldm, sizeof oldm, "%s/slot%d.card", M.root, port);
        if (h_kind(c->host, NULL) < 0 && h_kind(old, NULL) == 1 && rename(old, c->host) == 0 &&
            h_kind(c->meta, NULL) < 0 && h_kind(oldm, NULL) == 0)
            rename(oldm, c->meta);
    }
    if (policy == MC_SLOT_EMPTY)
        return 0;
    int exists = h_kind(c->host, NULL) == 1;
    if (!exists) {
        if (policy == MC_SLOT_IF_EXISTS)
            return 0;
        h_mkdirs(c->host);
        if (h_kind(c->host, NULL) != 1)
            return -1;
        c->present = 1;
        c->formatted = policy == MC_SLOT_UNFORMATTED ? 0 : 1;
        c->changed = 1;
        add_ent(c, "/", 1);
        save_meta(port);
        return 0;
    }
    c->present = 1;
    c->changed = 1;
    meta_set ms;
    load_meta(c->meta, &ms);
    c->formatted = ms.formatted < 0 ? 1 : ms.formatted;
    c->next_seq = ms.seq;
    ment *root = add_ent(c, "/", 1);
    meta_rec *rr = meta_find(&ms, "/");
    if (root && rr) {
        root->attr = rr->attr;
        root->ctime = rr->ct;
        root->mtime = rr->mt;
        root->seq = rr->seq;
    }
    if (c->formatted)
        scan_dir(c, &ms, "/", c->host);
    /* entries found on the host without metadata get fresh sequence numbers after
     * every recorded one (scan order = name order) */
    uint32_t mx = 0;
    for (int i = 0; i < ms.n; i++)
        if (ms.v[i].seq + 1 > mx)
            mx = ms.v[i].seq + 1;
    c->next_seq = ms.seq > mx ? ms.seq : mx; /* add_ent above counted scanned entries too */
    for (int i = 0; i < c->n; i++)
        if (!meta_find(&ms, c->e[i].path))
            c->e[i].seq = c->next_seq++;
    free_meta(&ms);
    save_meta(port);
    return 0;
}

int mccard_init(const mccard_config *cfg)
{
    if (M.inited)
        mccard_shutdown();
    memset(&M, 0, sizeof M);
    if (cfg)
        M.cfg = *cfg;
    else
        mccard_default_config(&M.cfg);
    if (M.cfg.max_fds <= 0 || M.cfg.max_fds > MAX_FDS_CAP)
        M.cfg.max_fds = MAX_FDS_CAP;
    const char *root = M.cfg.root;
    if (!root || !*root)
        root = getenv("RG_SAVES");
    if (!root || !*root)
        root = "saves";
    snprintf(M.root, sizeof M.root, "%s", root);
    for (char *p = M.root; *p; p++)
        if (*p == '\\')
            *p = '/';
    size_t rl = strlen(M.root);
    while (rl > 1 && M.root[rl - 1] == '/')
        M.root[--rl] = 0;
    M.cfg.root = M.root;
    if (M.cfg.backup_root && *M.cfg.backup_root)
        snprintf(M.broot, sizeof M.broot, "%s", M.cfg.backup_root);
    else
        snprintf(M.broot, sizeof M.broot, "%s/backups", M.root);
    M.cfg.backup_root = M.broot;
    {
        const char *dv = getenv("RG_MC_DURABLE");
        if (dv && *dv)
            M.cfg.durable = atoi(dv) != 0;
    }
    for (int p = 0; p < MC_PORTS; p++) {
        char ev[16];
        snprintf(ev, sizeof ev, "RG_MC_SLOT%d", p + 1);
        const char *v = getenv(ev);
        if (!v || !*v)
            continue;
        if (!strcmp(v, "auto"))
            M.cfg.slot_policy[p] = MC_SLOT_AUTO;
        else if (!strcmp(v, "ifexists"))
            M.cfg.slot_policy[p] = MC_SLOT_IF_EXISTS;
        else if (!strcmp(v, "none") || !strcmp(v, "empty"))
            M.cfg.slot_policy[p] = MC_SLOT_EMPTY;
        else if (!strcmp(v, "unformatted"))
            M.cfg.slot_policy[p] = MC_SLOT_UNFORMATTED;
        else
            fprintf(stderr, "mccard: %s=%s ignored (auto | ifexists | none | unformatted)\n", ev, v);
    }
    M.inited = 1;
    int r = 0;
    for (int p = 0; p < MC_PORTS; p++)
        r |= load_card(p, M.cfg.slot_policy[p]);
    return r;
}

static void ensure(void)
{
    if (!M.inited)
        mccard_init(NULL);
}

void mccard_shutdown(void)
{
    if (!M.inited)
        return;
    close_port_fds(-1, FD_COMMIT);
    for (int p = 0; p < MC_PORTS; p++) {
        save_meta(p);
        card_clear(&M.card[p]);
    }
    M.inited = 0;
}

int mccard_inited(void) { return M.inited; }

const mccard_config *mccard_get_config(void)
{
    ensure();
    return &M.cfg;
}

const char *mccard_root(void)
{
    ensure();
    return M.root;
}

int mccard_insert(int port, int policy)
{
    ensure();
    if (port < 0 || port >= MC_PORTS)
        return -1;
    close_port_fds(port, FD_DROP); /* handles from before the swap are dead */
    return load_card(port, policy);
}

void mccard_eject(int port)
{
    ensure();
    if (port < 0 || port >= MC_PORTS)
        return;
    close_port_fds(port, FD_GONE);
    save_meta(port);
    card_clear(&M.card[port]);
    memset(&M.card[port], 0, sizeof M.card[port]);
    strcpy(M.card[port].cwd, "/");
}

int mccard_present(int port)
{
    ensure();
    return port >= 0 && port < MC_PORTS && M.card[port].present;
}

int mccard_formatted(int port)
{
    ensure();
    return mccard_present(port) && M.card[port].formatted;
}

uint32_t mccard_free(int port)
{
    ensure();
    if (port < 0 || port >= MC_PORTS)
        return 0;
    return card_free(&M.card[port]);
}

int mccard_open_count(void)
{
    int k = 0;
    for (int i = 0; i < MAX_FDS_CAP; i++)
        k += M.fd[i].used;
    return k;
}

void mccard_inject_fault(int port, int after, int result)
{
    M.fault.port = port;
    M.fault.countdown = after > 0 ? after : 0;
    M.fault.result = result;
}

/* every card operation passes here first; nonzero = the injected failure */
static int fault_hit(int port)
{
    if (M.fault.countdown <= 0 || port != M.fault.port)
        return 0;
    if (--M.fault.countdown > 0)
        return 0;
    if (M.fault.result == MC_RES_NOCARD)
        mccard_eject(port);
    return M.fault.result;
}

/* ---- paths -------------------------------------------------------------------------- */
/* Normalise `in` (absolute, or relative to the port's cwd) into `out`. */
static int resolve(mcard *c, const char *in, char *out)
{
    char tmp[MC_PATH_MAX * 2];
    if (in[0] == '/')
        snprintf(tmp, sizeof tmp, "%s", in);
    else
        snprintf(tmp, sizeof tmp, "%s/%s", c->cwd, in);
    char *comps[MC_PATH_MAX / 2];
    int n = 0;
    char *save = tmp;
    while (*save) {
        while (*save == '/')
            save++;
        if (!*save)
            break;
        char *s = save;
        while (*save && *save != '/')
            save++;
        if (*save)
            *save++ = 0;
        if (!strcmp(s, "."))
            continue;
        if (!strcmp(s, "..")) {
            if (n > 0)
                n--;
            continue;
        }
        if (strlen(s) >= MC_NAME_MAX)
            return MC_RES_NOENTRY;
        if (n < (int)(sizeof comps / sizeof comps[0]))
            comps[n++] = s;
    }
    if (n == 0) {
        strcpy(out, "/");
        return 0;
    }
    int o = 0;
    for (int i = 0; i < n; i++) {
        int l = (int)strlen(comps[i]);
        if (o + l + 2 >= MC_PATH_MAX)
            return MC_RES_NOENTRY;
        out[o++] = '/';
        memcpy(out + o, comps[i], (size_t)l);
        o += l;
    }
    out[o] = 0;
    return 0;
}

static int card_check(int port, mcard **out)
{
    ensure();
    if (port < 0 || port >= MC_PORTS)
        return MC_RES_NOCARD;
    mcard *c = &M.card[port];
    if (!c->present)
        return MC_RES_NOCARD;
    if (!c->formatted)
        return MC_RES_NOFORMAT;
    *out = c;
    return 0;
}

int mccard_host_path(int port, const char *card_path, char *out, int outlen)
{
    ensure();
    if (port < 0 || port >= MC_PORTS)
        return -1;
    char enc[MC_PATH_MAX * 3];
    enc_path(card_path, enc, sizeof enc, 0);
    snprintf(out, (size_t)outlen, "%s/%s%s", M.root, mccard_slot_name(port), strcmp(enc, "/") ? enc : "");
    return 0;
}

/* ---- backups ------------------------------------------------------------------------- */
int mccard_backup_dir(int port, const char *top, char *out, int outlen)
{
    ensure();
    if (port < 0 || port >= MC_PORTS || !top)
        return -1;
    char enc[MC_PATH_MAX * 3];
    enc_path(top, enc, sizeof enc, 0);
    snprintf(out, (size_t)outlen, "%s/%s%s", M.broot, mccard_slot_name(port), enc);
    return 0;
}

/* sorted names of the finished snapshots in a backup directory */
static void backup_list(const char *bdir, namelist *l)
{
    namelist all = {0};
    h_list(bdir, nl_add, &all);
    for (int i = 0; i < all.n; i++) {
        char p[HOST_PATH_MAX];
        snprintf(p, sizeof p, "%s/%s", bdir, all.v[i]);
        if (strstr(all.v[i], "%~")) { /* unfinished snapshot */
            h_rmtree_contents(p);
            h_rmdir(p);
            continue;
        }
        if (h_kind(p, NULL) == 1)
            nl_add(all.v[i], l);
    }
    nl_free(&all);
    if (l->n > 1)
        qsort(l->v, (size_t)l->n, sizeof *l->v, nl_cmp);
}

int mccard_backup_count(int port, const char *top)
{
    char bdir[HOST_PATH_MAX];
    if (mccard_backup_dir(port, top, bdir, sizeof bdir))
        return 0;
    namelist l = {0};
    backup_list(bdir, &l);
    int n = l.n;
    nl_free(&l);
    return n;
}

static int same_file(const char *a, const char *b)
{
    uint32_t na, nb;
    uint8_t *da = h_slurp(a, &na), *db = h_slurp(b, &nb);
    int same = (da || !na) && (db || !nb) && na == nb && (na == 0 || memcmp(da, db, na) == 0);
    free(da);
    free(db);
    return same;
}

/* Snapshot the save directory `top` (a child of the root) before the first change to
 * it, when it holds a finished save: icon.sys plus at least two other files, no file
 * in it open for writing, and contents unlike the newest snapshot. The game's own
 * save renames icon.sys away first (McSaveStep_374110), so exactly one snapshot is
 * taken per save, holding the previous one. Files only (PS2 saves have no
 * subdirectories); the card metadata is not copied. */
static void backup_top(int port, mcard *c, const char *top)
{
    if (M.cfg.backup_keep <= 0)
        return;
    ment *t = find(c, top);
    if (!t || !t->is_dir || !is_child("/", top))
        return;
    size_t tl = strlen(top);
    for (int i = 0; i < MAX_FDS_CAP; i++) {
        mfd *d = &M.fd[i];
        if (d->used && !d->gone && d->port == port && (d->mode & MC_O_WRONLY) &&
            !strncmp(d->path, top, tl) && d->path[tl] == '/')
            return;
    }
    int has_icon = 0, others = 0;
    for (int i = 0; i < c->n; i++) {
        if (c->e[i].is_dir || !is_child(top, c->e[i].path))
            continue;
        if (!strcmp(base_of(c->e[i].path), "icon.sys"))
            has_icon = 1;
        else
            others++;
    }
    if (!has_icon || others < 2)
        return;
    char bdir[HOST_PATH_MAX];
    mccard_backup_dir(port, top, bdir, sizeof bdir);
    namelist l = {0};
    backup_list(bdir, &l);
    if (l.n > 0) { /* unchanged since the newest snapshot? */
        char snap[HOST_PATH_MAX];
        snprintf(snap, sizeof snap, "%s/%s", bdir, l.v[l.n - 1]);
        namelist sf = {0};
        h_list(snap, nl_add, &sf);
        int same = sf.n == others + 1;
        for (int i = 0; same && i < c->n; i++) {
            if (c->e[i].is_dir || !is_child(top, c->e[i].path))
                continue;
            char hp[HOST_PATH_MAX], bp[HOST_PATH_MAX * 2], en[MC_NAME_MAX * 3];
            host_of(port, c->e[i].path, hp);
            enc_name(base_of(c->e[i].path), en, 0);
            snprintf(bp, sizeof bp, "%s/%s", snap, en);
            same = same_file(hp, bp);
        }
        nl_free(&sf);
        if (same) {
            nl_free(&l);
            return;
        }
    }
    /* <stamp> = host local time; "_002", "_003" ... when two land in one second (the
     * names sort in time order) */
    char stamp[64], snap[HOST_PATH_MAX], tmp[HOST_PATH_MAX + 8];
    time_t now = time(NULL);
    struct tm tmv;
#ifdef _WIN32
    localtime_s(&tmv, &now);
#else
    localtime_r(&now, &tmv);
#endif
    strftime(stamp, sizeof stamp, "%Y-%m-%d_%H%M%S", &tmv);
    {
        /* the new name must sort after the newest one (several per second, a clock
         * set back) */
        const char *nw = l.n ? l.v[l.n - 1] : "";
        char name[160];
        snprintf(name, sizeof name, "%s", stamp);
        if (strcmp(name, nw) <= 0) {
            size_t sl = strlen(stamp);
            int same = !strncmp(nw, stamp, sl);
            int k = same && nw[sl] == '_' ? atoi(nw + sl + 1) : 1;
            snprintf(name, sizeof name, "%s_%03d", same ? stamp : nw, k + 1);
        }
        snprintf(snap, sizeof snap, "%s/%s", bdir, name);
    }
    snprintf(tmp, sizeof tmp, "%s%s", snap, TMP_SUFFIX);
    IO.backups++;
    h_mkdirs(tmp);
    int ok = h_kind(tmp, NULL) == 1;
    for (int i = 0; ok && i < c->n; i++) {
        if (c->e[i].is_dir || !is_child(top, c->e[i].path))
            continue;
        char hp[HOST_PATH_MAX], bp[HOST_PATH_MAX * 2], en[MC_NAME_MAX * 3];
        host_of(port, c->e[i].path, hp);
        enc_name(base_of(c->e[i].path), en, 0);
        snprintf(bp, sizeof bp, "%s/%s", tmp, en);
        uint32_t n;
        uint8_t *d = h_slurp(hp, &n);
        FILE *f = fopen(bp, "wb");
        ok = f && (n == 0 || fwrite(d, 1, n, f) == n);
        if (f && fclose(f) != 0)
            ok = 0;
        free(d);
    }
    if (ok && rename(tmp, snap) == 0) {
        nl_add(base_of(snap), &l);
        qsort(l.v, (size_t)l.n, sizeof *l.v, nl_cmp);
    } else {
        fprintf(stderr, "mccard: backup of %s failed (%s)\n", top, tmp);
        h_rmtree_contents(tmp);
        h_rmdir(tmp);
    }
    for (int i = 0; i + M.cfg.backup_keep < l.n; i++) { /* oldest first */
        char old[HOST_PATH_MAX];
        snprintf(old, sizeof old, "%s/%s", bdir, l.v[i]);
        h_rmtree_contents(old);
        h_rmdir(old);
    }
    nl_free(&l);
}

/* about to change card path `ap`: back up the save directory it lies in */
static void backup_before(int port, mcard *c, const char *ap)
{
    if (!strcmp(ap, "/"))
        return;
    char top[MC_PATH_MAX];
    snprintf(top, sizeof top, "%s", ap);
    char *s = strchr(top + 1, '/');
    if (s)
        *s = 0;
    backup_top(port, c, top);
}

static void host_of(int port, const char *card_path, char *out)
{
    mccard_host_path(port, card_path, out, HOST_PATH_MAX);
}

static int wild_match(const char *p, const char *s)
{
    if (!*p)
        return !*s;
    if (*p == '*') {
        for (;;) {
            if (wild_match(p + 1, s))
                return 1;
            if (!*s)
                return 0;
            s++;
        }
    }
    if (!*s)
        return 0;
    if (*p == '?' || *p == *s)
        return wild_match(p + 1, s + 1);
    return 0;
}

/* ---- operations --------------------------------------------------------------------- */
int mccard_getinfo(int port, int *type, int *free_clusters, int *format)
{
    ensure();
    int t = 0, fr = 0, fm = 0, res;
    int flt = fault_hit(port);
    if (flt && flt != MC_RES_NOCARD) {
        res = flt;
    } else if (port < 0 || port >= MC_PORTS || !M.card[port].present) {
        res = MC_RES_NOCARD;
    } else {
        mcard *c = &M.card[port];
        t = MC_TYPE_PS2;
        if (c->formatted) {
            fm = 1;
            fr = (int)card_free(c);
            res = c->changed ? MC_RES_CHANGEDCARD : MC_RES_SUCCEED;
        } else {
            res = MC_RES_NOFORMAT;
        }
        c->changed = 0;
    }
    if (type)
        *type = t;
    if (free_clusters)
        *free_clusters = fr;
    if (format)
        *format = fm;
    return res;
}

static mfd *fd_get(int fd)
{
    if (fd < 0 || fd >= MAX_FDS_CAP || !M.fd[fd].used)
        return NULL;
    return &M.fd[fd];
}

static int fd_open_on(int port, const char *path)
{
    for (int i = 0; i < MAX_FDS_CAP; i++)
        if (M.fd[i].used && !M.fd[i].gone && M.fd[i].port == port && !strcmp(M.fd[i].path, path))
            return 1;
    return 0;
}

/* the buffered contents of `path` when a write descriptor holds it */
static mfd *writer_of(int port, const char *path)
{
    for (int i = 0; i < MAX_FDS_CAP; i++) {
        mfd *d = &M.fd[i];
        if (d->used && !d->gone && d->buf && d->port == port && !strcmp(d->path, path))
            return d;
    }
    return NULL;
}

static int commit_fd(mfd *d)
{
    if (!d->wdirty || d->gone)
        return 0;
    char hp[HOST_PATH_MAX];
    host_of(d->port, d->path, hp);
    if (h_write_atomic(hp, d->buf, d->len, M.cfg.durable) != 0)
        return MC_RES_DENIEDPERMIT;
    d->wdirty = 0;
    return 0;
}

static int fd_reserve(uint32_t *cap, uint8_t **buf, uint32_t need)
{
    if (need <= *cap)
        return 0;
    uint32_t nc = *cap ? *cap : 4096;
    while (nc < need)
        nc *= 2;
    uint8_t *nb = (uint8_t *)realloc(*buf, nc);
    if (!nb)
        return -1;
    *buf = nb;
    *cap = nc;
    return 0;
}

int mccard_open(int port, const char *path, int mode)
{
    mcard *c;
    int r = fault_hit(port);
    if (r)
        return r;
    r = card_check(port, &c);
    if (r)
        return r;
    if (!path || !*path)
        return MC_RES_NOENTRY;
    char ap[MC_PATH_MAX], par[MC_PATH_MAX];
    if (resolve(c, path, ap))
        return MC_RES_NOENTRY;
    if (strpbrk(base_of(ap), "*?"))
        return MC_RES_NOENTRY;
    parent_of(ap, par);
    ment *pe = find(c, par);
    if (!pe || !pe->is_dir)
        return MC_RES_NOENTRY;
    ment *m = find(c, ap);
    char hp[HOST_PATH_MAX];
    host_of(port, ap, hp);
    if (mode & MC_O_MKDIR) {
        if (m || !strcmp(ap, "/"))
            return MC_RES_NOENTRY;
        if (card_free(c) < 1u + dir_growth(c, par))
            return MC_RES_FULLDEVICE;
        backup_before(port, c, ap);
        if (h_mkdir(hp) != 0 && h_kind(hp, NULL) != 1)
            return MC_RES_DENIEDPERMIT;
        add_ent(c, ap, 1);
        pe = find(c, par);
        now_time(&pe->mtime);
        save_meta(port);
        return 0;
    }
    if (m && m->is_dir)
        return MC_RES_DENIEDPERMIT;
    if (m && (mode & MC_O_CREAT) && (mode & MC_O_EXCL))
        return MC_RES_NOENTRY;
    int slot = -1, open_now = 0;
    for (int i = 0; i < MAX_FDS_CAP; i++) {
        if (M.fd[i].used)
            open_now++;
        else if (slot < 0)
            slot = i;
    }
    if (slot < 0 || open_now >= M.cfg.max_fds)
        return MC_RES_UPLIMITHANDLE;
    int created = 0;
    int wr = (mode & MC_O_WRONLY) != 0;
    if (wr || !m)
        backup_before(port, c, ap);
    if (!m) {
        if (!(mode & MC_O_CREAT))
            return MC_RES_NOENTRY;
        if (card_free(c) < dir_growth(c, par))
            return MC_RES_FULLDEVICE;
        FILE *nf = fopen(hp, "wb");
        if (!nf)
            return MC_RES_DENIEDPERMIT;
        fclose(nf);
        m = add_ent(c, ap, 0);
        if (!m)
            return MC_RES_DENIEDPERMIT;
        pe = find(c, par);
        now_time(&pe->mtime);
        created = 1;
    }
    if (wr && !(m->attr & MC_ATTR_WRITEABLE))
        return MC_RES_DENIEDPERMIT;
    if ((mode & MC_O_RDONLY) && !(m->attr & MC_ATTR_READABLE))
        return MC_RES_DENIEDPERMIT;
    mfd *d = &M.fd[slot];
    memset(d, 0, sizeof *d);
    if (wr) {
        /* write descriptors buffer the whole file (saves are ~100 KB) and replace
         * the host file atomically on flush / close */
        mfd *w = writer_of(port, ap);
        if (w) {
            d->len = w->len;
            if (d->len && fd_reserve(&d->cap, &d->buf, d->len)) {
                free(d->buf);
                memset(d, 0, sizeof *d);
                return MC_RES_DENIEDPERMIT;
            }
            if (d->len)
                memcpy(d->buf, w->buf, d->len);
            d->wdirty = w->wdirty;
        } else {
            uint32_t n;
            d->buf = h_slurp(hp, &n);
            if (!d->buf && h_kind(hp, NULL) != 0)
                return MC_RES_NOENTRY;
            d->len = d->cap = n; /* the host file is the truth for the bytes */
        }
        if (!d->buf && fd_reserve(&d->cap, &d->buf, 4096))
            return MC_RES_DENIEDPERMIT;
        if ((mode & MC_O_TRUNC) && d->len) {
            d->len = 0;
            d->wdirty = 1;
            m->size = 0;
            now_time(&m->mtime);
        }
        m->size = d->len;
    } else {
        FILE *f = fopen(hp, "rb");
        if (!f)
            return MC_RES_NOENTRY;
        d->f = f;
    }
    d->used = 1;
    d->port = port;
    d->path = strdup(ap);
    d->mode = mode;
    if (created || d->wdirty)
        save_meta(port);
    return slot;
}

int mccard_close(int fd)
{
    ensure();
    mfd *d = fd_get(fd);
    if (!d)
        return MC_RES_DENIEDPERMIT;
    int port = d->port, dirty = d->dirty, gone = d->gone;
    int r = gone ? MC_RES_NOCARD : fault_hit(port);
    if (r && !gone && M.fd[fd].used && !M.fd[fd].gone)
        return r; /* an injected failure other than a pulled card: still open */
    if (!r)
        r = commit_fd(d);
    if (d->f)
        fclose(d->f);
    free(d->buf);
    free(d->path);
    memset(d, 0, sizeof *d);
    if (dirty && !gone && M.card[port].present)
        save_meta(port);
    return r;
}

int mccard_seek(int fd, int32_t offset, int whence)
{
    ensure();
    mfd *d = fd_get(fd);
    if (!d)
        return MC_RES_DENIEDPERMIT;
    int fr = d->gone ? MC_RES_NOCARD : fault_hit(d->port);
    if (fr)
        return fr;
    ment *m = find(&M.card[d->port], d->path);
    if (!m)
        return MC_RES_NOENTRY;
    int64_t base = whence == 0 ? 0 : whence == 1 ? (int64_t)d->pos : whence == 2 ? (int64_t)m->size : -1;
    if (base < 0)
        return MC_RES_DENIEDPERMIT;
    int64_t np = base + offset;
    if (np < 0)
        np = 0;
    d->pos = (uint32_t)np;
    return (int)d->pos;
}

int mccard_read(int fd, void *dst, int size)
{
    ensure();
    mfd *d = fd_get(fd);
    if (!d)
        return MC_RES_DENIEDPERMIT;
    int fr = d->gone ? MC_RES_NOCARD : fault_hit(d->port);
    if (fr)
        return fr;
    if (!(d->mode & MC_O_RDONLY))
        return MC_RES_DENIEDPERMIT;
    ment *m = find(&M.card[d->port], d->path);
    if (!m)
        return MC_RES_NOENTRY;
    if (size <= 0 || d->pos >= m->size)
        return 0;
    uint32_t n = (uint32_t)size;
    if (n > m->size - d->pos)
        n = m->size - d->pos;
    mfd *w = d->buf ? d : writer_of(d->port, d->path);
    size_t got;
    if (w) { /* written but not yet committed: read the buffer */
        got = d->pos < w->len ? (w->len - d->pos < n ? w->len - d->pos : n) : 0;
        memcpy(dst, w->buf + d->pos, got);
    } else {
        fseek(d->f, (long)d->pos, SEEK_SET);
        got = fread(dst, 1, n, d->f);
    }
    d->pos += (uint32_t)got;
    return (int)got;
}

int mccard_write(int fd, const void *src, int size)
{
    ensure();
    mfd *d = fd_get(fd);
    if (!d)
        return MC_RES_DENIEDPERMIT;
    int fr = d->gone ? MC_RES_NOCARD : fault_hit(d->port);
    if (fr)
        return fr;
    if (!(d->mode & MC_O_WRONLY) || !d->buf)
        return MC_RES_DENIEDPERMIT;
    mcard *c = &M.card[d->port];
    ment *m = find(c, d->path);
    if (!m)
        return MC_RES_NOENTRY;
    if (size <= 0)
        return 0;
    uint32_t end = d->pos + (uint32_t)size;
    uint32_t nsize = end > m->size ? end : m->size;
    uint32_t need = (nsize + 1023u) / 1024u - (m->size + 1023u) / 1024u;
    if (need > card_free(c))
        return MC_RES_FULLDEVICE;
    if (fd_reserve(&d->cap, &d->buf, end > d->len ? end : d->len))
        return MC_RES_DENIEDPERMIT;
    if (d->pos > d->len) /* zero-fill a hole after a seek past the end */
        memset(d->buf + d->len, 0, d->pos - d->len);
    memcpy(d->buf + d->pos, src, (size_t)size);
    d->pos = end;
    if (end > d->len)
        d->len = end;
    m->size = d->len;
    d->wdirty = 1;
    now_time(&m->mtime);
    d->dirty = 1;
    return size;
}

int mccard_flush(int fd)
{
    ensure();
    mfd *d = fd_get(fd);
    if (!d)
        return MC_RES_DENIEDPERMIT;
    int r = d->gone ? MC_RES_NOCARD : fault_hit(d->port);
    if (r)
        return r;
    r = commit_fd(d);
    if (d->dirty) {
        save_meta(d->port);
        d->dirty = 0;
    }
    return r;
}

int mccard_chdir(int port, const char *path, char *prev_out)
{
    mcard *c;
    int r = fault_hit(port);
    if (r)
        return r;
    r = card_check(port, &c);
    if (r)
        return r;
    char ap[MC_PATH_MAX];
    if (!path || resolve(c, path, ap))
        return MC_RES_NOENTRY;
    ment *m = find(c, ap);
    if (!m || !m->is_dir)
        return MC_RES_NOENTRY;
    if (prev_out)
        snprintf(prev_out, MC_PATH_MAX, "%s", c->cwd);
    snprintf(c->cwd, sizeof c->cwd, "%s", ap);
    return 0;
}

static void fill_dirent(mcard *c, const ment *m, const char *name, mc_dirent *o)
{
    memset(o, 0, sizeof *o);
    o->created = m->ctime;
    o->modified = m->mtime;
    o->size = m->is_dir ? 2u + (uint32_t)nchildren(c, m->path) : m->size;
    o->attr = m->attr;
    snprintf(o->name, sizeof o->name, "%s", name);
}

static int seq_cmp(const void *a, const void *b)
{
    const ment *x = *(const ment *const *)a, *y = *(const ment *const *)b;
    return x->seq < y->seq ? -1 : x->seq > y->seq;
}

int mccard_getdir(int port, const char *path, int cont, int maxent, mc_dirent *out)
{
    mcard *c;
    int r = fault_hit(port);
    if (r)
        return r;
    r = card_check(port, &c);
    if (r)
        return r;
    if (!cont) {
        free(c->it);
        c->it = NULL;
        c->it_n = c->it_pos = 0;
        if (!path || !*path)
            return MC_RES_NOENTRY;
        char raw[MC_PATH_MAX], dir[MC_PATH_MAX], pat[MC_PATH_MAX];
        snprintf(raw, sizeof raw, "%s", path);
        char *s = strrchr(raw, '/');
        if (s) {
            snprintf(pat, sizeof pat, "%s", s + 1);
            if (s == raw)
                strcpy(raw, "/");
            else
                *s = 0;
            if (resolve(c, raw, dir))
                return MC_RES_NOENTRY;
        } else {
            snprintf(pat, sizeof pat, "%s", raw);
            snprintf(dir, sizeof dir, "%s", c->cwd);
        }
        ment *de = find(c, dir);
        if (!de || !de->is_dir)
            return MC_RES_NOENTRY;
        int nc = nchildren(c, dir);
        c->it = (mc_dirent *)calloc((size_t)nc + 2, sizeof *c->it);
        const ment **kids = (const ment **)calloc((size_t)nc + 1, sizeof *kids);
        if (!c->it || !kids) {
            free(kids);
            return MC_RES_DENIEDPERMIT;
        }
        int k = 0;
        for (int i = 0; i < c->n; i++)
            if (is_child(dir, c->e[i].path))
                kids[k++] = &c->e[i];
        qsort(kids, (size_t)k, sizeof *kids, seq_cmp);
        if (*pat) {
            char par[MC_PATH_MAX];
            parent_of(dir, par);
            ment *pp = find(c, par);
            if (wild_match(pat, "."))
                fill_dirent(c, de, ".", &c->it[c->it_n++]);
            if (wild_match(pat, ".."))
                fill_dirent(c, pp ? pp : de, "..", &c->it[c->it_n++]);
            for (int i = 0; i < k; i++)
                if (wild_match(pat, base_of(kids[i]->path)))
                    fill_dirent(c, kids[i], base_of(kids[i]->path), &c->it[c->it_n++]);
        }
        free(kids);
    }
    int w = 0;
    while (w < maxent && c->it_pos < c->it_n) {
        if (out)
            out[w] = c->it[c->it_pos];
        w++;
        c->it_pos++;
    }
    return w;
}

static void rename_prefix(int port, mcard *c, const char *from, const char *to)
{
    size_t fl = strlen(from);
    for (int i = 0; i < c->n; i++) {
        char *p = c->e[i].path;
        if (!strcmp(p, from) || (!strncmp(p, from, fl) && p[fl] == '/')) {
            char np[MC_PATH_MAX];
            snprintf(np, sizeof np, "%s%s", to, p + fl);
            free(c->e[i].path);
            c->e[i].path = strdup(np);
        }
    }
    for (int i = 0; i < MAX_FDS_CAP; i++) {
        mfd *d = &M.fd[i];
        if (!d->used || d->port != port)
            continue;
        if (!strcmp(d->path, from) || (!strncmp(d->path, from, fl) && d->path[fl] == '/')) {
            char np[MC_PATH_MAX];
            snprintf(np, sizeof np, "%s%s", to, d->path + fl);
            free(d->path);
            d->path = strdup(np);
        }
    }
}

int mccard_setinfo(int port, const char *path, const mc_dirent *info, unsigned flags)
{
    mcard *c;
    int r = fault_hit(port);
    if (r)
        return r;
    r = card_check(port, &c);
    if (r)
        return r;
    char ap[MC_PATH_MAX];
    if (!path || !info || resolve(c, path, ap) || !strcmp(ap, "/"))
        return MC_RES_NOENTRY;
    ment *m = find(c, ap);
    if (!m)
        return MC_RES_NOENTRY;
    backup_before(port, c, ap);
    m = find(c, ap);
    if (flags & MC_INFO_NAME) {
        char nn[MC_NAME_MAX + 1];
        memcpy(nn, info->name, MC_NAME_MAX);
        nn[MC_NAME_MAX] = 0;
        if (!nn[0] || strlen(nn) >= MC_NAME_MAX || strchr(nn, '/') || !strcmp(nn, ".") || !strcmp(nn, ".."))
            return MC_RES_NOENTRY;
        char par[MC_PATH_MAX], np[MC_PATH_MAX + MC_NAME_MAX + 1];
        parent_of(ap, par);
        snprintf(np, sizeof np, "%s/%s", strcmp(par, "/") ? par : "", nn);
        if (strcmp(np, ap)) {
            if (find(c, np))
                return MC_RES_NOENTRY;
            char h1[HOST_PATH_MAX], h2[HOST_PATH_MAX];
            host_of(port, ap, h1);
            host_of(port, np, h2);
            /* an open FILE* keeps the old name on Windows; reopen around the rename */
            long pos[MAX_FDS_CAP];
            size_t fl = strlen(ap);
            for (int i = 0; i < MAX_FDS_CAP; i++) {
                mfd *d = &M.fd[i];
                pos[i] = -1;
                if (d->used && !d->gone && d->f && d->port == port &&
                    (!strcmp(d->path, ap) || (!strncmp(d->path, ap, fl) && d->path[fl] == '/'))) {
                    pos[i] = 1;
                    fclose(d->f);
                    d->f = NULL;
                }
            }
            if (rename(h1, h2) != 0)
                return MC_RES_DENIEDPERMIT;
            rename_prefix(port, c, ap, np);
            for (int i = 0; i < MAX_FDS_CAP; i++) {
                mfd *d = &M.fd[i];
                if (pos[i] < 0)
                    continue;
                char hp[HOST_PATH_MAX];
                host_of(port, d->path, hp);
                d->f = fopen(hp, "rb");
            }
            snprintf(ap, sizeof ap, "%s", np);
            m = find(c, ap);
        }
    }
    if (flags & MC_INFO_CTIME)
        m->ctime = info->created;
    if (flags & MC_INFO_MTIME)
        m->mtime = info->modified;
    if (flags & MC_INFO_ATTR)
        m->attr = (uint16_t)((m->attr & ~MC_ATTR_USER_MASK) | (info->attr & MC_ATTR_USER_MASK));
    save_meta(port);
    return 0;
}

int mccard_delete(int port, const char *path)
{
    mcard *c;
    int r = fault_hit(port);
    if (r)
        return r;
    r = card_check(port, &c);
    if (r)
        return r;
    char ap[MC_PATH_MAX], par[MC_PATH_MAX];
    if (!path || resolve(c, path, ap) || !strcmp(ap, "/"))
        return MC_RES_NOENTRY;
    ment *m = find(c, ap);
    if (!m)
        return MC_RES_NOENTRY;
    if (m->is_dir && nchildren(c, ap) > 0)
        return MC_RES_NOTEMPTY;
    if (!m->is_dir && fd_open_on(port, ap))
        return MC_RES_DENIEDPERMIT;
    backup_before(port, c, ap);
    m = find(c, ap);
    char hp[HOST_PATH_MAX];
    host_of(port, ap, hp);
    if ((m->is_dir ? h_rmdir(hp) : remove(hp)) != 0 && h_kind(hp, NULL) >= 0)
        return MC_RES_DENIEDPERMIT;
    del_ent(c, m);
    parent_of(ap, par);
    ment *pe = find(c, par);
    if (pe)
        now_time(&pe->mtime);
    size_t al = strlen(ap);
    if (!strncmp(c->cwd, ap, al) && (c->cwd[al] == 0 || c->cwd[al] == '/'))
        strcpy(c->cwd, "/");
    save_meta(port);
    return 0;
}

static int wipe(int port, int formatted)
{
    ensure();
    int fr = fault_hit(port);
    if (fr)
        return fr;
    if (port < 0 || port >= MC_PORTS || !M.card[port].present)
        return MC_RES_NOCARD;
    mcard *c = &M.card[port];
    close_port_fds(port, FD_DROP);
    for (int i = 0; i < c->n; i++) /* formatting erases every save: keep a copy */
        if (c->e[i].is_dir && is_child("/", c->e[i].path)) {
            char top[MC_PATH_MAX];
            snprintf(top, sizeof top, "%s", c->e[i].path);
            backup_top(port, c, top);
        }
    h_rmtree_contents(c->host);
    for (int i = 0; i < c->n; i++)
        free(c->e[i].path);
    c->n = 0;
    free(c->it);
    c->it = NULL;
    c->it_n = c->it_pos = 0;
    c->next_seq = 0;
    add_ent(c, "/", 1);
    c->formatted = formatted;
    c->changed = 0;
    strcpy(c->cwd, "/");
    save_meta(port);
    return 0;
}

int mccard_format(int port) { return wipe(port, 1); }
int mccard_unformat(int port) { return wipe(port, 0); }

int mccard_entspace(int port, const char *path)
{
    mcard *c;
    int r = fault_hit(port);
    if (r)
        return r;
    r = card_check(port, &c);
    if (r)
        return r;
    char ap[MC_PATH_MAX];
    if (!path || resolve(c, path, ap))
        return MC_RES_NOENTRY;
    ment *m = find(c, ap);
    if (!m || !m->is_dir)
        return MC_RES_NOENTRY;
    return ((2 + nchildren(c, ap)) % 2) ? 1 : 0;
}
