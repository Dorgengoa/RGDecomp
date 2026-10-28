/* rgp:protos */
#define RGP_SELF_CharaCmdHoldThrow_22a160 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Vec {
    f32 x, y, z, w;
} Vec;

typedef struct Actor {
    u8 pad[0xA44];
    u32 flags;
} Actor;

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
extern f32 D_0045B080[0x100];

s32 CharaCmdHoldThrow_22a160(s32 *arg0, u8 *arg1, s32 arg2) {
    Vec pos __attribute__((aligned(16)));
    Vec tgt __attribute__((aligned(16)));
    Vec d __attribute__((aligned(16)));
    Actor *actor;
    s32 flag;
    s32 obj;
    s32 kind;
    f32 speed;
    f32 maxv;
    f32 t;
    f32 v;

    switch (arg2) {
    case 3:
    case 2:
        actor = ((Actor *)ActionMgrFindById_233b50(((s32)GetActionMgr_1fdb50()), *arg0));
        if (actor == 0) {
            return 1;
        }
        flag = 0;
        if (arg2 > 2) {
            flag = ScriptArgGetInt_302d70(arg1 + 0xA) != 0;
        }
        if (!(actor->flags & 0x8000)) {
            maxv = ScriptArgGetFloat_302cf0(arg1 + 5);
            CharaReleaseHeldTarget_2116b0(actor, flag, 0.0f, maxv, ScriptArgGetFloat_302cf0(arg1));
            return 1;
        }
        obj = ((s32)CharaGetTargetRef_214a30(actor));
        kind = ((short)TargetRefGetKind_2e7130(obj));
        if (kind != 5 && kind != 4) {
            return 1;
        }
        if (((Actor *)ActionMgrFindById_233b50(((s32)GetActionMgr_1fdb50()), ((short)TargetRefGetId_2e7120(obj)))) == 0) {
            return 1;
        }
        CharaGetPos_2388a0(actor, &pos);
        TargetRefGetPos_2e6a60(obj, &tgt);
        pos.y = pos.y + 1.25f * D_0045B080[0];
        speed = ScriptArgGetFloat_302cf0(arg1);
        maxv = ScriptArgGetFloat_302cf0(arg1 + 5);
        VecSub_1cbd00(&d, &tgt, &pos);
        t = VecLengthXZ_1cb490(&d) / speed;
        v = d.y / t - t * (0.5f * GetThrowGravity_3647b0());
        if (!(v <= maxv)) {
            v = maxv;
        }
        CharaReleaseHeldTarget_2116b0(actor, flag, 0.0f, v, speed);
        break;
    default:
        return 0;
    }
    return 1;
}
