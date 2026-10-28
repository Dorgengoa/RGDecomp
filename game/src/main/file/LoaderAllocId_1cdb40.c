/* rgp:protos */
#define RGP_SELF_LoaderAllocId_1cdb40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

s32 LoaderAllocId_1cdb40(s8 *arg0) {
    s32 lim[2] = {0};
    s32 j;
    s32 i;
    s32 *p;

    j = *(s32 *)(arg0 + 4);
    lim[0] = 1000;
    lim[1] = j;
    for (i = 0; i < 2; i++) {
        p = &lim[i];
        for (; j < *p; j++) {
            if (LoaderIdInUse_1cdd70(arg0, j) == 0) {
                *(s32 *)(arg0 + 4) = j + 1;
                if (j + 1 >= 1000) {
                    *(s32 *)(arg0 + 4) = 0;
                }
                return j;
            }
        }
        j = 0;
    }
    return -1;
}
