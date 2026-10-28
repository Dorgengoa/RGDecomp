/* rgp:protos */
#define RGP_SELF_MenuObjOtherIdleExists_390ba0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern void *D_004832AC;

s32 MenuObjOtherIdleExists_390ba0(s32 arg0) {
    u8 *p;
    s32 i;
    s32 v;

    if (arg0 == 0) {
        return 0;
    }
    i = 0;
    p = (u8 *)D_004832AC;
    while (i < 5) {
        if (*(s8 *)(p + 0x985) != 0) {
            if ((s32)p == arg0) {
                goto next;
            }
            v = *(s32 *)(p + 0x9C4) != 0;
            if (v) {
                goto next;
            }
            v = *(s32 *)(p + 0x9C8) != 0;
            if (v) {
                goto next;
            }
            return 1;
        }
    next:
        i += 1;
        p += 0x9D0;
    }
    return 0;
}
