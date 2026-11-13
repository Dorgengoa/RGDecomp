/* SPDX-License-Identifier: CC0-1.0 */
/* rg_net: the transport of the online Insectron 2-Player Battle (lane insnet 2026-11-12,
 * docs/INSECTRON-VERSUS.md "Online 2-Player Battle").
 *
 * Three layers, all plain C, no dependency beyond the OS socket API (Winsock / BSD):
 *   sockets     rg_net_sock_*: one TCP connection, non-blocking, TCP_NODELAY
 *   messages    rg_net_msg_*: framing (8-byte header + body), every type with an exact or
 *               bounded body size; anything else is a protocol error
 *   lock-step   rg_net_stream_*: one player's pad as a stream of "pad P for fields A..B"
 *               ranges with a horizon (pure, unit-tested)
 * The session layer (src/game/rg_insnet.c) builds on these.  Nothing here opens a socket
 * unless asked to: no listener, no lookup, no traffic in a normal run. */
#ifndef RG_NET_H
#define RG_NET_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------------------------------------ sockets */
#define RG_NET_DEFAULT_PORT 7490

typedef struct rg_net_sock rg_net_sock;

/* WSAStartup once (Windows); 0 ok */
int rg_net_sock_init(void);
/* listen on all IPv4 + IPv6 addresses of this machine (dual stack where available); NULL
 * and err filled on failure */
rg_net_sock *rg_net_sock_listen(int port, char *err, size_t cap);
/* accept one connection within timeout_ms (0 = poll); returns the connection or NULL
 * (err[0] = 0 when it simply timed out) */
rg_net_sock *rg_net_sock_accept(rg_net_sock *listener, int timeout_ms, char *err, size_t cap);
/* connect to host:port (name or address) within timeout_ms */
rg_net_sock *rg_net_sock_connect(const char *host, int port, int timeout_ms, char *err, size_t cap);
/* the same without blocking: begin (NULL + err on a bad address), then poll every frame:
 * 1 connected (*out = the connection), 0 still trying, -1 failed (err).  The begin object is
 * freed by the poll that returns 1 or -1, or by rg_net_connect_cancel. */
typedef struct rg_net_connecting rg_net_connecting;
rg_net_connecting *rg_net_connect_begin(const char *host, int port, char *err, size_t cap);
int rg_net_connect_poll(rg_net_connecting *c, int timeout_ms, rg_net_sock **out, char *err, size_t cap);
void rg_net_connect_cancel(rg_net_connecting *c);
/* adopt an inherited OS socket handle (relaunch hand-over); NULL if it is not a socket */
rg_net_sock *rg_net_sock_adopt(uint64_t handle);
/* the OS handle, made inheritable by a child process (relaunch); 0 on failure */
uint64_t rg_net_sock_handle_for_child(rg_net_sock *s);
void rg_net_sock_close(rg_net_sock *s);
/* queue bytes (never blocks; the queue is flushed by rg_net_sock_pump) */
int rg_net_sock_send(rg_net_sock *s, const void *p, size_t n);
/* move bytes both ways without blocking; wait up to timeout_ms for readability when there
 * is nothing to do.  Returns 0, or -1 when the connection is gone (err filled). */
int rg_net_sock_pump(rg_net_sock *s, int timeout_ms, char *err, size_t cap);
/* received bytes not consumed yet */
const uint8_t *rg_net_sock_rx(rg_net_sock *s, size_t *n);
void rg_net_sock_consume(rg_net_sock *s, size_t n);
/* put bytes in front of the receive buffer as if they had just arrived (the relaunch hand-over:
 * what the first process read past its last message); 0 ok, -1 too many */
int rg_net_sock_inject(rg_net_sock *s, const void *p, size_t n);
/* bytes still queued for sending */
size_t rg_net_sock_tx_pending(const rg_net_sock *s);
/* this machine's IPv4 addresses for the host screen ("a.b.c.d" each, at most max); count */
int rg_net_local_addresses(char out[][48], int max);
/* "host:port", "[v6]:port", "host" (default port) -> host, port; 0 ok */
int rg_net_parse_address(const char *in, char *host, size_t cap, int *port);

/* ----------------------------------------------------------------- messages */
#define RG_NET_PROTOCOL 1
#define RG_NET_MAX_BODY (256u * 1024u)

enum {
    RG_MSG_HELLO = 1,
    RG_MSG_SETTINGS = 2,
    RG_MSG_SAVE = 3,
    RG_MSG_READY = 4,
    RG_MSG_INPUT = 5,
    RG_MSG_HASH = 6,
    RG_MSG_BYE = 7,
    RG_MSG_PING = 8,
    RG_MSG_COUNT_
};

/* BYE reasons */
enum {
    RG_BYE_QUIT = 1,      /* the player left */
    RG_BYE_DONE = 2,      /* the session ended normally (match over, players left the mode) */
    RG_BYE_DESYNC = 3,    /* hashes differ */
    RG_BYE_MISMATCH = 4,  /* version / build / data / saves do not fit */
    RG_BYE_ERROR = 5,     /* protocol error or local failure */
};

typedef struct rg_net_hello {
    char magic[8];          /* "RGINSNET" */
    uint32_t protocol;      /* RG_NET_PROTOCOL */
    uint32_t role;          /* 0 host, 1 join */
    uint64_t build;         /* game build id (same game code => same id on every arch) */
    uint64_t data;          /* data fingerprint */
    char name[16];          /* player label, printable ASCII, NUL padded */
} rg_net_hello;

typedef struct rg_net_input {
    uint32_t first, last;   /* fields first..last (game VBlank counter values), last >= first */
    uint16_t buttons;
    uint8_t lx, ly, rx, ry;
} rg_net_input;

typedef struct rg_net_hashmsg {
    uint32_t field;
    uint64_t hash;
} rg_net_hashmsg;

typedef struct rg_net_msg {
    uint16_t type;
    uint32_t len;
    const uint8_t *body;    /* points into the receive buffer: valid until consumed */
} rg_net_msg;

/* append one message (header + body) to the socket's send queue */
int rg_net_send_msg(rg_net_sock *s, uint16_t type, const void *body, uint32_t len);
/* look at the next complete message: 1 = msg filled, 0 = incomplete, -1 = protocol error
 * (unknown type, body too long or of the wrong size for its type; err filled).  The caller
 * calls rg_net_msg_done(s, &msg) when it has used the body. */
int rg_net_peek_msg(rg_net_sock *s, rg_net_msg *msg, char *err, size_t cap);
void rg_net_msg_done(rg_net_sock *s, const rg_net_msg *msg);
/* pure: validate a header + body length pair (exposed for the tests); 0 ok */
int rg_net_check_len(uint16_t type, uint32_t len, char *err, size_t cap);

/* little-endian (de)serialisers of the fixed messages (pure) */
#define RG_NET_HELLO_BYTES 48
#define RG_NET_INPUT_BYTES 14
#define RG_NET_HASH_BYTES 12
void rg_net_hello_pack(const rg_net_hello *h, uint8_t out[RG_NET_HELLO_BYTES]);
int rg_net_hello_unpack(const uint8_t in[RG_NET_HELLO_BYTES], rg_net_hello *h, char *err, size_t cap);
void rg_net_input_pack(const rg_net_input *in, uint8_t out[RG_NET_INPUT_BYTES]);
int rg_net_input_unpack(const uint8_t in[RG_NET_INPUT_BYTES], rg_net_input *out, char *err, size_t cap);
void rg_net_hash_pack(const rg_net_hashmsg *h, uint8_t out[RG_NET_HASH_BYTES]);
void rg_net_hash_unpack(const uint8_t in[RG_NET_HASH_BYTES], rg_net_hashmsg *h);

/* ---------------------------------------------------------------- lock-step */
/* One player's published pad stream.  Values are known for fields <= horizon; a field's
 * value is the newest range that covers it.  Fields are kept in a ring of RG_NET_RING
 * entries, so a lookup may be at most RG_NET_RING - 1 fields behind the horizon. */
#define RG_NET_RING 2048
#define RG_NET_MAX_SPAN 600     /* one INPUT message covers at most this many fields */

typedef struct rg_net_pad {
    uint16_t buttons;
    uint8_t lx, ly, rx, ry;
} rg_net_pad;

typedef struct rg_net_stream {
    int64_t horizon;            /* last field with a known value; -1 = none */
    rg_net_pad ring[RG_NET_RING];
} rg_net_stream;

void rg_net_stream_init(rg_net_stream *s, int64_t start);   /* horizon = start - 1 */
/* add "pad for fields first..last": first must be horizon + 1, last - first < RG_NET_MAX_SPAN
 * (the peer's promise: contiguous, increasing).  0 ok, -1 invalid (err filled). */
int rg_net_stream_add(rg_net_stream *s, uint32_t first, uint32_t last, const rg_net_pad *p,
                      char *err, size_t cap);
/* 1 = value known (out filled), 0 = not yet (field > horizon), -1 = too old */
int rg_net_stream_get(const rg_net_stream *s, uint32_t field, rg_net_pad *out);

/* ------------------------------------------------------------ small helpers */
uint64_t rg_net_fnv64(uint64_t h, const void *p, size_t n);   /* FNV-1a; h = 0 starts */
void rg_net_sleep_ms(int ms);
uint64_t rg_net_now_ms(void);

#ifdef __cplusplus
}
#endif
#endif
