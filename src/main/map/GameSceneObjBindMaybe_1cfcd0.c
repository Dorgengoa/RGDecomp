#include "types.h"

extern s32 ObjRecTableBindSlot_1c4ae0(s32, s32, s32, s32);
extern s32 ParamTableGetRec_1cfbc0(s32, s32);
extern s32 ParamRecReset_1cfdb0(s32);
extern s32 ActionMgrAssignWeaponAllGlobal_1fb4b0(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 GameSceneObjBindMaybe_1cfcd0(s32 p0, s32 p1, s32 p2, s32 p3)
{
    s32 r0;
    s32 r1;
    s32 r2;
    s32 r3;

    r0 = ObjRecTableBindSlot_1c4ae0(p0, p1, p2, p3);
    r1 = ParamTableGetRec_1cfbc0(p0, r0);
    if (r1 != 0) {
        r2 = ParamRecReset_1cfdb0(r1);
    }
    r3 = ActionMgrAssignWeaponAllGlobal_1fb4b0(r0);
    return r0;
}
