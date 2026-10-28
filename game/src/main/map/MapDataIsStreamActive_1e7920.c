/* rgp:protos */
#define RGP_SELF_MapDataIsStreamActive_1e7920 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

s32 MapDataIsStreamActive_1e7920(s32 arg0) {
    s32 v;

    v = ((signed char)MapDataGetState_1e7a00(arg0)) == 2;
    if (v == 0) {
        v = ((signed char)MapDataGetState_1e7a00(arg0)) == 3;
    }
    if (v == 0) {
        v = ((signed char)MapDataGetState_1e7a00(arg0)) == 1;
    }
    return v;
}
