/* SPDX-License-Identifier: CC0-1.0 */
/* rg_net: sockets, message framing and the lock-step pad stream (rg_net.h). */
#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
typedef SOCKET rg_os_sock;
#define RG_BADSOCK INVALID_SOCKET
#define rg_sock_close closesocket
#define rg_sock_err() WSAGetLastError()
#define RG_EWOULDBLOCK WSAEWOULDBLOCK
#define RG_EINPROGRESS WSAEWOULDBLOCK
#else
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <ifaddrs.h>
#include <net/if.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <poll.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>
typedef int rg_os_sock;
#define RG_BADSOCK (-1)
#define rg_sock_close close
#define rg_sock_err() errno
#define RG_EWOULDBLOCK EWOULDBLOCK
#define RG_EINPROGRESS EINPROGRESS
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rg_net.h"

/* ------------------------------------------------------------------ helpers */
uint64_t rg_net_fnv64(uint64_t h, const void *p, size_t n)
{
    const uint8_t *b = (const uint8_t *)p;
    if (!h) h = 0xcbf29ce484222325ull;
    for (size_t i = 0; i < n; i++) {
        h ^= b[i];
        h *= 0x100000001b3ull;
    }
    return h;
}

void rg_net_sleep_ms(int ms)
{
#ifdef _WIN32
    Sleep((DWORD)(ms < 0 ? 0 : ms));
#else
    struct timespec ts = {ms / 1000, (long)(ms % 1000) * 1000000L};
    nanosleep(&ts, NULL);
#endif
}

uint64_t rg_net_now_ms(void)
{
#ifdef _WIN32
    return (uint64_t)GetTickCount64();
#else
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint64_t)ts.tv_sec * 1000u + (uint64_t)ts.tv_nsec / 1000000u;
#endif
}

static void seterr(char *err, size_t cap, const char *fmt, const char *a, long b)
{
    if (err && cap) snprintf(err, cap, fmt, a, b);
}

static void put32(uint8_t *p, uint32_t v) { p[0] = (uint8_t)v; p[1] = (uint8_t)(v >> 8); p[2] = (uint8_t)(v >> 16); p[3] = (uint8_t)(v >> 24); }
static void put64(uint8_t *p, uint64_t v) { put32(p, (uint32_t)v); put32(p + 4, (uint32_t)(v >> 32)); }
static uint32_t get32(const uint8_t *p) { return p[0] | (uint32_t)p[1] << 8 | (uint32_t)p[2] << 16 | (uint32_t)p[3] << 24; }
static uint64_t get64(const uint8_t *p) { return get32(p) | (uint64_t)get32(p + 4) << 32; }

/* ------------------------------------------------------------------ sockets */
#define RG_RX_CAP (RG_NET_MAX_BODY + 64u * 1024u)

struct rg_net_sock {
    rg_os_sock fd;
    int listener;
    uint8_t *rx;
    size_t rx_n;
    uint8_t *tx;
    size_t tx_n, tx_cap;
};

int rg_net_sock_init(void)
{
#ifdef _WIN32
    static int done;
    if (!done) {
        WSADATA wd;
        if (WSAStartup(MAKEWORD(2, 2), &wd) != 0) return -1;
        done = 1;
    }
#endif
    return 0;
}

static int set_nonblock(rg_os_sock fd)
{
#ifdef _WIN32
    u_long one = 1;
    return ioctlsocket(fd, FIONBIO, &one) == 0 ? 0 : -1;
#else
    int f = fcntl(fd, F_GETFL, 0);
    return f >= 0 && fcntl(fd, F_SETFL, f | O_NONBLOCK) == 0 ? 0 : -1;
#endif
}

static void no_inherit(rg_os_sock fd)
{
#ifdef _WIN32
    SetHandleInformation((HANDLE)fd, HANDLE_FLAG_INHERIT, 0);
#else
    fcntl(fd, F_SETFD, FD_CLOEXEC);
#endif
}

static rg_net_sock *wrap(rg_os_sock fd, int listener)
{
    rg_net_sock *s = (rg_net_sock *)calloc(1, sizeof *s);
    if (!s) {
        rg_sock_close(fd);
        return NULL;
    }
    s->fd = fd;
    s->listener = listener;
    if (!listener) {
        int one = 1;
        setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, (const char *)&one, sizeof one);
        s->rx = (uint8_t *)malloc(RG_RX_CAP);
        if (!s->rx) {
            rg_sock_close(fd);
            free(s);
            return NULL;
        }
    }
    return s;
}

rg_net_sock *rg_net_sock_listen(int port, char *err, size_t cap)
{
    if (rg_net_sock_init()) {
        seterr(err, cap, "%sWSAStartup failed", "", 0);
        return NULL;
    }
    if (port <= 0 || port > 65535) {
        seterr(err, cap, "%sbad port %ld", "", port);
        return NULL;
    }
    /* dual-stack IPv6 socket first (accepts IPv4 too), plain IPv4 as the fallback */
    rg_os_sock fd = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);
    int ok = 0;
    if (fd != RG_BADSOCK) {
        int zero = 0, one = 1;
        setsockopt(fd, IPPROTO_IPV6, IPV6_V6ONLY, (const char *)&zero, sizeof zero);
#ifndef _WIN32
        setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (const char *)&one, sizeof one);
#else
        (void)one;
#endif
        struct sockaddr_in6 a;
        memset(&a, 0, sizeof a);
        a.sin6_family = AF_INET6;
        a.sin6_addr = in6addr_any;
        a.sin6_port = htons((unsigned short)port);
        ok = bind(fd, (struct sockaddr *)&a, sizeof a) == 0 && listen(fd, 1) == 0;
        if (!ok) rg_sock_close(fd);
    }
    if (!ok) {
        fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (fd == RG_BADSOCK) {
            seterr(err, cap, "%ssocket() failed (%ld)", "", (long)rg_sock_err());
            return NULL;
        }
#ifndef _WIN32
        int one = 1;
        setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (const char *)&one, sizeof one);
#endif
        struct sockaddr_in a;
        memset(&a, 0, sizeof a);
        a.sin_family = AF_INET;
        a.sin_addr.s_addr = htonl(INADDR_ANY);
        a.sin_port = htons((unsigned short)port);
        if (bind(fd, (struct sockaddr *)&a, sizeof a) != 0 || listen(fd, 1) != 0) {
            seterr(err, cap, "%scannot listen on port %ld (in use?)", "", port);
            rg_sock_close(fd);
            return NULL;
        }
    }
    no_inherit(fd);
    set_nonblock(fd);
    return wrap(fd, 1);
}

static int wait_fd(rg_os_sock fd, int for_write, int timeout_ms)
{
#ifdef _WIN32
    fd_set rs, ws, es;
    FD_ZERO(&rs);
    FD_ZERO(&ws);
    FD_ZERO(&es);
    if (for_write) {
        FD_SET(fd, &ws);
        FD_SET(fd, &es);
    } else
        FD_SET(fd, &rs);
    struct timeval tv = {timeout_ms / 1000, (timeout_ms % 1000) * 1000};
    int r = select(0, &rs, &ws, &es, &tv);
    if (r > 0 && for_write && FD_ISSET(fd, &es)) return -1;
    return r;
#else
    struct pollfd p = {fd, (short)(for_write ? POLLOUT : POLLIN), 0};
    int r = poll(&p, 1, timeout_ms);
    if (r > 0 && (p.revents & (POLLERR | POLLNVAL)) && for_write) return -1;
    return r;
#endif
}

rg_net_sock *rg_net_sock_accept(rg_net_sock *l, int timeout_ms, char *err, size_t cap)
{
    if (err && cap) err[0] = 0;
    if (!l || !l->listener) {
        seterr(err, cap, "%snot a listener", "", 0);
        return NULL;
    }
    if (timeout_ms > 0 && wait_fd(l->fd, 0, timeout_ms) <= 0) return NULL;
    rg_os_sock fd = accept(l->fd, NULL, NULL);
    if (fd == RG_BADSOCK) return NULL;
    no_inherit(fd);
    set_nonblock(fd);
    return wrap(fd, 0);
}

rg_net_sock *rg_net_sock_connect(const char *host, int port, int timeout_ms, char *err, size_t cap)
{
    if (rg_net_sock_init()) {
        seterr(err, cap, "%sWSAStartup failed", "", 0);
        return NULL;
    }
    char ps[16];
    snprintf(ps, sizeof ps, "%d", port);
    struct addrinfo hints, *res = NULL;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    if (getaddrinfo(host, ps, &hints, &res) != 0 || !res) {
        seterr(err, cap, "cannot find the address %s", host, 0);
        return NULL;
    }
    uint64_t t0 = rg_net_now_ms();
    for (struct addrinfo *ai = res; ai; ai = ai->ai_next) {
        rg_os_sock fd = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
        if (fd == RG_BADSOCK) continue;
        no_inherit(fd);
        set_nonblock(fd);
        int r = connect(fd, ai->ai_addr, (int)ai->ai_addrlen);
        if (r != 0) {
            int e = rg_sock_err();
#ifdef _WIN32
            int pending = e == WSAEWOULDBLOCK || e == WSAEINPROGRESS;
#else
            int pending = e == EINPROGRESS;
#endif
            int left = timeout_ms - (int)(rg_net_now_ms() - t0);
            if (!pending || left <= 0 || wait_fd(fd, 1, left) <= 0) {
                rg_sock_close(fd);
                continue;
            }
            int soerr = 0;
            socklen_t sl = sizeof soerr;
            getsockopt(fd, SOL_SOCKET, SO_ERROR, (char *)&soerr, &sl);
            if (soerr) {
                rg_sock_close(fd);
                continue;
            }
        }
        freeaddrinfo(res);
        return wrap(fd, 0);
    }
    freeaddrinfo(res);
    seterr(err, cap, "no answer from %s port %ld", host, port);
    return NULL;
}

struct rg_net_connecting {
    struct addrinfo *res, *cur;
    rg_os_sock fd;
    uint64_t t0;
    char host[256];
    int port;
};

static int conn_next(rg_net_connecting *c)
{
    while (c->cur) {
        struct addrinfo *ai = c->cur;
        c->cur = ai->ai_next;
        rg_os_sock fd = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
        if (fd == RG_BADSOCK) continue;
        no_inherit(fd);
        set_nonblock(fd);
        int r = connect(fd, ai->ai_addr, (int)ai->ai_addrlen);
        if (r != 0) {
            int e = rg_sock_err();
#ifdef _WIN32
            int pending = e == WSAEWOULDBLOCK || e == WSAEINPROGRESS;
#else
            int pending = e == EINPROGRESS;
#endif
            if (!pending) {
                rg_sock_close(fd);
                continue;
            }
        }
        c->fd = fd;
        c->t0 = rg_net_now_ms();
        return 0;
    }
    return -1;
}

rg_net_connecting *rg_net_connect_begin(const char *host, int port, char *err, size_t cap)
{
    if (rg_net_sock_init()) {
        seterr(err, cap, "%sWSAStartup failed", "", 0);
        return NULL;
    }
    rg_net_connecting *c = (rg_net_connecting *)calloc(1, sizeof *c);
    if (!c) return NULL;
    char ps[16];
    snprintf(ps, sizeof ps, "%d", port);
    snprintf(c->host, sizeof c->host, "%s", host);
    c->port = port;
    struct addrinfo hints;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    if (getaddrinfo(host, ps, &hints, &c->res) != 0 || !c->res) {
        seterr(err, cap, "cannot find the address %s", host, 0);
        free(c);
        return NULL;
    }
    c->cur = c->res;
    c->fd = RG_BADSOCK;
    if (conn_next(c)) {
        seterr(err, cap, "cannot call %s port %ld", host, port);
        rg_net_connect_cancel(c);
        return NULL;
    }
    return c;
}

int rg_net_connect_poll(rg_net_connecting *c, int timeout_ms, rg_net_sock **out, char *err, size_t cap)
{
    *out = NULL;
    if (!c) return -1;
    int w = wait_fd(c->fd, 1, timeout_ms < 0 ? 0 : timeout_ms);
    if (w > 0) {
        int soerr = 0;
        socklen_t sl = sizeof soerr;
        getsockopt(c->fd, SOL_SOCKET, SO_ERROR, (char *)&soerr, &sl);
        if (!soerr) {
            *out = wrap(c->fd, 0);
            c->fd = RG_BADSOCK;
            rg_net_connect_cancel(c);
            return *out ? 1 : -1;
        }
    }
    if (w < 0 || (w > 0) || rg_net_now_ms() - c->t0 > 4000) {
        /* refused, failed or no answer in 4 s: the next address, else give up */
        rg_sock_close(c->fd);
        c->fd = RG_BADSOCK;
        if (conn_next(c)) {
            seterr(err, cap, "no answer from %s port %ld", c->host, c->port);
            rg_net_connect_cancel(c);
            return -1;
        }
    }
    return 0;
}

void rg_net_connect_cancel(rg_net_connecting *c)
{
    if (!c) return;
    if (c->fd != RG_BADSOCK) rg_sock_close(c->fd);
    if (c->res) freeaddrinfo(c->res);
    free(c);
}

rg_net_sock *rg_net_sock_adopt(uint64_t handle)
{
    if (rg_net_sock_init()) return NULL;
    rg_os_sock fd = (rg_os_sock)handle;
    int type = 0;
    socklen_t sl = sizeof type;
    if (getsockopt(fd, SOL_SOCKET, SO_TYPE, (char *)&type, &sl) != 0 || type != SOCK_STREAM) return NULL;
    no_inherit(fd);
    set_nonblock(fd);
    return wrap(fd, 0);
}

uint64_t rg_net_sock_handle_for_child(rg_net_sock *s)
{
    if (!s) return 0;
#ifdef _WIN32
    if (!SetHandleInformation((HANDLE)s->fd, HANDLE_FLAG_INHERIT, HANDLE_FLAG_INHERIT)) return 0;
#else
    int f = fcntl(s->fd, F_GETFD, 0);
    if (f < 0 || fcntl(s->fd, F_SETFD, f & ~FD_CLOEXEC) != 0) return 0;
#endif
    return (uint64_t)s->fd;
}

void rg_net_sock_close(rg_net_sock *s)
{
    if (!s) return;
    if (s->fd != RG_BADSOCK) rg_sock_close(s->fd);
    free(s->rx);
    free(s->tx);
    free(s);
}

int rg_net_sock_send(rg_net_sock *s, const void *p, size_t n)
{
    if (!s || s->listener) return -1;
    if (s->tx_n + n > 16u * 1024u * 1024u) return -1;   /* a stuck peer: give up, never grow forever */
    if (s->tx_n + n > s->tx_cap) {
        size_t c = s->tx_cap ? s->tx_cap : 4096;
        while (c < s->tx_n + n) c *= 2;
        uint8_t *t = (uint8_t *)realloc(s->tx, c);
        if (!t) return -1;
        s->tx = t;
        s->tx_cap = c;
    }
    memcpy(s->tx + s->tx_n, p, n);
    s->tx_n += n;
    return 0;
}

int rg_net_sock_pump(rg_net_sock *s, int timeout_ms, char *err, size_t cap)
{
    if (!s || s->listener) return -1;
    for (int round = 0; round < 2; round++) {
        while (s->tx_n) {
            int w = (int)send(s->fd, (const char *)s->tx, (int)(s->tx_n > 65536 ? 65536 : s->tx_n), 0);
            if (w > 0) {
                memmove(s->tx, s->tx + w, s->tx_n - (size_t)w);
                s->tx_n -= (size_t)w;
                continue;
            }
            int e = rg_sock_err();
            if (w < 0 && (e == RG_EWOULDBLOCK
#ifndef _WIN32
                          || e == EAGAIN || e == EINTR
#endif
                          ))
                break;
            seterr(err, cap, "%sconnection lost (send %ld)", "", (long)e);
            return -1;
        }
        int got = 0;
        while (s->rx_n < RG_RX_CAP) {
            int r = (int)recv(s->fd, (char *)s->rx + s->rx_n, (int)(RG_RX_CAP - s->rx_n), 0);
            if (r > 0) {
                s->rx_n += (size_t)r;
                got = 1;
                continue;
            }
            if (r == 0) {
                seterr(err, cap, "%sthe other player closed the connection", "", 0);
                return -1;
            }
            int e = rg_sock_err();
            if (e == RG_EWOULDBLOCK
#ifndef _WIN32
                || e == EAGAIN || e == EINTR
#endif
            )
                break;
            seterr(err, cap, "%sconnection lost (recv %ld)", "", (long)e);
            return -1;
        }
        if (got || round || timeout_ms <= 0) break;
        if (wait_fd(s->fd, 0, timeout_ms) <= 0) break;
    }
    return 0;
}

const uint8_t *rg_net_sock_rx(rg_net_sock *s, size_t *n)
{
    *n = s ? s->rx_n : 0;
    return s ? s->rx : NULL;
}

int rg_net_sock_inject(rg_net_sock *s, const void *p, size_t n)
{
    if (!s || s->listener || n > RG_RX_CAP - s->rx_n) return -1;
    memmove(s->rx + n, s->rx, s->rx_n);
    memcpy(s->rx, p, n);
    s->rx_n += n;
    return 0;
}

void rg_net_sock_consume(rg_net_sock *s, size_t n)
{
    if (!s || n > s->rx_n) return;
    memmove(s->rx, s->rx + n, s->rx_n - n);
    s->rx_n -= n;
}

size_t rg_net_sock_tx_pending(const rg_net_sock *s) { return s ? s->tx_n : 0; }

int rg_net_local_addresses(char out[][48], int max)
{
    int n = 0;
    if (rg_net_sock_init()) return 0;
#ifdef _WIN32
    char name[256];
    if (gethostname(name, sizeof name) != 0) return 0;
    struct addrinfo hints, *res = NULL;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    if (getaddrinfo(name, NULL, &hints, &res) != 0) return 0;
    for (struct addrinfo *ai = res; ai && n < max; ai = ai->ai_next) {
        struct sockaddr_in *a = (struct sockaddr_in *)ai->ai_addr;
        char buf[48];
        if (!inet_ntop(AF_INET, &a->sin_addr, buf, sizeof buf)) continue;
        if (!strncmp(buf, "127.", 4) || !strncmp(buf, "169.254.", 8)) continue;
        int dup = 0;
        for (int i = 0; i < n; i++) dup |= !strcmp(out[i], buf);
        if (!dup) snprintf(out[n++], 48, "%s", buf);
    }
    freeaddrinfo(res);
#else
    struct ifaddrs *ifs = NULL;
    if (getifaddrs(&ifs) != 0) return 0;
    for (struct ifaddrs *i = ifs; i && n < max; i = i->ifa_next) {
        if (!i->ifa_addr || i->ifa_addr->sa_family != AF_INET || (i->ifa_flags & IFF_LOOPBACK)) continue;
        char buf[48];
        if (!inet_ntop(AF_INET, &((struct sockaddr_in *)i->ifa_addr)->sin_addr, buf, sizeof buf)) continue;
        if (!strncmp(buf, "169.254.", 8)) continue;
        snprintf(out[n++], 48, "%s", buf);
    }
    freeifaddrs(ifs);
#endif
    return n;
}

int rg_net_parse_address(const char *in, char *host, size_t cap, int *port)
{
    if (!in || !host || cap < 2 || !port) return -1;
    while (*in == ' ' || *in == '\t') in++;
    char tmp[300];
    size_t L = strlen(in);
    while (L && (in[L - 1] == ' ' || in[L - 1] == '\t' || in[L - 1] == '\r' || in[L - 1] == '\n')) L--;
    if (!L || L >= sizeof tmp) return -1;
    memcpy(tmp, in, L);
    tmp[L] = 0;
    *port = RG_NET_DEFAULT_PORT;
    char *h = tmp, *ps = NULL;
    if (tmp[0] == '[') {
        char *e = strchr(tmp, ']');
        if (!e) return -1;
        *e = 0;
        h = tmp + 1;
        if (e[1] == ':') ps = e + 2;
        else if (e[1]) return -1;
    } else {
        char *c = strchr(tmp, ':');
        if (c && !strchr(c + 1, ':')) {   /* one colon: host:port; more: a bare IPv6 address */
            *c = 0;
            ps = c + 1;
        }
    }
    if (ps) {
        char *e = NULL;
        long p = strtol(ps, &e, 10);
        if (!*ps || (e && *e) || p <= 0 || p > 65535) return -1;
        *port = (int)p;
    }
    if (!*h || strlen(h) >= cap) return -1;
    for (const char *c = h; *c; c++)
        if (!((*c >= '0' && *c <= '9') || (*c >= 'a' && *c <= 'z') || (*c >= 'A' && *c <= 'Z') || *c == '.' ||
              *c == '-' || *c == ':' || *c == '%' || *c == '_'))
            return -1;
    snprintf(host, cap, "%s", h);
    return 0;
}

/* ----------------------------------------------------------------- messages */
int rg_net_check_len(uint16_t type, uint32_t len, char *err, size_t cap)
{
    uint32_t want = 0xFFFFFFFFu, max = 0;
    switch (type) {
    case RG_MSG_HELLO: want = RG_NET_HELLO_BYTES; break;
    case RG_MSG_SETTINGS: max = 8192; break;
    case RG_MSG_SAVE: max = RG_NET_MAX_BODY; break;
    case RG_MSG_READY: want = 8; break;
    case RG_MSG_INPUT: want = RG_NET_INPUT_BYTES; break;
    case RG_MSG_HASH: want = RG_NET_HASH_BYTES; break;
    case RG_MSG_BYE: want = 4; break;
    case RG_MSG_PING: want = 0; break;
    default:
        seterr(err, cap, "%sunknown message type %ld", "", type);
        return -1;
    }
    if (want != 0xFFFFFFFFu ? len != want : len > max) {
        seterr(err, cap, "%sbad message length %ld", "", (long)len);
        return -1;
    }
    return 0;
}

int rg_net_send_msg(rg_net_sock *s, uint16_t type, const void *body, uint32_t len)
{
    uint8_t h[8];
    if (rg_net_check_len(type, len, NULL, 0)) return -1;
    h[0] = (uint8_t)type;
    h[1] = (uint8_t)(type >> 8);
    h[2] = h[3] = 0;
    put32(h + 4, len);
    if (rg_net_sock_send(s, h, 8)) return -1;
    return len ? rg_net_sock_send(s, body, len) : 0;
}

int rg_net_peek_msg(rg_net_sock *s, rg_net_msg *m, char *err, size_t cap)
{
    size_t n;
    const uint8_t *p = rg_net_sock_rx(s, &n);
    if (n < 8) return 0;
    uint16_t type = (uint16_t)(p[0] | p[1] << 8);
    uint32_t len = get32(p + 4);
    if (p[2] || p[3]) {
        seterr(err, cap, "%sbad message header", "", 0);
        return -1;
    }
    if (rg_net_check_len(type, len, err, cap)) return -1;
    if (n < 8u + len) return 0;
    m->type = type;
    m->len = len;
    m->body = p + 8;
    return 1;
}

void rg_net_msg_done(rg_net_sock *s, const rg_net_msg *m) { rg_net_sock_consume(s, 8u + m->len); }

void rg_net_hello_pack(const rg_net_hello *h, uint8_t o[RG_NET_HELLO_BYTES])
{
    memset(o, 0, RG_NET_HELLO_BYTES);
    memcpy(o, h->magic, 8);
    put32(o + 8, h->protocol);
    put32(o + 12, h->role);
    put64(o + 16, h->build);
    put64(o + 24, h->data);
    memcpy(o + 32, h->name, 16);
}

int rg_net_hello_unpack(const uint8_t in[RG_NET_HELLO_BYTES], rg_net_hello *h, char *err, size_t cap)
{
    memcpy(h->magic, in, 8);
    h->protocol = get32(in + 8);
    h->role = get32(in + 12);
    h->build = get64(in + 16);
    h->data = get64(in + 24);
    memcpy(h->name, in + 32, 16);
    if (memcmp(h->magic, "RGINSNET", 8)) {
        seterr(err, cap, "%snot a Rogue Galaxy port on the other end", "", 0);
        return -1;
    }
    if (h->role > 1) {
        seterr(err, cap, "%sbad role %ld", "", (long)h->role);
        return -1;
    }
    h->name[15] = 0;
    for (int i = 0; i < 15; i++)
        if (h->name[i] && (h->name[i] < 0x20 || h->name[i] > 0x7E)) h->name[i] = '?';
    return 0;
}

void rg_net_input_pack(const rg_net_input *in, uint8_t o[RG_NET_INPUT_BYTES])
{
    put32(o, in->first);
    put32(o + 4, in->last);
    o[8] = (uint8_t)in->buttons;
    o[9] = (uint8_t)(in->buttons >> 8);
    o[10] = in->lx;
    o[11] = in->ly;
    o[12] = in->rx;
    o[13] = in->ry;
}

int rg_net_input_unpack(const uint8_t in[RG_NET_INPUT_BYTES], rg_net_input *o, char *err, size_t cap)
{
    o->first = get32(in);
    o->last = get32(in + 4);
    o->buttons = (uint16_t)(in[8] | in[9] << 8);
    o->lx = in[10];
    o->ly = in[11];
    o->rx = in[12];
    o->ry = in[13];
    if (o->last < o->first || o->last - o->first >= RG_NET_MAX_SPAN) {
        seterr(err, cap, "%sbad input range (%ld fields)", "", (long)(o->last - o->first));
        return -1;
    }
    return 0;
}

void rg_net_hash_pack(const rg_net_hashmsg *h, uint8_t o[RG_NET_HASH_BYTES])
{
    put32(o, h->field);
    put64(o + 4, h->hash);
}

void rg_net_hash_unpack(const uint8_t in[RG_NET_HASH_BYTES], rg_net_hashmsg *h)
{
    h->field = get32(in);
    h->hash = get64(in + 4);
}

/* ---------------------------------------------------------------- lock-step */
void rg_net_stream_init(rg_net_stream *s, int64_t start)
{
    memset(s, 0, sizeof *s);
    s->horizon = start - 1;
    for (int i = 0; i < RG_NET_RING; i++) s->ring[i].lx = s->ring[i].ly = s->ring[i].rx = s->ring[i].ry = 0x80;
}

int rg_net_stream_add(rg_net_stream *s, uint32_t first, uint32_t last, const rg_net_pad *p, char *err, size_t cap)
{
    if ((int64_t)first != s->horizon + 1 || last < first || last - first >= RG_NET_MAX_SPAN) {
        seterr(err, cap, "%sinput out of order (field %ld)", "", (long)first);
        return -1;
    }
    for (uint64_t f = first; f <= last; f++) s->ring[f % RG_NET_RING] = *p;
    s->horizon = last;
    return 0;
}

int rg_net_stream_get(const rg_net_stream *s, uint32_t field, rg_net_pad *out)
{
    if ((int64_t)field > s->horizon) return 0;
    if (s->horizon - (int64_t)field >= RG_NET_RING) return -1;
    *out = s->ring[field % RG_NET_RING];
    return 1;
}
