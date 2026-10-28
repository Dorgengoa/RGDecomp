/* rgp:protos */
#define RGP_SELF_GsZbufCopyBaseFmt_156ea0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct D {
    u8 pad0[0x30];
    __extension__ unsigned short a : 9;
    unsigned short a_hi : 7;
    u8 pad32;
    u8 b : 4;
    u8 b_hi : 4;
} __attribute__((aligned(2))) D;

typedef struct S {
    __extension__ unsigned short f0 : 9;
    unsigned short f0_hi : 7;
    u8 pad2;
    u8 f3 : 4;
    u8 f3_hi : 4;
} __attribute__((aligned(2))) S;

void GsZbufCopyBaseFmt_156ea0(D *d, S *s)
{
    u16 v;
    u8 w;

    v = s->f0;
    d->a = v;
    w = s->f3;
    d->b = w;
}
