#include "types.h"
/* normal 0x00520E80 -- opens the shop/menu widget set: sizes and shows a stack
 * of widget ids off the gp session pointer, then hands a four-word block to
 * func_2A33E0.  $4 is unused; the guard is on the SECOND parameter.
 * 0x3F800000 is 1.0f and 0x3D800000 0.0625f. */

typedef struct Sess {
    u8  pad000[0x10];
    s8  f010;
    s8  f011;
} Sess;

extern void *D_00484920;          /* gp - 0x850, the widget-system handle */
extern Sess *D_00484934;          /* gp - 0x83C */
extern s32   D_00484928;          /* gp - 0x848, address taken */
extern s32   D_00484948;          /* gp - 0x828 */
extern s8    D_00484954;          /* gp - 0x81C */
extern s32   D_0048494C;          /* gp - 0x824 */
extern s32   D_00484950;          /* gp - 0x820 */
extern f32   D_0047DD34;          /* gp - 0x743C */
extern const u8 D_00528060[];

typedef struct Widget { u8 pad000[0x20]; void *f020; } Widget;

extern Widget *func_290460(void *a, s32 id);
extern void func_28D580(void *a, s32 b, s32 c, s32 d, s32 e, s32 f);
extern void func_290010(void *a, s32 id, s32 c, s32 d);
extern void func_290F60(void *a, s32 id, s32 c, s32 d);
extern void func_290690(void *a, s32 id, f32 x, f32 y, f32 z);
extern void func_291110(void *a, s32 id, s32 c, s32 d);
extern void func_2907A0(void *a, s32 id, f32 x);
extern void func_28DA30(const void *a, void *b, s32 id);
extern void func_28DB40(const void *a, s32 id, s32 c, s32 d, s32 e, s32 f,
                        s32 g, s32 h);
extern void func_28D9D0(const void *a);
extern void func_28D9C0(const void *a, s32 b);
extern void normal_ThinkMenuTabsLayout_520500(s32 id, s32 b);
extern void func_2A4B40(Sess *a, s32 id);
extern void func_2A3D90(Sess *a, s32 id);
typedef struct Rec { u8 pad000[0x18]; s32 f018; } Rec;
extern Rec *func_1FEDE0(void);
extern s32  func_3C86E0(s32 a, s32 b, s32 c, s32 d, s32 e, s32 f);
extern void func_131B60(void *a, s32 b, s32 c);
extern s32  func_28FE10(void *a, s32 id, s32 c);
extern s32  func_28F620(void *a, s32 id, s32 c);
extern void func_2A33E0(Sess *a, s32 b, s32 c, s32 d, s32 *e, s32 f, s32 g,
                        s32 h, f32 x);
extern void func_28EDE0(void *a, s32 id, s32 c);

s32 normal_ThinkMenuOpenState_520e80(void *unused, s32 show)
{
    s32 v[4];
    s32 t;

    if (show != 0) {
        func_28D580(func_290460(D_00484920, 0x7532)->f020, 0, 0, 0x186, 0x12D, 0);
        func_290010(D_00484920, 0x7532, 1, -1);
        func_290F60(D_00484920, 0x7532, 0x46, 0x4B);
        func_290690(D_00484920, 0x7532, 1.0f, 0.0625f, 0.0f);
        func_291110(D_00484920, 0x7531, 1, 1);
        func_290F60(D_00484920, 0x7531, 0, 8);
        func_290690(D_00484920, 0x7531, 1.0f, 0.0625f, 0.0f);
        func_290F60(D_00484920, 0x7548, 0, 8);
        func_291110(D_00484920, 0x753D, 1, 1);
        func_2907A0(D_00484920, 0x753D, 0.0f);
        func_290F60(D_00484920, 0x753D, 0x4D, 0x160);
        func_290F60(D_00484920, 0x753A, 0x3E, 0x35);
        func_28DA30(D_00528060, D_00484920, 0x753B);
        func_28DB40(D_00528060, 0x753B, 0x18, 0x18, 0x2A, 0x30, 0x46, 0x4B);
        func_28D9D0(D_00528060);
        func_28D9C0(D_00528060, 1);
        D_00484934->f010 = 6;
        D_00484934->f011 = 0;
        normal_ThinkMenuTabsLayout_520500(0x7535, 0);
        func_2A4B40(D_00484934, 0x7539);
        func_2A3D90(D_00484934, 0x753A);
        t = func_3C86E0(func_1FEDE0()->f018, 0, 0, 0, 0, 0);
        func_131B60(v, 0, 0x10);
        v[0] = func_28FE10(D_00484920, 0x7546, 0);
        v[1] = func_28FE10(D_00484920, 0x7545, 0);
        v[2] = func_28F620(D_00484920, 0x7545, 0);
        v[3] = func_28FE10(D_00484920, 0x7547, 0);
        func_2A33E0(D_00484934, t, 0x7540, 0x753D, v, 0x4D, 0x160, -1, D_0047DD34);
        D_00484948 = 1;
        D_00484954 = 1;
        D_0048494C = -1;
        D_00484950 = -1;
    }
    func_28EDE0(&D_00484928, 0x7532, 1);
    return 1;
}
