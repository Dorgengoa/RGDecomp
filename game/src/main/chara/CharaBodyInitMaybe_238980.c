/* rgp:protos */
#define RGP_SELF_CharaBodyInitMaybe_238980 1
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
    u8 pad000[0xA0];
    s32 mA0;
    s32 mA4;
    s32 mA8;
    s32 mAC;
    s32 mB0;
    s32 mB4;
    s32 mB8;
    s32 mBC;
    s32 mC0;
    s32 mC4;
    s32 mC8;
    s32 mCC;
    s32 mD0;
    s32 mD4;
    s32 mD8;
    s32 mDC;
    s32 mE0;
    s32 mE4;
    s32 mE8;
    s32 mEC;
    s32 mF0;
    s32 mF4;
    s32 mF8;
    s32 mFC;
    s32 m100;
    s32 m104;
    s32 m108;
    s32 m10C;
    u8 pad110[0x2BC];
    s32 m3CC;
    s64 m3D0;
    s32 m3D8;
    s32 m3DC;
    s32 m3E0;
    s32 m3E4;
    s32 m3E8;
    s32 m3EC;
    s32 m3F0;
    s32 m3F4;
    s32 m3F8;
    s32 m3FC;
    s32 m400;
    s32 m404;
    s32 m408;
    s16 m40C;
    u8 pad40E[0x2];
    s16 m410;
    s16 m412;
    s32 m414;
};

void CharaBodyInitMaybe_238980(struct Obj0 *p0)
{
    SrtInit_1c72c0(p0);
    SrtInit_1c72c0((struct Obj0 *)((u8 *)p0 + 0x50));
    p0->mA0 = 0;
    p0->mA4 = 0;
    p0->mA8 = 0;
    p0->mAC = 0;
    p0->mB0 = 0;
    p0->mB4 = 0;
    p0->mB8 = 0;
    p0->mBC = 0;
    p0->mC0 = 0;
    p0->mC4 = 0;
    p0->mC8 = 0;
    p0->mCC = 0;
    p0->mD0 = 0;
    p0->mD4 = 0;
    p0->mD8 = 0;
    p0->mDC = 0;
    p0->mE0 = 0;
    p0->mE4 = 0;
    p0->mE8 = 0;
    p0->mEC = 0;
    p0->mF0 = 0;
    p0->mF4 = 0;
    p0->mF8 = 0;
    p0->mFC = 0;
    p0->m100 = 0;
    p0->m104 = 0;
    p0->m108 = 0;
    p0->m10C = 0;
    p0->m3DC = 0;
    p0->m3E0 = 0;
    p0->m3E4 = 0;
    p0->m3E8 = 0;
    p0->m3EC = 0;
    p0->m3F0 = 0;
    p0->m3D0 = 0;
    p0->m3D8 = 0;
    p0->m412 = 0;
    p0->m40C = 0;
    p0->m414 = 0x3F800000;
    p0->m410 = 0;
    p0->m3F4 = 0;
    p0->m3F8 = 0;
    p0->m3FC = 0;
    p0->m400 = 0;
    p0->m404 = 0;
    p0->m408 = 0;
    p0->m3CC = 0x80000000;
}
