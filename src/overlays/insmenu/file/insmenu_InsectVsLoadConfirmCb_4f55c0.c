#include "types.h"

/* insmenu 0x004F55C0 (1416 bytes, 354 instructions) -- the insect-menu top
 * state machine.  `D_00484394` (gp - 0xDDC) is the state; the dispatch is a
 * five-arm compiled SWITCH (every arm is entered by a `beq`/`beql` INTO it and
 * the compare chain runs 4,3,2,1,0 -- i.e. reversed from the source order),
 * with the fall-through being the default.  Every arm ends in the shared
 * `return 1`.
 *
 * MEASURED, and the ONLY defect in the first draft (2 words LONG, 0x590 vs
 * 0x588, every other wrong word a pure -8 branch displacement): the widget id
 * carried across the nine-term `||` chain is an `s32` local NARROWED AT ITS
 * USE, `func_28EDE0(&D_004842E8, (u16)w, 0)` -- retail assigns it with a bare
 * `ori $16,$0,0x88BB` / `ori $16,$0,0x88C0` and masks once, `andi $5,$16,
 * 0xFFFF`, at the call.  Declaring the local `u16` instead masks at EVERY
 * ASSIGNMENT (`ori $3,$0,K` + `andi $16,$3,0xFFFF`), which is the two extra
 * words.  Note 0x88BB > 0x7FFF, so an s32 assignment still emits `ori`, not
 * `addiu` -- the constant's materialisation is unchanged by the widening.
 *
 * The switch compiles to a compare chain, not a jump table: the object has no
 * .rodata, no .lit4 and no .sdata, so this unit needs NO link plumbing.
 */

typedef struct Kind Kind;
struct Kind {
    u8  pad00[8];
    s32 field08;
};

typedef struct Ctx Ctx;
struct Ctx {
    u8   pad0000[0x1188];
    Kind *field1188;
};

typedef struct Handle Handle;
struct Handle {
    u8  pad00[0x24];
    Ctx *field24;
};

extern const u8 D_004FA1A0[];
extern const u8 D_004B2570[];
extern const u8 D_004B27E0[];

extern s32 D_00484394;          /* gp - 0xDDC */
extern s32 D_00484398;          /* gp - 0xDD8 */
extern u8  D_00484344;          /* gp - 0xE2C */
extern u8  D_00484348;          /* gp - 0xE28 */
extern u8  D_004842E8;          /* gp - 0xE88, passed by address */

extern s32  func_37B970(void);
extern u8   func_37B9B0(s32 a);
extern void insmenu_InsectVsSaveSetError_4f6e20(s32 a);
extern void insmenu_InsectVsSaveShowMsg_4f6e00(s32 a, s32 b, s32 c);
extern void insmenu_InsectVsLoadYesNoCursorBob_4f69e0(s32 a, s32 b, s32 c);
extern void func_37B460(s32 a);
extern s32  func_2F6660(void);
extern s32  func_1839F0(const void *a, s32 b);
extern s32  func_2882C0(void);
extern void func_376B20(s32 a);
extern void func_28EA90(const void *a, s32 b, s32 c);
extern void func_377180(s32 *a);
extern void func_37B9E0(s32 a);
extern void insmenu_InsectVsSaveProgressWindowShow_4f6b90(s32 a, s32 b);
extern s32  func_37BAA0(void);
extern void *insmenu_InsectVsGetSaveCtx_4f3850(void);
extern void func_373840(void *dst, void *s);
extern void *insmenu_InsectVsGetLoadSysMsgBuf_4f9700(void);
extern void func_1319A8(void *dst, void *src, s32 n);
extern Handle *func_1FEDE0(void);
extern void func_430DB0(Ctx *c, s32 a);
extern void func_28EDE0(void *a, s32 b, s32 c);

s32 insmenu_InsectVsLoadConfirmCb_4f55c0(void)
{
    u8 buf[0x70];
    Handle *hnd;
    s32 id;
    s32 st;
    s32 w;

    if (D_00484394 != 4 && D_00484394 != 3) {
        st = func_37B970();
        if (func_37B9B0(1) == 0 || st == 6 || st == 5 || st == 8) {
            insmenu_InsectVsSaveSetError_4f6e20(8);
            return 1;
        }
    }
    switch (D_00484394) {
    case 0:
        if (D_00484344 != 0) {
            insmenu_InsectVsSaveShowMsg_4f6e00(0x1F4, 0, -1);
            D_00484398 = 0;
            insmenu_InsectVsLoadYesNoCursorBob_4f69e0(0, 1, 0);
            func_37B460(0x890D);
        } else {
            insmenu_InsectVsSaveShowMsg_4f6e00(0x15, 0, -1);
            D_00484398 = 0;
            insmenu_InsectVsLoadYesNoCursorBob_4f69e0(0, 1, 1);
            func_37B460(0x890D);
        }
        D_00484394 = 1;
        break;
    case 1:
        if (D_00484344 != 0) {
            if (func_2F6660() != 0) {
                break;
            }
            if (func_1839F0(D_004B2570, 0x60) != 0 ||
                (func_2882C0() != 0 && func_1839F0(D_004B27E0, 0x60) != 0)) {
                D_00484344 = 0;
                insmenu_InsectVsSaveShowMsg_4f6e00(-1, 0, -1);
                func_376B20(5);
                func_28EA90(D_004FA1A0, 0x88BB, 0);
            }
        } else {
            func_377180(&D_00484398);
            insmenu_InsectVsLoadYesNoCursorBob_4f69e0(D_00484398, 0, 1);
            if (func_2F6660() != 0) {
                break;
            }
            if ((func_1839F0(D_004B2570, 0x20) != 0 ||
                 (func_2882C0() != 0 && func_1839F0(D_004B27E0, 0x20) != 0)) ||
                ((func_1839F0(D_004B2570, 0x40) != 0 ||
                  (func_2882C0() != 0 && func_1839F0(D_004B27E0, 0x40) != 0)) &&
                 D_00484398 == 1)) {
                insmenu_InsectVsLoadYesNoCursorBob_4f69e0(D_00484398, 0, 0);
                func_376B20(6);
                insmenu_InsectVsSaveShowMsg_4f6e00(-1, 0, -1);
                func_28EA90(D_004FA1A0, 0x88BB, 0);
            } else if (func_1839F0(D_004B2570, 0x40) != 0 ||
                       (func_2882C0() != 0 &&
                        func_1839F0(D_004B27E0, 0x40) != 0)) {
                insmenu_InsectVsLoadYesNoCursorBob_4f69e0(D_00484398, 0, 0);
                func_376B20(5);
                D_00484394 = 2;
            }
        }
        break;
    case 2:
        func_37B9E0(5);
        insmenu_InsectVsSaveProgressWindowShow_4f6b90(2, 1);
        insmenu_InsectVsSaveShowMsg_4f6e00(7, 0, -1);
        D_00484394 = 3;
        break;
    case 3:
        if (func_37BAA0() == 0) {
            break;
        }
        insmenu_InsectVsSaveProgressWindowShow_4f6b90(2, 0);
        st = func_37B970();
        if (st == 0) {
            if (func_37B9B0(0) == 1) {
                func_376B20(0x23);
                insmenu_InsectVsSaveShowMsg_4f6e00(0x16, 0, -1);
                func_373840(buf, insmenu_InsectVsGetSaveCtx_4f3850());
                func_1319A8(insmenu_InsectVsGetLoadSysMsgBuf_4f9700(), buf, 0x70);
                D_00484394 = 4;
                break;
            }
        }
        if (st == 5 || st == 6 || st == 8 || st == 2 || st == 3) {
            insmenu_InsectVsSaveSetError_4f6e20(0xE);
        } else if (st == 1) {
            insmenu_InsectVsSaveSetError_4f6e20(1);
        } else {
            insmenu_InsectVsSaveSetError_4f6e20(5);
        }
        break;
    case 4:
        if (func_2F6660() != 0) {
            break;
        }
        if (func_1839F0(D_004B2570, 0x60) != 0 ||
            (func_2882C0() != 0 && func_1839F0(D_004B27E0, 0x60) != 0)) {
            insmenu_InsectVsSaveShowMsg_4f6e00(-1, 0, -1);
            hnd = func_1FEDE0();
            id = hnd->field24->field1188->field08;
            w = 0x88BB;
            if (id == 0x268 || id == 0x25D || id == 0x25A || id == 0x264 ||
                id == 0x26E || id == 0x278 || id == 0x1F6 || id == 0x1F7 ||
                id == 0x193) {
                w = 0x88C0;
            } else {
                D_00484348 = 1;
            }
            if (id == 0x26E) {
                func_430DB0(hnd->field24, 0x26F);
            }
            func_28EDE0(&D_004842E8, (u16)w, 0);
        }
        break;
    }
    return 1;
}
