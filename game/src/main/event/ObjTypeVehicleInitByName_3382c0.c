/* rgp:protos */
#define RGP_SELF_ObjTypeVehicleInitByName_3382c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct T3382c0 {
    u8  pad000[0x110];
    s32 f110;
    s16 f114;
    s16 f116;
    s32 f118;
    s32 f11C;
} T3382c0;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void ObjTypeVehicleInitByName_3382c0(T3382c0 *o, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5,
                  s32 a6, s32 a7, s32 s0, s32 s1, s32 s2, s32 s3)
{
    ObjTypeVehicleReset_3383c0(o);
    EvObjInitByName_2f9de0(o, a1, a2 | 0x08000000, a3);
    TargetRefSetMapObj_2e6470((u8 *)o + 0xA0, a4, a5, 0.0f);
    TargetRefSetMapNode_2e6370((u8 *)o + 0xE0, a6, a7, 0.0f);
    o->f118 = ((s32)EventObjMgrFindVolumeRecByName_2e9bc0(((s32)GetEventObjMgr_2d1960()), s0));
    o->f11C = ((s32)EventObjMgrFindPathRecByName_2e9c90(((s32)GetEventObjMgr_2d1960()), s1));
    o->f110 = s2;
    o->f114 = (s16)s3;
}
