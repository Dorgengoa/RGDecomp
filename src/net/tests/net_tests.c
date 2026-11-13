/* SPDX-License-Identifier: CC0-1.0 */
/* rg_net unit tests (lane insnet): rg-net-tests NAME; exit 0 = pass. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rg_net.h"

static int fails;
#define CHECK(c)                                                       \
    do {                                                               \
        if (!(c)) {                                                    \
            fprintf(stderr, "FAIL %s:%d: %s\n", __FILE__, __LINE__, #c); \
            fails++;                                                   \
        }                                                              \
    } while (0)

static int t_frames(void)
{
    char err[128];
    CHECK(rg_net_check_len(RG_MSG_HELLO, RG_NET_HELLO_BYTES, err, sizeof err) == 0);
    CHECK(rg_net_check_len(RG_MSG_HELLO, RG_NET_HELLO_BYTES + 1, err, sizeof err) < 0);
    CHECK(rg_net_check_len(RG_MSG_INPUT, RG_NET_INPUT_BYTES, err, sizeof err) == 0);
    CHECK(rg_net_check_len(RG_MSG_INPUT, 0, err, sizeof err) < 0);
    CHECK(rg_net_check_len(RG_MSG_SAVE, RG_NET_MAX_BODY, err, sizeof err) == 0);
    CHECK(rg_net_check_len(RG_MSG_SAVE, RG_NET_MAX_BODY + 1, err, sizeof err) < 0);
    CHECK(rg_net_check_len(RG_MSG_SETTINGS, 8193, err, sizeof err) < 0);
    CHECK(rg_net_check_len(RG_MSG_PING, 0, err, sizeof err) == 0);
    CHECK(rg_net_check_len(RG_MSG_PING, 1, err, sizeof err) < 0);
    CHECK(rg_net_check_len(0, 0, err, sizeof err) < 0);
    CHECK(rg_net_check_len(RG_MSG_COUNT_, 0, err, sizeof err) < 0);
    CHECK(rg_net_check_len(0xFFFF, 4, err, sizeof err) < 0);

    rg_net_hello h, g;
    uint8_t b[RG_NET_HELLO_BYTES];
    memset(&h, 0, sizeof h);
    memcpy(h.magic, "RGINSNET", 8);
    h.protocol = RG_NET_PROTOCOL;
    h.role = 1;
    h.build = 0x0123456789ABCDEFull;
    h.data = 42;
    strcpy(h.name, "ALPHA\x01");
    rg_net_hello_pack(&h, b);
    CHECK(rg_net_hello_unpack(b, &g, err, sizeof err) == 0);
    CHECK(g.build == h.build && g.data == 42 && g.role == 1 && g.protocol == RG_NET_PROTOCOL);
    CHECK(!strcmp(g.name, "ALPHA?"));   /* control characters scrubbed */
    b[0] = 'X';
    CHECK(rg_net_hello_unpack(b, &g, err, sizeof err) < 0);
    rg_net_hello_pack(&h, b);
    b[12] = 7;   /* role 7 */
    CHECK(rg_net_hello_unpack(b, &g, err, sizeof err) < 0);

    rg_net_input in = {100, 104, 0xBEEF, 1, 2, 3, 4}, out;
    uint8_t ib[RG_NET_INPUT_BYTES];
    rg_net_input_pack(&in, ib);
    CHECK(rg_net_input_unpack(ib, &out, err, sizeof err) == 0);
    CHECK(out.first == 100 && out.last == 104 && out.buttons == 0xBEEF && out.ry == 4);
    in.last = 99;
    rg_net_input_pack(&in, ib);
    CHECK(rg_net_input_unpack(ib, &out, err, sizeof err) < 0);
    in.last = 100 + RG_NET_MAX_SPAN;
    rg_net_input_pack(&in, ib);
    CHECK(rg_net_input_unpack(ib, &out, err, sizeof err) < 0);

    rg_net_hashmsg hm = {12345, 0xFEEDFACECAFEBEEFull}, hm2;
    uint8_t hb[RG_NET_HASH_BYTES];
    rg_net_hash_pack(&hm, hb);
    rg_net_hash_unpack(hb, &hm2);
    CHECK(hm2.field == 12345 && hm2.hash == hm.hash);
    return fails;
}

static int t_stream(void)
{
    static rg_net_stream s;
    char err[128];
    rg_net_pad a = {1, 0x80, 0x80, 0x80, 0x80}, b = {2, 0, 0, 0, 0}, o;
    rg_net_stream_init(&s, 1000);
    CHECK(rg_net_stream_get(&s, 1000, &o) == 0);
    CHECK(rg_net_stream_add(&s, 1001, 1004, &a, err, sizeof err) < 0);   /* gap */
    CHECK(rg_net_stream_add(&s, 1000, 1004, &a, err, sizeof err) == 0);
    CHECK(rg_net_stream_get(&s, 1004, &o) == 1 && o.buttons == 1);
    CHECK(rg_net_stream_get(&s, 1005, &o) == 0);
    CHECK(rg_net_stream_add(&s, 1003, 1006, &b, err, sizeof err) < 0);   /* overlap */
    CHECK(rg_net_stream_add(&s, 1005, 1005 + RG_NET_MAX_SPAN, &b, err, sizeof err) < 0);
    CHECK(rg_net_stream_add(&s, 1005, 1006, &b, err, sizeof err) == 0);
    CHECK(rg_net_stream_get(&s, 1005, &o) == 1 && o.buttons == 2);
    CHECK(rg_net_stream_get(&s, 1002, &o) == 1 && o.buttons == 1);
    for (uint32_t f = 1007; f < 1007 + 3 * RG_NET_RING; f += 500)
        CHECK(rg_net_stream_add(&s, f, f + 499, &a, err, sizeof err) == 0);
    CHECK(rg_net_stream_get(&s, 1002, &o) == -1);   /* fell out of the ring */
    return fails;
}

static int t_address(void)
{
    char h[64];
    int p;
    CHECK(rg_net_parse_address("203.0.113.5:7491", h, sizeof h, &p) == 0 && !strcmp(h, "203.0.113.5") && p == 7491);
    CHECK(rg_net_parse_address(" 198.51.100.2 ", h, sizeof h, &p) == 0 && !strcmp(h, "198.51.100.2") && p == RG_NET_DEFAULT_PORT);
    CHECK(rg_net_parse_address("[::1]:80", h, sizeof h, &p) == 0 && !strcmp(h, "::1") && p == 80);
    CHECK(rg_net_parse_address("fe80::1", h, sizeof h, &p) == 0 && !strcmp(h, "fe80::1"));
    CHECK(rg_net_parse_address("my-pc.lan:7490", h, sizeof h, &p) == 0 && !strcmp(h, "my-pc.lan"));
    CHECK(rg_net_parse_address("host:0", h, sizeof h, &p) < 0);
    CHECK(rg_net_parse_address("host:70000", h, sizeof h, &p) < 0);
    CHECK(rg_net_parse_address("host:12x", h, sizeof h, &p) < 0);
    CHECK(rg_net_parse_address("", h, sizeof h, &p) < 0);
    CHECK(rg_net_parse_address("bad host", h, sizeof h, &p) < 0);
    CHECK(rg_net_parse_address("a;rm", h, sizeof h, &p) < 0);
    return fails;
}

/* two sockets on 127.0.0.1 in one process: a message each way, then a malformed frame */
static int t_loopback(void)
{
    char err[160];
    int base = 47000 + (int)(rg_net_now_ms() % 1000), port = 0;
    rg_net_sock *l = NULL;
    for (int k = 0; k < 20 && !l; k++) {
        port = base + k * 7;
        l = rg_net_sock_listen(port, err, sizeof err);
    }
    if (!l) {
        fprintf(stderr, "listen: %s\n", err);
        return 1;
    }
    rg_net_sock *c = rg_net_sock_connect("127.0.0.1", port, 3000, err, sizeof err);
    CHECK(c != NULL);
    if (!c) return fails;
    rg_net_sock *a = rg_net_sock_accept(l, 3000, err, sizeof err);
    CHECK(a != NULL);
    if (!a) return fails;
    rg_net_input in = {5, 9, 0x1234, 1, 2, 3, 4};
    uint8_t ib[RG_NET_INPUT_BYTES];
    rg_net_input_pack(&in, ib);
    CHECK(rg_net_send_msg(c, RG_MSG_INPUT, ib, sizeof ib) == 0);
    CHECK(rg_net_send_msg(c, RG_MSG_PING, NULL, 0) == 0);
    rg_net_msg m;
    int got = 0;
    for (int k = 0; k < 200 && got < 2; k++) {
        CHECK(rg_net_sock_pump(c, 0, err, sizeof err) == 0);
        CHECK(rg_net_sock_pump(a, 10, err, sizeof err) == 0);
        while (rg_net_peek_msg(a, &m, err, sizeof err) == 1) {
            if (got == 0) {
                rg_net_input o;
                CHECK(m.type == RG_MSG_INPUT && rg_net_input_unpack(m.body, &o, err, sizeof err) == 0 && o.buttons == 0x1234);
            } else
                CHECK(m.type == RG_MSG_PING);
            rg_net_msg_done(a, &m);
            got++;
        }
    }
    CHECK(got == 2);
    /* malformed: unknown type 0x7777 with a huge length -> protocol error, never a read */
    uint8_t bad[8] = {0x77, 0x77, 0, 0, 0xFF, 0xFF, 0xFF, 0x7F};
    CHECK(rg_net_sock_send(a, bad, 8) == 0);
    int perr = 0;
    for (int k = 0; k < 200 && !perr; k++) {
        rg_net_sock_pump(a, 0, err, sizeof err);
        rg_net_sock_pump(c, 10, err, sizeof err);
        perr = rg_net_peek_msg(c, &m, err, sizeof err) < 0;
    }
    CHECK(perr);
    /* a known type with the wrong length is refused too */
    rg_net_sock_close(c);
    c = rg_net_sock_connect("127.0.0.1", port, 3000, err, sizeof err);
    rg_net_sock *a2 = rg_net_sock_accept(l, 3000, err, sizeof err);
    CHECK(c && a2);
    if (c && a2) {
        uint8_t bad2[12] = {RG_MSG_HASH, 0, 0, 0, 4, 0, 0, 0, 1, 2, 3, 4};
        rg_net_sock_send(a2, bad2, sizeof bad2);
        perr = 0;
        for (int k = 0; k < 200 && !perr; k++) {
            rg_net_sock_pump(a2, 0, err, sizeof err);
            rg_net_sock_pump(c, 10, err, sizeof err);
            perr = rg_net_peek_msg(c, &m, err, sizeof err) < 0;
        }
        CHECK(perr);
        /* the peer closing is reported as a lost connection */
        rg_net_sock_close(a2);
        a2 = NULL;
        int lost = 0;
        for (int k = 0; k < 200 && !lost; k++) lost = rg_net_sock_pump(c, 10, err, sizeof err) < 0;
        CHECK(lost);
    }
    rg_net_sock_close(a2);
    rg_net_sock_close(c);
    rg_net_sock_close(a);
    /* the non-blocking connect of the menus: begin, poll until connected */
    {
        rg_net_connecting *cc = rg_net_connect_begin("127.0.0.1", port, err, sizeof err);
        CHECK(cc != NULL);
        rg_net_sock *got = NULL, *acc = NULL;
        int r = 0;
        for (int k = 0; k < 300 && r == 0; k++) {
            if (!acc) acc = rg_net_sock_accept(l, 0, err, sizeof err);
            r = rg_net_connect_poll(cc, 0, &got, err, sizeof err);
            if (r == 0) rg_net_sleep_ms(10);
        }
        if (r != 1) fprintf(stderr, "connect_poll: %d %s\n", r, err);
        CHECK(r == 1 && got != NULL);
        rg_net_sock_close(got);
        rg_net_sock_close(acc);
        /* nobody listening: the poll fails (refused) within a few seconds */
        rg_net_sock_close(l);
        l = NULL;
        cc = rg_net_connect_begin("127.0.0.1", port, err, sizeof err);
        r = 0;
        for (int k = 0; k < 800 && r == 0 && cc; k++) {
            r = rg_net_connect_poll(cc, 0, &got, err, sizeof err);
            if (r == 0) rg_net_sleep_ms(10);
        }
        CHECK(!cc || r == -1);
    }
    rg_net_sock_close(l);
    return fails;
}

int main(int argc, char **argv)
{
    if (argc < 2) return 2;
    int r = -1;
    if (!strcmp(argv[1], "frames")) r = t_frames();
    else if (!strcmp(argv[1], "stream")) r = t_stream();
    else if (!strcmp(argv[1], "address")) r = t_address();
    else if (!strcmp(argv[1], "loopback")) r = t_loopback();
    if (r < 0) {
        fprintf(stderr, "unknown test %s\n", argv[1]);
        return 2;
    }
    printf("%s: %s\n", argv[1], r ? "FAIL" : "PASS");
    return r ? 1 : 0;
}
