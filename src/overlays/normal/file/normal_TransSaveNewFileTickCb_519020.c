#include "types.h"
/* normal 0x00519020 -- the ending/credits state pump.  One s16 state word in
 * gp small data (D_00484810) drives an if/else-if chain tested in DESCENDING
 * order (0x67, 0x66, 0x65, 0x64, 3, 2, 1, 0), which is why this is a chain and
 * not a switch: mwcc sorts a compiled switch ASCENDING.
 * The preamble runs BEFORE the chain and re-reads the state word afterwards,
 * so every arm reads the global directly rather than a cached local.
 * `daddiu`-free: every constant here is an addiu, so the ids are s32.
 * 0x4B2570 is passed BY NAME (an incomplete extern array) -- a cast literal
 * would come out lui/ori instead of lui/addiu. */

extern const u8 D_004B2570[];

extern f32   D_0047D34C;      /* gp - 0x7E24 */
extern void *D_00484724;      /* gp - 0xA4C  */
extern void *D_004847D4;      /* gp - 0x99C  */
extern void *D_004847D8;      /* gp - 0x998  */
extern s32   D_004847F0;      /* gp - 0x980  */
extern s32   D_004847F4;      /* gp - 0x97C  */
extern s16   D_00484810;      /* gp - 0x960  */
extern s32   D_00484814;      /* gp - 0x95C  */
extern s32   D_00484818;      /* gp - 0x958  */

extern s32  func_1839F0(const void *a, s32 b);
extern void func_28EA90(void *a, s32 b, s32 c);
extern void func_290690(void *a, s32 b, f32 x, f32 y, f32 z);
extern s32  func_2F6660(void);
extern void func_373580(void *a);
extern void func_376B20(s32 a);
extern void func_377180(void *a);
extern void func_37B460(s32 a);
extern s32  func_37B970(void);
extern u8   func_37B9B0(s32 a);
extern void func_37B9E0(s32 a);
extern s32  func_37BAA0(void);
extern void normal_TransSaveYesNoCursorBob_5188c0(s32 a, s32 b, s32 c);
extern void normal_TransSaveProgressWindowShow_519e50(s32 a, s32 b);
extern void normal_TransSaveShowMsg_519ff0(s32 a);
extern void normal_TransSaveSetError_51a000(s32 a);

s32 normal_TransSaveNewFileTickCb_519020(void)
{
    s32 t;

    if (D_00484810 != 0x67 && D_00484810 != 3) {
        t = func_37B970();
        if (func_37B9B0(1) == 0 || t == 6 || t == 5 || t == 8) {
            normal_TransSaveSetError_51a000(8);
            return 1;
        }
    }

    switch (D_00484810) {
    case 0:
        normal_TransSaveShowMsg_519ff0(8);
        D_00484814 = 1;
        normal_TransSaveYesNoCursorBob_5188c0(1, 1, 1);
        func_37B460(0x75A2);
        D_00484810 = D_00484810 + 1;
        break;
    case 1:
        func_377180(&D_00484814);
        normal_TransSaveYesNoCursorBob_5188c0(D_00484814, 0, 1);
        if (func_2F6660() == 0) {
            if (func_1839F0(D_004B2570, D_004847F4) != 0 ||
                (func_1839F0(D_004B2570, D_004847F0) != 0 && D_00484814 == 1)) {
                normal_TransSaveYesNoCursorBob_5188c0(D_00484814, 1, 0);
                func_376B20(6);
                normal_TransSaveShowMsg_519ff0(-1);
                func_28EA90(D_004847D8, 4, 0);
            } else if (func_1839F0(D_004B2570, D_004847F0) != 0) {
                normal_TransSaveYesNoCursorBob_5188c0(D_00484814, 1, 0);
                func_376B20(5);
                normal_TransSaveProgressWindowShow_519e50(0, 0);
                D_00484810 = D_00484810 + 1;
            }
        }
        break;
    case 2:
        func_290690(D_004847D4, 0x75A2, 0.0f, D_0047D34C, -1.0f);
        normal_TransSaveProgressWindowShow_519e50(0, 1);
        func_37B9E0(2);
        normal_TransSaveShowMsg_519ff0(6);
        D_00484810 = D_00484810 + 1;
        break;
    case 3:
        if (func_37BAA0() != 0) {
            t = func_37B970();
            if (t == 6 || t == 5 || t == 8) {
                func_376B20(0x24);
                normal_TransSaveSetError_51a000(6);
            } else {
                func_28EA90(D_004847D8, 6, 0);
                D_00484818 = 2;
            }
        }
        break;
    case 0x64:
        normal_TransSaveShowMsg_519ff0(4);
        D_00484814 = 1;
        normal_TransSaveYesNoCursorBob_5188c0(1, 1, 1);
        func_37B460(0x75A2);
        D_00484810 = D_00484810 + 1;
        break;
    case 0x65:
        func_377180(&D_00484814);
        normal_TransSaveYesNoCursorBob_5188c0(D_00484814, 0, 1);
        if (func_2F6660() == 0) {
            if (func_1839F0(D_004B2570, D_004847F4) != 0 ||
                (func_1839F0(D_004B2570, D_004847F0) != 0 && D_00484814 == 1)) {
                normal_TransSaveYesNoCursorBob_5188c0(D_00484814, 1, 0);
                func_376B20(6);
                normal_TransSaveShowMsg_519ff0(-1);
                func_28EA90(D_004847D8, 4, 0);
            } else if (func_1839F0(D_004B2570, D_004847F0) != 0) {
                normal_TransSaveYesNoCursorBob_5188c0(D_00484814, 1, 0);
                func_376B20(5);
                D_00484810 = D_00484810 + 1;
            }
        }
        break;
    case 0x66:
        func_37B9E0(6);
        normal_TransSaveShowMsg_519ff0(0x10);
        normal_TransSaveProgressWindowShow_519e50(3, 1);
        D_00484810 = D_00484810 + 1;
        break;
    case 0x67:
        if (func_37BAA0() != 0) {
            t = func_37B970();
            if (t == 5 || t == 6 || t == 8) {
                normal_TransSaveSetError_51a000(0xD);
                func_376B20(0x24);
            } else {
                D_00484810 = 2;
                func_373580(D_00484724);
            }
        }
        break;
    }
    return 1;
}
