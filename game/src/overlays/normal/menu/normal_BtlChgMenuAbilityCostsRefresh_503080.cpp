/* rgp:protos */
#line 1
#include "types.h"
/* normal 0x00503080 -- the three-slot party-member strip of the battle-result
 * scene.  FRESH, session 31, lane n31e.
 *
 * TWO VIRTUAL CALLS (`lw $25,0($16) / lw $25,K($25) / jalr $25`), so this unit
 * is .cpp -- [[jalr-is-cpp-virtual]].  vptr offset 0, slot = 8 + 4*N, so
 * 0x10C is index 65 and 0x2D0 is index 178.  Index 65 is the SAME `count()`
 * the merged sibling normal_BtlChgMenuAbilityListOpenState_502970.cpp already names at 0x10C, which is
 * an independent confirmation of the slot arithmetic on this class.
 *
 * Everything structural here is lifted from that merged, byte-identical
 * sibling: the Iter/tmp pair (`func_3A8180(tmp, ob, 0, -1)` then
 * `func_370170(&it, tmp)` then `it.f004` as the count), the
 * `func_3C2FB0(root->f018, normal_BtlChgPageGetMember_505f90(D_00484454))` line, and the
 * gp names D_00484454 / D_0048449C / D_004844A0 / D_004844C0.
 *
 * m2c type census (whole unit):
 *  - `dsll32 $7,$22,0 / dsra32 $7,$7,0` before func_291250 is the s32->s64
 *    widening pair, so func_291250's 4th parameter is `s64` and the value
 *    passed is `s32` -- [[mwcc-s32-s64-widening-pair]].  m2c typed
 *    func_3A05C0/func_3F5CA0 `s64`; they are `s32`.
 *  - `daddiu $23,$0,1` for the all-owned flag is the C++ `bool` tell, not an
 *    s32 1 -- see [[jalr-is-cpp-virtual]] ("bool REACHES daddiu").
 *  - `lbu $2,3($19)` is a u8 member, stored to a compiler SPILL slot at
 *    0xE0; 0xB0/0xC0 are sq/lq spills too.  The only DECLARED stack locals are
 *    `it` (0x108) and `tmp` (0xF0).
 *  - D_004844C0 is f32 here (lwc1/swc1) even though 00502970 declares it s32;
 *    `= 0.0f` is what emits retail's `sw $0`.
 *
 * s32 lane nc32c -- CLOSED the last 2 words (243 w, 2 bad -> MATCH).
 * The residue was `daddu $5,$2,$0` / `addiu $4,$29,0xF0` emitted in the WRONG
 * ORDER and argument 2 sourced from `ob`'s home $16 instead of the raw return
 * register $2.  It is NOT a property of the call site: a 10-arm prototype /
 * stack-address / constant deck (s32 recon) and a 729-arm pool sweep over 172
 * distinct objects both read ZERO.  The lever is TWO NAMES FOR ONE VALUE:
 *
 *     ob = t = func_3C2FB0(...);
 *     if (t == 0) return 0;
 *     func_3A8180(tmp, t, 0, -1);      -- the FIRST use reads `t`
 *     ... every later use reads `ob` ...
 *
 * `t` is the short-lived web that dies at the argument copy, so it keeps the
 * call's raw $2; `ob` is the long-lived web and takes $16 for the later uses.
 * mwcc then emits the $5 copy FIRST because it is the argument that owns a
 * dying value.  Measured: `ob = t = call` (g4), `if ((ob = t = call) == 0)`
 * (g5) and `t = ob = call` (g7) are ONE object and all MATCH in all three
 * declaration positions for `t`; `t = call; ob = t;` with the SAME first use
 * (g1/g2/gA/gB) reads 6 bad, and `t = call; if (t==0)...; ob = t;` (g3/g6/g8/
 * g9) collapses back onto the 2-bad park.  So the double assignment in ONE
 * statement is load-bearing, not merely the extra name.
 */

struct Obj {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 count() { return VCM0(s32, 0x10C); }                 /* slot 65 -> vtable +0x10C */
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 held(s16 k) { return VCM(s32, (void *, s16), 0x2D0, k); }              /* slot 178 -> vtable +0x2D0 */
};

typedef struct Ctx  { u8 pad000[0x76]; s16 f076; } Ctx;
typedef struct Root { u8 pad000[0x18]; s32 f018; } Root;
typedef struct Iter { u8 pad000[4];    s16 f004; } Iter;
typedef struct Ent  { s16 f000; u8 f002; u8 f003; } Ent;
typedef struct Widget { u8 pad000[0x16]; s16 f016; s16 f018; } Widget;
typedef struct Res  { u8 pad000[0x24]; Widget *f024; } Res;

extern "C" Ctx  *D_00484454;      /* gp - 0xD1C  */
extern "C" void *D_0048449C;      /* gp - 0xCD4  */
extern "C" void *D_004844A0;      /* gp - 0xCD0  */
extern "C" f32   D_004844C0;      /* gp - 0xCB0  */
extern "C" f32   D_0047D34C;      /* gp - 0x7E24 */
extern "C" f32   D_0047D1FC;      /* gp - 0x7F74 */

extern "C" f32    Sinf_128fd0(f32 v);
extern "C" Root  *GetGameData_1fede0(void);
extern "C" void   UiPageSetSpritePresetMaybe_289090(Ctx *p, u16 id, s32 a, s32 b);
extern "C" void  *UiEntryListGetCurrentData_28ec60(void *p);
extern "C" Res   *UiFindWidget_290460(void *p, u16 id);
extern "C" void   UiSetWidgetColor_2905b0(void *p, u16 id, f32 r, f32 g, f32 b, f32 a);
extern "C" void   UiSetWidgetSubItemValue_291250(void *p, u16 id, s32 a, s64 v);
extern "C" Ent   * IterSeek_36fff0(Iter *, s32, int, int);
extern "C" Ent   *IterNext_370040(Iter *it);
extern "C" void IterInit_370170(Iter *, void *, int, int);
extern "C" s32    EquipSlotGetNthLinkedId_3a04e0(void *h, s32 i);
extern "C" s32    EquipSlotCountLinkedIds_3a0560(void *h);
extern "C" s32    EquipSlotGetScaledCost_3a05c0(void *h);
extern "C" void   CharaAbilityViewCtor_3a8180(void *tmp, Obj *o, s32 a, s32 b);
extern "C" void  *CharaFindSlotByRecId_3ad390(Obj *o, s16 k);
extern "C" s32    PartyFindActiveChara_3c2350(s32 a, s32 b);
extern "C" Obj   *PartyGetSlotChara_3c2fb0(s32 a, s32 b);
extern "C" s32    AbilityDataGetCost_3f5ca0(Ent *e);
extern "C" s32 normal_BtlChgPageSetAbilityTypeIcon_505470(void *p, s32 id, s32 c);
extern "C" s32    normal_BtlChgPageGetMember_505f90(Ctx *p);

extern "C" s32 normal_BtlChgMenuAbilityCostsRefresh_503080(void);

s32 normal_BtlChgMenuAbilityCostsRefresh_503080(void)
{
    __attribute__((aligned(16))) unsigned char rgp_blk1[(0x8 + sizeof(Iter)) + (0x10)];
    Root   *root;
    u16     id;
    Ent    *ent;
    Res    *res;
    Widget *w;
    s32     i;
    bool    ok;
    s32     cnt;
    s32     val;
    s32     n;
    s32     e;
    s32     m;
    void   *h;
    s32     j;
    Obj    *ob;
    Obj    *t;
    u8      tmp[0x10] __attribute__((aligned(16)));
    f32     half;
    f32     v;
    s32     base;

    if (UiEntryListGetCurrentData_28ec60(D_004844A0) == 0) {
        return 0;
    }
    base = D_00484454->f076;
    root = GetGameData_1fede0();
    if (root == 0) {
        return 0;
    }
    ob = t = PartyGetSlotChara_3c2fb0(root->f018, normal_BtlChgPageGetMember_505f90(D_00484454));
    if (t == 0) {
        return 0;
    }
    CharaAbilityViewCtor_3a8180(tmp, t, 0, -1);
    IterInit_370170(&(*(Iter *)(rgp_blk1 + 0x8)), tmp, 0, 0);
    cnt = (*(Iter *)(rgp_blk1 + 0x8)).f004;
    ent = IterSeek_36fff0(&(*(Iter *)(rgp_blk1 + 0x8)), base, 0, 0);
    half = 0.5f + Sinf_128fd0(D_004844C0) / 2.0f;
    v = D_004844C0 + D_0047D34C;
    D_004844C0 = v;
    if (!(v < D_0047D1FC)) {
        D_004844C0 = 0.0f;
    }
    for (i = 0; i < 3; i++) {
        if (base + i < cnt && ent != 0) {
            id = i * 3 + 6;
            res = UiFindWidget_290460(D_0048449C, id);
            if (res == 0) {
                return 0;
            }
            w = res->f024;
            if (w == 0) {
                return 0;
            }
            w->f016 = 0xC;
            w->f018 = 0xF;
            h = CharaFindSlotByRecId_3ad390(ob, ent->f000);
            if (h != 0) {
                val = EquipSlotGetScaledCost_3a05c0(h);
            } else {
                val = AbilityDataGetCost_3f5ca0(ent);
            }
            n = ent->f003;
            UiSetWidgetSubItemValue_291250(D_0048449C, id, 0, val);
            UiSetWidgetColor_2905b0(D_0048449C, id, 1.0f, 1.0f, 1.0f, -1.0f);
            ok = true;
            m = EquipSlotCountLinkedIds_3a0560(h);
            for (j = 0; j < m; j++) {
                e = ((short)EquipSlotGetNthLinkedId_3a04e0(h, j));
                if (PartyFindActiveChara_3c2350(GetGameData_1fede0()->f018, e) == 0) {
                    ok = false;
                    break;
                }
            }
            if (ob->held(ent->f000) == 0) {
                UiSetWidgetColor_2905b0(D_0048449C, id, half, half, half, -1.0f);
                if (!ok) {
                    if (!(ob->count() < val)) {
                        UiSetWidgetColor_2905b0(D_0048449C, id, 1.0f, 1.0f, 1.0f, -1.0f);
                    }
                }
            }
            normal_BtlChgPageSetAbilityTypeIcon_505470(D_00484454, (u16)(i + 0x11), n);
            normal_BtlChgPageSetAbilityTypeIcon_505470(D_00484454, (u16)(i + 0x15), -1);
        } else {
            id = i * 3 + 6;
            res = UiFindWidget_290460(D_0048449C, id);
            if (res == 0) {
                return 0;
            }
            w = res->f024;
            if (w == 0) {
                return 0;
            }
            w->f018 = 0;
            w->f016 = 0;
            UiSetWidgetSubItemValue_291250(D_0048449C, id, 0, 0);
            UiPageSetSpritePresetMaybe_289090(D_00484454, i + 0x11, 0, 0);
            UiPageSetSpritePresetMaybe_289090(D_00484454, i + 0x15, -1, 0);
        }
        ent = IterNext_370040(&(*(Iter *)(rgp_blk1 + 0x8)));
    }
    return 1;
}
