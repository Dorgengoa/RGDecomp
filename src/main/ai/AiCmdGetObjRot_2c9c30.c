#pragma opt_propagation off
#include "types.h"

typedef struct V4 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} V4 __attribute__((aligned(16)));

extern void *ObjRecGetLiveObject_1c4a90(s32, s32);
extern void ScriptSlotStoreVec3_2cc8a0(s32, f32 *);
extern s32 ScriptSlotGetInt_2cc9c0(void);
extern f32 D_0047EDF0;
extern f32 D_0047EDF4;
extern f32 D_0047EDF8;
extern f32 D_0047EDFC;
extern s32 D_004DB920[4];

s32 AiCmdGetObjRot_2c9c30(s32 arg0, s32 arg1) {
    f32 v[4] __attribute__((aligned(16)));
    s32 t;
    void *p;

    if (arg1 != 4) {
        return 0;
    }
    arg0 += 8;
    t = ScriptSlotGetInt_2cc9c0();
    v[0] = D_0047EDF0;
    v[1] = D_0047EDF4;
    v[2] = D_0047EDF8;
    v[3] = D_0047EDFC;
    p = ObjRecGetLiveObject_1c4a90(D_004DB920[0], t);
    if (p == NULL) {
        return 0;
    }
    *(__int128 *)v = *(__int128 *)((u8 *)p + 0x190);
    ScriptSlotStoreVec3_2cc8a0(arg0, v);
    return 1;
}
