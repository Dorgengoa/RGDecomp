#include "types.h"
/* normal 0x00519990 -- pad/repeat dispatcher.  $16 is ONE register reused for
 * two roles across the function: the func_37B970() dispatch id first, then
 * (after being zeroed) a "changed" flag threaded through the whole rest of
 * the body down to the final normal_TransSaveSlotListConfirm_519c60/00519c20 tail -- write it
 * as ONE C local (`v`) or the `v = 0;` reset becomes dead code and mwcc
 * won't keep $16 live across the branch chain the way retail does. */

typedef struct Obj {
    u8  pad000[0xA];
    s16 fA;
    u8  padC[0x2];
    s16 fE;
    u8  pad10[0x2];
    s16 f12;
    u8  pad14[0x2];
    s16 f16;
} Obj;

typedef struct W {
    u8  pad00[0x14];
    s32 f14;
    u8  pad18[0x4];
    s32 f1C;
} W;

extern const u8 D_004B2570;
extern W    *D_004847D8;          /* gp - 0x998 */
extern s32   D_004847F0;          /* gp - 0x980 */
extern s32   D_004847F4;          /* gp - 0x97C */

extern void normal_TransSaveSlotCursorBob_518990(void *a, void *b, s32 c);
extern s32  func_37B970(void);
extern s32  func_37B9B0(s32 a);
extern void normal_TransSaveSetError_51a000(s32 a);
extern s32  func_2F6660(void);
extern s32  func_1839F0(const u8 *p, s32 mask);
extern s32  func_183DD0(const u8 *p, s32 mask);
extern s32  func_37B500(void *a, s32 b);
extern s32  func_28E9E0(W *a, s32 b);
extern s32  normal_TransSaveSlotMoveCb_519dd0(void *a, void *b);
extern void func_3777A0(void *a, s32 b, s32 c);
extern s32  normal_TransSaveSlotListConfirm_519c60(void *a, void *b);
extern s32  normal_TransSaveSlotListCancel_519c20(void *a, void *b);

s32 normal_TransSaveSlotListTickCb_519990(Obj *a, void *b)
{
    s32 v;

    normal_TransSaveSlotCursorBob_518990(a, b, 0);

    v = func_37B970();
    if ((func_37B9B0(1) & 0xFF) == 0 || v == 6 || v == 5 || v == 8) {
        normal_TransSaveSetError_51a000(8);
        return 1;
    }

    v = 0;
    if (func_2F6660() != 0) {
        goto ret1;
    }

    if (func_1839F0(&D_004B2570, 0x2000) != 0) {
        v = func_37B500(a, 1);
    } else if (func_1839F0(&D_004B2570, 0x8000) != 0) {
        v = func_37B500(a, 0);
    } else if ((D_004847D8->f14 & 1) != 0 &&
               func_1839F0(&D_004B2570, 0x1000) != 0 &&
               func_183DD0(&D_004B2570, 0x1000) == 0) {
        if (a->f12 == 0 && a->f16 == 0 && a->fE > 0) {
            v = 1;
            a->f12 = a->fA;
            a->f16 = a->fE - a->fA;
        }
    } else if ((D_004847D8->f14 & 2) != 0 &&
               func_1839F0(&D_004B2570, 0x4000) != 0 &&
               func_183DD0(&D_004B2570, 0x4000) == 0) {
        if (a->f12 == a->fA && a->f16 == a->fE - a->fA && a->fE > 0) {
            a->f12 = 0;
            v = 1;
            a->f16 = 0;
        }
    }

    if (v != 0) {
        if ((D_004847D8->f1C & 1) == 0) {
            func_28E9E0(D_004847D8, 0);
        }
        normal_TransSaveSlotMoveCb_519dd0(a, b);
        func_3777A0(a, 0x75A1, 0);
    }

    if (func_1839F0(&D_004B2570, D_004847F0) != 0) {
        normal_TransSaveSlotListConfirm_519c60(a, b);
    } else if (func_1839F0(&D_004B2570, D_004847F4) != 0) {
        normal_TransSaveSlotListCancel_519c20(a, b);
    }
ret1:
    return 1;
}
