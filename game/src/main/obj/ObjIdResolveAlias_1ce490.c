/* rgp:protos */
#define RGP_SELF_ObjIdResolveAlias_1ce490 1
#define RGP_SELF_conv 1
#include "port/game_protos.h"
#line 1
#include "types.h"

static inline s32 conv(s32 x, s32 k)
{
    return (x >= 0 && x < 12) ? x * 4 + k : -1;
}

s32 ObjIdResolveAlias_1ce490(s32 arg0, s32 arg1)
{
    if (arg1 == -1) {
        return arg0;
    }
    switch (arg1) {
    case -10:
        return conv(arg0, 12);
    case -11:
        return conv(arg0, 13);
    case -20:
        return conv(arg0, 14);
    case -21:
        return conv(arg0, 15);
    }
    return arg1;
}
