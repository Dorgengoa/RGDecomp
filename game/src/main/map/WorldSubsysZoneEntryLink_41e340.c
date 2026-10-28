/* rgp:protos */
#define RGP_SELF_WorldSubsysZoneEntryLink_41e340 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
extern s32 D_004644A8[];

s32 WorldSubsysZoneEntryLink_41e340(void *arg0, void *arg1) {
    s16 t5;
    s32 t3;
    void *result;

    if (arg1 == 0) {
        return 0;
    }
    t5 = *(s16 *)((u8 *)arg1 + 0x10);
    if ((t5 < 0) || (t5 >= D_004644A8[0])) return 0;
    t3 = *(s32 *)((u8 *)arg0 + 0x8);
    result = 0;
    if (t3 != 0) {
        result = (u8 *)t3 + t5 * 0x98;
    }
    if (result != 0) {
        WorldSubsysLinkIds_41ebe0(result, *(s32 *)((u8 *)arg0 + 0x4), arg1, arg0);
    }
    return 1;
}
