/* rgp:protos */
#define RGP_SELF_ObjTypeVehicleIsTargetActive_337b00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

s32 ObjTypeVehicleIsTargetActive_337b00(void *arg0)
{
    if (TargetRefIsValid_2e6e40((u8 *)arg0 + 0xA0) == 0) {
        return 0;
    }
    if (TargetRefGetObj_2e7110((u8 *)arg0 + 0xE0) == 0) {
        return 0;
    }
    if (*(s32 *)((u8 *)arg0 + 0x118) == 0) {
        return 0;
    }
    if (*(s32 *)((u8 *)arg0 + 0x11C) == 0) {
        return 0;
    }
    return *(s32 *)((u8 *)arg0 + 0x110) != 0;
}
