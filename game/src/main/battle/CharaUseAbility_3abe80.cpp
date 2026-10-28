/* rgp:protos */
#line 1
#include "types.h"

struct Msg {
    s16 id;
    s16 pad2;
    s16 kind;
    s16 pad6;
    s32 pad8;
    s32 arg;
    u8 rest[0x60];
};

struct Big {
    u8 pad[0x48];
    s64 a;
    s64 b;
    s64 c;
    s64 d;
    u8 rest[0x28];
};

struct Flags {
    u8 b0 : 3;
    u8 b3 : 1;
    u8 b4 : 4;
};

class BObj;
class AObj {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    void v38() { VCM0(void, 0x38); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 vBC() { return VCM0(s32, 0xBC); }
    s32 vC0() { return VCM0(s32, 0xC0); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v114(s32 a0) { VCM(void, (void *, s32), 0x114, a0); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v1BC(s32 a0, s32 a1, s32 a2, s32 a3) { VCM(void, (void *, s32, s32, s32, s32), 0x1BC, a0, a1, a2, a3); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v270(s32 a0) { VCM(void, (void *, s32), 0x270, a0); }
    
    
    
    void v280(struct Msg * a0) { VCM(void, (void *, struct Msg *), 0x280, a0); }
    void v284(struct Big * a0) { VCM(void, (void *, struct Big *), 0x284, a0); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    class BObj * v2D0(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(class BObj *, (void *, int, int, int), 0x2D0, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v47C() { VCM0(void, 0x47C); }
    
    
    
    
    
    void v494(s32 a0, s32 a1, s32 a2) { VCM(void, (void *, s32, s32, s32), 0x494, a0, a1, a2); }
};

class BObj {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v54() { VCM0(void, 0x54); }
};

extern "C" {
s32 EquipSlotDynamicCastKind1_39fec0(BObj *, int, int, int);
s32 EquipSlotGetAbilityActionGaugeCost_3a0300(BObj *);
s32 EquipSlotGetScaledCost_3a05c0(BObj *);
s32 EquipSlotGetEffectTargetKind_3a0680(BObj *);
s32 EquipSlotGetAbilityWeaponSlot_3a06e0(s32);
s32 EquipSlotGetAbilityType_3a0720(BObj *);
void CharaSysEventLogRecord_3a3320(s32, s32, s32, s32, s32);
void CharaSysEventLogKeyRemove_3a3380(s32, s32, int);
void CharaSysEventLogKeyAdd_3a33b0(s32, s32, s32);
void ActionResultSetupMaybe_3a6d70(Big *, Msg *, s32, s32, s32, s32, f32);
void ActionResultClear_3a6e60(Big *);
void ExecInfoInit_3a7940(Msg *);
AObj *PartyFindMember_3c2130(s32, s32, s32, s32, s32, s32, s32);
AObj *PartyGetMemberChara_3c2420(s32, s32);
void FieldHudLogOpen_203fb0(void);
extern s32 D_00483818;
BObj *CharaUseAbility_3abe80(AObj *arg0, s32 arg1, int rgp_a2, int rgp_a3);
}

BObj *CharaUseAbility_3abe80(AObj *arg0, s32 arg1, int rgp_a2, int rgp_a3)
{
    Msg m1 __attribute__((aligned(16)));
    Big g1 __attribute__((aligned(16)));
    Msg m2 __attribute__((aligned(16)));
    Big g2 __attribute__((aligned(16)));
    Msg m3 __attribute__((aligned(16)));
    Big g3 __attribute__((aligned(16)));
    BObj *b;
    s32 d;
    s32 kind;
    s32 sub;
    s32 i;
    AObj *o;
    u8 *p;

    if (arg1 < 0) {
        return 0;
    }
    b = arg0->v2D0((int)(long)(arg1), (int)(long)(rgp_a2), (int)(long)(rgp_a3));
    if (b == 0) {
        return 0;
    }
    d = EquipSlotDynamicCastKind1_39fec0(b, 0, 0, 0);
    if (d == 0) {
        return 0;
    }
    kind = ((unsigned char)EquipSlotGetAbilityType_3a0720(b));
    sub = EquipSlotGetEffectTargetKind_3a0680(b);
    if (kind == 2) {
        arg0->v47C();
        *(s32 *)((u8 *)arg0 + 0x498) = d;
        b->v54();
    }
    arg0->v114(-EquipSlotGetScaledCost_3a05c0(b));
    if (*(s32 *)((u8 *)arg0 + 0x498) != 0) {
        arg0->v494(EquipSlotGetAbilityWeaponSlot_3a06e0(*(s32 *)((u8 *)arg0 + 0x498)), 0, -1);
    } else {
        arg0->v270(-EquipSlotGetAbilityActionGaugeCost_3a0300(b));
    }
    CharaSysEventLogKeyAdd_3a33b0(*(s32 *)(D_00483818 + 0x20), 0x7FFC, 0);
    CharaSysEventLogRecord_3a3320(*(s32 *)(D_00483818 + 0x20), 0x7FFC, ((s32 *)arg0)[3], -1, arg1);
    if ((u32)(kind - 3) < 2) {
        if (sub == 2) {
            ExecInfoInit_3a7940(&m1);
            m1.id = 0x7FFC;
            m1.kind = 3;
            m1.arg = *(s32 *)(d + 4);
            arg0->v280(&m1);
            g1.a = 0;
            g1.b = 0;
            g1.c = 0;
            g1.d = 0;
            ActionResultClear_3a6e60(&g1);
            ActionResultSetupMaybe_3a6d70(&g1, &m1, *(s32 *)((u32)arg0 + 0xC), -1, 0, 1, 0.0f);
            arg0->v284(&g1);
        } else if (EquipSlotGetEffectTargetKind_3a0680(b) == 3) {
            ExecInfoInit_3a7940(&m2);
            m2.id = 0x7FFC;
            m2.kind = 3;
            m2.arg = *(s32 *)(d + 4);
            arg0->v280(&m2);
            i = 0;
            do {
                o = PartyGetMemberChara_3c2420(*(s32 *)(D_00483818 + 0x18), i);
                if (o != 0 && o->vC0() == 0) {
                    g2.a = 0;
                    g2.b = 0;
                    g2.c = 0;
                    g2.d = 0;
                    ActionResultClear_3a6e60(&g2);
                    ActionResultSetupMaybe_3a6d70(&g2, &m2, *(s32 *)((u8 *)o + 0xC), -1, 0, 1, 0.0f);
                    o->v284(&g2);
                }
                i++;
            } while (i < 3);
        }
    }
    if ((u32)(arg1 - 0x371) < 2) {
        o = PartyFindMember_3c2130(*(s32 *)(D_00483818 + 0x18), 0x2B00, 1, 1, -1, 0, 0);
        if (o != 0 && o->vBC() != 0) {
            ExecInfoInit_3a7940(&m3);
            m3.id = 0x7FFC;
            m3.kind = 3;
            m3.arg = *(s32 *)(d + 4);
            arg0->v280(&m3);
            g3.a = 0;
            g3.b = 0;
            g3.c = 0;
            g3.d = 0;
            ActionResultClear_3a6e60(&g3);
            ActionResultSetupMaybe_3a6d70(&g3, &m3, *(s32 *)((u8 *)o + 0xC), -1, 0, 1, 0.0f);
            o->v284(&g3);
        }
    }
    CharaSysEventLogKeyRemove_3a3380(*(s32 *)(D_00483818 + 0x20), 0x7FFC, 0);
    FieldHudLogOpen_203fb0();
    arg0->v38();
    *(s16 *)((u8 *)arg0 + 0x4B2) += 1;
    if (arg1 == 0x1AF) {
        arg0->v1BC(0x2B, 0x64, 0, 1);
    } else if (arg1 == 0x1B0) {
        arg0->v1BC(0x2D, 0x64, 0, 1);
    }
    p = *(u8 **)(*(s32 *)(D_00483818 + 0x20) + 0x238);
    if (p != 0) {
        u8 *q = p + 0x168;
        if (*(s16 *)(p + 0x2C) == 2) {
            ((Flags *)(q + 0xA))->b3 = true;
        }
    }
    return b;
}
