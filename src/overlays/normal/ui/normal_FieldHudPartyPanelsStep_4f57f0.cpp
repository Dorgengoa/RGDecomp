#pragma optimization_level 3
/* ★★★★★★★ CLOSED / MOVED, s27, BY `#pragma optimization_level 3`.
 * mwcc's DEFAULT here is -O4.  Level 3 is a DISTINCT AXIS from the `opt_*`
 * pragma namespace [[mwcc-pragma-namespace]] enumerates: 14 `opt_*` arms were a
 * clean null on normal_FieldHudLeaderChangedNop_4f50e0 and 23 were a clean null on this unit's
 * residue, while the LEVEL knob moved both.  Screened over all 68 open drafted
 * normal units in build/wf-normal/s27/olevel.log (levels 1/2/3): levels 1 and 2
 * are catastrophic on every unit, level 3 CLOSED normal_FieldHudPartyPanelsStep_4f57f0 and
 * normal_MenuBattleEndMemberRowsFadeIn_4eb5f0 outright and took normal_ShopMenuSellItemStatusLayout_50ef80 and
 * normal_BtlChgMenuWeaponGridDrawCb_503930 from LENGTH-WRONG to the RIGHT LENGTH. */
#include "types.h"
/* ==================================================================== *
 *  PARKED -- RIGHT LENGTH, **26 BAD** (was 38), ALL OF THEM PURE REGISTERS.
 *  DELIBERATELY *NOT* IN config/ocunits/normal.txt.  Right length is the
 *  one kind of residue olink's length guard cannot catch, so admitting
 *  this would ship a wrong image that still links byte-identical.
 *
 *  ★★★ 2026-09-01, lane `ne`: 38 -> 26 BY ONE C++-ONLY SPELLING.
 *  `for (s32 j = 0; j < cnt; j++)` -- the loop counter declared IN THE FOR
 *  INIT -- is worth **12 words** and it clears the ENTIRE third loop region.
 *  The recorded 24-permutation declaration sweep below could not reach it:
 *  in C every local must be declared at the top of the block, so that sweep
 *  permuted ONE list and `j` was always in it.  A C-measured null does not
 *  bind a C++ unit, and this is the proof.
 *
 *  ⚠ AND THAT IS THE ONLY LIVE CELL ON THE C++ SCOPING AXIS.  Six further
 *  point-of-use declarations -- `for (s32 i)` in region 1, `s32 t`/`u16 id`
 *  inside the loop body, `u16 id2`/`u16 m`, `Ent *o` at all three sites,
 *  `s32 cnt` at all three sites, `Root *q` at all three sites -- are ONE
 *  OBJECT, 42788c6d, byte-identical to the base.  Only the FOR-INIT position
 *  is live.
 *
 *  RESIDUE NOW: one 4-CYCLE confined to the SECOND loop region
 *  (0x004F59D4-0x004F5B9C); region 1 and region 3 are byte-identical.
 *      ours    q=$19  j=$16  t=$18  id=$17
 *      retail  q=$17  j=$19  t=$16  id=$18
 *  Re-measured on the NEW base: 9 declaration orders -> exactly TWO objects,
 *  26 (`id` first of {id,q,t}) and 42 (`q` or `t` first).  Same two-valued
 *  shape the old base had; a cycle still has no pair swap.
 *
 *  ★★ 2026-09-01, s22 -- THE DECLARATION AXIS IS NOW A **WHOLE-LIST** NULL,
 *  not a window one.  [[mwcc-wholelist-decl-sweep]] says move ONE decl through
 *  EVERY position of the FULL list rather than permuting a window, and the
 *  recorded sweeps here were windows over {j,id,q,t}.  Done properly -- `id`,
 *  `q`, `t`, `n`, `cnt` and `i` each through ALL 12 positions of the full local
 *  list, 67 arms -- the result is still **exactly TWO objects**, 26 and 42.
 *  build/wf-normal/s22/v_57f0.py, sw_57f0.log.  Declaration order is spent.
 *
 *  ★★ AND THE s22 CSE LEVER DOES NOT REACH IT EITHER.  The 4-cycle is a
 *  RANKING reversal -- retail ranks j > id > q > t and we rank q > t > id > j --
 *  so the natural idea is that retail RECOMPUTES `j * 7` inside the `if` (which
 *  would raise j's in-loop weight and drop t's), exactly the split that closed
 *  [[normal-cse-cost-split]] this session.  Nine arms: `j * 7 + 0xC` inline,
 *  `(u32)j * 7 + 0xC`, `j * 7 + 6 + 6`, `id + 6`, and the same four with `t`
 *  dropped entirely -- **every same-length arm is the BASE OBJECT**.  mwcc
 *  forward-substitutes the named `t` and canonicalises all of them, which is
 *  [[mwcc-volatile-access-site-pin]]'s stated failure mode for named-local
 *  arms; the three `(u32)` arms are one word LONG.
 *  build/wf-normal/s22/v_57f0b.py.
 *
 *  Measured negatives against the OLD (38-bad) base, kept for the record:
 *   * all 24 declaration orders of {j,id,q,t}  -> exactly TWO objects,
 *     38 and 54 bad (build/n_perm4f57f0.py).
 *   * live-range edits: do/while, splitting q, splitting cnt, merging both
 *     loop bounds into one variable, dropping id2, moving the frame locals
 *     -> 38 (build/n_arms3.py, n_arms4.py).
 *   * statement order: j*7 inline, id before t, masked id definition -> 38.
 *   * the register-class and optimizer pragma axis: cse_hard_reg_gpr,
 *     reg_class_allocs, cse_hard_reg_special, opt_lifetimes,
 *     opt_movepostops, opt_common_subs, opt_serializeassignments -> 38;
 *     opt_dead_assignments off -> 44; opt_repositioncode on -> length.
 *  Sweep drivers: build/wf-normal/var/ne/q3arms.py, q3arms2.py, q3arms3.py.
 * ==================================================================== */
/* normal 0x004F57F0 -- the party-formation panel's open/close driver.  1,808
 * bytes, 61 calls.  Three states in f2B0 (0 = idle, 1 = slide in, 2 = slide
 * out), each re-reading the field, and each state's own two-step in f2B2.
 *
 * One VIRTUAL call (`lw $25,0($2) / lw $25,0xF0($25) / jalr $25`), so this unit
 * is .cpp: a struct of function pointers gives `jalr $v0`, only a real C++
 * `virtual` gives `jalr $t9`.  mwcc puts the first virtual at vtable slot
 * +0x08, so 0xF0 is index (0xF0-8)/4 = 58; the placeholder list is expanded by
 * build/n_gen4f57f0.py from that OFFSET so the index cannot drift.
 *
 * ★ THE WIDGET IDS ARE THE CALLEE'S u16 PARAMETER, AND THAT IS THE WHOLE
 * `andi` STORY -- there is not one explicit cast in this function.  `id` is a
 * u16 LOCAL, so passing it straight through is a bare `daddu $5,$18,$0`, while
 * `id + 1` has to promote it first: `andi / addiu / andi`, three words, exactly
 * what retail has at 0x004F5A6C.  Where the SAME promotion feeds two calls
 * (`id + 2` and `id + 3`) mwcc CSEs it into a callee-saved register and retail
 * has the single `andi $16,$18,0xFFFF` -- the recorded "the CSE only appears at
 * two or more" lever, seen here in both directions inside one loop body.
 *
 * `i * 0x7D` and `j * 7` are named locals because both are read on the far side
 * of a call (and `j * 7` on the far side of a BRANCH, where mwcc's
 * per-basic-block CSE cannot reach it).
 *
 * The stores that land in a call's delay slot -- `p->f370` before both
 * func_1FEDE0 calls and `p->f36C` before normal_FieldHudPanelsFadeTo_4f4860 -- are written
 * BEFORE the call in the source; that is what sinks them into the slot.
 * `mtc1 $0,$f1 / nop / c.le.s` is the mfc1-hazard nop, compiler output. */

struct Ent {
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
    virtual s32 alive();          /* slot 58 -> vtable +0xF0 */
};

typedef struct Root {
    u8   pad000[0x18];
    void *f018;
} Root;

typedef struct Obj {
    u8   pad000[0x2B0];
    s16  f2B0;
    s16  f2B2;
    s16  f2B4[(0x36C - 0x2B4) / 2];
    s32  f36C;
    s32  f370;
    u8   pad374[0x378 - 0x374];
    s16  f378;
    u8   pad37A[0x37E - 0x37A];
    s16  f37E;
    u8   pad380[0x3D8 - 0x380];
    s16  f3D8;
    s16  f3DA;
    u8   pad3DC[0x49C - 0x3DC];
    s16  f49C;
    s16  f49E;
    s16  f4A0;
    s16  f4A2;
    s16  f4A4;
    s16  f4A6;
} Obj;

extern "C" f32   D_0047D248;      /* gp - 0x7F28 */
extern "C" f32   D_0047D288;      /* gp - 0x7EE8 */
extern "C" f32   D_0047DA74;      /* gp - 0x76FC */
extern "C" f32   D_0047DA78;      /* gp - 0x76F8 */

extern "C" Root *func_1FEDE0(void);
extern "C" void  func_290010(void *p, u16 id, s32 c, s32 d);
extern "C" void  func_290690(void *p, u16 id, f32 x, f32 y, f32 z);
extern "C" f32   func_290770(void *p, u16 id);
extern "C" void  func_2907A0(void *p, u16 id, f32 x);
extern "C" void  func_290F50(void *p, u16 id, s32 c, s32 d, s32 e, f32 x);
extern "C" void  func_290F60(void *p, u16 id, s32 c, s32 d);
extern "C" void  func_2910A0(void *p, u16 id, s32 *c, s32 *d);
extern "C" void  func_291110(void *p, u16 id, s32 c, s32 d);
extern "C" void  func_3AE1A0(Ent *o);
extern "C" Ent  *func_3C2420(void *w, s32 i);
extern "C" void  normal_FieldHudPanelsFadeTo_4f4860(void *p, f32 x, f32 y);
extern "C" void  normal_FieldHudPanelsFadeUpdate_4f6d30(void);
extern "C" void  normal_FieldHudTacticsModeIconRefresh_4f7be0(void *p);
extern "C" void  normal_FieldHudWidget87Close_4f9c00(void *p);
extern "C" s32   normal_FieldHudPartyRowCount_4f9c50(void *p);

extern "C" void normal_FieldHudPartyPanelsStep_4f57f0(Obj *p);

void normal_FieldHudPartyPanelsStep_4f57f0(Obj *p)
{
    s32   x;
    s32   y;
    /* DECLARATION ORDER IS LOAD-BEARING: later in the list means a LOWER
     * callee-saved register, and retail reads $21=cnt, $19=j, $18=id/i,
     * $17=q, $16=n/t in BOTH loop regions at once. */
    s32   cnt;
    u16   id;
    s32   i;
    Root *q;
    s32   n;
    s32   t;
    Ent  *o;
    s32   st;
    u16   id2;
    u16   m;

    if (p->f378 != 0) {
        st = p->f2B0;
        if (st == 0) {
            normal_FieldHudPanelsFadeUpdate_4f6d30();
            return;
        }
        if ((s16)st == 1) {
            if (p->f2B2 == 0) {
                p->f370 = 0;
                q = func_1FEDE0();
                if (q == 0) {
                    return;
                }
                n = normal_FieldHudPartyRowCount_4f9c50(p);
                for (i = 0; i < n; i++) {
                    id = i * 7 + 6;
                    cnt = i * 0x7D;
                    func_290F60(p, id, cnt + 0xA, 0x17C);
                    func_291110(p, id, 0, 1);
                    id = i + 3;
                    func_290F60(p, id, cnt + 0x26, 0x16F);
                    func_291110(p, id, 0, 1);
                    p->f2B4[i] = 0;
                }
                func_291110(p, 0x24, 0, 1);
                func_290F60(p, 0x24, 0xDF, 0x15);
                normal_FieldHudTacticsModeIconRefresh_4f7be0(p);
                func_290F60(p, 2, 0, 0x178);
                for (i = 0; i < n; i++) {
                    o = func_3C2420(q->f018, i);
                    if (o != 0) {
                        func_3AE1A0(o);
                    }
                }
                func_290010(p, 2, 0, -1);
                p->f36C = 0;
                normal_FieldHudPanelsFadeTo_4f4860(p, 1.0f, 10.0f);
                p->f2B2 = p->f2B2 + 1;
            }
            if (p->f2B2 == 1) {
                q = func_1FEDE0();
                if (q == 0) {
                    return;
                }
                cnt = normal_FieldHudPartyRowCount_4f9c50(p);
                func_291110(p, 0x24, 1, 1);
                func_290690(p, 0x24, D_0047D288, D_0047DA74, 0.0f);
                for (s32 j = 0; j < cnt; j++) {
                    t = j * 7;
                    id = t + 6;
                    func_291110(p, id, 1, 1);
                    func_2907A0(p, id, 0.0f);
                    func_290690(p, id, 1.0f, D_0047DA74, 0.0f);
                    func_290690(p, id + 1, D_0047D248, D_0047DA74, 0.0f);
                    o = func_3C2420(q->f018, j);
                    if (o != 0 && o->alive() <= 0) {
                        func_290690(p, t + 0xC, 1.0f, D_0047DA74, 0.0f);
                    }
                    func_290690(p, (id & 0xFFFF) + 2, D_0047D288, D_0047DA74, 0.0f);
                    func_290690(p, id + 3, 1.0f, D_0047DA74, 0.0f);
                    id2 = j + 3;
                    func_291110(p, id2, 1, 1);
                    func_2907A0(p, id2, 0.0f);
                    func_290690(p, id2, 1.0f, D_0047DA74, 0.0f);
                    func_290010(p, 2, 1, -1);
                    func_290690(p, 2, 1.0f, D_0047DA74, 0.0f);
                }
                p->f2B0 = 0;
            }
        }
        if (p->f2B0 == 2) {
            if (p->f2B2 == 0) {
                p->f370 = 1;
                q = func_1FEDE0();
                if (q == 0) {
                    return;
                }
                cnt = normal_FieldHudPartyRowCount_4f9c50(p);
                for (s32 j = 0; j < cnt; j++) {
                    t = j * 7;
                    id = t + 6;
                    func_290690(p, id, 0.0f, D_0047DA78, 1.0f);
                    func_290F50(p, id, -0x80, 0x17C, 1, 8.0f);
                    o = func_3C2420(q->f018, j);
                    if (o != 0 && o->alive() <= 0) {
                        m = t + 0xC;
                        func_2910A0(p, id, &x, &y);
                        func_290F60(p, m, x, y);
                        func_290690(p, m, 0.0f, D_0047DA78, 1.0f);
                    }
                    id2 = j + 3;
                    func_290690(p, id2, 0.0f, D_0047DA78, 1.0f);
                    func_290F50(p, id2, -0x80, 0x16F, 1, 8.0f);
                }
                func_290690(p, 0x24, 0.0f, D_0047DA78, 1.0f);
                func_290F50(p, 2, -0x80, 0x178, 1, 8.0f);
                func_290690(p, 2, 0.0f, D_0047DA78, 1.0f);
                normal_FieldHudWidget87Close_4f9c00(p);
                p->f2B2 = p->f2B2 + 1;
            }
            if (p->f2B2 == 1 && func_290770(p, 0x14) <= 0.0f) {
                func_291110(p, 2, 0, 1);
                func_2907A0(p, 1, 1.0f);
                func_291110(p, 1, 0, 1);
                func_291110(p, 3, 0, 1);
                func_291110(p, 4, 0, 1);
                func_291110(p, 5, 0, 1);
                func_291110(p, 0x81, 0, 1);
                func_291110(p, 0x82, 0, 1);
                func_290010(p, 0x83, 0, -1);
                func_291110(p, 0x7F, 0, 1);
                func_290010(p, 0x87, 0, -1);
                func_290010(p, 0x50, 0, -1);
                func_290010(p, 0x80, 0, -1);
                func_290010(p, 0x24, 0, -1);
                p->f4A2 = 0;
                p->f37E = 0;
                p->f49C = 0;
                p->f4A4 = 0;
                p->f49E = 0;
                p->f4A0 = 0;
                p->f3D8 = 0;
                p->f3DA = 0;
                p->f2B0 = 0;
                p->f4A6 = 0;
            }
        }
    }
}
