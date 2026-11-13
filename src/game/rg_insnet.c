/* SPDX-License-Identifier: CC0-1.0 */
/* Online Insectron 2-Player Battle: the session layer (lane insnet 2026-11-12,
 * docs/INSECTRON-VERSUS.md "Online 2-Player Battle").
 *
 * A session is a fresh power-on of the game on both machines with identical inputs:
 *   - the same session saves: card 1 = the host's chosen save as FILE 01, card 2 = the
 *     joiner's chosen save as FILE 01 (built in <saves>/netplay/session/, the player's own
 *     saves are only ever read);
 *   - the host's game-affecting settings (gameplay.*, accessibility.*), locked for the session;
 *   - a fixed scripted prefix (title -> INSECTRON -> 2-Player Battle -> controllers 1 / 2 ->
 *     load both players' data) on port 0, port 1 neutral, both ports connected;
 *   - from the hand-over VBlank on, lock-step: port 0 = the host's pad, port 1 = the joiner's,
 *     each published `delay` VBlanks ahead (rg_net_stream), so both sides read exactly the
 *     same words at the same VBlanks.
 * Every 60 fields both sides exchange the run hash; a difference is a desync (reported, the
 * session stops).  rg_net.h has the transport. */
#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <winsock2.h>
#include <windows.h>
#include <direct.h>
#include <process.h>
#define rg_mkdir(p) _mkdir(p)
#else
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#define rg_mkdir(p) mkdir((p), 0755)
#endif
#ifndef _WIN32
#include <dirent.h>
#endif
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "host.h"
#include "mccard.h"
#include "rg_insnet.h"
#include "rg_net.h"
#include "rg_runtime.h"
#include "rg_settings.h"

#ifndef RG_INSNET_BUILD
#define RG_INSNET_BUILD 0x0ull
#endif

/* the game's VBlank counter (the key of every input script) */
extern uint32_t D_004810C4[];

#define SAVE_DIR_PREFIX "BASCUS-97490LV5RG_"
#define SAVE_DATA_BYTES 113664u
#define SAVE_ICONSYS_BYTES 964u
#define SAVE_ICO_MAX (64u * 1024u)
#define HASH_EVERY 60u
#define HASH_RING 64

/* the built-in prefix: power-on -> INSMENU 2-Player menu with both players loaded, cursor on
 * "Begin battle".  Session saves hold exactly one save per card, so the route is fixed.  Generous
 * gaps (~300 fields) between presses; the hand-over VBlank is the first after the last press. */
static const char k_prefix[] =
    "# rg_insnet built-in session prefix (docs/INSECTRON-VERSUS.md)\n"
    "1880 1883 DOWN\n"
    "1900 1905 CROSS\n"
    "3010 3013 CROSS\n"
    "3410 3413 CROSS\n"
    "3660 3663 CROSS\n"
    "4010 4013 CROSS\n"
    "4410 4413 CROSS\n"
    "4800 4803 CROSS\n"
    "5090 5093 RIGHT\n"
    "5100 5103 CROSS\n"
    "5400 5403 CROSS\n"
    "5450 5453 CROSS\n"
    "5700 5703 CROSS\n"
    "6000 6003 CROSS\n"
    "6300 6303 CROSS\n"
    "6700 6703 CROSS\n"
    /* (measured, out/insnet/prefix_check: leaving a cage display takes two presses) */
    "8100 8103 CROSS\n"        /* P1's cage display */
    "8500 8503 CROSS\n"        /* -> back (cursor to Load Player 2's Data) */
    "8800 8803 CROSS\n"        /* Load Player 2's Data */
    "9100 9103 DOWN\n"         /* MEMORY CARD slot 2 */
    "9130 9133 CROSS\n"
    "9600 9603 CROSS\n"        /* FILE 01 */
    "9900 9903 CROSS\n"        /* Load? Yes */
    "10400 10403 CROSS\n"      /* File 1 loaded */
    "11800 11803 CROSS\n";     /* P2's cage display -> back (cursor to Battle Start!!; if the cage is
                                * still up, the players' own press leaves it) */
#define K_PREFIX_HANDOVER 12100u

typedef struct key_range { uint32_t first, last; uint16_t buttons; } key_range;

static struct {
    int on;                     /* a session is running (or was) */
    int role;                   /* 0 host, 1 join */
    int phase;                  /* 0 off, 1 prefix, 2 live, 3 ended */
    int lost;                   /* connection lost / ended: peer port reads neutral */
    int exit_at_end;            /* --net-exit-at-end (tests) */
    int quiet;
    int solo;
    int left;                   /* the players left the 2-Player Battle */
    int relaunch_pending;
    char why[256];
    rg_net_sock *sock;
    int delay;
    uint32_t handover;
    rg_input_script prefix;
    /* local pad from a script (tests): sparse ranges, no length limit */
    key_range *loc;
    int nloc;
    int have_loc;
    rg_net_stream *mine, *peer;
    int64_t last_pub;
    uint64_t last_rx_ms;
    int timeout_ms, handover_timeout_ms;
    /* sync check */
    uint64_t my_hash[HASH_RING], peer_hash[HASH_RING];
    uint32_t my_hash_f[HASH_RING], peer_hash_f[HASH_RING];
    uint32_t checks, last_check_field;
    /* settings lock */
    char locked[2048];
    rg_settings *settings;
    FILE *log;
    uint64_t waits, wait_ms_total, wait_ms_max;
    uint64_t stall_hist[5];
    int realtime;
    uint64_t rt_t0, rt_k0;
    char session_saves[1024];
} N;

/* ------------------------------------------------------------------ options */
static struct {
    int host_port;              /* --net-host PORT */
    char join[300];             /* --net-join ADDR[:PORT] */
    char save[1024];            /* --net-save CARD:NN or a save folder */
    char input[1024];           /* --net-input SCRIPT (local pad, tests) */
    char prefix[1024];          /* --net-prefix SCRIPT */
    char log[1024];             /* --net-log FILE */
    char hofile[1024];          /* --net-handover-file FILE: bytes the first process read for us */
    char name[16];
    int delay;
    int handover;
    int timeout_s;
    int exit_at_end;
    uint64_t handle;            /* --net-handle H (relaunch hand-over) */
    int solo;                   /* --net-solo: no network, port 1 mirrors port 0 (match drivers) */
    int role;                   /* --net-role host|join (with --net-handle); -1 = from --net-join */
    int relaunch;               /* --net-relaunch: started by the INSMENU flow (rg_insnet_ui.c) */
    char save2[1024];           /* --net-save2: player 2's save for --net-solo */
    int any;
} O = {.delay = 4, .timeout_s = 15, .role = -1};

static void nlog(const char *fmt, ...)
{
    char b[512];
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(b, sizeof b, fmt, ap);
    va_end(ap);
    if (!N.quiet) fprintf(stderr, "rg_insnet: %s\n", b);
    if (N.log) {
        fprintf(N.log, "%s\n", b);
        fflush(N.log);
    }
}

static int g_menu_port = RG_NET_DEFAULT_PORT;   /* --net-port */

int rg_insnet_arg(const char *a, const char *v)
{
    if (!strncmp(a, "--net-", 6)) O.any = 1;
    if (!strcmp(a, "--net-relaunch")) {
        O.relaunch = 1;   /* started from the game's menus: back to the normal game at the end */
        return 1;
    }
    if (!strcmp(a, "--net-solo")) {
        O.solo = 1;
        return 1;
    }
    if (!strcmp(a, "--net-exit-at-end")) {
        O.exit_at_end = 1;
        return 1;
    }
    if (!v) return strncmp(a, "--net-", 6) ? 0 : -1;
    if (!strcmp(a, "--net-host")) {
        O.host_port = atoi(v);
        if (O.host_port <= 0 || O.host_port > 65535) return -1;
    } else if (!strcmp(a, "--net-join")) snprintf(O.join, sizeof O.join, "%s", v);
    else if (!strcmp(a, "--net-save")) snprintf(O.save, sizeof O.save, "%s", v);
    else if (!strcmp(a, "--net-save2")) snprintf(O.save2, sizeof O.save2, "%s", v);
    else if (!strcmp(a, "--net-input")) snprintf(O.input, sizeof O.input, "%s", v);
    else if (!strcmp(a, "--net-prefix")) snprintf(O.prefix, sizeof O.prefix, "%s", v);
    else if (!strcmp(a, "--net-log")) snprintf(O.log, sizeof O.log, "%s", v);
    else if (!strcmp(a, "--net-handover-file")) snprintf(O.hofile, sizeof O.hofile, "%s", v);
    else if (!strcmp(a, "--net-name")) snprintf(O.name, sizeof O.name, "%s", v);
    else if (!strcmp(a, "--net-port")) {
        /* the port the menus host on (default 7490), and the joiner's default */
        g_menu_port = atoi(v);
        if (g_menu_port <= 0 || g_menu_port > 65535) return -1;
    }
    else if (!strcmp(a, "--net-delay")) {
        O.delay = atoi(v);
        if (O.delay < 1 || O.delay > 60) return -1;
    } else if (!strcmp(a, "--net-handover")) O.handover = atoi(v);
    else if (!strcmp(a, "--net-timeout")) {
        O.timeout_s = atoi(v);
        if (O.timeout_s < 2 || O.timeout_s > 3600) return -1;
    } else if (!strcmp(a, "--net-handle")) O.handle = strtoull(v, NULL, 0);
    else if (!strcmp(a, "--net-role")) {
        if (!strcmp(v, "host")) O.role = 0;
        else if (!strcmp(v, "join")) O.role = 1;
        else return -1;
    }
    else
        return strncmp(a, "--net-", 6) ? 0 : -1;
    return 2;
}

/* the port the INSMENU flow hosts on / calls by default: --net-port, else $RG_NET_PORT, else 7490 */
int rg_insnet_menu_port(void)
{
    const char *e = getenv("RG_NET_PORT");
    if (g_menu_port == RG_NET_DEFAULT_PORT && e && atoi(e) > 0 && atoi(e) <= 65535) return atoi(e);
    return g_menu_port;
}

static int g_argc_s;
static char **g_argv_s;
void rg_insnet_set_argv(int argc, char **argv)
{
    g_argc_s = argc;
    g_argv_s = argv;
    rg_insnet_ui_set_argv(argc, argv);
}

int rg_insnet_wanted(void) { return O.host_port > 0 || O.join[0] || O.handle || O.solo; }
int rg_insnet_active(void) { return N.on && N.phase >= 1 && N.phase < 3; }

/* ---------------------------------------------------------- local scripts */
static int btn_bit(const char *name)
{
    static const char *const names[16] = {"L2", "R2", "L1", "R1", "TRIANGLE", "CIRCLE", "CROSS", "SQUARE",
                                          "SELECT", "L3", "R3", "START", "UP", "RIGHT", "DOWN", "LEFT"};
    for (int i = 0; i < 16; i++)
        if (!strcmp(name, names[i])) return 1 << i;
    return -1;
}

/* "first last KEY[+KEY]" or "vbl KEY" lines, '#' comments (the --input grammar, no length cap) */
static int load_local_script(const char *path, char *err, size_t cap)
{
    FILE *f = fopen(path, "rb");
    if (!f) {
        snprintf(err, cap, "cannot read %s", path);
        return -1;
    }
    char line[512];
    int ln = 0;
    while (fgets(line, sizeof line, f)) {
        ln++;
        char *h = strchr(line, '#');
        if (h) *h = 0;
        char *tok[8];
        int nt = 0;
        for (char *t = strtok(line, " \t\r\n"); t && nt < 8; t = strtok(NULL, " \t\r\n")) tok[nt++] = t;
        if (!nt) continue;
        if (nt < 2 || nt > 3) {
            snprintf(err, cap, "%s:%d: want 'first last KEYS'", path, ln);
            fclose(f);
            return -1;
        }
        uint32_t a = (uint32_t)strtoul(tok[0], NULL, 0), b = nt == 3 ? (uint32_t)strtoul(tok[1], NULL, 0) : a;
        int bits = 0;
        char keys[128];
        snprintf(keys, sizeof keys, "%s", tok[nt - 1]);
        for (char *k = strtok(keys, "+"); k; k = strtok(NULL, "+")) {
            int bb = btn_bit(k);
            if (bb < 0) {
                snprintf(err, cap, "%s:%d: unknown button %s", path, ln, k);
                fclose(f);
                return -1;
            }
            bits |= bb;
        }
        /* a static table: no heap use before rg_runtime_init (a save state's init fingerprint
         * must not depend on the script's length) */
        static key_range table[65536];
        if (N.nloc >= (int)(sizeof table / sizeof table[0]) || b < a) {
            fclose(f);
            snprintf(err, cap, "%s:%d: bad range (or more than 65536 lines)", path, ln);
            return -1;
        }
        N.loc = table;
        N.loc[N.nloc].first = a;
        N.loc[N.nloc].last = b;
        N.loc[N.nloc].buttons = (uint16_t)bits;
        N.nloc++;
    }
    fclose(f);
    N.have_loc = 1;
    return 0;
}

static uint16_t local_script_word(uint32_t vbl)
{
    uint16_t w = 0;
    for (int i = 0; i < N.nloc; i++)
        if (vbl >= N.loc[i].first && vbl <= N.loc[i].last) w |= N.loc[i].buttons;
    return w;
}

/* --------------------------------------------------------------- save files */
typedef struct save_pkg {
    uint8_t *data;      /* the SAVE message body */
    size_t n;
} save_pkg;

static uint8_t *read_all(const char *path, size_t *n, size_t max)
{
    FILE *f = fopen(path, "rb");
    if (!f) return NULL;
    fseek(f, 0, SEEK_END);
    long L = ftell(f);
    fseek(f, 0, SEEK_SET);
    if (L < 0 || (size_t)L > max) {
        fclose(f);
        return NULL;
    }
    uint8_t *b = (uint8_t *)malloc((size_t)L + 1);
    if (b && fread(b, 1, (size_t)L, f) != (size_t)L) {
        free(b);
        b = NULL;
    }
    fclose(f);
    if (b) *n = (size_t)L;
    return b;
}

static int write_all(const char *path, const void *p, size_t n)
{
    FILE *f = fopen(path, "wb");
    if (!f) return -1;
    int ok = fwrite(p, 1, n, f) == n;
    return fclose(f) == 0 && ok ? 0 : -1;
}

/* body: "RGSV" u32 files, then per file: u8 kind (0 icon.sys, 1 RG.ICO, 2 data), u32 size, bytes */
static void put32(uint8_t *p, uint32_t v) { p[0] = (uint8_t)v; p[1] = (uint8_t)(v >> 8); p[2] = (uint8_t)(v >> 16); p[3] = (uint8_t)(v >> 24); }
static uint32_t get32(const uint8_t *p) { return p[0] | (uint32_t)p[1] << 8 | (uint32_t)p[2] << 16 | (uint32_t)p[3] << 24; }

/* resolve --net-save: "CARD:NN" (card 1/2, file number) or a save folder path */
static int save_folder(const char *saves, const char *spec, char *out, size_t cap)
{
    int card = 1, nn = -1;
    if (spec[0] && sscanf(spec, "%d:%d", &card, &nn) == 2 && (card == 1 || card == 2) && nn >= 0 && nn < 100) {
        snprintf(out, cap, "%s/card%d/" SAVE_DIR_PREFIX "%02d", saves, card, nn);
        return 0;
    }
    if (spec[0]) {
        snprintf(out, cap, "%s", spec);
        return 0;
    }
    /* default: the lowest-numbered save on card 1 */
    for (nn = 0; nn < 100; nn++) {
        struct stat st;
        snprintf(out, cap, "%s/card1/" SAVE_DIR_PREFIX "%02d", saves, nn);
        if (!stat(out, &st) && (st.st_mode & S_IFDIR)) return 0;
    }
    return -1;
}

static int pack_save(const char *dir, save_pkg *pk, char *err, size_t cap)
{
    const char *base = strrchr(dir, '/');
#ifdef _WIN32
    const char *bs = strrchr(dir, '\\');
    if (bs > base) base = bs;
#endif
    base = base ? base + 1 : dir;
    if (strncmp(base, SAVE_DIR_PREFIX, strlen(SAVE_DIR_PREFIX))) {
        snprintf(err, cap, "%s is not a Rogue Galaxy save folder", dir);
        return -1;
    }
    char p[1200];
    size_t n[3];
    uint8_t *b[3];
    snprintf(p, sizeof p, "%s/icon.sys", dir);
    b[0] = read_all(p, &n[0], SAVE_ICONSYS_BYTES);
    snprintf(p, sizeof p, "%s/RG.ICO", dir);
    b[1] = read_all(p, &n[1], SAVE_ICO_MAX);
    snprintf(p, sizeof p, "%s/%s", dir, base);
    b[2] = read_all(p, &n[2], SAVE_DATA_BYTES);
    if (!b[0] || !b[1] || !b[2] || n[0] != SAVE_ICONSYS_BYTES || n[2] != SAVE_DATA_BYTES) {
        snprintf(err, cap, "cannot read the save in %s", dir);
        for (int i = 0; i < 3; i++) free(b[i]);
        return -1;
    }
    pk->n = 8 + 3 * 5 + n[0] + n[1] + n[2];
    pk->data = (uint8_t *)malloc(pk->n);
    if (!pk->data) return -1;
    uint8_t *q = pk->data;
    memcpy(q, "RGSV", 4);
    put32(q + 4, 3);
    q += 8;
    for (int i = 0; i < 3; i++) {
        q[0] = (uint8_t)i;
        put32(q + 1, (uint32_t)n[i]);
        memcpy(q + 5, b[i], n[i]);
        q += 5 + n[i];
        free(b[i]);
    }
    return 0;
}

/* validate a peer's SAVE body; files[] point into it */
static int unpack_save(const uint8_t *body, size_t len, const uint8_t *files[3], uint32_t sizes[3], char *err,
                       size_t cap)
{
    if (len < 8 || memcmp(body, "RGSV", 4) || get32(body + 4) != 3) {
        snprintf(err, cap, "the other player's save is not a save");
        return -1;
    }
    size_t off = 8;
    int seen = 0;
    for (int i = 0; i < 3; i++) {
        if (off + 5 > len) goto bad;
        unsigned kind = body[off];
        uint32_t sz = get32(body + off + 1);
        off += 5;
        if (kind > 2 || (seen & (1 << kind)) || sz > len - off) goto bad;
        if ((kind == 0 && sz != SAVE_ICONSYS_BYTES) || (kind == 1 && (sz == 0 || sz > SAVE_ICO_MAX)) ||
            (kind == 2 && sz != SAVE_DATA_BYTES))
            goto bad;
        seen |= 1 << kind;
        files[kind] = body + off;
        sizes[kind] = sz;
        off += sz;
    }
    if (off != len || seen != 7) goto bad;
    /* icon.sys starts with the PS2 icon header "PS2D" */
    if (memcmp(files[0], "PS2D", 4)) goto bad;
    return 0;
bad:
    snprintf(err, cap, "the other player's save is damaged or not a Rogue Galaxy save");
    return -1;
}

/* names in a directory (no "." / ".."), at most max of 64 chars; count */
static int list_dir(const char *path, char names[][64], int max)
{
    int n = 0;
#ifdef _WIN32
    char pat[1200];
    WIN32_FIND_DATAA fd;
    snprintf(pat, sizeof pat, "%s\\*", path);
    HANDLE h = FindFirstFileA(pat, &fd);
    if (h == INVALID_HANDLE_VALUE) return 0;
    do {
        if (!strcmp(fd.cFileName, ".") || !strcmp(fd.cFileName, "..")) continue;
        if (n < max) snprintf(names[n++], 64, "%s", fd.cFileName);
    } while (FindNextFileA(h, &fd));
    FindClose(h);
#else
    DIR *d = opendir(path);
    if (!d) return 0;
    struct dirent *e;
    while ((e = readdir(d))) {
        if (!strcmp(e->d_name, ".") || !strcmp(e->d_name, "..")) continue;
        if (n < max) snprintf(names[n++], 64, "%s", e->d_name);
    }
    closedir(d);
#endif
    return n;
}

static void mkdirs(const char *path)
{
    char p[1200];
    snprintf(p, sizeof p, "%s", path);
    for (char *c = p + 1; *c; c++)
        if (*c == '/' || *c == '\\') {
            char k = *c;
            *c = 0;
            rg_mkdir(p);
            *c = k;
        }
    rg_mkdir(p);
}

static void rm_tree(const char *path, int depth)
{
    if (depth > 4) return;
    static char names[5][256][64];
    int n = list_dir(path, names[depth], 256);
    for (int i = 0; i < n; i++) {
        char p[1200];
        struct stat st;
        snprintf(p, sizeof p, "%s/%s", path, names[depth][i]);
        if (!stat(p, &st) && (st.st_mode & S_IFDIR)) rm_tree(p, depth + 1);
        else remove(p);
    }
#ifdef _WIN32
    _rmdir(path);
#else
    rmdir(path);
#endif
}

/* one card of the session: the save as FILE 01 (folder _00) + a fixed card metadata file */
static int write_card(const char *root, int card, const uint8_t *files[3], const uint32_t sizes[3])
{
    char d[1200], p[1300];
    snprintf(d, sizeof d, "%s/card%d/" SAVE_DIR_PREFIX "00", root, card);
    mkdirs(d);
    snprintf(p, sizeof p, "%s/icon.sys", d);
    if (write_all(p, files[0], sizes[0])) return -1;
    snprintf(p, sizeof p, "%s/RG.ICO", d);
    if (write_all(p, files[1], sizes[1])) return -1;
    snprintf(p, sizeof p, "%s/" SAVE_DIR_PREFIX "00", d);
    if (write_all(p, files[2], sizes[2])) return -1;
    /* the card's metadata (docs/SAVES.md), identical on both machines: the virtual card clock's
     * epoch 2006-01-31 12:00:00 for every time */
    snprintf(p, sizeof p, "%s/card%d.card", root, card);
    static const char meta[] =
        "RGMC 1\nformatted 1\nseq 5\n"
        "E 0 d 8427 0000000C1F01D607 0000000C1F01D607 /\n"
        "E 1 d 8427 0000000C1F01D607 0000000C1F01D607 /" SAVE_DIR_PREFIX "00\n"
        "E 2 f 8497 0000000C1F01D607 0000000C1F01D607 /" SAVE_DIR_PREFIX "00/icon.sys\n"
        "E 3 f 8497 0000000C1F01D607 0000000C1F01D607 /" SAVE_DIR_PREFIX "00/RG.ICO\n"
        "E 4 f 8497 0000000C1F01D607 0000000C1F01D607 /" SAVE_DIR_PREFIX "00/" SAVE_DIR_PREFIX "00\n";
    return write_all(p, meta, sizeof meta - 1);
}

/* ---------------------------------------------------------------- settings */
static int lockable(const char *id)
{
    return !strncmp(id, "gameplay.", 9) || !strncmp(id, "accessibility.", 14);
}

static size_t settings_text(rg_settings *s, char *out, size_t cap)
{
    size_t n = 0;
    out[0] = 0;
    for (int i = 0; s && i < rg_settings_count(s); i++) {
        const rg_setting_def *d = rg_settings_def(s, i);
        if (!d || !lockable(d->id)) continue;
        char v[128];
        rg_settings_value_text(s, i, v, sizeof v);
        int w = snprintf(out + n, cap - n, "%s=%s\n", d->id, v);
        if (w < 0 || (size_t)w >= cap - n) break;
        n += (size_t)w;
    }
    return n;
}

/* apply the host's "id=value" lines (only lockable ids, bounded, printable) */
static int apply_settings(rg_settings *s, const uint8_t *body, size_t len, char *err, size_t cap)
{
    char txt[8193];
    if (len >= sizeof txt) return -1;
    memcpy(txt, body, len);
    txt[len] = 0;
    for (size_t i = 0; i < len; i++)
        if ((txt[i] < 0x20 || txt[i] > 0x7E) && txt[i] != '\n') {
            snprintf(err, cap, "bad settings from the host");
            return -1;
        }
    for (char *l = strtok(txt, "\n"); l; l = strtok(NULL, "\n")) {
        char *eq = strchr(l, '=');
        if (!eq) continue;
        *eq = 0;
        if (!strcmp(l, "net.delay")) {
            int d = atoi(eq + 1);
            if (d >= 1 && d <= 60) N.delay = d;
            continue;
        }
        if (!strcmp(l, "net.handover")) {
            long h = atol(eq + 1);
            if (h > 0 && h < 1000000) N.handover = (uint32_t)h;
            continue;
        }
        if (!lockable(l) || rg_settings_find(s, l) < 0) continue;   /* unknown here: the hash check decides */
        *eq = '=';
        rg_settings_override(s, l);
    }
    return 0;
}

/* ------------------------------------------------------------- the transport */
static int send_msg(uint16_t t, const void *b, uint32_t n)
{
    if (!N.sock || rg_net_send_msg(N.sock, t, b, n)) return -1;
    return 0;
}

/* wait for one message of type `want` (others are protocol errors before the session runs) */
static int recv_msg(uint16_t want, rg_net_msg *m, int timeout_ms, char *err, size_t cap)
{
    uint64_t t0 = rg_net_now_ms();
    for (;;) {
        int r = rg_net_peek_msg(N.sock, m, err, cap);
        if (r < 0) return -1;
        if (r == 1) {
            if (m->type == RG_MSG_BYE) {
                snprintf(err, cap, "the other player cancelled (%u)", m->len >= 4 ? get32(m->body) : 0u);
                return -1;
            }
            if (m->type == RG_MSG_PING) {
                rg_net_msg_done(N.sock, m);
                continue;
            }
            if (m->type != want) {
                snprintf(err, cap, "unexpected message %u", m->type);
                return -1;
            }
            return 0;
        }
        if ((int)(rg_net_now_ms() - t0) > timeout_ms) {
            snprintf(err, cap, "the other player did not answer");
            return -1;
        }
        if (rg_net_sock_pump(N.sock, 20, err, cap)) return -1;
    }
}

static void bye(uint32_t why)
{
    uint8_t b[4];
    put32(b, why);
    if (N.sock) {
        send_msg(RG_MSG_BYE, b, 4);
        for (int i = 0; i < 20 && rg_net_sock_tx_pending(N.sock); i++) rg_net_sock_pump(N.sock, 10, NULL, 0);
    }
}

static uint64_t g_data_id;
static uint64_t data_fingerprint(const char *data_dir);
uint64_t rg_insnet_build_id(void) { return RG_INSNET_BUILD; }
uint64_t rg_insnet_data_id(void)
{
    if (!g_data_id) {
        const rg_runtime_config *c = rg_runtime_get_config();
        g_data_id = data_fingerprint(c && c->data_dir ? c->data_dir : getenv("RG_DATA"));
    }
    return g_data_id;
}

static uint64_t data_fingerprint(const char *data_dir)
{
    /* the extraction's own manifest (data/MANIFEST.tsv: every file of the disc with its hash,
     * docs/EXTRACT.md), line ends normalised; without one, the top level's names + sizes */
    {
        char mp[1200];
        size_t mn = 0;
        snprintf(mp, sizeof mp, "%s/MANIFEST.tsv", data_dir ? data_dir : "data");
        uint8_t *m = read_all(mp, &mn, 4u * 1024u * 1024u);
        if (m) {
            uint64_t hm = rg_net_fnv64(0, "manifest", 8);
            for (size_t i = 0; i < mn; i++)
                if (m[i] != '\r') hm = rg_net_fnv64(hm, m + i, 1);
            free(m);
            return hm;
        }
    }
    uint64_t h = rg_net_fnv64(0, "data", 4);
    static char names[512][64];
    int n = list_dir(data_dir ? data_dir : "data", names, 512);
    qsort(names, (size_t)n, 64, (int (*)(const void *, const void *))strcmp);
    for (int i = 0; i < n; i++) {
        char p[1200];
        struct stat st;
        snprintf(p, sizeof p, "%s/%s", data_dir ? data_dir : "data", names[i]);
        uint64_t sz = !stat(p, &st) && !(st.st_mode & S_IFDIR) ? (uint64_t)st.st_size : 0;
        h = rg_net_fnv64(h, names[i], strlen(names[i]));
        h = rg_net_fnv64(h, &sz, sizeof sz);
    }
    return h;
}

/* --------------------------------------------------------------- the session */
int rg_insnet_start(rg_runtime_config *cfg, rg_settings *settings, char *err, size_t cap)
{
    memset(&N, 0, sizeof N);
    N.settings = settings;
    N.role = O.role >= 0 ? O.role : O.join[0] ? 1 : 0;
    N.delay = O.delay;
    N.exit_at_end = O.exit_at_end;
    N.timeout_ms = O.timeout_s * 1000;
    N.handover_timeout_ms = 180 * 1000;
    N.realtime = getenv("RG_INSNET_REALTIME") && getenv("RG_INSNET_REALTIME")[0] == '1';
    N.handover = O.handover > 0 ? (uint32_t)O.handover : K_PREFIX_HANDOVER;
    if (!O.log[0] && getenv("RG_INSNET_LOG")) /* (tests: a session started from the menus has no --net-log) */
        snprintf(O.log, sizeof O.log, "%s", getenv("RG_INSNET_LOG"));
    if (O.log[0]) N.log = fopen(O.log, "w");
    const char *saves = cfg->saves_dir ? cfg->saves_dir : getenv("RG_SAVES");
    if (!saves || !*saves) saves = "saves";

    /* 1. our save (read first: no point in connecting without one) */
    char folder[1100];
    save_pkg mine = {0, 0};
    if (save_folder(saves, O.save, folder, sizeof folder) || pack_save(folder, &mine, err, cap)) {
        if (!err[0]) snprintf(err, cap, "no save to bring (use --net-save CARD:NN)");
        return -1;
    }
    nlog("role %s, save %s, delay %d", O.solo ? "solo" : N.role ? "join" : "host", folder, N.delay);
    if (O.solo) {
        /* --net-solo (tools/net/netmatch.py): the session without a peer.  Same session saves and
         * prefix; from the hand-over on both ports read the local script (one driver plays both
         * players), no delay */
        char f2[1100];
        save_pkg two = {0, 0};
        const uint8_t *f1p[3], *f2p[3];
        uint32_t s1[3], s2[3];
        if (save_folder(saves, O.save2[0] ? O.save2 : "2:0", f2, sizeof f2) || pack_save(f2, &two, err, cap) ||
            unpack_save(mine.data, mine.n, f1p, s1, err, cap) || unpack_save(two.data, two.n, f2p, s2, err, cap)) {
            free(mine.data);
            free(two.data);
            return -1;
        }
        snprintf(N.session_saves, sizeof N.session_saves, "%s/netplay/session", saves);
        /* a driver's later segment (save state) keeps the session saves the game wrote */
        char keep[1200];
        struct stat kst;
        snprintf(keep, sizeof keep, "%s/card1.card", N.session_saves);
        int bad = 0;
        if (stat(keep, &kst) != 0) {
            rm_tree(N.session_saves, 0);
            mkdirs(N.session_saves);
            bad = write_card(N.session_saves, 1, f1p, s1) || write_card(N.session_saves, 2, f2p, s2);
        }
        free(mine.data);
        free(two.data);
        if (bad) {
            snprintf(err, cap, "cannot write the session saves in %s", N.session_saves);
            return -1;
        }
        cfg->saves_dir = N.session_saves;
        cfg->input_script = NULL;
        char e3[256];
        if ((O.prefix[0] ? rg_input_script_load(&N.prefix, O.prefix, e3, sizeof e3)
                         : rg_input_script_parse(&N.prefix, k_prefix, "built-in prefix", e3, sizeof e3)) ||
            (O.input[0] && load_local_script(O.input, e3, sizeof e3))) {
            snprintf(err, cap, "%s", e3);
            return -1;
        }
        N.on = 1;
        N.phase = 1;
        N.solo = 1;
        rg_runtime_set_pad_hook(rg_insnet_pad, NULL);
        return 0;
    }

    /* 2. connect */
    char e2[256] = "";
    if (O.handle) {
        N.sock = rg_net_sock_adopt(O.handle);
        if (N.sock && O.hofile[0]) {
            size_t hn = 0;
            uint8_t *hb = read_all(O.hofile, &hn, 256u * 1024u);
            if (hb && hn) rg_net_sock_inject(N.sock, hb, hn);
            if (hb) nlog("handed over %u byte(s) already received", (unsigned)hn);
            free(hb);
            remove(O.hofile);
        }
        if (!N.sock) {
            snprintf(err, cap, "the connection was not handed over");
            free(mine.data);
            return -1;
        }
    } else if (N.role == 1) {
        char host[256];
        int port = 0;
        if (rg_net_parse_address(O.join, host, sizeof host, &port)) {
            snprintf(err, cap, "bad address %s", O.join);
            free(mine.data);
            return -1;
        }
        nlog("connecting to %s port %d", host, port);
        uint64_t t0 = rg_net_now_ms();
        while (!N.sock && rg_net_now_ms() - t0 < (uint64_t)N.timeout_ms * 2) {
            N.sock = rg_net_sock_connect(host, port, 3000, e2, sizeof e2);
            if (!N.sock) rg_net_sleep_ms(250);   /* the host may still be starting */
        }
    } else {
        rg_net_sock *l = rg_net_sock_listen(O.host_port, e2, sizeof e2);
        if (l) {
            char addr[8][48];
            int na = rg_net_local_addresses(addr, 8);
            for (int i = 0; i < na; i++) nlog("waiting on %s:%d", addr[i], O.host_port);
            if (!na) nlog("waiting on port %d", O.host_port);
            uint64_t t0 = rg_net_now_ms();
            int wait_ms = O.timeout_s >= 60 ? O.timeout_s * 1000 : 600 * 1000;
            while (!N.sock && rg_net_now_ms() - t0 < (uint64_t)wait_ms) N.sock = rg_net_sock_accept(l, 200, e2, sizeof e2);
            rg_net_sock_close(l);   /* one opponent: stop listening at once */
        }
    }
    if (!N.sock) {
        snprintf(err, cap, "%s", e2[0] ? e2 : "no connection");
        free(mine.data);
        return -1;
    }
    nlog("connected");

    /* 3. HELLO both ways */
    rg_net_hello h;
    memset(&h, 0, sizeof h);
    memcpy(h.magic, "RGINSNET", 8);
    h.protocol = RG_NET_PROTOCOL;
    h.role = (uint32_t)N.role;
    h.build = RG_INSNET_BUILD;
    h.data = data_fingerprint(cfg->data_dir ? cfg->data_dir : getenv("RG_DATA"));
    g_data_id = h.data;
    snprintf(h.name, sizeof h.name, "%s", O.name[0] ? O.name : (N.role ? "2P" : "1P"));
    uint8_t hb[RG_NET_HELLO_BYTES];
    rg_net_hello_pack(&h, hb);
    rg_net_msg m;
    rg_net_hello ph;
    if (send_msg(RG_MSG_HELLO, hb, sizeof hb) || recv_msg(RG_MSG_HELLO, &m, N.timeout_ms, err, cap) ||
        rg_net_hello_unpack(m.body, &ph, err, cap))
        goto fail;
    rg_net_msg_done(N.sock, &m);
    if (ph.protocol != RG_NET_PROTOCOL || ph.role == (uint32_t)N.role) {
        snprintf(err, cap, "the other player runs another version (protocol %u)", ph.protocol);
        bye(RG_BYE_MISMATCH);
        goto fail;
    }
    if (ph.build != h.build) {
        snprintf(err, cap, "the other player's game build differs (%016llx vs %016llx)", (unsigned long long)ph.build,
                 (unsigned long long)h.build);
        bye(RG_BYE_MISMATCH);
        goto fail;
    }
    if (ph.data != h.data) {
        snprintf(err, cap, "the other player's game data differs (%016llx vs %016llx)", (unsigned long long)ph.data,
                 (unsigned long long)h.data);
        bye(RG_BYE_MISMATCH);
        goto fail;
    }
    nlog("peer \"%s\" ok", ph.name);

    /* 4. settings: the host's win (joiner applies them) */
    char st[8192];
    size_t sn = 0;
    if (N.role == 0) {
        sn = settings_text(settings, st, sizeof st - 64);
        sn += (size_t)snprintf(st + sn, sizeof st - sn, "net.delay=%d\nnet.handover=%u\n", N.delay, N.handover);
        if (send_msg(RG_MSG_SETTINGS, st, (uint32_t)sn)) goto fail;
    } else {
        if (recv_msg(RG_MSG_SETTINGS, &m, N.timeout_ms, err, cap) || apply_settings(settings, m.body, m.len, err, cap))
            goto fail;
        rg_net_msg_done(N.sock, &m);
        sn = settings_text(settings, st, sizeof st - 64);
        sn += (size_t)snprintf(st + sn, sizeof st - sn, "net.delay=%d\nnet.handover=%u\n", N.delay, N.handover);
    }
    snprintf(N.locked, sizeof N.locked, "%.*s", (int)(sn < sizeof N.locked ? sn : sizeof N.locked - 1), st);

    /* 5. saves both ways */
    if (send_msg(RG_MSG_SAVE, mine.data, (uint32_t)mine.n) || recv_msg(RG_MSG_SAVE, &m, N.timeout_ms * 4, err, cap))
        goto fail;
    const uint8_t *pf[3], *mf[3];
    uint32_t psz[3], msz[3];
    if (unpack_save(m.body, m.len, pf, psz, err, cap) || unpack_save(mine.data, mine.n, mf, msz, err, cap)) {
        bye(RG_BYE_MISMATCH);
        goto fail;
    }
    /* session saves: <saves>/netplay/session (card1 = host, card2 = joiner) */
    snprintf(N.session_saves, sizeof N.session_saves, "%s/netplay/session", saves);
    rm_tree(N.session_saves, 0);
    mkdirs(N.session_saves);
    {
        const uint8_t **c1 = N.role == 0 ? mf : pf, **c2 = N.role == 0 ? pf : mf;
        const uint32_t *s1 = N.role == 0 ? msz : psz, *s2 = N.role == 0 ? psz : msz;
        if (write_card(N.session_saves, 1, c1, s1) || write_card(N.session_saves, 2, c2, s2)) {
            snprintf(err, cap, "cannot write the session saves in %s", N.session_saves);
            goto fail;
        }
        /* 6. READY: both computed the same session */
        uint64_t sh = rg_net_fnv64(0, c1[2], s1[2]);
        sh = rg_net_fnv64(sh, c2[2], s2[2]);
        sh = rg_net_fnv64(sh, N.locked, strlen(N.locked));
        rg_net_msg_done(N.sock, &m);
        uint8_t rb[8];
        put32(rb, (uint32_t)sh);
        put32(rb + 4, (uint32_t)(sh >> 32));
        if (send_msg(RG_MSG_READY, rb, 8) || recv_msg(RG_MSG_READY, &m, N.timeout_ms, err, cap)) goto fail;
        if (memcmp(m.body, rb, 8)) {
            snprintf(err, cap, "the two sessions differ (saves or settings)");
            bye(RG_BYE_MISMATCH);
            goto fail;
        }
        rg_net_msg_done(N.sock, &m);
        nlog("session %016llx ready", (unsigned long long)sh);
        /* flush what is queued (our READY): the peer waits for it while we boot */
        for (int i = 0; i < 500 && rg_net_sock_tx_pending(N.sock); i++)
            if (rg_net_sock_pump(N.sock, 10, err, cap)) break;
    }
    free(mine.data);
    mine.data = NULL;
    cfg->saves_dir = N.session_saves;
    cfg->input_script = NULL;

    /* 7. the prefix, the local script, the streams */
    {
        char e3[256];
        int pr;
        if (O.prefix[0]) pr = rg_input_script_load(&N.prefix, O.prefix, e3, sizeof e3);
        else pr = rg_input_script_parse(&N.prefix, k_prefix, "built-in prefix", e3, sizeof e3);
        if (pr) {
            snprintf(err, cap, "prefix: %s", e3);
            goto fail;
        }
        if (O.input[0] && load_local_script(O.input, e3, sizeof e3)) {
            snprintf(err, cap, "%s", e3);
            goto fail;
        }
    }
    N.mine = (rg_net_stream *)malloc(sizeof *N.mine);
    N.peer = (rg_net_stream *)malloc(sizeof *N.peer);
    if (!N.mine || !N.peer) goto fail;
    rg_net_stream_init(N.mine, N.handover);
    rg_net_stream_init(N.peer, N.handover);
    N.last_pub = -1;
    N.last_rx_ms = rg_net_now_ms();
    N.on = 1;
    N.phase = 1;
    rg_runtime_set_pad_hook(rg_insnet_pad, NULL);
    return 0;
fail:
    free(mine.data);
    nlog("failed: %s", err);
    rg_net_sock_close(N.sock);
    N.sock = NULL;
    return -1;
}

static void end_session(const char *why, int code)
{
    if (N.phase == 3) return;
    snprintf(N.why, sizeof N.why, "%s", why);
    nlog("session ended at field %llu: %s (%u hash checks, %llu waits, longest %llu ms)",
         (unsigned long long)rg_runtime_get_stats()->fields, why, N.checks, (unsigned long long)N.waits,
         (unsigned long long)N.wait_ms_max);
    if (code) bye((uint32_t)code);
    N.phase = 3;
    N.lost = 1;
}

static void check_hashes(void)
{
    for (int i = 0; i < HASH_RING; i++) {
        if (!N.peer_hash_f[i]) continue;
        uint32_t f = N.peer_hash_f[i];
        int j = (int)((f / HASH_EVERY) % HASH_RING);
        if (N.my_hash_f[j] != f) continue;
        N.peer_hash_f[i] = 0;
        N.checks++;
        N.last_check_field = f;
        if (N.my_hash[j] != N.peer_hash[i]) {
            char b[200];
            snprintf(b, sizeof b, "desync at field %u (mine %016llx, theirs %016llx)", f,
                     (unsigned long long)N.my_hash[j], (unsigned long long)N.peer_hash[i]);
            end_session(b, RG_BYE_DESYNC);
            return;
        }
    }
}

/* drain received messages; 0 ok, -1 the session ended */
static int process(void)
{
    char err[200] = "";
    if (!N.sock || N.phase == 3) return -1;
    if (rg_net_sock_pump(N.sock, 0, err, sizeof err)) {
        end_session(err[0] ? err : "connection lost", 0);
        return -1;
    }
    rg_net_msg m;
    int r;
    while ((r = rg_net_peek_msg(N.sock, &m, err, sizeof err)) == 1) {
        N.last_rx_ms = rg_net_now_ms();
        if (m.type == RG_MSG_INPUT) {
            rg_net_input in;
            rg_net_pad p;
            if (rg_net_input_unpack(m.body, &in, err, sizeof err)) break;
            p.buttons = in.buttons;
            p.lx = in.lx;
            p.ly = in.ly;
            p.rx = in.rx;
            p.ry = in.ry;
            if (rg_net_stream_add(N.peer, in.first, in.last, &p, err, sizeof err)) {
                r = -1;
                break;
            }
        } else if (m.type == RG_MSG_HASH) {
            rg_net_hashmsg hm;
            rg_net_hash_unpack(m.body, &hm);
            if (hm.field % HASH_EVERY == 0 && hm.field) {
                int i = (int)((hm.field / HASH_EVERY) % HASH_RING);
                N.peer_hash_f[i] = hm.field;
                N.peer_hash[i] = hm.hash;
            }
        } else if (m.type == RG_MSG_BYE) {
            uint32_t why = get32(m.body);
            rg_net_msg_done(N.sock, &m);
            end_session(why == RG_BYE_DESYNC ? "the other player saw a desync"
                        : why == RG_BYE_DONE ? "the other player ended the session"
                                             : "the other player left",
                        0);
            return -1;
        } else if (m.type != RG_MSG_PING) {
            snprintf(err, sizeof err, "unexpected message %u during the battle", m.type);
            r = -1;
            rg_net_msg_done(N.sock, &m);
            break;
        }
        rg_net_msg_done(N.sock, &m);
    }
    if (r < 0) {
        end_session(err, RG_BYE_ERROR);
        return -1;
    }
    check_hashes();
    return N.phase == 3 ? -1 : 0;
}

static void local_pad(uint32_t vbl, rg_net_pad *out)
{
    out->lx = out->ly = out->rx = out->ry = 0x80;
    out->buttons = 0;
    if (N.have_loc) {
        out->buttons = local_script_word(vbl);
        return;
    }
    rg_host *h = rg_runtime_host();
    if (!h) return;
    rg_pad p;
    rg_host_read_pad(h, 0, vbl, &p);
    out->buttons = p.buttons;
    out->lx = p.lx;
    out->ly = p.ly;
    out->rx = p.rx;
    out->ry = p.ry;
}

static void publish(uint32_t vbl)
{
    if ((int64_t)vbl <= N.last_pub) return;
    N.last_pub = vbl;
    int64_t want = (int64_t)vbl + N.delay;
    if (want <= N.mine->horizon) return;
    rg_net_pad p;
    local_pad(vbl, &p);
    while (N.mine->horizon < want) {
        int64_t a = N.mine->horizon + 1, b = want;
        if (b - a >= RG_NET_MAX_SPAN) b = a + RG_NET_MAX_SPAN - 1;
        rg_net_stream_add(N.mine, (uint32_t)a, (uint32_t)b, &p, NULL, 0);
        rg_net_input in = {(uint32_t)a, (uint32_t)b, p.buttons, p.lx, p.ly, p.rx, p.ry};
        uint8_t ib[RG_NET_INPUT_BYTES];
        rg_net_input_pack(&in, ib);
        if (send_msg(RG_MSG_INPUT, ib, sizeof ib)) {
            end_session("cannot send", 0);
            return;
        }
    }
}

void rg_insnet_pad(void *user, int port, uint32_t vbl, uint16_t *buttons, uint8_t sticks[4], int *connected)
{
    (void)user;
    *connected = 1;   /* both ports, the whole session */
    *buttons = 0;
    sticks[0] = sticks[1] = sticks[2] = sticks[3] = 0x80;
    if (!N.on) return;
    if (N.phase == 1 && vbl < N.handover) {
        if (port == 0) *buttons = rg_input_script_word(&N.prefix, vbl);
        return;
    }
    if (N.phase == 1) {
        N.phase = 2;
        nlog("live from VBlank %u (field %llu)", vbl, (unsigned long long)rg_runtime_get_stats()->fields);
        /* the prefix must have loaded player 2 last, from MEMORY CARD slot 2 (both machines see
         * the same, so both stop the same way when it did not) */
        int lp = -1;
        unsigned seq = mccard_last_loaded(&lp, NULL, 0);
        if (seq && (seq < 2 || lp != 1)) {   /* (seq 0: a save state was loaded past the prefix) */
            char b[160];
            snprintf(b, sizeof b, "the session could not be set up (loads %u, last from slot %d)", seq, lp + 1);
            end_session(b, 0);
        }
    }
    if (N.phase == 3) {
        /* the session ended (connection lost, desync): the match goes on at this end with this
         * player holding both controllers; leaving the 2-Player menu ends the session process */
        if (vbl >= N.handover) {
            rg_net_pad lp;
            local_pad(vbl, &lp);
            *buttons = lp.buttons;
            sticks[0] = lp.lx;
            sticks[1] = lp.ly;
            sticks[2] = lp.rx;
            sticks[3] = lp.ry;
        }
        return;
    }
    if (N.phase != 2) return;
    if (N.solo) {
        *buttons = local_script_word(vbl);
        return;
    }
    publish(vbl);
    int mine_port = N.role;   /* host = port 0, joiner = port 1 */
    rg_net_stream *s = port == mine_port ? N.mine : N.peer;
    rg_net_pad p;
    int r = rg_net_stream_get(s, vbl, &p);
    if (r == 0) {
        /* lock-step wait for the other player's pad */
        uint64_t t0 = rg_net_now_ms();
        int limit = vbl < N.handover + 120 ? N.handover_timeout_ms : N.timeout_ms;
        rg_host *h = rg_runtime_host();
        while ((r = rg_net_stream_get(s, vbl, &p)) == 0) {
            if (process()) return;
            char err[200] = "";
            if (rg_net_sock_pump(N.sock, 5, err, sizeof err)) {
                end_session(err, 0);
                return;
            }
            if (h) rg_host_keepalive(h);
            if ((int)(rg_net_now_ms() - t0) > limit) {
                end_session("the other player stopped answering", RG_BYE_ERROR);
                return;
            }
        }
        uint64_t w = rg_net_now_ms() - t0;
        if (vbl >= N.handover + 120)   /* (the hand-over wait is the slower machine finishing the prefix) */
            N.stall_hist[w < 2 ? 0 : w < 17 ? 1 : w < 50 ? 2 : w < 200 ? 3 : 4]++;
        N.waits++;
        N.wait_ms_total += w;
        if (w > N.wait_ms_max) N.wait_ms_max = w;
    }
    if (r < 0) {
        end_session("input fell out of the window", RG_BYE_ERROR);
        return;
    }
    *buttons = p.buttons;
    sticks[0] = p.lx;
    sticks[1] = p.ly;
    sticks[2] = p.rx;
    sticks[3] = p.ry;
}

void rg_insnet_before_field(uint64_t k)
{
    (void)k;
    if (!N.on) return;
    /* the prefix runs as fast as the machine allows (each phase unchanged: the speed-up of
     * gameplay.battle_speed, docs/NATIVE-THREADS.md); live play at 1x */
    rg_runtime_set_speed(N.phase == 1 ? 64.0 : 1.0, 0);
    if (N.phase == 2 && N.realtime) {
        /* $RG_INSNET_REALTIME=1 (tests): a headless run is not paced, so pace the live part to
         * the NTSC field rate here, as a windowed game would be: the stall numbers then are
         * what players see */
        if (!N.rt_t0) {
            N.rt_t0 = rg_net_now_ms();
            N.rt_k0 = k;
        }
        uint64_t due = N.rt_t0 + (k - N.rt_k0) * 1001u / 60u;
        uint64_t now = rg_net_now_ms();
        if (due > now) rg_net_sleep_ms((int)(due - now));
    }
    /* settings lock: the session values win over a live change */
    if (N.phase == 2 && N.settings && N.locked[0]) {
        char now[2048];
        settings_text(N.settings, now, sizeof now);
        if (strncmp(now, N.locked, strlen(now))) {
            char tmp[2048];
            snprintf(tmp, sizeof tmp, "%s", N.locked);
            for (char *l = strtok(tmp, "\n"); l; l = strtok(NULL, "\n"))
                if (strncmp(l, "net.", 4)) rg_settings_override(N.settings, l);
            nlog("a game setting was changed during the session: kept the session's value");
        }
    }
}

/* after field k (1-based count of fields run): hashes, end of session.  Returns 1 when the
 * process should stop (--net-exit-at-end), else 0. */
int rg_insnet_after_field(uint64_t k)
{
    if (!N.on) return 0;
    {
        /* the session is over when the game leaves the battle (INSECT, overlay 5) for INSMENU
         * (overlay 6) after the match and its rematches: the players said no to a rematch.
         * 600 fields later, so the stadium's "How was the match?" shows first. */
        extern uint32_t D_0047E254[];
        static int was_battle;
        static uint64_t left_at;
        int ovl = (int)D_0047E254[0];
        if (ovl == 5) {
            was_battle = 1;
            left_at = 0;
        } else if (was_battle && ovl == 6 && !N.left) {
            if (!left_at) {
                left_at = k;
                nlog("the battle is over (field %llu)", (unsigned long long)k);
            }
            if (k - left_at >= 600 && !N.solo) rg_insnet_session_left();
        }
    }
    if (N.phase == 1 && N.sock && !N.solo) {
        /* the prefix: keep the connection moving (sends; received bytes wait in the buffer) */
        char perr[200];
        if (rg_net_sock_pump(N.sock, 0, perr, sizeof perr)) end_session(perr, 0);
    }
    if (N.phase == 2) {
        process();
        if (k % HASH_EVERY == 0 && N.phase == 2) {
            uint64_t h = rg_runtime_run_hash();
            int i = (int)((k / HASH_EVERY) % HASH_RING);
            N.my_hash_f[i] = (uint32_t)k;
            N.my_hash[i] = h;
            rg_net_hashmsg hm = {(uint32_t)k, h};
            uint8_t b[RG_NET_HASH_BYTES];
            rg_net_hash_pack(&hm, b);
            send_msg(RG_MSG_HASH, b, sizeof b);
            if (N.log) fprintf(N.log, "hash %llu %016llx\n", (unsigned long long)k, (unsigned long long)h);
            check_hashes();
        }
        if (N.sock) {
            char err[200];
            if (rg_net_sock_pump(N.sock, 0, err, sizeof err)) end_session(err, 0);
        }
    }
    if (N.phase == 3 && N.exit_at_end && (N.left || !N.relaunch_pending)) return 1;
    if (N.left && O.relaunch) {
        rg_insnet_finish();
        rg_insnet_spawn_self(g_argc_s, g_argv_s, NULL, 0);   /* the normal game again */
    }
    return 0;
}

int rg_insnet_finish(void)
{
    if (!N.on) return 0;
    int desync = strstr(N.why, "desync") != NULL;
    if (N.phase != 3) {
        /* the run stopped (--fields, window closed) while the session was live */
        if (N.sock) process();   /* last hashes */
        nlog("finished at field %llu, %u hash checks (last at field %u)%s",
             (unsigned long long)rg_runtime_get_stats()->fields, N.checks, N.last_check_field,
             desync ? ", DESYNC" : "");
        bye(RG_BYE_QUIT);
    }
    if (N.log) {
        fprintf(N.log, "checks %u last %u waits %llu wait_ms %llu max %llu why %s\n", N.checks, N.last_check_field,
                (unsigned long long)N.waits, (unsigned long long)N.wait_ms_total, (unsigned long long)N.wait_ms_max,
                N.why[0] ? N.why : "-");
        fprintf(N.log, "stalls <2ms %llu, 2-16ms %llu, 17-49ms %llu, 50-199ms %llu, >=200ms %llu (pad reads that waited for the peer)\n",
                (unsigned long long)N.stall_hist[0], (unsigned long long)N.stall_hist[1], (unsigned long long)N.stall_hist[2],
                (unsigned long long)N.stall_hist[3], (unsigned long long)N.stall_hist[4]);
        fclose(N.log);
        N.log = NULL;
    }
    rg_net_sock_close(N.sock);
    N.sock = NULL;
    rg_runtime_set_pad_hook(NULL, NULL);
    return desync ? 6 : 0;
}

const char *rg_insnet_end_reason(void) { return N.why; }

/* (session) the INSMENU 2-Player menu should say the connection was lost: 1 once */
int rg_insnet_lost_notice(void)
{
    static int shown;
    if (!N.on || N.phase != 3 || shown || N.solo) return 0;
    shown = 1;
    return 1;
}

int rg_insnet_session(void) { return N.on && !N.solo; }

/* (session) the players left the 2-Player Battle (back to the mode list): the session is over.
 * Started from the menus: this process restarts as the normal game; tests stop. */
void rg_insnet_session_left(void)
{
    if (!N.on || N.solo) return;
    if (N.phase != 3) end_session("the players left the 2-Player Battle", RG_BYE_DONE);
    N.left = 1;
}
