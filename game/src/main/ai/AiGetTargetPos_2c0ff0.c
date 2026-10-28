/* rgp:protos */
#define RGP_SELF_AiGetTargetPos_2c0ff0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
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
    s32 m00;
    s32 m04;
    s32 m08;
    s32 m0C;
};

void AiGetTargetPos_2c0ff0(s32 p0, struct Obj0 *p1)
{
    s32 r0;
    s32 rv8;
    s32 r1;
    s32 r2;
    s32 r3;
    s32 r4;
    s32 rv7;
    s32 r5;
    s32 r6;

    p1->m00 = 0;
    p1->m04 = 0;
    p1->m08 = 0;
    p1->m0C = 0x3F800000;
    r0 = AiGetTargetMode_2c10b0(p0);
    rv8 = rv7;
    if (r0 == 1) {
        r1 = AiGetTargetPoint_2c0fe0(p0, p1);
        rv8 = r1;
    } else {
        r2 = GetCurrentScene_1f5be0();
        r3 = AiGetTargetCharaId_2c0fd0(p0);
        r4 = ((s32)ObjRecGetLiveObject_1c4a90(r2, r3));
        rv7 = r4;
        if (r4 != 0) {
            r5 = ModelGetRootFrame_1511a0(r4);
            r6 = (FrameGetWorldPos_148f30(r5, p1), (s32)0);
            rv7 = r6;
        }
        rv8 = rv7;
    }
}
