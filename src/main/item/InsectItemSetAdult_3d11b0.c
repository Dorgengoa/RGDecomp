#include "types.h"
/* `sltu $3,$0,$5` then `sll $4,$3,1` then `and ~2`/`or`: bit 1 of the byte at
   0x28 is set to the truth value of the argument. */
typedef struct A3D11B0 {
    u8 pad000[0x28];
    u8 b0 : 1;
    u8 b1 : 1;
    u8 b2 : 6;
} A3D11B0;
typedef struct P3D11B0 { u8 pad000[0x18]; A3D11B0 *m18; } P3D11B0;
void InsectItemSetAdult_3d11b0(P3D11B0 *p, s32 v)
{
    A3D11B0 *q;

    q = p->m18;
    q->b1 = v != 0;
}
