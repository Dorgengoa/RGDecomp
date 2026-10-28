/* rgp:protos */
#line 1
#include "types.h"

typedef rg_u128 u128;

struct Vec4 {
    f32 x, y, z, w;
};

struct T30 {
    s16 a;
    s16 b;
    s32 w[11];
};

struct CamBase {
    u8 pad[0xC0];
};

class Actor {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 Can(s32 a0) { return VCM(s32, (void *, s32), 0x6C, a0); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v100() { VCM0(void, 0x100); }
    
    
    
    void v110() { VCM0(void, 0x110); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v1E0() { VCM0(void, 0x1E0); }
    
    
    
    
    
    
    
    
    
    
    
    
    f32 Speed() { return VCM0(f32, 0x214); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v274(s32 a0) { return VCM(s32, (void *, s32), 0x274, a0); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void Turn() { VCM0(void, 0x334); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 Accept(s32 a0) { return VCM(s32, (void *, s32), 0x44C, a0); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v4C8() { return VCM0(s32, 0x4C8); }
};

class Cam : public CamBase {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    f32 Yaw() { return VCM0(f32, 0xBC); }
};

struct Sub18 {
    u8 pad[0x18E];
    s16 id;              /* 0x18E */
};

struct Ctl {
    u8 pad0[0x18];
    Sub18 *s;            /* 0x18 */
    s32 f1C;             /* 0x1C */
    s32 f20;             /* 0x20 */
};

struct Unit {
    u8 pad0[0x3D0];
    u64 d3D0;            /* 0x3D0 */
    u8 pad3D8[0xA44 - 0x3D8];
    u32 fA44;            /* 0xA44 */
};

struct Mgr {
    u8 pad0[0x38];
    u32 f38;             /* 0x38 */
};

struct It4 {
    s32 w0;
    volatile s16 s4;
};

extern "C" {
s32 GetCurrentScene_1f5be0(void);
s32 ObjRecGetLiveObject_1c4a90(s32, s32);
Cam *ObjRecGetLiveObject_1c3bc0(s32, s32);
Unit *ActionMgrFindById_233b50(Mgr *, s32);
s32 CharaGetActionTable_214cd0(Unit *);
Ctl *GetGameData_1fede0(void);
Actor *ActorFindById_3eb870(Ctl *, s32);
u64 CharaGetFlags_2124b0(Unit *);
T30 *CharaGetTargetRef_214a30(Unit *);
void TargetRefClear_2e71d0(T30 *);
void CharaGetPos_2388a0(Unit *, Vec4 *);
void CharaGetRot_2388b0(Unit *, Vec4 *);
s32 CharaGetId_214a80(Unit *);
s32 GetTargetMng_313dd0(void);
T30 *TargetMngGetTargetRef_320820(s32);
void TargetRefGetPos_2e6a60(T30 *, Vec4 *);
s32 TargetMngHasTargetId_313bf0(void);
s32 GetGameMode_1f59c0(void);
s32 GetGameModePhase_1f59b0(void);
s32 CharaSysStateUnitFlag7EBit3Related_3a38e0(s32);
s32 CharaCanLiftMaybe_2106c0(Unit *);
Actor * ActorCastToChara_3b87b0(Actor *, int, int, int);
f32 CharaGetCollRadius_2386a0(Unit *);
s32 ActionMgrFindLiftableInFrontMaybe_232de0(Mgr *, Vec4 *, f32, f32);
void FieldHudWidget80LiftOpenMaybe_203f60(void);
s32 PadIsTriggered_1839f0(void *, s32);
s32 PadIsHeld_183a20(void *, s32);
void GameFlowResetChainReq_285f60(void);
void GameFlowSetChainCharaId_285f10(s32);
void GameFlowSetChainTargetId_285f00(s32);
void GameReqQueuePushBack_1f5b50(s32, s32);
void FieldHudWidget80LiftCloseMaybe_203f50(s32);
f32 PadGetAnalogLXNorm_183af0(void *);
f32 PadGetAnalogLYNorm_183a50(void *);
f32 Cosf_128d30(f32);
f32 Sinf_128fd0(f32);
f32 VecLengthSq_1cb470(Vec4 *, void *);
void VecNormalize_1cbb80(Vec4 *, Vec4 *);
f32 Atan2f_1291a8(f32, f32);
void CharaSetStickDirXYZMaybe_213ab0(Unit *, f32, f32, f32);
void CharaGetDirMaybe_214a60(Unit *, Vec4 *);
void CharaSetDirNormalizedMaybe_213b30(Unit *, Vec4 *);
void VecCopy_1cbe30(Vec4 *, Vec4 *);
f32 VecDot3_1cba90(Vec4 *, Vec4 *);
It4 *CharaGetEvObjContact_214990(Unit *);
s32 GetEventObjMgr_2d1960(void);
s32 EventObjMgrFindObjByName_2e9920(s32, s32, s32);
s32 EvObjLiftGetPlayState_336120(s32);
void GameSceneSoundSlot0PlaySeVol_1d05f0(s32, s32, f32);
s32 CharaActFlagsDirBitsMaybe_20a5a0(int);
void CharaSetSpeedScale_238230(Unit *, f32);
s32 IsInBattle_288420(void);
s32 TargetRefGetKind_2e7130(T30 *);
s32 TargetRefGetId_2e7120(T30 *);
s32 CharaIsInKnockbackMotionMaybe_214db0(Unit *);
f32 VecDistSq_1cb3c0(Vec4 *, Vec4 *);
f32 AngleWrap_1cbf30(f32);
void CameraQueueEyeYaw_161220(Cam *, f32);
void TargetRefCtor_2e71f0(T30 *);
s32 TargetFindInFrontMaybe_2d0aa0(T30 *, Vec4 *, f32, f32);
s32 CharaCanPickFrontTargetMaybe_2107c0(Unit *);
void FieldHudWidget7FOpen_203f90(s32);
void FieldHudWidget7FClose_203f80(void);
T30 *CharaGetFrontTargetRefMaybe_214a20(Unit *);
Actor *ObjFindById_3bb3a0(s32, s32);
void CharaHeadPopupSpawnMaybe_2ef810(s32);
void CharaSysEventLogRecordOpenHud_3a3260(s32, s32, s32, s32, s32);
void CharaSetPosVec_2387a0(Unit *, Vec4 *);
void CharaSetFlags_212470(Unit *, u64);
void CharaGetHoldDir_2143b0(Unit *, Vec4 *);
void CharaSetHoldDir_214390(Unit *, Vec4 *);
void CharaSetHoldFlags_214270(Unit *, u64);
extern Mgr D_004B8680;
extern u8 D_004B2570[];
extern f32 D_0045B080[];
extern f32 D_0047E4A0;
extern f32 D_0047E4A4;
extern f32 D_0047E4A8;
extern f32 D_0047E4AC;
extern f32 D_0047DC3C;
extern f32 D_0047DC40;
extern f32 D_0047D1FC;
}

#define ZERO16(v) { u8 *p_ = (u8 *)&(v); u32 n_ = 0x10; if (p_) { while (n_) { *p_ = 0; n_--; p_++; } } }

extern "C" void PlayerControlUpdateMaybe_1fc4a0(void *pad, s32 id) {
    Vec4 p200 __attribute__((aligned(16)));
    Vec4 r1F0 __attribute__((aligned(16)));
    Vec4 v1E0 __attribute__((aligned(16)));
    Vec4 p1D0 __attribute__((aligned(16)));
    Vec4 r1C0 __attribute__((aligned(16)));
    Vec4 mv __attribute__((aligned(16)));
    Vec4 m1A0 __attribute__((aligned(16)));
    Vec4 m190 __attribute__((aligned(16)));
    Vec4 p180 __attribute__((aligned(16)));
    Vec4 p170 __attribute__((aligned(16)));
    Vec4 r160 __attribute__((aligned(16)));
    T30 t130 __attribute__((aligned(16)));
    Vec4 p120 __attribute__((aligned(16)));
    Vec4 v110 __attribute__((aligned(16)));
    Vec4 v100 __attribute__((aligned(16)));
    Mgr *mgr;
    s32 w;
    bool ok2;
    bool locked;
    Unit *u;
    Ctl *ctl;
    Actor *act;
    f32 lx;
    f32 ly;
    u64 flags;
    T30 *tgt;
    T30 *x;
    Actor *a;
    Unit *o;
    s32 r;
    s32 k;
    s32 q;
    s32 id2;
    bool ok;
    Cam *cam;
    Actor *z;
    f32 ang;
    bool isMe;
    f32 c;
    f32 s;
    f32 mag;
    f32 d1;
    f32 d2;
    f32 f21;
    f32 f20;
    f32 f22;

    if (pad == 0) return;
    w = GetCurrentScene_1f5be0();
    if (ObjRecGetLiveObject_1c4a90(w, id) == 0) return;
    cam = ObjRecGetLiveObject_1c3bc0(w, *(s32 *)(w + 0x4344));
    if (cam == 0) return;
    mgr = &D_004B8680;
    u = ActionMgrFindById_233b50(mgr, id);
    if (u == 0) return;
    if (CharaGetActionTable_214cd0(u) == 0) return;
    ctl = GetGameData_1fede0();
    act = ActorFindById_3eb870(ctl, id);
    if (act == 0) return;
    isMe = id == ctl->s->id;
    flags = CharaGetFlags_2124b0(u);
    tgt = CharaGetTargetRef_214a30(u);
    TargetRefClear_2e71d0(tgt);
    CharaGetPos_2388a0(u, &p200);
    CharaGetRot_2388b0(u, &r1F0);
    v1E0.x = D_0047E4A0;
    v1E0.y = D_0047E4A4;
    v1E0.z = D_0047E4A8;
    v1E0.w = D_0047E4AC;
    {
        s32 me = ctl->s->id;
        s32 owner = ((short)CharaGetId_214a80(u));
        if (owner == me) {
            x = TargetMngGetTargetRef_320820(GetTargetMng_313dd0());
            if (x != 0) {
                TargetRefGetPos_2e6a60(x, &v1E0);
                u->fA44 |= 0x8000;
                *tgt = *x;
                if (((unsigned char)TargetMngHasTargetId_313bf0()) != 0) flags |= 0xC0000000ULL;
            }
        }
    }
    locked = 0;
    if (GetGameMode_1f59c0() == 7 && GetGameModePhase_1f59b0() == 0xC9 && CharaSysStateUnitFlag7EBit3Related_3a38e0(ctl->f20) != 0 &&
        (((u->d3D0 & 0x0080000000000000ULL) != 0) ^ 1) && CharaCanLiftMaybe_2106c0(u) != 0) {
        a = ActorCastToChara_3b87b0(act, 0, 0, 0);
        if (a != 0 && a->v274(-1) != 0 && a->Can(0) != 0 && a->v4C8() != 0) {
            CharaGetPos_2388a0(u, &p1D0);
            CharaGetRot_2388b0(u, &r1C0);
            r = ActionMgrFindLiftableInFrontMaybe_232de0(mgr, &p1D0, r1C0.y, CharaGetCollRadius_2386a0(u) + 1.5f * D_0045B080[0]);
            if (r >= 0) {
                FieldHudWidget80LiftOpenMaybe_203f60();
                locked = 1;
                if (PadIsTriggered_1839f0(D_004B2570, 0x80) != 0 && PadIsHeld_183a20(D_004B2570, 8) != 0) {
                    GameFlowResetChainReq_285f60();
                    GameFlowSetChainCharaId_285f10(ctl->s->id);
                    GameFlowSetChainTargetId_285f00(r);
                    GameReqQueuePushBack_1f5b50(9, -1);
                    FieldHudWidget80LiftCloseMaybe_203f50(0);
                    return;
                }
            }
        }
    }
    if (!locked) FieldHudWidget80LiftCloseMaybe_203f50(1);
    ang = cam->Yaw();
    lx = PadGetAnalogLXNorm_183af0(pad);
    ly = PadGetAnalogLYNorm_183a50(pad);
    ZERO16(mv);
    c = Cosf_128d30(ang);
    mv.x = ly * Sinf_128fd0(ang) + lx * c;
    s = Sinf_128fd0(ang);
    mv.z = ly * Cosf_128d30(ang) + -lx * s;
    if (!(VecLengthSq_1cb470(&mv, 0) <= 1.0f)) VecNormalize_1cbb80(&mv, &mv);
    if (flags & 0x40000000) {
        f22 = Atan2f_1291a8(v1E0.x - p200.x, v1E0.z - p200.z);
        m1A0.x = Sinf_128fd0(f22);
        m1A0.y = 0.0f;
        m1A0.z = Cosf_128d30(f22);
        m1A0.w = 0.0f;
        m190.x = m1A0.z;
        m190.y = 0.0f;
        m190.w = 0.0f;
        m190.z = -m1A0.x;
    } else {
        m1A0.x = Sinf_128fd0(r1F0.y);
        m1A0.y = 0.0f;
        m1A0.z = Cosf_128d30(r1F0.y);
        m1A0.w = 0.0f;
        m190.x = m1A0.z;
        m190.y = 0.0f;
        m190.w = 0.0f;
        m190.z = -m1A0.x;
    }
    mag = mv.x * mv.x + mv.z * mv.z;
    flags &= ~0x7F8ULL;
    if (!(mag < D_0047DC3C)) {
        flags |= 1;
        if (!(mag < D_0047DC40)) flags |= 2;
        CharaSetStickDirXYZMaybe_213ab0(u, lx, ly, 0.0f);
        d1 = (ly < 0.0f) ? -ly : ly;
        lx = (f32)lx;
        d2 = (lx < 0.0f) ? -lx : lx;
        if (!(d1 < d2)) {
            if (ly < 0.0f) flags |= 0x20;
            else flags |= 0x40;
        } else {
            if (lx < 0.0f) flags |= 8;
            else flags |= 0x10;
        }
        f21 = VecDot3_1cba90(&mv, &m1A0);
        f20 = VecDot3_1cba90(&mv, &m190);
        CharaSetDirNormalizedMaybe_213b30(u, &mv);
        d1 = (f21 < 0.0f) ? -f21 : f21;
        d2 = (f20 < 0.0f) ? -f20 : f20;
        if (!(d1 < d2)) {
            if (!(f21 <= 0.0f)) flags |= 0x200;
            else flags |= 0x400;
        } else {
            if (!(f20 <= 0.0f)) flags |= 0x80;
            else flags |= 0x100;
        }
    } else {
        CharaSetStickDirXYZMaybe_213ab0(u, 0.0f, 0.0f, 0.0f);
        CharaGetDirMaybe_214a60(u, &mv);
        if (VecLengthSq_1cb470(&mv, 0) == 0.0f) {
            CharaSetDirNormalizedMaybe_213b30(u, &m1A0);
            VecCopy_1cbe30(&mv, &m1A0);
        }
    }
    flags |= 0x18000000;
    if (PadIsTriggered_1839f0(pad, 0x40) != 0) flags |= 0x2000;
    if (PadIsTriggered_1839f0(pad, 0x20) != 0) flags |= 0x4000;
    if ((act == 0 || act->Can(3) != 0) && PadIsTriggered_1839f0(pad, 0x20) != 0) {
        ok = 1;
        {
        It4 *it = CharaGetEvObjContact_214990(u);
        if (it->s4 == 4) {
            q = EventObjMgrFindObjByName_2e9920(GetEventObjMgr_2d1960(), it->w0, it->s4);
            if (q != 0 && ((short)EvObjLiftGetPlayState_336120(q)) == 5) {
                ok = 0;
                GameSceneSoundSlot0PlaySeVol_1d05f0(w, 0x2B, 1.0f);
            }
        }
        }
        if (ok) flags |= 0x10000;
    }
    if ((act == 0 || act->Can(6) != 0) && PadIsTriggered_1839f0(pad, 0x40) != 0) flags |= 0x80000;
    if (act == 0 || act->Can(5) != 0) {
        if (PadIsTriggered_1839f0(pad, 0x40) != 0) flags |= 0x20000;
        if (PadIsTriggered_1839f0(pad, 0x20) != 0) {
            if ((flags & 3) && CharaActFlagsDirBitsMaybe_20a5a0((int)(flags)) == 0x40) {
                flags |= 0x40000;
            } else {
                flags |= 0x20000;
            }
        }
        u->d3D0 &= ~0x0400000000000000ULL;
    } else {
        u->d3D0 |= 0x0400000000000000ULL;
    }
    if (act != 0) {
        CharaSetSpeedScale_238230(u, act->Speed());
    } else {
        CharaSetSpeedScale_238230(u, 1.0f);
    }
    if (((unsigned char)IsInBattle_288420()) != 0) {
        if (PadIsTriggered_1839f0(pad, 0x40) != 0) flags |= 0x0080000000000000ULL;
        if (PadIsTriggered_1839f0(pad, 0x80) != 0) flags |= 0x0100000000000000ULL;
        if (PadIsTriggered_1839f0(pad, 0x400) != 0) flags |= 0x0200000000000000ULL;
        if (PadIsHeld_183a20(pad, 0x40) != 0) flags |= 0x0040000000000000ULL;
        if (PadIsHeld_183a20(pad, 0x80) != 0) flags |= 0x1000000000000000ULL;
        if (u->fA44 & 0x8000) {
            switch (((short)TargetRefGetKind_2e7130(tgt))) {
            case 2:
            case 4:
                o = ActionMgrFindById_233b50(mgr, ((short)TargetRefGetId_2e7120(tgt)));
                if (o != 0 && !(o->fA44 & 0x80000) && CharaIsInKnockbackMotionMaybe_214db0(o) != 0) {
                    CharaGetPos_2388a0(o, &p180);
                    f32 kk = D_0045B080[0];
                    kk = 1.5f * (f32)kk;
                    f32 ra = CharaGetCollRadius_2386a0(o);
                    f32 sa = kk + (ra + CharaGetCollRadius_2386a0(u));
                    f32 rb = CharaGetCollRadius_2386a0(o);
                    f32 lim = sa * (kk + (rb + CharaGetCollRadius_2386a0(u)));
                    if (VecDistSq_1cb3c0(&p180, &p200) <= lim && (flags & 0x0080000000000000ULL)) {
                        flags |= 0x0400000000000000ULL;
                    }
                }
                break;
            }
        }
        if (PadIsHeld_183a20(pad, 8) != 0) flags |= 0x100000000ULL;
        if (PadIsTriggered_1839f0(pad, 8) != 0 && isMe && (flags & 0x40000000)) {
            CameraQueueEyeYaw_161220(cam, AngleWrap_1cbf30(D_0047D1FC + r1F0.y));
        }
        if (((u->d3D0 & 0x0080000000000000ULL) != 0) ^ 1) {
            if (act->Can(0) != 0) {
                CharaGetPos_2388a0(u, &p170);
                CharaGetRot_2388b0(u, &r160);
                TargetRefCtor_2e71f0(&t130);
                r = TargetFindInFrontMaybe_2d0aa0(&t130, &p170, r160.y, CharaGetCollRadius_2386a0(u) + 1.5f * D_0045B080[0]);
                switch (r) {
                case 1:
                    if (CharaCanPickFrontTargetMaybe_2107c0(u) != 0) {
                        if (!locked) {
                            FieldHudWidget7FOpen_203f90(1);
                        } else {
                            FieldHudWidget7FClose_203f80();
                        }
                        if (PadIsHeld_183a20(pad, 8) != 0 && PadIsTriggered_1839f0(pad, 0x40) != 0) {
                            *CharaGetFrontTargetRefMaybe_214a20(u) = t130;
                            FieldHudWidget7FClose_203f80();
                            ok2 = 1;
                            if (((short)TargetRefGetKind_2e7130(&t130)) == 2) {
                                id2 = ((short)TargetRefGetId_2e7120(&t130));
                                z = ObjFindById_3bb3a0(ctl->f1C, id2);
                                if (z == 0 || z->Accept((s32)ActorCastToChara_3b87b0(act, 0, 0, 0)) == 0) {
                                    CharaHeadPopupSpawnMaybe_2ef810(id);
                                    CharaSysEventLogRecordOpenHud_3a3260(ctl->f20, 0x7FFA, id2, 0x4D, 1);
                                    ok2 = 0;
                                }
                            }
                            if (ok2) {
                                flags |= 0x100000;
                            } else {
                                GameSceneSoundSlot0PlaySeVol_1d05f0(GetCurrentScene_1f5be0(), 0x2A, 1.0f);
                                flags |= 0x20000000000ULL;
                            }
                        }
                    } else {
                        FieldHudWidget7FClose_203f80();
                    }
                    break;
                case 0:
                    if (CharaCanPickFrontTargetMaybe_2107c0(u) != 0) {
                        if (!locked) {
                            FieldHudWidget7FOpen_203f90(0);
                        } else {
                            FieldHudWidget7FClose_203f80();
                        }
                        if (PadIsHeld_183a20(pad, 8) != 0 && PadIsTriggered_1839f0(pad, 0x40) != 0) {
                            FieldHudWidget7FClose_203f80();
                        }
                    } else {
                        FieldHudWidget7FClose_203f80();
                    }
                    break;
                default:
                    FieldHudWidget7FClose_203f80();
                    break;
                }
            }
        }
        if (PadIsTriggered_1839f0(pad, 0x80) != 0) flags |= 0x200000;
        if (PadIsTriggered_1839f0(pad, 0x20) != 0) flags |= 0x400000;
    } else {
        flags |= 0x400000;
    }
    if (mgr->f38 & 0x40000000) {
        CharaGetPos_2388a0(u, &p120);
        if (PadIsHeld_183a20(pad, 0x1000) != 0) p120.y = p120.y + 10.0f;
        if (PadIsHeld_183a20(pad, 0x4000) != 0) p120.y = p120.y - 10.0f;
        CharaSetPosVec_2387a0(u, &p120);
    }
    CharaSetFlags_212470(u, flags);
    CharaGetDirMaybe_214a60(u, &v110);
    CharaGetHoldDir_2143b0(u, &v100);
    CharaSetHoldDir_214390(u, &v110);
    CharaSetHoldFlags_214270(u, flags);
    if (VecDot3_1cba90(&v110, &v100) < -0.5f) act->Turn();
}
