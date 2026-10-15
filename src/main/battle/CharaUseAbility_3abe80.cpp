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
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void v38();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual void d24();
    virtual void d25();
    virtual void d26();
    virtual void d27();
    virtual void d28();
    virtual void d29();
    virtual void d30();
    virtual void d31();
    virtual void d32();
    virtual void d33();
    virtual void d34();
    virtual void d35();
    virtual void d36();
    virtual void d37();
    virtual void d38();
    virtual void d39();
    virtual void d40();
    virtual void d41();
    virtual void d42();
    virtual void d43();
    virtual void d44();
    virtual s32 vBC();
    virtual s32 vC0();
    virtual void d47();
    virtual void d48();
    virtual void d49();
    virtual void d50();
    virtual void d51();
    virtual void d52();
    virtual void d53();
    virtual void d54();
    virtual void d55();
    virtual void d56();
    virtual void d57();
    virtual void d58();
    virtual void d59();
    virtual void d60();
    virtual void d61();
    virtual void d62();
    virtual void d63();
    virtual void d64();
    virtual void d65();
    virtual void d66();
    virtual void v114(s32);
    virtual void d68();
    virtual void d69();
    virtual void d70();
    virtual void d71();
    virtual void d72();
    virtual void d73();
    virtual void d74();
    virtual void d75();
    virtual void d76();
    virtual void d77();
    virtual void d78();
    virtual void d79();
    virtual void d80();
    virtual void d81();
    virtual void d82();
    virtual void d83();
    virtual void d84();
    virtual void d85();
    virtual void d86();
    virtual void d87();
    virtual void d88();
    virtual void d89();
    virtual void d90();
    virtual void d91();
    virtual void d92();
    virtual void d93();
    virtual void d94();
    virtual void d95();
    virtual void d96();
    virtual void d97();
    virtual void d98();
    virtual void d99();
    virtual void d100();
    virtual void d101();
    virtual void d102();
    virtual void d103();
    virtual void d104();
    virtual void d105();
    virtual void d106();
    virtual void d107();
    virtual void d108();
    virtual void v1BC(s32, s32, s32, s32);
    virtual void d110();
    virtual void d111();
    virtual void d112();
    virtual void d113();
    virtual void d114();
    virtual void d115();
    virtual void d116();
    virtual void d117();
    virtual void d118();
    virtual void d119();
    virtual void d120();
    virtual void d121();
    virtual void d122();
    virtual void d123();
    virtual void d124();
    virtual void d125();
    virtual void d126();
    virtual void d127();
    virtual void d128();
    virtual void d129();
    virtual void d130();
    virtual void d131();
    virtual void d132();
    virtual void d133();
    virtual void d134();
    virtual void d135();
    virtual void d136();
    virtual void d137();
    virtual void d138();
    virtual void d139();
    virtual void d140();
    virtual void d141();
    virtual void d142();
    virtual void d143();
    virtual void d144();
    virtual void d145();
    virtual void d146();
    virtual void d147();
    virtual void d148();
    virtual void d149();
    virtual void d150();
    virtual void d151();
    virtual void d152();
    virtual void d153();
    virtual void v270(s32);
    virtual void d155();
    virtual void d156();
    virtual void d157();
    virtual void v280(struct Msg *);
    virtual void v284(struct Big *);
    virtual void d160();
    virtual void d161();
    virtual void d162();
    virtual void d163();
    virtual void d164();
    virtual void d165();
    virtual void d166();
    virtual void d167();
    virtual void d168();
    virtual void d169();
    virtual void d170();
    virtual void d171();
    virtual void d172();
    virtual void d173();
    virtual void d174();
    virtual void d175();
    virtual void d176();
    virtual void d177();
    virtual class BObj *v2D0();
    virtual void d179();
    virtual void d180();
    virtual void d181();
    virtual void d182();
    virtual void d183();
    virtual void d184();
    virtual void d185();
    virtual void d186();
    virtual void d187();
    virtual void d188();
    virtual void d189();
    virtual void d190();
    virtual void d191();
    virtual void d192();
    virtual void d193();
    virtual void d194();
    virtual void d195();
    virtual void d196();
    virtual void d197();
    virtual void d198();
    virtual void d199();
    virtual void d200();
    virtual void d201();
    virtual void d202();
    virtual void d203();
    virtual void d204();
    virtual void d205();
    virtual void d206();
    virtual void d207();
    virtual void d208();
    virtual void d209();
    virtual void d210();
    virtual void d211();
    virtual void d212();
    virtual void d213();
    virtual void d214();
    virtual void d215();
    virtual void d216();
    virtual void d217();
    virtual void d218();
    virtual void d219();
    virtual void d220();
    virtual void d221();
    virtual void d222();
    virtual void d223();
    virtual void d224();
    virtual void d225();
    virtual void d226();
    virtual void d227();
    virtual void d228();
    virtual void d229();
    virtual void d230();
    virtual void d231();
    virtual void d232();
    virtual void d233();
    virtual void d234();
    virtual void d235();
    virtual void d236();
    virtual void d237();
    virtual void d238();
    virtual void d239();
    virtual void d240();
    virtual void d241();
    virtual void d242();
    virtual void d243();
    virtual void d244();
    virtual void d245();
    virtual void d246();
    virtual void d247();
    virtual void d248();
    virtual void d249();
    virtual void d250();
    virtual void d251();
    virtual void d252();
    virtual void d253();
    virtual void d254();
    virtual void d255();
    virtual void d256();
    virtual void d257();
    virtual void d258();
    virtual void d259();
    virtual void d260();
    virtual void d261();
    virtual void d262();
    virtual void d263();
    virtual void d264();
    virtual void d265();
    virtual void d266();
    virtual void d267();
    virtual void d268();
    virtual void d269();
    virtual void d270();
    virtual void d271();
    virtual void d272();
    virtual void d273();
    virtual void d274();
    virtual void d275();
    virtual void d276();
    virtual void d277();
    virtual void d278();
    virtual void d279();
    virtual void d280();
    virtual void d281();
    virtual void d282();
    virtual void d283();
    virtual void d284();
    virtual void v47C();
    virtual void d286();
    virtual void d287();
    virtual void d288();
    virtual void d289();
    virtual void d290();
    virtual void v494(s32, s32, s32);
};

class BObj {
public:
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void v54();
};

extern "C" {
s32 EquipSlotDynamicCastKind1_39fec0(BObj *);
s32 EquipSlotGetAbilityActionGaugeCost_3a0300(BObj *);
s32 EquipSlotGetScaledCost_3a05c0(BObj *);
s32 EquipSlotGetEffectTargetKind_3a0680(BObj *);
s32 EquipSlotGetAbilityWeaponSlot_3a06e0(s32);
s32 EquipSlotGetAbilityType_3a0720(BObj *);
void CharaSysEventLogRecord_3a3320(s32, s32, s32, s32, s32);
void CharaSysEventLogKeyRemove_3a3380(s32, s32);
void CharaSysEventLogKeyAdd_3a33b0(s32, s32, s32);
void ActionResultSetupMaybe_3a6d70(Big *, Msg *, s32, s32, s32, s32, f32);
void ActionResultClear_3a6e60(Big *);
void ExecInfoInit_3a7940(Msg *);
AObj *PartyFindMember_3c2130(s32, s32, s32, s32, s32, s32, s32);
AObj *PartyGetMemberChara_3c2420(s32, s32);
void FieldHudLogOpen_203fb0(void);
extern s32 D_00483818;
BObj *CharaUseAbility_3abe80(AObj *arg0, s32 arg1);
}

BObj *CharaUseAbility_3abe80(AObj *arg0, s32 arg1)
{
    Msg m1;
    Big g1;
    Msg m2;
    Big g2;
    Msg m3;
    Big g3;
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
    b = arg0->v2D0();
    if (b == 0) {
        return 0;
    }
    d = EquipSlotDynamicCastKind1_39fec0(b);
    if (d == 0) {
        return 0;
    }
    kind = EquipSlotGetAbilityType_3a0720(b);
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
    CharaSysEventLogKeyRemove_3a3380(*(s32 *)(D_00483818 + 0x20), 0x7FFC);
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
