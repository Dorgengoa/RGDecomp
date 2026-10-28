/* rgp:protos */
#define RGP_SELF_MapAreaFindActiveById_1dc4e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void *MapAreaFindActiveById_1dc4e0(void *self, s32 idx)
{
    void *r;

    if (idx < 0) {
        return NULL;
    }
    if (((unsigned char)MapDataIsLoadedOrUnloading_1e7980((int)self)) == 0) {
        return NULL;
    }
    if (idx == ((short)MapDataGetId_1e7bd0(self))) {
        return self;
    }
    r = MapAreaFindActiveBlockById_1dbf20(self, idx);
    if (r != NULL) {
        return r;
    }
    r = MapAreaFindActiveShareById_1dc280(self, idx);
    if (r != NULL) {
        return r;
    }
    return NULL;
}
