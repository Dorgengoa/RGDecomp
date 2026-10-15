#include "types.h"
/* normal 0x0051A3C0 -- the 0x753x/0x75Ax menu group's open, then a two-phase
 * fade ramp on the s8 phase at gp-0x994.
 * m2c renders the phase test as an irregular `switch`; the listing is a plain
 * compare CHAIN (`bnel $3,$0` then `bne $3,$2`), so it is if / else-if.
 * `func_290D30`'s result is masked with `andi 0xFF`, i.e. it returns u8.
 * The `cnt = l->f034; cnt = cnt - n;` SPLIT is load-bearing: written as one
 * statement mwcc emits the two member loads in argument order and the delay
 * slot takes the wrong argument.  Splitting the LOAD from the arithmetic on
 * it is what reorders the group -- 10 other spellings all sat at 5 bad. */

extern void *D_004847D0;          /* gp - 0x9A0 */
extern void *D_004847D4;          /* gp - 0x99C */
extern void *D_004847D8;          /* gp - 0x998 */
extern s32   D_004847F0;          /* gp - 0x980 */
extern s32   D_004847F4;          /* gp - 0x97C */
extern s32   D_004847E4;          /* gp - 0x98C */
extern s8    D_004847DC;          /* gp - 0x994 */
extern f32   D_004847E0;          /* gp - 0x990 */
extern void *D_0048470C;          /* gp - 0xA64 */
extern s32   D_00484710;          /* gp - 0xA60 */
extern void *D_00484720;          /* gp - 0xA50 */
extern s32   D_00484714;          /* gp - 0xA5C */
extern f32   D_0047DA00;          /* gp - 0x7770 */
extern f32   D_0047DA04;          /* gp - 0x776C */
extern f32   D_0047D9A8;          /* gp - 0x77C8 */
extern f32   D_0047D35C;          /* gp - 0x7E14 */
extern f32   D_0047D5D0;          /* gp - 0x7BA0 */

typedef struct Actor {
    u8   pad000[0x4FC];
    s16  f4FC;
} Actor;
extern Actor *D_00484724;         /* gp - 0xA4C */

typedef struct List {
    u8   pad000[0x28];
    s32  f028;
    s32  f02C;
    u8   pad030[4];
    s32  f034;
} List;
extern List *D_004846E0;          /* gp - 0xA90 */

extern void func_14D810(void *it, s32 base, s32 n);
extern void func_14E030(void *it);
extern void func_28EB10(void *p, s32 a);
extern void func_28EDE0(void *p, s32 id, s32 a);
extern void func_290010(void *p, s32 id, s32 c, s32 d);
extern void func_2905B0(void *p, s32 id, f32 r, f32 g, f32 b, f32 a);
extern void func_290690(void *p, s32 id, f32 x, f32 y, f32 z);
extern void func_2907A0(void *p, s32 id, f32 x);
extern u8   func_290D30(void *p, s32 id);
extern void func_290F50(void *p, s32 id, s32 c, s32 d, s32 e, f32 x);
extern void func_290F60(void *p, s32 id, s32 c, s32 d);
extern void func_291110(void *p, s32 id, s32 c, s32 d);
extern void func_3774C0(s32 a);
extern void func_377740(s32 a, s32 b);
extern void func_377790(s32 a);
extern void func_377830(s32 a, s32 b, s32 c, s32 d, s32 e);
extern void func_37B460(s32 a);
extern void func_37BAC0(s32 a);
extern void func_37BC50(s32 a);
extern void func_37BC60(Actor *p, void *it);
extern s32  normal_TransMenuIsQuickOpen_514a00(void);
extern void normal_TransMenuWidgetListShow_514a10(s32 a);
extern void normal_TransSavePanelFade_518700(s32 a);
extern void normal_TransSaveSlotListRefreshMaybe_518a80(s32 a);
extern void normal_TransSaveHighlightOption_519e70(s32 a);
extern void normal_TransSavePortSelectDraw_519e80(s32 a);
extern void normal_TransSaveShowMsg_519ff0(s32 a);

s32 normal_TransSaveOpenState_51a3c0(void *a, s32 b)
{
    u8 it[0x60];
    List *l;
    Actor *p;
    s32 n;
    f32 v;
    s32 cnt;
    s32 base;

    if (b != 0) {
        func_14E030(it);
        l = D_004846E0;
        n = l->f02C;
        cnt = l->f034;
        cnt = cnt - n;
        base = l->f028 + (n * 0x10);
        func_14D810(it, base, cnt);
        D_004847F0 = 0x40;
        D_004847F4 = 0x20;
        D_004847D0 = D_0048470C;
        D_004847D4 = (void *)D_00484710;
        D_004847D8 = D_00484720;
        D_004847E4 = 0;
        func_37BC50(D_00484710);
        func_37BC60(D_00484724, it);
        func_377790(0x80EB);
        func_3774C0(0x80EA);
        if (normal_TransMenuIsQuickOpen_514a00() != 0) {
            p = D_00484724;
            if (p != 0) {
                p->f4FC = 1;
            }
        }
        func_28EB10(D_004847D8, 4);
        func_377740(D_00484714, 0);
        normal_TransSavePortSelectDraw_519e80(-1);
        normal_TransSaveHighlightOption_519e70(-1);
        func_290F60(D_004847D4, 0x753B, -0x12, 0xC);
        func_290F60(D_004847D4, 0x7536, -0xF, 0xF);
        func_290F50(D_004847D4, 0x753B, 0x5A, 0xC, 0, 0.25f);
        func_290F50(D_004847D4, 0x7536, 0x5D, 0xF, 0, 0.25f);
        func_290690(D_004847D4, 0x7553, 1.0f, D_0047DA00, -1.0f);
        func_291110(D_004847D4, 0x7531, 1, 1);
        func_2907A0(D_004847D4, 0x7531, 1.0f);
        func_290690(D_004847D4, 0x7531, 1.0f, D_0047DA00, -1.0f);
        D_004847DC = 0;
        D_004847E0 = 0.0f;
        normal_TransMenuWidgetListShow_514a10(1);
        func_290010(D_004847D4, 0x759E, 1, -1);
        func_290F60(D_004847D4, 0x7558, 0xC8, 0);
        func_290F60(D_004847D4, 0x7562, 0x38, 0x49);
        func_290F60(D_004847D4, 0x7576, 0x38, 0xC0);
        func_290F60(D_004847D4, 0x758A, 0x38, 0x137);
        func_290F60(D_004847D4, 0x75A0, 0x1E5, 0x4A);
        func_290F60(D_004847D4, 0x75A1, 0x1E9, 0x4C);
        func_290F60(D_004847D4, 0x759E, 0x117, 0x1F);
        func_37B460(0x75A2);
        normal_TransSaveSlotListRefreshMaybe_518a80(0);
        normal_TransSaveHighlightOption_519e70(-1);
        func_377830(0x75A1, 0x15B, 3, 0x32, 0);
        func_2907A0(D_004847D4, 0x7558, 0.0f);
        normal_TransSavePanelFade_518700(0);
        normal_TransSaveShowMsg_519ff0(-1);
    }
    func_37BAC0(0);
    if (D_004847DC == 0) {
        v = D_004847E0 + D_0047D9A8;
        D_004847E0 = v;
        if (!(v < D_0047D35C)) {
            D_004847DC = 1;
            D_004847E0 = D_0047D35C;
            func_290690(D_004847D4, 0x7558, 1.0f, D_0047DA04, -1.0f);
            func_290F50(D_004847D4, 0x7558, 0, 0, 0, D_0047D5D0);
        }
    } else if (D_004847DC == 1) {
        D_004847E0 = D_004847E0 - D_0047D9A8;
    }
    v = D_004847E0;
    func_2905B0(D_004847D4, 0x7553, v, v, v, 1.0f);
    if (D_004847E0 <= 1.0f) {
        if (D_004847DC == 1) {
            D_004847E0 = 1.0f;
            func_2905B0(D_004847D4, 0x7553, 1.0f, 1.0f, 1.0f, 1.0f);
            if (func_290D30(D_004847D4, 0x7558) == 0) {
                func_28EDE0(D_004847D0, 6, 0);
            }
        }
    }
    return 1;
}
