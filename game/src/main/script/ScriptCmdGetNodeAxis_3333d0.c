/* rgp:protos */
#define RGP_SELF_ScriptCmdGetNodeAxis_3333d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { s32 a; s32 b; } Arg;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

/* `> 2` not `>= 3`: the $at compare class.
   stack locals in REVERSE declaration order: q -> 0x90, m -> 0x50 */
s32 ScriptCmdGetNodeAxis_3333d0(Arg *p, s32 kind)
{
    f32 q[4] __attribute__((aligned(16)));
    f32 m[16] __attribute__((aligned(16)));
    s32 a;
    s32 b;
    s32 n;
    s32 rec;
    s32 h;

    if (kind != 6) {
        return 0;
    }
    a = ScriptSlotGetInt_3348b0(p++);
    b = ScriptSlotGetCodeAddr_334870(p++);
    n = ScriptSlotGetInt_3348b0(p++);
    /* two tests branching in OPPOSITE directions = an || */
    if (n < 0 || n > 2) {
        return 0;
    }
    rec = ((s32)ObjRecGetLiveObject_1c4a90(GetCurrentScene_1f5be0(), a));
    if (rec == 0) {
        return 0;
    }
    h = ((s32)ModelGetFrame_1511f0(rec, ModelFindFrameIndexByName_151220(rec, b)));
    if (h == 0) {
        return 0;
    }
    q[0] = 0.0f;
    q[1] = 0.0f;
    q[2] = 0.0f;
    q[3] = 1.0f;
    q[n] = 1.0f;
    FrameCalcWorldMatrix_148ff0(h, m);
    m[12] = 0.0f;
    m[13] = 0.0f;
    m[14] = 0.0f;
    m[15] = 1.0f;
    MtxMulVec4_10a8c0(q, m, q);
    VecNormalize_13bd90(q, q);
    ScriptSlotStoreVec3_334790(p, q);
    return 1;
}
