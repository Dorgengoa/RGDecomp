/* rgp:protos */
#define RGP_SELF_AiCmdTurnToward_2c87a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef rg_u128 u128;
#pragma opt_propagation off

typedef union {
    u128 q;
    f32 f[4];
    s32 i[4];
} V4;

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
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0047D1DC;
/*rgp*/
extern s32 D_004DB920[];
extern s32 D_004DB92C[];

s32 AiCmdTurnToward_2c87a0(s64 *arg0, s32 arg1) {
    f32 d;
    V4 pos __attribute__((aligned(16)));
    V4 rot __attribute__((aligned(16)));
    V4 tgt __attribute__((aligned(16)));
    V4 dir __attribute__((aligned(16)));
    V4 out __attribute__((aligned(16)));
    V4 diff __attribute__((aligned(16)));
    s32 need;
    f32 lim;
    u8 *obj;
    s32 t;

    if (D_004DB92C[0] == 0) {
        return 0;
    }
    CharaGetPos_2388a0(D_004DB92C[0], &pos);
    CharaGetRot_2388b0(D_004DB92C[0], &rot);
    t = *(s32 *)arg0;
    if (t == 1) {
        tgt.f[0] = ScriptSlotGetFloat_2cc9a0(arg0++);
        tgt.f[1] = pos.f[1];
        ScriptSlotGetFloat_2cc9a0(arg0++);
        tgt.f[2] = ScriptSlotGetFloat_2cc9a0(arg0++);
        need = 5;
        tgt.i[3] = 0;
    } else if (t == 0) {
        obj = ((u8 *)ObjRecGetLiveObject_1c4a90(D_004DB920[0], ScriptSlotGetInt_2cc9c0(arg0++)));
        if (obj == 0) {
            return 1;
        }
        t = ModelGetRootFrame_1511a0(obj);
        if (t != 0) {
            FrameGetWorldPos_148f30(t, &tgt);
        } else {
            tgt.q = *(u128 *)(obj + 0x180);
        }
        tgt.i[3] = 0;
        need = 3;
    }
    lim = ScriptSlotGetFloat_2cc9a0(arg0++);
    if (pos.f[0] == tgt.f[0] && pos.f[2] == tgt.f[2]) {
        return 1;
    }
    dir.f[0] = Sinf_128fd0(rot.f[1]);
    dir.i[1] = 0;
    dir.f[2] = Cosf_128d30(rot.f[1]);
    dir.i[3] = 0;
    VecSub_13be40(&diff, &tgt, &pos);
    diff.i[1] = 0;
    VecNormalize_13bd90(&diff, &diff);
    AxisAngleBetweenVecs_1d7da0(&out, &d, &dir, &diff);
    {
        f64 h = 0.5;
        f64 x = d;
        d = dpmul(h, x);
    }
    if (d > lim) {
        d = lim;
    }
    VecRotateAxisAngle_1d7f10(&dir, &dir, &out, d);
    if (out.f[1] < 0.0f) {
        d *= -1.0f;
    }
    rot.f[1] = WrapAngle_13c050(rot.f[1] + d);
    CharaSetYaw_2138f0(D_004DB92C[0], rot.f[1]);
    CharaSetDirNormalizedMaybe_213b30(D_004DB92C[0], &dir);
    if (arg1 >= need) {
        f32 a;
        a = d;
        a = (a < 0.0f) ? -a : a;
        if (a < D_0047D1DC) {
            ScriptSlotStoreFloatRef_2cc8e0(arg0, 0.0f);
        } else {
            ScriptSlotStoreFloatRef_2cc8e0(arg0, *(f32 *)&d);
        }
    }
    return 1;
}
