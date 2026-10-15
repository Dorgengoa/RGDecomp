#include "types.h"

typedef struct E8 { s32 a; s32 b; } E8;

extern s32 ScriptSlotGetInt_2cc9c0(E8 *);
extern s32 ObjRecHasFlags6_1c3eb0(s32, s32, s32);
extern s32 ScriptSlotStoreIntRef_2cc900(E8 *, s32);

extern const s32 D_004DB920;

s32 AiCmdObjRecHasFlags6_2ca4c0(E8 *p0)
{
    s32 t0;
    s32 r0;
    s32 r1;
    s32 r2;

    t0 = *(volatile s32 *)&D_004DB920;
    r0 = ScriptSlotGetInt_2cc9c0(p0++);
    r1 = ObjRecHasFlags6_1c3eb0(t0, 1, r0);
    r2 = ScriptSlotStoreIntRef_2cc900(p0, r1);
    return 1;
}
