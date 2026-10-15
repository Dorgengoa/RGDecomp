#include "types.h"

extern s32 FieldViewModeIsEntered_2f36e0(void);
extern s32 GetNpcObjTable_312860(void);
extern s32 NpcObjTableSetFlags_2fb2c0(s32, s32, s32);
extern s32 FieldViewModeSetEntered_2f36d0(s32);
extern s32 GetInsectCageMgr_1fdb30(void);
extern s32 InsectCageMgrSetEnabled_39b180(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 FieldViewModeLeave_2f3660(s32 p0, s32 p1)
{
    s32 r0;
    s32 rv6;
    s32 r1;
    s32 r2;
    s32 r3;
    s32 r4;
    s32 r5;

    r0 = FieldViewModeIsEntered_2f36e0();
    rv6 = r0;
    if (r0 != 0) {
        r1 = GetNpcObjTable_312860();
        r2 = NpcObjTableSetFlags_2fb2c0(r1, p0, p1);
        r3 = FieldViewModeSetEntered_2f36d0(0);
        r4 = GetInsectCageMgr_1fdb30();
        r5 = InsectCageMgrSetEnabled_39b180(r4, 0);
        rv6 = r5;
    }
    return rv6;
}
