/* rgp:protos */
#line 1
#include "types.h"

typedef struct Obj {
    u8 pad0[0x3D0];
    u64 m3D0;
    u8 pad3D8[0x3F4 - 0x3D8];
    s32 m3F4;
    u8 pad3F8[0x428 - 0x3F8];
    s32 m428;
    s32 m42C;
    u8 pad430[0x568 - 0x430];
    u64 m568;
    u8 pad570[0xA2E - 0x570];
    s16 mA2E;
    u8 padA30[2];
    s16 mA32;
    s16 mA34;
    u8 padA36[0xACC - 0xA36];
    f32 mACC;
    s32 mAD0;
    s32 mAD4;
    u8 padAD8[0xB4C - 0xAD8];
    s16 mB4C;
    u8 padB4E[2];
    s16 mB50;
} Obj;

typedef struct V2 {
    s32 x;
    f32 y;
    s32 pad[2];
} V2;

extern "C" {
void CharaActBattleInOut_21bbf0(Obj *p, s32 arg);
f32 Cosf_128d30(f32);
f32 Sinf_128fd0(f32);
s32 ModelHasMotion_20a5b0(s32, s32);
s32 CharaGetPlayedMotionName_212500(Obj *);
void CharaPlayMotion_212590(Obj *, s32, s32, s32, f32);
void CharaClearFlags_2124a0(Obj *);
s32 CharaPlayedMotionIsCurrent_2124c0(Obj *);
void CharaSetMoveDirXYZMaybe_213a90(Obj *, f32, f32, f32);
s32 CharaGetId_214a80(Obj *);
s32 CharaGetActionState_21c180(Obj *);
void CharaActLoco_21cc10(Obj *, s32);
void CharaResetToBaseMode_21e830(Obj *);
void ActCfgTableRunEvntByName_21f680(s32, s32, void *);
u64 ActCfgTableEvalNormalPrmtFlags_221600(s32, s32, s32, f32);
u64 ActCfgTableEvalNormalPendingPrmtFlags_2217a0(s32, s32, s32, f32);
s32 ActCfgTableGetInfoNameById_223b40(s32, s32, s32);
s32 CharaGetCurMotionName_238560(Obj *);
f32 CharaGetMotionFrame_238570(Obj *);
void CharaGetRot_2388b0(Obj *, V2 *);
extern u8 D_0045CED8[];
extern u8 D_0045CEE0[];
extern f32 D_0047D94C;
}

void CharaActBattleInOut_21bbf0(Obj *p, s32 arg)
{
    V2 v0 __attribute__((aligned(16)));
    V2 v1 __attribute__((aligned(16)));
    V2 v2 __attribute__((aligned(16)));
    u64 keep;
    s32 st;
    f32 a;
    bool fail;
    s32 r;

    p->m42C = 0;
    keep = ActCfgTableEvalNormalPendingPrmtFlags_2217a0(p->m428, p->mA32, CharaGetCurMotionName_238560(p), CharaGetMotionFrame_238570(p));
    ActCfgTableEvalNormalPrmtFlags_221600(p->m428, p->mA32, CharaGetCurMotionName_238560(p), CharaGetMotionFrame_238570(p));
    st = ((short)CharaGetActionState_21c180(p));
    switch (st) {
    case 40:
    case 41:
        fail = false;
        if (p->mB4C != 2) {
            fail = true;
        } else {
            if (p->mACC == 0.0f) {
                r = ActCfgTableGetInfoNameById_223b40(p->m428, st, 0);
                if (r != 0 && ModelHasMotion_20a5b0(p->m3F4, r) != 0) {
                    CharaPlayMotion_212590(p, p->m3F4, r, 2, D_0047D94C);
                    p->mA34 = st;
                    p->mAD0 = 0;
                    p->mAD4 = 0;
                    CharaClearFlags_2124a0(p);
                    CharaGetRot_2388b0(p, &v0);
                    a = Sinf_128fd0(v0.y);
                    CharaSetMoveDirXYZMaybe_213a90(p, a, 0.0f, Cosf_128d30(v0.y));
                } else {
                    fail = true;
                }
            }
            if (((unsigned char)CharaPlayedMotionIsCurrent_2124c0(p)) != 0 && !(CharaGetMotionFrame_238570(p) < 1.0f)) {
                fail = true;
            }
        }
        if (fail) {
            ActCfgTableRunEvntByName_21f680(p->m428, ((short)CharaGetId_214a80(p)), D_0045CED8);
            p->mB4C = 0;
            p->mA2E = 2;
            CharaResetToBaseMode_21e830(p);
            CharaActLoco_21cc10(p, arg);
            return;
        }
        p->m3D0 |= (u64)0x10 << 32;
        break;
    case 43:
        p->mA2E = 2;
        CharaResetToBaseMode_21e830(p);
        st = 0x2A;
    case 42:
        fail = false;
        if (p->mB50 != 2) {
            fail = true;
        } else {
            if (p->mACC == 0.0f) {
                r = ActCfgTableGetInfoNameById_223b40(p->m428, st, 0);
                if (r != 0 && ModelHasMotion_20a5b0(p->m3F4, r) != 0) {
                    CharaPlayMotion_212590(p, p->m3F4, r, 2, D_0047D94C);
                    p->mA34 = st;
                    p->mAD0 = 0;
                    p->mAD4 = 0;
                    CharaClearFlags_2124a0(p);
                    CharaGetRot_2388b0(p, &v1);
                    a = Sinf_128fd0(v1.y);
                    CharaSetMoveDirXYZMaybe_213a90(p, a, 0.0f, Cosf_128d30(v1.y));
                } else {
                    fail = true;
                }
            }
            if (ModelHasMotion_20a5b0(p->m3F4, CharaGetPlayedMotionName_212500(p)) == 0 || (((unsigned char)CharaPlayedMotionIsCurrent_2124c0(p)) != 0 && !(CharaGetMotionFrame_238570(p) < 1.0f))) {
                fail = true;
            }
        }
        if (fail) {
            ActCfgTableRunEvntByName_21f680(p->m428, ((short)CharaGetId_214a80(p)), D_0045CEE0);
            p->mB50 = 0;
            p->mA2E = 0;
            CharaResetToBaseMode_21e830(p);
            CharaActLoco_21cc10(p, arg);
            return;
        }
        p->m3D0 |= (u64)0x10 << 32;
        break;
    case 45:
        p->mA2E = 2;
        CharaResetToBaseMode_21e830(p);
        st = 0x2C;
    case 44:
        fail = false;
        if (p->mB50 != 3) {
            fail = true;
        } else {
            if (p->mACC == 0.0f) {
                r = ActCfgTableGetInfoNameById_223b40(p->m428, st, 0);
                if (r != 0 && ModelHasMotion_20a5b0(p->m3F4, r) != 0) {
                    CharaPlayMotion_212590(p, p->m3F4, r, 2, D_0047D94C);
                    p->mA34 = st;
                    p->mAD0 = 0;
                    p->mAD4 = 0;
                    CharaClearFlags_2124a0(p);
                    CharaGetRot_2388b0(p, &v2);
                    a = Sinf_128fd0(v2.y);
                    CharaSetMoveDirXYZMaybe_213a90(p, a, 0.0f, Cosf_128d30(v2.y));
                } else {
                    fail = true;
                }
            }
            if (ModelHasMotion_20a5b0(p->m3F4, CharaGetPlayedMotionName_212500(p)) == 0 || (((unsigned char)CharaPlayedMotionIsCurrent_2124c0(p)) != 0 && !(CharaGetMotionFrame_238570(p) < 1.0f))) {
                fail = true;
            }
        }
        if (fail) {
            p->mB50 = 0;
            p->mA2E = 0;
            CharaResetToBaseMode_21e830(p);
            CharaActLoco_21cc10(p, arg);
            return;
        }
        p->m3D0 |= (u64)0x10 << 32;
        break;
    default:
        CharaResetToBaseMode_21e830(p);
        CharaActLoco_21cc10(p, arg);
        return;
    }
    p->m3D0 |= (u64)0x04000000 << 32;
    p->m568 &= keep;
}
