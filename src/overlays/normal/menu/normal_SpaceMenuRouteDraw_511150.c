/* === SESSION 73 (2026-09-21, SOLO): 15 bad -> MATCH, MERGED.  NORMAL.BIN
 * relinked BYTE-IDENTICAL (250,240 B) with an armed 1-byte control
 * (`func_1418C0(h, 0x32D -> 0x32C, ...)` = 1 differing byte at vram
 * 0x00511324).  Sweeps build/wf-normal/s73/c1.py, c2.py, c3.py.
 *
 * THREE EDITS, AND THE FIRST IS A TEXTBOOK TWO-EDIT CROSS
 * ([[levers.d/two-edit-cross-beats-count-ranking]], [[levers.d/mwcc-named-local-dead-assignment]]):
 *  1. ★ `pa` DECLARED FIRST + the `a == e` BLOCK FIRST + `#pragma
 *     opt_arithtransformation off` -> 15 -> 7.  EVERY HALF IS WORSE ALONE:
 *     the source change alone is 21, the pragma alone is 17.  s71's header
 *     recorded decl order and block order as MEASURED NULLS -- they were, with
 *     every optimiser pass ON.  This is exactly s72's warning that every
 *     "naming / ordering is INERT" verdict in this corpus is a CROSS HALF.
 *     Found by running the 68-name opt_* table (9 live cells, ARMED) and then
 *     crossing all 9 live columns with the retired 4-cell source deck.
 *  2. `dx` BEFORE `dy`, and `sqrtf(dx * dx + dy * dy)` -> 7 -> 3.  The residue
 *     at 7 was FOUR words and ONE fact: retail puts dy in $f2 and dx in $f3,
 *     ours the other way round; the sqrt's operand order picks the temps.
 *     ⚠ the `ux`/`uy` order is the WRONG axis (swapping it is +6).
 *  3. ★ 3.1415927f AND 0.18f AS gp-POOL EXTERNS, NOT LITERALS -> 3 -> MATCH.
 *     `extern f32 D_0047D1FC;` (gp - 0x7F74) and `extern f32 D_0047D4CC;`
 *     (gp - 0x7CA4).  All three residual words were `.lit4`: we emitted a
 *     LOCAL literal (`lwc1 $f0,0x0(<our .lit4>)`) where retail loads from the
 *     shared MAIN pool (`lwc1 $f0,-0x7F74(gp)`).  The three sites are
 *     INDEPENDENT -- each one flipped is -1 -- so a partial install still pays.
 *     ⚠⚠ THIS INVERTS THIS UNIT'S OWN s68 NOTE, which said these two pool
 *     entries "are written as literals".  [[levers.d/mwcc-float-literal-pool]]
 *     is a TWO-WAY lever: read the `lwc1` offset off the object and let it
 *     decide.  A gp offset means the EXTERN; offset 0 means the LITERAL.
 * Everything below predates this session. */
/* === SESSION 71 (2026-09-21, SOLO): 224 bad -> 15, EXACT 280 words.  NOT
 * merged.  Sweeps build/wf-normal/s71/e1..e11.py.  What landed:
 *  - ax/ay/bx/by are two STRUCT locals `V2 pb; V2 pa;` -- scalarised fields
 *    of an aggregate get HOME SLOTS and the four prologue lwc1 loads that s68
 *    could not buy (s68's "frame-size fact").  Prologue now word-identical.
 *  - s31's `(s32)i` index cast removed (it was in the CODE and the header).
 *  - `pos` is an 8x4-byte AGGREGATE copy `*(P8 *)pos = *(const P8 *)
 *    D_00525C60;` -- mwcc's own 2-aligned copy loop, not the do-while.
 *  - second half rewritten in retail order: n right after the sqrt; the twelve
 *    func_13E* calls with NOTHING interleaved (s31 had moved `uy = 24*uy` and
 *    `n` in among them); both `24.0f *` scalings after the phase update.
 *  - `py = (s16)py; px = (s16)px;` right before the first func_13F110 -- the
 *    REDUNDANT SELF-CAST retail re-narrows with (every other spelling of the
 *    second narrow -- a new s16 variable, an inlined s16-parameter helper,
 *    Pt struct, s16/u16 prototypes -- is folded or wrong).
 * WHAT IS LEFT (15 words) IS ONE CLASS: the FPR PAIRS of the two endpoints
 * are swapped.  Retail: pb={$f20,$f21}@0xC0, pa={$f22,$f23}@0xC8, and the a==e
 * block comes FIRST in the map loop (it tests $s0 = a).  Every arm gives pa
 * {$f20,$f21} whatever the declaration order, block order, dx/dy order,
 * ux/uy order, decl position of the derived floats, or aggregate form
 * (V2 p[2], f32 q[4], f32 qa[2]/qb[2]) -- measured nulls.  With the block
 * order fixed (a first, pa declared first) the residue is EXACTLY that swap
 * (21 bad, every other word equal).  Next: the pair assignment of
 * scalarised aggregate fields -- see [[levers.d/mwcc-allocator-decompiled]].
 */
/* SESSION 31 STAGE 2 (same six decks, re-run from the stage-1 bases).
 * Installed arm `MV_ux_L150_T145_DEREF_mov` from the DEFINING-STATEMENT MOVE deck.
 *   before: 277 words, ? bad   after: 280 words, 227 bad   (retail 280 words)
 * Everything below predates THIS install; read older numbers as history.
 * Re-score with build/wf-normal/s31/nscore.py, not dv_osbuild.py. */
/* SESSION 31 (combined six-deck sweep, 31,338 arms over 98 units).
 * Installed arm `I_s32_L116_3_idx` from the index-cast deck (mkidx31.py)
 *   before: 272 words, ? bad   after: 277 words, ? bad   (retail 280 words)
 * Every line BELOW this note predates that install -- read its numbers
 * as the state at the time it was written, not as the current score.
 * Re-score with build/wf-normal/s31/nscore.py, not dv_osbuild.py.
 * KEEP OUT OF config/ocunits/normal.txt. */
/* === SESSION 68 (2026-09-20, SOLO): READ AGAINST THE LISTING FOR THE FIRST
 * TIME.  Still 280 w / 224 bad and NOT INSTALLED -- but the residue is now
 * characterised and the whole first third is understood.  Sweeps:
 * build/wf-normal/s68/f1.py, f2.py, f3.py.
 *
 * ★★ THE ROOT CAUSE IS A FRAME-SIZE FACT, AND THE s31 INDEX CAST IS HIDING IT.
 * Retail's frame is 0xD0 with HOME SLOTS for the four uninitialised floats at
 * 0xC0(bx) 0xC4(by) 0xC8(ax) 0xCC(ay), and it LOADS ALL FOUR IN THE PROLOGUE:
 *     swc1 $f20,0x0($29) / lwc1 $f21,0xC4 / lwc1 $f22,0xC8 / lwc1 $f23,0xCC
 *     jal func_1FEDE0 / lwc1 $f20,0xC0        <- four words we never emit
 * Our frame is 0xC0 and mwcc gives the four the SAME registers ($f20-$f23,
 * confirmed word for word) but no home and no entry load.  That is -4 words.
 * The `D_00525AF0[(s32)i].f02` index cast (an s31 mkidx31.py install) is
 * worth +5: it breaks the CSE of `&D_00525AF0[i]` so the `b == e` arm
 * re-derives the map address (`sll/addu/lh` twice) where retail reuses $6.
 * The two defects CANCEL in the length column -- remove the cast alone and
 * the unit is 0x44c vs 0x460, FIVE WORDS SHORT.  This is exactly
 * [[levers.d/uninit-local-draft-screen]]'s "the bug is PAYING for a second
 * defect" trap, with the halves in the unusual order.
 * ⚠ MEASURED NULL on the home slots (all still 0x44c with the cast removed):
 * self-initialising declarations (`f32 ay = ay;`), self-assignment statements
 * at the top of the guarded block, and an address-taken dummy `pf = &ay;`.
 * `volatile` on all four is +4 words the wrong way (0x470).  The next arm has
 * to find whatever makes mwcc give an uninitialised local a HOME rather than
 * an undefined register -- see [[levers.d/mwcc-named-home-vs-inline-spill]]
 * and [[levers.d/mwcc-dominating-def-colouring]].
 *
 * OTHER FACTS READ OUT OF RETAIL (not yet installed, all measured on the
 * un-fixed coat where they read +1 to +3 -- RE-MEASURE THEM AFTER THE FRAME
 * FIX LANDS, per [[levers.d/normal-session64-levers]]'s rule):
 *  - `n = (s16)(len / 24.0f);` is computed IMMEDIATELY AFTER the sqrt and
 *    BEFORE ux/uy (retail 0x005112C8-0x005112E4), not down among the
 *    func_13Exxx calls.  `n` lives in $16, a GPR.
 *  - `dy = by - ay;` is written BEFORE `dx = bx - ax;` -- retail puts dy in
 *    $f2 and dx in $f3, and `mula.s $f2,$f2` squares dy first.
 *  - ux and uy REUSE by's and bx's registers: `div.s $f21,$f3,$f1` (ux) and
 *    `div.s $f20,$f2,$f1` (uy).  Ours matches.
 *  - retail's map walk keeps `&D_00525AF0[i]` in $6 across BOTH arms and
 *    re-derives only `i*8` in the `bnel` delay slot at the loop bottom. */
#include "types.h"
#pragma opt_arithtransformation off
/* normal 0x00511150 -- the constellation line renderer.  Copies the 8 anchor
 * points out of D_00525C60 into a stack array, walks the 9-entry D_00525AF0
 * map to find the two endpoints that match the current and the previous slot,
 * then draws `len / 24` segments along the unit vector between them, each one
 * faded by a sine of the running phase D_004846BC.
 *
 * ax/ay/bx/by are READ UNINITIALISED (the caller passes nothing -- see
 * normal_SpaceMenuDraw_511100 -- so the four `lwc1 $fNN, 0xC0..0xCC($sp)` at entry are
 * an uninitialised local's home slot, not incoming arguments).  Their homes
 * and their FPRs agree on ONE declaration order: locals are allocated
 * DOWNWARD from the top of the frame and callee-saved FPRs are handed out
 * HIGHEST FIRST, so ay(0xCC/$f23), ax(0xC8/$f22), by(0xC4/$f21), bx(0xC0/$f20)
 * must be declared in exactly that order, with pos[8] (0xA0) after them.
 *
 * `c1 0x10044` is sqrt.s -- an mwcc INTRINSIC, no call.  mula.s takes the
 * FIRST product, so dy is squared first.
 * 0.18f (0x0047D4CC) and 3.1415927f (0x0047D1FC) are MAIN `.lit4` pool
 * entries and are written as literals; 0.05f lives at 0x0047D814, above the
 * pool, and stays an extern. */

extern f32 sqrtf(f32 x);

typedef struct Pt   { s16 x; s16 y; } Pt;
typedef struct P8 { Pt p[8]; } P8;
typedef struct V2   { f32 x; f32 y; } V2;
typedef struct Ent2 { u8 pad000[0x1A4]; u8 f1A4; } Ent2;
typedef struct Ent  { u8 pad000[0x18]; Ent2 *f18; } Ent;
typedef struct Ctx  { u8 pad000[0x14]; u8 f14; } Ctx;
typedef struct Map  { s16 f00; s16 f02; s16 f04; s16 f06; } Map;

extern const Pt  D_00525C60[];
extern const Map D_00525AF0[];
extern const u8  D_00526580[];

extern Ctx  *D_004846B8;          /* gp - 0xAB8 */
extern f32   D_004846BC;          /* gp - 0xAB4 */
extern f32   D_0047D814;          /* gp - 0x795C, 0.05f */
extern f32   D_0047D1FC;          /* gp - 0x7F74, 3.1415927f */
extern f32   D_0047D4CC;          /* gp - 0x7CA4, 0.18f */

extern Ent  *func_1FEDE0(void);
extern void *func_15DE80(void);
extern void *func_15DE40(void);
extern void  func_1418C0(void *h, s32 id, f32 t);
extern void *func_159FB0(void *h, const u8 *name, s32 id);
extern void *func_141B00(void *h);
extern void  func_141A20(void *h);
extern void  func_13E2F0(void *o, s32 v);
extern void  func_13E3B0(void *o, s32 v);
extern void  func_13E3D0(void *o, s32 v);
extern void  func_13E3E0(void *o, s32 v);
extern void  func_13E400(void *o, s32 v);
extern void  func_13E430(void *o, s32 v);
extern void  func_13E460(void *o, s32 v);
extern void  func_13E4D0(void *o, s32 v);
extern void  func_13E4F0(void *o, s32 v);
extern void  func_13E500(void *o, s32 v);
extern void  func_13F730(void *o, s32 v);
extern void  func_13EC00(void *o, void *t);
extern void  func_13EE40(void *o, s32 r, s32 g, s32 b, s32 a);
extern void  func_13ED90(void *o, s32 u, s32 v);
extern void  func_13F110(void *o, s32 x, s32 y, s32 z);
extern void  func_13F5B0(void *o);
extern f32   func_128FD0(f32 t);
extern s32   normal_SpaceMenuGetTransitFromAreaId_514800(void);
extern s32   normal_SpaceMenuGetPrevAreaId_514780(void);
extern s32   normal_SpaceMenuGetTransitToAreaId_5147c0(void);
extern f32   normal_SpaceMenuGetFadeAlpha_511780(Ctx *c);
extern s32   normal_SpaceMenuTexelToUv_5115b0(s32 v);

s32 normal_SpaceMenuRouteDraw_511150(void)
{
    V2    pa;
    V2    pb;
    Pt    pos[8];
    s32   k;
    const Pt *sp2;
    Pt   *dp;
    s32   i;
    s32   e;
    s32   a;
    s32   b;
    s16   n;
    f32   dx;
    f32   dy;
    f32   len;
    f32   ux;
    f32   uy;
    f32   t;
    f32   s;
    void *h;
    void *tex;
    void *obj;
    s16   px;
    s16   py;

    if ((func_1FEDE0()->f18->f1A4 & 1) && D_004846B8->f14 >= 2) {
        *(P8 *)pos = *(const P8 *)D_00525C60;
        a = normal_SpaceMenuGetTransitFromAreaId_514800();
        if (a == 9) {
            a = normal_SpaceMenuGetPrevAreaId_514780();
        }
        b = normal_SpaceMenuGetTransitToAreaId_5147c0();
        for (i = 0; i < 9; i++) {
            e = D_00525AF0[i].f00;
            if (a == e) {
                pa.x = (f32)pos[D_00525AF0[i].f02].x;
                pa.y = (f32)pos[D_00525AF0[i].f02].y;
            }
            if (b == e) {
                pb.x = (f32)pos[D_00525AF0[i].f02].x;
                pb.y = (f32)pos[D_00525AF0[i].f02].y;
            }
        }
        dx = pb.x - pa.x;
        dy = pb.y - pa.y;
        len = sqrtf(dx * dx + dy * dy);
        n = (s16)(len / 24.0f);
        ux = dx / len;
        uy = dy / len;
        h = func_15DE80();
        tex = func_15DE40();
        func_1418C0(h, 0x32D, 1.0f);
        tex = func_159FB0(tex, D_00526580, 0x32D);
        obj = func_141B00(h);
        func_13E2F0(obj, 0);
        func_13E3E0(obj, 1);
        func_13E500(obj, 1);
        func_13E4F0(obj, 1);
        func_13E4D0(obj, 1);
        func_13E3D0(obj, 1);
        func_13E430(obj, 0);
        func_13E460(obj, 0);
        func_13E3B0(obj, 0);
        func_13E400(obj, 1);
        func_13F730(obj, 6);
        func_13EC00(obj, tex);
        t = D_004846BC + D_0047D814;
        D_004846BC = t;
        if (!(t < D_0047D1FC)) {
            D_004846BC = 0.0f;
        }
        ux = 24.0f * ux;
        uy = 24.0f * uy;
        for (i = 0; i < n; i++) {
            t = D_004846BC - D_0047D4CC * (f32)i;
            if (t <= 0.0f) {
                t = D_0047D1FC;
            }
            px = (s16)(pa.x + ux * (f32)(i + 1));
            py = (s16)(pa.y + uy * (f32)(i + 1));
            s = 80.0f * func_128FD0(t);
            func_13EE40(obj, 0x80, 0x80, 0x80,
                        (s32)(s * normal_SpaceMenuGetFadeAlpha_511780(D_004846B8)));
            func_13ED90(obj, normal_SpaceMenuTexelToUv_5115b0(0x4C),
                        normal_SpaceMenuTexelToUv_5115b0(0x46));
            py = (s16)py;
            px = (s16)px;
            func_13F110(obj, px + 8, py + 8, 0);
            func_13ED90(obj, normal_SpaceMenuTexelToUv_5115b0(0x96),
                        normal_SpaceMenuTexelToUv_5115b0(0x9C));
            func_13F110(obj, px + 0x10, py + 0x10, 0);
        }
        func_13F5B0(obj);
        func_141A20(h);
    }
    return 0;
}
