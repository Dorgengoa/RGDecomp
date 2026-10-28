/* rgp:protos */
#define RGP_SELF_AbilityReqSet_27a450 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern void strcpy(void *, s32);
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_004D7C70;
extern s32 D_004D7C74;
extern s32 D_004D7C78;
extern u8 D_004D7C7C[];

struct Obj0;

struct Obj0 {
    u8 pad000[0x38];
    s32 m38;
};

s32 AbilityReqSet_27a450(s32 p0, s32 p1, s32 p2, s32 p3, s32 p4)
{
    s32 rv3;
    struct Obj0 *r2;
    s32 t0;

    rv3 = 1;
    if (p4 == 0) {
        rv3 = 0;
    } else {
        *(s32 *)&D_004D7C74 = p2;
        *(s32 *)&D_004D7C70 = p1;
        *(s32 *)&D_004D7C78 = p3;
        strcpy(D_004D7C7C, p4);
        GameReqQueuePushFront_1f5ab0(0xA, -1);
        r2 = GetActionMgr_1fdb50();
        t0 = r2->m38;
        r2->m38 = (t0 | 0x10000000);
        rv3 = 1;
    }
    return rv3;
}
