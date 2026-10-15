/* === SESSION 71 (2026-09-21, SOLO): 296 bad -> MATCH.  Read against the
 * listing (build/wf-normal/s71/d1..d6.py):
 *  - `hit = 0;` back AFTER the switch (s31's move deck had hoisted it above
 *    func_3D4D80); retail sets it at the switch join and in the default's slot.
 *  - three if/else arm swaps so retail's fall-through arm comes first:
 *    `func_3D46F0(e, vt) != 0` -> 0x3A else hit = 1; `if (hit)` -> 0x19 path;
 *    `func_3D4630(e) != 0` -> 0x72 path.
 *  - `u8 hit` + a BARE `if (hit)` (daddiu for the constant; `!= 0` re-masks).
 *  - the 66-byte table copy is an lh/sh HALFWORD loop: declare the template
 *    `extern "C" const Row D_00525A50[];` and copy `tbl = *(const Tbl *)
 *    D_00525A50;` -- a whole-object `extern const Tbl` is copied with lq/sq.
 *    (This also fixes s53's linkage warning: it is now extern "C".)
 *  - `tbl.r[(u32)i]` at the func_28F970 args: retail recomputes i*6 after the
 *    call ([[mwcc-index-cast-defeats-cse]]).
 *  - the early `return 1;` is `goto done;` to the function's final return, so
 *    the two func_3E97C0 arms branch to `li v0,1` with a nop slot.
 * Everything below predates this session. */
/* === SESSION 53 (2026-09-08, SOLO): STILL 296 / 454.  MEASURED NEGATIVE on
 * the two spellings its MERGED TWIN uses.  clone.py pairs this unit with
 * `normal_ShopMenuSellItemStatusLayout_50ef80` (436w, opcode overlap 0.90, CALL-TARGET overlap 0.68 --
 * the strongest pair on the board), and that twin differs from us in exactly
 * two structural ways.  BOTH ARE NULLS HERE:
 *  - `#pragma optimization_level 3`, which the twin opens with.  The full
 *    ladder is measured: 0 -> 0x9c4, 1 -> 0x8d8, 2 -> 0x89c, 3 -> 0x724
 *    (retail 0x718), and 4 == THE BASELINE OBJECT, i.e. 4 is the default here.
 *    ARMED BOTH WAYS ([[mwcc-optimization-level]]): `#pragma zzz_not_a_pragma 3`
 *    is byte-identical to the baseline and `optimization_level off` fails to
 *    build (NOOBJ).
 *  - the twin's 33-halfword global->local copy written as an EXPLICIT do-while
 *    pointer loop (`cd = (s16 *)&tbl; cs = D_00525A50; cn = 0x21;
 *    do { *cd = *cs; cs++; cd++; cn--; } while (cn > 0);`) instead of our
 *    `tbl = D_00525A50;` struct assignment: ONE WORD SHORT (0x714 vs 0x718).
 *    Crossed with optimization_level 3 it is 0x720, still wrong.
 * The residue is 62 substitutions over 454 words -- a whole-function colouring
 * problem -- so neither local fact can pay until that moves.
 * ⚠ `extern const Tbl D_00525A50;` in this .cpp file is NOT inside an
 * `extern "C"` block, unlike every other extern here.  It has never been
 * linked (the unit is open); check its linkage before merging.
 */
/* SESSION 31 STAGE 2 (same six decks, re-run from the stage-1 bases).
 * Installed arm `D_e_at13_dec` from the declaration sweep.
 *   before: 454 words, 305 bad   after: 454 words, 296 bad   (retail 454 words)
 * Everything below predates THIS install; read older numbers as history.
 * Re-score with build/wf-normal/s31/nscore.py, not dv_osbuild.py. */
/* SESSION 31 (combined six-deck sweep, 31,338 arms over 98 units).
 * Installed arm `MV_hit_L385_T369_SAFE_mov` from the DEFINING-STATEMENT MOVE deck (mkmove31.py)
 *   before: 453 words, ? bad   after: 454 words, 305 bad   (retail 454 words)
 * Every line BELOW this note predates that install -- read its numbers
 * as the state at the time it was written, not as the current score.
 * Re-score with build/wf-normal/s31/nscore.py, not dv_osbuild.py.
 * KEEP OUT OF config/ocunits/normal.txt. */
#include "types.h"
/* normal 0x0050BE30 -- the party-member swap panel's confirm handler.
 * Four C++ VIRTUAL calls (lw $25,0($19) / lw $25,0xNNN($25) / jalr $25) on the
 * object func_3D4D80 returns; vptr is at offset 0, so slot = (off - 8) / 4:
 * 0x388 -> 224, 0x38C -> 225, 0x3C4 -> 239, 0x3D8 -> 244.
 * The 33-halfword lh/sh copy loop at 0x0050BE90 into sp+0x60 is a 66-byte
 * STRUCT ASSIGNMENT of D_00525A50 (11 rows of three s16); the tail loop at
 * 0x0050C2D8 walks ten of those rows looking for the func_3D4D50 result.
 * func_2905B0 takes FOUR floats (per normal_MenuBattleEndExpBonusShowMaybe_4eb400's recorded reading).
 * Session 31 lane a7, FRESH unit. */

typedef struct Desc {
    s16 f00;
    s8  f02;
    u8  pad03[0x14 - 0x3];
    s8  f14;
} Desc;

typedef struct Ent {
    u8    pad00[0x10];
    Desc *f10;
} Ent;

typedef struct G {
    u8    pad00[0x18];
    void *f18;
} G;

typedef struct Row { s16 f0; s16 f2; s16 f4; } Row;
typedef struct Tbl { Row r[11]; } Tbl;

struct VObj {
    virtual void m000();
    virtual void m001();
    virtual void m002();
    virtual void m003();
    virtual void m004();
    virtual void m005();
    virtual void m006();
    virtual void m007();
    virtual void m008();
    virtual void m009();
    virtual void m010();
    virtual void m011();
    virtual void m012();
    virtual void m013();
    virtual void m014();
    virtual void m015();
    virtual void m016();
    virtual void m017();
    virtual void m018();
    virtual void m019();
    virtual void m020();
    virtual void m021();
    virtual void m022();
    virtual void m023();
    virtual void m024();
    virtual void m025();
    virtual void m026();
    virtual void m027();
    virtual void m028();
    virtual void m029();
    virtual void m030();
    virtual void m031();
    virtual void m032();
    virtual void m033();
    virtual void m034();
    virtual void m035();
    virtual void m036();
    virtual void m037();
    virtual void m038();
    virtual void m039();
    virtual void m040();
    virtual void m041();
    virtual void m042();
    virtual void m043();
    virtual void m044();
    virtual void m045();
    virtual void m046();
    virtual void m047();
    virtual void m048();
    virtual void m049();
    virtual void m050();
    virtual void m051();
    virtual void m052();
    virtual void m053();
    virtual void m054();
    virtual void m055();
    virtual void m056();
    virtual void m057();
    virtual void m058();
    virtual void m059();
    virtual void m060();
    virtual void m061();
    virtual void m062();
    virtual void m063();
    virtual void m064();
    virtual void m065();
    virtual void m066();
    virtual void m067();
    virtual void m068();
    virtual void m069();
    virtual void m070();
    virtual void m071();
    virtual void m072();
    virtual void m073();
    virtual void m074();
    virtual void m075();
    virtual void m076();
    virtual void m077();
    virtual void m078();
    virtual void m079();
    virtual void m080();
    virtual void m081();
    virtual void m082();
    virtual void m083();
    virtual void m084();
    virtual void m085();
    virtual void m086();
    virtual void m087();
    virtual void m088();
    virtual void m089();
    virtual void m090();
    virtual void m091();
    virtual void m092();
    virtual void m093();
    virtual void m094();
    virtual void m095();
    virtual void m096();
    virtual void m097();
    virtual void m098();
    virtual void m099();
    virtual void m100();
    virtual void m101();
    virtual void m102();
    virtual void m103();
    virtual void m104();
    virtual void m105();
    virtual void m106();
    virtual void m107();
    virtual void m108();
    virtual void m109();
    virtual void m110();
    virtual void m111();
    virtual void m112();
    virtual void m113();
    virtual void m114();
    virtual void m115();
    virtual void m116();
    virtual void m117();
    virtual void m118();
    virtual void m119();
    virtual void m120();
    virtual void m121();
    virtual void m122();
    virtual void m123();
    virtual void m124();
    virtual void m125();
    virtual void m126();
    virtual void m127();
    virtual void m128();
    virtual void m129();
    virtual void m130();
    virtual void m131();
    virtual void m132();
    virtual void m133();
    virtual void m134();
    virtual void m135();
    virtual void m136();
    virtual void m137();
    virtual void m138();
    virtual void m139();
    virtual void m140();
    virtual void m141();
    virtual void m142();
    virtual void m143();
    virtual void m144();
    virtual void m145();
    virtual void m146();
    virtual void m147();
    virtual void m148();
    virtual void m149();
    virtual void m150();
    virtual void m151();
    virtual void m152();
    virtual void m153();
    virtual void m154();
    virtual void m155();
    virtual void m156();
    virtual void m157();
    virtual void m158();
    virtual void m159();
    virtual void m160();
    virtual void m161();
    virtual void m162();
    virtual void m163();
    virtual void m164();
    virtual void m165();
    virtual void m166();
    virtual void m167();
    virtual void m168();
    virtual void m169();
    virtual void m170();
    virtual void m171();
    virtual void m172();
    virtual void m173();
    virtual void m174();
    virtual void m175();
    virtual void m176();
    virtual void m177();
    virtual void m178();
    virtual void m179();
    virtual void m180();
    virtual void m181();
    virtual void m182();
    virtual void m183();
    virtual void m184();
    virtual void m185();
    virtual void m186();
    virtual void m187();
    virtual void m188();
    virtual void m189();
    virtual void m190();
    virtual void m191();
    virtual void m192();
    virtual void m193();
    virtual void m194();
    virtual void m195();
    virtual void m196();
    virtual void m197();
    virtual void m198();
    virtual void m199();
    virtual void m200();
    virtual void m201();
    virtual void m202();
    virtual void m203();
    virtual void m204();
    virtual void m205();
    virtual void m206();
    virtual void m207();
    virtual void m208();
    virtual void m209();
    virtual void m210();
    virtual void m211();
    virtual void m212();
    virtual void m213();
    virtual void m214();
    virtual void m215();
    virtual void m216();
    virtual void m217();
    virtual void m218();
    virtual void m219();
    virtual void m220();
    virtual void m221();
    virtual void m222();
    virtual void m223();
    virtual Ent *m224();
    virtual Ent *m225();
    virtual void m226();
    virtual void m227();
    virtual void m228();
    virtual void m229();
    virtual void m230();
    virtual void m231();
    virtual void m232();
    virtual void m233();
    virtual void m234();
    virtual void m235();
    virtual void m236();
    virtual void m237();
    virtual void m238();
    virtual Ent *m239();
    virtual void m240();
    virtual void m241();
    virtual void m242();
    virtual void m243();
    virtual Ent *m244();
};

extern "C" const Row D_00525A50[];

extern "C" void *D_004845CC;   /* gp - 0xBA4 */
extern "C" void *D_004845F8;   /* gp - 0xB78 */
extern "C" f32   D_0047D288;   /* gp - 0x7EE8 */

extern "C" G    *func_1FEDE0(void);
extern "C" s32   func_3C78D0(void *p, s16 id, s8 c, s32 d);
extern "C" void  func_291250(void *p, s32 id, s32 c, s64 v);
extern "C" void *func_28FE10(void *p, s32 id, s32 c);
extern "C" s32   func_3CE890(Ent **p);
extern "C" void  func_288E50(void *w, s32 a, s32 b, s32 c);
extern "C" void  func_2905B0(void *p, s32 id, f32 a, f32 b, f32 c, f32 d);
extern "C" void  func_291110(void *p, s32 id, s32 a, s32 b);
extern "C" void  func_290F60(void *p, s32 id, s32 a, s32 b);
extern "C" void  func_28F970(void *p, s32 id, s32 a, s32 b, s32 c);
extern "C" void *func_28AA30(void *p, s32 id);
extern "C" void  func_28A800(void *w, void *q, s32 a, s32 b, s32 c);
extern "C" s32   func_3E97C0(G *g, s16 id, s32 a, s32 b, s32 c, s32 d, s32 e);
extern "C" s32   func_3D4860(Ent *e);
extern "C" s32   func_3D4630(Ent *e);
extern "C" s32   func_3D4D50(Ent *e, s32 a);
extern "C" VObj *func_3D4D80(Ent *e, s32 a);
extern "C" s32   func_3D46F0(Ent *e, VObj *v);

extern "C" s32 normal_ShopMenuBuyItemStatusLayout_50be30(Ent **pp);

s32 normal_ShopMenuBuyItemStatusLayout_50be30(Ent **pp)
{
    Tbl   tbl;
    s8    c;
    s8    flag;
    G    *g;
    void *w56;
    void *w51;
    void *w74;
    void *w75;
    s32   r;
    VObj *vt;
    Ent  *obj;
    s32   id;
    u8    hit;
    Ent  *e;
    s32   i;
    void *x;

    if (pp == 0) {
        return 0;
    }
    e = *pp;
    if (e == 0) {
        return 0;
    }
    c = e->f10->f14;
    flag = 0;
    if (c >= 0) {
        flag = c;
    }
    tbl = *(const Tbl *)D_00525A50;
    g = func_1FEDE0();
    func_291250(D_004845CC, 0x55, 0, (s64)func_3C78D0(g->f18, e->f10->f00, flag, 0));
    w56 = func_28FE10(D_004845CC, 0x56, 0);
    if (w56 == 0) {
        return 0;
    }
    func_288E50(w56, func_3CE890(pp), 0x28, 0x2D);
    w51 = func_28FE10(D_004845CC, 0x51, 0);
    w74 = func_28FE10(D_004845CC, 0x74, 0);
    w75 = func_28FE10(D_004845CC, 0x75, 0);
    if (w51 == 0) {
        return 0;
    }
    if (w74 == 0) {
        return 0;
    }
    if (w75 == 0) {
        return 0;
    }
    func_2905B0(D_004845CC, 0x75, 1.0f, 1.0f, 1.0f, 1.0f);
    func_291110(D_004845CC, 0x74, 1, 1);
    func_290F60(D_004845CC, 0x74, 9, 6);
    if (func_3D4860(e) != 0) {
        func_291110(D_004845CC, 0x59, 0, 1);
        func_291110(D_004845CC, 0x53, 1, 1);
        r = func_3D4D50(e, 1);
        if (r == -1) {
            func_2905B0(D_004845CC, 0x75, D_0047D288, D_0047D288, D_0047D288, 1.0f);
            func_290F60(D_004845CC, 0x75, 0x32, 0x1E);
            func_28A800(w75, func_28AA30(D_004845F8, 0x12), 0, 0, -2);
        } else {
            vt = func_3D4D80(e, 0);
            obj = 0;
            switch (e->f10->f02) {
            case 0:
                obj = vt->m224();
                break;
            case 1:
                obj = vt->m225();
                break;
            case 2:
                obj = vt->m239();
                break;
            case 3:
                obj = vt->m244();
                break;
            }
            hit = 0;
            id = -1;
            if (obj != 0) {
                id = obj->f10->f00;
            }
            if (id == e->f10->f00) {
                func_290F60(D_004845CC, 0x75, 0x3C, 0x1E);
                func_28A800(w75, func_28AA30(D_004845F8, 0x13), 0, 0, -2);
            } else if (func_3D46F0(e, vt) != 0) {
                func_290F60(D_004845CC, 0x75, 0x3A, 0x1E);
                func_28A800(w75, func_28AA30(D_004845F8, 0x11), 0, 0, -2);
            } else {
                hit = 1;
            }
            if (hit) {
                func_2905B0(D_004845CC, 0x75, D_0047D288, D_0047D288, D_0047D288, 1.0f);
                func_290F60(D_004845CC, 0x75, 0x28, 0x1E);
                func_28A800(w75, func_28AA30(D_004845F8, 0x19), 0, 0, -2);
                func_2905B0(D_004845CC, 0x53, D_0047D288, D_0047D288, D_0047D288, 1.0f);
            } else {
                func_2905B0(D_004845CC, 0x53, 1.0f, 1.0f, 1.0f, 1.0f);
            }
            func_291110(D_004845CC, 0x75, 1, 1);
        }
        if (func_3D4630(e) != 0) {
            func_28F970(D_004845CC, 0x53, 0x72, 0, 0);
        } else {
            if (r == -1) {
                func_291110(D_004845CC, 0x53, 0, 1);
            } else {
                for (i = 0; i < 0xA; i++) {
                    if (r == tbl.r[i].f0) {
                        func_291110(D_004845CC, 0x53, 1, 1);
                        func_28F970(D_004845CC, 0x53, tbl.r[(u32)i].f2, tbl.r[(u32)i].f4, 0);
                        break;
                    }
                }
            }
        }
        func_291110(D_004845CC, 0x52, 1, 1);
        goto done;
    }
    func_291110(D_004845CC, 0x53, 0, 1);
    func_291110(D_004845CC, 0x52, 0, 1);
    func_291110(D_004845CC, 0x75, 0, 1);
    func_291110(D_004845CC, 0x59, 1, 1);
    func_2905B0(D_004845CC, 0x59, 1.0f, 1.0f, 1.0f, 1.0f);
    func_290F60(D_004845CC, 0x59, 9, 0x1E);
    if (func_3E97C0(g, e->f10->f00, -1, 0, 1, 1, 0) > 0) {
        x = func_28FE10(D_004845CC, 0x59, 0);
        func_28A800(x, func_28AA30(D_004845F8, 0x16), 0, 0, -2);
    } else if (func_3E97C0(g, e->f10->f00, -1, 1, 0, 0, 1) > 0) {
        x = func_28FE10(D_004845CC, 0x59, 0);
        func_2905B0(D_004845CC, 0x59, D_0047D288, D_0047D288, D_0047D288, 1.0f);
        func_28A800(x, func_28AA30(D_004845F8, 0x17), 0, 0, -2);
    } else {
        x = func_28FE10(D_004845CC, 0x59, 0);
        func_2905B0(D_004845CC, 0x59, D_0047D288, D_0047D288, D_0047D288, 1.0f);
        func_28A800(x, func_28AA30(D_004845F8, 0x18), 0, 0, -2);
    }
done:
    return 1;
}
