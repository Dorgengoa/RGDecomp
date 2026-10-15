#include "types.h"

extern s32 TargetRefResolve_2e5ed0(void *arg0, s32 arg1);
extern void TargetRefSetMapNode_2e6370(void *arg0, f32 arg1);

s32 ObjTypeMonographPlaceOnMapNode_372870(void *arg0, f32 fparg0, f32 fparg1) {
    u8 *p;
    s32 var_3;
    s32 var_2;

    p = (u8 *)arg0;
    *(s32 *)(p + 0xD0) = *(s32 *)(p + 0xD0) | 0x80000000;
    TargetRefSetMapNode_2e6370(p + 0xA0, 0.0f);
    if (!(TargetRefResolve_2e5ed0(p + 0xA0, 0) & 0xFF)) {
        var_2 = *(s32 *)(p + 0xD0) | 0x80000000;
    } else {
        var_2 = *(s32 *)(p + 0xD0) & 0x7FFFFFFF;
    }
    *(s32 *)(p + 0xD0) = var_2;
    *(s32 *)(p + 0xF0) = 0;
    *(f32 *)(p + 0x100) = fparg1;
    *(f32 *)(p + 0xFC) = fparg0;
    if (fparg0 >= 0.0f) {
        var_3 = *(s32 *)(p + 0xD0) | 0x800000;
    } else {
        var_3 = *(s32 *)(p + 0xD0) & 0xFF7FFFFF;
    }
    *(s32 *)(p + 0xD0) = var_3;
    return !(var_3 & 0x80000000);
}
