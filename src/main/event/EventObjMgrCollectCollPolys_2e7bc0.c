#include "types.h"

extern s32 ObjTypeVehicleCollectCollPolys_337190(u8 *, u8 *, s32, s32, s32);
extern s32 ObjTypeMonographCollectCollPolys_371930(u8 *, u8 *, s32, s32, s32);
extern u8 *DListGetHead_42ea60(s32);
extern u8 *DListGetNext_42eb30(u8 *);

s32 EventObjMgrCollectCollPolys_2e7bc0(s32 o, u8 *arr, s32 cap, s32 arg3, s32 arg4)
{
    s32 n;
    u8 *e;
    s32 i;

    if (arr == 0 || cap <= 0) {
        return 0;
    }
    n = 0;
    for (e = DListGetHead_42ea60(o + 0x60); e != 0; e = DListGetNext_42eb30(e)) {
        n += ObjTypeVehicleCollectCollPolys_337190(e + 0x10, arr + n * 0x60, cap - n, arg3, arg4);
    }
    for (e = DListGetHead_42ea60(o + 0xA0); e != 0; e = DListGetNext_42eb30(e)) {
        n += ObjTypeMonographCollectCollPolys_371930(e + 0x10, arr + n * 0x60, cap - n, arg3, arg4);
    }
    for (i = 0; i < n; i++) {
        *(s32 *)(arr + 0x54) = -1;
        arr += 0x60;
    }
    return n;
}
