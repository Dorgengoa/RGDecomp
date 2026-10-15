#include "types.h"

extern s32 GetMapMgr_201a90(void);
extern s32 ScriptGetCodeAddr_249050(void *);
extern s32 MapSlotsFindBlockByName_1e4910(s32, s32, s32);
extern s32 ScriptGetInt_2490f0(void *);
extern s32 MapSlotsFindBlockById_1e49b0(s32, s32, s32);
extern s32 MapDataSetEnabled_1e7440(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s32 m00;
};

s32 EvCmdMapDataSetEnabled_2461e0(struct Obj0 *p0, s32 p1)
{
    s32 rv10;
    s32 r0;
    s32 t0;
    s32 rv5;
    s32 rv6;
    s32 r1;
    s32 r2;
    s32 r3;
    s32 r4;
    s32 rv9;
    s32 r7;
    s32 r8;

    if (p1 != 2) {
        rv10 = 0;
    } else {
        r0 = GetMapMgr_201a90();
        t0 = p0->m00;
        if (t0 == 2) {
            r1 = ScriptGetCodeAddr_249050(p0);
            r2 = MapSlotsFindBlockByName_1e4910(r0, r1, 0);
            rv5 = r2;
            rv6 = r2;
        } else {
            r3 = ScriptGetInt_2490f0(p0);
            r4 = MapSlotsFindBlockById_1e49b0(r0, r3, 0);
            rv5 = r4;
            rv6 = r4;
        }
        rv9 = 1;
        if (rv6 == 0) {
            rv9 = 0;
        } else {
            r7 = ScriptGetInt_2490f0((struct Obj0 *)((u8 *)p0 + 8));
            r8 = MapDataSetEnabled_1e7440(rv6, (r7 != 0));
            rv9 = 1;
        }
        rv10 = rv9;
    }
    return rv10;
}
