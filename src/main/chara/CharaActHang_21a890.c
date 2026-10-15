#include "types.h"

typedef struct Obj {
    u8 pad0[0x350];
    u8 m350[0x3D0 - 0x350];
    u64 m3D0;
    u8 pad3D8[0x3F4 - 0x3D8];
    s32 m3F4;
    u8 pad3F8[0x428 - 0x3F8];
    s32 m428;
    s32 m42C;
    u8 pad430[0x568 - 0x430];
    u64 m568;
    u64 m570;
    u8 pad578[0xA32 - 0x578];
    s16 mA32;
    s16 mA34;
    u8 padA36[0xAD0 - 0xA36];
    s32 mAD0;
    s32 mAD4;
} Obj;

extern void CharaPlayMotion_212590(Obj *, s32, void *, s32, f32);
extern void CharaClearFlags_2124a0(Obj *);
extern s32 CharaPlayedMotionIsCurrent_2124c0(Obj *);
extern u32 CharaSelectHangState_21acc0(Obj *);
extern void CharaSetActionModeHang_21ae30(Obj *);
extern void CharaActMoveMotion_21b180(Obj *, s32);
extern void CharaSetActionModeMoveMotion_21bbb0(Obj *);
extern void CharaActLoco_21cc10(Obj *, s32);
extern void CharaResetToBaseMode_21e830(Obj *);
extern s32 CharaInputInterruptMaybe_21e8f0(Obj *, s32);
extern u64 ActCfgTableEvalNormalPrmtFlags_221600(s32, s32, s32, f32);
extern u64 ActCfgTableEvalNormalPendingPrmtFlags_2217a0(s32, s32, s32, f32);
extern void CharaHangLedgeInvalidate_23a2a0(void *);
extern s32 CharaGetCurMotionName_238560(Obj *);
extern f32 CharaGetMotionFrame_238570(Obj *);
extern u8 D_0045CE10[];
extern u8 D_0045CE20[];
extern u8 D_0045CE30[];
extern u8 D_0045CE40[];
extern u8 D_0045CE50[];

void CharaActHang_21a890(Obj *p, s32 arg)
{
    u64 keep;
    u32 st;

    p->m42C = 0;
    keep = ActCfgTableEvalNormalPendingPrmtFlags_2217a0(p->m428, p->mA32, CharaGetCurMotionName_238560(p), CharaGetMotionFrame_238570(p));
    p->m570 = p->m568 & (ActCfgTableEvalNormalPrmtFlags_221600(p->m428, p->mA32, CharaGetCurMotionName_238560(p), CharaGetMotionFrame_238570(p)) | 0x8000000000000000ULL);
    st = CharaSelectHangState_21acc0(p);
    switch (st) {
    case 0:
        if (p->mA34 != st) {
            CharaPlayMotion_212590(p, p->m3F4, D_0045CE10, 2, 1.0f);
            p->mA34 = st;
            p->mAD0 = 0;
            p->mAD4 = 0;
            CharaClearFlags_2124a0(p);
        }
        if (CharaPlayedMotionIsCurrent_2124c0(p) != 0 && !(CharaGetMotionFrame_238570(p) < 1.0f)) {
            CharaPlayMotion_212590(p, p->m3F4, D_0045CE20, 0, 1.0f);
            p->mA34 = 1;
            p->mAD0 = 0;
            p->mAD4 = 0;
        }
        break;
    case 1:
        if (p->mA34 != st) {
            CharaPlayMotion_212590(p, p->m3F4, D_0045CE20, 0, 0.125f);
            p->mAD0 = 0;
            p->mAD4 = 0;
            p->mA34 = st;
            CharaClearFlags_2124a0(p);
        }
        break;
    case 2:
        if (p->mA34 != st) {
            CharaPlayMotion_212590(p, p->m3F4, D_0045CE30, 6, 1.0f);
            p->mA34 = st;
            p->mAD0 = 0;
            p->mAD4 = 0;
            CharaClearFlags_2124a0(p);
        } else {
            if (CharaPlayedMotionIsCurrent_2124c0(p) != 0 && !(CharaGetMotionFrame_238570(p) < 1.0f)) {
                CharaSetActionModeHang_21ae30(p);
                CharaActHang_21a890(p, arg);
                return;
            }
        }
        break;
    case 3:
        if (p->mA34 != st) {
            CharaPlayMotion_212590(p, p->m3F4, D_0045CE40, 6, 1.0f);
            p->mA34 = st;
            p->mAD0 = 0;
            p->mAD4 = 0;
            CharaClearFlags_2124a0(p);
        } else {
            if (CharaPlayedMotionIsCurrent_2124c0(p) != 0 && !(CharaGetMotionFrame_238570(p) < 1.0f)) {
                CharaSetActionModeHang_21ae30(p);
                CharaActHang_21a890(p, arg);
                return;
            }
        }
        break;
    case 4:
        if (p->mA34 != st) {
            CharaPlayMotion_212590(p, p->m3F4, D_0045CE50, 6, 1.0f);
            p->mA34 = st;
            p->mAD0 = 0;
            p->mAD4 = 0;
            CharaClearFlags_2124a0(p);
        } else {
            if (CharaInputInterruptMaybe_21e8f0(p, arg) != 0) {
                return;
            }
            if (CharaPlayedMotionIsCurrent_2124c0(p) != 0 && !(CharaGetMotionFrame_238570(p) < 1.0f)) {
                CharaHangLedgeInvalidate_23a2a0(p->m350);
                p->m3D0 |= (u64)0x04000000 << 32;
                CharaResetToBaseMode_21e830(p);
                CharaActLoco_21cc10(p, arg);
                return;
            }
        }
        break;
    case 5:
        CharaHangLedgeInvalidate_23a2a0(p->m350);
        p->m3D0 |= (u64)0x04000000 << 32;
        CharaClearFlags_2124a0(p);
        CharaSetActionModeMoveMotion_21bbb0(p);
        p->mA34 = 0xCA;
        CharaActMoveMotion_21b180(p, arg);
        return;
    default:
        CharaSetActionModeHang_21ae30(p);
        CharaActHang_21a890(p, arg);
        return;
    }
    p->m568 &= keep;
}
