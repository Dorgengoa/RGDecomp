/* rgp:protos */
#define RGP_SELF_CharaResetActionState_21ea00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x428];
    s32 m428;
    u8 pad42C[0x5E0];
    s32 mA0C;
    s32 mA10;
    s32 mA14;
    s32 mA18;
    s32 mA1C;
    s32 mA20;
    s32 mA24;
    u8 mA28;
    u8 padA29[0x9];
    s16 mA32;
    s16 mA34;
    s16 mA36;
    s16 mA38;
    u8 padA3A[0x2E];
    u8 mA68;
    u8 padA69[0x63];
    s32 mACC;
    s32 mAD0;
    s32 mAD4;
};

void CharaResetActionState_21ea00(struct Obj0 *p0)
{
    s32 r2;
    s16 t0;
    s32 t1;

    p0->mA34 = -1;
    p0->mA36 = 0;
    p0->mA38 = 0;
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
    CharaDropHeldTarget_211de0(p0, 0);
    p0->mA68 = 0;
    CharaClearActionEffects_214ce0(p0);
    r2 = ((short)CharaGetId_214a80(p0));
    t0 = p0->mA32;
    t1 = p0->m428;
    ActCfgTableRunNormalEvntsById_2224d0(t1, r2, t0);
}
