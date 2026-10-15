#include "types.h"

extern s32 GetCurEventPlayer_26b830(void);
extern s32 SysModeMsgIsKeyCapWarpStartMaybe_27bc40(void);
extern s32 GetMesMgr_277e90(void);
extern s32 MesMgrDrawAll_277a50(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void TaskDrawMessage_27a8b0(void)
{
    s32 r0;
    s32 rv2;
    s32 r1;
    s32 r3;
    s32 r4;

    r0 = GetCurEventPlayer_26b830();
    rv2 = 0;
    if (r0 != 0) {
        r1 = SysModeMsgIsKeyCapWarpStartMaybe_27bc40();
        if (r1 != 0) {
            return;
        }
        rv2 = r1;
    }
    r3 = GetMesMgr_277e90();
    r4 = MesMgrDrawAll_277a50(r3);
}
