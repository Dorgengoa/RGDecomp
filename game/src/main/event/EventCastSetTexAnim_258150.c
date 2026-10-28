/* rgp:protos */
#define RGP_SELF_EventCastSetTexAnim_258150 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

s32 EventCastSetTexAnim_258150(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    void *p;
    s32 field;

    if (arg1 < 0 || arg1 >= 0x20) {
        return 0;
    }
    p = (u8 *)arg0 + arg1 * 0x10;
    switch (*(s32 *)p) {
    case 0:
        break;
    default:
        goto ret;
    }
    field = *(s32 *)((u8 *)p + 0xC);
    if (arg2 == 1) {
        ModelObjTexAnimStartByName_1ac590(field, arg3);
    } else if (arg3 != 0) {
        ModelObjTexAnimResetByName_1ac510(field, arg3);
    } else {
        ModelObjTexAnimResetAll_1ac450(field);
    }
ret:
    return 0;
}
