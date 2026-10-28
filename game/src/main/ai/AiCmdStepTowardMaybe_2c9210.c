/* rgp:protos */
#define RGP_SELF_AiCmdStepTowardMaybe_2c9210 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef rg_u128 u128;
typedef struct {
    u128 q;
} Vec;

#define F(v, i) (((f32 *)&(v))[i])
#define I(v, i) (((s32 *)&(v))[i])

typedef struct {
    s32 a;
    s32 b;
} Slot;

typedef struct {
    u8 pad0[0x180];
    Vec x180;
} Obj;

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
/*rgp*/
/*rgp*/
extern s64 D_0047D188;
extern f32 D_0047D1FC;
extern s32 D_004DB920 __attribute__((section(".bss")));
extern s32 D_004DB92C __attribute__((section(".bss")));

s32 AiCmdStepTowardMaybe_2c9210(Slot *arg0, s32 arg1)
{
    Vec pos __attribute__((aligned(16)));
    Vec rot __attribute__((aligned(16)));
    Vec old __attribute__((aligned(16)));
    Vec tgt __attribute__((aligned(16)));
    Vec t __attribute__((aligned(16)));
    Vec s __attribute__((aligned(16)));
    Vec d __attribute__((aligned(16)));
    Vec m[4] __attribute__((aligned(16)));
    Vec out[4] __attribute__((aligned(16)));
    Obj *o;
    s32 h;
    f32 scale;
    f32 w;
    f32 diff;
    f32 ry;

    if (D_004DB92C == 0) {
        return 0;
    }
    CharaGetPos_2388a0(D_004DB92C, &pos);
    CharaGetRot_2388b0(D_004DB92C, &rot);
    w = D_0047D1FC;
    old = rot;
    scale = 1.0f;
    if (arg0->a == 1) {
        F(tgt, 0) = ScriptSlotGetFloat_2cc9a0(arg0++);
        F(tgt, 1) = ScriptSlotGetFloat_2cc9a0(arg0++);
        F(tgt, 2) = ScriptSlotGetFloat_2cc9a0(arg0++);
        I(tgt, 3) = 0;
        scale = ScriptSlotGetFloat_2cc9a0(arg0++);
        if (arg1 >= 5) {
            w = ScriptSlotGetFloat_2cc9a0(arg0++);
        }
        if (arg1 >= 6) {
            switch (arg0->a) {
            case 1:
                ScriptSlotGetFloat_2cc9a0(arg0);
                break;
            case 0:
                ScriptSlotGetInt_2cc9c0(arg0);
                break;
            }
        }
    } else if (arg0->a == 0) {
        h = D_004DB920;
        o = ((Obj *)ObjRecGetLiveObject_1c4a90(h, ScriptSlotGetInt_2cc9c0(arg0++)));
        if (o == 0) {
            return 1;
        }
        tgt = o->x180;
        scale = ScriptSlotGetFloat_2cc9a0(arg0++);
        if (arg1 >= 3) {
            w = ScriptSlotGetFloat_2cc9a0(arg0++);
        }
        if (arg1 >= 4) {
            switch (arg0->a) {
            case 1:
                ScriptSlotGetFloat_2cc9a0(arg0);
                break;
            case 0:
                ScriptSlotGetInt_2cc9c0(arg0);
                break;
            }
        }
    }
    F(t, 0) = Sinf_128fd0(F(rot, 1));
    I(t, 1) = 0;
    F(t, 2) = Cosf_128d30(F(rot, 1));
    I(t, 3) = 0;
    VecSub_13be40(&d, &tgt, &pos);
    VecNormalize_13bd90(&d, &d);
    F(m[1], 1) = 1.0f;
    I(m[1], 0) = 0;
    I(m[1], 2) = 0;
    m[2] = t;
    sceVu0OuterProduct(&m[0], &m[1], &m[2]);
    m[3] = pos;
    F(m[3], 3) = 1.0f;
    I(m[2], 3) = 0;
    I(m[1], 3) = 0;
    I(m[0], 3) = 0;
    MtxTurnTowardsY_2cdbe0(out, m, &tgt, w);
    F(rot, 1) = Atan2f_1291a8(F(out[2], 0), F(out[2], 2));
    VecScale_13be00(&s, &t, scale);
    VecAdd_13be20(&pos, &pos, &s);
    CharaSetPosVec_2387a0(D_004DB92C, &pos);
    ry = F(rot, 1);
    diff = F(old, 1) - ry;
    if (diff < 0.0f) {
        diff = -diff;
    }
    if (((unsigned char)DoubleGreater_100260(fptodp(diff), __builtin_bit_cast(double, (long long)(D_0047D188)))) != 0) {
        CharaSetYaw_2138f0(D_004DB92C, ry);
        CharaSetDirNormalizedMaybe_213b30(D_004DB92C, &out[2]);
    }
    return 1;
}
