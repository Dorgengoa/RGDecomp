#include "types.h"

extern s32 GetMapSequencer_201a80(void);
extern s32 TaggedGetStr_1e9ff0(void *);
extern s32 MapSequencerFindOrAddMoverByAreaName_2fa260(s32, s32, s32);
extern s32 TaggedGetInt_1ea050(void *);
extern s32 MapSequencerFindOrAddMover_2fa2c0(s32, s32, s32);
extern s32 ScriptSlotStoreIntRef_1e9fd0(void *, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x8];
    s32 m08;
};

s32 MapScriptCmdGetNodeMover_1e9cd0(struct Obj0 *p0, s32 p1)
{
    s32 rv9;
    s32 r0;
    s32 t0;
    s32 rv7;
    s32 r1;
    s32 r2;
    s32 r3;
    s32 r4;
    s32 r5;
    s32 r6;
    s32 r8;

    rv9 = 1;
    if (p1 != 3) {
        rv9 = 0;
    } else {
        r0 = GetMapSequencer_201a80();
        t0 = p0->m08;
        rv7 = r6;
        if (t0 == 2) {
            r1 = TaggedGetStr_1e9ff0((struct Obj0 *)((u8 *)p0 + 8));
            r2 = TaggedGetStr_1e9ff0((struct Obj0 *)((u8 *)p0 + 0x10));
            r3 = MapSequencerFindOrAddMoverByAreaName_2fa260(r0, r1, r2);
            rv7 = r3;
        } else {
            r4 = TaggedGetInt_1ea050((struct Obj0 *)((u8 *)p0 + 8));
            r5 = TaggedGetStr_1e9ff0((struct Obj0 *)((u8 *)p0 + 0x10));
            r6 = MapSequencerFindOrAddMover_2fa2c0(r0, r4, r5);
            rv7 = r6;
        }
        r8 = ScriptSlotStoreIntRef_1e9fd0(p0, rv7);
        rv9 = 1;
    }
    return rv9;
}
