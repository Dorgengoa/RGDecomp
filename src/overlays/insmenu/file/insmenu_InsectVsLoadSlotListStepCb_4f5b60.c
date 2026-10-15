#include "types.h"

/* insmenu 0x004F5B60 (968 bytes, 242 instructions) -- the map-scroll input
 * handler.  Six `||` short-circuit chains of the family idiom
 *   func_1839F0(D_004B2570, M) || (func_2882C0() && func_1839F0(D_004B27E0, M))
 * (see insmenu_FUN_004EABB0 / 004F82E0), two of them extended with a
 * !func_183DD0(...) term.
 *
 * MEASURED, and the ONLY defect in the first draft (1 word LONG, 0x3CC vs
 * 0x3C8, every other wrong word a pure -4 branch displacement):
 * `if (func_2F6660() != 0) { return 1; }` written as an early-return GUARD is
 * three words -- `beql $2,$0,<continue>` + `b <epilogue>` + `addiu $2,$0,1`.
 * Retail is TWO: `bnel $2,$0,.L004F5F10` with `addiu $2,$0,1` in the delay
 * slot.  The whole remainder of the function is the BODY of
 * `if (func_2F6660() == 0) { ... }` and the trailing `return 1;` is the
 * function's fall-out, so mwcc's branch-AROUND-the-body absorbs the shared
 * return block's first instruction.  Same reading as insmenu_FUN_004F5F70's
 * func_376B20(6) fall-out; this is its second confirmed instance.
 *
 * D_004FA1B4 / D_004FA1BC are declared as 16-byte arrays and read at [0] so
 * they stay out of small data and get the %hi/%lo pair retail has
 * (insmenu_FUN_004F6740's lever).  No .lit4 and no .rodata in the object:
 * this unit needs NO link plumbing.
 */

typedef struct Obj Obj;
struct Obj {
    u8  pad00[0xA];
    s16 f0A;
    u8  pad0C[2];
    s16 f0E;
    u8  pad10[2];
    s16 f12;
    u8  pad14[2];
    s16 f16;
};

extern const u8 D_004FA1A0[];
extern const u8 D_004B2570[];
extern const u8 D_004B27E0[];
extern s32 D_004FA1B4[4];
extern s32 D_004FA1BC[4];

extern void insmenu_InsectVsLoadSlotCursorBob_4f6810(void *a, s32 b, s32 c);
extern s32  func_37B970(void);
extern u8   func_37B9B0(s32 a);
extern void insmenu_InsectVsSaveSetError_4f6e20(s32 a);
extern s32  func_2F6660(void);
extern s32  func_1839F0(const void *a, s32 b);
extern s32  func_183DD0(const void *a, s32 b);
extern s32  func_2882C0(void);
extern s32  func_37B500(Obj *o, s32 b);
extern void func_28E9E0(const void *a, s32 b);
extern s32  insmenu_InsectVsLoadSlotMoveCb_4f6180(Obj *o, s32 b);
extern void func_3777A0(void *a, s32 b, s32 c);
extern s32  insmenu_InsectVsLoadSlotListConfirm_4f5f70(Obj *o, s32 b);
extern void func_376B20(s32 a);
extern s32  insmenu_InsectVsLoadSlotListCancel_4f5f30(Obj *o, s32 b);

s32 insmenu_InsectVsLoadSlotListStepCb_4f5b60(Obj *o, s32 arg1)
{
    s32 st;
    s32 r;
    s16 a;

    insmenu_InsectVsLoadSlotCursorBob_4f6810(o, arg1, 0);
    st = func_37B970();
    if (func_37B9B0(1) == 0 || st == 6 || st == 5 || st == 8) {
        insmenu_InsectVsSaveSetError_4f6e20(8);
        return 1;
    }
    r = 0;
    if (func_2F6660() == 0) {
        if (func_1839F0(D_004B2570, 0x2000) != 0 ||
            (func_2882C0() != 0 && func_1839F0(D_004B27E0, 0x2000) != 0)) {
            r = func_37B500(o, 1);
        } else if (func_1839F0(D_004B2570, 0x8000) != 0 ||
                   (func_2882C0() != 0 && func_1839F0(D_004B27E0, 0x8000) != 0)) {
            r = func_37B500(o, 0);
        } else if ((D_004FA1B4[0] & 1) &&
                   ((func_1839F0(D_004B2570, 0x1000) != 0 &&
                     func_183DD0(D_004B2570, 0x1000) == 0) ||
                    (func_2882C0() != 0 && func_1839F0(D_004B27E0, 0x1000) != 0 &&
                     func_183DD0(D_004B27E0, 0x1000) == 0))) {
            if (o->f12 == 0 && o->f16 == 0 && o->f0E > 0) {
                o->f12 = o->f0A;
                r = 1;
                o->f16 = o->f0E - o->f0A;
            }
        } else if ((D_004FA1B4[0] & 2) &&
                   ((func_1839F0(D_004B2570, 0x4000) != 0 &&
                     func_183DD0(D_004B2570, 0x4000) == 0) ||
                    (func_2882C0() != 0 && func_1839F0(D_004B27E0, 0x4000) != 0 &&
                     func_183DD0(D_004B27E0, 0x4000) == 0))) {
            a = o->f0A;
            if (o->f12 == a && o->f16 == o->f0E - a && o->f0E > 0) {
                o->f12 = 0;
                r = 1;
                o->f16 = 0;
            }
        }
        if (r != 0) {
            if ((D_004FA1BC[0] & 1) == 0) {
                func_28E9E0(D_004FA1A0, 0);
            }
            insmenu_InsectVsLoadSlotMoveCb_4f6180(o, arg1);
            func_3777A0(o, 0x890C, 0);
        }
        if (func_1839F0(D_004B2570, 0x40) != 0 ||
            (func_2882C0() != 0 && func_1839F0(D_004B27E0, 0x40) != 0)) {
            insmenu_InsectVsLoadSlotListConfirm_4f5f70(o, arg1);
        } else if (func_1839F0(D_004B2570, 0x20) != 0 ||
                   (func_2882C0() != 0 && func_1839F0(D_004B27E0, 0x20) != 0)) {
            func_376B20(6);
            insmenu_InsectVsLoadSlotListCancel_4f5f30(o, arg1);
        }
    }
    return 1;
}
