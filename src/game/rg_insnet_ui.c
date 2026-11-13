/* SPDX-License-Identifier: CC0-1.0 */
/* Online Insectron 2-Player Battle: the player's way in, inside the game's own INSMENU screens
 * (lane insnet 2026-11-12; USER: online interfaces use the game's existing assets and
 * characters; docs/INSECTRON-VERSUS.md "Online 2-Player Battle").
 *
 * 2-Player Battle -> Controller setting: Left / Right on a player's row also offers
 * "Online rival" (the game's own row, text and controller icon).  Player 2 online = this game
 * HOSTS (the rival joins as Player 2); Player 1 online = this game JOINS (the rival hosts as
 * Player 1).  Each player loads their own data with the game's load screens.  "Begin battle"
 * then runs the flow below through the stadium's own confirm dialog (yes / no, the menu's
 * frame and font) and, for the joiner, the game's own text entry for the address:
 *
 *   host:  "Waiting for your rival..." (address shown) -> rival arrives -> "Start?" -> go
 *   join:  address entry -> "Calling your rival..." -> "Start?" -> go
 *   go:    both answered yes -> this process relaunches itself as the session (rg_insnet.c),
 *          handing the connection over (inherited socket), with the save it loaded
 *
 * The overrides (overrides/src/overlays/insmenu/...) call the functions below; nothing here
 * opens a socket until "Begin battle" with an online rival. */
#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <winsock2.h>
#include <windows.h>
#else
#include <sys/stat.h>
#include <unistd.h>
#endif
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "host.h"
#include "mccard.h"
#include "rg_insnet.h"
#include "rg_net.h"
#include "rg_runtime.h"

/* dialog ids (the confirm dialog's message ids; the game's own are < 0x100) */
enum {
    D_NONE = 0,
    D_FIRST = 0x7000,
    D_HOST_WAIT = 0x7001,     /* waiting, address shown; yes = stop */
    D_JOIN_CALL = 0x7002,     /* calling; yes = stop */
    D_FOUND = 0x7003,         /* rival here; yes = start */
    D_WAIT_GO = 0x7004,       /* waiting for the rival's yes; yes = stop */
    D_FAIL = 0x7005,          /* something failed (text in g_fail); yes = try again */
    D_NEED_DATA = 0x7006,     /* load your data first; any = back */
    D_LOST = 0x7007,          /* (session) connection lost; any = on */
    D_ROLE = 0x7008,          /* host (yes) or join (no) */
    D_ROW_TEXT = 0x7010,      /* controller row text "Online rival" */
    D_ENTRY_TITLE = 0x7011,   /* address entry title */
    D_LAST
};

enum { S_IDLE, S_ROLE, S_HOST_WAIT, S_JOIN_ENTRY, S_JOIN_CALL, S_HELLO, S_LOAD, S_FOUND, S_WAIT_GO, S_FAIL, S_NEED_DATA, S_GO };

static struct {
    int ctx;                    /* where the flow's screens open: 0 the mode list, 1 the 2-Player menu */
    int go2p_pending;           /* the mode list should enter the 2-Player menu (load your data) */
    int role;                   /* 0 host (Player 1 in the battle), 1 join (Player 2) */
    int state;
    int dialog_open;            /* our dialog is up (id) */
    int want_dialog;            /* next dialog to open (the 2-Player menu step opens it) */
    int want_entry;             /* open the address entry */
    int entry_pending;          /* the address entry is up */
    rg_net_sock *listener, *sock;
    rg_net_connecting *conn;
    int port;
    char addr[64];              /* the joiner's address text */
    char text[600];             /* the dialog text being shown */
    char fail[200];
    char peer[16];
    int sent_go, got_go;
    int calls;                  /* connection attempts that failed (the joiner keeps calling) */
    uint64_t t0;
    int loaded_port;            /* the save the player loaded (mccard_last_loaded) */
    char loaded_path[256];
    unsigned loaded_seq_at_begin;
} U;

static int g_argc;
static char **g_argv;

void rg_insnet_ui_set_argv(int argc, char **argv)
{
    g_argc = argc;
    g_argv = argv;
}

/* ------------------------------------------------------------- the strings */
static const char *saves_dir(void)
{
    const rg_runtime_config *c = rg_runtime_get_config();
    const char *s = c && c->saves_dir ? c->saves_dir : getenv("RG_SAVES");
    return s && *s ? s : "saves";
}

static void last_address(char *out, size_t cap, int write)
{
    char p[1100];
    snprintf(p, sizeof p, "%s/netplay/last-address.txt", saves_dir());
    if (write) {
        char d[1100];
        snprintf(d, sizeof d, "%s/netplay", saves_dir());
#ifdef _WIN32
        CreateDirectoryA(d, NULL);
#else
        mkdir(d, 0755);
#endif
        FILE *f = fopen(p, "w");
        if (f) {
            fprintf(f, "%s\n", out);
            fclose(f);
        }
        return;
    }
    out[0] = 0;
    FILE *f = fopen(p, "r");
    if (!f) return;
    if (fgets(out, (int)cap, f)) out[strcspn(out, "\r\n")] = 0;
    fclose(f);
}

/* the text for a dialog / label id; NULL = not ours (the game's own table) */
const char *rg_insnet_ui_text(int id)
{
    switch (id) {
    case D_ROW_TEXT:
        return "Online rival";
    case D_ENTRY_TITLE:
        return "Rival's address";
    /* the stadium's confirm dialog has room for one line (about 44 characters) above Yes / No */
    case D_HOST_WAIT: {
        char ad[4][48];
        int n = rg_net_local_addresses(ad, 4);
        snprintf(U.text, sizeof U.text, "Waiting at %s:%d. Stop waiting?", n ? ad[0] : "this PC", U.port);
        return U.text;
    }
    case D_JOIN_CALL:
        snprintf(U.text, sizeof U.text, "Calling %s... Stop calling?", U.addr);
        return U.text;
    case D_FOUND:
        return "Your rival is here! Start the battle?";
    case D_WAIT_GO:
        return "Waiting for your rival... Stop waiting?";
    case D_FAIL:
        snprintf(U.text, sizeof U.text, "%s Try again?", U.fail);
        return U.text;
    case D_NEED_DATA:
        return "Please load your own data first.";
    case D_LOST:
        return "The connection to your rival was lost.";
    case D_ROLE:
        return "Will you host the battle? (No: join one)";
    }
    return NULL;
}

/* ------------------------------------------------------- controller setting */
/* ------------------------------------------------------------------- flow */
static void fail(const char *why)
{
    fprintf(stderr, "rg-game: online battle (menu): %s (state %d)\n", why, U.state);
    snprintf(U.fail, sizeof U.fail, "%s", why);
    rg_net_sock_close(U.sock);
    U.sock = NULL;
    rg_net_sock_close(U.listener);
    U.listener = NULL;
    rg_net_connect_cancel(U.conn);
    U.conn = NULL;
    U.state = S_FAIL;
    U.want_dialog = D_FAIL;
}

static void stop(void)
{
    if (U.sock) {
        uint8_t b[4] = {RG_BYE_QUIT, 0, 0, 0};
        rg_net_send_msg(U.sock, RG_MSG_BYE, b, 4);
        rg_net_sock_pump(U.sock, 20, NULL, 0);
    }
    rg_net_sock_close(U.sock);
    U.sock = NULL;
    rg_net_sock_close(U.listener);
    U.listener = NULL;
    rg_net_connect_cancel(U.conn);
    U.conn = NULL;
    U.state = S_IDLE;
    U.want_dialog = 0;
    U.want_entry = 0;
}

int rg_insnet_ui_active(void) { return U.state != S_IDLE || U.dialog_open; }

static void start_host(void)
{
    char err[200];
    U.port = rg_insnet_menu_port();
    U.listener = rg_net_sock_listen(U.port, err, sizeof err);
    if (!U.listener) {
        char b[200];
        snprintf(b, sizeof b, "Port %d is busy.", U.port);
        fail(b);
        return;
    }
    U.state = S_HOST_WAIT;
    U.want_dialog = D_HOST_WAIT;
}

/* "Begin battle" with an online rival.  Returns 1 when the flow took over (the game must not
 * begin the local battle). */
int rg_insnet_ui_begin(void)
{
    if (rg_insnet_active() || U.state != S_IDLE) return 0;
    U.sent_go = U.got_go = 0;
    U.peer[0] = 0;
    U.ctx = 0;
    U.go2p_pending = 0;
    U.state = S_ROLE;
    U.want_dialog = D_ROLE;
    return 1;
}

int rg_insnet_ui_ctx(void) { return U.ctx; }

/* the address entry: initial text (the last address) and the result */
const char *rg_insnet_ui_entry_initial(void)
{
    static char a[64];
    last_address(a, sizeof a, 0);
    if (!a[0]) snprintf(a, sizeof a, "192" ".168.1.2:%d", rg_insnet_menu_port());
    return a;
}

int rg_insnet_ui_entry_pending(void) { return U.entry_pending; }
int rg_insnet_ui_dialog_id(void) { return U.dialog_open; }

void rg_insnet_ui_entry_done(const char *text, int ok)
{
    U.want_entry = 0;
    U.entry_pending = 0;
    if (!ok) {
        stop();
        return;
    }
    /* the entry keeps '*' / ' ' for empty cells.  On the letter grid there is no '.' or ':', so
     * digit groups split by empty cells (R1 skips a cell) read as an IPv4 address: 4 groups =
     * a.b.c.d, a 5th = the port ("203 0 113 5 7490").  Typed or pasted text keeps its own dots. */
    char a[64], groups[6][8];
    int n = 0, ng = 0, gl = 0, digits_only = 1;
    for (const char *c = text; *c && n < 63; c++) {
        int sep = *c == '*' || *c == ' ' || *c == '\n' || *c == '.' || *c == ':';
        if (*c != '*' && *c != ' ' && *c != '\n') a[n++] = *c;
        if (sep) {
            if (gl) {
                ng++;
                gl = 0;
            }
            continue;
        }
        if (*c < '0' || *c > '9') digits_only = 0;
        if (ng < 6 && gl < 7) {
            groups[ng][gl++] = *c;
            groups[ng][gl] = 0;
        }
    }
    if (gl) ng++;
    a[n] = 0;
    if (digits_only && (ng == 4 || ng == 5)) {
        if (ng == 4) snprintf(a, sizeof a, "%s.%s.%s.%s", groups[0], groups[1], groups[2], groups[3]);
        else snprintf(a, sizeof a, "%s.%s.%s.%s:%s", groups[0], groups[1], groups[2], groups[3], groups[4]);
    }
    char host[64];
    int port;
    if (rg_net_parse_address(a, host, sizeof host, &port)) {
        fail("That address doesn't look right.");
        return;
    }
    snprintf(U.addr, sizeof U.addr, "%s", a);
    last_address(U.addr, 0, 1);
    char err[200];
    U.conn = rg_net_connect_begin(host, port, err, sizeof err);
    if (!U.conn) {
        fail("Couldn't find that address.");
        return;
    }
    U.state = S_JOIN_CALL;
    U.calls = 0;
    U.want_dialog = D_JOIN_CALL;
}

static void send_hello(void)
{
    rg_net_hello h;
    memset(&h, 0, sizeof h);
    memcpy(h.magic, "RGINSNET", 8);
    h.protocol = RG_NET_PROTOCOL;
    h.role = (uint32_t)U.role;
    h.build = rg_insnet_build_id();
    h.data = rg_insnet_data_id();
    snprintf(h.name, sizeof h.name, "%s", U.role == 0 ? "Player 1" : "Player 2");
    uint8_t b[RG_NET_HELLO_BYTES];
    rg_net_hello_pack(&h, b);
    rg_net_send_msg(U.sock, RG_MSG_HELLO, b, sizeof b);
}

/* per frame while the flow runs (from the 2-Player menu step and from our dialog's step).
 * Returns 1 when the dialog on screen should close by itself (its question is moot). */
static int tick_inner(void)
{
    char err[200] = "";
    switch (U.state) {
    case S_HOST_WAIT:
        if (U.listener && !U.sock) {
            U.sock = rg_net_sock_accept(U.listener, 0, err, sizeof err);
            if (U.sock) {
                rg_net_sock_close(U.listener);   /* one rival */
                U.listener = NULL;
                send_hello();
                U.state = S_HELLO;
                U.t0 = rg_net_now_ms();
                fprintf(stderr, "rg-game: online battle (menu): a rival connected\n");
                return 1;
            }
        }
        return 0;
    case S_JOIN_CALL: {
        rg_net_sock *s = NULL;
        if (!U.conn) {
            /* keep calling (the host may not be waiting yet) until the player stops: a new
             * attempt every 2 s */
            if (rg_net_now_ms() - U.t0 < 2000) return 0;
            char host[64];
            int port;
            if (rg_net_parse_address(U.addr, host, sizeof host, &port) == 0)
                U.conn = rg_net_connect_begin(host, port, err, sizeof err);
            if (!U.conn) {
                fail("Couldn't find that address.");
                return 1;
            }
        }
        int r = rg_net_connect_poll(U.conn, 0, &s, err, sizeof err);
        if (getenv("RG_INSNET_DEBUG")) {
            static unsigned polls;
            if (r || (polls++ % 600) == 0)
                fprintf(stderr, "rg-game: online battle (menu): poll %u -> %d %s\n", polls, r, r < 0 ? err : "");
        }
        if (r == 1) {
            U.conn = NULL;
            U.sock = s;
            send_hello();
            U.state = S_HELLO;
            U.t0 = rg_net_now_ms();
            return 1;
        }
        if (r < 0) {
            U.conn = NULL;   /* (freed by the poll) try again in a moment */
            U.t0 = rg_net_now_ms();
            if (!U.calls++) fprintf(stderr, "rg-game: online battle (menu): %s; calling again\n", err);
        }
        return 0;
    }
    case S_HELLO:
    case S_LOAD:
    case S_FOUND:
    case S_WAIT_GO: {
        if (rg_net_sock_pump(U.sock, 0, err, sizeof err)) {
            fail("Your rival left.");
            return 1;
        }
        rg_net_msg m;
        int r = 0;
        /* nothing past the rival's "go": what follows is their session's, handed over */
        while (!U.got_go && (r = rg_net_peek_msg(U.sock, &m, err, sizeof err)) == 1) {
            if (m.type == RG_MSG_HELLO && U.state == S_HELLO) {
                rg_net_hello ph;
                if (rg_net_hello_unpack(m.body, &ph, err, sizeof err)) {
                    fail("That isn't a Rogue Galaxy game.");
                    return 1;
                }
                if (ph.protocol != RG_NET_PROTOCOL || ph.build != rg_insnet_build_id() || ph.data != rg_insnet_data_id()) {
                    fail("Your rival's game is another version.");
                    return 1;
                }
                if (ph.role == (uint32_t)U.role) {
                    fail(U.role == 0 ? "Your rival is hosting too." : "Your rival is joining too.");
                    return 1;
                }
                snprintf(U.peer, sizeof U.peer, "%s", ph.name);
                /* connected: each player now loads their own data with the 2-Player menu's own
                 * load screens ("Load Player 1's Data"); "Your rival is here!" follows */
                U.state = S_LOAD;
                U.loaded_seq_at_begin = mccard_last_loaded(NULL, NULL, 0);
                U.go2p_pending = 1;
            } else if (m.type == RG_MSG_READY) {
                U.got_go = 1;
            } else if (m.type == RG_MSG_BYE) {
                rg_net_msg_done(U.sock, &m);
                fail("Your rival changed their mind.");
                return 1;
            }
            rg_net_msg_done(U.sock, &m);
        }
        if (r < 0) {
            fail("Something went wrong.");
            return 1;
        }
        if (U.state == S_LOAD && U.ctx == 1) {
            int port = -1;
            unsigned seq = mccard_last_loaded(&port, U.loaded_path, sizeof U.loaded_path);
            if (seq != U.loaded_seq_at_begin && port >= 0 && U.loaded_path[0]) {
                U.loaded_port = port;
                U.state = S_FOUND;
                U.want_dialog = D_FOUND;
            }
        }
        if (U.state == S_HELLO && rg_net_now_ms() - U.t0 > 10000) {
            fail("Your rival didn't answer.");
            return 1;
        }
        if (U.state == S_WAIT_GO && U.got_go && U.sent_go) {
            U.state = S_GO;
            return 1;
        }
        return U.state == S_HELLO ? 0 : 0;
    }
    }
    return 0;
}

/* the state a dialog of ours belongs to (-1: any) */
static int dialog_state(int d)
{
    switch (d) {
    case D_HOST_WAIT: return S_HOST_WAIT;
    case D_JOIN_CALL: return S_JOIN_CALL;
    case D_FOUND: return S_FOUND;
    case D_WAIT_GO: return S_WAIT_GO;
    case D_ROLE: return S_ROLE;
    case D_FAIL: return S_FAIL;
    }
    return -1;
}

/* per frame while the flow runs.  Returns 1 when the dialog on screen should close by itself:
 * the flow moved on (the rival arrived, the call failed) and its question is moot. */
int rg_insnet_ui_tick(void)
{
    int r = tick_inner();
    int need = dialog_state(U.dialog_open);
    if (U.dialog_open && need >= 0 && need != U.state) r = 1;
    return r;
}

/* the player answered our dialog `id` (yes = 1).  The 2-Player menu comes back after it; the
 * flow then asks for the next dialog through rg_insnet_ui_want(). */
void rg_insnet_ui_answer(int id, int yes)
{
    U.dialog_open = 0;
    if (yes < 0) return;   /* closed by itself: the flow already moved on */
    switch (id) {
    case D_HOST_WAIT:
    case D_JOIN_CALL:
        if (yes) stop();   /* stop waiting / calling */
        else if (U.state == S_HOST_WAIT) U.want_dialog = D_HOST_WAIT;
        else if (U.state == S_JOIN_CALL) U.want_dialog = D_JOIN_CALL;
        break;
    case D_FOUND:
        if (!yes) {
            stop();
            break;
        }
        rg_net_send_msg(U.sock, RG_MSG_READY, "\0\0\0\0\0\0\0\0", 8);
        rg_net_sock_pump(U.sock, 0, NULL, 0);
        U.sent_go = 1;
        U.state = U.got_go ? S_GO : S_WAIT_GO;
        if (U.state == S_WAIT_GO) U.want_dialog = D_WAIT_GO;
        break;
    case D_WAIT_GO:
        if (yes) stop();
        else if (U.state == S_WAIT_GO) U.want_dialog = D_WAIT_GO;
        break;
    case D_FAIL:
        U.state = S_IDLE;
        if (yes) {   /* try again: host or join, where the player is now (mode list or 2-Player menu) */
            int ctx = U.ctx;
            rg_insnet_ui_begin();
            U.ctx = ctx;
        }
        break;
    case D_LOST:
        break;   /* the match goes on at this end; leaving the 2-Player Battle ends the session */
    case D_ROLE:
        U.role = yes ? 0 : 1;
        if (yes) start_host();
        else {
            U.state = S_JOIN_ENTRY;
            U.want_entry = 1;
        }
        break;
    case D_NEED_DATA:
    default:
        U.state = S_IDLE;
        break;
    }
}

/* the next thing the 2-Player menu should open: a dialog id (> 0), -1 = the address entry,
 * -2 = relaunch now (the menu does nothing more), 0 = nothing */
int rg_insnet_ui_want(void)
{
    if (U.state == S_GO) return -2;
    if (U.go2p_pending && U.ctx == 0 && !U.dialog_open && !U.entry_pending) {
        U.go2p_pending = 0;
        U.ctx = 1;
        return -3;
    }
    if (U.dialog_open || U.entry_pending) return 0;
    if (U.state == S_IDLE && rg_insnet_lost_notice()) {
        U.dialog_open = D_LOST;
        return D_LOST;
    }
    if (U.want_entry) {
        U.want_entry = 0;
        U.entry_pending = 1;
        return -1;
    }
    if (U.want_dialog) {
        int d = U.want_dialog;
        U.want_dialog = 0;
        if (dialog_state(d) >= 0 && dialog_state(d) != U.state) return 0;   /* stale: the flow moved on */
        U.dialog_open = d;
        return d;
    }
    return 0;
}

/* ------------------------------------------------------------------ relaunch */
/* start this exe again as the session (the connection inherited), then end this process */
void rg_insnet_ui_relaunch(void)
{
    char folder[1200];
    snprintf(folder, sizeof folder, "%s/card%d%s", saves_dir(), U.loaded_port + 1, U.loaded_path);
    char *slash = strrchr(folder, '/');   /* the data file -> its save folder */
    if (slash && slash > folder + strlen(saves_dir()) + 6) *slash = 0;
    uint64_t h = rg_net_sock_handle_for_child(U.sock);
    char hs[32];
    snprintf(hs, sizeof hs, "%llu", (unsigned long long)h);
    /* bytes this process already read past the rival's "go" belong to the session: hand them
     * over in a file (the session puts them back in front of its receive buffer) */
    char ho[1200];
    size_t left = 0;
    const uint8_t *rx = rg_net_sock_rx(U.sock, &left);
    snprintf(ho, sizeof ho, "%s/netplay", saves_dir());
#ifdef _WIN32
    CreateDirectoryA(ho, NULL);
#else
    mkdir(ho, 0755);
#endif
    snprintf(ho, sizeof ho, "%s/netplay/handover.bin", saves_dir());
    FILE *f = fopen(ho, "wb");
    if (f) {
        if (left) fwrite(rx, 1, left, f);
        fclose(f);
    }
    const char *extra[] = {"--net-handle", hs, "--net-role", U.role == 0 ? "host" : "join", "--net-save", folder,
                           "--net-handover-file", ho, "--net-relaunch"};
    rg_insnet_spawn_self(g_argc, g_argv, extra, 9);
}

/* start this exe with argv minus any --net-* plus extra; the caller's process then ends */
void rg_insnet_spawn_self(int argc, char **argv, const char *const *extra, int nextra)
{
    char *args[256];
    int n = 0;
    args[n++] = argv && argc ? argv[0] : (char *)"rg-game";
    for (int i = 1; argv && i < argc && n < 200; i++) {
        if (!strncmp(argv[i], "--net-", 6)) {
            if (strcmp(argv[i], "--net-exit-at-end") && strcmp(argv[i], "--net-solo") && strcmp(argv[i], "--net-relaunch") &&
                i + 1 < argc)
                i++;
            continue;
        }
        if (!strcmp(argv[i], "--shot") && i + 1 < argc &&
            strtoull(argv[i + 1], NULL, 0) > rg_runtime_get_stats()->fields) {
            args[n++] = argv[i++];   /* a shot still to come: the session takes it (tests) */
            args[n++] = argv[i];
            continue;
        }
        if ((!strcmp(argv[i], "--shot") || !strcmp(argv[i], "--screenshot") || !strcmp(argv[i], "--input")) &&
            i + 1 < argc) {
            i++;   /* the first process's shots / script, not the session's */
            continue;
        }
        args[n++] = argv[i];
    }
    for (int i = 0; i < nextra && n < 254; i++) args[n++] = (char *)extra[i];
    args[n] = NULL;
    fflush(stdout);
    fflush(stderr);
#ifdef _WIN32
    char exe[1024];
    if (!GetModuleFileNameA(NULL, exe, sizeof exe)) return;
    char cmd[8192];
    size_t L = 0;
    for (int i = 0; i < n && L < sizeof cmd - 4; i++) {
        const char *a = i == 0 ? exe : args[i];
        L += (size_t)snprintf(cmd + L, sizeof cmd - L, "%s\"%s\"", i ? " " : "", a);
    }
    STARTUPINFOA si;
    PROCESS_INFORMATION pi;
    memset(&si, 0, sizeof si);
    si.cb = sizeof si;
    if (CreateProcessA(exe, cmd, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi)) {
        CloseHandle(pi.hThread);
        CloseHandle(pi.hProcess);
        fprintf(stderr, "rg-game: online battle: the session starts (pid %lu)\n", (unsigned long)pi.dwProcessId);
        _Exit(0);
    }
    fprintf(stderr, "rg-game: online battle: cannot start the session (%lu)\n", (unsigned long)GetLastError());
#else
    char exe[1024];
    ssize_t len = readlink("/proc/self/exe", exe, sizeof exe - 1);
    if (len <= 0) return;
    exe[len] = 0;
    execv(exe, args);
    perror("rg-game: online battle: execv");
#endif
}

/* the address entry's title (+0xE8) and cell template (+0x197) after TextEntrySetMode(1): the
 * game's generic-mode layout, see docs/INSECTRON-VERSUS.md "Address entry" */
void rg_insnet_ui_entry_setup(void *entry)
{
    uint8_t *e = (uint8_t *)entry;
    /* +0x197: the cell template (0xAF bytes, '1' = a cell to fill, '.' = none): one row of 21 */
    memset(e + 0x197, '.', 0xAE);
    memset(e + 0x197, '1', 21);
    e[0x197 + 0xAE] = 0;
    if (getenv("RG_INSNET_ENTRY_DUMP")) {
        for (int part = 0; part < 3; part++) {
            int off = part == 0 ? 0xE8 : part == 1 ? 0x197 : 0x30;
            fprintf(stderr, "ENTRYDUMP +0x%X:", off);
            for (int i = 0; i < 0xAF; i++) fprintf(stderr, " %02X", e[off + i]);
            fprintf(stderr, "\n");
        }
    }
}

/* debug ($RG_INSNET_UIDUMP=1): the INSMENU widget list (ids, positions, sprite and text slots)
 * -- the layout facts the mode list's extra row is built from (i686 only: raw pointers) */
void rg_insnet_ui_dump(const void *mgr)
{
#if !defined(_WIN64) && !defined(__x86_64__)
    if (!getenv("RG_INSNET_UIDUMP") || !mgr) return;
    const uint8_t *link = *(const uint8_t *const *)mgr;
    for (int n = 0; link && n < 400; n++) {
        const uint8_t *e = *(const uint8_t *const *)link;
        if (!e) break;
        float x, y;
        memcpy(&x, e + 0x14, 4);
        memcpy(&y, e + 0x18, 4);
        fprintf(stderr, "UIDUMP elem id=0x%X pos=%.0f,%.0f h1C=%d raw:", *(const uint16_t *)e, x, y, *(const int16_t *)(e + 0x1C));
        for (int i = 0; i < 0x94; i += 4) fprintf(stderr, " %08X", *(const uint32_t *)(e + i));
        fprintf(stderr, "\n");
        const uint8_t *sp = *(const uint8_t *const *)(e + 0x20);
        for (int i = 0; sp && i < 48; i++) {
            fprintf(stderr, "UIDUMP   spr%d:", i);
            for (int k = 0; k < 0x20; k += 2) fprintf(stderr, " %d", *(const int16_t *)(sp + i * 0x20 + k));
            fprintf(stderr, "\n");
            if (*(const int16_t *)(sp + i * 0x20) < 0) break;
        }
        const uint8_t *tx = *(const uint8_t *const *)(e + 0x28);
        for (int i = 0; tx && i < 10; i++) {
            const uint8_t *t = tx + i * 0x10;
            const char *s = *(const char *const *)(t + 4);
            fprintf(stderr, "UIDUMP   txt%d: x=%d y=%d w08=%08X b=%02X%02X%02X%02X c=%08X s=\"%.30s\"\n", i, *(const int16_t *)t,
                    *(const int16_t *)(t + 2), *(const uint32_t *)(t + 8), t[8], t[9], t[10], t[11], *(const uint32_t *)(t + 12),
                    (s && (uintptr_t)s > 0x10000) ? s : "");
            if (*(const int16_t *)t < 0) break;
        }
        link = *(const uint8_t *const *)(link + 8);
    }
#else
    (void)mgr;
#endif
}

/* ---------------------------------------------------------- the mode list row
 * The INSMENU mode list (widget 1 at 38,80; out/insnet/uidump_top.txt) draws its four mode rows
 * from repeated sprites: the row frame (widget 3) and the label boxes (0x39, under 3) are each one
 * sprite set repeated ny = 4 times at a 43-pixel step (sprite +0x14 f32 = rows, +0x1A = step);
 * "Return to title" is its own small frame (0x36 at y 172); the row names are text slots of 0x37
 * (y 12 + 43 * row; slot 4 = Return to title) and the side labels ("1P", "2P", "CPU") slots of 0x38;
 * the controller icons and the "VS" mark are sprites of 0x3B (under 3).
 * The sixth row, "Online Battle", becomes row 4 exactly like the 2-Player Battle row (frame, label
 * box, 1P [pad] VS [pad] 2P), and Return to title moves one step down to row 5: the frame and box
 * repeat 5 times, the text / sprite arrays are copied into larger ones here (the game's own text
 * system and sprite sheet draw them; nothing new is drawn).  Game memory holds 4-byte pointers on
 * every arch.  Called after insmenu_InsectVsTopPanelLayout_4f2c20 (override), idempotent. */
#define ROW_STEP 43
static uint8_t *gp(uint32_t a) { return (uint8_t *)(uintptr_t)a; }
static uint32_t ga(const void *p) { return (uint32_t)(uintptr_t)p; }

static uint8_t *find_elem(void *mgr, uint16_t id, uint16_t parent)
{
    uint8_t *link = gp(*(uint32_t *)mgr);
    for (int n = 0; link && n < 2000; n++) {
        uint8_t *e = gp(*(uint32_t *)link);
        if (!e) break;
        if (*(uint16_t *)e == id && *(uint16_t *)(e + 2) == parent) return e;
        link = gp(*(uint32_t *)(link + 8));
    }
    return NULL;
}

static int count_until_end(const uint8_t *arr, int size, int max)
{
    int n = 0;
    while (n < max && *(const int16_t *)(arr + n * size) != -1) n++;
    return n;
}

static void set_rows(uint8_t *e, float from, float to)
{
    uint8_t *sp = e ? gp(*(uint32_t *)(e + 0x20)) : NULL;
    for (int i = 0; sp && i < 64 && *(int16_t *)(sp + i * 0x20) != -1; i++) {
        float ny;
        memcpy(&ny, sp + i * 0x20 + 0x14, 4);
        if (ny == from) memcpy(sp + i * 0x20 + 0x14, &to, 4);
    }
}

void rg_insnet_ui_top_layout(void *widgets)
{
    static uint8_t names[8 * 0x10], labels[10 * 0x10], icons[24 * 0x20];
    static const char online_name[] = "Online Battle";
    if (!widgets) return;
    uint8_t *frame = find_elem(widgets, 0x03, 0x01), *box = find_elem(widgets, 0x39, 0x03);
    uint8_t *ret = find_elem(widgets, 0x36, 0x01), *ic = find_elem(widgets, 0x3B, 0x03);
    uint8_t *tx = find_elem(widgets, 0x37, 0x01), *lb = find_elem(widgets, 0x38, 0x01);
    if (!frame || !box || !ret || !ic || !tx || !lb) return;   /* not the retail layout: leave it */
    set_rows(frame, 4.0f, 5.0f);
    set_rows(box, 4.0f, 5.0f);
    /* Return to title: one row down (its position and the animation's rest position) */
    float y = 172.0f + ROW_STEP;
    memcpy(ret + 0x18, &y, 4);
    memcpy(ret + 0x64, &y, 4);
    /* row names: slot 4 = Online Battle, slot 5 = Return to title (the game's own string) */
    uint8_t *t = gp(*(uint32_t *)(tx + 0x28));
    if (t != names) {
        int n = count_until_end(t, 0x10, 6);
        if (n != 5) return;
        memcpy(names, t, 6 * 0x10);   /* 5 slots + the end mark */
        *(uint32_t *)(tx + 0x28) = ga(names);
    }
    if (*(uint32_t *)(names + 4 * 0x10 + 4) != ga(online_name)) {
        memcpy(names + 5 * 0x10, names + 4 * 0x10, 0x10);       /* Return to title -> slot 5 */
        *(int16_t *)(names + 5 * 0x10 + 2) = (int16_t)(*(int16_t *)(names + 4 * 0x10 + 2) + ROW_STEP);
        *(uint32_t *)(names + 4 * 0x10 + 4) = ga(online_name);  /* slot 4: our row's name */
        memset(names + 6 * 0x10, 0, 0x10);
        *(int16_t *)(names + 6 * 0x10) = -1;
    }
    /* side labels: "1P" and "2P" (the 2-Player row's own strings) on row 4 */
    uint8_t *l = gp(*(uint32_t *)(lb + 0x28));
    if (l != labels) {
        int n = count_until_end(l, 0x10, 8);
        if (n != 6) return;
        memcpy(labels, l, 6 * 0x10);
        memcpy(labels + 6 * 0x10, l + 0 * 0x10, 0x10);   /* "1P" of row 0 */
        memcpy(labels + 7 * 0x10, l + 3 * 0x10, 0x10);   /* "2P" of row 0 */
        *(int16_t *)(labels + 6 * 0x10 + 2) = (int16_t)(*(int16_t *)(l + 2) + 4 * ROW_STEP);
        *(int16_t *)(labels + 7 * 0x10 + 2) = (int16_t)(*(int16_t *)(l + 3 * 0x10 + 2) + 4 * ROW_STEP);
        memset(labels + 8 * 0x10, 0, 0x10);
        *(int16_t *)(labels + 8 * 0x10) = -1;
        *(uint32_t *)(lb + 0x28) = ga(labels);
    } else {
        /* the layout rewrote slots 0..5: keep row 4's labels the game's current "1P" / "2P" */
        *(uint32_t *)(labels + 6 * 0x10 + 4) = *(uint32_t *)(labels + 0 * 0x10 + 4);
        *(uint32_t *)(labels + 7 * 0x10 + 4) = *(uint32_t *)(labels + 3 * 0x10 + 4);
    }
    /* controller icons and VS on row 4: copies of row 0's (sprites 0, 1 and the VS mark 6) */
    uint8_t *s = gp(*(uint32_t *)(ic + 0x20));
    if (s != icons) {
        int n = count_until_end(s, 0x20, 20);
        if (n != 11) return;
        memcpy(icons, s, (size_t)n * 0x20);
        int k = n;
        const int src[3] = {0, 1, 6};
        for (int i = 0; i < 3; i++, k++) {
            memcpy(icons + k * 0x20, s + src[i] * 0x20, 0x20);
            *(int16_t *)(icons + k * 0x20 + 2) = (int16_t)(*(int16_t *)(s + src[i] * 0x20 + 2) + 4 * ROW_STEP);
            float one = 1.0f;
            memcpy(icons + k * 0x20 + 0x14, &one, 4);   /* the VS mark repeats 3 rows: here once */
        }
        memset(icons + k * 0x20, 0, 0x20);
        *(int16_t *)(icons + k * 0x20) = -1;
        *(uint32_t *)(ic + 0x20) = ga(icons);
    }
}

/* the player backed out of the 2-Player menu during the online flow: hang up */
void rg_insnet_ui_cancel(void)
{
    if (U.state != S_IDLE) stop();
    U.ctx = 0;
}

/* the menu step should take no input: the flow is between its screens (not while the player
 * loads their data in the 2-Player menu) */
int rg_insnet_ui_blocks_menu(void)
{
    return (U.state != S_IDLE && U.state != S_LOAD) || U.dialog_open || U.entry_pending;
}

/* the mode list's cursor row as the menu step last saw it (Focus puts it back on Online) */
static int g_top_row;
void rg_insnet_ui_set_top_row(int row) { g_top_row = row; }
int rg_insnet_ui_top_row(void) { return g_top_row; }

/* once, on entering the 2-Player menu for the online flow: the menu should count the controller
 * setting as done (the session sets its own controllers), so the cursor starts on "Load Player 1's
 * Data" -- loading your own data is the step that matters */
int rg_insnet_ui_take_ctrl_done(void)
{
    static unsigned done_for;
    static unsigned flow;
    if (U.state == S_ROLE) flow++;   /* (a new flow) */
    if (U.ctx == 1 && U.state == S_LOAD && done_for != flow + 1) {
        done_for = flow + 1;
        return 1;
    }
    return 0;
}
