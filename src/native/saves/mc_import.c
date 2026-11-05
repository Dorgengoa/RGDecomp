/* SPDX-License-Identifier: CC0-1.0 */
/* PCSX2 memory-card import and the saves command-line tools (mc_import.h, docs/SAVES.md). */
#include "mc_import.h"

#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <dirent.h>
#include <sys/stat.h>
#endif

/* ---- card geometry (the same constants as tools/saves/ps2card.py) ---- */
#define PAGE 512
#define SPARE 16
#define PAGES 16384
#define PPC 2
#define CLUSTER (PAGE * PPC)
#define SIZE_ECC ((size_t)PAGES * (PAGE + SPARE))
#define SIZE_RAW ((size_t)PAGES * PAGE)
#define FAT_EOC 0xFFFFFFFFu
#define FAT_USED 0x80000000u
#define M_FILE 0x0010
#define M_DIR 0x0020
#define M_EXISTS 0x8000
#define MAX_FILE_LEN (8u << 20)

static void seterr(char *err, size_t cap, const char *fmt, const char *a)
{
    if (err && cap)
        snprintf(err, cap, fmt, a ? a : "");
}

static uint32_t rd32(const uint8_t *p) { return (uint32_t)p[0] | (uint32_t)p[1] << 8 | (uint32_t)p[2] << 16 | (uint32_t)p[3] << 24; }
static uint16_t rd16(const uint8_t *p) { return (uint16_t)(p[0] | p[1] << 8); }

typedef struct img {
    const uint8_t *b;
    size_t raw_page;
    uint32_t clusters, alloc_offset, alloc_end, root;
    uint32_t ifc[32];
} img;

/* cluster c (absolute) into out[CLUSTER]; -1 outside the card */
static int rd_cluster(const img *m, uint32_t c, uint8_t *out)
{
    if ((uint64_t)c * PPC + PPC > PAGES)
        return -1;
    for (int i = 0; i < PPC; i++)
        memcpy(out + i * PAGE, m->b + ((size_t)c * PPC + (size_t)i) * m->raw_page, PAGE);
    return 0;
}

static int fat_get(const img *m, uint32_t n, uint32_t *v)
{
    uint8_t buf[CLUSTER];
    const uint32_t per = CLUSTER / 4;
    uint32_t fi = n / per;
    if (fi / per >= 32 || rd_cluster(m, m->ifc[fi / per], buf))
        return -1;
    uint32_t fc = rd32(buf + (fi % per) * 4);
    if (rd_cluster(m, fc, buf))
        return -1;
    *v = rd32(buf + (n % per) * 4);
    return 0;
}

/* the chain from `first` (relative clusters) read into a new buffer of len bytes (len 0:
 * the whole chain, *outlen set) */
static uint8_t *rd_chain(const img *m, uint32_t first, uint32_t len, uint32_t *outlen)
{
    uint32_t cap = 0, got = 0, n = first, steps = 0;
    uint8_t *b = NULL;
    for (;;) {
        if (n >= m->alloc_end || ++steps > m->clusters)
            goto bad;
        if (got + CLUSTER > cap) {
            uint32_t nc = cap ? cap * 2 : 8 * CLUSTER;
            uint8_t *nb = (uint8_t *)realloc(b, nc);
            if (!nb)
                goto bad;
            b = nb;
            cap = nc;
        }
        if (rd_cluster(m, m->alloc_offset + n, b + got))
            goto bad;
        got += CLUSTER;
        if (len && got >= len)
            break;
        uint32_t v;
        if (fat_get(m, n, &v))
            goto bad;
        if (v == FAT_EOC)
            break;
        if (!(v & FAT_USED))
            goto bad;
        n = v & 0x7FFFFFFFu;
    }
    if (len && got < len)
        goto bad;
    *outlen = len ? len : got;
    return b;
bad:
    free(b);
    return NULL;
}

typedef struct dent {
    uint16_t mode;
    uint32_t length, cluster;
    mc_datetime ctime, mtime;
    char name[MC_NAME_MAX];
} dent;

static void parse_dent(const uint8_t *p, dent *d)
{
    d->mode = rd16(p);
    d->length = rd32(p + 4);
    memcpy(&d->ctime, p + 8, 8);
    d->cluster = rd32(p + 0x10);
    memcpy(&d->mtime, p + 0x18, 8);
    memcpy(d->name, p + 0x40, MC_NAME_MAX - 1);
    d->name[MC_NAME_MAX - 1] = 0;
}

/* directory entries (count: from the "." entry when 0) */
static dent *rd_dir(const img *m, uint32_t first, uint32_t count, uint32_t *n)
{
    uint32_t len;
    uint8_t *raw = rd_chain(m, first, 0, &len);
    if (!raw)
        return NULL;
    uint32_t have = len / PAGE;
    if (!count && have)
        count = rd32(raw + 4);
    if (count > have)
        count = have;
    dent *d = (dent *)calloc(count ? count : 1, sizeof *d);
    if (d)
        for (uint32_t i = 0; i < count; i++)
            parse_dent(raw + (size_t)i * PAGE, &d[i]);
    free(raw);
    *n = count;
    return d;
}

static void dir_title(mc_src_dir *d)
{
    d->title[0] = 0;
    for (int k = 0; k < d->nfiles; k++)
        if (!strcmp(d->files[k].name, "icon.sys"))
            mc_icon_title(d->files[k].data, d->files[k].len, d->title, sizeof d->title);
}

int mc_src_open_image(const uint8_t *b, size_t len, mc_src_card *card, char *err, size_t errcap)
{
    memset(card, 0, sizeof *card);
    img m;
    memset(&m, 0, sizeof m);
    m.b = b;
    if (len == SIZE_ECC)
        m.raw_page = PAGE + SPARE;
    else if (len == SIZE_RAW)
        m.raw_page = PAGE;
    else {
        seterr(err, errcap, "not an 8 MB memory card image (%s)", len ? "wrong size" : "empty");
        return -1;
    }
    uint8_t sb[CLUSTER];
    rd_cluster(&m, 0, sb);
    if (memcmp(sb, "Sony PS2 Memory Card Format ", 28)) {
        seterr(err, errcap, "the card is not formatted (no superblock)%s", NULL);
        return -1;
    }
    if (rd16(sb + 0x28) != PAGE || rd16(sb + 0x2A) != PPC) {
        seterr(err, errcap, "unsupported card geometry%s", NULL);
        return -1;
    }
    m.clusters = rd32(sb + 0x30);
    m.alloc_offset = rd32(sb + 0x34);
    m.alloc_end = rd32(sb + 0x38);
    m.root = rd32(sb + 0x3C);
    for (int i = 0; i < 32; i++)
        m.ifc[i] = rd32(sb + 0x50 + 4 * i);
    if (m.clusters > PAGES / PPC || m.alloc_offset >= m.clusters || m.alloc_end > m.clusters) {
        seterr(err, errcap, "bad superblock%s", NULL);
        return -1;
    }
    card->kind = 1;
    card->ecc = m.raw_page > PAGE;
    uint32_t nroot;
    dent *root = rd_dir(&m, m.root, 0, &nroot);
    if (!root) {
        seterr(err, errcap, "unreadable root directory (broken FAT chain)%s", NULL);
        return -1;
    }
    for (uint32_t i = 2; i < nroot; i++) {
        const dent *e = &root[i];
        if (!(e->mode & M_EXISTS) || !(e->mode & M_DIR) || !e->name[0])
            continue;
        uint32_t nf;
        dent *fl = rd_dir(&m, e->cluster, e->length, &nf);
        if (!fl)
            continue;   /* a broken directory: skipped (listed nowhere) */
        mc_src_dir *nd = (mc_src_dir *)realloc(card->dirs, (size_t)(card->ndirs + 1) * sizeof *nd);
        if (!nd) {
            free(fl);
            break;
        }
        card->dirs = nd;
        mc_src_dir *d = &card->dirs[card->ndirs++];
        memset(d, 0, sizeof *d);
        memcpy(d->name, e->name, sizeof d->name);
        d->mode = e->mode;
        d->has_time = 1;
        d->ctime = e->ctime;
        d->mtime = e->mtime;
        d->files = (mc_src_file *)calloc(nf ? nf : 1, sizeof *d->files);
        for (uint32_t k = 2; d->files && k < nf; k++) {
            const dent *f = &fl[k];
            if (!(f->mode & M_EXISTS) || !(f->mode & M_FILE) || !f->name[0] || f->length > MAX_FILE_LEN)
                continue;
            mc_src_file *o = &d->files[d->nfiles];
            uint32_t got = 0;
            o->data = f->length ? rd_chain(&m, f->cluster, f->length, &got) : (uint8_t *)calloc(1, 1);
            if (!o->data)
                continue;
            memcpy(o->name, f->name, sizeof o->name);
            o->len = f->length;
            o->mode = f->mode;
            o->has_time = 1;
            o->ctime = f->ctime;
            o->mtime = f->mtime;
            d->nfiles++;
        }
        dir_title(d);
        free(fl);
    }
    free(root);
    return 0;
}

/* ---- host files ---- */
static uint8_t *slurp(const char *path, size_t *n)
{
    *n = 0;
    FILE *f = fopen(path, "rb");
    if (!f)
        return NULL;
    uint8_t *b = NULL;
    size_t len = 0, cap = 0;
    for (;;) {
        if (len == cap) {
            size_t nc = cap ? cap * 2 : 1 << 16;
            if (nc > (size_t)(16u << 20))
                break;
            uint8_t *nb = (uint8_t *)realloc(b, nc);
            if (!nb)
                break;
            b = nb;
            cap = nc;
        }
        size_t got = fread(b + len, 1, cap - len, f);
        if (!got)
            break;
        len += got;
    }
    fclose(f);
    *n = len;
    return b;
}

typedef void (*list_fn)(const char *name, int is_dir, void *u);
static int host_list(const char *dir, list_fn fn, void *u)
{
#ifdef _WIN32
    char pat[2048];
    snprintf(pat, sizeof pat, "%s\\*", dir);
    WIN32_FIND_DATAA fd;
    HANDLE h = FindFirstFileA(pat, &fd);
    if (h == INVALID_HANDLE_VALUE)
        return -1;
    do {
        if (strcmp(fd.cFileName, ".") && strcmp(fd.cFileName, ".."))
            fn(fd.cFileName, (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0, u);
    } while (FindNextFileA(h, &fd));
    FindClose(h);
    return 0;
#else
    DIR *d = opendir(dir);
    if (!d)
        return -1;
    struct dirent *e;
    while ((e = readdir(d)) != NULL) {
        if (!strcmp(e->d_name, ".") || !strcmp(e->d_name, ".."))
            continue;
        char p[2048];
        struct stat st;
        snprintf(p, sizeof p, "%s/%s", dir, e->d_name);
        if (stat(p, &st) == 0)
            fn(e->d_name, S_ISDIR(st.st_mode), u);
    }
    closedir(d);
    return 0;
#endif
}

static int is_dir(const char *p)
{
#ifdef _WIN32
    DWORD a = GetFileAttributesA(p);
    return a != INVALID_FILE_ATTRIBUTES && (a & FILE_ATTRIBUTE_DIRECTORY);
#else
    struct stat st;
    return stat(p, &st) == 0 && S_ISDIR(st.st_mode);
#endif
}

typedef struct names {
    char (*v)[MC_NAME_MAX];
    int n;
    int want_dirs;
} names;
static void names_add(const char *name, int dir, void *u)
{
    names *l = (names *)u;
    if (dir != l->want_dirs || !strncmp(name, "_pcsx2_", 7) || strlen(name) >= MC_NAME_MAX)
        return;
    void *nv = realloc(l->v, (size_t)(l->n + 1) * sizeof *l->v);
    if (!nv)
        return;
    l->v = (char (*)[MC_NAME_MAX])nv;
    snprintf(l->v[l->n++], MC_NAME_MAX, "%s", name);
}
/* the order the game creates a save's files in: icon.sys, the icon(s), the data
 * (BASCUS-...) last; then by name */
static int rank_of(const char *n) { return !strcmp(n, "icon.sys") ? 0 : !strncmp(n, "BASCUS-", 7) ? 2 : 1; }
static int file_cmp(const void *a, const void *b)
{
    const char *x = (const char *)a, *y = (const char *)b;
    int r = rank_of(x) - rank_of(y);
    return r ? r : strcmp(x, y);
}
static int name_cmp(const void *a, const void *b) { return strcmp((const char *)a, (const char *)b); }

static int open_folder(const char *path, mc_src_card *card, char *err, size_t errcap)
{
    memset(card, 0, sizeof *card);
    card->kind = 2;
    names dl = {NULL, 0, 1};
    if (host_list(path, names_add, &dl)) {
        seterr(err, errcap, "cannot list %s", path);
        return -1;
    }
    if (dl.n)
        qsort(dl.v, (size_t)dl.n, sizeof *dl.v, name_cmp);
    card->dirs = (mc_src_dir *)calloc(dl.n ? (size_t)dl.n : 1, sizeof *card->dirs);
    for (int i = 0; card->dirs && i < dl.n; i++) {
        char dp[2048];
        snprintf(dp, sizeof dp, "%s/%s", path, dl.v[i]);
        names fl = {NULL, 0, 0};
        host_list(dp, names_add, &fl);
        if (fl.n)
            qsort(fl.v, (size_t)fl.n, sizeof *fl.v, file_cmp);
        mc_src_dir *d = &card->dirs[card->ndirs++];
        snprintf(d->name, sizeof d->name, "%s", dl.v[i]);
        d->mode = 0x8427;
        d->files = (mc_src_file *)calloc(fl.n ? (size_t)fl.n : 1, sizeof *d->files);
        for (int k = 0; d->files && k < fl.n; k++) {
            char fp[2300];
            size_t n;
            snprintf(fp, sizeof fp, "%s/%s", dp, fl.v[k]);
            uint8_t *data = slurp(fp, &n);
            if (!data && n)
                continue;
            mc_src_file *o = &d->files[d->nfiles++];
            snprintf(o->name, sizeof o->name, "%s", fl.v[k]);
            o->data = data ? data : (uint8_t *)calloc(1, 1);
            o->len = (uint32_t)n;
            o->mode = 0x8497;
        }
        dir_title(d);
        free(fl.v);
    }
    free(dl.v);
    return 0;
}

int mc_src_open(const char *path, mc_src_card *card, char *err, size_t errcap)
{
    memset(card, 0, sizeof *card);
    if (!path || !*path) {
        seterr(err, errcap, "no card given%s", NULL);
        return -1;
    }
    if (is_dir(path)) {
        char sb[2100];
        snprintf(sb, sizeof sb, "%s/_pcsx2_superblock", path);
        FILE *f = fopen(sb, "rb");
        if (f)
            fclose(f);
        else {
            seterr(err, errcap, "%s is not a PCSX2 folder card (no _pcsx2_superblock)", path);
            return -1;
        }
        return open_folder(path, card, err, errcap);
    }
    size_t n;
    uint8_t *b = slurp(path, &n);
    if (!b) {
        seterr(err, errcap, "cannot read %s", path);
        return -1;
    }
    int r = mc_src_open_image(b, n, card, err, errcap);
    free(b);
    return r;
}

void mc_src_free(mc_src_card *card)
{
    for (int i = 0; i < card->ndirs; i++) {
        for (int k = 0; k < card->dirs[i].nfiles; k++)
            free(card->dirs[i].files[k].data);
        free(card->dirs[i].files);
    }
    free(card->dirs);
    memset(card, 0, sizeof *card);
}

int mc_glob(const char *p, const char *s)
{
    if (!*p)
        return !*s;
    if (*p == '*')
        return mc_glob(p + 1, s) || (*s && mc_glob(p, s + 1));
    if (!*s)
        return 0;
    return (*p == '?' || *p == *s) && mc_glob(p + 1, s + 1);
}

/* ---- import ---- */
static int mc_import_dir(const mc_src_dir *d, int port, int exists, char *err, size_t errcap);
static int port_has_dir(int port, const char *name)
{
    int n = mccard_list_saves(port, NULL, 0);
    if (n <= 0)
        return 0;
    mc_save_info *l = (mc_save_info *)calloc((size_t)n, sizeof *l);
    int found = 0;
    if (l) {
        n = mccard_list_saves(port, l, n);
        for (int i = 0; i < n && !found; i++)
            found = !strcmp(l[i].dir, name);
        free(l);
    }
    return found;
}

static void remove_dir(int port, const mc_src_dir *d)
{
    char p[MC_PATH_MAX];
    for (int k = 0; k < d->nfiles; k++) {
        snprintf(p, sizeof p, "/%s/%s", d->name, d->files[k].name);
        mccard_delete(port, p);
    }
    snprintf(p, sizeof p, "/%s", d->name);
    mccard_delete(port, p);
}

int mc_src_import(const mc_src_card *card, int i, int port, int force, char *err, size_t errcap)
{
    if (!card || i < 0 || i >= card->ndirs || !mccard_inited()) {
        seterr(err, errcap, "nothing to import%s", NULL);
        return -1;
    }
    const mc_src_dir *d = &card->dirs[i];
    int type = 0, freec = 0, fmt = 0;
    int r = mccard_getinfo(port, &type, &freec, &fmt);
    if (r == MC_RES_CHANGEDCARD)
        r = mccard_getinfo(port, &type, &freec, &fmt);
    if (r < 0 || !mccard_present(port)) {
        seterr(err, errcap, "no card in the slot%s", NULL);
        return -1;
    }
    if (!mccard_formatted(port)) {
        seterr(err, errcap, "the port's card is not formatted (start the game once and let it format)%s", NULL);
        return -1;
    }
    int exists = port_has_dir(port, d->name);
    if (exists && !force)
        return 1;
    char top[MC_PATH_MAX];
    snprintf(top, sizeof top, "/%s", d->name);
    if (exists) {
        /* the save being replaced is snapshotted by the card model on this first change
         * (a no-op setinfo); then no more snapshots until the import is done */
        mc_dirent keep;
        memset(&keep, 0, sizeof keep);
        mccard_setinfo(port, top, &keep, 0);
    }
    mccard_backup_hold(port, top, 1);
    r = mc_import_dir(d, port, exists, err, errcap);
    mccard_backup_hold(port, top, 0);
    return r;
}

static int mc_import_dir(const mc_src_dir *d, int port, int exists, char *err, size_t errcap)
{
    char p[MC_PATH_MAX];
    int r;
    if (exists) {
        /* replace: the files the source does not have go (the card model snapshots the
         * finished save on its first change: saves/backups) */
        mc_dirent e[64];
        snprintf(p, sizeof p, "/%s/*", d->name);
        int n = mccard_getdir(port, p, 0, 64, e);
        for (int k = 0; k < n; k++) {
            if (!(e[k].attr & MC_ATTR_FILE))
                continue;
            int keep = 0;
            for (int j = 0; j < d->nfiles && !keep; j++)
                keep = !strcmp(d->files[j].name, e[k].name);
            if (!keep) {
                char fp[MC_PATH_MAX + MC_NAME_MAX];
                snprintf(fp, sizeof fp, "/%s/%s", d->name, e[k].name);
                mccard_delete(port, fp);
            }
        }
    } else {
        snprintf(p, sizeof p, "/%s", d->name);
        r = mccard_open(port, p, MC_O_MKDIR);
        if (r < 0) {
            seterr(err, errcap, "cannot create the directory (card result %s)", r == MC_RES_FULLDEVICE ? "full" : "error");
            return -1;
        }
    }
    for (int k = 0; k < d->nfiles; k++) {
        const mc_src_file *f = &d->files[k];
        snprintf(p, sizeof p, "/%s/%s", d->name, f->name);
        int fd = mccard_open(port, p, MC_O_WRONLY | MC_O_CREAT | MC_O_TRUNC);
        int ok = fd >= 0;
        uint32_t off = 0;
        while (ok && off < f->len) {
            int chunk = f->len - off > 65536 ? 65536 : (int)(f->len - off);
            int w = mccard_write(fd, f->data + off, chunk);
            if (w != chunk)
                ok = 0;
            else
                off += (uint32_t)w;
        }
        if (fd >= 0 && mccard_close(fd) < 0)
            ok = 0;
        if (!ok) {
            seterr(err, errcap, "writing %s failed (the card is full or the host refused the write)", f->name);
            if (!exists)
                remove_dir(port, d);
            return -1;
        }
        if (f->has_time) {
            mc_dirent info;
            memset(&info, 0, sizeof info);
            info.created = f->ctime;
            info.modified = f->mtime;
            info.attr = f->mode;
            mccard_setinfo(port, p, &info, MC_INFO_CTIME | MC_INFO_MTIME | MC_INFO_ATTR);
        }
    }
    if (d->has_time) {
        mc_dirent info;
        memset(&info, 0, sizeof info);
        info.created = d->ctime;
        info.modified = d->mtime;
        info.attr = d->mode;
        snprintf(p, sizeof p, "/%s", d->name);
        mccard_setinfo(port, p, &info, MC_INFO_CTIME | MC_INFO_MTIME | MC_INFO_ATTR);
    }
    return 0;
}

/* ---- command line ---- */
int mc_cli_arg(mc_cli_opts *o, int argc, char **argv, int *i)
{
    const char *a = argv[*i];
    const char *v = *i + 1 < argc ? argv[*i + 1] : NULL;
    if (!strcmp(a, "--list-saves")) { o->list_saves = 1; return 1; }
    if (!strcmp(a, "--import-force")) { o->import_force = 1; return 1; }
    if (!strcmp(a, "--import-list")) { o->import_list = 1; return 1; }
    if (!strcmp(a, "--name-save") || !strcmp(a, "--import-card") || !strcmp(a, "--import-save") ||
        !strcmp(a, "--import-slot")) {
        if (!v)
            return -1;
        (*i)++;
        if (!strcmp(a, "--name-save")) o->name_save = v;
        else if (!strcmp(a, "--import-card")) o->import_card = v;
        else if (!strcmp(a, "--import-save")) o->import_glob = v;
        else {
            o->import_slot = atoi(v);
            if (o->import_slot != 1 && o->import_slot != 2)
                return -1;
        }
        return 1;
    }
    return 0;
}

int mc_cli_wanted(const mc_cli_opts *o)
{
    return o->list_saves || o->name_save || o->import_card;
}

static void local_clock(void *u, mc_datetime *t)
{
    (void)u;
    time_t now = time(NULL);
    struct tm *tm = localtime(&now);
    memset(t, 0, sizeof *t);
    if (!tm)
        return;
    t->sec = (uint8_t)tm->tm_sec;
    t->min = (uint8_t)tm->tm_min;
    t->hour = (uint8_t)tm->tm_hour;
    t->day = (uint8_t)tm->tm_mday;
    t->month = (uint8_t)(tm->tm_mon + 1);
    t->year = (uint16_t)(tm->tm_year + 1900);
}

static void print_card(int port, FILE *out)
{
    fprintf(out, "card %d (%s/):", port + 1, mccard_slot_name(port));
    if (!mccard_present(port)) {
        fprintf(out, " no card\n");
        return;
    }
    if (!mccard_formatted(port)) {
        fprintf(out, " unformatted\n");
        return;
    }
    int n = mccard_list_saves(port, NULL, 0);
    fprintf(out, " %d director%s, %u KB free\n", n, n == 1 ? "y" : "ies", (unsigned)mccard_free(port));
    if (n <= 0)
        return;
    mc_save_info *l = (mc_save_info *)calloc((size_t)n, sizeof *l);
    if (!l)
        return;
    n = mccard_list_saves(port, l, n);
    for (int i = 0; i < n; i++) {
        const mc_save_info *s = &l[i];
        char meta[400] = "";
        if (s->has_meta)
            mc_save_meta_line(&s->meta, meta, sizeof meta);
        fprintf(out, "  %-24s %04u-%02u-%02u %02u:%02u  %4u KB  %s\n", s->dir, s->mtime.year, s->mtime.month,
                s->mtime.day, s->mtime.hour, s->mtime.min, (unsigned)s->kb, s->title[0] ? s->title : "(no icon.sys)");
        if (s->name[0] || meta[0])
            fprintf(out, "      %s%s%s\n", s->name[0] ? s->name : "", s->name[0] && meta[0] ? " | " : "", meta);
    }
    free(l);
}

int mc_cli_run(const mc_cli_opts *o, const char *root, int backup_keep, FILE *out)
{
    int rc = 0;
    mc_src_card src;
    memset(&src, 0, sizeof src);
    int port = (o->import_slot ? o->import_slot : 1) - 1;
    char err[512] = "";
    if (o->import_card) {
        if (mc_src_open(o->import_card, &src, err, sizeof err)) {
            fprintf(out, "rg-game: --import-card %s: %s\n", o->import_card, err);
            return 1;
        }
        const char *g = o->import_glob ? o->import_glob : "BASCUS-97490LV5RG_*";
        fprintf(out, "%s: %s card, %d save director%s\n", o->import_card,
                src.kind == 2 ? "PCSX2 folder" : src.ecc ? "8 MB image (ECC)" : "8 MB image (raw)", src.ndirs,
                src.ndirs == 1 ? "y" : "ies");
        for (int i = 0; i < src.ndirs; i++) {
            const mc_src_dir *d = &src.dirs[i];
            uint32_t kb = 0;
            const mc_src_file *data = NULL;
            for (int k = 0; k < d->nfiles; k++) {
                kb += (d->files[k].len + 1023u) / 1024u;
                if (!strcmp(d->files[k].name, d->name))
                    data = &d->files[k];
            }
            char meta[400] = "";
            mc_save_meta sm;
            if (data && mc_save_meta_parse(data->data, data->len, &sm) == 0)
                mc_save_meta_line(&sm, meta, sizeof meta);
            fprintf(out, "  %c %-24s %4u KB  %s%s%s\n", mc_glob(g, d->name) ? '*' : ' ', d->name, (unsigned)kb,
                    d->title[0] ? d->title : "(no icon.sys)", meta[0] ? "  | " : "", meta);
        }
        if (o->import_list) {
            mc_src_free(&src);
            return 0;
        }
    }
    mccard_config mc;
    mccard_default_config(&mc);
    mc.root = root;
    mc.clock = local_clock;
    mc.backup_keep = backup_keep;
    if (mccard_init(&mc) != 0) {
        fprintf(out, "rg-game: the memory cards under %s are unavailable\n", root ? root : "saves");
        mc_src_free(&src);
        return 1;
    }
    if (o->import_card) {
        const char *g = o->import_glob ? o->import_glob : "BASCUS-97490LV5RG_*";
        int n = 0;
        for (int i = 0; i < src.ndirs; i++) {
            if (!mc_glob(g, src.dirs[i].name))
                continue;
            n++;
            int r = mc_src_import(&src, i, port, o->import_force, err, sizeof err);
            if (r == 0)
                fprintf(out, "imported %s into card %d\n", src.dirs[i].name, port + 1);
            else if (r == 1) {
                fprintf(out, "skipped %s: card %d has it already (--import-force replaces it; the old one is backed up)\n",
                        src.dirs[i].name, port + 1);
                rc = 1;
            } else {
                fprintf(out, "failed %s: %s\n", src.dirs[i].name, err);
                rc = 1;
            }
        }
        if (!n) {
            fprintf(out, "no save directory on %s matches %s\n", o->import_card, g);
            rc = 1;
        }
    }
    if (o->name_save) {
        /* C:NN=TEXT or C:DIRECTORY=TEXT */
        const char *v = o->name_save, *eq = strchr(v, '=');
        int c = (v[0] == '1' || v[0] == '2') && v[1] == ':' ? v[0] - '1' : -1;
        char dir[MC_NAME_MAX] = "";
        if (c >= 0 && eq && eq > v + 2 && (size_t)(eq - (v + 2)) < sizeof dir) {
            size_t dl = (size_t)(eq - (v + 2));
            int digits = 1;
            for (size_t k = 0; k < dl; k++)
                digits &= v[2 + k] >= '0' && v[2 + k] <= '9';
            if (digits && dl <= 2)
                snprintf(dir, sizeof dir, "BASCUS-97490LV5RG_%02d", atoi(v + 2));
            else {
                memcpy(dir, v + 2, dl);
                dir[dl] = 0;
            }
        }
        if (!dir[0] || mccard_set_save_name(c, dir, eq + 1) != 0) {
            fprintf(out, "rg-game: --name-save %s: expected CARD:NN=name (CARD 1 or 2, NN the save's number)\n", v);
            rc = rc ? rc : 2;
        } else if (eq[1])
            fprintf(out, "named %s on card %d: %s\n", dir, c + 1, eq + 1);
        else
            fprintf(out, "removed the name of %s on card %d\n", dir, c + 1);
    }
    if (o->list_saves || o->import_card || o->name_save)
        for (int p = 0; p < MC_PORTS; p++)
            print_card(p, out);
    mccard_shutdown();
    mc_src_free(&src);
    return rc;
}
