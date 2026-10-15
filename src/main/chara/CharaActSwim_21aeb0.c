#include "types.h"

typedef unsigned __int128 u128;

typedef struct Obj {
    u8 pad0[0x3F4];
    s32 u3F4;
    u8 pad1[0x30];
    s32 u428;
    s32 u42C;
    u8 pad2[0x10];
    u8 u440[0x128];
    u64 u568;
    u64 u570;
    u8 pad3[0x4BA];
    s16 uA32;
    s16 uA34;
    u8 pad4[0x4];
    s16 uA3A;
    u8 pad5[0x94];
    s32 uAD0;
    s32 uAD4;
} Obj;

extern void CharaClearFlags_2124a0(void *);
extern s32 CharaPlayedMotionIsCurrent_2124c0(void *);
extern void CharaPlayMotion_212590(void *, s32, void *, s32, f32);
extern void CharaSetMoveDirMaybe_213b00(void *, void *);
extern void CharaActHang_21a890(void *, s32);
extern void CharaSetActionModeHang_21ae30(void *);
extern s32 CharaSelectSwimState_21b110(void *);
extern void CharaSetActionModeSwim_21b170(void *);
extern u64 ActCfgTableEvalNormalPrmtFlags_221600(s32, s32, s32, f32);
extern u64 ActCfgTableEvalNormalPendingPrmtFlags_2217a0(s32, s32, s32, f32);
extern s32 ActCfgTableFindMoveById_223080(s32, s32);
extern s32 CharaIsCurMotion_238540(void *, void *);
extern s32 CharaGetCurMotionName_238560(void *);
extern f32 CharaGetMotionFrame_238570(void *);

extern u8 D_0045CE78[];
extern u8 D_0045CE88[];
extern f32 D_0047DA74;

void CharaActSwim_21aeb0(Obj *arg0, s32 arg1)
{
    s32 a;
    u64 mask;
    s32 st;

    arg0->u42C = 0;
    a = CharaGetCurMotionName_238560(arg0);
    mask = ActCfgTableEvalNormalPendingPrmtFlags_2217a0(arg0->u428, arg0->uA32, a, CharaGetMotionFrame_238570(arg0));
    a = CharaGetCurMotionName_238560(arg0);
    arg0->u570 = arg0->u568 & (ActCfgTableEvalNormalPrmtFlags_221600(arg0->u428, arg0->uA32, a, CharaGetMotionFrame_238570(arg0)) | 0x8017CFFDC0080FFFULL);
    st = CharaSelectSwimState_21b110(arg0);
    arg0->u570 |= 0x800;
    arg0->u42C = ActCfgTableFindMoveById_223080(arg0->u428, 5);
    if (arg0->u570 & 3) {
        CharaSetMoveDirMaybe_213b00(arg0, arg0->u440);
    }
    switch (st) {
    case 0:
        if (arg0->uA34 != st && CharaIsCurMotion_238540(arg0, D_0045CE78) == 0 &&
            (arg0->uA32 != arg0->uA3A || CharaPlayedMotionIsCurrent_2124c0(arg0) != 0)) {
            CharaPlayMotion_212590(arg0, arg0->u3F4, D_0045CE78, 0, D_0047DA74);
            arg0->uA34 = st;
            arg0->uAD0 = 0;
            arg0->uAD4 = 0;
            CharaClearFlags_2124a0(arg0);
        }
        break;
    case 1:
        if (arg0->uA34 != st && CharaIsCurMotion_238540(arg0, D_0045CE88) == 0 &&
            (arg0->uA32 != arg0->uA3A || CharaPlayedMotionIsCurrent_2124c0(arg0) != 0)) {
            CharaPlayMotion_212590(arg0, arg0->u3F4, D_0045CE88, 0, D_0047DA74);
            arg0->uA34 = st;
            arg0->uAD0 = 0;
            arg0->uAD4 = 0;
        }
        break;
    case 100:
        CharaSetActionModeHang_21ae30(arg0);
        arg0->uA34 = 201;
        CharaActHang_21a890(arg0, arg1);
        return;
    default:
        CharaSetActionModeSwim_21b170(arg0);
        CharaActSwim_21aeb0(arg0, arg1);
        return;
    }
    arg0->u568 &= mask;
}
