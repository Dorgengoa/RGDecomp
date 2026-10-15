#include "types.h"

extern s32 GetInsectCageMgr_1fdb30(void);
extern void InsectCageMgrSetEnabled_39b180(s32, s32);
extern void FieldViewModeEnter_2f35e0(void);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void FieldViewModeBegin_202f10(void)
{
    s32 r0;

    r0 = GetInsectCageMgr_1fdb30();
    InsectCageMgrSetEnabled_39b180(r0, 1);
    FieldViewModeEnter_2f35e0();
}
