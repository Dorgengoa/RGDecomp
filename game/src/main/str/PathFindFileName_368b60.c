/* rgp:protos */
#define RGP_SELF_PathFindFileName_368b60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern s32 strlen(s32);

void *PathFindFileName_368b60(s32 pad0, s32 arg1)
{
    s8 *p;
    s32 len;
    s32 i;
    void *r;

    if (arg1 == 0) {
        return NULL;
    }
    r = NULL;
    len = strlen(arg1);
    if (len > 0) {
        i = len - 1;
        p = (s8 *)(arg1 + len) - 1;
        for (; i >= 0; i--, p--) {
            if (*p == 0x5C || *p == 0x2F) {
                r = p + 1;
                break;
            }
        }
    }
    return r;
}
