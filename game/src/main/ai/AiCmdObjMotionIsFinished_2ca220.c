/* rgp:protos */
#define RGP_SELF_AiCmdObjMotionIsFinished_2ca220 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef struct { s32 a, b; } E8_2ca220;
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern struct { s32 v; s32 pad[3]; } D_004DB920;

s32 AiCmdObjMotionIsFinished_2ca220(E8_2ca220 *p0)
{
    s32 h;
    s32 r;
    u8 *o;
    s32 v;

    h = D_004DB920.v;
    r = ScriptSlotGetInt_2cc9c0(p0++);
    o = ((u8 *)ObjRecGetLiveObject_1c4a90(h, r));
    if (o != 0) {
        v = MotionListIsFinished_171d90(o + 0x1F0, -1);
        ScriptSlotStoreIntRef_2cc900(p0, v);
    }
    return 1;
}
