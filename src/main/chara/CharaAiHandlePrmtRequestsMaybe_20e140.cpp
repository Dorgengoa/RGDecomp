#include "types.h"

class Mgr20e {
public:
    virtual void e0();
    virtual void e1();
    virtual void e2();
    virtual void e3();
    virtual void e4();
    virtual void e5();
    virtual void e6();
    virtual void e7();
    virtual void e8();
    virtual void e9();
    virtual void e10();
    virtual void e11();
    virtual void e12();
    virtual void e13();
    virtual void e14();
    virtual void e15();
    virtual void e16();
    virtual void e17();
    virtual void e18();
    virtual void e19();
    virtual void e20();
    virtual void e21();
    virtual void e22();
    virtual void e23();
    virtual void e24();
    virtual void e25();
    virtual void e26();
    virtual void e27();
    virtual void e28();
    virtual void e29();
    virtual void e30();
    virtual void e31();
    virtual void e32();
    virtual void e33();
    virtual void e34();
    virtual void e35();
    virtual void e36();
    virtual void e37();
    virtual void e38();
    virtual void e39();
    virtual void e40();
    virtual void e41();
    virtual void e42();
    virtual void e43();
    virtual void e44();
    virtual void e45();
    virtual void e46();
    virtual void e47();
    virtual void e48();
    virtual void e49();
    virtual void e50();
    virtual void e51();
    virtual void e52();
    virtual void e53();
    virtual void e54();
    virtual void e55();
    virtual void e56();
    virtual void e57();
    virtual void e58();
    virtual void e59();
    virtual void e60();
    virtual void e61();
    virtual void e62();
    virtual void e63();
    virtual void e64();
    virtual void e65();
    virtual void e66();
    virtual void e67();
    virtual void e68();
    virtual void e69();
    virtual void e70();
    virtual void e71();
    virtual void e72();
    virtual void e73();
    virtual void e74();
    virtual void e75();
    virtual void e76();
    virtual void e77();
    virtual void e78();
    virtual void e79();
    virtual void e80();
    virtual void e81();
    virtual void e82();
    virtual void e83();
    virtual void e84();
    virtual void e85();
    virtual void e86();
    virtual void e87();
    virtual void e88();
    virtual void e89();
    virtual void e90();
    virtual void e91();
    virtual void e92();
    virtual void e93();
    virtual void e94();
    virtual void e95();
    virtual void e96();
    virtual void e97();
    virtual void e98();
    virtual void e99();
    virtual void e100();
    virtual void e101();
    virtual void e102();
    virtual void e103();
    virtual void e104();
    virtual void e105();
    virtual void e106();
    virtual void e107();
    virtual void e108();
    virtual void e109();
    virtual void e110();
    virtual void e111();
    virtual void e112();
    virtual void e113();
    virtual void e114();
    virtual void e115();
    virtual void e116();
    virtual void e117();
    virtual void e118();
    virtual void e119();
    virtual void e120();
    virtual void e121();
    virtual void e122();
    virtual void e123();
    virtual void e124();
    virtual void e125();
    virtual void e126();
    virtual void e127();
    virtual void e128();
    virtual void e129();
    virtual void e130();
    virtual void e131();
    virtual void e132();
    virtual void e133();
    virtual void e134();
    virtual void e135();
    virtual void e136();
    virtual void e137();
    virtual void e138();
    virtual void e139();
    virtual void e140();
    virtual void e141();
    virtual void e142();
    virtual void e143();
    virtual void e144();
    virtual void e145();
    virtual void e146();
    virtual void e147();
    virtual void e148();
    virtual void e149();
    virtual void e150();
    virtual void e151();
    virtual void e152();
    virtual void e153();
    virtual void e154();
    virtual s32 v274(s32);
};

typedef struct Ch20e {
    u8 pad0[0x3F4];
    s32 m3F4;
    u8 pad3F8[0x424 - 0x3F8];
    s16 m424;
    u8 pad426[2];
    s32 m428;
    u8 pad42C[0x568 - 0x42C];
    u64 m568;
    u8 pad570[0x590 - 0x570];
    u8 m590[0x6CC - 0x590];
    s16 m6CC;
    s16 m6CE;
    s16 m6D0;
    u8 pad6D2[0x898 - 0x6D2];
    s32 m898;
    s32 m89C;
    s32 m8A0;
    s32 m8A4;
    s32 m8A8;
    u8 pad8AC[0xA0C - 0x8AC];
    s32 mA0C;
    f32 mA10;
    s32 mA14;
    s32 mA18;
    s32 mA1C;
    s32 mA20;
    s32 mA24;
    u8 mA28;
    u8 padA29[0xA2E - 0xA29];
    s16 mA2E;
    s16 mA30;
    s16 mA32;
    s16 mA34;
    s16 mA36;
    s16 mA38;
    u8 padA3A[0xA44 - 0xA3A];
    s32 mA44;
    u8 padA48[0xA68 - 0xA48];
    s8 mA68;
    u8 padA69[0xA88 - 0xA69];
    f32 mA88;
    u8 padA8C[0xAAC - 0xA8C];
    u8 mAAC[0xB20 - 0xAAC];
    s32 mB20;
    u8 mB24[0xB44 - 0xB24];
    s16 mB44;
    s16 mB46;
    u8 padB48[4];
    s16 mB4C;
    s16 padB4E;
    s16 mB50;
} Ch20e;

extern "C" {
void FrameSetDirty_14a5e0(u8 *);
u8 *ModelGetRootFrame_1511a0(s32);
s32 ModelGetFrame_1511f0(s32, s32);
s32 ModelFindFrameIndexByName_151220(s32, s32);
s32 ScriptVmHasLabel_1768f0(s32, s32);
s32 ObjRecGetFlags_1c3d90(s32, s32, s32);
s32 ObjRecGetLiveObject_1c4a90(s32, s32);
s32 GetCurrentScene_1f5be0(void);
s32 GetActionMgr_1fdb50(void);
s32 GetGameData_1fede0(void);
void CharaActionStepSimpleMaybe_215ae0(Ch20e *, s32 *);
void CharaBeginActionStateMaybe_215c50(Ch20e *);
s32 ActCfgTableResolveActionAlias_223730(s32, s32, s32, u8 *, s8 *);
s32 ActCfgTableFindActionByName_223d20(s32, s32);
s32 CharaTableGetStepArray_225470(s32);
s32 CharaTableGetName_225480(s32);
Ch20e *ActionMgrFindById_233b50(s32, s32);
s32 AiIsScriptVmEnabled_2bb4c0(u8 *, s32);
s32 AiGetScriptVm_2bb4f0(u8 *, s32);
void AiSetState2_2bb510(u8 *, s32);
void AiSetState_2bb520(u8 *, s32);
void AiSetStateOnBarrierReqMaybe_2bb530(u8 *);
void AiSetStateOnReflectReqMaybe_2bb540(u8 *);
void AiRetargetOnHitReqMaybe_2bb590(u8 *, s32, s32, s32, s32, s32);
void AiRollIdleOnContactMaybe_2bb770(u8 *, s32, s32);
void AiRetargetOnDeadReqMaybe_2bba70(u8 *, s32, s32);
void AiRetargetOnDamageReqMaybe_2bba80(u8 *, s32, s32, s32, s32, s32);
s32 AiUpdate_2c05b0(u8 *, Ch20e **);
s32 AiGetTargetCharaId_2c0fd0(u8 *);
Mgr20e *ActorFindById_3eb870(s32, s32);
void CharaAiHandlePrmtRequestsMaybe_20e140(Ch20e *o);
}

static inline bool NotF100000(Ch20e *o) { return !((o->mA44 & 0x100000) != 0); }

static inline bool IsSide(Ch20e *o) { return o->mA2E == 2 || o->mA2E == 3; }

static inline bool CanAct(Ch20e *o)
{
    switch (o->mA36) {
    case 0xF:
    case 0x13:
    case 0x1E:
    case 0x1F:
        return false;
    }
    if (o->mA38 == 0) {
        switch (o->mA32) {
        case 0xA:
        case 0x12:
            return false;
        }
    }
    if (!IsSide(o)) {
        switch (o->mB4C) {
        case 1:
        case 2:
            return false;
        }
    }
    if (IsSide(o)) {
        switch (o->mB50) {
        case 2:
        case 3:
            return false;
        }
    }
    return true;
}

void CharaAiHandlePrmtRequestsMaybe_20e140(Ch20e *o)
{
    Ch20e *self;
    Ch20e *self2;
    s32 unk[2];
    u64 flags;
    s32 sys;
    Ch20e *tgt;
    u64 mask;
    bool done;
    bool hit;
    s32 q;
    s32 r;
    u8 *e;
    s32 id;
    s32 d;
    f32 f;
    s32 t;
    Mgr20e *m;

    if (!(o->mA44 & 0x40000000)) {
        return;
    }
    flags = o->m568;
    if (o->mA44 & 0x80000) {
        o->m568 = 0;
    }
    if (o->m3F4 == 0) {
        return;
    }
    sys = GetCurrentScene_1f5be0();
    if (!(o->mA44 & 0x80000) && !(ObjRecGetFlags_1c3d90(sys, 1, o->m424) & 0x800000)) {
        return;
    }
    {
        bool b = o->mA32 != 0x11 && (flags & 0x0000080000000000ULL);
        if (!b) {
            if (!(o->mA44 & 0x1000000) || (o->mA44 & 0x800000)) {
                return;
            }
            if (o->mA44 & 0x40) {
                return;
            }
            if (o->mA44 & 0x20) {
                return;
            }
            if (o->mA32 == 0xA) {
                return;
            }
            if (o->mA32 == 0x12) {
                return;
            }
            switch (o->mA36) {
            case 0x15:
            case 0x16:
            case 0x17:
            case 0x13:
            case 0x1E:
            case 0x1F:
                return;
            }
        }
    }
    tgt = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), AiGetTargetCharaId_2c0fd0(o->m590));
    mask = 0x0017C7FC00000000ULL;
    if (o->m424 >= 0x80 && o->m424 < 0x9C) {
        mask &= ~0x0000040000000000ULL;
    }
    if (o->mA36 == 0x10) {
        mask &= ~0x0000020000000000ULL;
    }
    done = 0;
    if (o->mA32 != 0x11 && (flags & 0x0000080000000000ULL)) {
        AiRetargetOnDeadReqMaybe_2bba70(o->m590, o->m89C, o->m898);
        if (o->mA44 & 0x80000) {
            o->mA32 = 0x11;
        }
    } else if (flags & 0x0000040000000000ULL) {
        AiSetStateOnReflectReqMaybe_2bb540(o->m590);
    } else if (flags & 0x0004000000000000ULL) {
        AiSetStateOnBarrierReqMaybe_2bb530(o->m590);
    } else if (flags & mask) {
        hit = 0;
        if (AiIsScriptVmEnabled_2bb4c0(o->m590, 0)) {
            switch (o->m8A0) {
            case 0x262:
                if (ScriptVmHasLabel_1768f0(AiGetScriptVm_2bb4f0(o->m590, 0), 0x280)) {
                    AiSetState_2bb520(o->m590, 0x280);
                    hit = 1;
                    o->m6CC = o->m89C;
                    o->m6CE = o->m8A4;
                    o->m6D0 = o->m8A8;
                }
                break;
            case 0x13:
                if (ScriptVmHasLabel_1768f0(AiGetScriptVm_2bb4f0(o->m590, 0), 0x294)) {
                    AiSetState_2bb520(o->m590, 0x294);
                    hit = 1;
                    o->m6CC = o->m89C;
                    o->m6CE = o->m8A4;
                    o->m6D0 = o->m8A8;
                }
                break;
            }
        }
        if (!hit) {
            if (NotF100000(o)) {
                AiRetargetOnDamageReqMaybe_2bba80(o->m590, o->m89C, o->m898, -1, o->m8A4, o->m8A8);
                o->m8A8 = -1;
            }
        }
    } else if (flags & 0x0000000200000000ULL) {
        hit = 0;
        if (AiIsScriptVmEnabled_2bb4c0(o->m590, 1)) {
            switch (o->m8A0) {
            case 0x262:
                if (ScriptVmHasLabel_1768f0(AiGetScriptVm_2bb4f0(o->m590, 1), 0x28A)) {
                    AiSetState2_2bb510(o->m590, 0x28A);
                    hit = 1;
                    o->m6CC = o->m89C;
                    o->m6CE = o->m8A4;
                    o->m6D0 = o->m8A8;
                }
                break;
            case 0x13:
                if (ScriptVmHasLabel_1768f0(AiGetScriptVm_2bb4f0(o->m590, 1), 0x29E)) {
                    AiSetState2_2bb510(o->m590, 0x29E);
                    hit = 1;
                    o->m6CC = o->m89C;
                    o->m6CE = o->m8A4;
                    o->m6D0 = o->m8A8;
                }
                break;
            }
        }
        if (!hit) {
            AiRetargetOnHitReqMaybe_2bb590(o->m590, o->m89C, o->m898, -1, o->m8A4, o->m8A8);
        }
    } else if (tgt != 0 && (tgt->mA44 & 2)) {
        if (o->mA36 != 0x12) {
            if (!(o->mA44 & 0x4000)) {
                AiRollIdleOnContactMaybe_2bb770(o->m590, tgt->m424, 0);
                o->mA44 |= 0x4000;
            }
            done = 1;
        }
    } else if (o->m424 >= 0 && o->m424 < 12 && o->mA36 != 0x12) {
        m = ActorFindById_3eb870(GetGameData_1fede0(), *(s16 *)((u8 *)o + 0x424));
        if (m != 0 && m->v274(-1) == 0) {
            AiRollIdleOnContactMaybe_2bb770(o->m590, -1, 1);
        }
    }
    if (!done) {
        o->mA44 &= ~0x4000;
    }
    if (o->mA44 & 0x80000) {
        if (o->mA32 != 0x11 && (flags & 0x0000080000000000ULL)) {
            o->mA32 = 0x11;
        }
        if (o->mA32 == 0x11 && (flags & 0x0000100000000000ULL)) {
            o->mA32 = 0;
        }
        q = ObjRecGetLiveObject_1c4a90(sys, o->mB20);
        if (q != 0) {
            r = ModelGetFrame_1511f0(q, ModelFindFrameIndexByName_151220(q, (s32)o->mB24));
            if (r != 0) {
                e = ModelGetRootFrame_1511a0(o->m3F4);
                e[0x28] = 1;
                *(s32 *)(e + 4) = r;
                FrameSetDirty_14a5e0(e);
            }
        }
        self = o;
        AiUpdate_2c05b0(o->m590, &self);
        if (o->m428 == 0) {
            return;
        }
        if (o->mA68 == 0) {
            return;
        }
        if (!CanAct(o)) {
            return;
        }
        id = ActCfgTableFindActionByName_223d20(o->m428, ActCfgTableResolveActionAlias_223730(o->m428, o->mB44, o->mB46, o->mAAC, &o->mA68));
        if (id != 0) {
        CharaBeginActionStateMaybe_215c50(o);
        d = CharaTableGetStepArray_225470(id);
        f = o->mA88;
        t = CharaTableGetName_225480(id);
        o->mA10 = 1.0f;
        o->mA0C = 0;
        o->mA20 = 0;
        o->mA24 = 0;
        o->mA28 = 0;
        o->mA1C = 0;
        o->mA14 = 0;
        o->mA18 = 0;
        o->mA0C = t;
        o->mA10 = f;
        o->mA14 = id;
        o->mA18 = d;
        o->mA1C = 0;
        CharaActionStepSimpleMaybe_215ae0(o, unk);
        }
        o->mA68 = 0;
    } else if (o->m428 != 0) {
        self2 = o;
        AiUpdate_2c05b0(o->m590, &self2);
    }
}
