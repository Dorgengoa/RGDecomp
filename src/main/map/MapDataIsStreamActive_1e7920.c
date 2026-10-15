#include "types.h"

extern s32 MapDataGetState_1e7a00(s32 arg0);

s32 MapDataIsStreamActive_1e7920(s32 arg0) {
    s32 v;

    v = MapDataGetState_1e7a00(arg0) == 2;
    if (v == 0) {
        v = MapDataGetState_1e7a00(arg0) == 3;
    }
    if (v == 0) {
        v = MapDataGetState_1e7a00(arg0) == 1;
    }
    return v;
}
