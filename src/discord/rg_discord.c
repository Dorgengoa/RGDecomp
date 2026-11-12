/* SPDX-License-Identifier: CC0-1.0 */
/* Discord Rich Presence over the local IPC pipe: rg_discord.h, docs/DISCORD.md.
 * Written from Discord's public RPC / IPC documentation (frame = u32 LE op, u32 LE length,
 * JSON; op 0 HANDSHAKE, 1 FRAME, 2 CLOSE, 3 PING, 4 PONG). */
#include "rg_discord.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
typedef HANDLE pipe_t;
#define PIPE_NONE INVALID_HANDLE_VALUE
#else
#include <errno.h>
#include <poll.h>
#include <pthread.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/un.h>
#include <unistd.h>
typedef int pipe_t;
#define PIPE_NONE (-1)
#endif

enum { OP_HANDSHAKE = 0, OP_FRAME = 1, OP_CLOSE = 2, OP_PING = 3, OP_PONG = 4 };
#define TEXT_MAX 128
#define FRAME_MAX 65536

static struct {
    int started;
    volatile int stop;
    char client_id[32];
    char prefix[64];
    int retry_ms, activity_ms;
    /* shared with the caller, under the lock */
    char details[TEXT_MAX], state[TEXT_MAX];
    int dirty;
    rg_discord_stats st;
    int64_t start_unix;
#ifdef _WIN32
    CRITICAL_SECTION lock;
    HANDLE wake, thread;
#else
    pthread_mutex_t lock;
    pthread_cond_t cond;
    int woken;
    pthread_t thread;
#endif
} D;   /* zero: idle; retry / activity intervals 0 = the defaults (20 s, 15 s) */

/* ------------------------------------------------------------------ platform */
#ifdef _WIN32
static uint64_t now_ms(void) { return GetTickCount64(); }
static void lock(void) { EnterCriticalSection(&D.lock); }
static void unlock(void) { LeaveCriticalSection(&D.lock); }
static void wake(void) { SetEvent(D.wake); }
static void wait_ms(int ms) { WaitForSingleObject(D.wake, (DWORD)(ms < 0 ? 0 : ms)); }
static uint32_t self_pid(void) { return (uint32_t)GetCurrentProcessId(); }

static pipe_t pipe_open(int n)
{
    wchar_t name[128];
    swprintf(name, 128, L"\\\\.\\pipe\\%hs%d", D.prefix, n);
    HANDLE h = CreateFileW(name, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
    return h;
}
static void pipe_close(pipe_t h) { CloseHandle(h); }
static int pipe_write(pipe_t h, const void *b, uint32_t n)
{
    DWORD w = 0;
    return WriteFile(h, b, n, &w, NULL) && w == n ? 0 : -1;
}
/* bytes waiting, -1 = the pipe is gone */
static int64_t pipe_avail(pipe_t h)
{
    DWORD a = 0;
    return PeekNamedPipe(h, NULL, 0, NULL, &a, NULL) ? (int64_t)a : -1;
}
static int pipe_read(pipe_t h, void *b, uint32_t n)
{
    uint8_t *p = (uint8_t *)b;
    while (n) {
        DWORD r = 0;
        if (!ReadFile(h, p, n, &r, NULL) || !r) return -1;
        p += r;
        n -= r;
    }
    return 0;
}
#else
static uint64_t now_ms(void)
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint64_t)ts.tv_sec * 1000u + (uint64_t)ts.tv_nsec / 1000000u;
}
static void lock(void) { pthread_mutex_lock(&D.lock); }
static void unlock(void) { pthread_mutex_unlock(&D.lock); }
static void wake(void)
{
    pthread_mutex_lock(&D.lock);
    D.woken = 1;
    pthread_cond_signal(&D.cond);
    pthread_mutex_unlock(&D.lock);
}
static void wait_ms(int ms)
{
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    ts.tv_sec += ms / 1000;
    ts.tv_nsec += (long)(ms % 1000) * 1000000L;
    if (ts.tv_nsec >= 1000000000L) { ts.tv_sec++; ts.tv_nsec -= 1000000000L; }
    pthread_mutex_lock(&D.lock);
    while (!D.woken && !D.stop)
        if (pthread_cond_timedwait(&D.cond, &D.lock, &ts)) break;
    D.woken = 0;
    pthread_mutex_unlock(&D.lock);
}
static uint32_t self_pid(void) { return (uint32_t)getpid(); }

static pipe_t pipe_open(int n)
{
    const char *dirs[] = {getenv("XDG_RUNTIME_DIR"), getenv("TMPDIR"), getenv("TMP"), getenv("TEMP"), "/tmp"};
    for (size_t i = 0; i < sizeof dirs / sizeof dirs[0]; i++) {
        if (!dirs[i] || !*dirs[i]) continue;
        struct sockaddr_un a;
        memset(&a, 0, sizeof a);
        a.sun_family = AF_UNIX;
        snprintf(a.sun_path, sizeof a.sun_path, "%s/%s%d", dirs[i], D.prefix, n);
        int s = socket(AF_UNIX, SOCK_STREAM, 0);
        if (s < 0) return PIPE_NONE;
#ifdef SO_NOSIGPIPE
        { int one = 1; setsockopt(s, SOL_SOCKET, SO_NOSIGPIPE, &one, sizeof one); }
#endif
        if (connect(s, (struct sockaddr *)&a, sizeof a) == 0) return s;
        close(s);
    }
    return PIPE_NONE;
}
static void pipe_close(pipe_t h) { close(h); }
static int pipe_write(pipe_t h, const void *b, uint32_t n)
{
    const uint8_t *p = (const uint8_t *)b;
    while (n) {
#ifdef MSG_NOSIGNAL
        ssize_t w = send(h, p, n, MSG_NOSIGNAL);
#else
        ssize_t w = send(h, p, n, 0);
#endif
        if (w <= 0) return -1;
        p += w;
        n -= (uint32_t)w;
    }
    return 0;
}
static int64_t pipe_avail(pipe_t h)
{
    struct pollfd pf = {h, POLLIN, 0};
    int r = poll(&pf, 1, 0);
    if (r < 0) return -1;
    if (r == 0) return 0;
    if (pf.revents & (POLLERR | POLLNVAL)) return -1;
    uint8_t b[8];
    ssize_t k = recv(h, b, sizeof b, MSG_PEEK | MSG_DONTWAIT);
    if (k == 0) return -1;   /* closed */
    return k < 0 ? (errno == EAGAIN || errno == EWOULDBLOCK ? 0 : -1) : (int64_t)k;
}
static int pipe_read(pipe_t h, void *b, uint32_t n)
{
    uint8_t *p = (uint8_t *)b;
    while (n) {
        ssize_t r = recv(h, p, n, 0);
        if (r <= 0) return -1;
        p += r;
        n -= (uint32_t)r;
    }
    return 0;
}
#endif

/* ------------------------------------------------------------------ JSON / frames */
int rg_discord_json_str(char *out, int cap, const char *s)
{
    int o = 0;
#define PUT(c) do { if (o + 1 >= cap) return -1; out[o++] = (char)(c); } while (0)
    PUT('"');
    for (const unsigned char *p = (const unsigned char *)(s ? s : ""); *p; p++) {
        if (*p == '"' || *p == '\\') { PUT('\\'); PUT(*p); }
        else if (*p < 0x20) {
            if (o + 7 >= cap) return -1;
            o += snprintf(out + o, (size_t)(cap - o), "\\u%04x", *p);
        } else PUT(*p);
    }
    PUT('"');
#undef PUT
    out[o] = 0;
    return o;
}

int rg_discord_valid_id(const char *id)
{
    if (!id) return 0;
    size_t n = strlen(id);
    if (n < 5 || n > 24) return 0;
    for (size_t i = 0; i < n; i++)
        if (id[i] < '0' || id[i] > '9') return 0;
    return 1;
}

static int send_frame(pipe_t h, uint32_t op, const char *json, uint32_t len)
{
    uint8_t hdr[8] = {(uint8_t)op, (uint8_t)(op >> 8), (uint8_t)(op >> 16), (uint8_t)(op >> 24),
                      (uint8_t)len, (uint8_t)(len >> 8), (uint8_t)(len >> 16), (uint8_t)(len >> 24)};
    /* one write: Discord reads a frame as a unit */
    uint8_t buf[4096];
    if (len + 8 > sizeof buf) return -1;
    memcpy(buf, hdr, 8);
    memcpy(buf + 8, json, len);
    return pipe_write(h, buf, len + 8);
}

static int send_activity(pipe_t h, uint32_t nonce)
{
    char det[TEXT_MAX * 6 + 4], sta[TEXT_MAX * 6 + 4], act[2048], json[3072];
    lock();
    int hd = D.details[0] != 0, hs = D.state[0] != 0;
    if (hd) rg_discord_json_str(det, (int)sizeof det, D.details);
    if (hs) rg_discord_json_str(sta, (int)sizeof sta, D.state);
    D.dirty = 0;
    unlock();
    int n = snprintf(act, sizeof act, "{%s%s%s%s%s%s\"timestamps\":{\"start\":%lld}}",
                     hd ? "\"details\":" : "", hd ? det : "", hd ? "," : "",
                     hs ? "\"state\":" : "", hs ? sta : "", hs ? "," : "", (long long)D.start_unix);
    if (n <= 0 || n >= (int)sizeof act) return -1;
    n = snprintf(json, sizeof json, "{\"cmd\":\"SET_ACTIVITY\",\"args\":{\"pid\":%u,\"activity\":%s},\"nonce\":\"%u\"}",
                 self_pid(), act, nonce);
    if (n <= 0 || n >= (int)sizeof json) return -1;
    return send_frame(h, OP_FRAME, json, (uint32_t)n);
}

static void bump(uint32_t *field)
{
    lock();
    (*field)++;
    unlock();
}

static void set_connected(int c)
{
    lock();
    D.st.connected = c;
    unlock();
}

/* ------------------------------------------------------------------ the thread */
static void run(void)
{
    pipe_t h = PIPE_NONE;
    int ready = 0;
    uint32_t nonce = 0;
    uint64_t next_try = 0, hs_deadline = 0, next_act = 0;
    static char body[FRAME_MAX + 1];
    while (!D.stop) {
        uint64_t now = now_ms();
        if (h == PIPE_NONE && now >= next_try) {
            next_try = now + (uint64_t)D.retry_ms;
            for (int n = 0; n < 10 && h == PIPE_NONE; n++) h = pipe_open(n);
            if (h != PIPE_NONE) {
                char hs[96];
                int k = snprintf(hs, sizeof hs, "{\"v\":1,\"client_id\":\"%s\"}", D.client_id);
                bump(&D.st.connects);
                ready = 0;
                hs_deadline = now + 5000;
                if (send_frame(h, OP_HANDSHAKE, hs, (uint32_t)k)) {
                    pipe_close(h);
                    h = PIPE_NONE;
                }
            }
        }
        int drop = 0, refused = 0;   /* refused: Discord closed us (a bad application ID: retry rarely) */
        while (h != PIPE_NONE && !drop) {
            int64_t a = pipe_avail(h);
            if (a < 0) { drop = 1; break; }
            if (a < 8) break;
            uint8_t hdr[8];
            if (pipe_read(h, hdr, 8)) { drop = 1; break; }
            uint32_t op = hdr[0] | hdr[1] << 8 | hdr[2] << 16 | (uint32_t)hdr[3] << 24;
            uint32_t len = hdr[4] | hdr[5] << 8 | hdr[6] << 16 | (uint32_t)hdr[7] << 24;
            if (len > FRAME_MAX || pipe_read(h, body, len)) { drop = 1; break; }
            body[len] = 0;
            if (op == OP_PING) {
                if (send_frame(h, OP_PONG, body, len)) drop = 1;
                else bump(&D.st.pongs);
            } else if (op == OP_CLOSE) {
                drop = 1;
                refused = !ready;
            } else if (op == OP_FRAME) {
                if (strstr(body, "\"evt\":\"READY\"")) {
                    ready = 1;
                    set_connected(1);
                    lock();
                    D.dirty = 1;   /* (re)send the activity on every new connection */
                    unlock();
                } else if (strstr(body, "\"evt\":\"ERROR\"")) {
                    bump(&D.st.errors);
                }
            }
        }
        if (h != PIPE_NONE && !ready && now_ms() > hs_deadline) drop = 1;
        if (h != PIPE_NONE && !drop && ready) {
            lock();
            int dirty = D.dirty;
            unlock();
            if (dirty && now_ms() >= next_act) {
                if (send_activity(h, ++nonce)) drop = 1;
                else {
                    bump(&D.st.activities);
                    next_act = now_ms() + (uint64_t)D.activity_ms;
                }
            }
        }
        if (drop) {
            pipe_close(h);
            h = PIPE_NONE;
            ready = 0;
            set_connected(0);
            bump(&D.st.errors);
            next_try = now_ms() + (uint64_t)D.retry_ms * (refused ? 15u : 1u);
        }
        /* sleep until woken (new text, stop) or the next thing to do; a connected pipe is
         * polled twice a second for PINGs */
        int64_t until = h != PIPE_NONE ? 500 : (int64_t)(next_try - now_ms());
        if (h != PIPE_NONE && ready) {
            lock();
            int dirty = D.dirty;
            unlock();
            if (dirty && next_act > now_ms() && (int64_t)(next_act - now_ms()) < until) until = (int64_t)(next_act - now_ms());
        }
        if (until > 500) until = 500;
        if (until > 0) wait_ms((int)until);
    }
    if (h != PIPE_NONE) pipe_close(h);   /* Discord clears our activity */
    set_connected(0);
}

#ifdef _WIN32
static DWORD WINAPI thread_main(LPVOID p)
{
    (void)p;
    run();
    return 0;
}
#else
static void *thread_main(void *p)
{
    (void)p;
    run();
    return NULL;
}
#endif

/* ------------------------------------------------------------------ API */
void rg_discord_test_config(const char *prefix, int retry_ms, int activity_ms)
{
    if (prefix) snprintf(D.prefix, sizeof D.prefix, "%s", prefix);
    if (retry_ms > 0) D.retry_ms = retry_ms;
    if (activity_ms > 0) D.activity_ms = activity_ms;
}

int rg_discord_start(const char *client_id)
{
    if (D.started) return 0;
    if (!rg_discord_valid_id(client_id)) return 1;
    snprintf(D.client_id, sizeof D.client_id, "%s", client_id);
    if (!D.prefix[0]) {
        const char *e = getenv("RG_DISCORD_IPC");
        snprintf(D.prefix, sizeof D.prefix, "%s", e && *e ? e : "discord-ipc-");
    }
    if (D.retry_ms <= 0) D.retry_ms = 20000;
    if (D.activity_ms <= 0) D.activity_ms = 15000;
    D.start_unix = (int64_t)time(NULL);
    D.stop = 0;
    D.dirty = 1;
    memset(&D.st, 0, sizeof D.st);
#ifdef _WIN32
    InitializeCriticalSection(&D.lock);
    D.wake = CreateEventW(NULL, FALSE, FALSE, NULL);
    D.thread = D.wake ? CreateThread(NULL, 64 * 1024, thread_main, NULL, STACK_SIZE_PARAM_IS_A_RESERVATION, NULL) : NULL;
    if (!D.thread) {
        if (D.wake) CloseHandle(D.wake);
        DeleteCriticalSection(&D.lock);
        return 1;
    }
    SetThreadPriority(D.thread, THREAD_PRIORITY_BELOW_NORMAL);
#else
    pthread_mutex_init(&D.lock, NULL);
    pthread_cond_init(&D.cond, NULL);
    pthread_attr_t at;
    pthread_attr_init(&at);
    pthread_attr_setstacksize(&at, 128 * 1024);
    int rc = pthread_create(&D.thread, &at, thread_main, NULL);
    pthread_attr_destroy(&at);
    if (rc) return 1;
#endif
    D.started = 1;
    D.st.running = 1;
    return 0;
}

void rg_discord_set_activity(const char *details, const char *state)
{
    if (!D.started) {   /* before start: just remember it (one thread then) */
        snprintf(D.details, sizeof D.details, "%s", details ? details : "");
        snprintf(D.state, sizeof D.state, "%s", state ? state : "");
        return;
    }
    lock();
    char d[TEXT_MAX], s[TEXT_MAX];
    snprintf(d, sizeof d, "%s", details ? details : "");
    snprintf(s, sizeof s, "%s", state ? state : "");
    if (strcmp(d, D.details) || strcmp(s, D.state)) {
        memcpy(D.details, d, sizeof d);
        memcpy(D.state, s, sizeof s);
        D.dirty = 1;
    }
    unlock();
    wake();
}

void rg_discord_stop(void)
{
    if (!D.started) return;
    D.stop = 1;
    wake();
#ifdef _WIN32
    int gone = WaitForSingleObject(D.thread, 1000) == WAIT_OBJECT_0;
    if (!gone) {
        CancelSynchronousIo(D.thread);   /* a write into a pipe nobody reads */
        gone = WaitForSingleObject(D.thread, 1000) == WAIT_OBJECT_0;
    }
    CloseHandle(D.thread);
    if (gone) {   /* else the thread still holds them: leak rather than free under it */
        CloseHandle(D.wake);
        DeleteCriticalSection(&D.lock);
    }
#else
    pthread_join(D.thread, NULL);
#endif
    D.started = 0;
    D.st.running = 0;
    D.st.connected = 0;
}

void rg_discord_get_stats(rg_discord_stats *out)
{
    if (!D.started) {
        *out = D.st;
        return;
    }
    lock();
    *out = D.st;
    unlock();
}
