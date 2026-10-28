/* rgp:protos */
#define RGP_SELF_CharaCanActMaybe_210500 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

s32 CharaCanActMaybe_210500(void *arg0)
{
    s16 m;
    s32 t;

    if (!(*(s32 *)((u8 *)arg0 + 0x3D8) & 1)) {
        return 0;
    }
    if (*(s16 *)((u8 *)arg0 + 0xA38) != 0) {
        m = *(s16 *)((u8 *)arg0 + 0xA36);
        if (m == 2) {
            return 0;
        }
        if (m == 30) {
            return 0;
        }
        if (m == 31) {
            return 0;
        }
    }
    if (*(s16 *)((u8 *)arg0 + 0xA2E) != 0) {
        return 0;
    }
    if (*(s16 *)((u8 *)arg0 + 0xA32) != 0) {
        return 0;
    }
    t = MapSlotsFindById_1e4b90(((s32)GetMapMgr_201a90()), *(s32 *)((u8 *)arg0 + 0xA4C), 0);
    if ((t != 0) && (((unsigned char)MapDataIsJasterOnly_1e7a90(t)) != 0)) {
        return 0;
    }
    return 1;
}
