/* rgp:protos */
#define RGP_SELF_EvCmdMapPartDetach_247510 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Obj47510 {
    u8 pad34[0x34];
    s32 unk34;
    s32 unk38;
} Obj47510;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdMapPartDetach_247510(s64 *p) {
    u8 sp30[0x40] __attribute__((aligned(16)));
    s32 ctx;
    Obj47510 *o;
    s32 u;

    ctx = ((s32)GetMapMgr_201a90());
    if (*(s32 *)p == 2) {
        u = ScriptGetCodeAddr_249050(p++ );
        o = ((Obj47510 *)MapFindObjInAreaByName_1e4470(ctx, u, ScriptGetCodeAddr_249050(p)));
    } else if (*(s32 *)p == 0) {
        u = ScriptGetInt_2490f0(p++);
        o = ((Obj47510 *)MapFindObjInAreaById_1e44b0(ctx, u, ScriptGetCodeAddr_249050(p)));
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
