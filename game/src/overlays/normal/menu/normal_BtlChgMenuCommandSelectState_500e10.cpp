/* rgp:protos */
#line 1
/* SESSION 39 (n39h, SOLO): 7 bad -> MATCH, 260/260 words, byte-identical.
 * THE FIX IS ONE WORD IN A PROTOTYPE:
 *     extern void normal_BtlChgPageSetCommand_505da0(Ctx *p, s32 k);   -- was s16
 * The three call sites' delay-slot residue described below was a CALLEE
 * PARAMETER WIDTH defect ([[pk-callee-param-width]]), not a scheduler
 * preference.  With the parameter declared s16, mwcc treats `q->f12` as
 * already-narrow and schedules the `lh` as the cheap, deferrable operand; with
 * it declared s32 the argument is a widening conversion, which reorders it
 * against the `D_00484454` load and flips ALL THREE sites at once -- exactly
 * the "single upstream fix" this header predicted, just not on the axis it
 * predicted it on.  (`int` is identical; `u16` reads 6 bad; `s8` is +1 word.)
 * ⚠ The merged definition normal_BtlChgPageSetCommand_505da0.c spells the parameter `s8`,
 * and taking that literally is WRONG HERE -- it costs a word.  The merged
 * definition is an oracle for ARITY, not for the caller-side WIDTH that makes
 * the argument's conversion visible to the scheduler.
 * Found by build/wf-normal/s39/livearg.py, which flagged this call as one
 * where retail keeps more argument registers live than our C declares. */
/* Session s35 (lane n35b): LENGTH IS EXACT (260 words / 0x410); down to 7 bad
 * words (from an old parked state of 142/260, and from 14 at the start of
 * this session).  The stale "fifth callee-saved register" 5-reg/142-word
 * account below (lane nb, session 19) no longer applies -- that was fixed by
 * work already folded into this file (the `Ctx *c` hoist, splitting `j` from
 * `n`, the early `if (t == 0) return 0;` return, and this session's k/j
 * assignment-order swap).  Do not undo any of that.
 *
 * REMAINING 7 BAD WORDS, all at the three call sites of
 * `normal_BtlChgPageSetCommand_505da0(D_00484454, q->f12)` (k==1 arm, k==3 arm, and the
 * `(s16)j == 0` else-arm): retail and ours pick OPPOSITE arguments to defer
 * into the `jal`'s branch-delay slot vs. compute earlier.
 *   - k==1 arm (0x500FBC/FCC/FD4, an OR-merge into a shared `beql` target):
 *     retail duplicates the `q->f12` load onto BOTH incoming paths and defers
 *     `D_00484454`'s load into the jal delay slot; ours does the reverse
 *     (duplicates the global on both paths, defers q->f12).
 *   - k==3 arm (0x50100C/1014) and the else-arm (0x501124/112C): retail loads
 *     `D_00484454` right before the jal and defers `q->f12` into the delay
 *     slot; ours does the reverse (q->f12 before, global deferred).
 * Ours is already self-consistent (site A is the mirror image of B/C, same as
 * retail's own three sites are mirror images of each other) -- so a SINGLE
 * upstream fix that flips this delay-slot preference should fix all three at
 * once; this is not three independent bugs.
 * CONFIRMED NEGATIVE this session: any local reordering AT these three call
 * sites (already established before this session -- inert or +3 words);
 * caching/aliasing D_00484454 into a local pointer near the sites (+3,
 * confirmed before this session); moving `i = func_3C3120(...)` before the
 * `o == 0` return check (shortens the object, wrong length); hoisting
 * `Ctx *c = D_00484454;` out of the `if (o->count() > 0)` block to the top of
 * `if (r == 1)` (regrows the object by 2 words -- the old 5th-register
 * problem resurfaces); swapping `r`/`q` computation order (7 -> 22 bad);
 * `#pragma optimization_level 2` (badly regresses length); `3`/`4` (inert,
 * same as default -O4); swapping the `i`/`n` local declaration order (inert).
 * NEXT ARM (unmeasured): a fix in the k==1 arm's OR-chain
 * `(func_3CCD70(t->f10, 0xB6) == 0 || o->f0C != 0)` structure itself (not the
 * call site) that changes what mwcc has available to duplicate across the
 * `beql` merge; or search for what upstream reference to q->f12 or
 * D_00484454 (earlier than these three arms) most directly seeds the
 * scheduler's "prefer to duplicate/defer this one" choice -- candidates
 * tried so far (c's declaration point, r/q order, i's position) were all
 * negative, so the true lever is still open. */
#include "types.h"
/* normal 0x00500E10 -- the field menu's confirm/cancel handler for the member
 * list.  `b != 0` re-seeds the cursor from the per-member column table at
 * gp-0xCA8; then the 0x4B2570 pad state is read and, on CONFIRM (1), the
 * highlighted member's sub-command (q->f12) is dispatched: 0 = "use", 2 =
 * "order", 1 = "item" gated on three refusals, 3 = "swap" which re-opens the
 * whole page.  CANCEL (2) restores the saved column and closes.
 *
 * THREE `lw $25,0($19) / lw $25,K($25) / jalr $25` sites -> C++ virtual,
 * vptr 0, slots (0xF0-8)/4 = 58, (0x274-8)/4 = 155, (0x368-8)/4 = 216.
 * `$4` is never read -- the f(void *, s32) state-handler family.
 * `dsll32/dsra32 ..,16` off the plain `lh` is an s32 local plus an explicit
 * `(s16)` cast, CSEd across the three compares; the `k == 0` test runs on the
 * un-cast value, so it is the OUTER guard and its body is the `else`. */

struct Ent {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 count() { return VCM0(s32, 0xF0); }   /* slot 58 -> vtable +0xF0 */
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 canUse(s32 k) { return VCM(s32, (void *, s32), 0x274, k); }   /* slot 155 -> vtable +0x274 */
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 locked() { return VCM0(s32, 0x368); }   /* slot 216 -> vtable +0x368 */
    u8   pad04[0x0C - 4];
    s32  f0C;
};

typedef struct Ctx  { u8 pad000[0x43C]; s16 f43C; u8 pad43E[0x44E - 0x43E];
                      s16 f44E; } Ctx;
typedef struct Top  { u8 pad00[0x10]; void *f10; u8 pad14[4]; s32 f18; } Top;
typedef struct Cur  { u8 pad00[0x12]; s16 f12; u8 pad14[2]; s16 f16; } Cur;

extern "C" u8 normal_D_00527020[];
extern "C" u8 D_004B2570[];

extern "C" Ctx  *D_00484454;          /* gp - 0xD1C */
extern "C" void *D_00484498;          /* gp - 0xCD8 */
extern "C" void *D_004844A0;          /* gp - 0xCD0 */
extern "C" void *D_004844A4;          /* gp - 0xCCC */
extern "C" u8    D_004844C8[8];       /* gp - 0xCA8 ; size is a relocation control */
extern "C" void *D_0048456C;          /* gp - 0xC04 */

extern "C" {

extern s32   PadIsTriggered_1839f0(const u8 *p, s32 mask);
extern void  SoundPlayScaledVolume_1b9520(void *a, s32 b, s32 c, f32 x);
extern s32   CharaModeIsNormalByIdMaybe_1fb1f0(s32 a);
extern Top  *GetGameData_1fede0(void);
extern void *SceneSoundGetSlot0HandleCur_207df0(void);
extern s32   MenuGridCursorInput_28e170(void *w, const u8 *p, s32 c, s32 d);
extern Cur  *UiEntryListFindByTag_28ea40(void *w, s32 id);
extern void  UiEntryListSelectByTag_28ea90(void *w, s32 id, s32 a);
extern Cur  *UiEntryListGetCurrentData_28ec60(void *w);
extern void  StateMachineSetState_28ede0(void *w, s32 id, s32 a);
extern s32   CharaGetControlStateMaybe_2f5320(s32 a);
extern s32   CharaCountAbilitiesFilteredMaybe_3add30(Ent *o, s32 b, s32 c, s32 d);
extern void  PartySetLeader_3c1600(s32 a, s32 b, s32 c);
extern Ent  *PartyGetSlotChara_3c2fb0(s32 a, s32 k);
extern s32   PartyGetSlotId_3c3120(s32 a, s32 k);
extern s32   StateFlagTest_3ccd70(void *h, s32 id);
extern void  normal_FieldHudPanelSelectHide_4f4eb0(const u8 *w, s32 k);
extern void normal_FieldHudLeaderChangedNop_4f50e0(const u8 *);
extern void  normal_FieldHudPanelFlashStart_4f52f0(const u8 *w, s32 k);
extern u8 normal_BtlChgMenuTryLeaderChange_502250(void);
extern void  normal_BtlChgMenuCommandCursorPlace_503580(s32 k);
extern void  normal_LeaderHudBannerReshow_503720(void);
extern void  normal_BtlChgPageSetCommand_505da0(Ctx *p, s32 k);
extern s32   normal_BtlChgPageGetMember_505f90(Ctx *p);
extern void  normal_LeaderHudSetWeaponGaugeShown_5069c0(void *p, f32 x);
extern void  normal_LeaderHudSetPanelMode_506b10(void *p, s32 k);

}

extern "C" s32 normal_BtlChgMenuCommandSelectState_500e10(void *a, s32 b)
{
    Top *t;
    Ent *o;
    Ent *e;
    Cur *q;
    Cur *w;
    s32  r;
    s32  k;
    s32  j;
    s32  n;
    s32  i;

    t = GetGameData_1fede0();
    if (t == 0) {
        return 0;
    }
    if (b != 0) {
        D_00484454->f43C = 0;
        w = UiEntryListFindByTag_28ea40(D_004844A0, 0x55F2);
        w->f16 = D_004844C8[PartyGetSlotId_3c3120(t->f18, normal_BtlChgPageGetMember_505f90(D_00484454))];
    }
    UiEntryListSelectByTag_28ea90(D_004844A0, 0x55F2, 0);
    r = MenuGridCursorInput_28e170(D_004844A0, D_004B2570, 4, 0);
    q = UiEntryListGetCurrentData_28ec60(D_004844A0);
    normal_BtlChgMenuCommandCursorPlace_503580(q->f12);
    if (r == 1) {
        o = PartyGetSlotChara_3c2fb0(t->f18, normal_BtlChgPageGetMember_505f90(D_00484454));
        if (o == 0) {
            return 0;
        }
        i = PartyGetSlotId_3c3120(t->f18, normal_BtlChgPageGetMember_505f90(D_00484454));
        D_004844C8[i] = q->f12;
        if (o->count() > 0) {
            Ctx *c = D_00484454;
            j = c->f44E;
            k = q->f12;
            if (k != 0) {
                if ((s16)k == 2) {
                    normal_BtlChgPageSetCommand_505da0(c, (s16)k);
                    StateMachineSetState_28ede0(D_00484498, 0x55F8, 0);
                } else if ((s16)k == 1) {
                    if (o->locked() == 0 && CharaGetControlStateMaybe_2f5320(o->f0C) == 0 &&
                        (StateFlagTest_3ccd70(t->f10, 0xB6) == 0 || o->f0C != 0)) {
                        normal_BtlChgPageSetCommand_505da0(D_00484454, q->f12);
                        StateMachineSetState_28ede0(D_00484498, 0x55F8, 0);
                    }
                } else if ((s16)k == 3) {
                    if (normal_BtlChgMenuTryLeaderChange_502250() != 0) {
                        normal_BtlChgPageSetCommand_505da0(D_00484454, q->f12);
                        SoundPlayScaledVolume_1b9520(D_004844A4, 4, 0, 1.0f);
                        normal_FieldHudPanelSelectHide_4f4eb0(normal_D_00527020, -1);
                        n = normal_BtlChgPageGetMember_505f90(D_00484454);
                        e = PartyGetSlotChara_3c2fb0(t->f18, n);
                        if (e == 0) {
                            return 3;
                        }
                        PartySetLeader_3c1600(t->f18, e->f0C, 0);
                        normal_FieldHudPanelFlashStart_4f52f0(normal_D_00527020, n);
                        normal_FieldHudLeaderChangedNop_4f50e0(normal_D_00527020);
                        normal_LeaderHudSetWeaponGaugeShown_5069c0(D_0048456C, 0.0f);
                        normal_LeaderHudBannerReshow_503720();
                        normal_LeaderHudSetPanelMode_506b10(D_0048456C, 1);
                        StateMachineSetState_28ede0(D_00484498, 0x55F8, 0);
                    }
                }
            } else {
                if ((s16)j == 0 && o->canUse(-1) != 0 &&
                    CharaCountAbilitiesFilteredMaybe_3add30(o, 0, -1, 0) != 0 &&
                    CharaModeIsNormalByIdMaybe_1fb1f0(o->f0C) != 0) {
                    normal_BtlChgPageSetCommand_505da0(D_00484454, q->f12);
                    StateMachineSetState_28ede0(D_00484498, 0x55F8, 0);
                }
            }
        }
    }
    if (r == 2) {
        if (D_00484454->f44E == 0) {
            i = PartyGetSlotId_3c3120(t->f18, normal_BtlChgPageGetMember_505f90(D_00484454));
            D_004844C8[i] = q->f12;
            StateMachineSetState_28ede0(D_00484498, 0x55F8, 0);
            normal_BtlChgPageSetCommand_505da0(D_00484454, -1);
            normal_FieldHudPanelSelectHide_4f4eb0(normal_D_00527020, -1);
        }
    }
    if (PadIsTriggered_1839f0(D_004B2570, 0x80) != 0) {
        SoundPlayScaledVolume_1b9520(SceneSoundGetSlot0HandleCur_207df0(), 5, 0, 1.0f);
        StateMachineSetState_28ede0(D_00484498, 0x55F8, 0);
        normal_BtlChgPageSetCommand_505da0(D_00484454, 0x64);
    }
    return 1;
}
