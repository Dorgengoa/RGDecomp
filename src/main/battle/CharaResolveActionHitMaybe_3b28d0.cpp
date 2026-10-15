#include "types.h"

/* CharaResolveActionHitMaybe_3b28d0 -- the SECOND largest function in SCUS_974.90
   (3,789 instructions, 0x003B28D0..0x003B6403 + 3 pad nops).

   It is the virtual at slot 0x27C of an 11-class hierarchy (vtable base
   0x004722A8), so `arg0` is `this` and every `this->vNNN()` below is a
   sibling virtual of the SAME class.  MUST be C++: 107 of the 182 calls go
   through that vtable as `jalr $25`.

   Assembled by build/bg31/gen.py from head.inc + vtable.inc + body.inc.
   Do not hand-edit the draft; edit body.inc. */

struct Res;
struct Ent;
struct Cmd;
struct Prm;
struct Act;
struct Eff;
struct EffDef;
struct Tri;
struct Sys;
struct Sys2;
struct Holder;
struct Mgr;
struct Party;
struct Tune;
struct Rec;
struct Iter;
struct Slot;
struct Ref;
class  VObj;

typedef s64 Mask;

/* v198 returns EIGHT BYTES THROUGH A HIDDEN POINTER -- retail passes
   `addiu $4, $29, 0x12B8` (the destination) in a0 and `this` in a1,
   then reads the result back with `ld`.  A plain `s64` return comes
   back in v0 and loses the whole sequence, so the return type has to
   be a STRUCT. */
struct Mask64 { s64 v; Mask64() {} Mask64(const Mask64 &o) : v(o.v) {} };
union MaskU { s64 v; u32 w[2]; };

/* One slot of the 4-entry result array that lives at Res+0x1C. */
struct Ent {
    s8  m0;                     /* `lb` at 003B4614/003B4710: SIGNED */
    u8  b1_0 : 1;               /* 0x01 -- slot is used */
    u8  b1_1 : 7;
    s8  m2;                     /* priority / rank */
    u8  m3;
    s32 m4;                     /* the amount */
};

struct Rec {
    s16 m0;
    s16 m2;
    s16 m4;
};

/* `arg1` -- the per-target result record the caller hands in. */
struct Res {
    Cmd *m0;
    u8   pad04[4];
    Rec *m8;
    u8   pad0C[4];
    f32  m10;
    s8   m14;
    u8   pad15[3];
    u8   m18;                   /* `sb`/`lbu`, not a word */
    u8   pad19[1];
    s16  m1A;
    Ent  ent[4];
    s32  m3C;
    u8   b40_0 : 1;             /* 0x40 -- eight single bits */
    u8   b40_1 : 1;
    u8   b40_2 : 1;
    u8   b40_3 : 1;
    u8   b40_4 : 1;
    u8   b40_5 : 1;
    u8   b40_6 : 1;
    u8   b40_7 : 1;
    u8   b41_0 : 1;             /* 0x41 -- eight single bits */
    u8   b41_1 : 1;
    u8   b41_2 : 1;
    u8   b41_3 : 1;
    u8   b41_4 : 1;
    u8   b41_5 : 1;
    u8   b41_6 : 1;
    u8   b41_7 : 1;
    u8   b42_0 : 1;             /* 0x42 -- three bits then a nibble */
    u8   b42_1 : 1;
    u8   b42_2 : 1;
    u8   b42_3 : 4;
    u8   b42_7 : 1;
    u8   b43_0 : 4;             /* 0x43 */
    u8   b43_4 : 4;
    u8   pad44[4];
    s64  m48;
    s64  m50;
    s64  m58;
    s64  m60;
    s32  m68;
    s16  m6C;
    u8   pad6E[2];
    s32  m70[4];
    u8   b80_0 : 1;
    u8   b80_1 : 1;
    u8   b80_2 : 1;
    u8   b80_3 : 1;
};

/* `arg1->m0` -- the action being resolved. */
struct Cmd {
    s16  m0;
    u8   pad02[6];
    s16  m8;
    s16  mA;
    /* 0xC and 0x10 are read as `lh` AND as `lw` (a pointer) depending on
       the command kind -- s4: the old `s32 mC` shifted every later field
       +4.  Word reads go through *(s32 *)&cmd->mC / &cmd->m10. */
    s16  mC;
    s16  mE;
    s16  m10;
    u8   pad12[2];
    f32  m14;
    Prm *m18;
    s16  m1C;
    u8   pad1E[2];
    s32  m20;
    s32  m24;
    u8   pad28[4];
    s16  m2C;
    u8   b2E_0 : 1;
    u8   b2E_1 : 7;
    u8   pad2F[1];
    f32  m30;
    f32  m34;
    f32  m38;
    f32  m3C;
    f32  m40;
    s16  m44;
    s16  m46[5];
};

/* `Cmd::m18` -- the tuning record for this action. */
struct Prm {
    s16 m0;
    u8  pad02[2];
    s8  b4_0 : 7;
    s8  b4_7 : 1;
    s8  m5;
    s8  b6_0 : 5;
    s8  b6_5 : 3;
    u8  pad07[1];
    s16 b8_0 : 4;
    s16 b8_4 : 8;
    s16 b8_C : 4;
    u8  pad0A[10];
    f32 m14;
    f32 m18;
    f32 m1C;
    f32 m20;
    u8  pad24[8];
    f32 m2C;
    f32 m30;
    f32 m34;
};

/* An entry of the two-element list at sp+0x12C8. */
struct Act {
    s32 m0;
    s32 m4;
    u8  pad08[0x16];
    u8  n1E_0 : 4;
    u8  n1E_4 : 4;
    u8  n1F_0 : 4;
    u8  n1F_4 : 4;
    s32 m20;
};

/* The sp+0x12C0 iterator and what it yields. */
struct Iter {
    void *m0;
    void *m4;
};

struct Eff {
    s16     m0;
    s16     m2;
    EffDef *m4;
};

struct EffDef {
    s16 m0;
    u8  pad02[2];
    s16 m4;
    s16 m6;
    s16 m8;
};

/* m4..m7 are `unsigned int` BITFIELDS, not u8: the listing converts m6 and
   m7 to float through the full u32->f32 sequence (`bltzl` + halve + double),
   which mwcc only emits when the type really is 32-bit unsigned. */
struct Tri {
    u8  pad00[4];
    u32 m4 : 8;
    u32 m5 : 8;
    u32 m6 : 8;
    u32 m7 : 8;
};

struct Slot {
    u8   pad00[0x10];
    s16 *m10;
};

struct Ref {
    u8  pad00[0x3C];
    s16 m3C;
};

struct PartySub { u8 pad0[0xA]; u8 bA_0 : 2; u8 bA_2 : 1; u8 bA_3 : 5; };

struct Party {
    u8   pad000[0x2C];
    s16  m2C;
    s16  m2E;
    u8   pad030[0x138];
    PartySub m168;
    u8   pad173[0x49];
    s16  m1BC;
    s16  m1BE;
};

struct Mgr {
    u8      pad000[0x238];
    Party  *m238;
    u8      pad23C[0x10];
    u8      b24C_0 : 1;
    u8      b24C_1 : 3;
    u8      b24C_4 : 1;
    u8      b24C_5 : 3;
};

struct Tune {
    u8  pad00[0x94];
    f32 m94;
    f32 m98;
    f32 m9C;
    f32 mA0;
    f32 mA4;
    f32 mA8;
    u8  padAC[0xC];
    f32 mB8;
};

struct Cfg2 {
    u8    pad00[8];
    Tune *m8;
};

struct Cfg {
    u8     pad00[0x54];
    Cfg2  *m54;
};

/* D_00483818 -- the subsystem table. */
struct Sys {
    u8      pad00[8];
    Cfg    *m8;
    u8      pad0C[4];
    VObj   *m10;
    VObj   *m14;
    VObj   *m18;
    VObj   *m1C;
    Mgr    *m20;
};

struct Holder {
    u8    pad00[8];
    VObj *m8;
};

struct Sys2 {
    u8       pad00[0x58];
    Holder  *m58;
    Holder  *m5C;
};

class VObj {
public:
    virtual void f008();
    virtual void f00C();
    virtual void f010();
    virtual void f014();
    virtual void f018();
    virtual void f01C();
    virtual void f020();
    virtual void f024();
    virtual void f028();
    virtual void f02C();
    virtual void f030();
    virtual void f034();
    virtual void f038();
    virtual void f03C();
    virtual s32  v40();
    virtual void f044();
    virtual s32  v48();
    virtual void f04C();
    virtual void f050();
    virtual void f054();
    virtual void f058();
    virtual s32  v5C();
    virtual void f060();
    virtual void f064();
    virtual void f068();
    virtual void f06C();
    virtual void *v70(s32);
    virtual void f074();
    virtual void f078();
    virtual void f07C();
    virtual void f080();
    virtual void f084();
    virtual void f088();
    virtual void f08C();
    virtual void f090();
    virtual void f094();
    virtual void f098();
    virtual s32  v9C();
    virtual s32  vA0();
    virtual s32  vA4();
    virtual s32  vA8();
    virtual void f0AC();
    virtual void f0B0();
    virtual void f0B4();
    virtual void f0B8();
    virtual s32  vBC();
    virtual s32  vC0();
    virtual void f0C4();
    virtual void f0C8();
    virtual void f0CC();
    virtual void f0D0();
    virtual void f0D4();
    virtual void f0D8();
    virtual void f0DC();
    virtual void f0E0();
    virtual void f0E4();
    virtual void f0E8();
    virtual void f0EC();
    virtual s32  vF0();
    virtual void f0F4();
    virtual void vF8(s32);
    virtual void f0FC();
    virtual void f100();
    virtual void f104();
    virtual void f108();
    virtual s32  v10C();
    virtual void f110();
    virtual void v114(s32);
    virtual void f118();
    virtual void f11C();
    virtual void f120();
    virtual void f124();
    virtual s32  v128(s32);
    virtual void f12C();
    virtual s32  v130(s32);
    virtual void f134();
    virtual void f138();
    virtual void f13C();
    virtual s32  v140(s32);
    virtual void f144();
    virtual void f148();
    virtual void f14C();
    virtual void f150();
    virtual void f154();
    virtual void f158();
    virtual void f15C();
    virtual f32  v160(s32);
    virtual void f164();
    virtual f32  v168(s32);
    virtual void f16C();
    virtual f32  v170(s32);
    virtual void f174();
    virtual s32  v178(s32, s32);
    virtual void f17C();
    virtual void f180();
    virtual void f184();
    virtual s32  v188(s32, s32);
    virtual void f18C();
    virtual void f190();
    virtual void f194();
    virtual Mask64 v198();
    virtual s32  v19C(s32);
    virtual void v1A0(s32, s32, s32);
    virtual void v1A4(s32);
    virtual void f1A8();
    virtual void f1AC();
    virtual void f1B0();
    virtual void f1B4();
    virtual void f1B8();
    virtual s32  v1BC(s32, s32, s32, s32);
    virtual void f1C0();
    virtual void f1C4();
    virtual void f1C8();
    virtual void f1CC();
    virtual void f1D0();
    virtual void f1D4();
    virtual void f1D8();
    virtual void f1DC();
    virtual void f1E0();
    virtual void f1E4();
    virtual void f1E8();
    virtual void f1EC();
    virtual void f1F0();
    virtual void f1F4();
    virtual void f1F8();
    virtual void f1FC();
    virtual void f200();
    virtual void f204();
    virtual void f208();
    virtual void f20C();
    virtual void f210();
    virtual void f214();
    virtual void f218();
    virtual void f21C();
    virtual void f220();
    virtual void f224();
    virtual s32  v228();
    virtual void f22C();
    virtual void f230();
    virtual void f234();
    virtual void f238();
    virtual s32  v23C();
    virtual void f240();
    virtual void f244();
    virtual void f248();
    virtual s32  v24C();
    virtual void f250();
    virtual s32  v254();
    virtual void f258();
    virtual void f25C();
    virtual void f260();
    virtual void f264();
    virtual void f268();
    virtual void v26C(f32);
    virtual void f270();
    virtual void f274();
    virtual void f278();
    virtual void f27C();
    virtual void f280();
    virtual void f284();
    virtual void v288(Res *, s32, s32, u8, bool, Mask);
    virtual s32  v28C(s32, s32, s32, s32, s32, s32, s16, s32);
    virtual s32  v290(s32, s32, s32, s32);
    virtual s32  v294(s32, s32, s32, s32);
    virtual s32  v298(s32, s32, s32, s32);
    virtual s32  v29C(s32, s32);
    virtual s32  v2A0(s32, s32);
    virtual void f2A4();
    virtual void f2A8();
    virtual void f2AC();
    virtual void f2B0();
    virtual void f2B4();
    virtual void f2B8();
    virtual void v2BC(f32, s32);
    virtual void f2C0();
    virtual void f2C4();
    virtual void f2C8();
    virtual void f2CC();
    virtual void f2D0();
    virtual void f2D4();
    virtual void f2D8();
    virtual void f2DC();
    virtual void f2E0();
    virtual void f2E4();
    virtual void f2E8();
    virtual void f2EC();
    virtual void f2F0();
    virtual void f2F4();
    virtual void f2F8();
    virtual void f2FC();
    virtual void f300();
    virtual void f304();
    virtual void f308();
    virtual void f30C();
    virtual void f310();
    virtual void f314();
    virtual void f318();
    virtual void f31C();
    virtual void f320();
    virtual void f324();
    virtual void f328();
    virtual void f32C();
    virtual void f330();
    virtual void f334();
    virtual void f338();
    virtual void f33C();
    virtual void f340();
    virtual void f344();
    virtual void f348();
    virtual void f34C();
    virtual void f350();
    virtual void f354();
    virtual void f358();
    virtual void f35C();
    virtual void f360();
    virtual void f364();
    virtual void f368();
    virtual Tri *v36C();
    virtual void f370();
    virtual void f374();
    virtual void f378();
    virtual void f37C();
    virtual s32  v380();
    virtual void f384();
    virtual void f388();
    virtual void f38C();
    virtual void f390();
    virtual void f394();
    virtual void f398();
    virtual void f39C();
    virtual void f3A0();
    virtual void f3A4();
    virtual void f3A8();
    virtual void f3AC();
    virtual void f3B0();
    virtual void f3B4();
    virtual void f3B8();
    virtual void f3BC();
    virtual s32  v3C0();
    virtual void f3C4();
    virtual void f3C8();
    virtual void f3CC();
    virtual void f3D0();
    virtual void f3D4();
    virtual VObj *v3D8();
    virtual void f3DC();
    virtual void f3E0();
    virtual s32  v3E4();
    virtual void f3E8();
    virtual void f3EC();
    virtual void f3F0();
    virtual void f3F4();
    virtual void f3F8();
    virtual void f3FC();
    virtual void f400();
    virtual void f404();
    virtual void f408();
    virtual void f40C();
    virtual void f410();
    virtual void f414();
    virtual void f418();
    virtual void f41C();
    virtual void f420();
    virtual void f424();
    virtual void f428();
    virtual void f42C();
    virtual void f430();
    virtual void f434();
    virtual void f438();
    virtual void f43C();
    virtual void f440();
    virtual void f444();
    virtual void f448();
    virtual void f44C();
    virtual void f450();
    virtual void f454();
    virtual void f458();
    virtual void f45C();
    virtual void f460();
    virtual void f464();
    virtual void f468();
    virtual void f46C();
    virtual VObj *v470();
    /* data members, `this` = the object the vtable pointer sits in */
    u8   pad004[8];
    s32  mC;
    u8   pad010[0xB8];
    s64  mC8;
    f32  mD0[0x3C];
    u8   b1C0_0 : 1;
    u8   b1C0_1 : 7;
    u8   pad1C1[7];
    u8   b1C8_0 : 1;
    u8   b1C8_1 : 1;
    u8   b1C8_2 : 1;
    u8   b1C8_3 : 5;
    u8   pad1C9[3];
    f32  m1CC;
    f32  m1D0;
    u8   pad1D4[0xC];
    f32  m1E0;
    f32  m1E4;
    f32  m1E8;
};

#pragma optimization_level 3
extern "C" f32   RandFloat_13c010(void);
extern "C" VObj *CharaMgrPoolFindById_3a8c60(VObj *sys, s32 key);
extern "C" VObj *ObjFindById_3bb3a0(VObj *sys, s32 key);
extern "C" VObj *ActorFindById_3eb870(Sys *sys, s32 key);
extern "C" s32   CharaIsPartyLeader_3ae1a0(VObj *o);
extern "C" VObj *ActorCastToUnit_3b8770(VObj *o);
extern "C" VObj *ActorCastToChara_3b87b0(VObj *o);
extern "C" Slot *InvFindByUniqueId_3c85d0(VObj *o, s32 a, s32 b, s32 c);
extern "C" s32   AbilityDataGetCompositeId_3f5e10(void *p);
extern "C" s32   StateFlagTest_3ccd70(VObj *o, s32 i);
extern "C" s32   StateFlagSet_3ccb70(VObj *o, s32 a, s32 b, s32 c);
extern "C" s32   StateVarGet_3ccac0(VObj *o, s32 i);
extern "C" void  VariantInit_36ff00(void *p);
extern "C" s32   VariantPoolReset_3e01f0(void *p);
extern "C" s32   CharaSysGetEncounterEntryIdMaybe_3a36f0(Mgr *m);
extern "C" s32   CharaSysGetEncounterIdMaybe_3a36d0(Mgr *m);
extern "C" s32   CharaSysGetEncounterSpawnParamMaybe_3a36a0(Mgr *m);
extern "C" s32   CharaSysStateUnitFlag7EBit3Related_3a38e0(Mgr *m);
extern "C" s32   PlayStatBumpChainFinishMaybe_3a1aa0(Mgr *m, s32 i);
extern "C" s32   CharaSysStatusAdd_3a1630(Mgr *m, s32 i);
extern "C" s32   CharaSysEventLogRecord_3a3320(Mgr *m, s32 a, s32 b, s32 c, s32 e);
extern "C" s32   CharaSysEventLogRecordOpenHud_3a3260(Mgr *m, s32 a, s32 b, s32 c, s32 d);
extern "C" s32   ActionResultListAddUniqueRelated_3a6c50(void *p, s32 i);
extern "C" f32   EquipSlotGetAbilityDefenseScaleMaybe_3a0330(VObj *o);
extern "C" s32   EquipSlotGetAbilityCompositeId_3a0730(VObj *o);
extern "C" s32   EquipSlotGetAbilityLevel_3a0700(VObj *o);
extern "C" f32   BtlElemParamGetChainFinishScaleMaybe_3f94b0(Tune *t, s32 i);
extern "C" Iter *IterInit_370170(Iter *it, void *list);
extern "C" Eff  *IterNext_370040(Iter *it);
extern "C" s32   ObjMgrCountActiveMaybe_3bacc0(VObj *o, s32 a, s32 b, s32 c);
extern "C" s32   PlayStatBumpCureCountMaybe_3c04c0(VObj *o, s32 i);
extern "C" s32   PlayStatBumpReviveCountMaybe_3c0540(VObj *o, s32 i);
extern "C" s32   PlayStatAddHealAmountMaybe_3c05c0(VObj *o, s32 i, s32 n);
extern "C" s32   PlayStatBumpHealCountMaybe_3c0650(VObj *o, s32 i);
extern "C" s32   ObjHasMonographAttachPointMaybe_2d0840(s32 id);
extern "C" s32   GetEventObjMgr_2d1960(void);
extern "C" s32   EvSpawnChrMonographs_2e91e0(s32 a, s32 b, f32 f0, f32 f1);

extern Sys  *D_00483818;
extern Sys2 *D_0048381C;
extern Mgr  *D_00483824;
extern const s32 D_00465CD0;
extern const f32 D_0045B080;
extern f32   D_0047D1DC;
extern f32   D_0047D1E8;
extern f32   D_0047D240;
extern f32   D_0047D258;
extern f32   D_0047D28C;

static inline const Mask64 *addr64(const Mask64 &m) { return &m; }
static inline Mask xor64(const Mask64 &a, const Mask64 &b) { volatile Mask x; Mask r = a.v ^ b.v; x = r; return r; }
static inline void masks(Res *res, Mask k)
{
    volatile Mask mAB, mBA, mA, mB, mNA, mNB;
    {
        Mask a = res->m48;
        Mask m = ~a & k;
        Mask r = res->m50 & m;
        mA = a;
        mNA = m;
        mAB = r;
        res->m58 = r;
    }
    {
        Mask a = res->m50;
        Mask m = ~a & k;
        Mask r = m & res->m48;
        mB = a;
        mNB = m;
        mBA = r;
        res->m60 = r;
    }
}
extern "C" s32 CharaResolveActionHitMaybe_3b28d0(VObj *self, Res *res)
{
    f32   L1240[5];
    struct { u8 hdr[8]; u8 e[64][0x38]; } L430;
    u8    L420;
    VObj  *L41C;
    u8    L400;
    u8    L3F0;
    s32   L3E0;
    s32   L3DC;
    Slot  *L3D8;
    s32   L3C0;
    s32   L3B0;
    s32   L3A0;
    s32   L390;
    s32   L380;
    s32   L37C;
    u8    hurt;
    u8    L360;
    u8    L350;
    s32   L340;
    VObj  *L33C;
    u8    L320;
    u8    L310;
    s32   L30C;
    s32   L2F0;
    u8    L2E0;
    s32   L2D0;
    u8    L2C0;
    u8    L2B0;
    u8    L2A0;
    u8    L290;
    u8    L280;
    u8    L270;
    s32   L260;
    s32   L250;
    s32   L240;
    u8    L230;
    s32   L220;
    s32   L210;
    u8    L200;
    u8    L1F0;
    u8    has19C;
    s32   L1E0;
    s32   L1D4;
    s32   L1D0;
    s32   L1CC;
    VObj  *L1C8;
    s32   L1B0;
    s32   L1A0;
    u8    L180;
    s32   L160;
    s32   L150;
    s32   L140;
    s32   L130;
    s32   L120;
    f32     f31;
    f32     acc, f30, f29, f28, f27, f26, f25, f24, f23, f22, f21, f20;
    f32   L11C;
    f32   L118;
    f32   L114;
    f32   L110;
    f32   L10C;
    f32   L108;
    f32   L104;
    f32   L100;
    f32   LFC;
    f32   LF8;
    f32   LF4;
    f32   LF0;
    f32   LEC;
    f32   LE8;

    Cmd    *cmd;
    Prm    *prm;
    VObj   *o17, *o23, *oTmp;
    Act    *act;
    Eff    *eff;
    EffDef *def;
    Tune   *tune;
    Party  *pty;
    Rec    *rec;
    s32     i, n, t, t2, rank, rank2, kind, amount;
    u8      ok;
    VObj   *oSub;
    Mask    mMask;
    s32     pow;
    f32     ftmp;
    u8      guard, flags;

    if (res == 0) {
        return 0;
    }
    if (D_00483818 == 0) {
        return 0;
    }
    cmd = res->m0;
    L420 = 0;
    if (cmd == 0) {
        return 0;
    }
    res->m1A = 0;
    for (i = 0; i < 4; i++) {
        res->ent[i].m0 = 0;
        res->ent[i].b1_0 = 0;
        res->ent[i].m4 = -1;
        res->ent[i].m2 = 1;
    }
    res->m3C = 0;
    res->b40_0 = 0;
    res->b40_1 = 0;
    res->b40_2 = 0;
    res->b40_3 = 0;
    res->b40_4 = 0;
    res->b40_5 = 0;
    res->b40_6 = 0;
    res->b40_7 = 0;
    res->b41_0 = 0;
    res->b41_1 = 0;
    res->b41_2 = 0;
    res->b41_3 = 0;
    res->b41_4 = 0;
    res->b41_5 = 0;
    res->b41_6 = 0;
    res->b41_7 = 0;
    res->b42_0 = 0;
    res->b42_3 = 0;
    res->b43_0 = 0;
    res->b42_1 = 0;
    res->b42_2 = 0;
    res->m48 = self->mC8;
    res->m50 = self->mC8;
    res->m58 = 0;
    res->m60 = 0;
    res->m68 = 0;
    res->m6C = 0;
    for (i = 0; i < 4; i++) {
        res->m70[i] = 0;
    }
    res->b80_0 = 0;
    res->b80_1 = 0;
    res->b80_2 = 0;
    res->b80_3 = 0;
    L3E0 = -1;
    has19C = 0;
    L41C = 0;
    L400 = 0;
    L3F0 = 0;
    L3DC = -1;
    L3D8 = 0;
    L3C0 = -1;
    L3B0 = 0;
    L3A0 = 0;
    L390 = 0;
    L11C = 1.0f;
    Act  *L12C8[2] = {0};
    Iter  L12C0;
    L380 = -1;
    L37C = -1;
    f29 = cmd->m34;
    f20 = cmd->m38;
    L118 = cmd->m30;
    f28 = cmd->m3C;
    prm = 0;
    pow = cmd->m2C;
    f27 = cmd->m40;
    hurt = 0;
    L360 = cmd->b2E_0;
    L114 = 1.0f;
    L110 = (f32) cmd->m44;
    for (i = 0; i < 5; i++) {
        L1240[i] = (f32) cmd->m46[i];
    }
    L340 = -1;
    L350 = 0;
    switch (cmd->m1C) {
    case 1:
        n = 0;
        if (cmd->m24 != 0) {
            L12C8[n++] = (Act *) cmd->m24;
        }
        if (cmd->m20 != 0) {
            L12C8[n] = (Act *) cmd->m20;
        }
        prm = (Prm *) cmd->m18;
        oTmp = CharaMgrPoolFindById_3a8c60(D_00483818->m14, cmd->m8);
        if (oTmp != 0) {
            L400 = 1;
            L41C = oTmp;
            L3F0 = CharaIsPartyLeader_3ae1a0(oTmp);
            has19C = oTmp->v19C(3) & 0xFF;
            L3DC = oTmp->v5C();
            L3E0 = cmd->m8;
            L3C0 = cmd->mA;
            L3D8 = InvFindByUniqueId_3c85d0(D_00483818->m18, cmd->mC, -1, 0);
            L11C = cmd->m14;
            L3B0 = cmd->mE;
            L3A0 = cmd->m10;
            if (cmd->m10 == 5) {
                L390 = 1;
            } else if (cmd->m10 == 7) {
                L390 = 2;
            } else if (cmd->m10 == 9) {
                L390 = 3;
            }
            L420 = D_00483824->b24C_4;
        }
        break;
    case 2:
        prm = (Prm *) *(s32 *) &cmd->mC;
        L12C8[0] = (Act *) cmd->m20;
        oTmp = ObjFindById_3bb3a0(D_00483818->m1C, cmd->m8);
        if (oTmp != 0) {
            L41C = oTmp;
            L3DC = oTmp->v5C();
            L3E0 = cmd->m8;
            if (prm != 0) {
                t = prm->b8_0;
                if (t >= 0 && t < 5) {
                    for (i = 0; i < 5; i++) {
                        ftmp = 0.0f;
                        if (i == t) {
                            ftmp = (f32) prm->b8_4;
                        }
                        L1240[i] = ftmp;
                    }
                }
            }
        }
        break;
    case 3:
        prm = (Prm *) *(s32 *) &cmd->m10;
        L12C8[0] = (Act *) cmd->m20;
        oTmp = ActorFindById_3eb870(D_00483818, cmd->m8);
        if (oTmp != 0) {
            L3DC = oTmp->v5C();
            L41C = oTmp;
            L3E0 = oTmp->mC;
            L400 = oTmp->v40();
            oTmp->v48();
            L3F0 = 0;
            o17 = ActorCastToChara_3b87b0(oTmp);
            if (o17 != 0) {
                L3F0 = CharaIsPartyLeader_3ae1a0(o17);
            }
            L380 = *(s16 *) *(s32 *) &cmd->mC;
            L37C = AbilityDataGetCompositeId_3f5e10((void *) *(s32 *) &cmd->mC);
            if (L37C == 0xBC1 && (StateFlagTest_3ccd70(D_00483818->m10, 0x7EA) & 0xFF) == 0) {
                L114 = D_0047D240;
            }
        }
        break;
    case 4:
        prm = (Prm *) *(s32 *) &cmd->m10;
        L12C8[0] = (Act *) cmd->m20;
        oTmp = ActorFindById_3eb870(D_00483818, cmd->m8);
        if (oTmp != 0) {
            L41C = oTmp;
            L3E0 = oTmp->mC;
        }
        break;
    case 5:
        prm = (Prm *) *(s32 *) &cmd->mC;
        L12C8[0] = (Act *) cmd->m20;
        break;
    case 6:
        L350 = 1;
        L12C8[0] = (Act *) cmd->m20;
        L340 = cmd->mA;
        break;
    }
    if (L420 && res->m14 >= 2) {
        return 0;
    }
    {
        u8 (*p)[0x38] = L430.e;
        do {
            VariantInit_36ff00(*p);
            p++;
        } while (p < &L430.e[64]);
    }
    VariantPoolReset_3e01f0(L430.hdr);
    CharaSysGetEncounterEntryIdMaybe_3a36f0(D_00483818->m20);
    CharaSysGetEncounterIdMaybe_3a36d0(D_00483818->m20);
    CharaSysGetEncounterSpawnParamMaybe_3a36a0(D_00483818->m20);
    if (prm != 0 && prm->b4_7 != 0) {
        L360 = 1;
    }
    if (L420) {
        hurt = 1;
        L360 = 1;
    }
    o17 = ActorCastToChara_3b87b0(self);
    L33C = ActorCastToUnit_3b8770(self);
    L320 = 0;
    L310 = 0;
    if (o17 != 0) {
        L320 = 1;
        if (CharaIsPartyLeader_3ae1a0(o17) != 0) {
            L310 = 1;
        }
    }
    if (L400 && !has19C && o17 != 0 && o17->v19C(2) != 0) {
        o17->v1A4(2);
        L340 = 1;
        L350 = 1;
    }
    L30C = 0;
    if (L33C != 0) {
        L30C = L33C->v380();
    }
    rec = res->m8;
    L1D0 = 0;
    if (rec != 0) {
        if (rec->m0 == 0) {
            rec = 0;
        }
        if (rec != 0) {
            L1D0 = rec->m4;
        }
    }
    L2F0 = 0;
    if (prm != 0) {
        f29 *= prm->m14;
        f20 += prm->m18;
        f28 *= prm->m1C;
        L2F0 = prm->b6_0;
        f27 += prm->m20;
    }
    L2E0 = 0;
    if (!(f29 < 10.0f)) {
        L2E0 = 1;
    } else {
        ftmp = RandFloat_13c010(); f29 += D_0047D240 * ftmp - D_0047D240;
    }
    ftmp = RandFloat_13c010(); f20 += D_0047D240 * ftmp - D_0047D240;
    if (!(f27 <= 0.0f)) {
        if (f27 < 0.0f) {
            f27 = 0.0f;
        }
        if (!(f27 <= 100.0f)) {
            f27 = 100.0f;
        }
    }
    L2D0 = self->v140(1);
    o23 = 0;
    if (o17 != 0) {
        o23 = o17->v470();
    }
    if (o23 != 0) {
        L2D0 = (s32) ((f32) L2D0 * EquipSlotGetAbilityDefenseScaleMaybe_3a0330(o23));
    }
    guard = self->v23C() & 0xFF;
    if (L1D0 == 1) {
        guard = 1;
    }
    if (L420) {
        guard = 0;
    }
    L2C0 = self->v24C();
    if (L2C0 && hurt &&
        (self->v294(0x64, 0, cmd->m0, self->mC) & 0xFF) != 0) {
        L2C0 = 0;
        res->b42_1 = 1;
    }
    if (L2C0) {
        guard = 1;
    }
    L2B0 = self->v254();
    if (L2B0 && L360 &&
        (self->v298(0x64, 0, cmd->m0, self->mC) & 0xFF) != 0) {
        L2B0 = 0;
        res->b42_2 = 1;
    }
    if (L2B0) {
        guard = 1;
    }
    flags = self->b1C8_1 & 0xFF;
    if (guard) {
        flags = 1;
    }
    if (flags) {
        res->b40_5 = 1;
    }
    if (L1D0 == 3) {
        L340 = 1;
        L350 = 1;
    }
    if (L350) {
        guard = 0;
        flags = 0;
        res->b40_5 = 0;
    }
    L2A0 = 0;
    n = 0;
    if (o23 != 0) {
        t = EquipSlotGetAbilityCompositeId_3a0730(o23);
        t2 = EquipSlotGetAbilityLevel_3a0700(o23);
        if (t == 0x1F41) {
            n = (t2 - 1) * 0x14 + 0x32;
        }
    }
    if ((s32) (100.0f * RandFloat_13c010()) < n && !L350) {
        L2A0 = 1;
    }
    L290 = self->b1C8_2;
    if (L1D0 == 2) {
        L290 = 0;
    }
    L10C = self->m1D0;
    L108 = self->m1D0 + f20;
    self->vF0();
    L180 = self->v228();
    f24 = 1.0f;
    L104 = (f32) (s32) self->m1CC;
    f26 = 0.0f;
    L100 = 1.0f;
    f25 = 1.0f;
    LFC = 1.0f;
    if (prm != 0) {
        L100 = prm->m2C;
        f26 = (f32) prm->m5 / 100.0f;
        if (!(res->m10 <= 0.0f) && !(prm->m30 <= 0.0f)) {
            ftmp = res->m10 / D_0045B080; f25 = 1.0f - (1.0f - prm->m30) * ftmp;
            if (f25 < 0.0f) {
                f25 = 0.0f;
            } else if (!(f25 <= 1.0f)) {
                f25 = 1.0f;
            }
        }
        if (res->m14 >= 2 && !(prm->m34 < 0.0f)) {
            f24 = 1.0f - (f32) (res->m14 - 1) * (1.0f - prm->m34);
            if (f24 < 0.0f) {
                f24 = 0.0f;
            }
        }
    }
    if (L420) {
        if (L3B0 == L3A0) {
            LFC = BtlElemParamGetChainFinishScaleMaybe_3f94b0(D_00483818->m8->m54->m8, L390);
        } else {
            ftmp = D_00483818->m8->m54->m8->mA8;
            LFC = D_00483818->m8->m54->m8->mA4;
            LFC = LFC + (f32) (L3B0 - 1) * ftmp;
        }
    }
    f23 = 1.0f;
    if (L2F0 > 0 && L2F0 < 8) {
        f23 = D_0047D1DC * (f32) (0x64 - self->v188(L2F0, 1));
    }
    if (f23 <= 0.0f) {
        flags = 1;
        f23 = 0.0f;
        res->b40_5 = 1;
    }
    if (L420) {
        flags = 0;
    }
    res->m48 = self->mC8;
    L280 = 0;
    f22 = self->v160(1);
    if (guard) {
        f22 = 10.0f;
    }
    if (!(f22 < 10.0f)) {
        L2E0 = 0;
        L280 = 1;
    }
    LF8 = self->v168(1);
    if (self->v23C() != 0) {
        LF8 = 100.0f;
    }
    if (L1D0 == 1) {
        LF8 = 100.0f;
    }
    LF4 = self->v170(1);
    if (self->v23C() != 0) {
        LF4 = 100.0f;
    }
    if (L1D0 == 1) {
        LF4 = 100.0f;
    }
    L270 = 0;
    L260 = 0;
    LE8 = f29 - f22;
    L250 = 0;
    L240 = 0;
    L230 = 0;
    for (L220 = 0; L220 < 2; L220++) {
        act = L12C8[L220];
        if (act == 0) {
            continue;
        }
        f21 = 1.0f;
        L210 = 0;
        t = act->n1E_0;
        if (t != 0 && t != L30C) {
            f21 *= 0.0f;
            L210 -= 0x64;
        }
        t = act->n1E_4 & 0xFF;
        if (t != 0 && t == L30C) {
            f21 *= 0.0f;
            L210 -= 0x64;
        }
        if (L30C != 0) {
            t = act->n1F_0;
            if (t != 0 && t == L30C) {
                f21 = f21 * 1.25f;
                L210 += 0x19;
            }
            t = act->n1F_4 & 0xFF;
            if (t != 0 && t == L30C) {
                f21 = f21 * 0.75f;
                L210 -= 0x19;
            }
        }
        L200 = 0;
        {
            void *p = act;
            if (act != 0) {
                p = &act->m4;
            }
            IterInit_370170(&L12C0, p);
        }
        while ((((eff = IterNext_370040(&L12C0)) != 0) ^ 1) == 0 && res->m1A < 4) {
            def = eff->m4;
            if (def == 0) {
                continue;
            }
            rank = 0;
            L1E0 = eff->m2 + L210;
            L1F0 = 1;
            if ((self->v5C() == 0x2EE4 || self->v5C() == 0x3101) && L3D8 != 0 &&
                *L3D8->m10 == 0x3F07) {
                rank = -0x64;
                L1F0 = 1;
                guard = 0;
                flags = 0;
                L1E0 = 0x64;
            }
            if (!L1F0) {
                continue;
            }
            kind = def->m0;
            switch (kind) {
            case 0x0:
                f30 = f30;
                break;
            case 0x1:
                if (L270) {
                    break;
                }
                L270 = 1;
                if (L400) {
                    pty = D_00483818->m20->m238;
                    if (pty != 0) {
                        PartySub *s = &pty->m168;
                        if (pty->m2C == 1 && L3E0 != pty->m2E) {
                            s->bA_2 = 1;
                        }
                    }
                }
                f30 = 0.0f;
                if (L350 && !guard) {
                    acc = (f32) L340;
                    amount = L340;
                } else {
                    acc = 0.0f;
                    if (!(f26 <= acc)) {
                    oTmp = ActorCastToUnit_3b8770(self);
                    if (oTmp != 0 && oTmp->v3C0() != 0) {
                        f26 /= 2.0f;
                    }
                    t = self->v128(1);
                    acc = (f32) (s32) ((f32) t * f26);
                    amount = (s32) acc;
                } else {
                    f31 = (f32) pow;
                    tune = D_00483818->m8->m54->m8;
                    ftmp = tune->m94;
                    ftmp = ftmp * (f31 * (f31 / (f32) L2D0));
                    LF0 = L118 * (ftmp * L100);
                    if (L400) {
                        f30 = f31;
                    } else {
                        f30 = L110;
                    }
                    LEC = tune->m98;
                    for (i = 0; i < 5; i++) {
                        f32 hit = (f32) self->v178(i, 1);
                        f32 l = L1240[i];
                        f32 t = ((100.0f - hit) / 100.0f) * (f30 * (l * LEC));
                        t = t;
                        acc += t;
                    }
                    f30 = L114 * (LF0 + acc);
                    if (L420) {
                        acc = L11C * (f30 * LFC);
                    } else {
                        ftmp = D_00483818->m8->m54->m8->m9C;
                        acc = ftmp + f21 * (f24 * (f25 * (f30 * f23)));
                        ftmp = f31 * D_00483818->m8->m54->m8->mA0;
                        if (!(acc <= ftmp)) {
                            acc = ftmp;
                        }
                    }
                    amount = (s32) acc;
                    if (amount <= 0) {
                        amount = 1;
                    }
                }
                }
                rank2 = 1;
                t = self->v128(1);
                ftmp = (f32) amount / (f32) t;
                if (!(ftmp < D_0047D28C)) {
                    rank2 = 5;
                } else if (!(ftmp < D_0047D1E8)) {
                    rank2 = 4;
                } else if (!(ftmp < 0.25f)) {
                    rank2 = 3;
                }
                if (!L180 && L320) {
                    t = self->vF0();
                    if (t < amount) {
                        amount = t - 1;
                    }
                }
                if (flags && !guard) {
                    f32 pct = f27 / 100.0f;
                    f32 b8 = D_00483818->m8->m54->m8->mB8;
                    if (rank2 > 1 && !(b8 <= pct)) {
                        amount = (s32) (D_0047D258 + acc * b8);
                        res->b40_6 = 1;
                    } else {
                        amount = (s32) (D_0047D258 + acc * pct);
                        if (amount == 0) {
                            self->m1D0 = 0.0f;
                        }
                    }
                }
                L1D4 = 1;
                if (rank2 > 1 && L310) {
                    L1D4 = rank2;
                }
                if (guard) {
                    self->m1D0 = 0.0f;
                    amount = 0;
                    L1D4 = 1;
                }
                if (L2A0) {
                    amount = 0;
                    L1D4 = 1;
                }
                if (CharaSysGetEncounterIdMaybe_3a36d0(D_00483818->m20) == 0x3EB && L41C != 0 &&
                    self->v48() != 0 && L41C->v5C() != 0x2AF9 && amount >= 3) {
                    amount = (s32) (3.0f * RandFloat_13c010()) + 1;
                    L1D4 = 1;
                }
                if ((self->v5C() == 0x2EE4 || self->v5C() == 0x3101) &&
                    self->v19C(4) == 0) {
                    amount = 0;
                    L1D4 = 1;
                }
                L160 = self->vF0();
                L1CC = amount;
                if (amount > 0) {
                    if (L420 && L3B0 == L3A0) {
                        PlayStatBumpChainFinishMaybe_3a1aa0(D_00483818->m20, L3E0);
                    }
                    L1C8 = ActorCastToUnit_3b8770(self);
                    oSub = 0;
                    L1B0 = 0;
                    if (L1C8 != 0) {
                        oSub = L1C8->v3D8();
                        if (oSub != 0) {
                            t = L1C8->v3E4();
                            if (t > 0) {
                                t2 = (s32) (((f32) amount / 100.0f) * (f32) t);
                                L1B0 = t2;
                                amount -= t2;
                            }
                        }
                    }
                    if (amount > 0) {
                        if (L33C != 0) {
                            if (ObjMgrCountActiveMaybe_3bacc0(D_00483818->m1C, -1, 0, 0) >= 2) {
                                CharaSysEventLogRecord_3a3320(D_00483818->m20, cmd->m0, self->mC,
                                             0x83, amount);
                            } else {
                                CharaSysEventLogRecord_3a3320(D_00483818->m20, cmd->m0, self->mC,
                                             0x84, amount);
                            }
                        } else {
                            CharaSysEventLogRecord_3a3320(D_00483818->m20, cmd->m0, self->mC,
                                         0x84, amount);
                        }
                    }
                    if (L420) {
                        L1CC = self->v2A0(amount, 1);
                        if (oSub != 0 && L1B0 > 0) {
                            oSub->v2A0(L1B0, 0);
                        }
                    } else {
                        L1CC = self->v29C(amount, 1);
                        if (oSub != 0 && L1B0 > 0) {
                            oSub->v29C(L1B0, 0);
                        }
                    }
                    L260 += amount;
                }
                L150 = self->vF0();
                {
                    Ent *e = &res->ent[n = res->m1A];
                    res->m1A = (s16) (n + 1);
                    {
                        res->ent[n].m4 = 0;
                        res->ent[n].m0 = 0;
                        res->ent[n].m2 = 1;
                        res->ent[n].b1_0 = 0;
                        if (amount > 0) {
                            e->m4 = amount;
                            e->m0 = 1;
                            e->m2 = (s8) L1D4;
                            e->b1_0 = 1;
                        } else if (flags) {
                            e->m4 = 0;
                            if (L2C0 || L2B0 || guard) {
                                e->m0 = 6;
                                if (L2C0) {
                                    CharaSysEventLogRecordOpenHud_3a3260(D_00483818->m20, cmd->m0, self->mC, 0x47, 1);
                                }
                                if (L2B0) {
                                    CharaSysEventLogRecordOpenHud_3a3260(D_00483818->m20, cmd->m0, self->mC, 0x48, 1);
                                }
                            } else if (L380 >= 0) {
                                e->m0 = 6;
                            } else if (f23 == 0.0f) {
                                e->m0 = 6;
                            } else {
                                e->m0 = 0;
                            }
                            e->m2 = 1;
                            e->b1_0 = 1;
                        } else if (L2A0) {
                            e->m4 = 0;
                            e->m0 = 5;
                            e->m2 = 1;
                            e->b1_0 = 1;
                        } else {
                            e->m4 = 0;
                            e->m0 = 1;
                            e->m2 = 1;
                            e->b1_0 = 1;
                        }
                    }
                    t = act->m20;
                    if (t != 0 && L220 == 0) {
                        ActionResultListAddUniqueRelated_3a6c50((u8 *) res + 0x18, t);
                    }
                    if (!((f32) L1CC <= 0.0f)) {
                        res->b40_0 = 1;
                    }
                    if (!L290 && !((f32) L1CC <= 0.0f) &&
                        (LF8 <= L108 ||
                         amount >= (s32) (D_0047D240 * (f32) self->v128(1)))) {
                        res->b40_1 = 1;
                        self->m1D0 = 0.0f;
                    } else {
                        self->m1D0 = L108;
                    }
                    ok = 0;
                    if (!L280) {
                        if (!(f29 <= f22) && res->b40_1 != 0 &&
                            (!(L10C < 1.0f) || !(LE8 < 1.0f))) {
                            ok = 1;
                        } else if (L2E0) {
                            ok = 1;
                        }
                    }
                    if (ok) {
                        res->b40_1 = 0;
                        res->b40_3 = 0;
                        res->b40_4 = 1;
                        t = e->m0;
                        if (t != 6 && t != 1) {
                            e->m0 = 0;
                        }
                    }
                }
                if (flags && !guard && !(f27 <= 0.0f) &&
                    !((f32) L1CC <= 0.0f)) {
                    res->b40_7 = 1;
                    res->b40_5 = 0;
                }
                if (flags && !guard && !(f28 <= LF4)) {
                    res->b40_7 = 0;
                    res->b40_6 = 1;
                    res->b40_5 = 0;
                    t = res->ent[n].m0;
                    if (t != 6 && t != 1) {
                        res->ent[n].m0 = 0;
                    }
                }
                if (L2A0) {
                    res->b40_0 = 0;
                    res->b40_7 = 0;
                    res->b40_6 = 0;
                    res->b40_5 = 0;
                    res->b40_1 = 0;
                    res->b40_2 = 1;
                    res->b40_4 = 0;
                    res->b40_3 = 0;
                    res->b41_1 = 0;
                    res->b41_2 = 0;
                }
                if (flags && (f32) L1CC <= 0.0f && res->b40_6 == 0) {
                    res->b41_1 = 1;
                    res->b41_2 = 1;
                }
                ok = 1;
                if (prm != 0 && !(prm->m0 != 0x262 && prm->m0 != 0x263)) {
                    ok = 0;
                }
                if (!(cmd->m1C != 5 && cmd->m1C != 6)) {
                    ok = 0;
                }
                if (D_00483818->m20->b24C_0 == 0) {
                    ok = 0;
                }
                if (L420) {
                    ok = 0;
                    if (L3B0 >= L3A0 && (self->v1BC(0xA, 0x64, 0, 1) & 0xFF) != 0) {
                        res->b41_0 = 1;
                        res->b40_3 = 0;
                        res->b40_6 = 0;
                        res->b41_1 = 0;
                        res->b41_2 = 0;
                        self->m1CC = 0.0f;
                    }
                }
                if (!((f32) amount <= 0.0f) && self->vC0() == 0 && ok) {
                    ftmp = L104 + (f32) amount;
                    self->m1CC = ftmp;
                    L104 = ftmp;
                    if (!(self->m1CC < D_0047D28C * (f32) self->v128(1)) &&
                        (self->v1BC(0xA, 0x64, 0, 1) & 0xFF) != 0) {
                        res->b41_0 = 1;
                        res->b40_3 = 0;
                        res->b40_6 = 0;
                        res->b41_1 = 0;
                        res->b41_2 = 0;
                        self->m1CC = 0.0f;
                    }
                }
                if (prm != 0) {
                    s32 id = prm->m0;
                    if (!(id != 0x258 && id != 0x259)) {
                        if (ok && (self->v1BC(0xA, 0x64, 0, 1) & 0xFF) != 0) {
                            res->b41_0 = 1;
                            res->b40_3 = 0;
                            res->b40_6 = 0;
                            res->b41_2 = 0;
                            self->m1CC = 0.0f;
                        }
                        res->b41_1 = 0;
                    } else if (id == 0x25A || id == 0x260 || id == 0x25B ||
                               id == 0x25D || id == 0x264 || id == 0x25E) {
                        if (ok && (self->v1BC(5, 0x64, 0, 1) & 0xFF) != 0) {
                            res->b41_0 = 1;
                            res->b40_3 = 0;
                            res->b40_6 = 0;
                            res->b41_2 = 0;
                            res->b40_4 = 1;
                            self->m1CC = 0.0f;
                        }
                        res->b41_1 = 0;
                    } else if (id == 0x25C) {
                        if (ok && (self->v1BC(0xA, 0x64, 0, 1) & 0xFF) != 0) {
                            Ref *r;
                            res->b41_0 = 1;
                            res->b40_3 = 0;
                            res->b40_6 = 0;
                            res->b41_2 = 0;
                            res->b40_4 = 1;
                            self->m1CC = 0.0f;
                            oTmp = D_0048381C->m58->m8;
                            if (oTmp != 0) {
                                r = (Ref *) oTmp->v70(0xA);
                            } else {
                                r = 0;
                            }
                            if (r != 0) {
                                self->mD0[r->m3C] = self->mD0[r->m3C] / 2.0f;
                            }
                        }
                        res->b41_1 = 0;
                    }
                    id = prm->m0;
                    if (id == 0x25A || id == 0x260 || id == 0x25B) {
                        oTmp = D_0048381C->m5C->m8;
                        ActionResultListAddUniqueRelated_3a6c50((u8 *) res + 0x18, (s32) oTmp->v70(0x650));
                    } else if (id == 0x25D || id == 0x264 || id == 0x25E) {
                        oTmp = D_0048381C->m5C->m8;
                        ActionResultListAddUniqueRelated_3a6c50((u8 *) res + 0x18, (s32) oTmp->v70(0x651));
                    }
                }
                if (L420) {
                    res->b40_1 = 1;
                    res->b40_3 = 0;
                    res->b41_1 = 0;
                    res->b41_2 = 0;
                    if (L3B0 == L3A0) {
                        res->b40_1 = 0;
                        res->b40_4 = 1;
                    }
                    self->m1CC = 0.0f;
                }
                if (prm != 0 && !(prm->m0 != 0x262 && prm->m0 != 0x263) &&
                    !L290 && !L280) {
                    res->b40_1 = 0;
                    res->b40_4 = 1;
                }
                if (res->b41_1 != 0) {
                    if (L3C0 == 1) {
                        if (L3DC == 0x2AF9 || L3DC == 0x2AFB || L3DC == 0x2B00 ||
                            L3DC == 0x2AFD || L3DC == 0x2AFF || L3DC == 0x2AFA) {
                            res->b41_1 = 0;
                        }
                    } else if (L3C0 == 0 && L3DC == 0x2AFE) {
                        res->b41_1 = 0;
                    }
                }
                if (flags && self->vBC() != 0 && self->b1C0_0 == 0) {
                    self->v26C((f32) D_00465CD0);
                }
                if (!((f32) L1CC <= 0.0f) && self->vC0() == 0 &&
                    self->v48() != 0) {
                    self->m1E0 = self->m1E0 / 2.0f;
                    self->m1E4 = self->m1E4 / 2.0f;
                    self->m1E8 = self->m1E8 / 2.0f;
                }
                if (L400 && L33C != 0 && !L420 && !(f30 <= 0.0f)) {
                    Tri *tri;
                    ok = 1;
                    if (StateFlagTest_3ccd70(D_00483818->m10, 0x3ED) == 0) {
                        ok = 0;
                    }
                    if (ok && CharaSysStateUnitFlag7EBit3Related_3a38e0(D_00483818->m20) == 0) {
                        ok = 0;
                    }
                    tri = 0;
                    if (ok) {
                        tri = L33C->v36C();
                        if (tri != 0) {
                            if (tri->m4 == 0 || tri->m5 == 0 || tri->m7 == 0) {
                                ok = 0;
                            }
                        } else {
                            ok = 0;
                        }
                    }
                    if (ok) {
                        t = self->v128(1);
                        t2 = t / 2;
                        if (L160 < t2 || L150 >= t2) {
                            ok = 0;
                        }
                    }
                    if (ok) {
                        L140 = tri->m4;
                        if ((s32) (100.0f * RandFloat_13c010()) >= (s32) L140) {
                            ok = 0;
                        }
                    }
                    if (tri != 0 && StateFlagTest_3ccd70(D_00483818->m10, 0x3EE) != 0) {
                        ok = 1;
                        StateFlagSet_3ccb70(D_00483818->m10, 0x3EE, 0, 0);
                    }
                    if (ok) {
                        L1A0 = tri->m5;
                        if ((s32) tri->m6 >= 0) {
                        }
                        if ((s32) tri->m7 >= 0) {
                        }
                        f32 base = (f32) tri->m6;
                        L130 = (s32) (base +
                                      (1.0f + ((f32) tri->m7 - base)) *
                                          RandFloat_13c010());
                        t = 0;
                        for (i = 0; i < L130; i++) {
                            if (CharaSysStatusAdd_3a1630(D_00483824, L1A0) == 0) {
                                break;
                            }
                            t++;
                        }
                        if (t > 0) {
                            res->b43_0 = t;
                            res->b40_1 = 1;
                        }
                    }
                }
                if (guard) {
                    L200 = 1;
                } else if (L2A0) {
                    L200 = 1;
                } else if (flags && (f32) L1CC <= 0.0f) {
                    L200 = 1;
                } else if (L420) {
                    L200 = 1;
                } else if (L350) {
                    L200 = 1;
                }
                break;
            case 0x3:
                amount = 0;
                t2 = -1;
                if (self->vBC() != 0) {
                    Prm *q = (Prm *) *(s32 *) &cmd->mC;
                    if (q != 0) {
                        t2 = q->m0;
                    }
                    switch (t2) {
                    case 0x40C4:
                    case 0x40C6:
                        n = self->v128(1) / 2;
                        break;
                    case 0x40C5:
                    case 0x40C7:
                    case 0x40CA:
                    case 0x40CB:
                    case 0x41AA:
                    case 0x40D6:
                    case 0x40D7:
                    case 0x40D8:
                        n = self->v128(1);
                        break;
                    default:
                        n = self->v128(1);
                        break;
                    }
                    t = self->vF0();
                    self->vF8(n);
                    amount = self->vF0() - t;
                }
                {
                    Ent *e = &res->ent[n = res->m1A];
                    res->m1A = (s16) (n + 1);
                    if (amount > 0) {
                        e->m4 = amount;
                        e->m0 = 3;
                        e->b1_0 = 1;
                        res->m18 = 1;
                        t = act->m20;
                        if (t != 0 && L220 == 0) {
                            ActionResultListAddUniqueRelated_3a6c50((u8 *) res + 0x18, t);
                        }
                    } else {
                        e->m4 = 0;
                        e->m0 = 0;
                        e->b1_0 = 0;
                    }
                }
                L250 += amount;
                PlayStatBumpHealCountMaybe_3c0650(D_00483818->m18, self->mC);
                PlayStatAddHealAmountMaybe_3c05c0(D_00483818->m18, self->mC, amount);
                break;
            case 0x5:
                amount = 0;
                t2 = -1;
                if (self->vBC() != 0) {
                    Prm *q = (Prm *) *(s32 *) &cmd->mC;
                    if (q != 0) {
                        t2 = q->m0;
                    }
                    switch (t2) {
                    case 0x40C8:
                    case 0x40C9:
                    case 0x40CA:
                    case 0x40CB:
                    case 0x41AA:
                        n = self->v130(1);
                        break;
                    default:
                        n = self->v130(1);
                        break;
                    }
                    t = self->v10C();
                    self->v114(n);
                    amount = self->v10C() - t;
                }
                {
                    Ent *e = &res->ent[n = res->m1A];
                    res->m1A = (s16) (n + 1);
                    if (amount > 0) {
                        e->m4 = amount;
                        e->m0 = 4;
                        e->b1_0 = 1;
                        res->m18 = 1;
                        t = act->m20;
                        if (t != 0 && L220 == 0) {
                            ActionResultListAddUniqueRelated_3a6c50((u8 *) res + 0x18, t);
                        }
                    } else {
                        e->m4 = 0;
                        e->m0 = 0;
                        e->b1_0 = 0;
                    }
                }
                L240 += amount;
                break;
            case 0xA:
                if (guard) {
                    rank = 0xC8;
                }
                res->m18 = self->v290(L1E0, rank, cmd->m0, self->mC);
                {
                    Ent *e = &res->ent[n = res->m1A];
                    res->m1A = (s16) (n + 1);
                    e->m4 = 0;
                    if (res->m18 != 0) {
                        e->m0 = 7;
                    } else if (L37C == 0x1F47 || L37C == 0xFA7) {
                        e->m0 = 5;
                    } else {
                        e->m0 = 0;
                    }
                    e->m2 = 1;
                    e->b1_0 = 1;
                }
                t = act->m20;
                if (t != 0 && L220 == 0) {
                    ActionResultListAddUniqueRelated_3a6c50((u8 *) res + 0x18, t);
                }
                break;
            case 0xB:
                t = self->vC0() & 0xFF;
                self->v2BC(0.0f, 0);
                t2 = self->vBC() & 0xFF;
                if (t != 0 && t2 != 0) {
                    res->m18 = 1;
                    L230 = 1;
                    CharaSysEventLogRecord_3a3320(D_00483818->m20, cmd->m0, self->mC, def->m0,
                                 1);
                    PlayStatBumpReviveCountMaybe_3c0540(D_00483818->m18, self->mC);
                    {
                        Ent *e = &res->ent[n = res->m1A];
                        res->m1A = (s16) (n + 1);
                        e->m4 = 0;
                    }
                    res->ent[n].m0 = 8;
                    res->ent[n].m2 = 1;
                    res->ent[n].b1_0 = 1;
                    t = act->m20;
                    if (t != 0 && L220 == 0) {
                        ActionResultListAddUniqueRelated_3a6c50((u8 *) res + 0x18, t);
                    }
                } else {
                    Prm *q = (Prm *) *(s32 *) &cmd->mC;
                    if (q != 0 && q->m0 == 0x40D6) {
                        L200 = 1;
                    }
                }
                break;
            case 0x13: {
                Mask64 c = self->v198();
                self->v1A0(6, 0, 0);
                self->v1A0(0x2C, 0, 0);
                Mask64 d = self->v198();
                Mask xv = xor64(c, d);
                if (xv != 0) {
                    res->m18 = 1;
                    CharaSysEventLogRecord_3a3320(D_00483818->m20, cmd->m0, self->mC, def->m0,
                                 1);
                    PlayStatBumpCureCountMaybe_3c04c0(D_00483818->m18, self->mC);
                    {
                        Ent *e = &res->ent[n = res->m1A];
                        res->m1A = (s16) (n + 1);
                        e->m4 = 0;
                    }
                    res->ent[n].m0 = 0xA;
                    res->ent[n].m2 = 1;
                    res->ent[n].b1_0 = 1;
                    t = act->m20;
                    if (t != 0 && L220 == 0) {
                        ActionResultListAddUniqueRelated_3a6c50((u8 *) res + 0x18, t);
                    }
                }
                break;
            }
            case 0x1E: {
                Mask64 c = self->v198();
                self->v1A0(9, 0, 0);
                self->v1A0(8, 0, 0);
                self->v1A0(7, 0, 0);
                self->v1A0(6, 0, 0);
                self->v1A0(0x2C, 0, 0);
                self->v1A0(5, 0, 0);
                self->v1A0(4, 0, 0);
                self->v1A0(3, 0, 0);
                self->v1A0(2, 0, 0);
                self->v1A0(0xA, 0, 0);
                Mask64 d = self->v198();
                Mask xv = xor64(c, d);
                if (xv != 0) {
                    res->m18 = 1;
                    CharaSysEventLogRecord_3a3320(D_00483818->m20, cmd->m0, self->mC, def->m0,
                                 1);
                    PlayStatBumpCureCountMaybe_3c04c0(D_00483818->m18, self->mC);
                    {
                        Ent *e = &res->ent[n = res->m1A];
                        res->m1A = (s16) (n + 1);
                        e->m4 = 0;
                    }
                    res->ent[n].m0 = 0xA;
                    res->ent[n].m2 = 1;
                    res->ent[n].b1_0 = 1;
                    t = act->m20;
                    if (t != 0 && L220 == 0) {
                        ActionResultListAddUniqueRelated_3a6c50((u8 *) res + 0x18, t);
                    }
                }
                break;
            }
            case 0x1F:
                oTmp = self;
                {
                    VObj *h = ActorCastToUnit_3b8770(self);
                    if (h != 0) {
                        VObj *g = h->v3D8();
                        if (g != 0) {
                            oTmp = g;
                        }
                    }
                }
                L120 = oTmp->v19C(0x1F) & 0xFF;
                t = ObjHasMonographAttachPointMaybe_2d0840(oTmp->mC) & 0xFF;
                if (t != 0 && CharaSysGetEncounterIdMaybe_3a36d0(D_00483818->m20) == 0x3EB &&
                    StateVarGet_3ccac0(D_00483818->m10, 0) >= 3) {
                    t = 0;
                }
                if (t != 0) {
                    oTmp->v1A0(0x1F, 1, 1);
                }
                t2 = oTmp->v19C(0x1F) & 0xFF;
                n = -1;
                if (L120 == 0 && t2 != 0) {
                    res->m18 = 1;
                    EvSpawnChrMonographs_2e91e0(GetEventObjMgr_2d1960(), oTmp->mC, 0.0f, 10.0f);
                    n = 0x1F;
                } else if (L120 == 0 && t2 == 0) {
                    n = 0x45;
                }
                if (n > 0) {
                    CharaSysEventLogRecordOpenHud_3a3260(D_00483818->m20, cmd->m0, self->mC, n, 1);
                }
                break;
            case 0x3B:
                res->m18 = self->v294(L1E0, rank, cmd->m0, self->mC);
                if (res->m18 != 0) {
                    res->b42_1 = 1;
                }
                break;
            case 0x3C:
                res->m18 = self->v298(L1E0, rank, cmd->m0, self->mC);
                if (res->m18 != 0) {
                    res->b42_2 = 1;
                }
                break;
            default:
                if (guard) {
                    rank = 0xC8;
                }
                if (def->m4 == 3) {
                    res->m18 = self->v28C(def->m8, def->m6 == 3, L1E0, rank,
                                          cmd->m0, self->mC, (s16) kind, 1);
                    if (def->m6 == 4) {
                        PlayStatBumpCureCountMaybe_3c04c0(D_00483818->m18, self->mC);
                    }
                    t = 9;
                    if (def->m6 == 4) {
                        t = 0xA;
                    }
                    {
                        Ent *e = &res->ent[n = res->m1A];
                        res->m1A = (s16) (n + 1);
                        e->m4 = 0;
                    if (def->m6 == 3) {
                        e->m0 = (u8) (res->m18 != 0 ? t : 0);
                        if (res->m18 == 0 &&
                            !(def->m0 != 0x38 && def->m0 != 0x39)) {
                            e->m0 = 5;
                        }
                    } else {
                        e->m0 = (u8) (res->m18 != 0 ? t : 0);
                    }
                    e->m2 = 1;
                    e->b1_0 = 1;
                    }
                    t = act->m20;
                    if (t != 0 && L220 == 0) {
                        ActionResultListAddUniqueRelated_3a6c50((u8 *) res + 0x18, t);
                    }
                }
                break;
            }
            if (self->vC0() != 0) {
                L200 = 1;
            }
            if (L200) {
                break;
            }
        }
        if (L200) {
            break;
        }
    }
    if (L250 > 0) {
        CharaSysEventLogRecord_3a3320(D_00483818->m20, cmd->m0, self->mC, 3, L250);
    }
    if (L240 > 0) {
        CharaSysEventLogRecord_3a3320(D_00483818->m20, cmd->m0, self->mC, 5, L240);
    }
    if (res->b40_1 != 0 && self->vA0() == 0) {
        res->b40_1 = 0;
    }
    if (res->b40_3 != 0 && self->vA8() == 0) {
        res->b40_3 = 0;
    }
    if (res->b40_4 != 0 && self->vA4() == 0) {
        res->b40_3 = 0;
    }
    if (res->b40_6 != 0 && self->v9C() == 0) {
        res->b40_3 = 0;
    }
    pty = D_00483818->m20->m238;
    if (pty != 0) {
        if (L41C != 0 && L3F0 && res->b41_2 != 0) {
            pty->m1BC = (s16) (pty->m1BC + 1);
        }
        oTmp = ActorCastToChara_3b87b0(self);
        if (oTmp != 0 && CharaIsPartyLeader_3ae1a0(oTmp) != 0 && res->b40_0 != 0) {
            pty->m1BE = (s16) (pty->m1BE + 1);
        }
    }
    res->m50 = self->mC8;
    mMask = ((Mask) 0xFFFF << 0x20) | ((Mask) 0xFFFF << 0x10) | 0xFFFF;
    masks(res, mMask);
    self->v288(res, L260, L250, L230, L180, mMask);
    return 1;
}
