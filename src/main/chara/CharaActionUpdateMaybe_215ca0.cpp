#pragma opt_rebuildconditionals off
#pragma opt_propagation off
#pragma opt_loop_invariants off
#include "types.h"

typedef struct Obj {
    u8 pad0[0x70];
    f32 m70;
    u8 pad74[0x4];
    f32 m78;
    u8 pad7C[0x354];
    u64 m3D0;
    u8 pad3D8[0x1C];
    s32 m3F4;
    u8 pad3F8[0x30];
    s32 m428;
    s32 m42C;
    u8 pad430[0x10];
    f32 m440;
    u8 pad444[0x4];
    f32 m448;
    u8 pad44C[0x24];
    f32 m470;
    u8 pad474[0x4];
    f32 m478;
    u8 pad47C[0xEC];
    u64 m568;
    u64 m570;
    u8 pad578[0x3A8];
    u8 m920;
    u8 pad921[0xEB];
    s32 mA0C;
    f32 mA10;
    void * mA14;
    void * mA18;
    u8 padA1C[0x4];
    s32 mA20;
    f32 mA24;
    u8 padA28[0xA];
    s16 mA32;
    s16 mA34;
    s16 mA36;
    u8 padA38[0x4];
    s16 mA3C;
    u8 padA3E[0x6];
    s32 mA44;
    u8 padA48[0x88];
    s32 mAD0;
    s32 mAD4;
    u8 padAD8[0x4];
    s32 mADC;
} Obj;


typedef struct V4 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} V4;

typedef struct Node {
    s32 m0;
    u8 pad4[8];
    s32 mC;
    f32 m10;
} Node;

typedef struct Big {
    u8 pad0[0x10];
    u8 sub[0xA0];
    void *vptr;
    u8 padB4[0x890 - 0xB4];
} Big;

extern "C" {
extern f32 RandFloat_13c010(void);
extern s32 ModelGetFrame_1511f0(s32, s32);
extern Node *ObjFindNthAttachPoint_1addc0(s32, s32, s32);
extern void VecSub_1cbd00(V4 *, void *, f32 *);
extern s32 CharaHasLandedMaybe_20fdb0(Obj *);
extern s32 CharaActionGetCancelMaskMaybe_210b60(Obj *);
extern void CharaClearFlags_2124a0(Obj *);
extern s32 CharaPlayedMotionIsCurrent_2124c0(Obj *);
extern void CharaPlayMotion_212590(Obj *, s32, s32, s32, f32);
extern s32 CharaGetBaseActionMode_213830(Obj *);
extern void CharaSetMoveDirXYZMaybe_213a90(Obj *, f32, f32, f32);
extern void CharaGetTargetPos_214a40(Obj *, void *);
extern s32 CharaGetId_214a80(Obj *);
extern void CharaClearActionEffects_214ce0(Obj *);
extern s32 CharaIsActionActive_215040(Obj *);
extern s32 CharaTryStartAction_216700(Obj *, s32 *);
extern void NodeRefObjCloneAndRegister_219500(Big *);
extern void CharaActMoveMotion_21b180(Obj *, s32 *);
extern void CharaSetActionModeMoveMotion_21bbb0(Obj *);
extern void CharaActLoco_21cc10(Obj *, s32 *);
extern void CharaResetToBaseMode_21e830(Obj *);
extern s32 CharaInputInterruptMaybe_21e8f0(Obj *, s32 *);
extern u64 ActCfgTableEvalPrmtFlags_2210e0(s32, s32, s32, f32);
extern u64 ActCfgTableEvalPendingPrmtFlags_221380(s32, s32, s32, f32);
extern void ActCfgTableRunExitEvnt_222430(s32, s32, s32);
extern s32 ActCfgTableFindMoveById_223080(s32, s32);
extern f32 CharaTableGetIntRate_2253f0(void *);
extern s32 CharaTableGetStepCount_225410(void *);
extern void *CharaTableEntryAt_225420(void *, s32);
extern s32 CharaTableGetName_225480(void *);
extern void ActDataRunEvnts_225b70(void *, s32);
extern s16 CharaTableGetActionKind_225d30(void *);
extern s32 CharaTableEntryGetWaitFrameParam_2260c0(void *, s32);
extern s32 CharaTableEntryGetEndType_226100(void *);
extern s32 CharaTableEntryGetMotionFlags_226240(void *);
extern s32 CharaTableDataGetMotionName_2269e0(void *);
extern s32 CharaGetCurMotionName_238560(Obj *);
extern f32 CharaGetMotionFrame_238570(Obj *);
extern s32 IsInBattle_288420(void);
extern void NodeRefObjAddClsnPnt_318ca0(Big *, s32, s32, f32, f32);
extern s32 NodeRefListAdd_318d50(Big *, s32, s32, s32, s32, V4 *);
extern void NodeRefObjCtor_318ff0(Big *, s32, s32, s32, f32);
extern void ExecInfoInitFromObj_3a7790(void *, s32, s32);
extern void ExecInfoInitFromChara_3a7830(void *, s32, u8, s32, s32);
extern f32 D_0045B080[];
extern u8 D_00471AA0[];
extern f32 D_0047DB14;
extern V4 D_0047E640 __attribute__((section(".sdata")));
extern s32 D_004BCB20[];
void CharaActionUpdateMaybe_215ca0(Obj *a, s32 *arg1);
}

static inline u64 getA(Obj *a)
{
    return ActCfgTableEvalPrmtFlags_2210e0(a->m428, a->mA0C, CharaGetCurMotionName_238560(a), CharaGetMotionFrame_238570(a)) | 0x001FDFFDA0000000ULL;
}

static inline u64 getB(Obj *a)
{
    return ActCfgTableEvalPendingPrmtFlags_221380(a->m428, a->mA0C, CharaGetCurMotionName_238560(a), CharaGetMotionFrame_238570(a)) | 0x20000000;
}

extern "C" void CharaActionUpdateMaybe_215ca0(Obj *a, s32 *arg1)
{
    Big obj;
    V4 col;
    u8 buf[0x10];
    V4 out;
    void *s0;
    u64 m5;
    u64 m7;
    s32 fl;
    bool go;
    void *s4;
    s32 f;
    void *sub;
    s32 n;
    Node *nd;
    s32 *p;
    s32 tb;
    f32 f20;
    f32 t;
    s32 v;

    a->m42C = 0;
    if (a->mA0C == 0 || (s4 = a->mA14) == 0 || (s0 = a->mA18) == 0) {
        CharaClearFlags_2124a0(a);
        CharaResetToBaseMode_21e830(a);
        CharaActLoco_21cc10(a, arg1);
        return;
    }
    m5 = ActCfgTableEvalPendingPrmtFlags_221380(a->m428, a->mA0C, CharaGetCurMotionName_238560(a), CharaGetMotionFrame_238570(a));
    m7 = getA(a);
    m5 = m5 | 0x20000000;
    m7 = m7 | 0x0040000030000000ULL;
    a->m570 = a->m568 & m7;
    switch (a->mA34) {
    case 999:
        if (a->mA36 == 9) {
            goto do9;
        }
        if (a->mA36 == 10) {
        do9:
            if (CharaHasLandedMaybe_20fdb0(a) != 0) {
                f20 = CharaTableGetIntRate_2253f0(s4);
                CharaSetActionModeMoveMotion_21bbb0(a);
                a->mA34 = 0xCB;
                a->mA10 = f20;
                CharaActMoveMotion_21b180(a, arg1);
                return;
            }
        }
        if (IsInBattle_288420() != 0 && CharaTryStartAction_216700(a, arg1) != 0) {
            return;
        }
        if (CharaPlayedMotionIsCurrent_2124c0(a) == 0) {
            goto tail;
        }
        fl = CharaActionGetCancelMaskMaybe_210b60(a);
        if (fl & 1) {
            n = a->mA20 + 1;
            a->mA20 = n;
            if (n < CharaTableGetStepCount_225410(s4) && (s0 = CharaTableEntryAt_225420(s4, n), s0 != 0)) {
                CharaPlayMotion_212590(a, a->m3F4, CharaTableDataGetMotionName_2269e0(s0), CharaTableEntryGetMotionFlags_226240(s0), 1.0f);
                a->mA24 = 0.0f;
                if (CharaTableEntryGetEndType_226100(s0) == 1) {
                    t = CharaTableEntryGetWaitFrameParam_2260c0(s0, 1);
                    f20 = RandFloat_13c010();
                    a->mA24 = 0.0f + (f32)CharaTableEntryGetWaitFrameParam_2260c0(s0, 0) + f20 * t;
                }
                a->mA34 = 999;
                a->mAD0 = 0;
                a->mAD4 = 0;
                return;
            }
        }
        go = false;
        if (fl & 2) {
            go = true;
        } else if ((fl & 4) && IsInBattle_288420() == 0 && a->mA36 != 0 && a->mA36 != 0x1D) {
            go = true;
        }
        if (go) {
            f20 = CharaTableGetIntRate_2253f0(s4);
            CharaResetToBaseMode_21e830(a);
            v = CharaGetId_214a80(a);
            ActCfgTableRunExitEvnt_222430(a->m428, v, CharaTableGetName_225480(s4));
            if (CharaIsActionActive_215040(a) == 0) {
                a->mA10 = f20;
                CharaActLoco_21cc10(a, arg1);
            } else {
                CharaActionUpdateMaybe_215ca0(a, arg1);
            }
            return;
        }
        switch (a->mA36) {
        case 0xB:
        case 0x10:
            break;
        default:
            if (CharaInputInterruptMaybe_21e8f0(a, arg1) != 0) {
                return;
            }
            break;
        }
        break;
    default:
        CharaPlayMotion_212590(a, a->m3F4, CharaTableDataGetMotionName_2269e0(s0), CharaTableEntryGetMotionFlags_226240(s0), a->mA10);
        a->mA34 = 999;
        a->mA36 = CharaTableGetActionKind_225d30(s4);
        a->mAD0 = 0;
        a->mAD4 = 0;
        a->mA24 = 0.0f;
        if (CharaTableEntryGetEndType_226100(s0) == 1) {
            t = CharaTableEntryGetWaitFrameParam_2260c0(s0, 1);
            f20 = RandFloat_13c010();
            a->mA24 = 0.0f + (f32)CharaTableEntryGetWaitFrameParam_2260c0(s0, 0) + f20 * t;
        }
        if (a->mA3C != 0xB) {
            a->mADC = 0;
        }
        if (a->mA36 == 0xF) {
            a->m920 = 0;
        }
        m5 |= (u64)0x60000000 << 32;
        CharaClearActionEffects_214ce0(a);
        ActDataRunEvnts_225b70(s4, CharaGetId_214a80(a));
        if (a->mA36 == 0x16) {
            goto do16;
        }
        if (a->mA36 == 0x17) {
        do16:
          if (CharaGetId_214a80(a) >= 0x80 && CharaGetId_214a80(a) < 0x9C && *arg1 != 0) {
            NodeRefObjCtor_318ff0(&obj, 1, CharaGetId_214a80(a), 0x801, 45.0f);
            tb = D_004BCB20[CharaGetId_214a80(a)];
            sub = obj.sub;
            if (CharaGetId_214a80(a) >= 0 && CharaGetId_214a80(a) < 0xC) {
                {
                    s32 r2 = CharaGetBaseActionMode_213830(a);
                    s32 v2;
                    if (r2 == 3) v2 = 1; else v2 = 0;
                    f = (u8)v2;
                }
                ExecInfoInitFromChara_3a7830(sub, CharaGetId_214a80(a), (u8)f, 0, tb);
            } else if (CharaGetId_214a80(a) >= 0x80 && CharaGetId_214a80(a) < 0x9C) {
                ExecInfoInitFromObj_3a7790(sub, CharaGetId_214a80(a), tb);
            }
            {
                f32 k = D_0045B080[0];
                f20 = D_0047DB14 * k;
            }
            n = 0;
            while ((nd = ObjFindNthAttachPoint_1addc0(a->m3F4, 0x78, n)) != 0) {
                n++;
                if (nd->mC != 0) {
                    p = (s32 *)ModelGetFrame_1511f0(a->m3F4, nd->m0);
                    if (p != 0) {
                        *(V4 *)&col = D_0047E640;
                        NodeRefObjAddClsnPnt_318ca0(&obj, NodeRefListAdd_318d50(&obj, CharaGetId_214a80(a), -1, *p, -1, &col), 0, 0.0f, 1.25f * nd->m10 * f20);
                    }
                }
            }
            NodeRefObjCloneAndRegister_219500(&obj);
            obj.vptr = D_00471AA0;
        }
        }
    }
tail:
    if (a->m570 & 0x40000000) {
        a->m570 |= m7 & 0x1000;
        CharaSetMoveDirXYZMaybe_213a90(a, a->m470 - a->m70, 0.0f, a->m478 - a->m78);
    } else {
        a->m570 |= m7 & 0x800;
        switch (a->mA36) {
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 12:
        case 13:
        case 14:
            if (a->m570 & 0x800) {
                if (!(a->mA44 & 0x8000)) {
                    if (a->m568 & 3) {
                        CharaSetMoveDirXYZMaybe_213a90(a, a->m440, 0.0f, a->m448);
                        a->m570 |= 0x1000;
                    }
                } else {
                    CharaGetTargetPos_214a40(a, buf);
                    VecSub_1cbd00(&out, buf, &a->m70);
                    CharaSetMoveDirXYZMaybe_213a90(a, out.x, 0.0f, out.z);
                    a->m570 |= 0x1000;
                }
            }
            break;
        case 16:
        case 18:
            if (a->m570 & 3) {
                CharaSetMoveDirXYZMaybe_213a90(a, a->m440, 0.0f, a->m448);
                if (a->mA36 == 0x12) {
                    a->m570 &= ~3;
                }
            }
            break;
        }
    }
    switch (a->mA32) {
    case 5:
        a->m42C = ActCfgTableFindMoveById_223080(a->m428, 5);
        break;
    }
    switch (a->mA36) {
    case 2:
        a->m42C = ActCfgTableFindMoveById_223080(a->m428, 4);
        break;
    case 6:
    case 7:
    case 8:
    case 13:
    case 14:
    case 12:
        a->m42C = ActCfgTableFindMoveById_223080(a->m428, 0x64);
        break;
    case 9:
    case 10:
        a->m42C = ActCfgTableFindMoveById_223080(a->m428, 4);
        break;
    case 11:
        a->m42C = ActCfgTableFindMoveById_223080(a->m428, 0x69);
        break;
    case 16:
        a->m42C = ActCfgTableFindMoveById_223080(a->m428, 0x6A);
        break;
    case 18:
        a->m42C = ActCfgTableFindMoveById_223080(a->m428, 0x6A);
        break;
    }
    if (CharaTableEntryGetEndType_226100(s0) == 4) {
        a->m3D0 &= 0xFFFFBFFFFFFFFFFFULL;
        a->m3D0 &= 0xFFF7FFFFFFFFFFFFULL;
    }
    a->m3D0 |= (u64)0x04000000 << 32;
    a->m568 &= m5;
}
