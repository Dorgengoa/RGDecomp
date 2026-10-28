/* rgp:protos */
#define RGP_SELF_MapAreaFindLoadedByName_1dc370 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void *MapAreaFindLoadedByName_1dc370(void *a0, char *a1)
{
    s32 c;
    void *r;

    if (a1 == 0) {
        return 0;
    }
    if (((unsigned char)MapDataIsLoaded_1e79d0((int)a0)) == 0) {
        return 0;
    }
    c = a1[0];
    if (c == *((char *)MapDataGetName_1e7bf0(a0))) {
        if (StrNotEqual_1f5300(a1 + 1, ((char *)MapDataGetName_1e7bf0(a0)) + 1) == 0) {
            return a0;
        }
    }
    r = MapAreaFindLoadedBlockByName_1dbd70(a0, a1);
    if (r != 0) {
        return r;
    }
    r = MapAreaFindLoadedShareByName_1dc0d0(a0, a1);
    if (r != 0) {
        return r;
    }
    return 0;
}
