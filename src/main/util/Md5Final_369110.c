#include "types.h"

typedef struct {
    u64 count[2];
    u64 state[4];
} CTX;

extern void Md5Update_369280(CTX *, u8 *, u64);
extern u8 D_00453DD0[];

void Md5Final_369110(CTX *c, u8 *d)
{
    u8 bits[8];
    u64 lo;
    u64 hi;
    u64 idx;
    u64 pad;

    hi = (c->count[0] >> 29) | (c->count[1] << 3);
    lo = c->count[0] << 3;
    bits[0] = lo;
    bits[1] = lo >> 8;
    bits[2] = lo >> 16;
    bits[3] = lo >> 24;
    bits[4] = hi;
    bits[5] = hi >> 8;
    bits[6] = hi >> 16;
    bits[7] = hi >> 24;
    idx = c->count[0] & 0x3F;
    pad = (idx < 56) ? (56 - idx) : (120 - idx);
    Md5Update_369280(c, D_00453DD0, pad);
    Md5Update_369280(c, bits, 8);
    d[0] = c->state[0];
    d[1] = c->state[0] >> 8;
    d[2] = c->state[0] >> 16;
    d[3] = c->state[0] >> 24;
    d[4] = c->state[1];
    d[5] = c->state[1] >> 8;
    d[6] = c->state[1] >> 16;
    d[7] = c->state[1] >> 24;
    d[8] = c->state[2];
    d[9] = c->state[2] >> 8;
    d[10] = c->state[2] >> 16;
    d[11] = c->state[2] >> 24;
    d[12] = c->state[3];
    d[13] = c->state[3] >> 8;
    d[14] = c->state[3] >> 16;
    d[15] = c->state[3] >> 24;
}
