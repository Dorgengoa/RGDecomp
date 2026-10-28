/* rgp:protos */
#define RGP_SELF_ArenaStrDup_3701d0 1
#include "port/game_protos.h"
#line 1
/* MATCH (s41m). Stale pre-match note follows -- PARK: length 0xD4 vs retail 0xDC (8 short) after 1 round. Not re-tried. */
#include "types.h"

/*rgp*/
extern s32 strlen(s8 *arg0);
extern void strncpy(void *arg0, s8 *arg1, s32 arg2);

s32 ArenaStrDup_3701d0(s32 *arg0, s8 *arg1, s32 arg2, s32 arg3, s32 arg4)
{
    s32 var_2;
    s32 var_16;

    if (arg1 == NULL) {
        return 0;
    }
    if ((arg4 != 0) && (*arg1 == 0)) {
        return 0;
    }
    if (arg2 > 0) {
        var_2 = arg2 - 1;
    } else {
        var_2 = strlen(arg1);
    }
    if (var_2 <= 0) {
        return 0;
    }
    if (*arg0 != 0) {
        arg3 = ArenaAllocAligned_370330(arg0, var_2 + 1, 1, arg3);
    } else {
        arg3 = 0;
    }
    if (arg3 == 0) {
        return 0;
    }
    strncpy((void *) arg3, arg1, var_2);
    *(s8 *)(arg3 + var_2) = 0;
    return arg3;
}
