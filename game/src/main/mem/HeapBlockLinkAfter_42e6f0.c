/* rgp:protos */
#define RGP_SELF_HeapBlockLinkAfter_42e6f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct NFUN_0042e6f0;
struct HFUN_0042e6f0;

struct NFUN_0042e6f0 { struct NFUN_0042e6f0 *f0; struct NFUN_0042e6f0 *f4; struct HFUN_0042e6f0 *f8; };
struct HFUN_0042e6f0 { struct NFUN_0042e6f0 *f0; struct NFUN_0042e6f0 *f4; u16 f8; u16 fA; };

s32 HeapBlockLinkAfter_42e6f0(struct HFUN_0042e6f0 *h, struct NFUN_0042e6f0 *b, struct NFUN_0042e6f0 *c)
{
    s32 ok;

    ok = (b != 0 && b->f8 == h);
    if (ok == 0) {
        return 0;
    }
    if (b == c) {
        return 0;
    }
    ok = (c != 0 && c->f8 == h);
    if (ok != 0) {
        if (h->f0 == c) {
            h->f0 = c->f4;
        }
        if (h->f4 == c) {
            h->f4 = c->f0;
        }
        if (c->f0 != 0) {
            c->f0->f4 = c->f4;
        }
        if (c->f4 != 0) {
            c->f4->f0 = c->f0;
        }
        c->f8 = 0;
        c->f0 = 0;
        c->f4 = 0;
        h->f8 = h->f8 - 1;
        h->fA = 1;
        while (h->fA < h->f8) {
            h->fA <<= 1;
        }
    }
    if (c != 0) {
        c->f8 = b->f8;
        c->f4 = b->f4;
        c->f0 = b;
        if (c->f4 != 0) {
            c->f4->f0 = c;
        }
    }
    b->f4 = c;
    if (h->f4 == b) {
        h->f4 = c;
    }
    h->f8 = h->f8 + 1;
    h->fA = 1;
    while (h->fA < h->f8) {
        h->fA <<= 1;
    }
    return 1;
}
