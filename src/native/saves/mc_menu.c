/* SPDX-License-Identifier: CC0-1.0 */
/* The settings overlay's save manager on the card model (docs/SAVES.md "Saves in the
 * settings overlay"): rg_menu_saves_ops for rg_menu_set_saves.  Lists a card's saves with
 * their names and summaries, names them (mccard_set_save_name), lists and imports the saves
 * of a PCSX2 memory card (mc_import.c: read-only source, crash-safe writes, a replaced save
 * backed up first) and browses host folders for the card file.
 *
 * Runs on the thread that pumps the host (the game thread between fields), so the card
 * model is never used by the game at the same moment; an import is refused while the game
 * has a card file open (a save in progress), and marks the card changed afterwards so the
 * game rescans it as after a card swap. */
#include "mc_menu.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <dirent.h>
#include <sys/stat.h>
#endif

#include "mc_import.h"
#include "mccard.h"

static void msgf(char *msg, size_t cap, const char *fmt, const char *a, int b)
{
    if (msg && cap) snprintf(msg, cap, fmt, a, b);
}

static int is_game_dir(const char *d) { return !strncmp(d, "BASCUS-97490LV5RG_", 18); }

static void when_text(const mc_datetime *t, char *out, size_t cap)
{
    if (!t->year) { out[0] = 0; return; }
    snprintf(out, cap, "%04u-%02u-%02u %02u:%02u", t->year, t->month, t->day, t->hour, t->min);
}

static int ops_list(void *user, int card, rg_menu_save *out, int cap, char *msg, size_t msgcap)
{
    (void)user;
    if (!mccard_inited()) { msgf(msg, msgcap, "%sthe memory cards are not loaded", "", 0); return -1; }
    if (!mccard_present(card)) { msgf(msg, msgcap, "%sno card in this slot (saves/card%d/ is missing)", "", card + 1); return -1; }
    if (!mccard_formatted(card)) { msgf(msg, msgcap, "%sthe card is not formatted", "", 0); return -1; }
    int n = mccard_list_saves(card, NULL, 0);
    if (n <= 0) return n < 0 ? -1 : 0;
    mc_save_info *l = (mc_save_info *)calloc((size_t)n, sizeof *l);
    if (!l) return -1;
    n = mccard_list_saves(card, l, n);
    int k = 0;
    for (int i = 0; i < n && k < cap; i++) {
        rg_menu_save *o = &out[k++];
        memset(o, 0, sizeof *o);
        snprintf(o->dir, sizeof o->dir, "%s", l[i].dir);
        snprintf(o->name, sizeof o->name, "%s", l[i].name);
        snprintf(o->title, sizeof o->title, "%s", l[i].title);
        if (l[i].has_meta) mc_save_meta_line(&l[i].meta, o->meta, sizeof o->meta);
        when_text(&l[i].mtime, o->when, sizeof o->when);
        o->game = is_game_dir(o->dir);
    }
    free(l);
    return k;
}

static int ops_rename(void *user, int card, const char *dir, const char *name, char *msg, size_t msgcap)
{
    (void)user;
    if (mccard_set_save_name(card, dir, name) != 0) {
        msgf(msg, msgcap, "%s could not be named (saves/card%d.names not writable?)", dir, card + 1);
        return -1;
    }
    return 0;
}

/* the directory names of card `card` (count; *names to free) */
static int card_dirs(int card, mc_save_info **names)
{
    *names = NULL;
    if (!mccard_present(card) || !mccard_formatted(card)) return 0;
    int n = mccard_list_saves(card, NULL, 0);
    if (n <= 0) return 0;
    *names = (mc_save_info *)calloc((size_t)n, sizeof **names);
    return *names ? mccard_list_saves(card, *names, n) : 0;
}

static void src_save(const mc_src_dir *d, rg_menu_save *o)
{
    memset(o, 0, sizeof *o);
    snprintf(o->dir, sizeof o->dir, "%s", d->name);
    snprintf(o->title, sizeof o->title, "%s", d->title);
    for (int k = 0; k < d->nfiles; k++)
        if (!strcmp(d->files[k].name, d->name)) {
            mc_save_meta sm;
            if (mc_save_meta_parse(d->files[k].data, d->files[k].len, &sm) == 0)
                mc_save_meta_line(&sm, o->meta, sizeof o->meta);
        }
    if (d->has_time) when_text(&d->mtime, o->when, sizeof o->when);
    o->game = is_game_dir(o->dir);
}

static int ops_src_list(void *user, const char *path, int card, rg_menu_save *out, int cap, char *msg, size_t msgcap)
{
    (void)user;
    mc_src_card src;
    memset(&src, 0, sizeof src);
    if (mc_src_open(path, &src, msg, msgcap) != 0) return -1;
    mc_save_info *have;
    int nh = card_dirs(card, &have);
    int k = 0;
    for (int i = 0; i < src.ndirs && k < cap; i++) {
        src_save(&src.dirs[i], &out[k]);
        for (int j = 0; j < nh; j++)
            if (!strcmp(have[j].dir, src.dirs[i].name)) out[k].exists = 1;
        k++;
    }
    free(have);
    mc_src_free(&src);
    return k;
}

static int ops_src_import(void *user, const char *path, int card, const char *dir, int force, char *msg, size_t msgcap)
{
    (void)user;
    if (!mccard_present(card) || !mccard_formatted(card)) {
        msgf(msg, msgcap, "%scard %d is missing or not formatted", "", card + 1);
        return -1;
    }
    if (mccard_open_count() > 0) {
        msgf(msg, msgcap, "%sthe game is using a memory card right now (saving or loading); try again in a moment", "", 0);
        return -1;
    }
    mc_src_card src;
    memset(&src, 0, sizeof src);
    char err[256] = "";
    if (mc_src_open(path, &src, err, sizeof err) != 0) {
        msgf(msg, msgcap, "%s", err, 0);
        return -1;
    }
    int idx = -1;
    for (int i = 0; i < src.ndirs; i++)
        if (!strcmp(src.dirs[i].name, dir)) idx = i;
    int r;
    if (idx < 0) {
        msgf(msg, msgcap, "%s is no longer on the card file", dir, 0);
        r = -1;
    } else {
        r = mc_src_import(&src, idx, card, force, err, sizeof err);
        if (r == 0) {
            mccard_mark_changed(card);   /* the game rescans it, as after a card swap */
            if (force) msgf(msg, msgcap, "%s replaced on card %d (the previous one is in saves/backups)", dir, card + 1);
            else msgf(msg, msgcap, "%s imported into card %d", dir, card + 1);
        } else if (r == 1) {
            if (msg && msgcap) snprintf(msg, msgcap, "Card %d already has %s", card + 1, dir);
        } else {
            char t[400];
            snprintf(t, sizeof t, "%s: import failed: %s", dir, err);
            msgf(msg, msgcap, "%s", t, 0);
            r = -1;
        }
    }
    mc_src_free(&src);
    return r;
}

/* ---- the file picker ---- */
#define CARD_RAW (8u << 20)
#define CARD_ECC (CARD_RAW / 512u * 528u)

static int has_card_ext(const char *n)
{
    const char *e = strrchr(n, '.');
    if (!e) return 0;
    char x[8];
    size_t L = strlen(e);
    if (L >= sizeof x) return 0;
    for (size_t i = 0; i <= L; i++) x[i] = (char)tolower((unsigned char)e[i]);
    return !strcmp(x, ".ps2") || !strcmp(x, ".mcd") || !strcmp(x, ".mc2") || !strcmp(x, ".bin");
}

static int cmp_file(const void *a, const void *b)
{
    const rg_menu_file *x = (const rg_menu_file *)a, *y = (const rg_menu_file *)b;
    int kx = x->kind == RG_FILE_DIR ? 0 : 1, ky = y->kind == RG_FILE_DIR ? 0 : 1;
    if (kx != ky) return kx - ky;
#ifdef _WIN32
    return _stricmp(x->name, y->name);
#else
    return strcmp(x->name, y->name);
#endif
}

static int host_is_dir(const char *p)
{
#ifdef _WIN32
    DWORD a = GetFileAttributesA(p);
    return a != INVALID_FILE_ATTRIBUTES && (a & FILE_ATTRIBUTE_DIRECTORY);
#else
    struct stat st;
    return stat(p, &st) == 0 && S_ISDIR(st.st_mode);
#endif
}

static void path_join(const char *dir, const char *name, char *out, size_t cap)
{
    size_t L = strlen(dir);
    int sep = L && (dir[L - 1] == '/' || dir[L - 1] == '\\');
#ifdef _WIN32
    snprintf(out, cap, "%s%s%s", dir, sep || !L ? "" : "\\", name);
#else
    snprintf(out, cap, "%s%s%s", dir, sep || !L ? "" : "/", name);
#endif
}

/* the parent of dir ("" at a root: on Windows the drive list) */
static void path_parent(const char *dir, char *out, size_t cap)
{
    char t[1024];
    snprintf(t, sizeof t, "%s", dir);
    size_t L = strlen(t);
    while (L > 1 && (t[L - 1] == '/' || t[L - 1] == '\\')) t[--L] = 0;
#ifdef _WIN32
    if (L == 2 && t[1] == ':') { snprintf(out, cap, ":drives"); return; }
#else
    if (!strcmp(t, "/")) { snprintf(out, cap, "/"); return; }
#endif
    char *s = strrchr(t, '/'), *b = strrchr(t, '\\');
    if (b > s) s = b;
    if (!s) { snprintf(out, cap, ":drives"); return; }
    if (s == t) s[1] = 0;
#ifdef _WIN32
    else if (s == t + 2 && t[1] == ':') s[1] = 0;   /* "C:\" */
#endif
    else *s = 0;
    snprintf(out, cap, "%s", t);
}

void mc_menu_start_dir(char *out, size_t cap)
{
    out[0] = 0;
    const char *env = getenv("RG_IMPORT_DIR");
    if (env && *env && host_is_dir(env)) { snprintf(out, cap, "%s", env); return; }
#ifdef _WIN32
    const char *home = getenv("USERPROFILE");
    const char *sub[] = { "\\Documents\\PCSX2\\memcards", "\\OneDrive\\Documents\\PCSX2\\memcards" };
#else
    const char *home = getenv("HOME");
    const char *sub[] = { "/.config/PCSX2/memcards", "/Documents/PCSX2/memcards" };
#endif
    for (size_t i = 0; home && i < sizeof sub / sizeof sub[0]; i++) {
        char p[1024];
        snprintf(p, sizeof p, "%s%s", home, sub[i]);
        if (host_is_dir(p)) { snprintf(out, cap, "%s", p); return; }
    }
#ifdef _WIN32
    if (!GetCurrentDirectoryA((DWORD)cap, out)) snprintf(out, cap, "C:\\");
#else
    snprintf(out, cap, "%s", home && *home ? home : "/");
#endif
}

typedef struct blist {
    rg_menu_file *out;
    int cap, n;
    const char *dir;
} blist;

static void b_add(blist *b, const char *name, int kind)
{
    if (b->n >= b->cap || strlen(name) >= sizeof b->out[0].name) return;
    snprintf(b->out[b->n].name, sizeof b->out[0].name, "%s", name);
    b->out[b->n].kind = kind;
    b->n++;
}

static void b_entry(blist *b, const char *name, int dir, unsigned long long size)
{
    if (name[0] == '.') return;
    char p[1024], sb[1100];
    path_join(b->dir, name, p, sizeof p);
    if (dir) {
        snprintf(sb, sizeof sb, "%s%c_pcsx2_superblock", p,
#ifdef _WIN32
                 '\\'
#else
                 '/'
#endif
        );
        FILE *f = fopen(sb, "rb");
        if (f) { fclose(f); b_add(b, name, RG_FILE_FOLDER_CARD); }
        else b_add(b, name, RG_FILE_DIR);
    } else if (has_card_ext(name) || size == CARD_RAW || size == CARD_ECC) {
        b_add(b, name, RG_FILE_CARD);
    }
}

static int ops_browse(void *user, const char *dir, rg_menu_file *out, int cap, char *resolved, size_t rcap,
                      char *msg, size_t msgcap)
{
    (void)user;
    char d[1024];
    if (!dir || !dir[0]) mc_menu_start_dir(d, sizeof d);
    else snprintf(d, sizeof d, "%s", dir);
    blist b = { out, cap, 0, d };
#ifdef _WIN32
    if (!strcmp(d, ":drives")) {
        if (resolved && rcap) resolved[0] = 0;
        DWORD mask = GetLogicalDrives();
        for (int i = 0; i < 26; i++)
            if (mask & (1u << i)) {
                char n[4] = { (char)('A' + i), ':', 0, 0 };
                b_add(&b, n, RG_FILE_DRIVE);
            }
        return b.n;
    }
    char full[1024];
    if (!GetFullPathNameA(d, sizeof full, full, NULL)) snprintf(full, sizeof full, "%s", d);
    snprintf(d, sizeof d, "%s", full);
    if (!host_is_dir(d)) { msgf(msg, msgcap, "%s is not a folder", d, 0); return -1; }
    b_add(&b, "..", RG_FILE_UP);
    char pat[1100];
    path_join(d, "*", pat, sizeof pat);
    WIN32_FIND_DATAA fd;
    HANDLE h = FindFirstFileA(pat, &fd);
    if (h != INVALID_HANDLE_VALUE) {
        do {
            if (fd.dwFileAttributes & (FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM)) continue;
            unsigned long long sz = ((unsigned long long)fd.nFileSizeHigh << 32) | fd.nFileSizeLow;
            b_entry(&b, fd.cFileName, (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0, sz);
        } while (FindNextFileA(h, &fd));
        FindClose(h);
    }
#else
    if (!strcmp(d, ":drives")) snprintf(d, sizeof d, "/");
    char full[4096];
    if (realpath(d, full)) snprintf(d, sizeof d, "%s", full);
    DIR *dd = opendir(d);
    if (!dd) { msgf(msg, msgcap, "%s is not a folder", d, 0); return -1; }
    b_add(&b, "..", RG_FILE_UP);
    struct dirent *e;
    while ((e = readdir(dd)) != NULL) {
        char p[1100];
        struct stat st;
        path_join(d, e->d_name, p, sizeof p);
        if (stat(p, &st) == 0) b_entry(&b, e->d_name, S_ISDIR(st.st_mode), (unsigned long long)st.st_size);
    }
    closedir(dd);
#endif
    if (b.n > 1) qsort(out + 1, (size_t)(b.n - 1), sizeof *out, cmp_file);
    if (resolved && rcap) snprintf(resolved, rcap, "%s", d);
    return b.n;
}

static void ops_join(void *user, const char *dir, const char *name, int kind, char *out, size_t cap)
{
    (void)user;
    if (kind == RG_FILE_UP) path_parent(dir, out, cap);
    else if (kind == RG_FILE_DRIVE) snprintf(out, cap, "%s\\", name);
    else path_join(dir, name, out, cap);
}

static const rg_menu_saves_ops k_ops = {
    NULL, ops_list, ops_rename, ops_src_list, ops_src_import, ops_browse, ops_join,
};

const rg_menu_saves_ops *mc_menu_ops(void) { return &k_ops; }
