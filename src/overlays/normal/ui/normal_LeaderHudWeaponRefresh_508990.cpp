/* === SESSION 65 (2026-09-15, SOLO): 201 -> MATCH.  s50's two named CROSS
 * HALVES below were both right; the -1 they were waiting for is a TOKEN.
 * Four edits, in the order they paid:
 *  1. `if (flag != 0)` -> `if (flag)`.  `flag` is a u8, and per
 *     [[mwcc-daddiu-unsigned-narrow]] the `!= 0` TOKEN costs an
 *     `andi $2,$22,0xFF`.  **-1 WORD** -- this is s50's missing -1, and
 *     [[opcode-histogram-screen]] had been printing it as `andi:1->2` the
 *     whole time (with `sll:12->11`, which is opscan counting the nop that
 *     the extra andi displaced out of a delay slot).
 *  2. s50 edit 1: `flag = 0;` moved ~90 statements later, to between
 *     `cur = 0.0f;` and `lim = cur;`.  +1 word, 426 -> 427 EXACT, 28 bad.
 *  3. s50 edit 2: `col = 1.0f;` moved one block later, to just before
 *     `sum = normal_LeaderHudGetWeaponFlash_5069e0(...)`.  28 -> 10 bad.
 *  4. ★ the duplicated `func_290460(D_00484564, 5)->f20->f06 = 6;` in BOTH
 *     arms spelled `{ Hold *rr = func_290460(...); rr->f20->f06 = 6; }` --
 *     [[normal-session64-levers]]'s "name the RETURNED STRUCT, not the member
 *     it loads".  Naming only the MEMBER (`Wg *q = ...->f20;`) is 6 bad;
 *     naming the returned struct is MATCH.  Without it the constant 6 is
 *     CSE'd across the if/else into a CALLEE-SAVED $17 and fills the jal
 *     delay slot that retail gives to the `li $5,5` argument.
 *     (s16)/(u16)/`5 + 1`/a named `s16 six`/a volatile store are all == base.
 */
/* === SESSION 50 (2026-09-08, SOLO): NO CHANGE INSTALLED -- 427 w, 201 bad,
 * EXACT LENGTH -- but the residue is now NAMED and it is TWO STATEMENT
 * POSITIONS, each worth a large shape improvement and each +1 WORD.
 * Read this before touching the unit; both are CROSS HALVES looking for a -1.
 *
 *  1. `flag = 0;` IS ~90 STATEMENTS TOO EARLY.  Retail emits `daddu $22,$0,$0`
 *     at 0x00508B84 -- AFTER `pos = o->v052();` and `cur = 0.0f;`
 *     (`mtc1 $0,$f22` at 00508B7C) and BEFORE the `if (cnt > 0)` test, whose
 *     `blez $16` delay slot carries `lim = cur;` (`mov.s $f21,$f22`).
 *     Written there the SUBSTITUTION CENSUS collapses 56 -> 21 and every
 *     mdiff hunk outside one block disappears.  +1 word (0x6b0 vs 0x6ac).
 *     ⚠⚠ THE CURRENT POSITION IS AN s31 DEFINING-STATEMENT MOVE INSTALL
 *     (`MV_flag_L501_T454_SAFE_mov`) -- the FOURTH of that deck's installs
 *     this session found to be in the wrong place.
 *  2. `col = 1.0f;` IS ONE BLOCK TOO EARLY.  Retail builds the 1.0f web
 *     (`lui $2,0x3F800000 / mtc1 $2,$f20`) at 0x00508D18, i.e. AFTER
 *     `func_290F60(D_00484564, 4, 0x39, 0x1A);` and before
 *     `sum = normal_LeaderHudGetWeaponFlash_5069e0(...)`.  On top of edit 1 that takes the
 *     census 21 -> 15 and leaves ONE hunk region.  Alone it is 204 (worse).
 *
 * MEASURED NEGATIVE for the missing -1: hoisting the duplicated
 * `func_290460(D_00484564, 5)->f20->f06 = 6;` out of BOTH arms of the
 * `cnt > 0` if/else is FIVE WORDS SHORT (0x698) with or without a named
 * temp -- retail tail-DUPLICATES it, so it must stay written twice.
 * Both edits are reverted here so the unit stays SCOREABLE at exact length. */
/* SESSION 31 STAGE 2 (same six decks, re-run from the stage-1 bases).
 * Installed arm `D_pos_at03_dec` from the declaration sweep.
 *   before: 427 words, 216 bad   after: 427 words, 204 bad   (retail 427 words)
 * Everything below predates THIS install; read older numbers as history.
 * Re-score with build/wf-normal/s31/nscore.py, not dv_osbuild.py. */
/* SESSION 31 (combined six-deck sweep, 31,338 arms over 98 units).
 * Installed arm `MV_flag_L501_T454_SAFE_mov` from the DEFINING-STATEMENT MOVE deck (mkmove31.py)
 *   before: 428 words, ? bad   after: 427 words, 216 bad   (retail 427 words)
 * Every line BELOW this note predates that install -- read its numbers
 * as the state at the time it was written, not as the current score.
 * Re-score with build/wf-normal/s31/nscore.py, not dv_osbuild.py.
 * KEEP OUT OF config/ocunits/normal.txt. */
#include "types.h"
/* normal 0x00508990 -- FRESH, session 31 lane a5.
 * 13 `jalr $25` => C++ virtual dispatch, vptr at +0x0, slot = (off-8)/4.
 * Three dispatch targets: func_3C2820's result (slots 21/226/234),
 * that object's slot-226 result (slots 48/49/52/53/54/56/57) and
 * func_3D3D50's result (slot 64).
 * `andi $2,$18,7` + `bgez/addiu -8` is a SIGNED `% 8`; `sra 3` with the
 * `+7` bias is a SIGNED `/ 8`.
 * `dsll32/dsra32 ..,0` on func_291250's 4th argument is the s32->s64
 * widening pair [[mwcc-s32-s64-widening-pair]].
 * The far `lui $2,0x46 / lwc1 -0x4F88($2)` is const f32 D_0045B078. */

class Tgt {
public:
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
    virtual void *v021();          /* +0x5C  */
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
    virtual void s065();
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
    virtual void s178();
    virtual void s179();
    virtual void s180();
    virtual void s181();
    virtual void s182();
    virtual void s183();
    virtual void s184();
    virtual void s185();
    virtual void s186();
    virtual void s187();
    virtual void s188();
    virtual void s189();
    virtual void s190();
    virtual void s191();
    virtual void s192();
    virtual void s193();
    virtual void s194();
    virtual void s195();
    virtual void s196();
    virtual void s197();
    virtual void s198();
    virtual void s199();
    virtual void s200();
    virtual void s201();
    virtual void s202();
    virtual void s203();
    virtual void s204();
    virtual void s205();
    virtual void s206();
    virtual void s207();
    virtual void s208();
    virtual void s209();
    virtual void s210();
    virtual void s211();
    virtual void s212();
    virtual void s213();
    virtual void s214();
    virtual void s215();
    virtual void s216();
    virtual void s217();
    virtual void s218();
    virtual void s219();
    virtual void s220();
    virtual void s221();
    virtual void s222();
    virtual void s223();
    virtual void s224();
    virtual void s225();
    virtual class Ent *v226();     /* +0x390 */
    virtual void s227();
    virtual void s228();
    virtual void s229();
    virtual void s230();
    virtual void s231();
    virtual void s232();
    virtual void s233();
    virtual s32   v234();          /* +0x3B0 */
};

class Ent {
public:
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
    virtual s32 v048();            /* +0xC8 */
    virtual s32 v049();            /* +0xCC */
    virtual void s050();
    virtual void s051();
    virtual s32 v052();            /* +0xD8 */
    virtual f32 v053();            /* +0xDC */
    virtual f32 v054();            /* +0xE0 */
    virtual void s055();
    virtual s32 v056();            /* +0xE8 */
    virtual s32 v057();            /* +0xEC */
    u8  pad04[0x10 - 4];
    s32 f10;
};

class Nod {
public:
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
    virtual s32 v064(void *a);     /* +0x108 */
};

typedef struct Wg   { u8 pad00[4]; s16 f04; s16 f06; s16 f08; s16 f0A;
                      s16 f0C; s16 f0E; u8 pad10[0x1C - 0x10]; s16 f1C; } Wg;
typedef struct Hold { u8 pad00[4]; u8 f04[0x20 - 4]; Wg *f20; } Hold;
typedef struct Item { u8 pad00[4]; const void *f04; u8 pad08[4]; u32 f0C; } Item;
typedef struct Src  { u8 pad00[0x2C]; s16 f2C; } Src;
typedef struct Ctx  { u8 pad00[0x18]; void *f18; u8 pad1C[4]; s32 f20; } Ctx;

extern const f32 D_0045B078;
extern "C" const u8 D_00526498[];
extern "C" const u8 D_005264A8[];

extern "C" f32   D_0047D278;      /* gp - 0x7EF8 */
extern "C" f32   D_0047D288;      /* gp - 0x7EE8 */
extern "C" f32   D_0047D35C;      /* gp - 0x7E14 */
extern "C" f32   D_0047D520;      /* gp - 0x7C50 */
extern "C" void *D_00484564;      /* gp - 0xC0C  */
extern "C" void *D_0048456C;      /* gp - 0xC04  */
extern "C" Nod  *D_0048457C;      /* gp - 0xBF4  */

extern "C" Ctx  *func_1FEDE0(void);
extern "C" Tgt  *func_3C2820(void *p);
extern "C" void  func_291110(void *p, s32 id, s32 c, s32 d);
extern "C" Src  *func_3AE3E0(Tgt *t);
extern "C" Hold *func_290460(void *p, s32 id);
extern "C" void  func_134A98(void *d, const void *s);
extern "C" void  func_290F60(void *p, s32 id, s32 x, s32 y);
extern "C" Nod  *func_3D3D50(Ent *e);
extern "C" s32   func_40E0E0(s32 a);
extern "C" f32   normal_LeaderHudGetWeaponGaugeShown_5069d0(void *p);
extern "C" void  normal_LeaderHudSetWeaponGaugeShown_5069c0(void *p, f32 x);
extern "C" void  normal_LeaderHudGaugeBarSet_506630(void *p, s32 id, s32 c, s32 d, f32 x, f32 y);
extern "C" f32   normal_LeaderHudGetWeaponFlash_5069e0(void *p);
extern "C" f32   normal_LeaderHudGetWeaponFlashStep_506a20(void *p);
extern "C" void  normal_LeaderHudSetWeaponFlashStep_506a30(void *p, f32 x);
extern "C" void  normal_LeaderHudSetWeaponFlash_5069f0(void *p, f32 x);
extern "C" void  normal_LeaderHudSetField98Related_506a40(void *p, s32 a);
extern "C" void  func_291250(void *p, s32 id, s32 c, s64 v);
extern "C" void  func_2905B0(void *p, s32 id, f32 r, f32 g, f32 b, f32 a);
extern "C" Item *func_28F620(void *p, s32 id, s32 c);
extern "C" s32   func_3A36D0(s32 a);

extern "C" s32 normal_LeaderHudWeaponRefresh_508990(void);

s32 normal_LeaderHudWeaponRefresh_508990(void)
{
    Ctx  *ctx;
    Ent  *o;
    Nod  *nd;
    s32   pos;
    s32   n;
    Tgt  *tg;
    Src  *sc;
    Hold *hd;
    Wg   *w;
    s32   m;
    s32   cnt;
    u8    flag;
    f32   cur;
    f32   lim;
    f32   base;
    f32   sc2;
    f32   tot;
    f32   hi;
    f32   sum;
    f32   col;

    ctx = func_1FEDE0();
    if (ctx == 0) {
        return 0;
    }
    tg = func_3C2820(ctx->f18);
    if (tg == 0) {
        return 0;
    }
    o = tg->v226();
    if (o == 0) {
        func_291110(D_00484564, 2, 0, 1);
        D_0048457C = 0;
        return 0;
    }
    func_291110(D_00484564, 2, 1, 1);
    sc = func_3AE3E0(tg);
    if (sc == 0) {
        return 0;
    }
    n = sc->f2C;
    hd = func_290460(D_00484564, 3);
    if (hd == 0) {
        return 0;
    }
    w = hd->f20;
    if (w == 0) {
        return 0;
    }
    func_134A98(hd->f04, D_005264A8);
    w->f0C = 0x1F;
    w->f0E = 0x1F;
    w->f08 = (s16)((n % 8) * (w->f0C + 1));
    w->f0A = (s16)((n / 8) * (w->f0E + 1));
    w->f04 = 0x28;
    w->f06 = 0x28;
    w->f1C = 0;
    func_290F60(D_00484564, 3, 2, 2);
    nd = func_3D3D50(o);
    if (o == 0) {
        return 0;
    }
    if (o->f10 == 0) {
        return 0;
    }
    if (func_40E0E0(o->f10) == 0) {
        return 0;
    }
    cnt = o->v048();
    m = o->v049();
    pos = o->v052();
    cur = 0.0f;
    flag = 0;
    lim = cur;
    if (cnt > 0) {
        if (o->v057() != 0) {
            sc2 = (f32)cnt * o->v053();
            lim = sc2 / o->v054();
            pos = (s32)lim;
        }
        base = (f32)pos;
        if (D_0048457C != nd) {
            D_0048457C = nd;
            cur = base;
        } else {
            cur = normal_LeaderHudGetWeaponGaugeShown_5069d0(D_0048456C);
        }
        if (cur > lim) {
            tot = base + (f32)m;
            cur -= (f32)m / (0.25f * D_0045B078);
            if (cur < base) {
                cur = base;
            } else if (!(cur <= tot)) {
                cur = tot;
            }
        } else {
            if (o->v057() != 0) {
                cur = lim;
                flag = 1;
            } else if (cur < base) {
                cur = base;
            }
        }
    }
    normal_LeaderHudSetWeaponGaugeShown_5069c0(D_0048456C, cur);
    normal_LeaderHudGaugeBarSet_506630(D_0048456C, 5, 0, 0x66, (f32)cnt, (f32)pos);
    normal_LeaderHudGaugeBarSet_506630(D_0048456C, 4, 0, -1, (f32)cnt, cur);
    func_290F60(D_00484564, 5, 0x39, 0x1A);
    func_290F60(D_00484564, 4, 0x39, 0x1A);
    col = 1.0f;
    sum = normal_LeaderHudGetWeaponFlash_5069e0(D_0048456C);
    hi = normal_LeaderHudGetWeaponFlashStep_506a20(D_0048456C);
    if (o->v057() != 0) {
        if (o->v056() == 0) {
            col = D_0047D288;
        }
        sum += hi;
        if (sum > D_0047D35C || sum < D_0047D278) {
            normal_LeaderHudSetWeaponFlashStep_506a30(D_0048456C, -1.0f * hi);
            if (sum >= D_0047D35C) {
                sum = D_0047D35C;
            } else if (sum <= D_0047D278) {
                sum = D_0047D278;
            }
        }
        normal_LeaderHudSetWeaponFlash_5069f0(D_0048456C, sum);
        if (nd->v064(tg->v021()) != 0) {
            func_291110(D_00484564, 6, 1, 1);
            func_291250(D_00484564, 6, 0, (s64)tg->v234());
        } else {
            func_291110(D_00484564, 6, 0, 1);
        }
        { Hold *rr = func_290460(D_00484564, 5); rr->f20->f06 = 6; }
    } else {
        normal_LeaderHudSetField98Related_506a40(D_0048456C, 0);
        normal_LeaderHudSetWeaponFlashStep_506a30(D_0048456C, D_0047D520);
        normal_LeaderHudSetWeaponFlash_5069f0(D_0048456C, D_0047D278);
        func_291110(D_00484564, 6, 0, 1);
        { Hold *rr = func_290460(D_00484564, 5); rr->f20->f06 = 6; }
    }
    if (cnt > 0) {
        if (flag) {
            func_2905B0(D_00484564, 2, col, col, col, -1.0f);
            func_2905B0(D_00484564, 5, sum, sum, sum, -1.0f);
            func_2905B0(D_00484564, 4, sum, sum, sum, -1.0f);
        } else {
            func_2905B0(D_00484564, 2, col, col, col, -1.0f);
            func_2905B0(D_00484564, 5, 1.0f, 1.0f, 1.0f, -1.0f);
            func_2905B0(D_00484564, 4, 0.5f, 0.5f, 0.5f, -1.0f);
        }
    }
    {
        Item *it = func_28F620(D_00484564, 2, 0);
        if (func_3A36D0(ctx->f20) == 0x271B) {
            it->f04 = D_00526498;
            it->f0C = 0xFF181840;
            func_2905B0(D_00484564, 2, 0.5f, 0.5f, 0.5f, -1.0f);
        } else {
            it->f04 = 0;
        }
    }
    return 1;
}
