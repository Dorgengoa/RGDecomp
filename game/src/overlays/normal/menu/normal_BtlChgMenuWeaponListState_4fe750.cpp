/* rgp:protos */
#line 1
#include "types.h"
/* normal 0x004FE750 -- the world-map / travel screen's open-and-poll handler.
 * On the open edge (`b != 0`) it resets the 0x55F4 record, raises the seven
 * 0x21..0x29 widget groups, and -- when the cursor's map cell holds a live
 * entity -- hands that entity the 0x527B20 descriptor through its virtual
 * slot 17 and mirrors the descriptor into func_290460's 0x42 slot.  Every
 * frame after that it re-reads the 0x28 input map and, while the four cursor
 * halfwords are unchanged, dispatches on the 0x4B2570 pad result: 2 = confirm
 * (build the 0x3E/0x40 caption at the record's offset), 1 = cancel-into-the
 * cell (either the 0x560B refusal or the 0x560F accept).
 *
 * `$4` is never read; this is the f(void *, s32) state-handler family, same as
 * normal_ThinkMenuConfirmOpenState_520320 and normal_BtlChgMenuCommandOpenState_501290.
 * THREE VIRTUAL calls (`lw $25,0($x) / lw $25,off($25) / jalr $25`), so the
 * unit is .cpp -- a struct of function pointers gives `jalr $v0`, only a real
 * C++ `virtual` gives `jalr $t9`.  mwcc puts the first virtual at vtable +0x08,
 * so the three slots are (0x4C-8)/4 = 17 and (0x70-8)/4 = 26 on Ent and
 * (0xE8-8)/4 = 56 on Node; the placeholder lists are expanded from those
 * OFFSETS by build/n_gen4fe750.py so the indices cannot drift.
 *
 * `daddu $17,$2,$0` / `daddu $16,$2,$0` in a call's DELAY SLOT captures the
 * PREVIOUS call's result -- func_3D4D80's value is read in func_3D4C20's slot
 * and func_28E170's in the second func_28EC60's, so each belongs to the
 * statement BEFORE the call it sits in.
 * `dsll32/dsra32 ..,16` on normal_BtlChgPageGetMember_505f90's result is the explicit (s16)
 * cast, the same idiom normal_BtlChgMenuCommandOpenState_501290 already carries.
 * `mult`/`mult1` is mwcc using BOTH EE multiplier pipes for the two
 * independent products in the 0x40 caption's x and y -- one source expression.
 * D_004B2570 is a main-image object and needs a declared size over the
 * small-data threshold, or it comes out GPREL16 instead of lui/%lo.
 *
 * FOUR BUILDS, and the three length levers are all reusable:
 * 1. the four saved cursor halfwords are s32 LOCALS, not s16.  As s16 they
 *    live in callee-saved registers across func_28E170 and mwcc re-normalises
 *    each one with dsll32/dsra32 ..,16 before its compare -- SIX words long.
 *    The mirror of levers.d/normal-s16-cast-sign-extension: that note says an
 *    int local plus an explicit (s16) cast BUYS the pair; this says an s16
 *    local held across a call buys it when you do not want it.
 * 2. `arr` is a NAMED Ent ** for D_00484454->f7C.  A plain subscript gives
 *    `sll idx,2 / lw ctx / addu / lw 0x7C(..)`; retail materialises the array
 *    ADDRESS (`addiu $3,$2,0x7C`) and indexes off it (`lw 0($16)`), which is
 *    what lets the second use reload through the same register.  And the
 *    assignment has to come AFTER the idx arithmetic -- written before it,
 *    the addiu schedules to the head of the block, one word out of place.
 * 3. the four-way cursor compare is an EARLY `return 1` on the NEGATED
 *    condition, not an `&&` around the body.  Written positively all four
 *    failures share one exit; written negatively mwcc gives the first test a
 *    `bnel` straight to the epilogue with `li $2,1` in the LIKELY SLOT and
 *    the other three a `li $2,1 / b / nop` block of their own, and the
 *    mode==2 arm materialises its own 1 in its `b`'s delay slot.  Two words.
 *    Same class as normal_ShopMenuSellItemStatusLayout_50ef80's recorded open residue, reached from
 *    the other side. */

typedef struct Hdl {
    u8   pad00[4];
    s16  f04;
    s16  f06;
    s16  f08;
    s16  f0A;
    u8   pad0C[0x14 - 0xC];
    s16  f14;
    s16  f16;
    u8   pad18[2];
    s16  f1A;
} Hdl;

typedef struct Pos {
    u8   pad00[0x10];
    s16  f10;
    s16  f12;
    s16  f14;
    s16  f16;
} Pos;

typedef struct Mdl  { u8 pad00[0x30]; s32 f30; } Mdl;
typedef struct Slot { u8 pad00[4]; const void *f04; u8 pad08[0x14 - 8]; s32 f14; } Slot;
typedef struct Hold { u8 pad00[0x28]; Slot *f28; } Hold;

struct Node {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 count() { return VCM0(s32, 0xE8); }                  /* slot 56 -> vtable +0xE8 */
};

struct Ent {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void attach(const void *p) { VCM(void, (void *, const void *), 0x4C, p); }    /* slot 17 -> vtable +0x4C */
    
    
    
    
    
    
    
    
    s32 limit() { return VCM0(s32, 0x70); }                  /* slot 26 -> vtable +0x70 */
    u8   pad04[0x10 - 4];
    Mdl *f10;
};

typedef struct Ctx { u8 pad00[0x7C]; Ent *f7C[1]; } Ctx;

extern "C" u8    D_004B2570[0x10];   /* main-image object, materialised as an ADDRESS */
extern "C" u8  normal_D_00527020[];
extern "C" u8  normal_D_005278E0[];
extern "C" u8  normal_D_00527B20[];

extern "C" void *D_0048449C;         /* gp - 0xCD4  */
extern "C" void *D_004844A0;         /* gp - 0xCD0  */
extern "C" void *D_00484498;         /* gp - 0xCD8  */
extern "C" Ctx  *D_00484454;         /* gp - 0xD1C  */
extern "C" s32   D_004844C4;         /* gp - 0xCAC  */
extern "C" s16   D_004844E4;         /* gp - 0xC8C  */
extern "C" s16   D_0048051C;         /* gp - 0x4C54 */
extern "C" f32   D_0047D518;         /* gp - 0x7C58 */
extern "C" f32   D_0047D52C;         /* gp - 0x7C44 */

extern "C" s32   GetGameData_1fede0(void);
extern "C" void  UiSelFrameAnimStep_28d820(const void *a, s32 b);
extern "C" s32   MenuGridCursorInput_28e170(void *p, const u8 *q, s32 c, s32 d);
extern "C" Hdl  *UiEntryListFindByTag_28ea40(void *p, s32 id);
extern "C" void  UiEntryListSelectByTag_28ea90(void *p, s32 id, s32 a);
extern "C" Pos  *UiEntryListGetCurrentData_28ec60(void *p);
extern "C" void  StateMachineSetState_28ede0(void *p, s32 id, s32 a);
extern "C" void  UiSetWidgetVisible_290010(void *p, u16 id, s32 c, s32 d);
extern "C" Hold *UiFindWidget_290460(void *p, u16 id);
extern "C" void  UiFadeWidgetAlpha_290690(void *p, u16 id, f32 x, f32 y, f32 z);
extern "C" void  UiSetWidgetAlpha_2907a0(void *p, u16 id, f32 x);
extern "C" void  UiSetWidgetPos_290f60(void *p, u16 id, s32 x, s32 y);
extern "C" void  UiGetWidgetPos_2910a0(void *p, u16 id, s32 *x, s32 *y);
extern "C" void  UiSetWidgetsVisibleById_291110(void *p, u16 id, s32 c, s32 d);
extern "C" s32   PartyFindItemHolder_3d4c20(Ent *p);
extern "C" Node *ItemFindOwnerChara_3d4d80(Ent *p, s32 a);
extern "C" void  normal_FieldHudPanelSelectRaise_4f4dc0(const void *p, s16 n);
extern "C" void  normal_FieldHudPanelSelectHide_4f4eb0(const void *p, s16 n);
extern "C" void  normal_BtlChgMenuStatusIconsUpdate_501a70(s16 a);
extern "C" void  normal_BtlChgMenuCursorShow_503730(s32 a);
extern "C" s32   normal_BtlChgPageGetMember_505f90(Ctx *p);

extern "C" s32 normal_BtlChgMenuWeaponListState_4fe750(void *a, s32 b);

s32 normal_BtlChgMenuWeaponListState_4fe750(void *a, s32 b)
{
    Hdl  *r;
    Pos  *q;
    Hold *w;
    Slot *sl;
    Ent  *e;
    Ent **arr;
    Node *nd;
    s32   c0;
    s32   c1;
    s32   c2;
    s32   c3;
    s32   mode;
    s32   miss;
    s32   idx;
    s32   px;
    s32   py;

    if (b != 0) {
        D_0048051C = -1;
        D_004844C4 = 0;
        UiEntryListSelectByTag_28ea90(D_004844A0, 0x55F4, 0);
        UiFadeWidgetAlpha_290690(D_0048449C, 0x21, 1.0f, D_0047D518, -1.0f);
        UiFadeWidgetAlpha_290690(D_0048449C, 0x26, 1.0f, D_0047D518, -1.0f);
        UiFadeWidgetAlpha_290690(D_0048449C, 0x55, 1.0f, D_0047D518, -1.0f);
        UiFadeWidgetAlpha_290690(D_0048449C, 0x27, 1.0f, D_0047D518, -1.0f);
        UiFadeWidgetAlpha_290690(D_0048449C, 0x25, 1.0f, D_0047D518, -1.0f);
        UiFadeWidgetAlpha_290690(D_0048449C, 0x23, 1.0f, D_0047D518, -1.0f);
        UiFadeWidgetAlpha_290690(D_0048449C, 0x29, 1.0f, D_0047D518, -1.0f);
        UiSetWidgetsVisibleById_291110(D_0048449C, 0x41, 1, 1);
        UiSetWidgetPos_290f60(D_0048449C, 0x41, 0x3C, 0x92);
        r = UiEntryListFindByTag_28ea40(D_004844A0, 0x55F4);
        idx = (s16)(r->f14 + (r->f16 * 8) + (r->f1A * 8));
        arr = D_00484454->f7C;
        miss = 1;
        if (idx < 0xF0 && arr[idx] != 0) {
            if (GetGameData_1fede0() == 0) {
                return 0;
            }
            e = arr[idx];
            if (e == 0) {
                return 0;
            }
            w = UiFindWidget_290460(D_0048449C, 0x42);
            if (w == 0) {
                return 0;
            }
            sl = w->f28;
            if (sl == 0) {
                return 0;
            }
            e->attach(normal_D_00527B20);
            sl->f04 = normal_D_00527B20;
            sl->f14 = e->f10->f30;
            UiSetWidgetsVisibleById_291110(D_0048449C, 0x41, 1, 1);
            miss = 0;
        }
        if (miss != 0) {
            UiSetWidgetsVisibleById_291110(D_0048449C, 0x41, 0, 1);
        }
    }
    UiSelFrameAnimStep_28d820(normal_D_005278E0, 0x28);
    q = UiEntryListGetCurrentData_28ec60(D_004844A0);
    c0 = q->f10;
    c1 = q->f12;
    c2 = q->f14;
    c3 = q->f16;
    mode = MenuGridCursorInput_28e170(D_004844A0, D_004B2570, 2, 0);
    q = UiEntryListGetCurrentData_28ec60(D_004844A0);
    if (c0 != q->f10 || c1 != q->f12 || c2 != q->f14 || c3 != q->f16) {
        return 1;
    }
    {
        if (mode == 2) {
            UiSetWidgetsVisibleById_291110(D_0048449C, 0x3E, 1, 1);
            UiSetWidgetVisible_290010(D_0048449C, 0x2B, 1, -1);
            normal_BtlChgMenuCursorShow_503730(1);
            UiSetWidgetsVisibleById_291110(D_0048449C, 0x41, 0, 1);
            normal_FieldHudPanelSelectHide_4f4eb0(normal_D_00527020, UiEntryListFindByTag_28ea40(D_004844A0, 0x55F2)->f14);
            normal_FieldHudPanelSelectRaise_4f4dc0(normal_D_00527020, -1);
            UiSetWidgetsVisibleById_291110(D_0048449C, 0x21, 0, 1);
            normal_BtlChgMenuStatusIconsUpdate_501a70((s16)normal_BtlChgPageGetMember_505f90(D_00484454));
            r = UiEntryListFindByTag_28ea40(D_004844A0, 0x55F9);
            px = 0;
            py = 0;
            UiGetWidgetPos_2910a0(D_0048449C, 0x3E, &px, &py);
            px = px - 0x14;
            py = py + 4;
            UiSetWidgetPos_290f60(D_0048449C, 0x40,
                        px + r->f04 + (r->f14 * r->f08) - 8,
                        py + r->f06 + (r->f16 * r->f0A));
            UiSetWidgetAlpha_2907a0(D_0048449C, 0x40, 0.0f);
            StateMachineSetState_28ede0(D_00484498, 0x55FD, 0);
        } else if (mode == 1) {
            r = UiEntryListFindByTag_28ea40(D_004844A0, 0x55F4);
            idx = (s16)(r->f14 + (r->f16 * 8) + (r->f1A * 8));
            arr = D_00484454->f7C;
            if (idx < 0xF0 && arr[idx] != 0) {
                nd = ItemFindOwnerChara_3d4d80(arr[idx], 0);
                if (PartyFindItemHolder_3d4c20(arr[idx]) != 0) {
                    D_004844E4 = 3;
                    StateMachineSetState_28ede0(D_00484498, 0x560B, 0);
                } else if (nd->count() >= arr[idx]->limit()) {
                    UiFadeWidgetAlpha_290690(D_0048449C, 0x29, 0.0f, D_0047D52C, -1.0f);
                    UiSetWidgetsVisibleById_291110(D_0048449C, 0x41, 0, 1);
                    StateMachineSetState_28ede0(D_00484498, 0x560F, 0);
                }
            }
        }
    }
    return 1;
}
