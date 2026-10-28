/* rgp:protos */
#define RGP_SELF_AiCmdNavSnapPos_2c60a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "vec.h"

typedef struct Obj {
    u8 pad0[0x180];
    Vec4 unk180;
} Obj;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_004DB920[];
extern s32 D_004DB928[];

s32 AiCmdNavSnapPos_2c60a0(s64 *arg0, s32 mode)
{
    Vec4 sp50 __attribute__((aligned(16)));
    Vec4 sp40 __attribute__((aligned(16)));
    void *t;
    Obj *o;
    s32 id;

    t = GetNavMgr_2d1950();
    if (mode == 3 || mode == 4) {
        id = D_004DB928[0];
        if (mode == 4) {
            id = ScriptSlotGetInt_2cc9c0(arg0++);
        }
        o = (Obj *)ObjRecGetLiveObject_1c4a90(D_004DB920[0], id);
        if (o == NULL) {
            return 0;
        }
        sp50 = o->unk180;
    } else if (mode == 6) {
        sp50.x = ScriptSlotGetFloat_2cc9a0(arg0++);
        sp50.y = ScriptSlotGetFloat_2cc9a0(arg0++);
        sp50.z = ScriptSlotGetFloat_2cc9a0(arg0++);
    }
    if (NavSnapPosInAreaGraph_30ab90(t, &sp40, &sp50) != 0) {
        ScriptSlotStoreFloatRef_2cc8e0(arg0++, sp40.x);
        ScriptSlotStoreFloatRef_2cc8e0(arg0++, sp40.y);
        ScriptSlotStoreFloatRef_2cc8e0(arg0, sp40.z);
    } else {
        ScriptSlotStoreFloatRef_2cc8e0(arg0++, sp50.x);
        ScriptSlotStoreFloatRef_2cc8e0(arg0++, sp50.y);
        ScriptSlotStoreFloatRef_2cc8e0(arg0, sp50.z);
    }
    return 1;
}
