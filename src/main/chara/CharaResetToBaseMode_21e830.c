#include "types.h"

extern void CharaDropHeldTarget_211de0(void *, s32, s32);
extern s32 GetCurrentScene_1f5be0(void);
extern s32 CharaGetId_214a80(void *);
extern void ObjRecClearFlags_1c3dc0(s32, s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0xA0C];
    s32 mA0C;
    s32 mA10;
    s32 mA14;
    s32 mA18;
    s32 mA1C;
    s32 mA20;
    s32 mA24;
    u8 mA28;
    u8 padA29[0x5];
    s16 mA2E;
    u8 padA30[0x2];
    s16 mA32;
    s16 mA34;
    s16 mA36;
    s16 mA38;
    u8 padA3A[0xA];
    s32 mA44;
    u8 padA48[0x84];
    s32 mACC;
    s32 mAD0;
    s32 mAD4;
    s32 mAD8;
};

void CharaResetToBaseMode_21e830(struct Obj0 *p0)
{
    s16 t0;
    s32 r1;
    s32 r2;
    s32 t1;

    t0 = p0->mA2E;
    p0->mA32 = t0;
    p0->mA34 = -1;
    p0->mA36 = 0;
    p0->mA10 = 0x3F800000;
    p0->mA0C = 0;
    p0->mA20 = 0;
    p0->mA24 = 0;
    p0->mA28 = 0;
    p0->mA1C = 0;
    p0->mA14 = 0;
    p0->mA18 = 0;
    p0->mA38 = 0;
    p0->mACC = 0;
    p0->mAD0 = 0;
    p0->mAD4 = 0;
    p0->mAD8 = 0;
    CharaDropHeldTarget_211de0(p0, 0, t0);
    r1 = GetCurrentScene_1f5be0();
    r2 = CharaGetId_214a80(p0);
    ObjRecClearFlags_1c3dc0(r1, 1, r2, 0xA0000);
    t1 = p0->mA44;
    p0->mA44 = (t1 & 0xFFFBFFFF);
}
