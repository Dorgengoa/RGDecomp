#include "types.h"

extern s32 ScriptGetInt_26a2a0(s32);
extern s32 EventSceneGetObj_2676e0(s32);
extern void * ModelGetRootFrame_1511a0(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x4];
    s32 m04;
    u8 pad008[0x20];
    s8 m28;
};

s32 EvCmdObjDetachRootFrame_266dc0(s32 p0)
{
    s32 r0;
    s32 r1;
    s32 rv4;
    struct Obj0 *r2;
    s32 rv3;
    s8 t0;

    r0 = ScriptGetInt_26a2a0(p0);
    r1 = EventSceneGetObj_2676e0(r0);
    rv4 = rv3;
    if (r1 == 0) {
        rv4 = 0;
    } else {
        r2 = ModelGetRootFrame_1511a0(r1);
        rv3 = 1;
        if (r2 == 0) {
            rv3 = 0;
        } else {
            t0 = r2->m28;
            if (t0 != 0) {
                r2->m04 = 0;
            }
            rv3 = 1;
        }
        rv4 = rv3;
    }
    return rv4;
}
