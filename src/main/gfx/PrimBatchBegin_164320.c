#include "types.h"
#include "vec.h"
#pragma divbyzerocheck on

typedef union QW {
    u128 q;
    s32 w[4];
} QW;

typedef struct Pkt {
    u8 pad0[0xC];
    s32 xC;
    u8 pad10[0xF4 - 0x10];
    QW *F4;
    s32 F8;
    s32 FC;
    s32 x100;
    QW *x104;
    s32 *x108;
    s32 *x10C;
    QW *x110;
    QW *x114;
    QW *x118;
    QW *x11C;
} Pkt;

#pragma opt_propagation off
#pragma opt_common_subs off
void PrimBatchBegin_164320(Pkt *p, s32 arg1, s32 arg2) {
    s32 cnt;
    s32 n4;
    s32 n6;
    s32 n5;
    s32 one;
    s32 two;
    s32 k;
    s32 c;

    cnt = p->xC - 4;
    k = 13;
    cnt = cnt / k - 1;
    p->F8 = arg2;
    p->FC = arg1;
    p->x100 = 0;
    if (cnt < p->F8) {
        p->F8 = cnt;
    }
    one = 1;
    two = one + 1;
    n4 = (p->F8 + 1) * 2;
    n6 = n4 * two;
    n5 = n6 + n4;

    p->x104 = p->F4;
    p->F4->w[1] = 0;
    p->F4->w[2] = 0x01000101;
    p->F4->w[3] = 0x6C028000;
    c = 0x6C000000;
    p->F4[1].w[0] = p->FC;
    p->x108 = &p->F4[1].w[1];
    p->x10C = &p->F4[1].w[2];
    p->F4[1].w[3] = n4;
    p->F4[2].w[0] = n6;
    p->F4[2].w[1] = n5;
    p->F4[2].w[2] = 0;
    p->F4[2].w[3] = 0;
    { QW *q_ = p->F4; p->F4 = q_ + 3; q_[3].q = 0; }
    p->F4->w[3] = (p->F8 << 17) | (c | 0x8002);
    p->F4 += 1;
    p->x110 = p->F4;
    p->F4 += p->F8 * 2;
    p->F4->q = 0;
    { s32 t_ = ((n4 + 2) | 0x8000) | (p->F8 << 17); p->F4->w[3] = t_ | c; }
    p->F4 += 1;
    p->x114 = p->F4;
    p->F4 += p->F8 * 2;
    p->F4->q = 0;
    p->F4->w[3] = ((n6 + 2) | 0x8000) | (p->F8 << 17) | 0x64000000;
    p->F4 += 1;
    p->x118 = p->F4;
    p->F4 += p->F8;
    p->F4->q = 0;
    { s32 t_ = (p->F8 << 16) | ((n5 + 2) | 0x8000); p->F4->w[3] = t_ | c; }
    p->F4 += 1;
    p->x11C = p->F4;
    p->F4 += p->F8;
}
