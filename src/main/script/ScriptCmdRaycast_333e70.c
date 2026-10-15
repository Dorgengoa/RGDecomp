#include "types.h"
#include "vec.h"

typedef struct Hit {
    u8 pad0[0x30];
    Vec4 x30;
    u8 pad40[0x20];
} Hit;

extern void VecNormalize_13bd90(Vec4 *, Vec4 *);
extern f32 VecDistance_13d3d0(Vec4 *, Vec4 *);
extern void VecReflectNeg_13dc30(Vec4 *, Vec4 *, Vec4 *, Vec4 *);
extern s32 MeshRaycastWrapper_16f610(Hit *, s32, Vec4 *, Vec4 *, Vec4 *, s32, s32);
extern s32 MapEvCollectCollTrisNearMaybe_1ff130(Hit *, s32, Vec4 *, Vec4 *, f32, s32);
extern void ScriptSlotStoreFloatRef_3347d0(s64 *, f32);
extern void ScriptSlotStoreIntRef_3347f0(s64 *, s32);
extern void ScriptSlotsToVec4_334810(Vec4 *, s64 *);
extern s32 ScriptSlotGetInt_3348b0(s64 *);

s32 ScriptCmdRaycast_333e70(s64 *args, s32 cmd) {
    Vec4 c;
    Vec4 d;
    Vec4 hit;
    Vec4 nrm;
    Vec4 box[2];
    Hit buf[0x80];
    Vec4 m;
    s32 n;
    s32 sel;
    s32 idx;
    Hit *hp;
    s32 i;
    f32 r;

    if (cmd != 9 && cmd != 12 && cmd != 15) {
        return 0;
    }

    n = 0;
    sel = ScriptSlotGetInt_3348b0(args++);
    idx = ScriptSlotGetInt_3348b0(args++);
    ScriptSlotsToVec4_334810(&c, args);
    ScriptSlotsToVec4_334810(&d, args + 3);
    args += 6;
    if (sel < 0) {
        r = 10.0f + VecDistance_13d3d0(&c, &d);
        for (i = 0; i < 3; i++) {
            f32 *pc = &(&c.x)[i];
            f32 *pb = &(&box[0].x)[i];
            pb[0] = r + *pc;
            pb[4] = *pc - r;
        }
        box[0].w = 1.0f;
        box[1].w = 1.0f;
        n = MapEvCollectCollTrisNearMaybe_1ff130(buf, 0x80, box, &c, 0.0f, -1);
        hp = buf;
    }
    idx = MeshRaycastWrapper_16f610(hp, n, &c, &d, &hit, 1, idx);
    if (idx >= 0) {
        VecNormalize_13bd90(&m, &hp[idx].x30);
        VecReflectNeg_13dc30(&m, &hit, &c, &nrm);
        VecNormalize_13bd90(&nrm, &nrm);
    }
    switch (cmd) {
    case 9:
        break;
    case 12:
        ScriptSlotStoreFloatRef_3347d0(args++, hit.x);
        ScriptSlotStoreFloatRef_3347d0(args++, hit.y);
        ScriptSlotStoreFloatRef_3347d0(args++, hit.z);
        break;
    case 15:
        ScriptSlotStoreFloatRef_3347d0(args++, hit.x);
        ScriptSlotStoreFloatRef_3347d0(args++, hit.y);
        ScriptSlotStoreFloatRef_3347d0(args++, hit.z);
        ScriptSlotStoreFloatRef_3347d0(args++, nrm.x);
        ScriptSlotStoreFloatRef_3347d0(args++, nrm.y);
        ScriptSlotStoreFloatRef_3347d0(args++, nrm.z);
        break;
    default:
        return 0;
    }
    ScriptSlotStoreIntRef_3347f0(args, idx);
    return 1;
}
