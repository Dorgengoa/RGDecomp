/* rgp:protos */
#define RGP_SELF_ScriptCmdRaycast_333e70 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "vec.h"

typedef struct Hit {
    u8 pad0[0x30];
    Vec4 x30;
    u8 pad40[0x20];
} Hit;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 ScriptCmdRaycast_333e70(s64 *args, s32 cmd) {
    Vec4 c __attribute__((aligned(16)));
    Vec4 d __attribute__((aligned(16)));
    Vec4 hit __attribute__((aligned(16)));
    Vec4 nrm __attribute__((aligned(16)));
    Vec4 box[2] __attribute__((aligned(16)));
    Hit buf[0x80] __attribute__((aligned(16)));
    Vec4 m __attribute__((aligned(16)));
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
        n = MapEvCollectCollTrisNearMaybe_1ff130(buf, 0x80, box, &c, -1, 0.0f);
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
