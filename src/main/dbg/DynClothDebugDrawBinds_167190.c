/* PARK (round 1): length 0x1CC vs retail 0x1BC, close. */
#include "types.h"
#pragma opt_common_subs off

#define S16(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define S32(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define PTR(p, o) (*(void **)((u8 *)(p) + (o)))

extern void GsPktSetOriginMode_13e2f0(s32, s32);
extern void GsPktSetTextured_13e400(s32, s32);
extern void GsPktSetZWriteMask_13e430(s32, s32);
extern void GsPktEnableZTest_13e460(s32, s32);
extern void GsPktSetRGBAQ_13ee40(s32, s32, s32, s32, s32);
extern void GsPktSetXYZVecI_13eeb0(s32, void *);
extern void GsPktClose_13f5b0(s32);
extern void GsPktOpenPrim_13f730(s32, s32);
extern void DrawListEndPrim_141a20(s32);
extern s32 DrawListBeginPrim_141b00(s32);
extern void ProjectToScreen_15d340(void *, void *);
extern s32 GetDrawCtx_15de80(void);

void DynClothDebugDrawBinds_167190(void *arg0)
{
    u8 sp70[0x10];
    u8 sp60[0x10];
    s32 temp_2;
    s32 temp_2_2;
    s32 var_20;
    s32 var_20_2;
    void *temp_19;
    void *temp_19_2;

    temp_2 = GetDrawCtx_15de80();
    temp_2_2 = DrawListBeginPrim_141b00(temp_2);
    GsPktEnableZTest_13e460(temp_2_2, 0);
    GsPktSetZWriteMask_13e430(temp_2_2, 1);
    GsPktSetTextured_13e400(temp_2_2, 0);
    GsPktSetOriginMode_13e2f0(temp_2_2, 1);
    var_20 = 0;
    while (var_20 < S32(arg0, 0xD4)) {
        GsPktOpenPrim_13f730(temp_2_2, 1);
        temp_19 = (u8 *)PTR(arg0, 0xD8) + (var_20 * 0x10);
        GsPktSetRGBAQ_13ee40(temp_2_2, 0x80, 0x64, 0x50, 0x40);
        ProjectToScreen_15d340(sp70, (u8 *)PTR(arg0, 0xA8) + (S32(temp_19, 0) * 0x10));
        GsPktSetXYZVecI_13eeb0(temp_2_2, sp70);
        ProjectToScreen_15d340(sp70, (u8 *)PTR(arg0, 0xA8) + (S32(temp_19, 4) * 0x10));
        GsPktSetXYZVecI_13eeb0(temp_2_2, sp70);
        GsPktClose_13f5b0(temp_2_2);
        var_20 += 1;
    }
    var_20_2 = 0;
    while (var_20_2 < S32(arg0, 0xDC)) {
        GsPktOpenPrim_13f730(temp_2_2, 1);
        temp_19_2 = (u8 *)PTR(arg0, 0xE0) + (var_20_2 << 5);
        GsPktSetRGBAQ_13ee40(temp_2_2, 0x20, 0x3C, 0x1E, 0x40);
        ProjectToScreen_15d340(sp60, (u8 *)PTR(arg0, 0xA8) + (S32(temp_19_2, 0) * 0x10));
        GsPktSetXYZVecI_13eeb0(temp_2_2, sp60);
        ProjectToScreen_15d340(sp60, (u8 *)PTR(arg0, 0xA8) + (S32(temp_19_2, 4) * 0x10));
        GsPktSetXYZVecI_13eeb0(temp_2_2, sp60);
        GsPktClose_13f5b0(temp_2_2);
        var_20_2 += 1;
    }
    DrawListEndPrim_141a20(temp_2);
}
