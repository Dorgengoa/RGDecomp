#include "types.h"

extern s32 ScriptGetInt_26a2a0(s32);
extern s32 ObjRecSetFlag2_1c3e80(s32, s32, s32);
extern s32 ObjRecClearFlag2_1c3e40(s32, s32, s32);
extern s32 ObjRecGetLiveObject_1c4a90(s32, s32);
extern s32 ModelMotionEventReleaseHandlers_1b02b0(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00481F78;

s32 EvCmdObjRecSetFlag2All_260cf0(s32 p0, s32 p1)
{
    s32 r0;
    s32 l1;
    s32 l2;
    s32 rv8;
    s32 t0;
    s32 r3;
    s32 t1;
    s32 r4;
    s32 t2;
    s32 r5;
    s32 rv7;
    s32 r6;

    if (p1 != 1) {
        return 0;
    }
    r0 = ScriptGetInt_26a2a0(p0);
    l1 = r0;
    l2 = 0;
    do {
        if (r0 != 0) {
            t0 = D_00481F78;
            r3 = ObjRecSetFlag2_1c3e80(t0, 1, l2);
            rv8 = r3;
        } else {
            t1 = D_00481F78;
            r4 = ObjRecClearFlag2_1c3e40(t1, 1, l2);
            t2 = D_00481F78;
            r5 = ObjRecGetLiveObject_1c4a90(t2, l2);
            rv7 = 0;
            if (r5 != 0) {
                r6 = ModelMotionEventReleaseHandlers_1b02b0(r5);
                rv7 = r6;
            }
            rv8 = rv7;
        }
        l1 = ((l2 + 1) < 0xE0);
        l2 = (l2 + 1);
    } while (l1 != 0);
    return 1;
}
