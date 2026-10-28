/* rgp:protos */
#define RGP_SELF_AiCmdObjGetYawOrTurnAngle_2c9ab0 1
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
    Vec x190;
} Obj;

typedef struct {
    Vec r;
    Vec p;
} RP;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0047D1FC;
extern s32 D_004DB920 __attribute__((section(".bss")));

s32 AiCmdObjGetYawOrTurnAngle_2c9ab0(Slot *arg0, s32 arg1)
{
    Vec v __attribute__((aligned(16)));
    RP a __attribute__((aligned(16)));
    RP b __attribute__((aligned(16)));
    Vec t __attribute__((aligned(16)));
    Vec m[4] __attribute__((aligned(16)));
    Vec out[4] __attribute__((aligned(16)));
    Obj *o1;
    Obj *o2;
    s32 id1;
    s32 id2;

    if (arg1 == 2) {
        o1 = ((Obj *)ObjRecGetLiveObject_1c4a90(D_004DB920, ScriptSlotGetInt_2cc9c0(arg0++)));
        if (o1 == NULL) {
            return 0;
        }
        v = o1->x190;
        ScriptSlotStoreFloatRef_2cc8e0(arg0, F(v, 1));
        goto gpt_return;
    }
    if (arg1 == 3) {
        id1 = ScriptSlotGetInt_2cc9c0(arg0++);
        id2 = ScriptSlotGetInt_2cc9c0(arg0++);
        o1 = ((Obj *)ObjRecGetLiveObject_1c4a90(D_004DB920, id1));
        o2 = ((Obj *)ObjRecGetLiveObject_1c4a90(D_004DB920, id2));
        if (o1 == NULL || o2 == NULL) {
            return 0;
        }
        a.p = o1->x180;
        a.r = o1->x190;
        b.p = o2->x180;
        b.r = o2->x190;
        F(t, 0) = Sinf_128fd0(F(a.r, 1));
        I(t, 1) = 0;
        F(t, 2) = Cosf_128d30(F(a.r, 1));
        I(t, 3) = 0;
        F(m[1], 1) = 1.0f;
        I(m[1], 0) = 0;
        m[2] = t;
        I(m[1], 2) = 0;
        sceVu0OuterProduct(&m[0], &m[1], &m[2]);
        m[3] = a.p;
        F(m[3], 3) = 1.0f;
        I(m[2], 3) = 0;
        I(m[1], 3) = 0;
        I(m[0], 3) = 0;
        ScriptSlotStoreFloatRef_2cc8e0(arg0, MtxTurnTowardsY_2cdbe0(out, m, &b.p, D_0047D1FC));
        goto gpt_return;
    }
    goto gpt_return;

gpt_return: return 1;
}
