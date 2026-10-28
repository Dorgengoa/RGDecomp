/* rgp:protos */
#define RGP_SELF_LoaderQueueFindUnitById_1cdc70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/                    /* extern */
/*rgp*/                              /* extern */
/*rgp*/                             /* extern */

u8 *LoaderQueueFindUnitById_1cdc70(u8 *arg0, s32 arg1, s32 arg2, s32 *arg3) {
    s16 *list;
    s32 n;
    s32 i;
    u8 *e;

    if ((*(s32 *)(arg0 + 0x10) == 0) || (arg1 < 0) || (arg2 == 0)) {
        return 0;
    }
    list = ((s16 *)S16ArrayGetData_1ce1c0(arg2));
    if (list == 0) {
        return 0;
    }
    n = ((short)S16ArrayGetCount_1ce1b0(arg2));
    for (i = 0; i < n; i++, list++) {
        e = ((u8 *)LoaderGetUnit_1cde10(arg0, *list));
        if ((e != 0) && (*(s16 *)(e + 0x80) == arg1)) {
            if (arg3 != 0) {
                *arg3 = i;
            }
            return e;
        }
    }
    return 0;
}
