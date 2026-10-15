#include "types.h"
/* normal 0x00500B80 -- the field-menu open/close arbiter.  session 31, lane n31j.
 *
 * Shape read off the retail listing:
 *  - two parameters; only the SECOND ($5) is read, and it gates the first block.
 *  - `r` = normal_BtlChgPageGetCommand_505d90(D_00484454) lives in $16 and is compared
 *    0x64, 3, 2, 1, 0 in DESCENDING test order while the BODIES are laid out
 *    ASCENDING (0,1,2,3,0x64,default) -- that pairing IS a compiled `switch`.
 *    An if/else-if chain reads 2 words SHORT (161 vs 163): its dispatch is 13
 *    words against retail's 17, and it loses the two %hi(D_00527020) `lui`s
 *    that retail gets free in the two `beql` delay slots.
 *  - `lh $3,0x44E($4)` + `sltu $3,$0,$3` sit BEFORE the chain, so the
 *    "!= 0" boolean is its own statement, not a guard inside case 0.
 *  - D_00484454 is re-read after every call: mwcc CSEs the global load from the
 *    boolean statement into each arm's FIRST use and a call kills it, which is
 *    why case 3 and the default arm use the cached pointer and every other arm
 *    reloads.  Spelling it as the plain global everywhere reproduces both.
 *  - D_004844A8 / D_004844C8 are addressed `addiu $r,$28,-K`, so they must be
 *    declared <= 8 bytes ([[im-gp-array-sdata-threshold]]); D_00527020 is
 *    %hi/%lo, so it stays an incomplete array.
 */

typedef struct Ctx {
    u8  pad000[0x43C];
    s16 f43C;
    u8  pad43E[0x44E - 0x43E];
    s16 f44E;
} Ctx;

typedef struct Top {
    u8  pad00[0x18];
    s32 f18;
} Top;

extern const u8 D_00527020[];

extern Ctx  *D_00484454;          /* gp - 0xD1C */
extern s32   D_0048444C;          /* gp - 0xD24 */
extern void *D_00484498;          /* gp - 0xCD8 */
extern void *D_0048449C;          /* gp - 0xCD4 */
extern u8    D_004844A8[8];       /* gp - 0xCC8 */
extern s8    D_004844C8[8];       /* gp - 0xCA8 */
extern f32   D_0047D278;          /* gp - 0x7EF8 */

extern Top  *func_1FEDE0(void);
extern void  func_131B60(void *p, s32 v, s32 n);
extern void  func_28EDE0(void *p, s32 id, s32 a);
extern void  func_290010(void *p, s32 id, s32 c, s32 d);
extern void  func_290F50(void *p, s32 id, s32 x, s32 y, s32 k, f32 t);
extern s32   func_3C2FB0(s32 a, s32 b);
extern s32   func_3C3120(s32 a, s32 b);
extern void  normal_FieldHudPanelSelectRaise_4f4dc0(const u8 *w, s32 k);
extern void  normal_FieldHudPanelSelectHide_4f4eb0(const u8 *w, s32 k);
extern void  normal_FieldHudPanelsDim_4f4f80(const u8 *w, s32 k);
extern void  normal_BtlChgMenuCommandPanelSlide_501e90(s32 a, s32 b);
extern void  normal_BtlChgMenuCursorShow_503730(s32 a);
extern s32   normal_BtlChgPageGetCommand_505d90(Ctx *p);
extern s32   normal_BtlChgPageGetMember_505f90(Ctx *p);
extern void  normal_BtlChgPageSetCloseCode_505fc0(Ctx *p, s32 a);
extern void  normal_BtlChgPageStop_505fd0(Ctx *p);

s32 normal_BtlChgMenuCommandDispatchState_500b80(s32 arg0, s32 arg1)
{
    Top *top;
    s32  r;
    s32  busy;
    s32  n;

    top = func_1FEDE0();
    r = normal_BtlChgPageGetCommand_505d90(D_00484454);
    if (arg1 != 0 && r != 1) {
        normal_BtlChgMenuCommandPanelSlide_501e90(0, 0);
        func_290F50(D_0048449C, 0x40, 0x15E, 0x147, 0, D_0047D278);
    }
    if (r != 1) {
        normal_BtlChgMenuCursorShow_503730(0);
    }
    if (r != -1 && r != 1) {
        func_290010(D_0048449C, 0x2B, 0, -1);
    }
    busy = D_00484454->f44E != 0;
    switch (r) {
    case 0:
        if (busy == 0) {
            normal_FieldHudPanelsDim_4f4f80(D_00527020, -1);
            normal_FieldHudPanelSelectHide_4f4eb0(D_00527020, -1);
            D_00484454->f43C = 1;
            func_28EDE0(D_00484498, 0x55F1, 0);
        }
        break;
    case 1:
        normal_FieldHudPanelsDim_4f4f80(D_00527020, -1);
        D_00484454->f43C = 1;
        func_28EDE0(D_00484498, 0x55FD, 0);
        break;
    case 2:
        normal_FieldHudPanelsDim_4f4f80(D_00527020, -1);
        normal_FieldHudPanelSelectHide_4f4eb0(D_00527020, -1);
        D_00484454->f43C = 1;
        func_131B60(D_004844A8, 0, 6);
        n = normal_BtlChgPageGetMember_505f90(D_00484454);
        if (func_3C2FB0(top->f18, n) == 0) {
            return 0;
        }
        normal_FieldHudPanelSelectRaise_4f4dc0(D_00527020, n);
        func_28EDE0(D_00484498, 0x55F9, 0);
        break;
    case 3:
        normal_BtlChgPageStop_505fd0(D_00484454);
        n = func_3C3120(top->f18, normal_BtlChgPageGetMember_505f90(D_00484454));
        D_004844C8[n] = 0;
        D_0048444C = 2;
        normal_BtlChgPageStop_505fd0(D_00484454);
        break;
    case 0x64:
        normal_FieldHudPanelSelectHide_4f4eb0(D_00527020, -1);
        D_00484454->f43C = 1;
        func_28EDE0(D_00484498, 0x5608, 0);
        break;
    default:
        normal_BtlChgPageStop_505fd0(D_00484454);
        normal_BtlChgPageSetCloseCode_505fc0(D_00484454, 2);
        break;
    }
    return 1;
}
