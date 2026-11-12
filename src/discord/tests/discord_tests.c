/* SPDX-License-Identifier: CC0-1.0 */
/* rg_discord tests against a fake Discord IPC server (docs/DISCORD.md).   ctest -L discord
 *
 *   idle      no / bad application ID: no thread
 *   json      string escaping
 *   absent    no server: calls never block, stop is quick, nothing connects
 *   protocol  fake server on a private pipe name: handshake, READY, SET_ACTIVITY with our pid
 *             and text, PING -> PONG, a text change, the server dropping the pipe -> the
 *             client reconnects and sends the activity again; stop closes the pipe
 */
#include "rg_discord.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
static double ms(void) { return (double)GetTickCount64(); }
static void nap(int m) { Sleep((DWORD)m); }
static unsigned pid(void) { return (unsigned)GetCurrentProcessId(); }
#else
#include <pthread.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <time.h>
#include <unistd.h>
static double ms(void)
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec * 1000.0 + ts.tv_nsec / 1e6;
}
static void nap(int m) { usleep((useconds_t)m * 1000); }
static unsigned pid(void) { return (unsigned)getpid(); }
#endif

static int g_fail;
#define CHECK(c) do { if (!(c)) { fprintf(stderr, "%s:%d: CHECK(%s)\n", __FILE__, __LINE__, #c); g_fail++; } } while (0)

static const char *ID = "123456789012345678";
static char g_prefix[64];

/* ---------------------------------------------------------------- fake server */
#ifdef _WIN32
typedef HANDLE srv_t;
static srv_t srv_accept(void)
{
    char name[128];
    snprintf(name, sizeof name, "\\\\.\\pipe\\%s0", g_prefix);
    HANDLE h = CreateNamedPipeA(name, PIPE_ACCESS_DUPLEX, PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT, 1,
                                65536, 65536, 0, NULL);
    if (h == INVALID_HANDLE_VALUE) return NULL;
    if (!ConnectNamedPipe(h, NULL) && GetLastError() != ERROR_PIPE_CONNECTED) {
        CloseHandle(h);
        return NULL;
    }
    return h;
}
static int srv_read(srv_t h, void *b, unsigned n)
{
    char *p = (char *)b;
    while (n) {
        DWORD r = 0;
        if (!ReadFile(h, p, n, &r, NULL) || !r) return -1;
        p += r;
        n -= r;
    }
    return 0;
}
static int srv_write(srv_t h, const void *b, unsigned n)
{
    DWORD w = 0;
    return WriteFile(h, b, n, &w, NULL) && w == n ? 0 : -1;
}
static void srv_close(srv_t h)
{
    FlushFileBuffers(h);
    DisconnectNamedPipe(h);
    CloseHandle(h);
}
#else
typedef int srv_t;
static int g_listen = -1;
static srv_t srv_accept(void)
{
    if (g_listen < 0) {
        const char *d = getenv("XDG_RUNTIME_DIR");
        struct sockaddr_un a;
        memset(&a, 0, sizeof a);
        a.sun_family = AF_UNIX;
        snprintf(a.sun_path, sizeof a.sun_path, "%s/%s0", d && *d ? d : "/tmp", g_prefix);
        unlink(a.sun_path);
        g_listen = socket(AF_UNIX, SOCK_STREAM, 0);
        if (bind(g_listen, (struct sockaddr *)&a, sizeof a) || listen(g_listen, 1)) return 0;
    }
    int c = accept(g_listen, NULL, NULL);
    return c < 0 ? 0 : c;
}
static int srv_read(srv_t h, void *b, unsigned n)
{
    char *p = (char *)b;
    while (n) {
        ssize_t r = recv(h, p, n, 0);
        if (r <= 0) return -1;
        p += r;
        n -= (unsigned)r;
    }
    return 0;
}
static int srv_write(srv_t h, const void *b, unsigned n) { return send(h, b, n, 0) == (ssize_t)n ? 0 : -1; }
static void srv_close(srv_t h) { close(h); }
#endif

static int frame_read(srv_t h, unsigned *op, char *body, unsigned cap)
{
    unsigned char hd[8];
    if (srv_read(h, hd, 8)) return -1;
    *op = hd[0] | hd[1] << 8 | hd[2] << 16 | (unsigned)hd[3] << 24;
    unsigned len = hd[4] | hd[5] << 8 | hd[6] << 16 | (unsigned)hd[7] << 24;
    if (len >= cap || srv_read(h, body, len)) return -1;
    body[len] = 0;
    return 0;
}
static int frame_write(srv_t h, unsigned op, const char *json)
{
    unsigned len = (unsigned)strlen(json);
    unsigned char b[1024];
    for (int i = 0; i < 4; i++) {
        b[i] = (unsigned char)(op >> (8 * i));
        b[4 + i] = (unsigned char)(len >> (8 * i));
    }
    memcpy(b + 8, json, len);
    return srv_write(h, b, len + 8);
}

static const char *READY = "{\"cmd\":\"DISPATCH\",\"evt\":\"READY\",\"data\":{\"v\":1}}";
static int g_server_ok;
static double g_t_reconnect;

static int expect_activity(srv_t h, const char *details)
{
    unsigned op;
    char body[4096], want[256];
    if (frame_read(h, &op, body, sizeof body) || op != 1) return -1;
    snprintf(want, sizeof want, "\"pid\":%u", pid());
    if (!strstr(body, "\"cmd\":\"SET_ACTIVITY\"") || !strstr(body, want) || !strstr(body, "\"nonce\":")) return -2;
    if (!strstr(body, "\"timestamps\":{\"start\":")) return -3;
    snprintf(want, sizeof want, "\"details\":\"%s\"", details);
    if (!strstr(body, want)) {
        fprintf(stderr, "activity without %s: %s\n", want, body);
        return -4;
    }
    printf("server: %s\n", body);
    return 0;
}

static void server(void)
{
    unsigned op;
    char body[4096], want[64];
    srv_t h = srv_accept();
    if (!h) return;
    snprintf(want, sizeof want, "\"client_id\":\"%s\"", ID);
    if (frame_read(h, &op, body, sizeof body) || op != 0 || !strstr(body, want) || !strstr(body, "\"v\":1")) return;
    if (frame_write(h, 1, READY)) return;
    if (expect_activity(h, "Ch. 1: Departure")) return;
    if (frame_write(h, 3, "{\"ping\":7}") || frame_read(h, &op, body, sizeof body) || op != 4 ||
        strcmp(body, "{\"ping\":7}"))
        return;
    if (expect_activity(h, "Ch. 2: \\\"Quote\\\" \\\\ back")) return;   /* after the text change */
    srv_close(h);                                                      /* Discord quits */
    double t0 = ms();
    h = srv_accept();                                                  /* ... and comes back */
    if (!h) return;
    g_t_reconnect = ms() - t0;
    if (frame_read(h, &op, body, sizeof body) || op != 0) return;
    if (frame_write(h, 1, READY)) return;
    if (expect_activity(h, "Ch. 2: \\\"Quote\\\" \\\\ back")) return;
    g_server_ok = 1;
    /* wait for the client to close (rg_discord_stop) */
    while (frame_read(h, &op, body, sizeof body) == 0)
        if (op == 3) frame_write(h, 4, body);
    srv_close(h);
    g_server_ok = 2;
}

#ifdef _WIN32
static DWORD WINAPI server_thread(LPVOID p) { (void)p; server(); return 0; }
#else
static void *server_thread(void *p) { (void)p; server(); return NULL; }
#endif

/* ---------------------------------------------------------------- tests */
static void t_idle(void)
{
    CHECK(rg_discord_start(NULL) == 1);
    CHECK(rg_discord_start("") == 1);
    CHECK(rg_discord_start("12ab5678901234567") == 1);
    CHECK(rg_discord_valid_id(ID));
    rg_discord_set_activity("x", "y");   /* no-ops */
    rg_discord_stop();
    rg_discord_stats st;
    rg_discord_get_stats(&st);
    CHECK(!st.running && !st.connects);
}

static void t_json(void)
{
    char b[64];
    CHECK(rg_discord_json_str(b, sizeof b, "a\"b\\c\n") > 0 && !strcmp(b, "\"a\\\"b\\\\c\\u000a\""));
    CHECK(rg_discord_json_str(b, 4, "abcdef") == -1);
    CHECK(rg_discord_json_str(b, sizeof b, NULL) == 2 && !strcmp(b, "\"\""));
}

static void t_absent(void)
{
    rg_discord_test_config(g_prefix, 50, 50);   /* nobody serves this name */
    double t0 = ms();
    CHECK(rg_discord_start(ID) == 0);
    for (int i = 0; i < 1000; i++) rg_discord_set_activity(i & 1 ? "a" : "b", "s");
    double t1 = ms();
    nap(300);   /* several connect attempts */
    double t2 = ms();
    rg_discord_stop();
    double t3 = ms();
    rg_discord_stats st;
    rg_discord_get_stats(&st);
    printf("absent: start + 1000 updates %.0f ms, stop %.0f ms, connects %u\n", t1 - t0, t3 - t2, st.connects);
    CHECK(t1 - t0 < 100);
    CHECK(t3 - t2 < 700);
    CHECK(st.connects == 0 && st.activities == 0 && !st.running);
}

static void t_protocol(void)
{
#ifdef _WIN32
    HANDLE th = CreateThread(NULL, 0, server_thread, NULL, 0, NULL);
#else
    pthread_t th;
    pthread_create(&th, NULL, server_thread, NULL);
#endif
    nap(100);   /* the server's pipe exists */
    rg_discord_test_config(g_prefix, 200, 100);
    rg_discord_set_activity("Ch. 1: Departure", "");   /* before start: kept */
    CHECK(rg_discord_start(ID) == 0);
    nap(600);
    rg_discord_set_activity("Ch. 2: \"Quote\" \\ back", "");
    for (int i = 0; i < 100 && g_server_ok < 1; i++) nap(50);
    rg_discord_stats st;
    rg_discord_get_stats(&st);
    CHECK(g_server_ok >= 1);
    CHECK(st.connected == 1 && st.connects == 2 && st.activities == 3 && st.pongs == 1);
    double t0 = ms();
    rg_discord_stop();
    double t1 = ms();
#ifdef _WIN32
    WaitForSingleObject(th, 5000);
    CloseHandle(th);
#else
    pthread_join(th, NULL);
#endif
    printf("protocol: server %d, reconnect after %.0f ms, stop %.0f ms, connects %u activities %u pongs %u errors %u\n",
           g_server_ok, g_t_reconnect, t1 - t0, st.connects, st.activities, st.pongs, st.errors);
    CHECK(g_server_ok == 2);   /* the server saw the client close */
    CHECK(t1 - t0 < 1000);
}

/* manual (not in ctest): against the real Discord app with a made-up application ID:
 * Discord accepts the pipe and closes it with "Invalid Client ID"; the client counts one
 * connect + one error, sends no activity and backs off (5 min) */
static void t_live(void)
{
    rg_discord_test_config("discord-ipc-", 0, 0);
    CHECK(rg_discord_start("100000000000000001") == 0);
    nap(1500);
    rg_discord_stats st;
    rg_discord_get_stats(&st);
    double t0 = ms();
    rg_discord_stop();
    printf("live: connects %u errors %u activities %u connected %d, stop %.0f ms\n", st.connects, st.errors,
           st.activities, st.connected, ms() - t0);
    CHECK(st.connects == 1 && st.errors == 1 && st.activities == 0 && !st.connected);
}

int main(int argc, char **argv)
{
    const char *which = argc > 1 ? argv[1] : "";
    snprintf(g_prefix, sizeof g_prefix, "rg-test-ipc-%u-", pid());
    if (!strcmp(which, "idle")) t_idle();
    else if (!strcmp(which, "json")) t_json();
    else if (!strcmp(which, "absent")) t_absent();
    else if (!strcmp(which, "protocol")) t_protocol();
    else if (!strcmp(which, "live")) t_live();
    else {
        fprintf(stderr, "usage: rg-discord-tests idle|json|absent|protocol\n");
        return 2;
    }
    if (g_fail) {
        fprintf(stderr, "%d check(s) failed\n", g_fail);
        return 1;
    }
    printf("ok (%s)\n", which);
    return 0;
}
