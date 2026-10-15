#include "types.h"

extern void CharaJudgeObjRelease_213ca0(void *);

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
    u8 padA29[0xB];
    s16 mA34;
    s16 mA36;
    s16 mA38;
    u8 padA3A[0x92];
    s32 mACC;
    s32 mAD0;
    s32 mAD4;
};

void CharaBeginActionStateResetMaybe_216f10(struct Obj0 *p0)
{
    p0->mA34 = -1;
    p0->mA36 = 0;
    p0->mA38 = 1;
    p0->mA10 = 0x3F800000;
    p0->mA0C = 0;
    p0->mA20 = 0;
    p0->mA24 = 0;
    p0->mA28 = 0;
    p0->mA1C = 0;
    p0->mA14 = 0;
    p0->mA18 = 0;
    p0->mACC = 0;
    p0->mAD0 = 0;
    p0->mAD4 = 0;
    CharaJudgeObjRelease_213ca0(p0);
}
