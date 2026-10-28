/* rgp:protos */
#line 1
/* ******* CLOSED s29 (2026-09-04) -- BYTE-IDENTICAL, 872 B, on TWO DECLARATION
 * MOVES AND NOTHING ELSE (20 bad -> 7 -> MATCH):
 *   stage 1  `Sel *e;` moved from position 4 to position 7   (20 -> 7)
 *   stage 2  `Item *it;` <-> `s32 r;` swapped                (7  -> MATCH)
 * At 7 bad the residue was a PURE TWO-REGISTER CALLEE-SAVED TRANSPOSITION,
 * s0 <-> s2 over exactly two webs -- `o = func_1FEDE0()` (retail $s0) and
 * `e = func_3C2FB0(...)` (retail $s2) -- i.e. retail follows first-definition
 * order and we inverted it ([[mwcc-callee-saved-creation-order]],
 * [[residue-transposition-class]]).  s28's regswap28.py reported NORMAL had
 * ZERO pure two-register swaps to aim the degree work at; this unit BECAME one
 * after stage 1, so that census is a snapshot, not a property of the image.
 * !! Stage 2 is a PAIRWISE SWAP and stage 1 a SINGLE MOVE, and neither deck
 * finds the other's edit: the whole-list single-move deck gave 5 objects at
 * stage 1, and the swap only pays once the move is the base.  The STAGED deck
 * ([[mwcc-wholelist-decl-sweep]]) is the method, not a refinement of it.
 * build/wf-normal/s29/mkdeck29.py (pool deck, 1,120 arms over 20 units, every
 * unit's identity arm reproducing its recorded bad count) + the stage-2 rerun.
 */
#include "types.h"
/* normal 0x005025B0 -- the item-list screen's input frame.  func_28E170 over
 * the D_004B2570 pad map returns a mode: 1 = confirm, which walks the current
 * roster entry's iterator (func_3A8180 / func_370170 / func_36FFF0) to the row
 * the cursor is on and hands the found item to virtual slot 179, then either
 * refuses through 0x560E or opens the 0x55F4 sub-page and consumes the item
 * through slot 281; 2 = cancel; 6 = the sort toggle, which re-colours the
 * 0x1E / 0x1F headers according to normal_FUN_00505DB0.
 *
 * FOUR VIRTUAL calls, so the unit is .cpp -- a struct of function pointers
 * gives `jalr $v0`.  The slots are (0x5C-8)/4 = 21, (0x2D4-8)/4 = 179,
 * (0x46C-8)/4 = 281 and (0x470-8)/4 = 282; the dummy block is GENERATED so the
 * indices cannot drift.
 * `$4` is never read -- the f(void *, s32) state-handler family.
 * D_004B2570 is a main-image object and needs a declared size over the
 * small-data threshold, or it comes out GPREL16 instead of lui/%lo.
 * `daddu $18,$3,$2` sits in func_1FEDE0's DELAY SLOT: the row index is the
 * statement BEFORE that call, and `$16` is then re-used for its result. */

typedef struct Pos { u8 pad00[0x12]; s16 f12; u8 pad14[2]; s16 f16; } Pos;
typedef struct Ctx { u8 pad000[0x440]; s32 f440; } Ctx;
typedef struct Own { u8 pad00[0x18]; s32 f18; } Own;
typedef struct Cur { u8 b[8]; } Cur;
typedef struct Src { u8 b[0x18]; } Src;
typedef struct Item { u8 b[4]; } Item;

struct Sel {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 owner() { return VCM0(s32, 0x5C); }                 /* slot 21  -> vtable +0x5C  */
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 pick(Item *it) { return VCM(s32, (void *, Item *), 0x2D4, it); }          /* slot 179 -> vtable +0x2D4 */
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void take(Item *it) { VCM(void, (void *, Item *), 0x46C, it); }          /* slot 281 -> vtable +0x46C */
    s32 locked() { return VCM0(s32, 0x470); }                /* slot 282 -> vtable +0x470 */
};

extern "C" u8   D_004B2570[0x10];   /* main-image object, materialised as an ADDRESS */

extern "C" void *D_0048449C;      /* gp - 0xCD4  */
extern "C" void *D_004844A0;      /* gp - 0xCD0  */
extern "C" void *D_004844A4;      /* gp - 0xCCC  */
extern "C" void *D_00484498;      /* gp - 0xCD8  */
extern "C" Ctx  *D_00484454;      /* gp - 0xD1C  */
extern "C" f32   D_0047D278;      /* gp - 0x7EF8 */

extern "C" s32   PadIsTriggered_1839f0(const u8 *p, s32 a);
extern "C" void  SoundPlayScaledVolume_1b9520(void *p, s32 a, s32 b, f32 c);
extern "C" Own  *GetGameData_1fede0(void);
extern "C" s32   UiPageWidgetAtTargetPos_2899b0(Ctx *p, s32 a);
extern "C" s32   MenuGridCursorInput_28e170(void *p, const u8 *q, s32 c, s32 d);
extern "C" void  UiEntryListSelectByTag_28ea90(void *p, s32 id, s32 a);
extern "C" Pos  *UiEntryListGetCurrentData_28ec60(void *p);
extern "C" void  StateMachineSetState_28ede0(void *p, s32 id, s32 a);
extern "C" void  UiFadeWidgetAlpha_290690(void *p, u16 id, f32 x, f32 y, f32 z);
extern "C" void UiMoveWidgetUniform_290f50(void *, u16, s32, s32, f32, s32);
extern "C" void  UiSetWidgetsVisibleById_291110(void *p, u16 id, s32 c, s32 d);
extern "C" Item * IterSeek_36fff0(Cur *, s32, int, int);
extern "C" void IterInit_370170(Cur *, Src *, int, int);
extern "C" void  CharaAbilityViewCtor_3a8180(Src *s, Sel *e, s32 c, s32 d);
extern "C" Sel  *PartyGetSlotChara_3c2fb0(s32 a, s32 b);
extern "C" void  normal_BtlChgMenuAbilityDetailRefresh_503450(void);
extern "C" void  normal_LeaderHudBannerReshow_503720(void);
extern "C" void  normal_BtlChgPageSetAbilityReq_5052f0(Ctx *p, s32 a, s32 b);
extern "C" s32   normal_BtlChgPageIsDetailShown_505db0(Ctx *p);
extern "C" void  normal_BtlChgPageToggleDetail_505dc0(Ctx *p, s32 a, s32 b);
extern "C" s32   normal_BtlChgPageGetMember_505f90(Ctx *p);
extern "C" void  normal_BtlChgPageSetCloseCode_505fc0(Ctx *p, s32 a);

extern "C" s32 normal_BtlChgMenuAbilityListState_5025b0(void *a, s32 b);

s32 normal_BtlChgMenuAbilityListState_5025b0(void *a, s32 b)
{
    Cur   cur __attribute__((aligned(16)));
    Src   src __attribute__((aligned(16)));
    Pos  *q;
    Own  *o;
    s32   r;
    s32   mode;
    s32   row;
    Sel  *e;
    Item *it;
    const u8 *pad;

    if (b != 0) {
        UiSetWidgetsVisibleById_291110(D_0048449C, 0x40, 1, 1);
        UiEntryListSelectByTag_28ea90(D_004844A0, 0x55F1, 0);
    }
    mode = MenuGridCursorInput_28e170(D_004844A0, D_004B2570, 1, 0);
    q = UiEntryListGetCurrentData_28ec60(D_004844A0);
    if (mode == 1) {
        SoundPlayScaledVolume_1b9520(D_004844A4, 5, 0, 1.0f);
        if (q != 0) {
            row = q->f12 + q->f16;
            o = GetGameData_1fede0();
            if (o == 0) {
                return 0;
            }
            e = PartyGetSlotChara_3c2fb0(o->f18, normal_BtlChgPageGetMember_505f90(D_00484454));
            if (e == 0) {
                return 0;
            }
            CharaAbilityViewCtor_3a8180(&src, e, 0, -1);
            IterInit_370170(&cur, &src, 0, 0);
            it = IterSeek_36fff0(&cur, row, 0, 0);
            if (it == 0) {
                return 0;
            }
            r = e->pick(it);
            if (r != 0) {
                if (e->locked() == 0) {
                    StateMachineSetState_28ede0(D_00484498, 0x55F4, 0);
                    normal_LeaderHudBannerReshow_503720();
                    normal_BtlChgPageSetAbilityReq_5052f0(D_00484454, e->owner(), r);
                    D_00484454->f440 = 1;
                    normal_BtlChgPageSetCloseCode_505fc0(D_00484454, 1);
                    e->take(it);
                } else {
                    StateMachineSetState_28ede0(D_00484498, 0x560E, 0);
                }
            }
        }
    } else if (mode == 2) {
        SoundPlayScaledVolume_1b9520(D_004844A4, 6, 0, 1.0f);
        StateMachineSetState_28ede0(D_00484498, 0x55F5, 0);
    } else if (mode == 6) {
        pad = D_004B2570;
        if (q != 0 && PadIsTriggered_1839f0(pad, 0x10) != 0
            && UiPageWidgetAtTargetPos_2899b0(D_00484454, 0x1F) != 0) {
            normal_BtlChgPageToggleDetail_505dc0(D_00484454, 0, 0);
            if (normal_BtlChgPageIsDetailShown_505db0(D_00484454) != 0) {
                SoundPlayScaledVolume_1b9520(D_004844A4, 5, 0, 1.0f);
                UiMoveWidgetUniform_290f50(D_0048449C, 0x1F, -0x6E, -0x7B, D_0047D278, 0);
                UiFadeWidgetAlpha_290690(D_0048449C, 0x1F, 1.0f, 0.125f, 0.0f);
                UiFadeWidgetAlpha_290690(D_0048449C, 0x1E, 0.0f, 0.125f, 1.0f);
            } else {
                SoundPlayScaledVolume_1b9520(D_004844A4, 6, 0, 1.0f);
                UiMoveWidgetUniform_290f50(D_0048449C, 0x1F, 0x32, -0x7B, D_0047D278, 0);
                UiFadeWidgetAlpha_290690(D_0048449C, 0x1F, 0.0f, 0.25f, 1.0f);
                UiFadeWidgetAlpha_290690(D_0048449C, 0x1E, 1.0f, 0.125f, 0.0f);
            }
        }
    }
    normal_BtlChgMenuAbilityDetailRefresh_503450();
    return 1;
}
