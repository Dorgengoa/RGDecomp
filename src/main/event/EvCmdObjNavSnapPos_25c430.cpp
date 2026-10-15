#include "types.h"
#include "vec.h"
extern "C" {



typedef struct Vec3 { f32 x, y, z; } Vec3;

typedef struct Obj {
    u8 pad0[0x180];
    Vec4 unk180;
} Obj;

extern void *ObjRecGetLiveObject_1c4a90(s32, s32);
extern void ScriptSetRefFloat_26a1c0(s64 *, f32);
extern s32 ScriptGetInt_26a2a0(s64 *);
extern void *GetNavMgr_2d1950(void);
extern s32 NavSnapPosInAreaGraph_30ab90(void *, Vec4 *, Vec4 *);
extern s32 D_00481F78;

s32 EvCmdObjNavSnapPos_25c430(s64 *arg0)
{
    Vec4 sp40;
    Vec4 sp30;
    void *t;
    Obj *o;

    t = GetNavMgr_2d1950();
    o = (Obj *)ObjRecGetLiveObject_1c4a90(D_00481F78, ScriptGetInt_26a2a0(arg0++));
    if (o == NULL) {
        return 0;
    }
    sp40 = o->unk180;
    if (NavSnapPosInAreaGraph_30ab90(t, &sp30, &sp40) != 0) {
        ScriptSetRefFloat_26a1c0(arg0++, sp30.x);
        ScriptSetRefFloat_26a1c0(arg0++, sp30.y);
        ScriptSetRefFloat_26a1c0(arg0, sp30.z);
    } else {
        ScriptSetRefFloat_26a1c0(arg0++, sp40.x);
        ScriptSetRefFloat_26a1c0(arg0++, sp40.y);
        ScriptSetRefFloat_26a1c0(arg0, sp40.z);
    }

    return 1;
}

}
