/* rgp:protos */
#define RGP_SELF_CharaSetActionModeBattleInOut_21c190 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
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
    u8 pad000[0xA32];
    s16 mA32;
    u8 padA34[0x10];
    s32 mA44;
};

void CharaSetActionModeBattleInOut_21c190(struct Obj0 *p0)
{
    s32 r2;
    s32 t0;

    p0->mA32 = 0xA;
    CharaResetActionState_21ea00(p0);
    CharaMoveReqResetThunk_2194d0((struct Obj0 *)((u8 *)p0 + 0x930));
    r2 = (CharaSquashResetThunk_219300((struct Obj0 *)((u8 *)p0 + 0x950)), (s32)0);
    t0 = p0->mA44;
    p0->mA44 = (t0 & 0xFFFF7FFF);
    CharaStopLoopSe_213bf0(p0);
    CharaStopLoopFg_213b60(p0);
}
