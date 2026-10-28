/* rgp:protos */
#define RGP_SELF_ModelObjInit_1ae420 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

typedef rg_u128 u128;

struct Obj0;

struct Obj0 {
    u8 pad000[0x200];
    s32 m200;
    s32 m204;
    s32 m208;
    s32 m20C;
    s32 m210;
    s32 m214;
    s32 m218;
    s32 m21C;
    s32 m220;
    s32 m224;
    u8 pad228[0x208];
    s32 m430;
    s32 m434;
    s32 m438;
    s32 m43C;
    s32 m440;
    s32 m444;
    s32 m448;
    s32 m44C;
    s32 m450;
    s32 m454;
    s32 m458;
    s32 m45C;
    s32 m460;
    s32 m464;
    u8 m468;
    u8 pad469[0xB];
    s32 m474;
    u8 pad478[0x8];
    u128 m480;
    u128 m490;
    u8 pad4A0[0x10];
    u8 m4B0;
    u8 pad4B1[0x17];
    s32 m4C8;
    s32 m4CC;
    s32 m4D0;
    u8 pad4D4[0x8];
    s32 m4DC;
};

void ModelObjInit_1ae420(struct Obj0 *p0)
{
    s32 r1;
    s32 l2;
    s32 l3;
    s32 l4;

    ModelObjBaseInit_1867b0(p0);
    p0->m480 = 0;
    r1 = (VecSetOnes_13e180((struct Obj0 *)((u8 *)p0 + 0x4A0)), (s32)0);
    p0->m490 = 0;
    p0->m4B0 = 0;
    p0->m448 = 0x3F800000;
    p0->m200 = 0;
    p0->m474 = 0;
    p0->m204 = 0;
    p0->m208 = 0;
    p0->m4D0 = 0;
    p0->m4CC = 0;
    p0->m4C8 = 0;
    p0->m4DC = -1;
    p0->m220 = 0;
    p0->m224 = 1;
    l2 = 1;
    l3 = 0;
    do {
        *(s32 *)((u8 *)p0 + (l3 << 3) + 0x22C) = -1;
        *(s32 *)((u8 *)p0 + (l3 << 3) + 0x228) = -1;
        *(s32 *)((u8 *)p0 + (l3 << 3) + 0x24C) = -1;
        *(s32 *)((u8 *)p0 + (l3 << 3) + 0x248) = -1;
        l2 = ((l3 + 1) < 4);
        l3 = (l3 + 1);
    } while (l2 != 0);
    p0->m210 = 0;
    p0->m20C = 0;
    l4 = 0;
    do {
        *(s32 *)((u8 *)p0 + (l4 << 2) + 0x46C) = -1;
        l4 = (l4 + 1);
    } while (l4 < 2);
    p0->m214 = 0;
    p0->m218 = 0;
    p0->m21C = 0;
    ModelInit_151d50((struct Obj0 *)((u8 *)p0 + 0x270));
    p0->m45C = 0;
    p0->m444 = 0;
    p0->m430 = 0;
    p0->m438 = 0;
    p0->m434 = 0;
    p0->m440 = 0;
    p0->m43C = 0;
    p0->m464 = 0;
    p0->m468 = 0;
    p0->m460 = 1;
    p0->m44C = 0;
    p0->m450 = 1;
    p0->m454 = 0;
    p0->m458 = 0x3F800000;
}
