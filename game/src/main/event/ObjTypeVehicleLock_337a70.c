/* rgp:protos */
#define RGP_SELF_ObjTypeVehicleLock_337a70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

void ObjTypeVehicleLock_337a70(void *arg0) {
    s32 temp_5;
    s32 z;

    temp_5 = *(s32 *)((u8 *)arg0 + 0xD0);
    z = !(temp_5 & 0x80000000);
    if (z && (temp_5 & 0x02000000) &&
        (((short)ObjTypeVehicleGetPlayState_3380a0(arg0)) != 0) && (((short)ObjTypeVehicleGetPlayState_3380a0(arg0)) != 2) &&
        (*(s16 *)((u8 *)(*(void **)((u8 *)GetGameData_1fede0() + 0x18)) + 4) != 2)) {
        TargetRefSetAreaFlag2_2e6790((u8 *)arg0 + 0xA0);
    }
}
