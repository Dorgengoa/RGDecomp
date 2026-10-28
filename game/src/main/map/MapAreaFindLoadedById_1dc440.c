/* rgp:protos */
#define RGP_SELF_MapAreaFindLoadedById_1dc440 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void *MapAreaFindLoadedById_1dc440(void *self, s32 idx)
{
    void *r;

    if (idx < 0) {
        return NULL;
    }
    if (((unsigned char)MapDataIsLoaded_1e79d0((int)self)) == 0) {
        return NULL;
    }
    if (idx == ((short)MapDataGetId_1e7bd0(self))) {
        return self;
    }
    r = MapAreaFindLoadedBlockById_1dbe50(self, idx);
    if (r != NULL) {
        return r;
    }
    r = MapAreaFindLoadedShareById_1dc1b0(self, idx);
    if (r != NULL) {
        return r;
    }
    return NULL;
}
