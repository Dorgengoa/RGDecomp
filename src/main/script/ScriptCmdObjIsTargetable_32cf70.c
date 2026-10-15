#include "types.h"

extern s32 ScriptSlotGetInt_3348b0(s32);
extern s32 GetCurrentScene_1f5be0(void);
extern s32 ObjRecGetLiveObject_1c4a90(s32, s32);
extern s32 ObjIsTargetableById_32d010(s32);
extern s32 ScriptSlotStoreIntRef_3347f0(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 ScriptCmdObjIsTargetable_32cf70(s32 p0)
{
    s32 r0;
    s32 rv1;
    s32 r2;
    s32 r3;
    s32 rv4;
    s32 r5;
    s32 rv6;
    s32 r7;

    r0 = ScriptSlotGetInt_3348b0((p0 + 8));
    rv1 = 1;
    if (r0 == -1) {
        rv1 = 0;
    }
    r2 = GetCurrentScene_1f5be0();
    r3 = ObjRecGetLiveObject_1c4a90(r2, r0);
    rv4 = rv1;
    if (r3 == 0) {
        rv4 = 0;
    }
    r5 = ObjIsTargetableById_32d010(r0);
    rv6 = rv4;
    if (r5 == 0) {
        rv6 = 0;
    }
    r7 = ScriptSlotStoreIntRef_3347f0(p0, rv6);
    return 1;
}
