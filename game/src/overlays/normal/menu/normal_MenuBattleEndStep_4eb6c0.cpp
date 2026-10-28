/* rgp:protos */
#line 1
/* === SESSION 94 (2026-09-23): 185 -> MATCH, exact 727 words, MERGED,
 * NORMAL.BIN relinked BYTE-IDENTICAL at 654 units (armed: the 8-bad arm
 * reads DIFFERS at the link).  The scorer's last 3 are the three `.lit4`
 * notes, which n_olink retargets.  Seven edits, read off build/wf-normal/s94
 * (g1..g7):
 *  1. `++o->f010 > 0xF` for `>= 0x10` -- the $at-compare class
 *     ([[at-compare-class]]): retail's `slti $1` leaves $2 free, so the `sw`
 *     goes into the delay slot.  s93's "five spellings are one object" never
 *     varied the OPERATOR.  -1 word alone (a length half).
 *  2/3. `o->f008 > o->f00C` at cases 2 and 3: retail loads f008 FIRST, and in
 *     case 3 that load is the dispatch `beql`'s delay slot.
 *  4. the index cast placement in case 3's loop -- all three f02C accesses of
 *     the `f018 == 0` compare/store on `(s32)m`, the `f024 = f014` store on
 *     `(s32)m`, and the `f004 != 0` test on PLAIN `m`.  This is the +2 partner
 *     to edit 1: 185 -> 22 at exact length.
 *  5. `50.0f - (f32)(s32)(i * 4)` at case 6's FIRST site: creates the constant
 *     before the conversion ($f0/$f1).  22 -> 18.
 *  6. `((Rec *)o->f02C)[m].f028 += o->f02C[m].f030;` -- a no-op cast on ONE
 *     side makes the base load precede the m*52 chain in IR order (the
 *     allocator dump: chain 299..303, load 304 -> ours idx=v1 base=v0).
 *     Cast on both sides, `(u32)m`, `m[..]`, `(p + m)` are all byte-identical.
 *  7. site 2's compare: one side `((Rec *)o->f02C)[(s32)m]`, and the STORE's
 *     RHS spelled EXACTLY like the compare's converted operand so the `(f32)`
 *     conversion CSEs (81-arm cross g7: only A==C, B==D, A!=B reach 3).
 * Everything below predates this session. */
/* === SESSION 93 (2026-09-22): 300 -> 185 BAD at exact 727 words, and the
 * CALLEE-SAVED MAP IS NOW RETAIL'S EXACTLY (reghist: s1 130/130, s2 37/37,
 * s3 14/14, s4 7/7, s0 35 vs 37 -- the last 2 are the unit's known 2-word
 * source delta, not a colour).  ONE EDIT:
 *
 *     s32 m;                       <- DECLARED FIRST, before `Box *b;`
 *     ...
 *     for (m = 0; m < o->f008; m++) {      <- the SECOND of the three
 *         ...o->f0F0[m]... o->f02C[m]...    `for (i = ...)` loops, the one
 *     }                                     that walks f0F0/f02C
 *
 * *** WHY.  s93's vreg-index lever ([[levers.d/mwcc-propagated-temp-colouring]]):
 * mwcc numbers nodes 32.. as the declared locals in DECLARATION ORDER then
 * temps in IR order, and simplify removes ASCENDING INDEX inside a pass.  The
 * parameter `o` (node 32, deg 263) was the ONLY node left in simplify pass 3,
 * so it was selected FIRST and took $16 -- retail wants its 130-mention web at
 * $17, i.e. exactly ONE MORE WEB has to survive pass 2.  Three nodes need only
 * +1 interference (s93/hd.py, the SIMPLIFY HEADROOM screen: scan-degree 24
 * against K=25); s93/pick.py says which one by scoring each candidate's
 * resulting per-register MENTION TOTALS against retail's; and s93/pick2.py
 * says the +1 is free -- a node's scan degree is low only because LOWER-INDEXED
 * NEIGHBOURS were removed before it in the same pass, so GIVING IT AN INDEX
 * BELOW 34 holds it back.  Below 34 means being the FIRST DECLARED LOCAL.
 * `i` is shared by three loops, so each loop's counter is a SPLIT web with a
 * high index; giving this loop its own variable is what makes the declaration
 * position reachable at all.
 * ** ARMED: `m` declared FIRST and SECOND are the same object (185); declared
 * LAST is BYTE-IDENTICAL to the old base (300).  The cut is exactly where
 * pick2.py predicted (index < 34), which is the model confirmed end to end.
 *
 * THE RESIDUE is now ONE REGION, words 295..467 (the case-3 loop) plus 67/68,
 * 255..257, 490, 602..615, and it is a SCHEDULE/SOURCE-SHAPE grind:
 *  - it opens with `if (++o->f010 >= 0x10)`: retail computes the test BEFORE
 *    the store and puts `sw 0x10($17)` in the BRANCH DELAY SLOT; we store then
 *    test and pay a `nop`.  FIVE spellings (s93/gd.py: a named temp, the store
 *    after the test, `o->f010 = o->f010 + 1`, `o->f010++`, the base) are ONE
 *    OBJECT; only "store inside the if" differs and is worse (186).
 *  - retail keeps `m * sizeof(Rec)` in $18 and RELOADS `lw 0x2C($17)` at each
 *    site.  NAMING that offset goes the WRONG WAY (s93/ge.py): `s32 ro`,
 *    `u8 *ro` and a `Rec *rw` row pointer are 717/717/690 words against 727,
 *    i.e. the name makes the CSE stronger and we are already one word SHORT.
 * NOT MERGED.
 * Everything below predates this session. */
/* === SESSION 87 (2026-09-22): STILL 300 BAD.  s87/e1.py ran the whole
 * 68-name boolean `opt_*` table spelled `off` -- this unit had NO pragma
 * sweep on record.  Armed both ways.  Five live columns, none better:
 * opt_lifetimes 318 at exact length, common_subs +129 w, propagation +10,
 * loop_invariants +2, dead_assignments +4.  The pragma-ALONE column is
 * closed on this unit.  Everything below predates this session. */
/* === SESSION 73 (2026-09-21, SOLO): 310 -> 300 bad, exact 727 words.  TEN of
 * this unit's THIRTEEN `.lit4` residue words closed, -1 each, exactly
 * additive.  âš âš  THIS PARTLY REVERSES s49: s49 installed these pool entries as
 * LITERALS and read 313 -> 297, but the object shows retail loading them from
 * the shared MAIN gp pool, so the literal spelling leaves the word bad.
 * [[levers.d/mwcc-float-literal-pool]] IS A TWO-WAY LEVER and the retail word
 * decides which way -- see build/wf-normal/s73/lit4back.py, the reverse of
 * s49's poolscan.py.
 * INSTALLED (value -> symbol): 0.05f -> D_0047D844 (2 sites), 0.1f ->
 * D_0047D91C (2 of the 3 sites), -0.1f -> D_0047D924, -0.0833333358168602f ->
 * D_0047D928 (3 sites), -0.07f -> D_0047D92C, 0.3f -> D_0047D7C4.
 * â˜… THREE SITES GO THE OTHER WAY and are LEFT AS LITERALS -- prices in
 * build/wf-normal/s73/d4.py:
 *     -0.2f at the 0x48 call   +3      0.1f at the 0x10 call   +4
 *      0.4f at the 0x103 call  +6
 *   so ALL_13 together is 313, WORSE than the park.  The subset matters:
 *   price every site alone before combining.
 * Everything below predates this session. */
/* === SESSION 49 (2026-09-08): 313 -> 297 bad, exact 727 words.  THE FLOAT
 * LITERAL POOL IS MUCH BIGGER THAN THE BOARD RECORDED.  s48 wrote the pool as
 * 0x0047D1FC-0x0047D7FF; dumping main's data word by word shows ONE CONTINUOUS
 * run of hand-typed decimals from 0x0047D180 to about 0x0047DDFC.  Everything
 * from 0x0047D800 up was invisible to s48's poolscan.py.
 * The three entries that paid here are ALL in the newly visible half:
 *   D_0047D8B0 (-0.2f)  313 -> 309
 *   D_0047D91C ( 0.1f)  313 -> 308
 *   D_0047D920 ( 0.4f)  313 -> 306
 * and all eight together give 297.  Installed: all eight as literals.
 * See [[mwcc-float-literal-pool]] and build/wf-normal/s49/poolscan.py, whose
 * bounds are now 0x0047D180-0x0047DE00.
 * Everything below predates this. */
/* SESSION 31 STAGE 2 (same six decks, re-run from the stage-1 bases).
 * Installed arm `I_s32_L558_26_idx` from the index-cast deck.
 *   before: 725 words, ? bad   after: 727 words, 332 bad   (retail 727 words)
 * Everything below predates THIS install; read older numbers as history.
 * Re-score with build/wf-normal/s31/nscore.py, not dv_osbuild.py. */
/* SESSION 31 (combined six-deck sweep, 31,338 arms over 98 units).
 * Installed arm `I_s32_L539_8_idx` from the index-cast deck (mkidx31.py)
 *   before: 717 words, ? bad   after: 725 words, ? bad   (retail 727 words)
 * Every line BELOW this note predates that install -- read its numbers
 * as the state at the time it was written, not as the current score.
 * Re-score with build/wf-normal/s31/nscore.py, not dv_osbuild.py.
 * KEEP OUT OF config/ocunits/normal.txt. */
#include "types.h"
extern "C" {
extern f32 D_0047D8B0;   /* gp - 0x78C0, -0.2f */
extern f32 D_0047D844;   /* gp - 0x792C,  0.05f */
extern f32 D_0047D91C;   /* gp - 0x7854,  0.1f */
extern f32 D_0047D920;   /* gp - 0x7850,  0.4f */
extern f32 D_0047D924;   /* gp - 0x784C, -0.1f */
extern f32 D_0047D928;   /* gp - 0x7848, -0.0833333358168602f */
extern f32 D_0047D92C;   /* gp - 0x7844, -0.07f */
extern f32 D_0047D7C4;   /* gp - 0x79AC,  0.3f */
}

/* normal 0x004EB6C0 -- the roster/formation SCENE's per-frame phase driver,
 * 2,912 bytes / 728 instructions.  Same `Scene` object as the merged
 * normal_FUN_004EC990.cpp, and the Rec / Slot / vtable layouts are lifted
 * verbatim from that unit's header.
 *
 * Two `lw $25,0($X) / lw $25,0x43C-or-0x444($25) / jalr $25` sites -> C++
 * virtual, vptr offset 0, slots (0x43C-8)/4 = 269 and (0x444-8)/4 = 271.
 * normal_FUN_004EC990 already proved slot 271 on this very class.
 *
 * The phase machine is a `switch` on o->f000 with cases written ASCENDING
 * 0,1,2,3,4,5,6,7,0xFF while retail's compare chain runs DESCENDING -- the
 * recorded m2c-switch-arm-order rule.  case 4 FALLS THROUGH into case 5, and
 * case 0xFF is an EMPTY arm (its `beql` goes straight at the shared tail's
 * SECOND instruction, i.e. the tail's `daddu $4,$17,$0` is duplicated into the
 * branch-likely delay slot).
 *
 * The negative-state arm is placed out of line AFTER the tail, so the source
 * is `if (o->f000 >= 0) { ... } else if (o->f000 == -2) { ... }`.
 *
 * gp floats: -0x78C0 = -0.2f, -0x792C = 0.05f, -0x7854 = 0.1f,
 * -0x7850 = 0.4f, -0x784C = -0.1f, -0x7848 = -0.0833333358168602f,
 * -0x7844 = -0.07f, -0x79AC = 0.3f; -0xD90 = D_004843E0.
 */

struct Obj {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 slot269(s32 a) { return VCM(s32, (void *, s32), 0x43C, a); }   /* vtable +0x43C */
    
    s32 slot271(s32 a) { return VCM(s32, (void *, s32), 0x444, a); }   /* vtable +0x444 */
};

typedef struct Rec {
    s32 f000;
    s32 f004;
    s32 f008;
    s32 f00C;
    s32 f010;
    s32 f014;
    s16 f018;
    u8  pad01A[6];
    s32 f020;
    s32 f024;
    f32 f028;
    f32 f02C;
    f32 f030;
} Rec;

typedef struct Slot {
    f32 f000;
    f32 f004;
    s16 f008;
    u8  pad00A[2];
} Slot;

typedef struct Scene {
    s32   f000;
    s32   f004;
    s32   f008;
    s32   f00C;
    s32   f010;
    u8    f014[0x18];
    Rec  *f02C;
    Slot  f030[9];
    u8    f09C[0x10];
    u8    f0AC[0x40];
    void *f0EC;
    s8    f0F0[9];
    s8    f0F9[9];
    s16   f102;
    s16   f104;
    s16   f106;
    void *f108;
    s16   f10C;
    s16   f10E;
    u8    f110;
    u8    f111;
    u8    f112;
    u8    f113;
    u8    f114;
} Scene;

typedef struct Box { s16 f000; s16 f002; s16 f004; u8 pad006[0x1A]; s16 f020; } Box;
typedef struct Handle { u8 pad000[0x20]; Box *f020; } Handle;
typedef struct Ctx { u8 pad000[0x14]; void *f014; } Ctx;

extern "C" u8 D_004B2570[];

extern "C" void *D_004843E0;          /* gp - 0x0D90 */

extern "C" {

extern s32     PadIsTriggered_1839f0(void *a, s32 b);
extern void    SoundPlayScaledVolume_1b9520(void *a, s32 id, s32 b, f32 v);
extern Ctx    *GetGameData_1fede0(void);
extern Obj    *CharaMgrPoolFindById_3a8c60(void *a, s32 i);
extern Handle *UiFindWidget_290460(void *a, u16 id);
extern void    UiFadeWidgetAlpha_290690(void *a, u16 id, f32 x, f32 y, f32 z);
extern f32     UiGetWidgetAlpha_290770(void *a, u16 id);
extern void UiMoveWidgetUniform_290f50(void *, u16, s32, s32, f32, s32);
extern void    UiGetWidgetPos_2910a0(void *a, u16 id, s32 *px, s32 *py);
extern void    UiSetWidgetsVisibleById_291110(void *a, u16 id, s32 c, s32 d);
extern void    UiUpdateWidgets_2913a0(void *a);

extern void normal_MenuBattleEndLevelUpGlowUpdate_4ea0f0(Scene *o);
extern void normal_MenuBattleEndLevelUpLabelUpdate_4ea3f0(Scene *o);
extern void normal_MenuBattleEndSlideOutNop_4ea6f0(void);
extern void normal_MenuBattleEndItemRowsCascade_4ea700(Scene *o);
extern void normal_MenuBattleEndItemRowsShow_4ea890(Scene *o);
extern void normal_MenuBattleEndItemRowsCountUpdateMaybe_4eb150(Scene *o);
extern void normal_MenuBattleEndExpBonusAnimMaybe_4eb290(Scene *o);
extern void normal_MenuBattleEndExpBonusShowMaybe_4eb400(Scene *o);
extern void normal_MenuBattleEndItemRowsSlide_4eb4b0(Scene *o);
extern void normal_MenuBattleEndMemberRowsFadeIn_4eb5f0(Scene *o);
extern void normal_MenuBattleEndSkipInput_4ec220(Scene *o);
extern void normal_MenuBattleEndPromptBlink_4ec870(Scene *o);
extern void normal_MenuBattleEndMemberRowsRefreshMaybe_4ed370(Scene *o, s32 k);

extern void normal_MenuBattleEndStep_4eb6c0(Scene *o);

}

void normal_MenuBattleEndStep_4eb6c0(Scene *o)
{
    s32 m;
    Box *b;
    Obj *ob;
    s32 sx;
    s32 sy;
    s32 ok;
    s32 j;
    s32 y;
    s32 id;
    s32 k;
    s32 n;
    s32 i;

    if (o->f111 == 0) {
        return;
    }

    if (o->f102 != 0) {
        if (--o->f102 <= 0) {
            o->f102 = 0;
            UiFadeWidgetAlpha_290690(o->f014, 0x48, 0.0f, -0.2f, -1.0f);
            o->f000 = 0;
        }
    }

    if (o->f000 >= 0) {
        normal_MenuBattleEndSkipInput_4ec220(o);
        normal_MenuBattleEndItemRowsSlide_4eb4b0(o);
        normal_MenuBattleEndExpBonusAnimMaybe_4eb290(o);
        normal_MenuBattleEndItemRowsCountUpdateMaybe_4eb150(o);
        normal_MenuBattleEndItemRowsCascade_4ea700(o);
        normal_MenuBattleEndMemberRowsFadeIn_4eb5f0(o);
        normal_MenuBattleEndMemberRowsRefreshMaybe_4ed370(o, 0);
        normal_MenuBattleEndLevelUpLabelUpdate_4ea3f0(o);
        sx = 0;
        sy = 0;
        switch (o->f000) {
        case 0:
            o->f010 = 0;
            o->f000 = 1;
            o->f104 = 0;
            break;
        case 1:
            o->f110 = 1;
            UiSetWidgetsVisibleById_291110(o->f014, 0xF, 1, 1);
            UiSetWidgetsVisibleById_291110(o->f014, 0x12, 1, 1);
            b = UiFindWidget_290460(o->f014, 0xF)->f020;
            b->f004 += 0x14;
            b->f020 = b->f004;
            b = UiFindWidget_290460(o->f014, 0x12)->f020;
            b->f000 -= 0x14;
            if (b->f000 < -0xFF) {
                b->f000 = -0x100;
            }
            b->f004 += 0x14;
            if (b->f004 >= 0x100) {
                b->f004 = 0x100;
            }
            b->f020 = b->f000 - 2;
            if (b->f004 >= 0xB4) {
                y = 0;
                for (i = 0; i < o->f008; i++) {
                    if (i >= o->f00C) {
                        y = 6;
                    } else {
                        UiFadeWidgetAlpha_290690(o->f014, (u16)(i * 4 + 0x2D), 1.0f, D_0047D844, -1.0f);
                    }
                    id = i * 3 + 0x15;
                    UiMoveWidgetUniform_290f50(o->f014, (u16)id, 0xC, (y + 0x3D) + i * 0x2A, 30.0f, 1);
                    UiFadeWidgetAlpha_290690(o->f014, (u16)id, 1.0f, D_0047D844, 0.0f);
                }
                o->f010 = 0;
                normal_MenuBattleEndItemRowsShow_4ea890(o);
                o->f000 = 2;
            }
            break;
        case 2:
            b = UiFindWidget_290460(o->f014, 0xF)->f020;
            b->f004 += 0x14;
            if (b->f004 >= 0x100) {
                b->f004 = 0x100;
                UiFadeWidgetAlpha_290690(o->f014, 0x10, 1.0f, 0.1f, -1.0f);
                UiFadeWidgetAlpha_290690(o->f014, 0x13, 1.0f, D_0047D91C, -1.0f);
            }
            b->f020 = b->f004;
            b = UiFindWidget_290460(o->f014, 0x12)->f020;
            b->f000 -= 0x14;
            if (b->f000 < -0xFF) {
                b->f000 = -0x100;
            }
            b->f004 += 0x14;
            if (b->f004 >= 0x100) {
                b->f004 = 0x100;
            }
            b->f020 = b->f000 - 2;
            UiMoveWidgetUniform_290f50(o->f014, 2, 0x103, 0xD0, 0.4f, 0);
            UiFadeWidgetAlpha_290690(o->f014, 2, 1.0f, D_0047D91C, -1.0f);
            if (o->f008 > o->f00C) {
                UiSetWidgetsVisibleById_291110(o->f014, 0x14, 1, 1);
            }
            b = UiFindWidget_290460(o->f014, 0x14)->f020;
            b->f004 += 0xA;
            if (b->f004 >= 0xFC) {
                b->f004 = 0xFC;
            }
            UiGetWidgetPos_2910a0(o->f014, (u16)((o->f008 - 1) * 3 + 0x15), &sx, &sy);
            if (sx >= 0xC) {
                if (++o->f010 > 0xF) {
                    normal_MenuBattleEndExpBonusShowMaybe_4eb400(o);
                    o->f000 = 3;
                    o->f0F0[0] = 1;
                }
            }
            break;
        case 3:
            if (o->f008 > o->f00C) {
                UiSetWidgetsVisibleById_291110(o->f014, 0x14, 1, 1);
            }
            b = UiFindWidget_290460(o->f014, 0x14)->f020;
            b->f004 += 0xA;
            if (b->f004 >= 0xFC) {
                b->f004 = 0xFC;
            }
            o->f10C++;
            for (m = 0; m < o->f008; m++) {
                k = o->f10C / 8;
                if (o->f008 < k) {
                    k = o->f008 - 1;
                }
                if (o->f0F0[k] == -1) {
                    o->f0F0[k] = 1;
                }
                if (o->f0F0[m] != 1) {
                    continue;
                }
                ((Rec *)o->f02C)[m].f028 += o->f02C[m].f030;
                if (o->f02C[m].f018 == 0) {
                    if (o->f02C[m].f004 != 0) {
                        SoundPlayScaledVolume_1b9520(D_004843E0, 0x13, 0, 1.0f);
                    }
                    if (o->f02C[(s32)m].f028 >= (f32)((Rec *)o->f02C)[(s32)m].f024) {
                        o->f02C[(s32)m].f028 = (f32)((Rec *)o->f02C)[(s32)m].f024;
                        o->f0F0[m] = 0;
                    }
                } else {
                    if (o->f02C[m].f028 >= o->f02C[m].f02C) {
                        o->f02C[m].f028 = 0.0f;
                        ob = CharaMgrPoolFindById_3a8c60(GetGameData_1fede0()->f014, o->f02C[m].f000);
                        o->f02C[m].f020 = ob->slot269(o->f02C[m].f020);
                        n = ob->slot271(o->f02C[m].f020);
                        o->f02C[m].f02C = (f32)n;
                        o->f02C[m].f030 = (f32)(n / 32);
                        o->f02C[m].f018--;
                        if (o->f02C[m].f018 == 0) {
                            o->f02C[(s32)m].f024 = o->f02C[(s32)m].f014;
                        }
                        o->f030[m].f008 = 1;
                        o->f0F9[m] = 1;
                        if (o->f004 <= 0) {
                            if (o->f02C[m].f004 != 0) {
                                SoundPlayScaledVolume_1b9520(D_004843E0, 0x14, 0, 1.0f);
                            }
                        } else {
                            SoundPlayScaledVolume_1b9520(D_004843E0, 0x15, 0, 1.0f);
                        }
                        o->f004++;
                    }
                }
            }
            ok = 1;
            for (j = 0; j < o->f008; j++) {
                if (o->f0F0[j] != 0) {
                    ok = 0;
                }
            }
            if (ok != 0) {
                o->f010 = 0x14;
                o->f000 = 4;
                o->f10E = 0x28;
            }
            break;
        case 4:
            if (o->f114 != 0) {
                break;
            }
            /* fall through */
        case 5:
            if (o->f10E != 0) {
                if (--o->f10E <= 0) {
                    UiMoveWidgetUniform_290f50(o->f014, 0xF, -0x12C, 0x2D, 30.0f, 1);
                    UiMoveWidgetUniform_290f50(o->f014, 0x12, 0x32C, 0x2D, 30.0f, 1);
                    o->f000 = 6;
                    o->f10E = 0;
                }
            }
            if (o->f114 != 0 && PadIsTriggered_1839f0(D_004B2570, 0x40) != 0) {
                UiMoveWidgetUniform_290f50(o->f014, 0xF, -0x12C, 0x2D, 30.0f, 1);
                UiMoveWidgetUniform_290f50(o->f014, 0x12, 0x32C, 0x2D, 30.0f, 1);
                o->f000 = 6;
                o->f10E = 0;
            }
            normal_MenuBattleEndPromptBlink_4ec870(o);
            break;
        case 6:
            if (o->f114 != 0) {
                UiFadeWidgetAlpha_290690(o->f014, 0x47, 0.0f, D_0047D924, -1.0f);
            }
            UiGetWidgetPos_2910a0(o->f014, 0xF, &sx, &sy);
            if (sx < -0x45) {
                y = 0;
                for (i = 0; i < o->f008; i++) {
                    if (i >= o->f00C) {
                        y = 6;
                    } else {
                        id = i * 4 + 0x2D;
                        UiMoveWidgetUniform_290f50(o->f014, (u16)id, 0x212, i * 0x2A + 0x3D, 50.0f - (f32)(s32)(i * 4), 1
);
                        UiFadeWidgetAlpha_290690(o->f014, (u16)id, 0.0f, D_0047D928, 1.0f);
                    }
                    id = i * 3 + 0x15;
                    UiMoveWidgetUniform_290f50(o->f014, (u16)id, -0x12C, (y + 0x3D) + i * 0x2A, 50.0f - (f32)(i * 4), 1
);
                    UiFadeWidgetAlpha_290690(o->f014, (u16)id, 0.0f, D_0047D928, 1.0f);
                }
                UiFadeWidgetAlpha_290690(o->f014, 1, 0.0f, D_0047D92C, -1.0f);
                UiMoveWidgetUniform_290f50(o->f014, 0x14, -0x12C, 0xBD, 30.0f, 1);
                normal_MenuBattleEndSlideOutNop_4ea6f0();
                UiMoveWidgetUniform_290f50(o->f014, 2, 0x212, 0xD0, D_0047D7C4, 0);
                UiFadeWidgetAlpha_290690(o->f014, 2, 0.0f, D_0047D928, -1.0f);
                o->f000 = 7;
            }
            break;
        case 7:
            if (UiGetWidgetAlpha_290770(o->f014, (u16)((o->f008 - 1) * 3 + 0x15)) <= 0.0f) {
                o->f000 = -1;
                o->f110 = 0;
                o->f104 = 0;
            }
            break;
        case 0xFF:
            break;
        }
        normal_MenuBattleEndLevelUpGlowUpdate_4ea0f0(o);
        UiUpdateWidgets_2913a0(o->f014);
    } else if (o->f000 == -2) {
        UiUpdateWidgets_2913a0(o->f014);
    }
}
