#include "types.h"

extern s32 TargetRefGetKind_2e7130(s32);
extern u8 * TargetRefGetObjSlot_2e70e0(s32);
extern s32 TargetRefGetId_2e7120(s32);
extern s32 ObjTypeVehicleSnapBack_337e80(s32, s32, void *);

void ObjTypeVehicleApplyInitialState_337880(s32 p0)
{
    s32 r0;
    s32 rv5;
    u8 *r1;
    s32 rv4;
    s32 r2;
    s32 r3;

    r0 = TargetRefGetKind_2e7130((p0 + 0xE0));
    rv5 = r0;
    if (r0 == 9) {
        r1 = TargetRefGetObjSlot_2e70e0((p0 + 0xE0));
        rv4 = (s32)r1;
        if (r1 != 0) {
            r2 = TargetRefGetId_2e7120((p0 + 0xE0));
            r3 = ObjTypeVehicleSnapBack_337e80(p0, r2, (r1 + 0xC));
            rv4 = r3;
        }
        rv5 = rv4;
    }
}
