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
    virtual void s000();
    virtual void s001();
    virtual void s002();
    virtual void s003();
    virtual void s004();
    virtual void s005();
    virtual void s006();
    virtual void s007();
    virtual void s008();
    virtual void s009();
    virtual void s010();
    virtual void s011();
    virtual void s012();
    virtual void s013();
    virtual void s014();
    virtual void s015();
    virtual void s016();
    virtual void s017();
    virtual void s018();
    virtual void s019();
    virtual void s020();
    virtual void s021();
    virtual void s022();
    virtual void s023();
    virtual void s024();
    virtual void s025();
    virtual void s026();
    virtual void s027();
    virtual void s028();
    virtual void s029();
    virtual void s030();
    virtual void s031();
    virtual void s032();
    virtual void s033();
    virtual void s034();
    virtual void s035();
    virtual void s036();
    virtual void s037();
    virtual void s038();
    virtual void s039();
    virtual void s040();
    virtual void s041();
    virtual void s042();
    virtual void s043();
    virtual void s044();
    virtual void s045();
    virtual void s046();
    virtual void s047();
    virtual void s048();
    virtual void s049();
    virtual void s050();
    virtual void s051();
    virtual void s052();
    virtual void s053();
    virtual void s054();
    virtual void s055();
    virtual void s056();
    virtual void s057();
    virtual void s058();
    virtual void s059();
    virtual void s060();
    virtual void s061();
    virtual void s062();
    virtual void s063();
    virtual void s064();
    virtual s32 count();                 /* slot 65 -> vtable +0x10C */
    virtual void s066();
    virtual void s067();
    virtual void s068();
    virtual void s069();
    virtual void s070();
    virtual void s071();
    virtual void s072();
    virtual void s073();
    virtual void s074();
    virtual void s075();
    virtual void s076();
    virtual void s077();
    virtual void s078();
    virtual void s079();
    virtual void s080();
    virtual void s081();
    virtual void s082();
    virtual void s083();
    virtual void s084();
    virtual void s085();
    virtual void s086();
    virtual void s087();
    virtual void s088();
    virtual void s089();
    virtual void s090();
    virtual void s091();
    virtual void s092();
    virtual void s093();
    virtual void s094();
    virtual void s095();
    virtual void s096();
    virtual void s097();
    virtual void s098();
    virtual void s099();
    virtual void s100();
    virtual void s101();
    virtual void s102();
    virtual void s103();
    virtual void s104();
    virtual void s105();
    virtual void s106();
    virtual void s107();
    virtual void s108();
    virtual void s109();
    virtual void s110();
    virtual void s111();
    virtual void s112();
    virtual void s113();
    virtual void s114();
    virtual void s115();
    virtual void s116();
    virtual void s117();
    virtual void s118();
    virtual void s119();
    virtual void s120();
    virtual void s121();
    virtual void s122();
    virtual void s123();
    virtual void s124();
    virtual void s125();
    virtual void s126();
    virtual void s127();
    virtual void s128();
    virtual void s129();
    virtual void s130();
    virtual void s131();
    virtual void s132();
    virtual void s133();
    virtual void s134();
    virtual void s135();
    virtual void s136();
    virtual void s137();
    virtual void s138();
    virtual void s139();
    virtual void s140();
    virtual void s141();
    virtual void s142();
    virtual void s143();
    virtual void s144();
    virtual void s145();
    virtual void s146();
    virtual void s147();
    virtual void s148();
    virtual void s149();
    virtual void s150();
    virtual void s151();
    virtual void s152();
    virtual void s153();
    virtual void s154();
    virtual void s155();
    virtual void s156();
    virtual void s157();
    virtual void s158();
    virtual void s159();
    virtual void s160();
    virtual void s161();
    virtual void s162();
    virtual void s163();
    virtual void s164();
    virtual void s165();
    virtual void s166();
    virtual void s167();
    virtual void s168();
    virtual void s169();
    virtual void s170();
    virtual void s171();
    virtual void s172();
    virtual void s173();
    virtual void s174();
    virtual void s175();
    virtual void s176();
    virtual void s177();
    virtual s32 held(s16 k);              /* slot 178 -> vtable +0x2D0 */
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

extern "C" f32    func_128FD0(f32 v);
extern "C" Root  *func_1FEDE0(void);
extern "C" void   func_289090(Ctx *p, u16 id, s32 a, s32 b);
extern "C" void  *func_28EC60(void *p);
extern "C" Res   *func_290460(void *p, u16 id);
extern "C" void   func_2905B0(void *p, u16 id, f32 r, f32 g, f32 b, f32 a);
extern "C" void   func_291250(void *p, u16 id, s32 a, s64 v);
extern "C" Ent   *func_36FFF0(Iter *it, s32 n);
extern "C" Ent   *func_370040(Iter *it);
extern "C" void   func_370170(Iter *it, void *src);
extern "C" s32    func_3A04E0(void *h, s32 i);
extern "C" s32    func_3A0560(void *h);
extern "C" s32    func_3A05C0(void *h);
extern "C" void   func_3A8180(void *tmp, Obj *o, s32 a, s32 b);
extern "C" void  *func_3AD390(Obj *o, s16 k);
extern "C" s32    func_3C2350(s32 a, s32 b);
extern "C" Obj   *func_3C2FB0(s32 a, s32 b);
extern "C" s32    func_3F5CA0(Ent *e);
extern "C" s32 normal_BtlChgPageSetAbilityTypeIcon_505470(void *p, s32 id, s32 c);
extern "C" s32    normal_BtlChgPageGetMember_505f90(Ctx *p);

extern "C" s32 normal_BtlChgMenuAbilityCostsRefresh_503080(void);

s32 normal_BtlChgMenuAbilityCostsRefresh_503080(void)
{
    Iter    it;
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
    u8      tmp[0x10];
    f32     half;
    f32     v;
    s32     base;

    if (func_28EC60(D_004844A0) == 0) {
        return 0;
    }
    base = D_00484454->f076;
    root = func_1FEDE0();
    if (root == 0) {
        return 0;
    }
    ob = t = func_3C2FB0(root->f018, normal_BtlChgPageGetMember_505f90(D_00484454));
    if (t == 0) {
        return 0;
    }
    func_3A8180(tmp, t, 0, -1);
    func_370170(&it, tmp);
    cnt = it.f004;
    ent = func_36FFF0(&it, base);
    half = 0.5f + func_128FD0(D_004844C0) / 2.0f;
    v = D_004844C0 + D_0047D34C;
    D_004844C0 = v;
    if (!(v < D_0047D1FC)) {
        D_004844C0 = 0.0f;
    }
    for (i = 0; i < 3; i++) {
        if (base + i < cnt && ent != 0) {
            id = i * 3 + 6;
            res = func_290460(D_0048449C, id);
            if (res == 0) {
                return 0;
            }
            w = res->f024;
            if (w == 0) {
                return 0;
            }
            w->f016 = 0xC;
            w->f018 = 0xF;
            h = func_3AD390(ob, ent->f000);
            if (h != 0) {
                val = func_3A05C0(h);
            } else {
                val = func_3F5CA0(ent);
            }
            n = ent->f003;
            func_291250(D_0048449C, id, 0, val);
            func_2905B0(D_0048449C, id, 1.0f, 1.0f, 1.0f, -1.0f);
            ok = true;
            m = func_3A0560(h);
            for (j = 0; j < m; j++) {
                e = func_3A04E0(h, j);
                if (func_3C2350(func_1FEDE0()->f018, e) == 0) {
                    ok = false;
                    break;
                }
            }
            if (ob->held(ent->f000) == 0) {
                func_2905B0(D_0048449C, id, half, half, half, -1.0f);
                if (!ok) {
                    if (!(ob->count() < val)) {
                        func_2905B0(D_0048449C, id, 1.0f, 1.0f, 1.0f, -1.0f);
                    }
                }
            }
            normal_BtlChgPageSetAbilityTypeIcon_505470(D_00484454, (u16)(i + 0x11), n);
            normal_BtlChgPageSetAbilityTypeIcon_505470(D_00484454, (u16)(i + 0x15), -1);
        } else {
            id = i * 3 + 6;
            res = func_290460(D_0048449C, id);
            if (res == 0) {
                return 0;
            }
            w = res->f024;
            if (w == 0) {
                return 0;
            }
            w->f018 = 0;
            w->f016 = 0;
            func_291250(D_0048449C, id, 0, 0);
            func_289090(D_00484454, i + 0x11, 0, 0);
            func_289090(D_00484454, i + 0x15, -1, 0);
        }
        ent = func_370040(&it);
    }
    return 1;
}
