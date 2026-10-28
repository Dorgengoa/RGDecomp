/* rgp:protos */
#define RGP_SELF_FieldViewModeEnter_2f35e0 1
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
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 FieldViewModeEnter_2f35e0(void)
{
    s32 r0;
    s32 r1;
    s32 rv3;
    s32 r2;
    s32 r4;
    s32 rv12;
    s32 r5;
    s32 rv11;
    s32 r6;
    s32 r7;
    s32 r8;
    s32 r9;
    s32 r10;

    r0 = ((s32)SysGetModeMsg_1c39b0());
    r1 = FieldViewModeGet_2f35a0();
    rv3 = 0;
    if (r1 != 0) {
        r2 = FieldViewModeReset_2f3510();
        rv3 = r2;
    }
    r4 = FieldViewModeGet_2f35a0();
    rv12 = r4;
    if (r4 == 0) {
        r5 = ((unsigned char)FieldViewModeIsEntered_2f36e0());
        rv11 = r5;
        if (r5 == 0) {
            r6 = ((s32)GetNpcObjTable_312860());
            r7 = (NpcObjTableRestoreFlags_2fb2b0(r6), (s32)0);
            r8 = (FieldViewModeSetEntered_2f36d0(1), (s32)0);
            r9 = ((s32)GetInsectCageMgr_1fdb30());
            r10 = (InsectCageMgrSetEnabled_39b180(r9, 1), (s32)0);
            rv11 = r10;
        }
        rv12 = rv11;
    }
    return rv12;
}
