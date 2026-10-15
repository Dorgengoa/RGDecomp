#include "types.h"

s32 ConstructNewArray_100710(s32, void *, s32, s32, s32);
s32 MemStackNew_14e1b0(s32, s32);
s32 TargetRefCopy_2e7140(void *, s32, s32);
s32 EvObjInit_2f9cf0(void *, s32, s32, s32, s32, s32);
s32 ObjTypeVehicleGetTargetPairCount_338030(s32);
s32 ObjTypeVehicleGetTargetPairs_338040(s32);
s32 ObjTypeVehicleGetTargetPairAt_338050(s32, s32);
s32 ObjTypeVehicleGetPathRec_3380b0(s32);
s32 ObjTypeVehicleGetVolumeRec_3380c0(s32);
s32 ObjTypeVehicleGetTargetRef_3380d0(s32);
void ObjTypeVehicleReset_3383c0(void);
s32 TargetRefPairCopy_3385d0(s32, s32, s32);
extern u8 TargetRefPairCtor_338760[];

s32 ObjTypeVehicleInit_3380e0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s16 n;
    s32 p;
    s32 i;
    s32 t;
    s32 q;

    ObjTypeVehicleReset_3383c0();
    if (arg2 == 0 || arg3 == 0) {
        return 0;
    }
    if (EvObjInit_2f9cf0(arg0, arg1, arg2, arg3, arg4, arg5) == 0) {
        return 0;
    }
    t = ObjTypeVehicleGetVolumeRec_3380c0(arg2);
    *(s32 *)(arg0 + 0x118) = t;
    if (t == 0) {
        return 0;
    }
    t = ObjTypeVehicleGetPathRec_3380b0(arg2);
    *(s32 *)(arg0 + 0x11C) = t;
    if (t == 0) {
        return 0;
    }
    if (TargetRefCopy_2e7140(arg0 + 0xE0, ObjTypeVehicleGetTargetRef_3380d0(arg2), arg3) == 0) {
        return 0;
    }
    if (ObjTypeVehicleGetTargetPairs_338040(arg2) == 0 || ObjTypeVehicleGetTargetPairCount_338030(arg2) <= 0) {
        return 0;
    }
    n = ObjTypeVehicleGetTargetPairCount_338030(arg2);
    *(s16 *)(arg0 + 0x114) = n;
    *(s32 *)(arg0 + 0x110) = ConstructNewArray_100710(MemStackNew_14e1b0(n * 100 + 0x10, arg3), TargetRefPairCtor_338760, 0, 100, n);
    if (*(s32 *)(arg0 + 0x110) == 0) {
        return 0;
    }
    p = *(s32 *)(arg0 + 0x110);
    i = 0;
    while (i < *(s16 *)(arg0 + 0x114)) {
        if (TargetRefPairCopy_3385d0(p, ObjTypeVehicleGetTargetPairAt_338050(arg2, i), arg3) == 0) {
            return 0;
        }
        i++;
        p += 100;
    }
    return 1;
}
