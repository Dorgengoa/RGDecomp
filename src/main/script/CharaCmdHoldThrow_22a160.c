#include "types.h"

typedef struct Vec {
    f32 x, y, z, w;
} Vec;

typedef struct Actor {
    u8 pad[0xA44];
    u32 flags;
} Actor;

extern s32 GetActionMgr_1fdb50(void);
extern Actor *ActionMgrFindById_233b50(s32 a, s32 b);
extern s32 ScriptArgGetInt_302d70(u8 *p);
extern f32 ScriptArgGetFloat_302cf0(u8 *p);
extern void CharaReleaseHeldTarget_2116b0(Actor *a, s32 flag, f32 x, f32 y, f32 z);
extern s32 CharaGetTargetRef_214a30(Actor *a);
extern s32 TargetRefGetKind_2e7130(s32 x);
extern s32 TargetRefGetId_2e7120(s32 x);
extern void CharaGetPos_2388a0(Actor *a, Vec *v);
extern void TargetRefGetPos_2e6a60(s32 x, Vec *v);
extern void VecSub_1cbd00(Vec *d, Vec *a, Vec *b);
extern f32 VecLengthXZ_1cb490(Vec *v);
extern f32 GetThrowGravity_3647b0(void);
extern f32 D_0045B080[0x100];

s32 CharaCmdHoldThrow_22a160(s32 *arg0, u8 *arg1, s32 arg2) {
    Vec pos;
    Vec tgt;
    Vec d;
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
        actor = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), *arg0);
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
        obj = CharaGetTargetRef_214a30(actor);
        kind = TargetRefGetKind_2e7130(obj);
        if (kind != 5 && kind != 4) {
            return 1;
        }
        if (ActionMgrFindById_233b50(GetActionMgr_1fdb50(), TargetRefGetId_2e7120(obj)) == 0) {
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
