/* rgp:protos */
#line 1
/* !! PARKED after 3 round trips, TWO WORDS LONG (0x510 vs 0x508).  NOT under
 * src/.  Lane nb, session 19.  (Round trip 1 was lost to a compile error --
 * the Ent class had no f0C member -- so only two scoring arms were measured.)
 * The register-level diff isolates the excess to the three `f = 1` failure
 * arms of the entry pass.  Retail TAIL-MERGES all three into ONE
 * `addiu $16,$0,1` at 0x004FF8D4 and reaches two of them through
 * branch-likely delay slots:
 *     beqz $1,.L004FF8D4                      (k >= 0x21)
 *     beql $3,$2,.L004FF8D8 ; addiu $16,$0,1  (slot id == -1)
 *     beql $17,$0,.L004FF8D8 ; addiu $16,$0,1 (func_3C8370 failed)
 * mwcc instead emits the innermost `f = 1` inline as
 *     bnezl s1,ELSE ; ... ; li s0,1 ; b ...
 * which costs one extra word, and one more word is lost to an `sll` that
 * retail schedules after the `%lo` materialisation (0x004FF988 vs 0x004FF98C).
 * ARMS MEASURED: 1 (the natural nested if/else-if with three `f = 1` arms).
 * Everything else is length-clean: the six 0x290690 tint calls, the two
 * `(s16)`-cast index sums CSEd across the `< 0x21` test and the subscript,
 * both C++ virtual sites (slots 155 and 158), the normal_FieldHudItemUseFeedbackSeCb_4f2aa0 function
 * pointer argument, and the whole CONFIRM path.
 * NEXT ARM (unmeasured): hoist the failure flag out, e.g.
 *     f = 0; if (...) { ... if (...) { ... if (o != 0) { ...; goto done; } } }
 *     f = 1; done: ;
 * so all three failures reach ONE assignment, matching retail's tail merge. */
#include "types.h"
/* normal 0x004FF6C0 -- the quest-board page driver.  On the entry pass
 * (b != 0) the six sliders are re-tinted and the 0x42 preview is filled from
 * whichever board slot the cursor sits on, or the 0x41 frame is hidden.  Then
 * the pad is read: CANCEL (2) posts 0x55FB, CONFIRM (1) resolves the slot
 * again, records it in the gp block and either refuses (no usable member ->
 * 0x560B, wrong state -> 0x5604) or accepts, aiming the party at the quest
 * marker and posting 0x55F8.
 *
 * TWO "lw $25,0($x) / lw $25,K($25) / jalr $25" sites -> C++ virtual, vptr 0,
 * slots (0x274-8)/4 = 155 and (0x280-8)/4 = 158.
 * "$4" is never read -- the f(void *, s32) state-handler family.
 * "dsll32/dsra32 ..,16" off the index sum is an s32 expression with an
 * explicit (s16) cast, CSEd between the < 0x21 test and the subscript. */

struct Ent {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 canUse(s32 k) { return VCM(s32, (void *, s32), 0x274, k); }   /* slot 155 -> vtable +0x274 */
    
    
    void aim(void *m) { VCM(void, (void *, void *), 0x280, m); }   /* slot 158 -> vtable +0x280 */
    u8   pad04[0x0C - 4];
    s32  f0C;
};

typedef struct Slot { s32 f00; s32 f04; s32 f08; s16 f0C; s16 f0E; } Slot;
typedef struct Info { u8 pad00[0xC]; s32 f0C; u8 pad10[0x30 - 0x10]; s32 f30; } Info;
typedef struct Obj  { u8 pad00[4]; s16 f04; u8 pad06[0x10 - 6]; Info *f10; } Obj;
typedef struct Cell { u8 pad00[4]; s32 f04; u8 pad08[0x14 - 8]; s32 f14; } Cell;
typedef struct Wgt  { u8 pad00[0x28]; Cell *f28; } Wgt;
typedef struct Cur  { u8 pad00[0x10]; s16 f10; s16 f12; u8 pad14[2]; s16 f16; } Cur;
typedef struct Hdl  { u8 pad00[0x14]; s16 f14; s16 f16; u8 pad18[2]; s16 f1A; } Hdl;
typedef struct Root { u8 pad00[0xC]; s32 f0C; u8 pad10[8]; s32 f18; } Root;

extern "C" u8 D_004B2570[];
extern "C" u8 normal_D_005278E0[];
extern "C" Slot     normal_D_00527910[];

extern "C" s16   D_0048051C;          /* gp - 0x4C54 */
extern "C" Obj  *D_004844C4;          /* gp - 0xCAC */
extern "C" void *D_00484454;          /* gp - 0xD1C */
extern "C" void *D_00484498;          /* gp - 0xCD8 */
extern "C" void *D_0048449C;          /* gp - 0xCD4 */
extern "C" void *D_004844A0;          /* gp - 0xCD0 */
extern "C" s16   D_004844A8;          /* gp - 0xCC8 */
extern "C" s16   D_004844AA;          /* gp - 0xCC6 */
extern "C" s16   D_004844AC;          /* gp - 0xCC4 */
extern "C" s16   D_004844E4;          /* gp - 0xC8C */
extern "C" f32   D_0047D518;          /* gp - 0x7C58 */

extern "C" {

extern Root *GetGameData_1fede0(void);
extern void  UiSelFrameAnimStep_28d820(const u8 *p, s32 a);
extern s32   MenuGridCursorInput_28e170(void *w, const u8 *p, s32 c, s32 d);
extern Hdl  *UiEntryListFindByTag_28ea40(void *w, s32 id);
extern void  UiEntryListSelectByTag_28ea90(void *w, s32 id, s32 a);
extern Cur  *UiEntryListGetCurrentData_28ec60(void *w);
extern void  StateMachineSetState_28ede0(void *w, s32 id, s32 a);
extern Wgt  *UiFindWidget_290460(void *w, u16 id);
extern void  UiFadeWidgetAlpha_290690(void *w, u16 id, f32 r, f32 g, f32 b);
extern void  UiSetWidgetPos_290f60(void *w, u16 id, s32 x, s32 y);
extern void  UiSetWidgetsVisibleById_291110(void *w, u16 id, s32 c, s32 d);
extern void  ItemUseMaybe_2eef60(s32 a, void *m, void (*fn)(void *), s32 c, s32 d);
extern void  ExecInfoInitFromInvItem_3a7430(void *m, s32 a, s16 b, s32 c);
extern void  ExecInfoInit_3a7940(void *m);
extern Ent  *PartyFindMember_3c2130(s32 w, s32 a, s32 b, s32 c, s32 d, s32 e, s32 f);
extern Ent  *PartyGetSlotChara_3c2fb0(s32 w, s32 k);
extern Obj  *InvFindInCategoryRange_3c8370(s32 w, s32 id, s32 c, s32 d, s32 e, s32 f);
extern s32   ItemGetUseEffectTargetKind_3d4f30(Obj *o);
extern void  normal_FieldHudItemUseFeedbackSeCb_4f2aa0(void *p);
extern void  normal_FieldHudItemUseSeReset_4f2d40(void);
extern void  normal_BtlChgPageSetCommand_505da0(void *p, s16 k);
extern s32   normal_BtlChgPageGetMember_505f90(void *p);

}

/* ⚠ THE `o == 0` EDGE MUST BE ITS OWN `f = 1; goto shown;` IN AN EXPLICIT
 * `else` -- levers.d/mwcc-mixed-exit-statements, the DUPLICATE cell.  Letting
 * it fall out of the two nested ifs to the shared `f = 1` makes mwcc SHARE
 * (`beq $17,$0,.L004FF8D4` + `nop`); retail DUPLICATES (`beql $17,$0,.L004FF8D8`
 * with `addiu $16,$0,0x1` in the ANNULLED slot, branching PAST the shared
 * block).  2 words, and it reads as a scheduling difference, not a CFG one.
 * ⚠ THE INVERTED EARLY-EXIT GUARD IS NOT THE SAME CELL: `if (o == 0) { f = 1;
 * goto shown; }` ahead of the body comes out ONE WORD LONG (0x50c vs 0x508).
 * Only the `else` reaches it.  The other three edges into `f = 1` (k >= 0x21,
 * p->f00 == -1) still fall through to the SHARED block at .L004FF8D4. */
extern "C" s32 normal_BtlChgMenuItemListState_4ff6c0(void *a, s32 b)
{
    s32   m[0x1C] __attribute__((aligned(16)));
    Root *t;
    Cur  *q;
    Hdl  *h;
    Slot *p;
    Obj  *o;
    Ent  *v;
    Ent  *u;
    Wgt  *w;
    Cell *g;
    s32   r;
    s32   k;
    s32   kk;
    s32   f;
    s16   n;

    if (b != 0) {
        D_0048051C = -1;
        D_004844C4 = 0;
        UiEntryListSelectByTag_28ea90(D_004844A0, 0x55F3, 0);
        UiFadeWidgetAlpha_290690(D_0048449C, 0x21, 1.0f, D_0047D518, -1.0f);
        UiFadeWidgetAlpha_290690(D_0048449C, 0x26, 1.0f, D_0047D518, -1.0f);
        UiFadeWidgetAlpha_290690(D_0048449C, 0x27, 1.0f, D_0047D518, -1.0f);
        UiFadeWidgetAlpha_290690(D_0048449C, 0x25, 1.0f, D_0047D518, -1.0f);
        UiFadeWidgetAlpha_290690(D_0048449C, 0x23, 1.0f, D_0047D518, -1.0f);
        UiFadeWidgetAlpha_290690(D_0048449C, 0x29, 1.0f, D_0047D518, -1.0f);
        UiSetWidgetsVisibleById_291110(D_0048449C, 0x41, 1, 1);
        UiSetWidgetPos_290f60(D_0048449C, 0x41, 0x3C, 0x92);
        h = UiEntryListFindByTag_28ea40(D_004844A0, 0x55F3);
        k = h->f14 + h->f16 * 8 + h->f1A * 8;
        f = 0;
        if ((s16)k < 0x21) {
            p = &normal_D_00527910[(s16)k];
            if (p->f00 != -1) {
                t = GetGameData_1fede0();
                if (t == 0) {
                    return 0;
                }
                o = InvFindInCategoryRange_3c8370(t->f18, p->f00, 0, -1, 0, 0);
                if (o != 0) {
                    w = UiFindWidget_290460(D_0048449C, 0x42);
                    if (w == 0) {
                        return 0;
                    }
                    g = w->f28;
                    if (g == 0) {
                        return 0;
                    }
                    g->f04 = o->f10->f0C;
                    g->f14 = o->f10->f30;
                    UiSetWidgetsVisibleById_291110(D_0048449C, 0x41, 1, 1);
                    goto shown;
                } else {
                    f = 1;
                    goto shown;
                }
            }
        }
        f = 1;
    shown: ;
        if (f != 0) {
            UiSetWidgetsVisibleById_291110(D_0048449C, 0x41, 0, 1);
        }
    }
    UiSelFrameAnimStep_28d820(normal_D_005278E0, 0x28);
    r = MenuGridCursorInput_28e170(D_004844A0, D_004B2570, 2, 0);
    q = UiEntryListGetCurrentData_28ec60(D_004844A0);
    if (r == 2) {
        StateMachineSetState_28ede0(D_00484498, 0x55FB, 0);
    } else if (r == 1) {
        kk = (s16)(q->f10 + q->f12 * 8 + q->f16 * 8);
        if (kk < 0x21) {
            p = &normal_D_00527910[kk];
            if (p->f00 != -1) {
                t = GetGameData_1fede0();
                if (t == 0) {
                    return 0;
                }
                o = InvFindInCategoryRange_3c8370(t->f18, p->f00, 0, -1, 0, 0);
                if (o != 0) {
                    D_0048051C = kk;
                    D_004844C4 = o;
                    D_004844A8 = q->f10;
                    D_004844AA = q->f12;
                    D_004844AC = q->f16;
                    v = PartyGetSlotChara_3c2fb0(t->f18, normal_BtlChgPageGetMember_505f90(D_00484454));
                    if (v == 0) {
                        return 0;
                    }
                    if (v->canUse(-1) != 0) {
                        if (ItemGetUseEffectTargetKind_3d4f30(D_004844C4) == 1) {
                            u = PartyFindMember_3c2130(t->f18, -1, 1, 0, -1, 0, 0);
                            if (u != 0) {
                                o = InvFindInCategoryRange_3c8370(t->f18,
                                                normal_D_00527910[D_0048051C].f00,
                                                0, -1, 0, 0);
                                if (o != 0) {
                                    n = o->f04;
                                    ExecInfoInit_3a7940(m);
                                    ExecInfoInitFromInvItem_3a7430(m, u->f0C, n, 0);
                                    u->aim(m);
                                    normal_FieldHudItemUseSeReset_4f2d40();
                                    ItemUseMaybe_2eef60(-1, m, normal_FieldHudItemUseFeedbackSeCb_4f2aa0, 0, 0);
                                }
                            }
                            normal_BtlChgPageSetCommand_505da0(D_00484454, -1);
                            UiSetWidgetsVisibleById_291110(D_0048449C, 0x41, 0, 1);
                            UiSetWidgetsVisibleById_291110(D_0048449C, 0x21, 0, 1);
                            UiSetWidgetsVisibleById_291110(D_0048449C, 0x26, 0, 1);
                            StateMachineSetState_28ede0(D_00484498, 0x55F8, 0);
                        } else {
                            StateMachineSetState_28ede0(D_00484498, 0x5604, 0);
                        }
                        UiSetWidgetsVisibleById_291110(D_0048449C, 0x41, 0, 1);
                    } else {
                        D_004844E4 = 1;
                        StateMachineSetState_28ede0(D_00484498, 0x560B, 0);
                    }
                }
            }
        }
    }
    return 1;
}
