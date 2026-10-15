#include "vec.h"

/* Two tests branching the SAME way (both to the join) = `&&`.
   The operand cursor is only advanced AFTER the null check; the `n >= 4` probe
   reads the fourth operand cell directly at +0x18.

   The four gp defaults are written into `v` and three of them are then
   overwritten, and RETAIL KEEPS BOTH SETS.  MEASURED (7-arm sweep,
   build/zz/sw-q08-EvCmdCameraSetAt_2656f0): with plain member writes on both sides mwcc
   dead-store-eliminates the first three (6 words gone, 0xD0 vs 0xF4).  Writing
   EITHER side through a cast pointer stops it -- casting the gp side and
   casting the xyz side are ONE OBJECT (an inert pair) at 0xE8.  The remaining
   3 words are the third fetch: it has to be a NAMED local assigned BEFORE the
   default block, which buys the second callee-saved FPR ($f21/$f20) while the
   value itself stays in $f0. */

typedef struct Cmd { s32 a, b; } Cmd;

extern void *EventSceneGetCamera_265980(void);
extern s32 ScriptGetInt_26a2a0(s32);
extern f32 TaggedGetFloat_26a280(s32);
extern s32 GetCurrentScene_1f5be0(void);
extern void *ObjRecGetLiveObject_1c3bc0(s32, s32);

extern f32 D_0047E8E0, D_0047E8E4, D_0047E8E8, D_0047E8EC;

s32 EvCmdCameraSetAt_2656f0(Cmd *p0, s32 n)
{
    void *e;
    f32 x, y, z;
    Vec4 v;

    e = EventSceneGetCamera_265980();
    if (n >= 4 && ScriptGetInt_26a2a0((s32)p0 + 0x18) == 1) {
        e = ObjRecGetLiveObject_1c3bc0(GetCurrentScene_1f5be0(), 1);
    }
    if (e == 0) {
        return 0;
    }
    x = TaggedGetFloat_26a280((s32)p0++);
    y = TaggedGetFloat_26a280((s32)p0++);
    z = TaggedGetFloat_26a280((s32)p0);
    ((Vec4 *)&v)->x = D_0047E8E0;
    ((Vec4 *)&v)->y = D_0047E8E4;
    ((Vec4 *)&v)->z = D_0047E8E8;
    ((Vec4 *)&v)->w = D_0047E8EC;
    v.x = x;
    v.y = y;
    v.z = z;
    *(Vec4 *)((u8 *)e + 0xE0) = v;
    *(Vec4 *)((u8 *)e + 0x50) = v;
    return 1;
}
