/* rgp:protos */
#define RGP_SELF_EvMapObjIsTargetActive_365620 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_repositioncode off
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvMapObjIsTargetActive_365620(u8 *arg0) {
    s32 p;
    s32 i;

    if (EvMapObjGetModel_366bb0((void *)arg0) == 0) {
        return 0;
    }
    if (TargetRefGetMapObj_2e7050(arg0 + 0xA0) == 0) {
        return 0;
    }
    p = *(s32 *)(arg0 + 0x2F4);
    for (i = 0; i < *(s16 *)(arg0 + 0x2FC); i++, p += 0x150) {
        if (EvMapObjNodeGetFrame_3673d0(p) == 0) {
            return 0;
        }
    }
    return 1;
}
