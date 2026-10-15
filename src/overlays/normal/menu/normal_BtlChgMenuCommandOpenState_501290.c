#include "types.h"
/* normal 0x00501290 -- the 0x30..0x33/0x40 widget group's open, plus the
 * per-frame 0x2B poll that fills the 0x55F2 record.
 * # `$4` is never read; this is the f(void*, s32) state-handler family.
 * D_004844C8 is a gp array and its declared size is a RELOCATION control,
 * not a bound -- 8 bytes is what keeps it in small data.  Do not "fix" it. */

extern void *D_0048449C;          /* gp - 0xCD4  */
extern void *D_004844A0;          /* gp - 0xCD0  */
extern void *D_00484498;          /* gp - 0xCD8  */
extern s16   D_004844E0;          /* gp - 0xC90  */
extern s16   D_004844DC;          /* gp - 0xC94  */
extern s32   D_004844D8;          /* gp - 0xC98  */
extern u8    D_004844C8[8];       /* gp - 0xCA8 ; size is a relocation control */
extern f32   D_0047D520;          /* gp - 0x7C50 */
extern f32   D_0047D278;          /* gp - 0x7EF8 */

typedef struct Ctx {
    u8   pad000[0x43C];
    s16  f43C;
    u8   pad43E[0x44C - 0x43E];
    s16  f44C;
} Ctx;
extern Ctx *D_00484454;           /* gp - 0xD1C  */

typedef struct Rec {
    u8   pad000[6];
    s16  f006;
    s16  f008;
    u8   pad00A[0x10 - 0xA];
    s16  f010;
    s16  f012;
} Rec;

typedef struct Root {
    u8   pad000[0x18];
    s32  f018;
} Root;

extern Root *func_1FEDE0(void);
extern s32  func_2899B0(Ctx *p, s32 id);
extern void func_28EA90(void *p, s32 id, s32 a);
extern Rec *func_28EC60(void *p);
extern void func_28EDE0(void *p, s32 id, s32 a);
extern void func_290010(void *p, s32 id, s32 c, s32 d);
extern void func_290690(void *p, s32 id, f32 x, f32 y, f32 z);
extern void func_2907A0(void *p, s32 id, f32 x);
extern void func_290F60(void *p, s32 id, s32 c, s32 d);
extern void func_291110(void *p, s32 id, s32 c, s32 d);
extern s32  func_3C2010(s32 a, s32 b, s32 c);
extern s32  func_3C3120(s32 a, s32 b);
extern void normal_BtlChgMenuCommandRowsRefresh_501640(void);
extern void normal_BtlChgMenuStatusIconsUpdate_501a70(s16 a);
extern void normal_BtlChgMenuSetMemberFace_501d40(s32 a, s32 b);
extern void normal_BtlChgMenuCommandPanelSlide_501e90(s32 a, s32 b);
extern void normal_BtlChgMenuCommandCursorPlace_503580(u8 a);
extern void normal_BtlChgPageCommandFrameLayout_505c30(Ctx *p, s32 id, f32 x, f32 y);
extern s32  normal_BtlChgPageGetCommand_505d90(Ctx *p);
extern void normal_BtlChgPageSetCommand_505da0(Ctx *p, s32 a);
extern void normal_BtlChgPageGetCursorPos_505df0(Ctx *p, s32 *x, s32 *y);
extern void normal_BtlChgPageSetCursorPosFromWidget_505e10(Ctx *p, s32 a);
extern s32  normal_BtlChgPageGetMember_505f90(Ctx *p);
extern void *normal_UiPageGetStateMachine_289b40(Ctx *p);
extern void *normal_UiPageGetList_289b50(Ctx *p);
extern void *normal_UiPageGetLayout_289b60(Ctx *p);

s32 normal_BtlChgMenuCommandOpenState_501290(void *a, s32 b)
{
    Root *o;
    s32 mode;
    Rec *r;
    s32 px;
    s32 py;

    o = func_1FEDE0();
    if (o == 0) {
        return 0;
    }
    if (b != 0) {
        D_00484498 = normal_UiPageGetStateMachine_289b40(D_00484454);
        D_0048449C = normal_UiPageGetLayout_289b60(D_00484454);
        D_004844A0 = normal_UiPageGetList_289b50(D_00484454);
        mode = normal_BtlChgPageGetCommand_505d90(D_00484454);
        normal_BtlChgPageSetCommand_505da0(D_00484454, -1);
        func_290010(D_0048449C, 1, 0, -1);
        func_290010(D_0048449C, 0x2B, 1, -1);
        func_290010(D_0048449C, 0x35, 0, -1);
        func_290F60(D_0048449C, 0x33, -0x52, -0x18);
        D_004844E0 = -1;
        D_004844DC = 0;
        normal_BtlChgPageCommandFrameLayout_505c30(D_00484454, 0x2C,
                            (f32)(normal_BtlChgPageGetMember_505f90(D_00484454) * 0x88), -10.0f);
        if (mode != 1) {
            normal_BtlChgMenuCommandPanelSlide_501e90(1, 1);
        }
        normal_BtlChgMenuCommandCursorPlace_503580(D_004844C8[func_3C3120(o->f018, normal_BtlChgPageGetMember_505f90(D_00484454))]);
        normal_BtlChgMenuCommandRowsRefresh_501640();
        D_004844D8 = 0;
        normal_BtlChgMenuSetMemberFace_501d40(0x30, normal_BtlChgPageGetMember_505f90(D_00484454));
        if (mode != 1) {
            func_2907A0(D_0048449C, 0x30, 0.0f);
        }
        func_291110(D_0048449C, 0x30, 1, 1);
        func_290F60(D_0048449C, 0x30, -0x3A, 0x15);
        func_290690(D_0048449C, 0x30, 1.0f, D_0047D520, -1.0f);
        func_2907A0(D_0048449C, 0x33, 0.0f);
        func_290690(D_0048449C, 0x33, 1.0f, D_0047D520, -1.0f);
        D_004844E0 = -1;
        D_004844DC = 0;
        func_291110(D_0048449C, 0x31, 0, 1);
        func_291110(D_0048449C, 0x32, 0, 1);
        func_2907A0(D_0048449C, 0x31, 0.0f);
        func_2907A0(D_0048449C, 0x32, 0.0f);
        D_00484454->f43C = 0;
        normal_BtlChgMenuStatusIconsUpdate_501a70((s16)normal_BtlChgPageGetMember_505f90(D_00484454));
    }
    if (func_2899B0(D_00484454, 0x2B) != 0) {
        if (D_00484454->f44C == 0) {
            func_28EDE0(D_00484498, 0x55F7, 0);
            func_28EA90(D_004844A0, 0x55F2, 0);
            r = func_28EC60(D_004844A0);
            r->f010 = (s16)normal_BtlChgPageGetMember_505f90(D_00484454);
            r->f008 = (s16)(func_3C2010(o->f018, 1, 1) - 1);
            r->f012 = (s16)D_004844C8[func_3C3120(o->f018, normal_BtlChgPageGetMember_505f90(D_00484454))];
            normal_BtlChgPageSetCursorPosFromWidget_505e10(D_00484454, 0x2C);
            func_291110(D_0048449C, 0x40, 1, 1);
            func_290690(D_0048449C, 0x40, D_0047D278, 0.125f, 0.0f);
            normal_BtlChgPageGetCursorPos_505df0(D_00484454, &px, &py);
            func_290F60(D_0048449C, 0x40, px - 0x14, py + (r->f012 * r->f006));
            func_290F60(D_0048449C, 0x31, -0x4E, 0x17);
            func_290F60(D_0048449C, 0x32, 0x30, 0x17);
        }
    }
    return 1;
}
