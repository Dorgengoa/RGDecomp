#include "types.h"

extern s32 TargetRefGetKind_2e7130(u8 *);
extern s32 TargetRefGetId_2e7120(u8 *);
extern void ObjTypeMonographSetMagnetOffTime_372730(u8 *, f32);

void ObjTypeMonographSetMagnetOffIfTarget_3726b0(u8 *p, s32 p1, f32 t)
{
    s32 r;
    s32 s;

    r = TargetRefGetKind_2e7130(p + 0xA0);
    switch (r) {
    case 4:
    case 5:
        break;
    default:
        return;
    }
    s = TargetRefGetId_2e7120(p + 0xA0);
    if (p1 == s) {
        ObjTypeMonographSetMagnetOffTime_372730(p, t);
    }
}
