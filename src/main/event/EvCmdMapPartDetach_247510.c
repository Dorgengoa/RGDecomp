#include "types.h"

typedef struct Obj47510 {
    u8 pad34[0x34];
    s32 unk34;
    s32 unk38;
} Obj47510;

void MtxStore3x4_186390(Obj47510 *, void *);
Obj47510 *MapFindObjInAreaByName_1e4470(s32, s32, s32);
Obj47510 *MapFindObjInAreaById_1e44b0(s32, s32, s32);
s32 GetMapMgr_201a90(void);
s32 ScriptGetCodeAddr_249050(void *);
s32 ScriptGetInt_2490f0(void *);
void NodeCalcWorldMatrixThunk_186130(Obj47510 *, void *);

s32 EvCmdMapPartDetach_247510(s64 *p) {
    u8 sp30[0x40];
    s32 ctx;
    Obj47510 *o;
    s32 u;

    ctx = GetMapMgr_201a90();
    if (*(s32 *)p == 2) {
        u = ScriptGetCodeAddr_249050(p++ );
        o = MapFindObjInAreaByName_1e4470(ctx, u, ScriptGetCodeAddr_249050(p));
    } else if (*(s32 *)p == 0) {
        u = ScriptGetInt_2490f0(p++);
        o = MapFindObjInAreaById_1e44b0(ctx, u, ScriptGetCodeAddr_249050(p));
    } else {
        return 0;
    }
    if (o == NULL) {
        return 0;
    }
    NodeCalcWorldMatrixThunk_186130(o, sp30);
    o->unk34 = 0;
    o->unk38 = 0;
    MtxStore3x4_186390(o, sp30);
    return 1;
}
