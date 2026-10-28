/* rgp:protos */
#define RGP_SELF_AiCmdObjFindFrameIndex_2ca1a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef struct { s32 a, b; } E8_2ca1a0;
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern struct { s32 v; s32 pad[3]; } D_004DB920;

s32 AiCmdObjFindFrameIndex_2ca1a0(E8_2ca1a0 *p0)
{
    s32 a;
    s32 b;
    s32 r;
    s32 v;

    a = ScriptSlotGetInt_2cc9c0(p0++);
    b = ScriptSlotGetCodeAddr_2cc980(p0++);
    r = ((s32)ObjRecGetLiveObject_1c4a90(D_004DB920.v, a));
    if (r == 0) {
        return 0;
    }
    v = ModelFindFrameIndexByName_151220(r, b);
    ScriptSlotStoreIntRef_2cc900(p0, v);
    return 1;
}
