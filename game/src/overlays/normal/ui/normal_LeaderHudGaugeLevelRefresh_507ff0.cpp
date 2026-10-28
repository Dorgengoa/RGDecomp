/* rgp:protos */
#line 1
/* === SESSION 71 (2026-09-21, SOLO): 195 bad -> MATCH.  Read against the
 * listing (build/wf-normal/s71/c1..c8.py):
 *  - `found = 0;` back to right before the loop (s31's move deck had put it
 *    before func_28F510), `found = 1;` AFTER the func_291110 call (retail puts
 *    it in the `b` delay slot), `u8 found` DECLARED FIRST (fixes the i/found
 *    s1/s2 swap -- decl order of ctx was inert, found's was not).
 *  - `if (b == 0)` / `if (found == 0)` (retail re-masks both u8s); `!a` for a.
 *  - `arr[t]` / `v[t]` without s31's `(u32)` index casts.
 *  - `D_00484574 = 0;` before func_291110(0x13,0,1) (its delay slot);
 *    `i <= 3` for the `$at` loop bound; `s32 pos` (pos narrows twice).
 *  - frame: `s16 arr[4]; s32 v[3];` in THAT order -- v is only 3 long (i=1..3
 *    stores v[i-1]) and is NOT 16-aligned in retail (sp+0x78, arr sp+0x88).
 *    This is s44's "8-byte frame shift".
 *  - `s32 t = (s16)ob->m303();` and `(s16)t` at v[], the `> 0` test and
 *    v[t - 1]: retail re-narrows t after the v loop and shares t*4.
 *  - the arr fill is an 8-byte STRUCT COPY `*(S4 *)arr = *(S4 *)D_00480628;`
 *    -- emitted 0,1,2,3 unrotated; all 24 elementwise orders are rotated.
 * Everything below predates this session. */
/* === SESSION 53 (2026-09-08, SOLO): STILL 195 / 305.  MEASURED NEGATIVE, and
 * it retires s44's own suggested arm.  The sibling normal_LeaderHudGaugeGainFlash_5084c0 CLOSED
 * this session on four levers and ALL FOUR ARE NULLS HERE
 * (build/wf-normal/s53/a_507ff0.py, 8 arms):
 *   - the two-word pad wrapper `struct VW { s32 pad[2]; s32 v[4]; }` that s44
 *     wrote down for the 8-byte v[] shift: a NEW OBJECT (29ca3769) at the SAME
 *     195.  The one-word pad is likewise new (e7f7cf14) and likewise 195.
 *   - `*(AU *)arr = *(AU *)&D_00480628[0];` (the 4-element union cast that
 *     paid 7 words on the sibling): 196, one WORSE.  The 3+1 split is INERT.
 *   - splitting the 88.0f numerator into its own assignment (the sibling's
 *     last four words): a new object at 195, and 196 when crossed with A.
 * WHY IT DOES NOT TRANSFER: this unit's census is NINETY substitutions,
 * dominated by `s1>s3`/`s3>s1` -- a whole-function CALLEE-SAVED PERMUTATION
 * ([[mwcc-callee-saved-creation-order]]), not a local frame or FPR fact.  The
 * frame and fill levers move the object without moving the count because
 * everything downstream is renamed anyway.  ⚠ DO NOT re-run the sibling's
 * levers here; fix the callee-saved colouring FIRST, then re-sweep them
 * ([[two-edit-cross-beats-count-ranking]] -- a recorded null must be re-swept
 * after any coat change).
 */
/* SESSION 44 (SOLO): 195 bad / 305 words.  The new struct-field-offset screen
 * (build/wf-normal/s44/offscan.py) flags `0x6C: retail 0 -> ours 2`,
 * `0x74: 2 -> 0`, `0x70: 0 -> 1`, `0x78: 1 -> 0` -- the local `s32 v[4]` sits
 * at $sp+0x74 in retail and $sp+0x6C in ours, an EIGHT-byte frame shift that
 * displaces every access through it (`sw $2,0x74($3)` / `lw $20,0x78($2)` /
 * `lw $3,0x78($29)` / `lw $4,0x74($3)` against our 0x6C/0x70/0x70/0x6C).
 * spscan.py cannot see the ones reached through `$3 = $sp + i*4`.
 * Same class as normal_LeaderHudGaugeGainFlash_5084c0 (a FOUR-byte shift of its `b[5]`); read
 * that unit's header first, it carries the 17-arm frame probe. */
/* SESSION 31 STAGE 2 (same six decks, re-run from the stage-1 bases).
 * Installed arm `MV_found_L412_T411_SAFE_mov` from the DEFINING-STATEMENT MOVE deck.
 *   before: 304 words, ? bad   after: 305 words, 217 bad   (retail 305 words)
 * Everything below predates THIS install; read older numbers as history.
 * Re-score with build/wf-normal/s31/nscore.py, not dv_osbuild.py. */
/* SESSION 31 (combined six-deck sweep, 31,338 arms over 98 units).
 * Installed arm `I_allu32_idx` from the index-cast deck (mkidx31.py)
 *   before: 300 words, ? bad   after: 304 words, ? bad   (retail 305 words)
 * Every line BELOW this note predates that install -- read its numbers
 * as the state at the time it was written, not as the current score.
 * Re-score with build/wf-normal/s31/nscore.py, not dv_osbuild.py.
 * KEEP OUT OF config/ocunits/normal.txt. */
#include "types.h"
/* normal 0x00507FF0 -- the battle-result / gauge HUD builder.  1232 bytes,
 * 308 instructions.  Written fresh in s31 (lane a6).
 *
 * jalr $25 x5 => C++ virtual dispatch, vptr at offset 0, slot = 8 + 4*N.
 * Slots used: 0x4C0 (idx 302), 0x4C4 (303), 0x4CC (305), 0x4DC (309).
 *
 * Stack model: s32 v[4] and s16 arr[4] adjacent at the top of the frame.
 * The store loop writes v[i-1] for i=1..3 and the reads are v[t] / v[t-1],
 * arr[t] / arr[t-1] -- the -1 folds into the load displacement (0x74 vs 0x78,
 * 0x86 vs 0x88), which is what retail shows.
 */
struct Obj {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 m302() { return VCM0(s32, 0x4C0); }
    s32 m303() { return VCM0(s32, 0x4C4); }
    
    s32 m305() { return VCM0(s32, 0x4CC); }
    
    
    
    s32 m309() { return VCM0(s32, 0x4DC); }
};

typedef struct C2 { u8 pad000[8]; void *f008; } C2;
typedef struct C1 { u8 pad000[0x54]; C2 *f054; } C1;
typedef struct Ctx {
    u8    pad000[8];
    C1   *f008;
    u8    pad00C[4];
    void *f010;
    u8    pad014[4];
    void *f018;
    u8    pad01C[4];
    void *f020;
} Ctx;

typedef struct Box { u8 pad000[4]; const void *f004; u8 pad008[4]; u32 f00C; } Box;

extern "C" s32 normal_D_00526498[];

extern "C" void *D_00484564;          /* gp - 0xC0C  */
extern "C" s32   D_00484574;          /* gp - 0xBFC  */
extern "C" s16   D_00480628[4];       /* gp - 0x4B48 */

extern "C" Ctx  *GetGameData_1fede0(void);
extern "C" Obj  *PartyGetLeaderChara_3c2820(void *a);
extern "C" Obj  *PartyGetSlotChara_3c2fb0(void *a, s32 i);
extern "C" s32   PartyCountMembers_3c2010(void *a, s32 b, s32 c);
extern "C" s32   PartyCountReserve_3c1c20(void *a, s32 b, s32 c);
extern "C" u8    StateFlagTest_3ccd70(void *a, s32 b);
extern "C" s32   CharaSysStateUnitFlag7EBit3Related_3a38e0(void *a);
extern "C" s32   BtlElemParamGetGaugeThreshold_3f9480(void *a, s32 i);
extern "C" void  UiSetWidgetColor_2905b0(void *w, u16 id, f32 a, f32 b, f32 c, f32 d);
extern "C" void  UiSetTextString_28f510(void *w, u16 id, s32 a, s32 b);
extern "C" void  UiSetWidgetsVisibleById_291110(void *w, u16 id, s32 a, s32 b);
extern "C" Box  *UiGetWidgetText_28f620(void *w, u16 id, s32 a);
extern "C" void  UiSetSpriteV_28f8f0(void *w, u16 id, s16 a, s32 b);
extern "C" void  UiSetSpriteU_28f930(void *w, u16 id, s16 a, s32 b);
extern "C" void  UiSetSpriteW_28fbf0(void *w, u16 id, s16 a, s32 b);
extern "C" void  UiSetSpriteUvW_28f850(void *w, u16 id, s16 a, s32 b);
extern "C" s32   normal_LeaderHudGaugeLevelPulse_508820(void);
extern "C" s32   normal_LeaderHudGaugeGainFlash_5084c0(void);

typedef struct S4 { s16 a[4]; } S4;
extern "C" s32 normal_LeaderHudGaugeLevelRefresh_507ff0(void);

s32 normal_LeaderHudGaugeLevelRefresh_507ff0(void)
{
    u8 found;
    Ctx *ctx;
    Obj *ob;
    Obj *e;
    Box *bx;
    void *p;
    s16 arr[4];
    s32 v[3];
    s32 i;
    s32 cur;
    s32 rank;
    s32 hi;
    s32 lo;
    s16 n;
    s32 t;
    s32 pos;
    u8 a;
    u8 b;

    ctx = GetGameData_1fede0();
    if (ctx == 0) {
        return 0;
    }
    ob = PartyGetLeaderChara_3c2820(ctx->f018);
    if (ob == 0) {
        return 0;
    }
    a = ob->m302();
    b = StateFlagTest_3ccd70(ctx->f010, 0x3ED);
    UiSetWidgetColor_2905b0(D_00484564, 0x10, 1.0f, 1.0f, 1.0f, -1.0f);
    UiSetTextString_28f510(D_00484564, 0x10, 0, 0);
    if (b == 0) {
        UiSetWidgetsVisibleById_291110(D_00484564, 0x10, 0, 1);
        return 0;
    }
    p = ctx->f018;
    n = PartyCountMembers_3c2010(p, 1, 1) + PartyCountReserve_3c1c20(p, 1, 1);
    found = 0;
    for (i = 0; i < n; i++) {
        e = PartyGetSlotChara_3c2fb0(ctx->f018, i);
        if (e != 0) {
            if (e->m302()) {
                UiSetWidgetsVisibleById_291110(D_00484564, 0x10, 1, 1);
                found = 1;
                break;
            }
        }
    }
    if (found == 0) {
        UiSetWidgetsVisibleById_291110(D_00484564, 0x10, 0, 1);
        return 0;
    }
    if (!a || CharaSysStateUnitFlag7EBit3Related_3a38e0(ctx->f020) == 0) {
        bx = UiGetWidgetText_28f620(D_00484564, 0x10, 0);
        bx->f004 = normal_D_00526498;
        bx->f00C = 0xFF181840;
        UiSetWidgetColor_2905b0(D_00484564, 0x10, 0.5f, 0.5f, 0.5f, -1.0f);
    }
    t = (s16)ob->m303();
    *(S4 *)arr = *(S4 *)D_00480628;
    UiSetSpriteV_28f8f0(D_00484564, 0x12, arr[t], 0);
    cur = ob->m305();
    rank = ob->m309();
    for (i = 1; i <= 3; i++) {
        v[i - 1] = BtlElemParamGetGaugeThreshold_3f9480(ctx->f008->f054->f008, i);
    }
    hi = v[(s16)t];
    if ((s16)t > 0) {
        UiSetWidgetsVisibleById_291110(D_00484564, 0x13, 1, 1);
        UiSetSpriteU_28f930(D_00484564, 0x13, rank * 20, 0);
        UiSetSpriteW_28fbf0(D_00484564, 0x11, 0x58, 0);
        UiSetSpriteUvW_28f850(D_00484564, 0x11, 0x58, 0);
        UiSetSpriteV_28f8f0(D_00484564, 0x11, arr[t - 1], 0);
    } else {
        D_00484574 = 0;
        UiSetWidgetsVisibleById_291110(D_00484564, 0x13, 0, 1);
        UiSetSpriteW_28fbf0(D_00484564, 0x11, 0, 0);
        UiSetSpriteUvW_28f850(D_00484564, 0x11, 0, 0);
    }
    if (cur == 0 || cur == v[0] || cur == v[1] || cur == v[2]) {
        UiSetSpriteW_28fbf0(D_00484564, 0x12, 0, 0);
        UiSetSpriteUvW_28f850(D_00484564, 0x12, 0, 0);
    } else {
        if (t == 0) {
            pos = (s16)(88.0f / (f32)v[0] * (f32)cur);
        } else {
            lo = v[(s16)t - 1];
            pos = (s16)(88.0f / (f32)(hi - lo) * (f32)(cur - lo));
        }
        UiSetSpriteW_28fbf0(D_00484564, 0x12, pos, 0);
        UiSetSpriteUvW_28f850(D_00484564, 0x12, 0x58, 0);
    }
    normal_LeaderHudGaugeLevelPulse_508820();
    normal_LeaderHudGaugeGainFlash_5084c0();
    return 1;
}
