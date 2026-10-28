/* rgp:protos */
#line 1
/* === SESSION 71 (2026-09-21, SOLO): 296 bad -> MATCH.  Read against the
 * listing (build/wf-normal/s71/d1..d6.py):
 *  - `hit = 0;` back AFTER the switch (s31's move deck had hoisted it above
 *    func_3D4D80); retail sets it at the switch join and in the default's slot.
 *  - three if/else arm swaps so retail's fall-through arm comes first:
 *    `func_3D46F0(e, vt) != 0` -> 0x3A else hit = 1; `if (hit)` -> 0x19 path;
 *    `func_3D4630(e) != 0` -> 0x72 path.
 *  - `u8 hit` + a BARE `if (hit)` (daddiu for the constant; `!= 0` re-masks).
 *  - the 66-byte table copy is an lh/sh HALFWORD loop: declare the template
 *    `extern "C" const Row normal_D_00525A50[];` and copy `tbl = *(const Tbl *)
 *    normal_D_00525A50;` -- a whole-object `extern const Tbl` is copied with lq/sq.
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
 *    pointer loop (`cd = (s16 *)&tbl; cs = normal_D_00525A50; cn = 0x21;
 *    do { *cd = *cs; cs++; cd++; cn--; } while (cn > 0);`) instead of our
 *    `tbl = normal_D_00525A50;` struct assignment: ONE WORD SHORT (0x714 vs 0x718).
 *    Crossed with optimization_level 3 it is 0x720, still wrong.
 * The residue is 62 substitutions over 454 words -- a whole-function colouring
 * problem -- so neither local fact can pay until that moves.
 * ⚠ `extern const Tbl normal_D_00525A50;` in this .cpp file is NOT inside an
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
 * STRUCT ASSIGNMENT of normal_D_00525A50 (11 rows of three s16); the tail loop at
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
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    Ent * m224() { return VCM0(Ent *, 0x388); }
    Ent * m225() { return VCM0(Ent *, 0x38C); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    Ent * m239() { return VCM0(Ent *, 0x3C4); }
    
    
    
    
    Ent * m244() { return VCM0(Ent *, 0x3D8); }
};

extern "C" Row normal_D_00525A50[];

extern "C" void *D_004845CC;   /* gp - 0xBA4 */
extern "C" void *D_004845F8;   /* gp - 0xB78 */
extern "C" f32   D_0047D288;   /* gp - 0x7EE8 */

extern "C" G    *GetGameData_1fede0(void);
extern "C" s32   InvCountById_3c78d0(void *p, s16 id, s8 c, s32 d);
extern "C" void  UiSetWidgetSubItemValue_291250(void *p, s32 id, s32 c, s64 v);
extern "C" void *UiGetWidgetSprite_28fe10(void *p, s32 id, s32 c);
extern "C" s32   ShopRowGetItemIconIdMaybe_3ce890(Ent **p);
extern "C" void  UiSetItemIconUv_288e50(void *w, s32 a, s32 b, s32 c);
extern "C" void  UiSetWidgetColor_2905b0(void *p, s32 id, f32 a, f32 b, f32 c, f32 d);
extern "C" void  UiSetWidgetsVisibleById_291110(void *p, s32 id, s32 a, s32 b);
extern "C" void  UiSetWidgetPos_290f60(void *p, s32 id, s32 a, s32 b);
extern "C" void  UiSetSpriteUv_28f970(void *p, s32 id, s32 a, s32 b, s32 c);
extern "C" void *MsgTableLookup_28aa30(void *p, s32 id);
extern "C" void  UiLayoutStringGlyphs_28a800(void *w, void *q, s32 a, s32 b, s32 c);
extern "C" s32   SkillFlowCountByItemMaybe_3e97c0(G *g, s16 id, s32 a, s32 b, s32 c, s32 d, s32 e);
extern "C" s32   ItemKindBelow4_3d4860(Ent *e);
extern "C" s32   ItemIsKind3_3d4630(Ent *e);
extern "C" s32   ItemGetOwnerCharaId_3d4d50(Ent *e, s32 a);
extern "C" VObj *ItemFindOwnerChara_3d4d80(Ent *e, s32 a);
extern "C" s32 ItemCharaMeetsLevelReq_3d46f0(Ent *, VObj *, int, int);

extern "C" s32 normal_ShopMenuBuyItemStatusLayout_50be30(Ent **pp);

s32 normal_ShopMenuBuyItemStatusLayout_50be30(Ent **pp)
{
    Tbl   tbl __attribute__((aligned(16)));
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
    tbl = *(const Tbl *)normal_D_00525A50;
    g = GetGameData_1fede0();
    UiSetWidgetSubItemValue_291250(D_004845CC, 0x55, 0, (s64)InvCountById_3c78d0(g->f18, e->f10->f00, flag, 0));
    w56 = UiGetWidgetSprite_28fe10(D_004845CC, 0x56, 0);
    if (w56 == 0) {
        return 0;
    }
    UiSetItemIconUv_288e50(w56, ShopRowGetItemIconIdMaybe_3ce890(pp), 0x28, 0x2D);
    w51 = UiGetWidgetSprite_28fe10(D_004845CC, 0x51, 0);
    w74 = UiGetWidgetSprite_28fe10(D_004845CC, 0x74, 0);
    w75 = UiGetWidgetSprite_28fe10(D_004845CC, 0x75, 0);
    if (w51 == 0) {
        return 0;
    }
    if (w74 == 0) {
        return 0;
    }
    if (w75 == 0) {
        return 0;
    }
    UiSetWidgetColor_2905b0(D_004845CC, 0x75, 1.0f, 1.0f, 1.0f, 1.0f);
    UiSetWidgetsVisibleById_291110(D_004845CC, 0x74, 1, 1);
    UiSetWidgetPos_290f60(D_004845CC, 0x74, 9, 6);
    if (ItemKindBelow4_3d4860(e) != 0) {
        UiSetWidgetsVisibleById_291110(D_004845CC, 0x59, 0, 1);
        UiSetWidgetsVisibleById_291110(D_004845CC, 0x53, 1, 1);
        r = ItemGetOwnerCharaId_3d4d50(e, 1);
        if (r == -1) {
            UiSetWidgetColor_2905b0(D_004845CC, 0x75, D_0047D288, D_0047D288, D_0047D288, 1.0f);
            UiSetWidgetPos_290f60(D_004845CC, 0x75, 0x32, 0x1E);
            UiLayoutStringGlyphs_28a800(w75, MsgTableLookup_28aa30(D_004845F8, 0x12), 0, 0, -2);
        } else {
            vt = ItemFindOwnerChara_3d4d80(e, 0);
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
                UiSetWidgetPos_290f60(D_004845CC, 0x75, 0x3C, 0x1E);
                UiLayoutStringGlyphs_28a800(w75, MsgTableLookup_28aa30(D_004845F8, 0x13), 0, 0, -2);
            } else if (((unsigned char)ItemCharaMeetsLevelReq_3d46f0(e, vt, 0, 0)) != 0) {
                UiSetWidgetPos_290f60(D_004845CC, 0x75, 0x3A, 0x1E);
                UiLayoutStringGlyphs_28a800(w75, MsgTableLookup_28aa30(D_004845F8, 0x11), 0, 0, -2);
            } else {
                hit = 1;
            }
            if (hit) {
                UiSetWidgetColor_2905b0(D_004845CC, 0x75, D_0047D288, D_0047D288, D_0047D288, 1.0f);
                UiSetWidgetPos_290f60(D_004845CC, 0x75, 0x28, 0x1E);
                UiLayoutStringGlyphs_28a800(w75, MsgTableLookup_28aa30(D_004845F8, 0x19), 0, 0, -2);
                UiSetWidgetColor_2905b0(D_004845CC, 0x53, D_0047D288, D_0047D288, D_0047D288, 1.0f);
            } else {
                UiSetWidgetColor_2905b0(D_004845CC, 0x53, 1.0f, 1.0f, 1.0f, 1.0f);
            }
            UiSetWidgetsVisibleById_291110(D_004845CC, 0x75, 1, 1);
        }
        if (ItemIsKind3_3d4630(e) != 0) {
            UiSetSpriteUv_28f970(D_004845CC, 0x53, 0x72, 0, 0);
        } else {
            if (r == -1) {
                UiSetWidgetsVisibleById_291110(D_004845CC, 0x53, 0, 1);
            } else {
                for (i = 0; i < 0xA; i++) {
                    if (r == tbl.r[i].f0) {
                        UiSetWidgetsVisibleById_291110(D_004845CC, 0x53, 1, 1);
                        UiSetSpriteUv_28f970(D_004845CC, 0x53, tbl.r[(u32)i].f2, tbl.r[(u32)i].f4, 0);
                        break;
                    }
                }
            }
        }
        UiSetWidgetsVisibleById_291110(D_004845CC, 0x52, 1, 1);
        goto done;
    }
    UiSetWidgetsVisibleById_291110(D_004845CC, 0x53, 0, 1);
    UiSetWidgetsVisibleById_291110(D_004845CC, 0x52, 0, 1);
    UiSetWidgetsVisibleById_291110(D_004845CC, 0x75, 0, 1);
    UiSetWidgetsVisibleById_291110(D_004845CC, 0x59, 1, 1);
    UiSetWidgetColor_2905b0(D_004845CC, 0x59, 1.0f, 1.0f, 1.0f, 1.0f);
    UiSetWidgetPos_290f60(D_004845CC, 0x59, 9, 0x1E);
    if (SkillFlowCountByItemMaybe_3e97c0(g, e->f10->f00, -1, 0, 1, 1, 0) > 0) {
        x = UiGetWidgetSprite_28fe10(D_004845CC, 0x59, 0);
        UiLayoutStringGlyphs_28a800(x, MsgTableLookup_28aa30(D_004845F8, 0x16), 0, 0, -2);
    } else if (SkillFlowCountByItemMaybe_3e97c0(g, e->f10->f00, -1, 1, 0, 0, 1) > 0) {
        x = UiGetWidgetSprite_28fe10(D_004845CC, 0x59, 0);
        UiSetWidgetColor_2905b0(D_004845CC, 0x59, D_0047D288, D_0047D288, D_0047D288, 1.0f);
        UiLayoutStringGlyphs_28a800(x, MsgTableLookup_28aa30(D_004845F8, 0x17), 0, 0, -2);
    } else {
        x = UiGetWidgetSprite_28fe10(D_004845CC, 0x59, 0);
        UiSetWidgetColor_2905b0(D_004845CC, 0x59, D_0047D288, D_0047D288, D_0047D288, 1.0f);
        UiLayoutStringGlyphs_28a800(x, MsgTableLookup_28aa30(D_004845F8, 0x18), 0, 0, -2);
    }
done:
    return 1;
}
