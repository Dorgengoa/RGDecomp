/* rgp:protos */
#define RGP_SELF_MapDataInit_1e7c50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0xC];
    s32 m0C;
    s32 m10;
    s32 m14;
    s16 m18;
    s16 m1A;
    s16 m1C;
    s16 m1E;
    u8 m20;
    u8 m21;
    u8 pad022[0x1];
    u8 m23;
    u8 m24;
    u8 m25;
    s16 m26;
    s32 m28;
    s32 m2C;
    s32 m30;
    s32 m34;
    s32 m38;
    s32 m3C;
    s32 m40;
    s32 m44;
    s32 m48;
    s32 m4C;
    u8 m50;
    u8 m51;
    u8 m52;
    u8 m53;
};

void MapDataInit_1e7c50(struct Obj0 *p0)
{
    p0->m0C = 0;
    p0->m10 = 0;
    p0->m14 = 0;
    p0->m18 = -1;
    p0->m1A = -1;
    p0->m25 = 0;
    p0->m28 = 0;
    p0->m1E = -1;
    p0->m20 = 0;
    p0->m1C = -1;
    p0->m21 = 0;
    p0->m23 = 1;
    p0->m24 = 0;
    p0->m26 = -1;
    p0->m28 = 0;
    p0->m2C = 0;
    p0->m30 = 0;
    p0->m34 = 0;
    p0->m38 = 0;
    p0->m3C = 0;
    p0->m40 = 0;
    p0->m44 = 0;
    p0->m48 = 0;
    p0->m4C = 0;
    p0->m50 = 1;
    p0->m51 = 0x17;
    p0->m52 = 0x40;
    p0->m53 = 0xA6;
    MapDataClearLoadState_1e7c30(p0);
}
